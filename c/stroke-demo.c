#include <stdio.h>
#include "gezira.h"
#include "gezira-image.h"

#include "SDL.h"
#ifdef main
#undef main
#endif 

typedef nile_Real_t real;

#define NTHREADS 0
#define DEFAULT_WIDTH  500
#define DEFAULT_HEIGHT 500

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

real path[] =
{
    100, 100, 200, 200, 300, 100,
    300, 100, 400, 200, 100, 400
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

    for (;;) {
        SDL_Event event;
        if (SDL_PollEvent (&event) && event.type == SDL_QUIT)
            break;

        SDL_FillRect (image, NULL, 0xffffffff);
        SDL_LockSurface (image);

            nile_Kernel_t *stroke =
                gezira_StrokeBeziers (nl, 5, gezira_StrokeJoinRound (nl),
                                             gezira_StrokeJoinRound (nl));
            nile_Kernel_t *sampler = gezira_UniformColor (nl, 1, 0, 0, 0);
            nile_Kernel_t *pipeline = nile_Pipeline (nl,
                stroke,
                gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_DecomposeBeziers (nl),
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
