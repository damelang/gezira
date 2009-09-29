#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct
{
    nile_Kernel_t kernel;
    nile_Real_t start_x, start_y;
} gezira_Sampler_t;

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k,
                nile_Real_t start_x, nile_Real_t start_y);

typedef struct
{
    gezira_Sampler_t sampler;
    nile_Real_t c_a, c_r, c_g, c_b;
} gezira_UniformColor_t;

gezira_Sampler_t *
gezira_UniformColor (gezira_UniformColor_t *k,
                     nile_Real_t c_a, nile_Real_t c_r,
                     nile_Real_t c_g, nile_Real_t c_b);

#endif
