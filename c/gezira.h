 /* THE .H FILE */

#ifndef GEZIRA_H
#define GEZIRA_H

#include "nile.h"

typedef struct {
	nile_Kernel_t base;
} gezira_Sampler_t;

nile_Kernel_t *
gezira_Sampler_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
	nile_Kernel_t base;
} gezira_Compositor_t;

nile_Kernel_t *
gezira_Compositor_clone(nile_t *nl, nile_Kernel_t *k_);

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_start_x;
	nile_Real_t v_start_y;
} gezira_Canvas_t;

nile_Kernel_t *
gezira_Canvas_clone(nile_t *nl, nile_Kernel_t *k_);

nile_Kernel_t *
gezira_Canvas(
	nile_t *nl, 
	nile_Kernel_t *k_, 
	nile_Real_t v_start_x, 
	nile_Real_t v_start_y
);

nile_Kernel_t *
gezira_CompositeSamplers(
	nile_t *nl, 
	nile_Kernel_t *v_s1, 
	nile_Kernel_t *v_s2, 
	nile_Kernel_t *v_c
);

static int 
gezira_CompositeSamplers_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_UniformColor(
	nile_t *nl, 
	nile_Real_t v_c_a, 
	nile_Real_t v_c_r, 
	nile_Real_t v_c_g, 
	nile_Real_t v_c_b
);

static int 
gezira_UniformColor_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_CompositeOver(nile_t *nl);

static int 
gezira_CompositeOver_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_FillBetweenEdges(
	nile_t *nl, 
	nile_Real_t v_x0
);

static int 
gezira_FillBetweenEdges_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_CreateSamplePoints(
	nile_t *nl, 
	nile_Real_t v_start_x, 
	nile_Real_t v_start_y
);

static int 
gezira_CreateSamplePoints_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_Render_(
	nile_t *nl, 
	nile_Kernel_t *v_s, 
	nile_Kernel_t *v_c
);

static int 
gezira_Render__process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_Render(
	nile_t *nl, 
	nile_Kernel_t *v_s, 
	nile_Kernel_t *v_c
);

static int 
gezira_Render_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_TransformBezier(
	nile_t *nl, 
	nile_Real_t v_m_a, 
	nile_Real_t v_m_b, 
	nile_Real_t v_m_c, 
	nile_Real_t v_m_d, 
	nile_Real_t v_m_e, 
	nile_Real_t v_m_f
);

static int 
gezira_TransformBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_ClipBezier(
	nile_t *nl, 
	nile_Real_t v_min_x, 
	nile_Real_t v_min_y, 
	nile_Real_t v_max_x, 
	nile_Real_t v_max_y
);

static int 
gezira_ClipBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);

nile_Kernel_t *
gezira_DecomposeBezier(nile_t *nl);

static int 
gezira_DecomposeBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
);



#endif

