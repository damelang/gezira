#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
#include "utils/all.h"

#define NBYTES_PER_THREAD 1000000
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define NFLAKES 300
#define FLAKE_ALPHA 0.7
#define FLAKE_RED   0.8
#define FLAKE_GREEN 0.9
#define FLAKE_BLUE  1.0

static int   is_zooming = 0;
static float zoom       = 1.00;
static float dzoom      = 0.01;

typedef struct {
    float x, y, dy, scale, angle, dangle;
} gezira_snowflake_t;

static void
gezira_snowflake_update (gezira_snowflake_t *flake)
{
    flake->y += flake->dy;
    flake->angle += flake->dangle;
    if (flake->y > WINDOW_HEIGHT + 10)
        flake->y = -10;
}

static int
gezira_snowflake_offscreen (gezira_snowflake_t *flake)
{
    float dx = WINDOW_WIDTH / fabs (flake->x - WINDOW_WIDTH/2);
    float dy = WINDOW_HEIGHT / fabs (flake->y - WINDOW_HEIGHT/2);
    return zoom > dx || zoom > dy;
}

static void
gezira_snowflake_render (gezira_snowflake_t *flake,
                         gezira_Window_t *window, nile_Process_t *init)
{
    nile_Process_t *pipeline;
    Matrix_t I;
    Matrix_t M = Matrix ();
    if (gezira_snowflake_offscreen (flake))
        return;
    M = Matrix_translate (M, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    M = Matrix_scale (M, zoom, zoom);
    M = Matrix_translate (M, -WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2);
    M = Matrix_translate (M, flake->x, flake->y);
    M = Matrix_rotate (M, flake->angle);
    M = Matrix_scale (M, flake->scale, flake->scale);
    I = Matrix_inverse (M);

    /*
    nile_Process_t *colors = nile_Process_pipe (
        gezira_ColorSpan (init, 1,    0.5,   0.1, 0.3,
                                1,   0.25,   0.4, 0.3, 0.5),
        gezira_ColorSpan (init, 1,   0.25,   0.4, 0.3,
                                1,      0,     0,   1, 0.5),
        NILE_NULL);
    */
    /*
     */
    nile_Process_t *colors = gezira_ColorSpan (init, 1,    0.5,   0.1, 0.3,
                                                     1,      0,   0.7, 0.3, 1);
    nile_Process_t *texture = nile_Process_pipe (
        gezira_TransformPoints (init, I.a, I.b, I.c, I.d, I.e, I.f),
        gezira_LinearGradient (init, 0, 0, 10, 10),
        //gezira_RadialGradient (init, 250, 250, 50),
        //gezira_RadialGradient (init, 0, 0, 20),
        gezira_ReflectGradient (init),
        gezira_ApplyColorSpans (init, colors),
        NILE_NULL);

    pipeline = nile_Process_pipe (
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
        gezira_Rasterize (init),
        gezira_ApplyTexture (init, texture),
        gezira_WriteToImage_ARGB32 (init, &window->image),
        NILE_NULL);
    nile_Process_feed (pipeline, snowflake_path, snowflake_path_n);
}

int
main (int argc, char **argv)
{
    int i;
    gezira_Window_t window;
    nile_Process_t *init;
    gezira_snowflake_t flakes[NFLAKES];
    int nthreads = 1;
    int mem_size;

    gezira_Window_init (&window, WINDOW_WIDTH, WINDOW_HEIGHT);

    for (i = 0; i < NFLAKES; i++) {
        flakes[i].x      = gezira_random (0, window.image.width);
        flakes[i].y      = gezira_random (0, window.image.height);
        flakes[i].dy     = gezira_random (0.5, 3.0);
        flakes[i].scale  = gezira_random (0.2, 0.7);
        flakes[i].angle  = gezira_random (0, 4);
        flakes[i].dangle = gezira_random (-0.1, 0.1);
    }

    mem_size = nthreads * NBYTES_PER_THREAD;
    init = nile_startup (malloc (mem_size), mem_size, nthreads);
    if (!init) {
        fprintf (stderr, "nile_startup failed\n");
        exit (1);
    }

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
                nile_sync (init);
                free (nile_shutdown (init));
                mem_size = nthreads * NBYTES_PER_THREAD;
                init = nile_startup (malloc (mem_size), mem_size, nthreads);
                gezira_Image_reset_gate (&window.image);
            }
            c = gezira_Window_key_pressed (&window);
        }
        if (!nthreads)
            break;

        gezira_Window_update_and_clear (&window, init, 1, 0, 0, 0);
        for (i = 0; i < NFLAKES; i++) {
            gezira_snowflake_render (&flakes[i], &window, init);
            gezira_snowflake_update (&flakes[i]);
        }

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

    nile_sync (init);
    free (nile_shutdown (init));
    //printf ("Just Window_fini left\n"); fflush (stdout);
    // TODO why does the line below cause a segfault every now and then?
    //gezira_Window_fini (&window);

    return 0;
}
