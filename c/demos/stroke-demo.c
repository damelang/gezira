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
#define STROKE_WIDTH   0.25

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

void
draw_handles (nile_t *nl, real *path, int path_n, SDL_Surface *image)
{
    real dot[6];
    int i;
    for (i = 0; i < path_n; i += 2) {
        dot[0] = dot[2] = path[i + 0];
        dot[1] = dot[3] = path[i + 1];
        dot[4] = dot[0] + 0.01;
        dot[5] = dot[1] + 0.01;
        nile_Kernel_t *stroke =
            gezira_StrokeBeziers (nl, 3, gezira_StrokeJoinRound (nl),
                                         gezira_StrokeJoinRound (nl));
        nile_Kernel_t *texture = gezira_CompositeTextures (nl,
                gezira_UniformColor (nl, 0.5, 1, 0, 0),
                gezira_ReadFromImage_ARGB32 (nl, image->pixels, DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                             image->pitch / 4),
                gezira_CompositeOver (nl));
        nile_Kernel_t *pipeline = nile_Pipeline (nl,
            stroke,
            gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
            gezira_Rasterize (nl),
            gezira_ApplyTexture (nl, texture),
            gezira_WriteToImage_ARGB32 (nl, image->pixels,
                                        DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                        image->pitch / 4),
            NULL);
        nile_feed (nl, pipeline, dot, 6, 6, 1);
    }
    nile_sync (nl);
}

int
main (int argc, char **argv)
{
    int i, j;
    SDL_Surface *image;
    nile_t *nl;
    char mem[500000];
    int vertex_index = -1;

    real path[] = {100, 100, 350, 200, 300, 100, 400, 200, 100, 400};
    int path_n = sizeof (path) / sizeof (path[0]);

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    for (;;) {
        SDL_Event event;

        if (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT)
                break;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    for (i = 0; i < path_n; i += 2) {
                        if (fabs (event.motion.x - path[i]    ) < 5 &&
                            fabs (event.motion.y - path[i + 1]) < 5) {
                            vertex_index = i;
                            break;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    vertex_index = -1;
                    break;
                case SDL_MOUSEMOTION:
                    if (vertex_index >= 0) {
                        path[vertex_index]     = event.motion.x;
                        path[vertex_index + 1] = event.motion.y;
                    }
                    break;
            }
        }

        SDL_FillRect (image, NULL, 0xffffffff);
        SDL_LockSurface (image);

            nile_Kernel_t *stroke =
                gezira_StrokeBeziers (nl, STROKE_WIDTH / 2,
                                      //gezira_StrokeJoinRound (nl),
                                      gezira_StrokeJoinMiter (nl, 1.1, 0),
                                      //gezira_StrokeJoinMiter (nl, 1, 0),

                                      //gezira_StrokeJoinRound (nl));
                                      //gezira_StrokeJoinMiter (nl, 1, 100));
                                      gezira_StrokeJoinMiter (nl, 1, 0));
            nile_Kernel_t *texture = gezira_UniformColor (nl, 1, 0, 0, 0);
            nile_Kernel_t *pipeline = nile_Pipeline (nl,
                stroke,
                gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_Rasterize (nl),
                gezira_ApplyTexture (nl, texture),
                gezira_WriteToImage_ARGB32 (nl, image->pixels,
                                            DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                            image->pitch / 4),
                NULL);

            real nile_path[path_n / 4 * 6];
            int nile_path_n = sizeof (nile_path) / sizeof (nile_path[0]);
            for (i = 0, j = 0; j < nile_path_n; i += 4) {
                real A_x = path[i + 0];
                real A_y = path[i + 1];
                real B_x = path[i + 2];
                real B_y = path[i + 3];
                real C_x = path[i + 4];
                real C_y = path[i + 5];
                nile_path[j++] = A_x;
                nile_path[j++] = A_y;
                nile_path[j++] = 2 * B_x - (A_x + C_x) / 2;
                nile_path[j++] = 2 * B_y - (A_y + C_y) / 2;
                nile_path[j++] = C_x;
                nile_path[j++] = C_y;
            }

            nile_feed (nl, pipeline, nile_path, 6, nile_path_n, 1);
            nile_sync (nl);

            draw_handles (nl, path, path_n, image);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
    }

    nile_free (nl);
    printf ("done\n");

    return 0;
}
