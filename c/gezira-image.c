#include "gezira.h"
#include "gezira-image.h"

#define real nile_Real_t

static inline real nile_Real_from_pixel (uint32_t p, int index)
{ return nile_Real_div (nile_Real (p >> (index * 8) & 0xff), nile_Real (255)); }

static inline uint32_t nile_Real_to_pixel (real a, int index)
{ return (nile_Real_to_int (nile_Real_mul (a, nile_Real (255))) & 0xff) << (index * 8); }

static inline real nile_Real_lerp (real a, real l, real b)
{ return nile_Real_add (nile_Real_mul (a, l),
                        nile_Real_mul (b, nile_Real_sub (nile_Real (1), l))); }

typedef struct {
    nile_Kernel_t base;
    uint32_t *v_pixels;
    int v_width;
    int v_height;
    int v_stride;
} gezira_ReadImage_ARGB32_t;

nile_Kernel_t *
gezira_ReadImage_ARGB32_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_ReadImage_ARGB32_t *k = (gezira_ReadImage_ARGB32_t *) k_;
    gezira_ReadImage_ARGB32_t *clone =
        (gezira_ReadImage_ARGB32_t *) nile_Kernel_clone (nl, k_);
    clone->v_pixels = k->v_pixels;
    clone->v_width  = k->v_width;
    clone->v_height = k->v_height;
    clone->v_stride = k->v_stride;
    return (nile_Kernel_t *) clone;
}

static int
gezira_ReadImage_ARGB32_process (nile_t *nl, nile_Kernel_t *k_,
                                 nile_Buffer_t **in_, nile_Buffer_t **out_)
{
    gezira_ReadImage_ARGB32_t *k = (gezira_ReadImage_ARGB32_t *) k_;
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    k_->initialized = 1;

    while (in->i < in->n) {
        real v_a, v_r, v_g, v_b;
        real v_x = nile_Buffer_shift (in);
        real v_y = nile_Buffer_shift (in);
        if (v_x >= nile_Real (0) && v_x <= nile_Real (k->v_width) &&
            v_y >= nile_Real (0) && v_y <= nile_Real (k->v_height)) {
            int x = nile_Real_to_int (v_x);
            int y = nile_Real_to_int (v_y);
            if (x == k->v_width)
                x--;
            if (y == k->v_height)
                y--;
            uint32_t p = k->v_pixels[y * k->v_stride + x];
            v_a = nile_Real_from_pixel (p, 3);
            v_r = nile_Real_from_pixel (p, 2);
            v_g = nile_Real_from_pixel (p, 1);
            v_b = nile_Real_from_pixel (p, 0);
        }
        else
            v_a = v_r = v_g = v_b = nile_Real (0);
        out = nile_Buffer_prepare_to_append (nl, out, 4, k_);
        nile_Buffer_append (out, v_a);
        nile_Buffer_append (out, v_r);
        nile_Buffer_append (out, v_g);
        nile_Buffer_append (out, v_b);
    }

    *out_ = out;
    return NILE_INPUT_CONSUMED;
}

nile_Kernel_t *
gezira_ReadImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                         int width, int height, int stride)
{
    gezira_ReadImage_ARGB32_t *k = NILE_KERNEL_NEW (nl, gezira_ReadImage_ARGB32);
    k->v_pixels = pixels;
    k->v_width  = width;
    k->v_height = height;
    k->v_stride = stride;
    return (nile_Kernel_t *) k;
}

typedef struct {
    gezira_Canvas_t base;
    uint32_t *v_pixels;
    int v_width;
    int v_height;
    int v_stride;
    uint32_t *v_p;
} gezira_WriteImage_ARGB32_t;

nile_Kernel_t *
gezira_WriteImage_ARGB32_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_WriteImage_ARGB32_t *k = (gezira_WriteImage_ARGB32_t *) k_;
    gezira_WriteImage_ARGB32_t *clone =
        (gezira_WriteImage_ARGB32_t *) gezira_Canvas_clone (nl, k_);
    clone->v_pixels = k->v_pixels;
    clone->v_width  = k->v_width;
    clone->v_height = k->v_height;
    clone->v_stride = k->v_stride;
    return (nile_Kernel_t *) clone;
}

static int
gezira_WriteImage_ARGB32_process (nile_t *nl, nile_Kernel_t *k_,
                                  nile_Buffer_t **in_, nile_Buffer_t **out_)
{
    gezira_WriteImage_ARGB32_t *k = (gezira_WriteImage_ARGB32_t *) k_;
    nile_Buffer_t *in = *in_;
    int x = nile_Real_to_int (k->base.v_start_x);
    int y = nile_Real_to_int (k->base.v_start_y);

    if (!k_->initialized) {
        if (x < 0 || y < 0 || y >= k->v_height)
            return NILE_INPUT_CONSUMED;
        k_->initialized = 1;
    }

    while (in->i < in->n && x < k->v_width) {
        real v_a = nile_Buffer_shift (in);
        real v_r = nile_Buffer_shift (in);
        real v_g = nile_Buffer_shift (in);
        real v_b = nile_Buffer_shift (in);
        real v_m = nile_Buffer_shift (in);
        uint32_t p = k->v_pixels[y * k->v_stride + x];
        real d_a = nile_Real_from_pixel (p, 3);
        real d_r = nile_Real_from_pixel (p, 2);
        real d_g = nile_Real_from_pixel (p, 1);
        real d_b = nile_Real_from_pixel (p, 0);
        v_a = nile_Real_lerp (v_a, v_m, d_a);
        v_r = nile_Real_lerp (v_r, v_m, d_r);
        v_g = nile_Real_lerp (v_g, v_m, d_g);
        v_b = nile_Real_lerp (v_b, v_m, d_b);
        p = nile_Real_to_pixel (v_a, 3) |
            nile_Real_to_pixel (v_r, 2) |
            nile_Real_to_pixel (v_g, 1) |
            nile_Real_to_pixel (v_b, 0);
        k->v_pixels[y * k->v_stride + x] = p;
        x++;
    }

    k->base.v_start_x = nile_Real (x);
    k->base.v_start_y = nile_Real (y);
    return NILE_INPUT_CONSUMED;
}

nile_Kernel_t *
gezira_WriteImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                          int width, int height, int stride)
{
    gezira_WriteImage_ARGB32_t *k = NILE_KERNEL_NEW (nl, gezira_WriteImage_ARGB32);
    k->v_pixels = pixels;
    k->v_width  = width;
    k->v_height = height;
    k->v_stride = stride;
    return (nile_Kernel_t *) k;
}
