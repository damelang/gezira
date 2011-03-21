#include <stdlib.h>
#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
//#include "test/nile-print.h"
#include "gezira-matrix.h"
#include "gezira-star-path.h"

#define MEM_SIZE 1000000
#define NTHREADS 1
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

int
main (int argc, char **argv)
{
    nile_Process_t *init;
    char *mem = malloc (MEM_SIZE);
    float angle = 0;
    float scale;
    int frames = 0;

    init = nile_startup (mem, MEM_SIZE, NTHREADS);
    if (!init)
        DIE ("nile_startup failed");

    while (frames < 100) {
        angle += 0.005;
        scale = fabs (angle - (int) angle - 0.5) * 10;

            matrix_t M = matrix_new ();
            M = matrix_translate (M, 250, 250);
            M = matrix_rotate (M, angle);
            M = matrix_scale (M, scale, scale);
            M = matrix_translate (M, -250, -250);

            nile_Process_t *tap = nile_Tap (init, 4);

            nile_Process_t *p = nile_Process_pipe (
                nile_Funnel (init),
                gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
                gezira_ClipBeziers (init, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_CalculateBounds (init),
                tap,
                //nile_PrintToFile (init, stdout),
                NILE_NULL);
            nile_Funnel_pour (p, star_path, star_path_n, 1);

            for (;;) {
                int i;
                int n = 0;
#define DATA_CAPACITY 4
                float data[DATA_CAPACITY];
                int EOS = nile_Tap_open (tap, data, &n, DATA_CAPACITY);
                for (i = 0; i < n; i++)
                    printf ("%.2f\n", data[i]);
                if (EOS)
                    break;
                if (nile_sync (init)) {
                    DIE ("sync failed");
                    break;
                }
            }
            //printf ("\n----------------------------------------------\n");

        frames++;
    }

    free (nile_shutdown (init));
    printf ("frames: %d\n", frames);

    return 0;
}
