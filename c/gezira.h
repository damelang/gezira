#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
} gezira_Sampler_t;

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k,
                nile_Real_t start_x, nile_Real_t start_y);

typedef struct {
    gezira_Sampler_t sampler;
    nile_Real_t v_c_a;
    nile_Real_t v_c_r;
    nile_Real_t v_c_g;
    nile_Real_t v_c_b;
} gezira_UniformColor_t;

gezira_Sampler_t *
gezira_UniformColor (gezira_UniformColor_t *k,
                     nile_Real_t c_a, nile_Real_t c_r,
                     nile_Real_t c_g, nile_Real_t c_b);

typedef struct {
    nile_Kernel_t kernel;
} gezira_Compositor_t;

nile_Kernel_t *
gezira_Compositor (gezira_Compositor_t *k);

typedef struct {
    gezira_Compositor_t compositor;
} gezira_CompositeOver_t;

gezira_Compositor_t *
gezira_CompositeOver (gezira_CompositeOver_t *k);

typedef struct {
    gezira_Sampler_t sampler;
    gezira_Sampler_t *v_s1;
    gezira_Sampler_t *v_s2;
    gezira_Compositor_t *v_c;
    nile_Interleave_t p_1;
} gezira_CompositeSamplers_t;

gezira_Sampler_t *
gezira_CompositeSamplers (gezira_CompositeSamplers_t *k,
                          gezira_Sampler_t *s1, gezira_Sampler_t *s2,
                          gezira_Compositor_t *c);

#endif
