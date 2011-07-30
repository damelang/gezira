#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "test/nile-print.h"
#include "gezira.h"
#include "gezira-image.h"
#include "utils/all.h"

#define NBYTES_PER_THREAD 1000000
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define NSTARS 500
#define PEN_WIDTH 5
#define MITER_LIMIT 4
#define PEN_CAP -1

static int   is_zooming = 0;
static float zoom       = 1.00;
static float dzoom      = 0.01;

static gezira_Window_t window;
static nile_Process_t *init;
static nile_Process_t *gate;

typedef struct {
    float x, y, dy, scale, angle, dangle, alpha, red, green, blue;
} gezira_star_t;

static void
gezira_star_update (gezira_star_t *star)
{
    star->y += star->dy;
    star->angle += star->dangle;
    if (star->y > WINDOW_HEIGHT + 10)
        star->y = -10;
}

static int
gezira_star_offscreen (gezira_star_t *star)
{
    float dx = WINDOW_WIDTH / fabs (star->x - WINDOW_WIDTH/2);
    float dy = WINDOW_HEIGHT / fabs (star->y - WINDOW_HEIGHT/2);
    return zoom > dx || zoom > dy;
}

static void
gezira_star_render (gezira_star_t *star)
{
    nile_Process_t *pipeline, *gate_, *COI;
    Matrix_t M = Matrix ();
    if (gezira_star_offscreen (star))
        return;
    M = Matrix_translate (M, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    M = Matrix_scale (M, zoom, zoom);
    M = Matrix_translate (M, -WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2);
    M = Matrix_translate (M, star->x, star->y);
    M = Matrix_rotate (M, star->angle);
    M = Matrix_scale (M, star->scale, star->scale);
    M = Matrix_translate (M, -250, -250);
    COI = gezira_CompositeUniformColorOverImage_ARGB32 (init,
        star->alpha, star->red, star->green, star->blue,
        window.pixels, window.width, window.height, window.width);
    gate_ = nile_Identity (init, 8);
    nile_Process_gate (COI, gate_);
    pipeline = nile_Process_pipe (
        gezira_StrokeBezierPath (init, PEN_WIDTH, MITER_LIMIT, PEN_CAP),
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
        gezira_Rasterize (init),
        gate,
        COI,
        NILE_NULL);
    nile_Process_feed (pipeline, star_path, star_path_n / 2);
    gate = gate_;
}

int
main (int argc, char **argv)
{
    int i;
    gezira_star_t stars[NSTARS];
    int nthreads = 1;
    int mem_size;

    gezira_Window_init (&window, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (i = 0; i < NSTARS; i++) {
        stars[i].x      = gezira_random (0, window.width);
        stars[i].y      = gezira_random (0, window.height);
        stars[i].dy     = gezira_random (0.5, 3.0);
        stars[i].scale  = gezira_random (0.1, 0.5);
        stars[i].angle  = gezira_random (0, 4);
        stars[i].dangle = gezira_random (-0.1, 0.1);
        stars[i].alpha  = 0.8;
        stars[i].red    = gezira_random (0, 1);
        stars[i].green  = gezira_random (0, 1);
        stars[i].blue   = gezira_random (0, 1);
    }

    mem_size = nthreads * NBYTES_PER_THREAD;
    init = nile_startup (malloc (mem_size), mem_size, nthreads);
    if (!init) {
        fprintf (stderr, "nile_startup failed\n");
        exit (1);
    }

    gate = nile_Identity (init, 8);

    for (;;) {
        char c = gezira_Window_key_pressed (&window);
        while (c != -1) {
            switch (c) {
                case ')': nthreads = 10; break;
                case '!': nthreads = 11; break;
                case '@': nthreads = 12; break;
                case '#': nthreads = 13; break;
                case '$': nthreads = 14; break;
                case '%': nthreads = 15; break;
                case '^': nthreads = 16; break;
                case '&': nthreads = 17; break;
                case '*': nthreads = 18; break;
                case '(': nthreads = 19; break;
                case 'z': is_zooming = !is_zooming;  break;
                default: nthreads = c - '0'; break;
            }
            if (!nthreads)
                break;
            if (c == 'z')
                break;
            printf ("Requesting %d threads\n", nthreads); fflush (stdout);
            if (nthreads < 0 || nthreads > 50)
                printf ("Invalid thread count\n");
            else {
                nile_Process_feed (gate, NULL, 0);
                nile_sync (init);
                free (nile_shutdown (init));
                mem_size = nthreads * NBYTES_PER_THREAD;
                init = nile_startup (malloc (mem_size), mem_size, nthreads);
                gate = nile_Identity (init, 8);
            }
            c = gezira_Window_key_pressed (&window);
        }
        if (!nthreads)
            break;

        gate = gezira_Window_update_and_clear (&window, init, gate, 1, 0, 0, 0);
        for (i = 0; i < NSTARS; i++) {
            gezira_star_render (&stars[i]);
            gezira_star_update (&stars[i]);
        }

        nile_sync (init);
        if (nile_error (init)) {
            fprintf (stderr, "nile error (OOM)\n"); fflush (stderr);
            break;
        }

        gezira_update_fps (init);

        if (is_zooming) {
            zoom += dzoom;
            if (zoom > 8 || zoom < 1 - dzoom)
                dzoom = -dzoom;
        }
    }

    nile_Process_feed (gate, NULL, 0);
    nile_sync (init);
    free (nile_shutdown (init));
    //printf ("Just Window_fini left\n"); fflush (stdout);
    // TODO why does the line below cause a segfault every now and then?
    //gezira_Window_fini (&window);

    return 0;
}
