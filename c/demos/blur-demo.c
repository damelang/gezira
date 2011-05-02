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

#define DIE(s, ...) \
do { \
    fprintf (stderr, "(%s:%4d) " s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
    exit (1); \
} while (0)

int
main (int argc, char **argv)
{
    SDL_Surface *image;
    nile_t *nl;
    char mem[500000];
    int width, height;
    int frames = 0;
    uint32_t *background_pixels;
    uint32_t *temp_pixels;

    ilInit ();
    if (argc < 2)
        DIE ("need background texture");

    ilBindImage (iluGenImage ());
    printf ("loading background: %s\n", argv[1]);
    ilLoadImage (argv[1]);
    width = ilGetInteger (IL_IMAGE_WIDTH);
    height = ilGetInteger (IL_IMAGE_HEIGHT);
    if (!width || !height)
        DIE ("Failed to load background image");
    background_pixels = malloc (width * height * 4);
    temp_pixels = malloc (width * height * 4);
    ilCopyPixels (0, 0, 0, width, height, 1, IL_BGRA,
                  IL_UNSIGNED_BYTE, background_pixels);

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (width, height, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    for (;;) {
        SDL_Event event;
        if (SDL_PollEvent (&event) && event.type == SDL_QUIT)
            break;
        SDL_LockSurface (image);

            nile_Kernel_t *s;
            nile_Real_t rect[] = {
              0, 0, 0, 0, width, 0,
              width, 0, width, 0, width, height,
              width, height, width, height, 0, height,
              0, height, 0, 0, 0, 0
            };
            
            // no blur
            /*
            s = nile_Pipeline (nl, gezira_ImageExtendPad (nl, width, height),
                gezira_ReadImage_ARGB32 (nl, background_pixels, width, height, width),
                NULL);
            nile_feed (nl, gezira_Render (nl, s,
                gezira_WriteImage_ARGB32 (nl, image->pixels, width, height,
                                              image->pitch / 4)),
                    rect, 6, 6*4, 1);
            nile_sync (nl);
            */

            // blur
            /*
            */
            s = gezira_GaussianBlur1x21 (nl, 0,
                nile_Pipeline (nl,
                    gezira_ImageExtendPad (nl, width, height),
                    gezira_ReadFromImage_ARGB32 (nl, background_pixels, width, height, width),
                    NULL));
            nile_feed (nl, nile_Pipeline (nl,
                gezira_Rasterize (nl),
                gezira_ApplyTexture (nl, s),
                gezira_WriteToImage_ARGB32 (nl, temp_pixels, width, height, width),
                NULL),
                rect, 6, 6*4, 1);
            nile_sync (nl);

            s = gezira_GaussianBlur21x1 (nl, 0,
                nile_Pipeline (nl,
                    gezira_ImageExtendPad (nl, width, height),
                    gezira_ReadFromImage_ARGB32 (nl, temp_pixels, width, height, width),
                    NULL));
            nile_feed (nl, nile_Pipeline (nl,
                gezira_Rasterize (nl),
                gezira_ApplyTexture (nl, s),
                gezira_WriteToImage_ARGB32 (nl, image->pixels, width, height,
                                                image->pitch / 4),
                NULL),
                rect, 6, 6*4, 1);
            nile_sync (nl);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
        frames++;
    }

    nile_free (nl);
    printf ("frames: %d\n", frames);

    return 0;
}
