#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct gezira_Sampler_ gezira_Sampler_t;

typedef struct gezira_Compositor_ gezira_Compositor_t;

typedef struct gezira_Canvas_ gezira_Canvas_t;

gezira_Sampler_t *
gezira_CompositeSamplers (nile_t *n,
                          gezira_Sampler_t *v_s1,
                          gezira_Sampler_t *v_s2,
                          gezira_Compositor_t *v_c);

gezira_Sampler_t *
gezira_UniformColor (nile_t *n,
                     nile_Real_t v_c_a,
                     nile_Real_t v_c_r,
                     nile_Real_t v_c_g,
                     nile_Real_t v_c_b);

gezira_Compositor_t *
gezira_CompositeOver (nile_t *n);

nile_Kernel_t *
gezira_FillBetweenEdges (nile_t *n,
                         nile_Real_t v_start_x,
                         nile_Real_t v_start_y);

nile_Kernel_t *
gezira_CreateSamplePoints (nile_t *n,
                           nile_Real_t v_start_x,
                           nile_Real_t v_start_y);

nile_Kernel_t *
gezira_Render_ (nile_t *n,
                gezira_Sampler_t *v_s,
                gezira_Canvas_t *v_c);

nile_Kernel_t *
gezira_Render (nile_t *n,
               gezira_Sampler_t *v_s,
               gezira_Canvas_t *v_c);

nile_Kernel_t *
gezira_TransformBezier (nile_t *n,
                        nile_Real_t v_m_a,
                        nile_Real_t v_m_b,
                        nile_Real_t v_m_c,
                        nile_Real_t v_m_d,
                        nile_Real_t v_m_e,
                        nile_Real_t v_m_f);

nile_Kernel_t *
gezira_ClipBezier (nile_t *n,
                   nile_Real_t v_min_x,
                   nile_Real_t v_min_y,
                   nile_Real_t v_max_x,
                   nile_Real_t v_max_y);

nile_Kernel_t *
gezira_DecomposeBezier (nile_t *n);

#endif
