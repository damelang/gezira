#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct {
    nile_Kernel_t kernel;
} gezira_Sampler_t;

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k);

typedef struct {
    nile_Kernel_t kernel;
} gezira_Compositor_t;

nile_Kernel_t *
gezira_Compositor (gezira_Compositor_t *k);

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
} gezira_Canvas_t;

nile_Kernel_t *
gezira_Canvas (gezira_Canvas_t *k,
               nile_Real_t start_x,
               nile_Real_t start_y);

typedef struct {
    gezira_Sampler_t sampler;
    gezira_Sampler_t *v_s1;
    gezira_Sampler_t *v_s2;
    gezira_Compositor_t *v_c;
    nile_Interleave_t p_1;
} gezira_CompositeSamplers_t;

gezira_Sampler_t *
gezira_CompositeSamplers (gezira_CompositeSamplers_t *k,
                          gezira_Sampler_t *s1,
                          gezira_Sampler_t *s2,
                          gezira_Compositor_t *c);

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
    gezira_Compositor_t compositor;
} gezira_CompositeOver_t;

gezira_Compositor_t *
gezira_CompositeOver (gezira_CompositeOver_t *k);

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
    nile_Real_t v_x;
    nile_Real_t v_local;
    nile_Real_t v_run;
} gezira_FillBetweenEdges_t;

nile_Kernel_t *
gezira_FillBetweenEdges (gezira_FillBetweenEdges_t *k,
                         nile_Real_t start_x,
                         nile_Real_t start_y);

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
    nile_Real_t v_x;
    nile_Real_t v_y;
} gezira_CreateSamplePoints_t;

nile_Kernel_t *
gezira_CreateSamplePoints (gezira_CreateSamplePoints_t *k,
                           nile_Real_t start_x,
                           nile_Real_t start_y);

typedef struct {
    nile_Kernel_t kernel;
    gezira_Sampler_t *v_s;
    gezira_Canvas_t *v_c;
    gezira_FillBetweenEdges_t p_1;
    nile_Interleave_t p_2;
    gezira_CreateSamplePoints_t p_3;
    nile_Id_t p_4;
} gezira_Render_1_t;

nile_Kernel_t *
gezira_Render_1 (gezira_Render_1_t *k,
                 gezira_Sampler_t *s,
                 gezira_Canvas_t *c);

typedef struct {
    nile_Kernel_t kernel;
    gezira_Sampler_t *v_s;
    gezira_Canvas_t *v_c;
    nile_GroupBy_t p_1;
    nile_SortBy_t p_2;
    gezira_Render_1_t p_3;
} gezira_Render_t;

nile_Kernel_t *
gezira_Render (gezira_Render_t *k,
               gezira_Sampler_t *s,
               gezira_Canvas_t *c);

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_m_a;
    nile_Real_t v_m_b;
    nile_Real_t v_m_c;
    nile_Real_t v_m_d;
    nile_Real_t v_m_e;
    nile_Real_t v_m_f;
} gezira_TransformBezier_t;

nile_Kernel_t *
gezira_TransformBezier (gezira_TransformBezier_t *k,
                        nile_Real_t m_a,
                        nile_Real_t m_b,
                        nile_Real_t m_c,
                        nile_Real_t m_d,
                        nile_Real_t m_e,
                        nile_Real_t m_f);

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_ClipBezier_t;

nile_Kernel_t *
gezira_ClipBezier (gezira_ClipBezier_t *k,
                   nile_Real_t min_x,
                   nile_Real_t min_y,
                   nile_Real_t max_x,
                   nile_Real_t max_y);

typedef struct {
    nile_Kernel_t kernel;
} gezira_DecomposeBezier_t;

nile_Kernel_t *
gezira_DecomposeBezier (gezira_DecomposeBezier_t *k);

#endif
