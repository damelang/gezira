#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira-image.h"
#include "stddef.h"

#define Real nile_Real_t

static inline uint8_t
Real_to_uint8_t (Real r)
{
    return nile_Real_toi (nile_Real_add (nile_Real_mul (r, nile_Real (255)), nile_Real (0.5)));
}

typedef struct {
    uint32_t *pixels;
    int       width;
    int       height;
    int       stride;
} gezira_Image_ARGB32_t;

static nile_Buffer_t *
gezira_ReadFromImage_ARGB32_body (nile_Process_t *p, nile_Buffer_t *in, nile_Buffer_t *out)
{
    gezira_Image_ARGB32_t image = *(gezira_Image_ARGB32_t *) nile_Process_vars (p);
    Real width = nile_Real (image.width);
    Real height = nile_Real (image.height);

    while (!nile_Buffer_is_empty (in)) {
        int m = (in->tail - in->head) / 2;
        int o = (out->capacity - out->tail) / 4;
        m = m < o ? m : o;
        while (m--) {
            Real x = nile_Buffer_pop_head (in);
            Real y = nile_Buffer_pop_head (in);
            x = nile_Real_nz (nile_Real_eq (x, width )) ? nile_Real_sub (width,  nile_Real (1)) : x;
            y = nile_Real_nz (nile_Real_eq (y, height)) ? nile_Real_sub (height, nile_Real (1)) : y;
            int OOB = nile_Real_nz (nile_Real_lt (x, nile_Real (0))) ||
                      nile_Real_nz (nile_Real_lt (y, nile_Real (0))) ||
                      nile_Real_nz (nile_Real_gt (x, width))         ||
                      nile_Real_nz (nile_Real_gt (y, height));
            x = OOB ? nile_Real (0) : x;
            y = OOB ? nile_Real (0) : y;
            uint32_t C = image.pixels[nile_Real_toi (x) + nile_Real_toi (y) * image.stride];
            C = OOB ? 0 : C;
            uint8_t a = C >> 24;
            uint8_t r = C >> 16;
            uint8_t g = C >>  8;
            uint8_t b = C >>  0;
            Real a_ = nile_Real_div (nile_Real (a), nile_Real (255));
            Real r_ = nile_Real_div (nile_Real (r), nile_Real (255));
            Real g_ = nile_Real_div (nile_Real (g), nile_Real (255));
            Real b_ = nile_Real_div (nile_Real (b), nile_Real (255));
            nile_Buffer_push_tail (out, a_); nile_Buffer_push_tail (out, r_);
            nile_Buffer_push_tail (out, g_); nile_Buffer_push_tail (out, b_);
        }
        if (nile_Buffer_tailroom (out) < 4)
            out = nile_Process_append_output (p, out);
    }
    return out;
}

nile_Process_t *
gezira_ReadFromImage_ARGB32 (nile_Process_t *p, uint32_t *pixels,
                            int width, int height, int stride)
{
    gezira_Image_ARGB32_t *image;
    p = nile_Process (p, 2, sizeof (*image), NULL, gezira_ReadFromImage_ARGB32_body, NULL);
    if (p) {
        image = nile_Process_vars (p);
        image->pixels = pixels;
        image->width  = width;
        image->height = height;
        image->stride = stride;
    }
    return p;
}

static nile_Buffer_t *
gezira_WriteToImage_ARGB32_body (nile_Process_t *p, nile_Buffer_t *in, nile_Buffer_t *out)
{
    gezira_Image_ARGB32_t image = *(gezira_Image_ARGB32_t *) nile_Process_vars (p);
    Real width = nile_Real (image.width);
    Real height = nile_Real (image.height);

    int m = (in->tail - in->head) / 8;
    while (m--) {
        uint8_t sa = Real_to_uint8_t (nile_Buffer_pop_head (in));
        uint8_t sr = Real_to_uint8_t (nile_Buffer_pop_head (in)); 
        uint8_t sg = Real_to_uint8_t (nile_Buffer_pop_head (in)); 
        uint8_t sb = Real_to_uint8_t (nile_Buffer_pop_head (in)); 
        int x = nile_Real_toi (nile_Buffer_pop_head (in));
        int y = nile_Real_toi (nile_Buffer_pop_head (in));
        uint8_t c  = Real_to_uint8_t (nile_Buffer_pop_head (in));
        uint8_t ic = Real_to_uint8_t (nile_Buffer_pop_head (in));
        uint32_t *px = &image.pixels[x + y * image.stride];
        uint32_t d = *px;
        uint8_t da = d >> 24;
        uint8_t dr = d >> 16;
        uint8_t dg = d >>  8;
        uint8_t db = d >>  0;
        uint16_t a = sa * c + da * ic;
        uint16_t r = sr * c + dr * ic;
        uint16_t g = sg * c + dg * ic;
        uint16_t b = sb * c + db * ic;

        a >>= 8;
        r >>= 8;
        g >>= 8;
        b >>= 8;
        
        /*
        a += 128;
        r += 128;
        g += 128;
        b += 128;
        a = (a + (a >> 8)) >> 8;
        r = (r + (r >> 8)) >> 8;
        g = (g + (g >> 8)) >> 8;
        b = (b + (b >> 8)) >> 8;
        */

        *px = (a << 24) | (r << 16) | (g << 8) | (b << 0);
    }
    return out;
}

nile_Process_t *
gezira_WriteToImage_ARGB32 (nile_Process_t *p, uint32_t *pixels,
                           int width, int height, int stride)
{
    gezira_Image_ARGB32_t *image;
    p = nile_Process (p, 8, sizeof (*image), NULL, gezira_WriteToImage_ARGB32_body, NULL);
    if (p) {
        image = nile_Process_vars (p);
        image->pixels = pixels;
        image->width  = width;
        image->height = height;
        image->stride = stride;
    }
    return p;
}

typedef struct {
    uint8_t                a8,  r8,  g8,  b8;
    uint16_t              a16, r16, g16, b16;
    uint32_t                        a8r8g8b8; 
    uint8_t                              ia8;
    gezira_Image_ARGB32_t              image;
} gezira_CompositeUniformColorOverImage_ARGB32_vars_t;

static nile_Buffer_t *
gezira_CompositeUniformColorOverImage_ARGB32_body (nile_Process_t *p, nile_Buffer_t *in, nile_Buffer_t *out)
{
    gezira_CompositeUniformColorOverImage_ARGB32_vars_t v =
        *(gezira_CompositeUniformColorOverImage_ARGB32_vars_t *) nile_Process_vars (p);

    while (!nile_Buffer_is_empty (in)) {
        int     x = nile_Real_toi (nile_Buffer_pop_head (in));
        int     y = nile_Real_toi (nile_Buffer_pop_head (in));
        uint8_t c = Real_to_uint8_t (nile_Buffer_pop_head (in));
        int     l = nile_Real_toi (nile_Buffer_pop_head (in));
        uint32_t *px = &v.image.pixels[x + y * v.image.stride];

        if (c) { // required, not just an optimization!
            uint32_t d  = *px;
            uint8_t  da = d >> 24;
            uint8_t  dr = d >> 16;
            uint8_t  dg = d >>  8;
            uint8_t  db = d >>  0;
            uint16_t a  = v.a8 * c;
            uint16_t r  = v.r8 * c;
            uint16_t g  = v.g8 * c;
            uint16_t b  = v.b8 * c;

            uint16_t ia = (255 * 255 - a) >> 8;
            a = (a + da * ia) >> 8;
            r = (r + dr * ia) >> 8;
            g = (g + dg * ia) >> 8;
            b = (b + db * ia) >> 8;

            /*
            uint16_t ia = (255 * 255 - a) + 128;
            ia = (ia + (ia >> 8)) >> 8;
            a = a + da * ia + 128;
            r = r + dr * ia + 128;
            g = g + dg * ia + 128;
            b = b + db * ia + 128;
            a = (a + (a >> 8)) >> 8;
            r = (r + (r >> 8)) >> 8;
            g = (g + (g >> 8)) >> 8;
            b = (b + (b >> 8)) >> 8;
            */

            *px = (a << 24) | (r << 16) | (g << 8) | (b << 0);
        }
        px++;

        if (!v.ia8) {
            while (l--)
                *px++ = v.a8r8g8b8;
        }
        else {
            int32_t *px_ = (int32_t *) px;
            while (l--) {
                int32_t d  = *px_;
                uint8_t  da = d >> 24;
                uint8_t  dr = d >> 16;
                uint8_t  dg = d >>  8;
                uint8_t  db = d >>  0;
                uint16_t a  = v.a16 + da * v.ia8;
                uint16_t r  = v.r16 + dr * v.ia8;
                uint16_t g  = v.g16 + dg * v.ia8;
                uint16_t b  = v.b16 + db * v.ia8;

                a >>= 8;
                r >>= 8;
                g >>= 8;
                b >>= 8;

                /*
                a = (a + (a >> 8)) >> 8;
                r = (r + (r >> 8)) >> 8;
                g = (g + (g >> 8)) >> 8;
                b = (b + (b >> 8)) >> 8;
                */

                *px_++ = (a << 24) | (r << 16) | (g << 8) | (b << 0);
            }
        }
    }
    return out;
}

nile_Process_t *
gezira_CompositeUniformColorOverImage_ARGB32 (nile_Process_t *p,
                                              float a, float r, float g, float b,
                                              uint32_t *pixels,
                                              int width, int height, int stride)
{
    gezira_CompositeUniformColorOverImage_ARGB32_vars_t *vars;
    p = nile_Process (p, 4, sizeof (*vars), NULL, gezira_CompositeUniformColorOverImage_ARGB32_body, NULL);
    if (p) {
        vars = nile_Process_vars (p);
        vars->a8 =     a * 255.0f + 0.5f;
        vars->r8 = a * r * 255.0f + 0.5f;
        vars->g8 = a * g * 255.0f + 0.5f;
        vars->b8 = a * b * 255.0f + 0.5f;
        vars->a16 =     a * 255.0f * 255.0f + 0.5f;
        vars->r16 = a * r * 255.0f * 255.0f + 0.5f;
        vars->g16 = a * g * 255.0f * 255.0f + 0.5f;
        vars->b16 = a * b * 255.0f * 255.0f + 0.5f;
        vars->a16 += 128;
        vars->r16 += 128;
        vars->g16 += 128;
        vars->b16 += 128;
        vars->a8r8g8b8 = (vars->a8 << 24) | (vars->r8 << 16) | (vars->g8 << 8) | (vars->b8 << 0);
        vars->ia8 = 255 - vars->a8;
        vars->image.pixels = pixels;
        vars->image.width  = width;
        vars->image.height = height;
        vars->image.stride = stride;
    }
    return p;
}
