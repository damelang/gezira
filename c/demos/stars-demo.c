#include <stdlib.h>
#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
#include "gezira-matrix.h"
#include "gezira-star-path.h"

#define BYTES_PER_THREAD 1000000
#define DEFAULT_WIDTH  1000
#define DEFAULT_HEIGHT 1000
#define NSTARS 500
#define NFRAMES_PER_FPS_UPDATE 50

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

#include <sys/time.h>
static
double gettimeofday_d ()
{
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000.0;
}

static float rand_upto (float max) { return rand () / (float) RAND_MAX * max; }

typedef struct {
    float alpha, red, green, blue, x, y, scale, rotation, angle;
} gezira_star_t;

static void
render_star (gezira_star_t *star, nile_Process_t *init, nile_Process_t *COI)
{
    matrix_t M = matrix_new ();
    M = matrix_translate (M, star->x, star->y);
    M = matrix_rotate (M, star->angle);
    M = matrix_scale (M, star->scale, star->scale);
    M = matrix_translate (M, -250, -250);

    nile_Process_t *p = nile_Process_pipe (
        nile_Funnel (init),
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (init),
        COI,
        NILE_NULL);
    nile_Funnel_pour (p, star_path, star_path_n, 1);
}

int
main (int argc, char **argv)
{
    int i;
    int frames = 0;
    uint32_t *pixels = malloc (DEFAULT_WIDTH * DEFAULT_HEIGHT * sizeof (uint32_t));
    nile_Process_t *init;
    gezira_star_t stars[NSTARS];

    if (argc < 2)
        DIE ("Need nthreads arg");
    int nthreads = atoi (argv[1]);
    if (nthreads < 1 || nthreads > 100)
        DIE ("Bad nthread arg");
    printf ("nthreads: %d\n", nthreads);
    int mem_size = nthreads * BYTES_PER_THREAD;
    char *mem = malloc (mem_size);
    init = nile_startup (mem, mem_size, nthreads);
    if (!init)
        DIE ("nile_startup failed");

    srand (17837643);
    for (i = 0; i < NSTARS; i++) {
        stars[i].alpha = rand_upto (1);
        stars[i].red = rand_upto (1);
        stars[i].green = rand_upto (1);
        stars[i].blue = rand_upto (1);
        stars[i].x = rand_upto (DEFAULT_WIDTH);
        stars[i].y = rand_upto (DEFAULT_HEIGHT);
        //stars[i].scale = rand_upto (1);
        stars[i].scale = 0.5 + rand_upto (0.5);
        stars[i].rotation = rand_upto (0.1);
        stars[i].angle = rand_upto (5);
    }

    double before = gettimeofday_d ();

    while (frames < 1000) {
        for (i = 0; i < DEFAULT_HEIGHT * DEFAULT_WIDTH; i++)
            pixels[i] = 0xffffffff;

        nile_Process_t *COI = gezira_CompositeUniformColorOverImage_ARGB32 (init,
                stars[0].alpha, stars[0].red, stars[0].green, stars[0].blue,
                pixels, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_WIDTH);
        for (i = 0; i < NSTARS - 1; i++) {
            nile_Process_t *COI_ = gezira_CompositeUniformColorOverImage_ARGB32 (init,
                    stars[i+1].alpha, stars[i+1].red, stars[i+1].green, stars[i+1].blue,
                    pixels, DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_WIDTH);
            COI = nile_Process_gate (COI, COI_);
            render_star (&stars[i], init, COI);
            COI = COI_;
            stars[i].angle += stars[i].rotation;
        }
        render_star (&stars[i], init, COI);
        stars[i].angle += stars[i].rotation;

        if (nile_sync (init)) {
            fprintf (stderr, "sync failed\n");
            break;
        }

        frames++;
        if (!(frames % NFRAMES_PER_FPS_UPDATE)) {
            double now = gettimeofday_d ();
            printf ("fps: %.2lf\n", NFRAMES_PER_FPS_UPDATE / (now - before));
            before = now;
        }
    }

    printf ("frames: %d\n", frames);
    free (nile_shutdown (init));
    free (pixels);

    return 0;
}
