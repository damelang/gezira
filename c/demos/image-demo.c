#include <stdio.h>
#include "gezira.h"
#include "gezira-image.h"
#include <IL/ilu.h>

#include "SDL.h"
#ifdef main
#undef main
#endif 

typedef nile_Real_t real;

#define NTHREADS 0
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500
#define TEXTURE_WIDTH  200
#define TEXTURE_HEIGHT 200

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

matrix_t
matrix_inverse (matrix_t M)
{
    real det = M.a * M.d - M.b * M.c;
    if (det == 0)
        return (matrix_t) {0, 0, 0, 0, 0, 0};
    real n = 1 / det;
    return (matrix_t)
        {n * M.d, -n * M.b, -n * M.c, n * M.a,
         n * (M.f * M.c - M.d * M.e), -n * (M.f * M.a - M.b * M.e)};
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
    char mem[400000];
    uint32_t texture_pixels[TEXTURE_WIDTH * TEXTURE_HEIGHT] = {0};
    real angle = 0;
    real scale;

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    ilInit ();
    ilBindImage (iluGenImage ());
    if (argc < 3)
        return -1;
    printf ("loading: %s\n", argv[1]);
    ilLoadImage (argv[1]);
    ilCopyPixels (0, 0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT, 1, IL_BGRA,
                  IL_UNSIGNED_BYTE, &texture_pixels);
    int filter = atoi (argv[2]);

    for (;;) {
        angle += 0.001;
        scale = fabs (angle - (int) angle - 0.5) * 10;
        SDL_Event event;
        if (SDL_PollEvent (&event) && event.type == SDL_QUIT)
            break;

        SDL_FillRect (image, NULL, 0);
        SDL_LockSurface (image);

            matrix_t M = matrix_new ();
            M = matrix_translate (M, 250, 250);
            M = matrix_rotate (M, angle);
            M = matrix_scale (M, scale, scale);
            M = matrix_translate (M, -250, -250);
            matrix_t I = matrix_inverse (M);

            nile_Kernel_t *texture =
                gezira_ReadImage_ARGB32 (nl, texture_pixels, TEXTURE_WIDTH,
                                         TEXTURE_HEIGHT, TEXTURE_WIDTH);
            /*
             */
            texture = nile_Pipeline (nl,
                    gezira_ImageExtendReflect (nl, TEXTURE_WIDTH, TEXTURE_HEIGHT),
                    texture, NULL);
            if (filter == 2)
                texture = gezira_BilinearFilter (nl, texture);
            if (filter == 3)
                texture = gezira_BicubicFilter (nl, texture);
            /*
             */
            texture = nile_Pipeline (nl, 
                gezira_TransformPoints (nl, I.a, I.b, I.c, I.d, I.e - 150, I.f - 125),
                texture, NULL);
            nile_Kernel_t *pipeline = nile_Pipeline (nl,
                gezira_TransformBeziers (nl, M.a, M.b, M.c, M.d, M.e, M.f),
                gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_Render (nl, texture,
                    gezira_WriteImage_ARGB32 (nl, image->pixels,
                                              DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                              image->pitch / 4)),
                NULL);

            nile_feed (nl, pipeline, path, 6, path_n, 1);
            nile_sync (nl);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
    }

    nile_free (nl);
    printf ("done\n");

    return 0;
}
