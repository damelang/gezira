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
     336,  748,  436,  848,  454,  863,
     454,  863,  499,  901,  551,  922,
     551,  922,  603,  943,  654,  943,
     654,  943,  740,  943,  802,  893,
     802,  893,  864,  843,  885,  748,
     885,  748,  988,  868, 1059,  905,
    1059,  905, 1130,  943, 1205,  943,
    1205,  943, 1278,  943, 1334,  905,
    1334,  905, 1391,  868, 1424,  783,
    1424,  783, 1446,  725, 1446,  601,
    1446,  601, 1446,  601, 1446,  207,
    1446,  207, 1446,  121, 1459,   89,
    1459,   89, 1469,   67, 1496,   51,
    1496,   51, 1523,   36, 1584,   36,
    1584,   36, 1584,   36, 1584,    0,
    1584,    0, 1584,    0, 1132,    0,
    1132,    0, 1132,    0, 1132,   36,
    1132,   36, 1132,   36, 1151,   36,
    1151,   36, 1210,   36, 1243,   59,
    1243,   59, 1266,   75, 1276,  110,
    1276,  110, 1280,  127, 1280,  207,
    1280,  207, 1280,  207, 1280,  601,
    1280,  601, 1280,  713, 1253,  759,
    1253,  759, 1214,  823, 1128,  823,
    1128,  823, 1075,  823, 1021,  796,
    1021,  796,  968,  770,  892,  698,
     892,  698,  892,  698,  890,  687,
     890,  687,  890,  687,  892,  644,
     892,  644,  892,  644,  892,  207,
     892,  207,  892,  113,  902,   90,
     902,   90,  913,   67,  942,   51,
     942,   51,  971,   36, 1041,   36,
    1041,   36, 1041,   36, 1041,    0,
    1041,    0, 1041,    0,  578,    0,
     578,    0,  578,    0,  578,   36,
     578,   36,  654,   36,  682,   54,
     682,   54,  711,   72,  722,  108,
     722,  108,  727,  125,  727,  207,
     727,  207,  727,  207,  727,  601,
     727,  601,  727,  713,  694,  762,
     694,  762,  650,  826,  571,  826,
     571,  826,  517,  826,  464,  797,
     464,  797,  381,  753,  336,  698,
     336,  698,  336,  698,  336,  207,
     336,  207,  336,  117,  348,   90,
     348,   90,  361,   63,  385,   49,
     385,   49,  410,   36,  485,   36,
     485,   36,  485,   36,  485,    0,
     485,    0,  485,    0,   32,    0,
      32,    0,   32,    0,   32,   36,
      32,   36,   95,   36,  120,   49,
     120,   49,  145,   63,  158,   92,
     158,   92,  171,  122,  171,  207,
     171,  207,  171,  207,  171,  557,
     171,  557,  171,  708,  162,  752,
     162,  752,  155,  785,  140,  797,
     140,  797,  125,  810,   99,  810,
      99,  810,   71,  810,   32,  795,
      32,  795,   32,  795,   17,  831,
      17,  831,   17,  831,  293,  943,
     293,  943,  293,  943,  336,  943,
     336,  943,  336,  943,  336,  748
};
int path_n = sizeof (path) / sizeof (path[0]);

int
main (int argc, char **argv)
{
    SDL_Surface *image;
    nile_t *nl;
#define MEM_N 2000000
    char *mem = malloc (MEM_N);

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, MEM_N);

    for (;;) {
        SDL_Event event;
        if (SDL_PollEvent (&event) && event.type == SDL_QUIT)
            break;

        SDL_FillRect (image, NULL, 0xffffffff);
        SDL_LockSurface (image);

            nile_Kernel_t *pipeline = nile_Pipeline (nl,
                    gezira_TransformBeziers (nl, 0.00625, 0, 0, -0.00625, 334.3, 163.75),
                    gezira_ClipBeziers (nl, 0, 0, 540, 260),
                    gezira_DecomposeBeziers (nl),
                    gezira_Render (nl,
                            gezira_CompositeSamplers (nl,
                                    gezira_UniformColor (nl, 1, 0, 0, 0),
                                    gezira_ReadImage_ARGB32 (nl, image->pixels,
                                                      DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                                      image->pitch / 4),
                                    gezira_CompositeOver (nl)),
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
    free (mem);
    printf ("done\n");

    return 0;
}
