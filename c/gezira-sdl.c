#include "gezira-sdl.h"

#define real nile_Real_t

typedef struct {
    nile_Kernel_t base;
    SDL_Surface *v_image;
} gezira_SDL_ReadImage_t;

nile_Kernel_t *
gezira_SDL_ReadImage_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_SDL_ReadImage_t *k = (gezira_SDL_ReadImage_t *) k_;
    gezira_SDL_ReadImage_t *clone =
        (gezira_SDL_ReadImage_t *) nile_Kernel_clone (nl, k_);
    clone->v_image = k->v_image;
    return (nile_Kernel_t *) clone;
}

static int
gezira_SDL_ReadImage_process (nile_t *nl, nile_Kernel_t *k_,
                              nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    gezira_SDL_ReadImage_t *k = (gezira_SDL_ReadImage_t *) k_;
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    // FIXME assuming 32-bit RGB for now
    uint32_t *pixels = (uint32_t *) k->v_image->pixels;
    // FIXME assuming pitch is multiple of bpp
    int stride = k->v_image->pitch / sizeof (uint32_t);
    uint32_t *p;

    while (in->i < in->n) {
        NILE_CONSUME_2 (in, v_x, v_y);
        p = pixels + ((int) v_y) * stride + ((int) v_x);
        // FIXME assuming alpha = 1 for now
        real v_a = 1;
        // FIXME assuming no nile_Real conversion macro needed for now
        // FIXME this _should_ be nile_Real_div etc.
        real v_r = ((nile_Real_t) (*p >> 16 & 0xff)) / 255;
        real v_g = ((nile_Real_t) (*p >>  8 & 0xff)) / 255;
        real v_b = ((nile_Real_t) (*p >>  0 & 0xff)) / 255;
        nile_prepare_to_produce (nl, k_, out, OUT_QUANTUM);
        nile_produce_4 (out, v_a, v_r, v_g, v_b);
    }

    *out_ = out;
    return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_SDL_ReadImage (nile_t *nl, SDL_Surface *image)
{
    gezira_SDL_ReadImage_t *k = NILE_KERNEL_NEW (nl, gezira_SDL_ReadImage);
    k->v_image = image;
    return (nile_Kernel_t *) k;
}

typedef struct {
    gezira_Canvas_t base;
    SDL_Surface *v_image;
    uint32_t *v_p;
} gezira_SDL_WriteImage_t;

nile_Kernel_t *
gezira_SDL_WriteImage_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_SDL_WriteImage_t *k = (gezira_SDL_WriteImage_t *) k_;
    gezira_SDL_WriteImage_t *clone =
        (gezira_SDL_WriteImage_t *) gezira_Canvas_clone (nl, k_);
    clone->v_image = k->v_image;
    return (nile_Kernel_t *) clone;
}

static int
gezira_SDL_WriteImage_process (nile_t *nl, nile_Kernel_t *k_,
                               nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    gezira_SDL_WriteImage_t *k = (gezira_SDL_WriteImage_t *) k_;
    nile_Buffer_t *in = *in_;
    uint32_t *v_p = k->v_p;

    if (!k_->initialized) {
        k_->initialized = 1;
        // FIXME assuming 32-bit RGB for now
        uint32_t *pixels = (uint32_t *) k->v_image->pixels;
        // FIXME assuming pitch is multiple of bpp
        int stride = k->v_image->pitch / sizeof (uint32_t);
        v_p = pixels + ((int) k->base.v_start_y) * stride +
                       ((int) k->base.v_start_x);
    }

    while (in->i < in->n) {
        NILE_CONSUME_5 (in, v_a, v_r, v_g, v_b, v_m);
        // FIXME this _should_ be nile_Real_div etc.
        real d_r = ((nile_Real_t) (*v_p >> 16 & 0xff)) / 255;
        real d_g = ((nile_Real_t) (*v_p >>  8 & 0xff)) / 255;
        real d_b = ((nile_Real_t) (*v_p >>  0 & 0xff)) / 255;
        v_r = d_r * (1 - v_m) + v_r * v_m;
        v_g = d_g * (1 - v_m) + v_g * v_m;
        v_b = d_b * (1 - v_m) + v_b * v_m;
        *v_p++ = ((uint8_t) (v_r * 255)) << 16 |
                 ((uint8_t) (v_g * 255)) <<  8 |
                 ((uint8_t) (v_b * 255)) <<  0;
    }

    k->v_p = v_p;
    return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_SDL_WriteImage (nile_t *nl, SDL_Surface *image)
{
    gezira_SDL_WriteImage_t *k = NILE_KERNEL_NEW (nl, gezira_SDL_WriteImage);
    k->v_image = image;
    return (nile_Kernel_t *) k;
}
