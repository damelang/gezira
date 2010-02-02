#include <stdio.h>
#include "gezira-sdl.h"

#define NTHREADS 4
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

nile_Real_t path[] =
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

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    SDL_LockSurface (image);

        nile_Kernel_t *pipeline = nile_Pipeline (nl,
            gezira_DecomposeBezier (nl),
            gezira_Render (nl,
                gezira_UniformColor (nl, 1, 1, 0, 0),
                gezira_SDL_WriteImage (nl, image)),
            NULL);

        nile_feed (nl, pipeline, path, path_n, 1);
        nile_sync (nl);

    SDL_UnlockSurface (image);
    SDL_Flip (image);

    for (;;) {
        SDL_Event event;
        SDL_WaitEvent (&event);

        if (event.type == SDL_QUIT)
            break;
    }

    nile_free (nl);
    printf ("done\n");

    return 0;
}
