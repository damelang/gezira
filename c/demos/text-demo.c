#include <stdio.h>
#include "gezira.h"
#include "gezira-image.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "SDL.h"
#ifdef main
#undef main
#endif 

typedef nile_Real_t real;

#define FT_FIXED_TO_REAL(fixed) nile_Real (fixed / 64.0)

#define NTHREADS 0
#define DEFAULT_WIDTH  1300
#define DEFAULT_HEIGHT  800

#define FONT_FILE "/Library/Fonts/Times New Roman.ttf"

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

#define PRODUCE_LINE(x0, y0, x1, y1) \
do { \
    path[(*path_n)++] = FT_FIXED_TO_REAL (x0); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (y0); \
    path[(*path_n)++] = (FT_FIXED_TO_REAL (x0) + FT_FIXED_TO_REAL (x1)) / 2; \
    path[(*path_n)++] = (FT_FIXED_TO_REAL (y0) + FT_FIXED_TO_REAL (y1)) / 2; \
    path[(*path_n)++] = FT_FIXED_TO_REAL (x1); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (y1); \
} while (0)

#define PRODUCE_BEZIER(x0, y0, x1, y1, x2, y2) \
do { \
    path[(*path_n)++] = FT_FIXED_TO_REAL (x0); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (y0); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (x1); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (y1); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (x2); \
    path[(*path_n)++] = FT_FIXED_TO_REAL (y2); \
} while (0)

static void
convert_glyph_outline (nile_Real_t *path, int *path_n, FT_Outline *outline)
{
    int i, first, contour_i;
    FT_Vector *points = outline->points;
    FT_Vector p0, p1, p2;

    first = 0;
    for (contour_i = 0; contour_i < outline->n_contours; contour_i++) {
        int n = outline->contours[contour_i] + 1;

        if (FT_CURVE_TAG (outline->tags[first]) != FT_CURVE_TAG_ON)
            DIE ("I don't handle this");

        for (i = first + 1; i < n;) {
            switch (FT_CURVE_TAG (outline->tags[i])) {
                case FT_CURVE_TAG_ON:
                    PRODUCE_LINE (points[i - 1].x, points[i - 1].y,
                                  points[i    ].x, points[i    ].y);
                    i++;
                    break;
                case FT_CURVE_TAG_CONIC:
                    if (FT_CURVE_TAG (outline->tags[i - 1]) != FT_CURVE_TAG_ON)
                        p0 = (FT_Vector) {(points[i - 1].x + points[i].x) >> 1,
                                          (points[i - 1].y + points[i].y) >> 1};
                    else
                        p0 = points[i - 1];
                    p1 = points[i++];
                    if (i < n) {
                        if (FT_CURVE_TAG (outline->tags[i]) != FT_CURVE_TAG_ON)
                            p2 = (FT_Vector) {(points[i - 1].x + points[i].x) >> 1,
                                              (points[i - 1].y + points[i].y) >> 1};
                        else
                            p2 = points[i++];
                    }
                    else {
                        p2 = points[first];
                        i++;
                    }
                    PRODUCE_BEZIER (p0.x, p0.y, p1.x, p1.y, p2.x, p2.y);
                    break;
                default:
                    DIE ("I don't handle this");
            }
        }
        if (i == n)
            PRODUCE_LINE (points[i - 1].x, points[i - 1].y,
                          points[first].x, points[first].y);
        first = n;
    }
}

static void
render_glyph (nile_t *nl, FT_Face ft_face, char c, matrix_t M,
              SDL_Surface *image)
{
    nile_Real_t path[512];
    int path_n = 0;
    FT_Error error;

    error = FT_Load_Char (ft_face, c, FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP);
    if (error)
        DIE ("Freetype failed!");
    convert_glyph_outline (path, &path_n, &ft_face->glyph->outline);

    nile_Kernel_t *texture = gezira_UniformColor (nl, 1, 0, 0, 0);
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
}

int
main (int argc, char **argv)
{
    SDL_Surface *image;

    nile_t *nl;
    char mem[500000];

    FT_Library ft;
    FT_Face ft_face;
    FT_Error ft_error;

    ft_error = FT_Init_FreeType (&ft);
    ft_error = FT_New_Face (ft, FONT_FILE, 0, &ft_face);
    ft_error = FT_Set_Pixel_Sizes (ft_face, 100, 0);
    if (ft_error != 0)
        DIE ("Freetype failed!");

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

            matrix_t M = matrix_new ();
            M = matrix_translate (M, 0, DEFAULT_HEIGHT);
            M = matrix_scale (M, 1, -1);

            render_glyph (nl, ft_face, 'G', matrix_translate (M, 100, 100), image);
            render_glyph (nl, ft_face, 'e', matrix_translate (M, 200, 100), image);
            render_glyph (nl, ft_face, 'z', matrix_translate (M, 300, 100), image);
            render_glyph (nl, ft_face, 'i', matrix_translate (M, 400, 100), image);
            render_glyph (nl, ft_face, 'r', matrix_translate (M, 500, 100), image);
            render_glyph (nl, ft_face, 'a', matrix_translate (M, 600, 100), image);

            render_glyph (nl, ft_face, '@', matrix_translate (M, 100, 300), image);
            render_glyph (nl, ft_face, '&', matrix_translate (M, 200, 300), image);
            render_glyph (nl, ft_face, 'Q', matrix_translate (M, 300, 300), image);
            render_glyph (nl, ft_face, '?', matrix_translate (M, 400, 300), image);
            render_glyph (nl, ft_face, '%', matrix_translate (M, 500, 300), image);

        SDL_UnlockSurface (image);
        SDL_Flip (image);
    }

    nile_free (nl);
    printf ("done\n");

    return 0;
}
