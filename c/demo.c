#include <stdio.h>
#include "gezira.h"
#include "gezira-image.h"
#include "SDL.h"

typedef nile_Real_t real;

#define NTHREADS 1
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

typedef struct {
    real a, b, c, d, e, f;
} matrix_t;

matrix_t
matrix_new () {
    matrix_t M = { 1, 0, 0, 1, 0, 0 };
    return M;
}

matrix_t
matrix_translate (matrix_t M, real x, real y)
{
    matrix_t N = { M.a, M.b, M.c, M.d,
                   M.a * x + M.c * y + M.e,
                   M.b * x + M.d * y + M.f};
    return N;
}

matrix_t
matrix_rotate (matrix_t M, real t)
{
    matrix_t N = { M.a *  cos (t) + M.c * sin (t),
                   M.b *  cos (t) + M.d * sin (t),
                   M.a * -sin (t) + M.c * cos (t),
                   M.b * -sin (t) + M.d * cos (t),
                   M.e, M.f};
    return N;
}

matrix_t
matrix_scale (matrix_t M, real sx, real sy)
{
    matrix_t N = { M.a * sx, M.b * sx, M.c * sy, M.d * sy, M.e, M.f};
    return N;
}

real path[] =
{
    250.00000, 150.00000, 237.65650, 183.01064, 225.31301, 216.02128,
    225.31301, 216.02128, 190.10368, 217.55979, 154.89434, 219.09830,
    154.89434, 219.09830, 182.47498, 241.03850, 210.05562, 262.97871,
    210.05562, 262.97871, 200.63855, 296.94020, 191.22147, 330.90169,
    191.22147, 330.90169, 220.61073, 311.45084, 250.00000, 292.00000,
    250.00000, 292.00000, 279.38926, 311.45084, 308.77852, 330.90169,
    308.77852, 330.90169, 299.36144, 296.94020, 289.94437, 262.97871,
    289.94437, 262.97871, 317.52501, 241.03850, 345.10565, 219.09830,
    345.10565, 219.09830, 309.89631, 217.55979, 274.68698, 216.02128,
    274.68698, 216.02128, 262.34349, 183.01064, 250.00000, 150.00000
};
int path_n = sizeof (path) / sizeof (path[0]);

int
main (int argc, char **argv)
{
    SDL_Surface *image;
    nile_t *nl;
    char mem[1000000];
    real angle = 0;
    real scale;

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    for (;;) {
        angle += 0.001;
        scale = fabs (angle - (int) angle - 0.5) * 10;
        SDL_Event event;
        if (SDL_PollEvent (&event) && event.type == SDL_QUIT)
            break;

        SDL_FillRect (image, NULL, 0xffffffff);
        SDL_LockSurface (image);

            matrix_t M = matrix_new ();
            M = matrix_translate (M, 250, 250);
            M = matrix_rotate (M, angle);
            M = matrix_scale (M, scale, scale);
            M = matrix_translate (M, -250, -250);

            //nile_Kernel_t *sampler = gezira_UniformColor (nl, 1, 1, 0, 0);
            nile_Kernel_t *sampler = gezira_CompositeSamplers (nl,
                gezira_UniformColor (nl, 0.5, 1, 0, 0),
                gezira_ReadImage_ARGB32 (nl, image->pixels,
                                         DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                         image->pitch / 4),
                gezira_CompositeOver (nl));

            nile_Kernel_t *pipeline = nile_Pipeline (nl,
                gezira_TransformBezier (nl, M.a, M.b, M.c, M.d, M.e, M.f),
                gezira_ClipBezier (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_DecomposeBezier (nl),
                gezira_Render (nl, sampler,
                    gezira_WriteImage_ARGB32 (nl, image->pixels,
                                              DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                              image->pitch / 4)),
                NULL);

            nile_feed (nl, pipeline, path, path_n, 1);
            nile_sync (nl);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
    }

    nile_free (nl);
    printf ("done\n");

    return 0;
}
