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
#define STROKE_WIDTH    10.0
#define SHADOW_ALPHA     0.8
#define SHADOW_OFFSET_X  2.0
#define SHADOW_OFFSET_Y  5.0
#define BLUR_WIDTH         5
#define BLUR_FLATTEN_FACTOR  0.5

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

real star_path[] =
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
int star_path_n = sizeof (star_path) / sizeof (star_path[0]);

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

void
draw_shadow (nile_t *nl, real *path, int path_n, nile_Kernel_t *k, SDL_Surface *image)
{
    uint32_t shadow_pixels[2][DEFAULT_WIDTH * DEFAULT_HEIGHT] = {{0},{0}};
    nile_Kernel_t *pipeline, *texture;
    real bbox[4];
    int bbox_path_n = 4*6;
    real bbox_path[bbox_path_n];
    int n = 0;

    // draw shadow

    pipeline = nile_Pipeline (nl, k->clone (nl, k),
        gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (nl),
        gezira_ApplyTexture (nl, gezira_UniformColor (nl, SHADOW_ALPHA, 0, 0, 0)),
        gezira_WriteToImage_ARGB32 (nl, shadow_pixels[0],
                                    DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                    DEFAULT_WIDTH),
        NULL);

    nile_feed (nl, pipeline, path, 6, path_n, 1);
    nile_sync (nl);

    // get shadow's bounding box

    pipeline = nile_Pipeline (nl, k,
        gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_CalculateBounds (nl),
        nile_Capture (nl, bbox, 4, &n),
        NULL);

    nile_feed (nl, pipeline, path, 6, path_n, 1);
    nile_sync (nl);

    // adjust bbox for blur

    bbox[0] = floor (bbox[0]) - (BLUR_WIDTH + 1) / 2;
    bbox[1] = floor (bbox[1]) - (BLUR_WIDTH + 1) / 2;
    bbox[2] = ceil  (bbox[2]) + (BLUR_WIDTH + 1) / 2;
    bbox[3] = ceil  (bbox[3]) + (BLUR_WIDTH + 1) / 2;

    // create bbox rectangle path

    bbox_path[0]  = bbox[0]; bbox_path[1]  = bbox[1];
    bbox_path[2]  = bbox[0]; bbox_path[3]  = bbox[1];
    bbox_path[4]  = bbox[0]; bbox_path[5]  = bbox[3];
    bbox_path[6]  = bbox[0]; bbox_path[7]  = bbox[3];
    bbox_path[8]  = bbox[0]; bbox_path[9]  = bbox[3];
    bbox_path[10] = bbox[2]; bbox_path[11] = bbox[3];
    bbox_path[12] = bbox[2]; bbox_path[13] = bbox[3];
    bbox_path[14] = bbox[2]; bbox_path[15] = bbox[3];
    bbox_path[16] = bbox[2]; bbox_path[17] = bbox[1];
    bbox_path[18] = bbox[2]; bbox_path[19] = bbox[1];
    bbox_path[20] = bbox[2]; bbox_path[21] = bbox[1];
    bbox_path[22] = bbox[0]; bbox_path[23] = bbox[1];

    // blur in x dimension

    texture =
        gezira_GaussianBlur5x1 (nl, BLUR_FLATTEN_FACTOR,
            nile_Pipeline (nl,
                gezira_ImageExtendPad (nl, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_ReadFromImage_ARGB32 (nl, shadow_pixels[0],
                                             DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                             DEFAULT_WIDTH),
                NULL));
    pipeline = nile_Pipeline (nl,
        gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (nl),
        gezira_ApplyTexture (nl, texture),
        gezira_WriteToImage_ARGB32 (nl, shadow_pixels[1],
                                    DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                    DEFAULT_WIDTH),
        NULL);

    nile_feed (nl, pipeline, bbox_path, 6, bbox_path_n, 1);
    nile_sync (nl);

    // blur in y dimension

    texture =
        gezira_GaussianBlur1x5 (nl, BLUR_FLATTEN_FACTOR,
            nile_Pipeline (nl,
                gezira_ImageExtendPad (nl, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_ReadFromImage_ARGB32 (nl, shadow_pixels[1],
                                             DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                             DEFAULT_WIDTH),
                NULL));
    pipeline = nile_Pipeline (nl,
        gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (nl),
        gezira_ApplyTexture (nl, texture),
        gezira_WriteToImage_ARGB32 (nl, shadow_pixels[0],
                                    DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                    DEFAULT_WIDTH),
        NULL);

    nile_feed (nl, pipeline, bbox_path, 6, bbox_path_n, 1);
    nile_sync (nl);

    // composite

    texture = gezira_CompositeTextures (nl,
            gezira_ReadFromImage_ARGB32 (nl, shadow_pixels[0],
                                         DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                         DEFAULT_WIDTH),
            gezira_ReadFromImage_ARGB32 (nl, image->pixels,
                                         DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                         image->pitch / 4),
            gezira_CompositeOver (nl));
    pipeline = nile_Pipeline (nl,
        gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
        gezira_Rasterize (nl),
        gezira_ApplyTexture (nl, texture),
        gezira_WriteToImage_ARGB32 (nl, image->pixels,
                                    DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                    image->pitch / 4),
        NULL);

    nile_feed (nl, pipeline, bbox_path, 6, bbox_path_n, 1);
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
    real angle = 0;
    real scale;
    uint32_t background_pixels[DEFAULT_WIDTH * DEFAULT_HEIGHT] = {0};
    int frames = 0;

    real stroke_path[] = {100, 100, 350, 200, 300, 100, 400, 200, 100, 400};
    int stroke_path_n = sizeof (stroke_path) / sizeof (stroke_path[0]);

    nile_Kernel_t *stroke, *texture, *pipeline;
    real gezira_stroke_path[stroke_path_n / 4 * 6];
    int gezira_stroke_path_n = sizeof (gezira_stroke_path) /
                               sizeof (gezira_stroke_path[0]);

    ilInit ();
    if (argc < 2)
        DIE ("need background texture");

    ilBindImage (iluGenImage ());
    printf ("loading background: %s\n", argv[1]);
    ilLoadImage (argv[1]);
    ilCopyPixels (0, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT, 1, IL_BGRA,
                  IL_UNSIGNED_BYTE, &background_pixels);
    SDL_Surface *background =
        SDL_CreateRGBSurfaceFrom (background_pixels, DEFAULT_WIDTH,
            DEFAULT_HEIGHT, 32, DEFAULT_WIDTH * 4,
            0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        DIE ("SDL_Init failed: %s", SDL_GetError ());
    if (!SDL_SetVideoMode (DEFAULT_WIDTH, DEFAULT_HEIGHT, 0,
                           SDL_HWSURFACE | SDL_ANYFORMAT | SDL_DOUBLEBUF))
        DIE ("SDL_SetVideoMode failed: %s", SDL_GetError ());
    image = SDL_GetVideoSurface ();

    nl = nile_new (NTHREADS, mem, sizeof (mem));

    for (;;) {
        SDL_Event event;
        angle += 0.005;
        scale = fabs (angle - (int) angle - 0.5) * 2;

        if (SDL_PollEvent (&event)) {
            if (event.type == SDL_QUIT)
                break;
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    for (i = 0; i < stroke_path_n; i += 2) {
                        if (fabs (event.motion.x - stroke_path[i]    ) < 5 &&
                            fabs (event.motion.y - stroke_path[i + 1]) < 5) {
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
                        stroke_path[vertex_index]     = event.motion.x;
                        stroke_path[vertex_index + 1] = event.motion.y;
                    }
                    break;
            }
        }

        for (i = 0, j = 0; j < gezira_stroke_path_n; i += 4) {
            real A_x = stroke_path[i + 0];
            real A_y = stroke_path[i + 1];
            real B_x = stroke_path[i + 2];
            real B_y = stroke_path[i + 3];
            real C_x = stroke_path[i + 4];
            real C_y = stroke_path[i + 5];
            gezira_stroke_path[j++] = A_x;
            gezira_stroke_path[j++] = A_y;
            gezira_stroke_path[j++] = 2 * B_x - (A_x + C_x) / 2;
            gezira_stroke_path[j++] = 2 * B_y - (A_y + C_y) / 2;
            gezira_stroke_path[j++] = C_x;
            gezira_stroke_path[j++] = C_y;
        }

        SDL_FillRect (image, NULL, 0xffffffff);
        SDL_BlitSurface (background, NULL, image, NULL);
        SDL_LockSurface (image);

            matrix_t M = matrix_new ();
            M = matrix_translate (M, 250, 250);
            M = matrix_rotate (M, angle);
            M = matrix_scale (M, scale, scale);
            M = matrix_translate (M, -250, -250);

            // stroke shadow

            draw_shadow (nl, gezira_stroke_path, gezira_stroke_path_n,
                nile_Pipeline (nl,
                    gezira_TransformBeziers (nl, 1, 0, 0, 1, SHADOW_OFFSET_X, SHADOW_OFFSET_Y),
                    gezira_StrokeBeziers (nl, STROKE_WIDTH / 2,
                                          gezira_StrokeJoinRound (nl),
                                          gezira_StrokeJoinRound (nl)),
                    NULL),
                image);

            // stroke

            stroke =
                gezira_StrokeBeziers (nl, STROKE_WIDTH / 2,
                                      gezira_StrokeJoinRound (nl),
                                      gezira_StrokeJoinRound (nl));
            texture = gezira_UniformColor (nl, 1, 0, 0, 0);
            pipeline = nile_Pipeline (nl,
                stroke,
                gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_Rasterize (nl),
                gezira_ApplyTexture (nl, texture),
                gezira_WriteToImage_ARGB32 (nl, image->pixels,
                                            DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                            image->pitch / 4),
                NULL);

            nile_feed (nl, pipeline, gezira_stroke_path, 6, gezira_stroke_path_n, 1);
            nile_sync (nl);

            // handles

            draw_handles (nl, stroke_path, stroke_path_n, image);

            // star shadow

            draw_shadow (nl, star_path, star_path_n, 
                gezira_TransformBeziers (nl, M.a, M.b, M.c, M.d,
                                         M.e + SHADOW_OFFSET_X, M.f + SHADOW_OFFSET_Y),
                image);

            // star

            texture = gezira_UniformColor (nl, 1, 1, 0, 0);
            pipeline = nile_Pipeline (nl,
                gezira_TransformBeziers (nl, M.a, M.b, M.c, M.d, M.e, M.f),
                gezira_ClipBeziers (nl, 0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT),
                gezira_Rasterize (nl),
                gezira_ApplyTexture (nl, texture),
                gezira_WriteToImage_ARGB32 (nl, image->pixels,
                                            DEFAULT_WIDTH, DEFAULT_HEIGHT,
                                            image->pitch / 4),
                NULL);

            nile_feed (nl, pipeline, star_path, 6, star_path_n, 1);
            nile_sync (nl);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
        frames++;
    }

    nile_free (nl);
    printf ("frames: %d\n", frames);

    return 0;
}
