#include <stdio.h>
#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"
#include "gezira-image.h"
#include "utils/all.h"

#define NBYTES_PER_THREAD 1000000
#define NFALLING_GLYPHS   5000

static int   window_width  = 600;
static int   window_height = 600;
static int   window_x      =   0;
static int   window_y      =   0;
static int   is_zooming    =   0;
static float zoom          =   1.00;
static float dzoom         =   0.01;

static gezira_Window_t window;
static nile_Process_t *init;
static nile_Process_t *gate;

#include <ft2build.h>
#include FT_FREETYPE_H
#define FT_FIXED_TO_FLOAT(fixed) (fixed / 64.0f)
#define FONT_FILE "/Library/Fonts/Times New Roman.ttf"

typedef struct {
    char  c;
    float path[512];
    int   path_n;
} glyph_t;

#define PRODUCE_LINE(x0, y0, x1, y1) \
do { \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (x0); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (y0); \
    path[(*path_n)++] = (FT_FIXED_TO_FLOAT (x0) + FT_FIXED_TO_FLOAT (x1)) / 2; \
    path[(*path_n)++] = (FT_FIXED_TO_FLOAT (y0) + FT_FIXED_TO_FLOAT (y1)) / 2; \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (x1); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (y1); \
} while (0)

#define PRODUCE_BEZIER(x0, y0, x1, y1, x2, y2) \
do { \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (x0); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (y0); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (x1); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (y1); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (x2); \
    path[(*path_n)++] = FT_FIXED_TO_FLOAT (y2); \
} while (0)

static void
convert_glyph_outline (float *path, int *path_n, FT_Outline *outline)
{
    int i, first, contour_i;
    FT_Vector *points = outline->points;
    FT_Vector p0, p1, p2;

    first = 0;
    for (contour_i = 0; contour_i < outline->n_contours; contour_i++) {
        int n = outline->contours[contour_i] + 1;

        if (FT_CURVE_TAG (outline->tags[first]) != FT_CURVE_TAG_ON) {
            fprintf (stderr, "I don't handle this\n");
            exit (1);
        }

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
                    fprintf (stderr, "I don't handle this\n");
                    exit (1);
            }
        }
        if (i == n)
            PRODUCE_LINE (points[i - 1].x, points[i - 1].y,
                          points[first].x, points[first].y);
        first = n;
    }
}

static void
load_glyph_path (glyph_t *glyph, FT_Face ft_face)
{
    FT_Error error;
    error = FT_Load_Char (ft_face, glyph->c, FT_LOAD_NO_HINTING | FT_LOAD_NO_BITMAP);
    if (error) {
        fprintf (stderr, "Freetype failed!\n");
        exit (1);
    }
    convert_glyph_outline (glyph->path, &glyph->path_n, &ft_face->glyph->outline);
}

typedef struct {
    float  x, y, dy, scale, angle, dangle, alpha, red, green, blue;
    glyph_t *glyph;
} gezira_falling_glyph_t;

static void
gezira_falling_glyph_update (gezira_falling_glyph_t *fglyph)
{
    fglyph->y += fglyph->dy;
    fglyph->angle += fglyph->dangle;
    if (fglyph->y > window_height + 20)
        fglyph->y = -20;
}

static int
gezira_falling_glyph_offscreen (gezira_falling_glyph_t *fglyph)
{
    float dx = window_width / fabs (fglyph->x - window_width/2);
    float dy = window_height / fabs (fglyph->y - window_height/2);
    return zoom > dx || zoom > dy;
}

static void
gezira_falling_glyph_render (gezira_falling_glyph_t *fglyph)
{
    nile_Process_t *pipeline, *gate_, *COI;
    Matrix_t M = Matrix ();
    if (gezira_falling_glyph_offscreen (fglyph))
        return;

    M = Matrix_translate (M, window_width / 2, window_height / 2);
    M = Matrix_scale (M, zoom, zoom);
    M = Matrix_translate (M, -window_width / 2, -window_height / 2);
    //M = Matrix_translate (M, 0, window_height);
    M = Matrix_scale (M, 1, -1);
    M = Matrix_translate (M, fglyph->x, -fglyph->y);
    M = Matrix_scale (M, fglyph->scale, fglyph->scale);
    M = Matrix_rotate (M, fglyph->angle);
    M = Matrix_translate (M, -20, -20);

    COI = gezira_CompositeUniformColorOverImage_ARGB32 (init,
        fglyph->alpha, fglyph->red, fglyph->green, fglyph->blue,
        window.pixels, window.width, window.height, window.width);
    gate_ = nile_Identity (init);
    nile_Process_gate (COI, gate_);

    pipeline = nile_Process_pipe (
        gezira_TransformBeziers (init, M.a, M.b, M.c, M.d, M.e, M.f),
        gezira_ClipBeziers (init, 0, 0, window_width, window_height),
        gezira_Rasterize (init),
        gate,
        COI,
        NILE_NULL);
    nile_Process_feed (pipeline, fglyph->glyph->path, fglyph->glyph->path_n);
    gate = gate_;
}

int
main (int argc, char **argv)
{
    int i;
    gezira_falling_glyph_t fglyphs[NFALLING_GLYPHS];
    int nthreads = 1;
    int mem_size;
    FT_Library ft;
    FT_Face ft_face;
    FT_Error ft_error;
    static glyph_t glyphs[] = {
        {'a'}, {'b'}, {'c'}, {'d'},
        {'e'}, {'f'}, {'g'}, {'h'},
        {'i'}, {'j'}, {'k'}, {'l'},
        {'m'}, {'n'}, {'o'}, {'p'},
        {'q'}, {'r'}, {'s'}, {'t'},
        {'u'}, {'v'}, {'w'}, {'x'},
        {'y'}, {'z'},
    };
    int nglyphs = (sizeof (glyphs) / sizeof (glyphs[0]));

    if (argc == 5) {
        window_x = atoi (argv[1]);
        window_y = atoi (argv[2]);
        window_width = atoi (argv[3]);
        window_height = atoi (argv[4]);
        if (window_width <= 0 || window_height <= 0) {
            fprintf (stderr, "Bad window dimensions\n");
            exit (1);
        }
    }

    gezira_Window_init (&window, window_x, window_y, window_width, window_height, 0);

    ft_error = FT_Init_FreeType (&ft);
    ft_error = FT_New_Face (ft, FONT_FILE, 0, &ft_face);
    ft_error = FT_Set_Pixel_Sizes (ft_face, 100, 0);
    if (ft_error != 0) {
        fprintf (stderr, "freetype failed\n");
        exit (1);
    }
    for (i = 0; i < nglyphs; i++)
        load_glyph_path (&glyphs[i], ft_face);

    for (i = 0; i < NFALLING_GLYPHS; i++) {
        fglyphs[i].x      = gezira_random (0, window.width);
        fglyphs[i].y      = gezira_random (0, window.height);
        fglyphs[i].dy     = gezira_random (0.5, 2.5);
        fglyphs[i].scale  = 0.17;
        //fglyphs[i].scale  = gezira_random (0.1, 0.3);
        fglyphs[i].angle  = gezira_random (0, 4);
        fglyphs[i].dangle = gezira_random (-0.1, 0.1);
        /*
        fglyphs[i].alpha  = 1;
        fglyphs[i].red    = 0;
        fglyphs[i].green  = 0;
        fglyphs[i].blue   = 0;
        */
        fglyphs[i].alpha  = gezira_random (0.7, 0.9);
        fglyphs[i].red    = gezira_random (0, 1);
        fglyphs[i].green  = gezira_random (0, 1);
        fglyphs[i].blue   = gezira_random (0, 1);
        fglyphs[i].glyph  = &glyphs[i % nglyphs];
    }

    mem_size = nthreads * NBYTES_PER_THREAD;
    init = nile_startup (malloc (mem_size), mem_size, nthreads);
    if (!init) {
        fprintf (stderr, "nile_startup failed\n");
        exit (1);
    }

    gate = nile_Identity (init);

    for (;;) {
        char c = gezira_Window_key_pressed (&window);
        while (c != -1) {
            switch (c) {
                case ')': nthreads = 10; break;
                case '!': nthreads = 11; break;
                case '@': nthreads = 12; break;
                case '#': nthreads = 13; break;
                case '$': nthreads = 14; break;
                case '%': nthreads = 15; break;
                case '^': nthreads = 16; break;
                case '&': nthreads = 17; break;
                case '*': nthreads = 18; break;
                case '(': nthreads = 19; break;
                case 'z': is_zooming = !is_zooming;  break;
                default: nthreads = c - '0'; break;
            }
            if (!nthreads)
                break;
            if (c == 'z')
                break;
            printf ("Requesting %d threads\n", nthreads); fflush (stdout);
            if (nthreads < 0 || nthreads > 50)
                printf ("Invalid thread count\n");
            else {
                nile_Process_feed (gate, NULL, 0);
                nile_sync (init);
                free (nile_shutdown (init));
                mem_size = nthreads * NBYTES_PER_THREAD;
                init = nile_startup (malloc (mem_size), mem_size, nthreads);
                gate = nile_Identity (init);
            }
            c = gezira_Window_key_pressed (&window);
        }
        if (!nthreads)
            break;

        gate = gezira_Window_update_and_clear (&window, init, gate, 1, 1, 1, 1);
        for (i = 0; i < NFALLING_GLYPHS; i++) {
            gezira_falling_glyph_render (&fglyphs[i]);
            gezira_falling_glyph_update (&fglyphs[i]);
        }

        if (nile_error (init)) {
            fprintf (stderr, "nile error (OOM)\n"); fflush (stderr);
            break;
        }

        gezira_update_fps (init);

        if (is_zooming) {
            zoom += dzoom;
            if (zoom > 8 || zoom < 1 - dzoom)
                dzoom = -dzoom;
        }
    }

    nile_Process_feed (gate, NULL, 0);
    nile_sync (init);
    free (nile_shutdown (init));
    //gezira_Window_fini (&window);

    return 0;
}
