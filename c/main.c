#include <stdio.h>
#include "gezira-sdl.h"

#define NTHREADS 1
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

nile_Real_t path[] =
{
    100, 100, 300, 200, 300, 200,
    300, 200, 200, 300, 200, 300,
    200, 300, 100, 100, 100, 100
};
int path_n = sizeof (path) / sizeof (path[0]);

int
main (int argc, char **argv)
{
    SDL_Surface *image;
    nile_t *nl;
    char mem[1000000];

    if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT))
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
    SDL_UpdateRect (image, 0, 0, 0, 0);

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
