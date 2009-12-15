/* THE .C FILE */

#include <stddef.h>
#include "gezira.h"

nile_Kernel_t *
gezira_Sampler_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_Sampler_t *k = (gezira_Sampler_t *) k_;
	gezira_Sampler_t *clone = (gezira_Sampler_t *) nile_Kernel_clone(nl, k_);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_Compositor_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_Compositor_t *k = (gezira_Compositor_t *) k_;
	gezira_Compositor_t *clone = (gezira_Compositor_t *) nile_Kernel_clone(nl, k_);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_Canvas_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
	gezira_Canvas_t *clone = (gezira_Canvas_t *) nile_Kernel_clone(nl, k_);
	clone->v_start_x = k->v_start_x;
	clone->v_start_y = k->v_start_y;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_Canvas(
	nile_t *nl, 
	nile_Kernel_t *k_, 
	nile_Real_t v_start_x, 
	nile_Real_t v_start_y
) {
	gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
	k->v_start_x = v_start_x;
	k->v_start_y = v_start_y;
	return (nile_Kernel_t *) k;
}

typedef struct {
	nile_Kernel_t base;
	nile_Kernel_t *v_s1;
	nile_Kernel_t *v_s2;
	nile_Kernel_t *v_c;
} gezira_CompositeSamplers_t;

static nile_Kernel_t *
gezira_CompositeSamplers_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
	gezira_CompositeSamplers_t *clone = (gezira_CompositeSamplers_t *) nile_Kernel_clone(nl, k_);
	clone->v_s1 = k->v_s1->clone(nl, k->v_s1);
	clone->v_s2 = k->v_s2->clone(nl, k->v_s2);
	clone->v_c = k->v_c->clone(nl, k->v_c);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_CompositeSamplers(
	nile_t *nl, 
	nile_Kernel_t *v_s1, 
	nile_Kernel_t *v_s2, 
	nile_Kernel_t *v_c
) {
	gezira_CompositeSamplers_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSamplers);
	k->v_s1 = v_s1;
	k->v_s2 = v_s2;
	k->v_c = v_c;
	return (nile_Kernel_t *) k;
}

static int 
gezira_CompositeSamplers_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
	nile_Kernel_t *v_s1 = k->v_s1;
	nile_Kernel_t *v_s2 = k->v_s2;
	nile_Kernel_t *v_c = k->v_c;

	if (!k_->initialized) {
		k_->initialized = 1;
{ }
nile_Real_t t_1 = 4;
nile_Real_t t_2 = 4;
nile_Kernel_t *t_3 = nile_Interleave(nl, v_s1, t_1, v_s2, t_2);
nile_Kernel_t *t_4 = nile_Pipeline(nl, t_3, v_c, NULL);
		nile_Kernel_t *f = t_4;
		f->downstream = k_->downstream;
		k_->downstream = f;
	}

	return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_c_a;
	nile_Real_t v_c_r;
	nile_Real_t v_c_g;
	nile_Real_t v_c_b;
} gezira_UniformColor_t;

static nile_Kernel_t *
gezira_UniformColor_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
	gezira_UniformColor_t *clone = (gezira_UniformColor_t *) nile_Kernel_clone(nl, k_);
	clone->v_c_a = k->v_c_a;
	clone->v_c_r = k->v_c_r;
	clone->v_c_g = k->v_c_g;
	clone->v_c_b = k->v_c_b;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_UniformColor(
	nile_t *nl, 
	nile_Real_t v_c_a, 
	nile_Real_t v_c_r, 
	nile_Real_t v_c_g, 
	nile_Real_t v_c_b
) {
	gezira_UniformColor_t *k = NILE_KERNEL_NEW(nl, gezira_UniformColor);
	k->v_c_a = v_c_a;
	k->v_c_r = v_c_r;
	k->v_c_g = v_c_g;
	k->v_c_b = v_c_b;
	return (nile_Kernel_t *) k;
}

static int 
gezira_UniformColor_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
	nile_Real_t v_c_a = k->v_c_a;
	nile_Real_t v_c_r = k->v_c_r;
	nile_Real_t v_c_g = k->v_c_g;
	nile_Real_t v_c_b = k->v_c_b;

	if (!k_->initialized) {
		k_->initialized = 1;
	}

	while (in->i < in->n) {
		nile_Real_t v_p_x = nile_Buffer_shift(in);
		nile_Real_t v_p_y = nile_Buffer_shift(in);
nile_Real_t t_2 = nile_Real_mul(v_c_a, v_c_r);
nile_Real_t t_3 = nile_Real_mul(v_c_a, v_c_g);
nile_Real_t t_4 = nile_Real_mul(v_c_a, v_c_b);
nile_Real_t t_1_1 = v_c_a;
nile_Real_t t_1_2 = t_2;
nile_Real_t t_1_3 = t_3;
nile_Real_t t_1_4 = t_4;
nile_Real_t t_5_a = t_1_1;
nile_Real_t t_5_r = t_1_2;
nile_Real_t t_5_g = t_1_3;
nile_Real_t t_5_b = t_1_4;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_5_a);
nile_Buffer_append(out, t_5_r);
nile_Buffer_append(out, t_5_g);
nile_Buffer_append(out, t_5_b);
	}

	if (in->eos) {
	}
	else {
		k->v_c_a = v_c_a;
		k->v_c_r = v_c_r;
		k->v_c_g = v_c_g;
		k->v_c_b = v_c_b;
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
} gezira_CompositeOver_t;

static nile_Kernel_t *
gezira_CompositeOver_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;
	gezira_CompositeOver_t *clone = (gezira_CompositeOver_t *) nile_Kernel_clone(nl, k_);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_CompositeOver(nile_t *nl) {
	gezira_CompositeOver_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeOver);
	return (nile_Kernel_t *) k;
}

static int 
gezira_CompositeOver_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 8
#define OUT_QUANTUM 4
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;

	if (!k_->initialized) {
		k_->initialized = 1;
	}

	while (in->i < in->n) {
		nile_Real_t v_a_a = nile_Buffer_shift(in);
		nile_Real_t v_a_r = nile_Buffer_shift(in);
		nile_Real_t v_a_g = nile_Buffer_shift(in);
		nile_Real_t v_a_b = nile_Buffer_shift(in);
		nile_Real_t v_b_a = nile_Buffer_shift(in);
		nile_Real_t v_b_r = nile_Buffer_shift(in);
		nile_Real_t v_b_g = nile_Buffer_shift(in);
		nile_Real_t v_b_b = nile_Buffer_shift(in);
nile_Real_t t_1 = 1;
nile_Real_t t_2 = nile_Real_sub(t_1, v_a_a);
nile_Real_t t_3_a = t_2;
nile_Real_t t_3_r = t_2;
nile_Real_t t_3_g = t_2;
nile_Real_t t_3_b = t_2;
nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
nile_Real_t t_5_a = nile_Real_add(v_a_a, t_4_a);
nile_Real_t t_5_r = nile_Real_add(v_a_r, t_4_r);
nile_Real_t t_5_g = nile_Real_add(v_a_g, t_4_g);
nile_Real_t t_5_b = nile_Real_add(v_a_b, t_4_b);
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_5_a);
nile_Buffer_append(out, t_5_r);
nile_Buffer_append(out, t_5_g);
nile_Buffer_append(out, t_5_b);
	}

	if (in->eos) {
	}
	else {
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_x0;
	nile_Real_t v_x;
	nile_Real_t v_local;
	nile_Real_t v_run;
} gezira_FillBetweenEdges_t;

static nile_Kernel_t *
gezira_FillBetweenEdges_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
	gezira_FillBetweenEdges_t *clone = (gezira_FillBetweenEdges_t *) nile_Kernel_clone(nl, k_);
	clone->v_x0 = k->v_x0;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_FillBetweenEdges(
	nile_t *nl, 
	nile_Real_t v_x0
) {
	gezira_FillBetweenEdges_t *k = NILE_KERNEL_NEW(nl, gezira_FillBetweenEdges);
	k->v_x0 = v_x0;
	return (nile_Kernel_t *) k;
}

static int 
gezira_FillBetweenEdges_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
	nile_Real_t v_x0 = k->v_x0;
	nile_Real_t v_x = k->v_x;
	nile_Real_t v_x_ = v_x;
	nile_Real_t v_local = k->v_local;
	nile_Real_t v_local_ = v_local;
	nile_Real_t v_run = k->v_run;
	nile_Real_t v_run_ = v_run;

	if (!k_->initialized) {
		k_->initialized = 1;
v_x = v_x0;
nile_Real_t t_3 = 0;
v_local = t_3;
nile_Real_t t_4 = 0;
v_run = t_4;
	}

	while (in->i < in->n) {
		v_x_ = nile_Buffer_shift(in);
		nile_Real_t v_y = nile_Buffer_shift(in);
		nile_Real_t v_w = nile_Buffer_shift(in);
		nile_Real_t v_h = nile_Buffer_shift(in);
nile_Real_t t_5 = nile_Real_sub(v_x_, v_x);
nile_Real_t v_n = t_5;
nile_Real_t t_6 = nile_Real_add(v_run, v_h);
v_run_ = t_6;
nile_Real_t t_7 = 0;
nile_Real_t t_8 = nile_Real_eq(v_n, t_7);
if (t_8) {
nile_Real_t t_9 = nile_Real_mul(v_w, v_h);
nile_Real_t t_10 = nile_Real_add(v_local, t_9);
v_local_ = t_10;
} else {
nile_Real_t t_11 = nile_Real_mul(v_w, v_h);
nile_Real_t t_12 = nile_Real_add(v_run, t_11);
v_local_ = t_12;
nile_Real_t t_13 = nile_Real_abs(v_local);
nile_Real_t t_14 = 1;
nile_Real_t t_15 = nile_Real_min(t_13, t_14);
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_15);
nile_Real_t t_16 = 1;
nile_Real_t t_17 = nile_Real_sub(v_n, t_16);
nile_Real_t t_18 = nile_Real_abs(v_run);
nile_Real_t t_19 = 1;
nile_Real_t t_20 = nile_Real_min(t_18, t_19);
out = nile_Buffer_append_repeat(nl, out, t_20, t_17, k_);
}
		v_x = v_x_;
		v_local = v_local_;
		v_run = v_run_;
	}

	if (in->eos) {
nile_Real_t t_21 = 0;
nile_Real_t t_22 = nile_Real_neq(v_local, t_21);
if (t_22) {
nile_Real_t t_23 = nile_Real_abs(v_local);
nile_Real_t t_24 = 1;
nile_Real_t t_25 = nile_Real_min(t_23, t_24);
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_25);
} else {
{ }
}
	}
	else {
		k->v_x0 = v_x0;
		k->v_x = v_x;
		k->v_local = v_local;
		k->v_run = v_run;
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_start_x;
	nile_Real_t v_start_y;
	nile_Real_t v_x;
	nile_Real_t v_y;
} gezira_CreateSamplePoints_t;

static nile_Kernel_t *
gezira_CreateSamplePoints_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
	gezira_CreateSamplePoints_t *clone = (gezira_CreateSamplePoints_t *) nile_Kernel_clone(nl, k_);
	clone->v_start_x = k->v_start_x;
	clone->v_start_y = k->v_start_y;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_CreateSamplePoints(
	nile_t *nl, 
	nile_Real_t v_start_x, 
	nile_Real_t v_start_y
) {
	gezira_CreateSamplePoints_t *k = NILE_KERNEL_NEW(nl, gezira_CreateSamplePoints);
	k->v_start_x = v_start_x;
	k->v_start_y = v_start_y;
	return (nile_Kernel_t *) k;
}

static int 
gezira_CreateSamplePoints_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 1
#define OUT_QUANTUM 2
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
	nile_Real_t v_start_x = k->v_start_x;
	nile_Real_t v_start_y = k->v_start_y;
	nile_Real_t v_x = k->v_x;
	nile_Real_t v_x_ = v_x;
	nile_Real_t v_y = k->v_y;
	nile_Real_t v_y_ = v_y;

	if (!k_->initialized) {
		k_->initialized = 1;
v_x = v_start_x;
v_y = v_start_y;
	}

	while (in->i < in->n) {
		nile_Real_t v_c = nile_Buffer_shift(in);
nile_Real_t t_1 = 1;
nile_Real_t t_2 = nile_Real_add(v_x, t_1);
v_x_ = t_2;
nile_Real_t t_3_1 = v_x;
nile_Real_t t_3_2 = v_y;
nile_Real_t t_4_x = t_3_1;
nile_Real_t t_4_y = t_3_2;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_4_x);
nile_Buffer_append(out, t_4_y);
		v_x = v_x_;
		v_y = v_y_;
	}

	if (in->eos) {
	}
	else {
		k->v_start_x = v_start_x;
		k->v_start_y = v_start_y;
		k->v_x = v_x;
		k->v_y = v_y;
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Kernel_t *v_s;
	nile_Kernel_t *v_c;
} gezira_Render__t;

static nile_Kernel_t *
gezira_Render__clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_Render__t *k = (gezira_Render__t *) k_;
	gezira_Render__t *clone = (gezira_Render__t *) nile_Kernel_clone(nl, k_);
	clone->v_s = k->v_s->clone(nl, k->v_s);
	clone->v_c = k->v_c->clone(nl, k->v_c);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_Render_(
	nile_t *nl, 
	nile_Kernel_t *v_s, 
	nile_Kernel_t *v_c
) {
	gezira_Render__t *k = NILE_KERNEL_NEW(nl, gezira_Render_);
	k->v_s = v_s;
	k->v_c = v_c;
	return (nile_Kernel_t *) k;
}

static int 
gezira_Render__process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_Render__t *k = (gezira_Render__t *) k_;
	nile_Kernel_t *v_s = k->v_s;
	nile_Kernel_t *v_c = k->v_c;

	if (!k_->initialized) {
		k_->initialized = 1;
		nile_Real_t v_x = in->data[in->i++];
		nile_Real_t v_y = in->data[in->i++];
		nile_Real_t v_w = in->data[in->i++];
		nile_Real_t v_h = in->data[in->i++];
		in->i -= 4;
nile_Real_t t_1_1 = v_x;
nile_Real_t t_1_2 = v_y;
nile_Real_t t_2 = 0.5;
nile_Real_t t_3_1 = t_2;
nile_Real_t t_3_2 = t_2;
nile_Real_t t_4_1 = nile_Real_add(t_1_1, t_3_1);
nile_Real_t t_4_2 = nile_Real_add(t_1_2, t_3_2);
nile_Real_t v_p_1 = t_4_1;
nile_Real_t v_p_2 = t_4_2;
nile_Kernel_t *t_5 = gezira_FillBetweenEdges(nl, v_x);
nile_Real_t t_6_x = v_p_1;
nile_Real_t t_6_y = v_p_2;
nile_Kernel_t *t_7 = gezira_CreateSamplePoints(nl, t_6_x, t_6_y);
nile_Kernel_t *t_8 = nile_Pipeline(nl, t_7, v_s, NULL);
nile_Real_t t_9 = 4;
nile_Kernel_t *t_10 = nile_Pipeline(nl, NULL);
nile_Real_t t_11 = 1;
nile_Kernel_t *t_12 = nile_Interleave(nl, t_8, t_9, t_10, t_11);
nile_Real_t t_13_x = v_p_1;
nile_Real_t t_13_y = v_p_2;
nile_Kernel_t *t_14 = gezira_Canvas(nl, v_c, t_13_x, t_13_y);
nile_Kernel_t *t_15 = nile_Pipeline(nl, t_12, t_14, NULL);
nile_Kernel_t *t_16 = nile_Pipeline(nl, t_5, t_15, NULL);
		nile_Kernel_t *f = t_16;
		f->downstream = k_->downstream;
		k_->downstream = f;
	}

	return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Kernel_t *v_s;
	nile_Kernel_t *v_c;
} gezira_Render_t;

static nile_Kernel_t *
gezira_Render_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_Render_t *k = (gezira_Render_t *) k_;
	gezira_Render_t *clone = (gezira_Render_t *) nile_Kernel_clone(nl, k_);
	clone->v_s = k->v_s->clone(nl, k->v_s);
	clone->v_c = k->v_c->clone(nl, k->v_c);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_Render(
	nile_t *nl, 
	nile_Kernel_t *v_s, 
	nile_Kernel_t *v_c
) {
	gezira_Render_t *k = NILE_KERNEL_NEW(nl, gezira_Render);
	k->v_s = v_s;
	k->v_c = v_c;
	return (nile_Kernel_t *) k;
}

static int 
gezira_Render_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_Render_t *k = (gezira_Render_t *) k_;
	nile_Kernel_t *v_s = k->v_s;
	nile_Kernel_t *v_c = k->v_c;

	if (!k_->initialized) {
		k_->initialized = 1;
{ }
nile_Real_t t_1 = 1;
nile_Real_t t_2 = 4;
nile_Kernel_t *t_3 = nile_GroupBy(nl, t_1, t_2);
nile_Real_t t_4 = 0;
nile_Real_t t_5 = 4;
nile_Kernel_t *t_6 = nile_SortBy(nl, t_4, t_5);
nile_Kernel_t *t_7 = gezira_Render_(nl, v_s, v_c);
nile_Kernel_t *t_8 = nile_Pipeline(nl, t_6, t_7, NULL);
nile_Kernel_t *t_9 = nile_Pipeline(nl, t_3, t_8, NULL);
		nile_Kernel_t *f = t_9;
		f->downstream = k_->downstream;
		k_->downstream = f;
	}

	return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_m_a;
	nile_Real_t v_m_b;
	nile_Real_t v_m_c;
	nile_Real_t v_m_d;
	nile_Real_t v_m_e;
	nile_Real_t v_m_f;
} gezira_TransformBezier_t;

static nile_Kernel_t *
gezira_TransformBezier_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_TransformBezier_t *k = (gezira_TransformBezier_t *) k_;
	gezira_TransformBezier_t *clone = (gezira_TransformBezier_t *) nile_Kernel_clone(nl, k_);
	clone->v_m_a = k->v_m_a;
	clone->v_m_b = k->v_m_b;
	clone->v_m_c = k->v_m_c;
	clone->v_m_d = k->v_m_d;
	clone->v_m_e = k->v_m_e;
	clone->v_m_f = k->v_m_f;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_TransformBezier(
	nile_t *nl, 
	nile_Real_t v_m_a, 
	nile_Real_t v_m_b, 
	nile_Real_t v_m_c, 
	nile_Real_t v_m_d, 
	nile_Real_t v_m_e, 
	nile_Real_t v_m_f
) {
	gezira_TransformBezier_t *k = NILE_KERNEL_NEW(nl, gezira_TransformBezier);
	k->v_m_a = v_m_a;
	k->v_m_b = v_m_b;
	k->v_m_c = v_m_c;
	k->v_m_d = v_m_d;
	k->v_m_e = v_m_e;
	k->v_m_f = v_m_f;
	return (nile_Kernel_t *) k;
}

static int 
gezira_TransformBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_TransformBezier_t *k = (gezira_TransformBezier_t *) k_;
	nile_Real_t v_m_a = k->v_m_a;
	nile_Real_t v_m_b = k->v_m_b;
	nile_Real_t v_m_c = k->v_m_c;
	nile_Real_t v_m_d = k->v_m_d;
	nile_Real_t v_m_e = k->v_m_e;
	nile_Real_t v_m_f = k->v_m_f;

	if (!k_->initialized) {
		k_->initialized = 1;
	}

	while (in->i < in->n) {
		nile_Real_t v_a_x = nile_Buffer_shift(in);
		nile_Real_t v_a_y = nile_Buffer_shift(in);
		nile_Real_t v_b_x = nile_Buffer_shift(in);
		nile_Real_t v_b_y = nile_Buffer_shift(in);
		nile_Real_t v_c_x = nile_Buffer_shift(in);
		nile_Real_t v_c_y = nile_Buffer_shift(in);
nile_Real_t t_3 = nile_Real_mul(v_m_a, v_a_x);
nile_Real_t t_4 = nile_Real_mul(v_m_c, v_a_y);
nile_Real_t t_5 = nile_Real_add(t_3, t_4);
nile_Real_t t_6 = nile_Real_add(t_5, v_m_e);
nile_Real_t t_7 = nile_Real_mul(v_m_b, v_a_x);
nile_Real_t t_8 = nile_Real_mul(v_m_d, v_a_y);
nile_Real_t t_9 = nile_Real_add(t_7, t_8);
nile_Real_t t_10 = nile_Real_add(t_9, v_m_f);
nile_Real_t t_2_1 = t_6;
nile_Real_t t_2_2 = t_10;
nile_Real_t t_11_x = t_2_1;
nile_Real_t t_11_y = t_2_2;
nile_Real_t t_13 = nile_Real_mul(v_m_a, v_b_x);
nile_Real_t t_14 = nile_Real_mul(v_m_c, v_b_y);
nile_Real_t t_15 = nile_Real_add(t_13, t_14);
nile_Real_t t_16 = nile_Real_add(t_15, v_m_e);
nile_Real_t t_17 = nile_Real_mul(v_m_b, v_b_x);
nile_Real_t t_18 = nile_Real_mul(v_m_d, v_b_y);
nile_Real_t t_19 = nile_Real_add(t_17, t_18);
nile_Real_t t_20 = nile_Real_add(t_19, v_m_f);
nile_Real_t t_12_1 = t_16;
nile_Real_t t_12_2 = t_20;
nile_Real_t t_21_x = t_12_1;
nile_Real_t t_21_y = t_12_2;
nile_Real_t t_23 = nile_Real_mul(v_m_a, v_c_x);
nile_Real_t t_24 = nile_Real_mul(v_m_c, v_c_y);
nile_Real_t t_25 = nile_Real_add(t_23, t_24);
nile_Real_t t_26 = nile_Real_add(t_25, v_m_e);
nile_Real_t t_27 = nile_Real_mul(v_m_b, v_c_x);
nile_Real_t t_28 = nile_Real_mul(v_m_d, v_c_y);
nile_Real_t t_29 = nile_Real_add(t_27, t_28);
nile_Real_t t_30 = nile_Real_add(t_29, v_m_f);
nile_Real_t t_22_1 = t_26;
nile_Real_t t_22_2 = t_30;
nile_Real_t t_31_x = t_22_1;
nile_Real_t t_31_y = t_22_2;
nile_Real_t t_1_1_x = t_11_x;
nile_Real_t t_1_1_y = t_11_y;
nile_Real_t t_1_2_x = t_21_x;
nile_Real_t t_1_2_y = t_21_y;
nile_Real_t t_1_3_x = t_31_x;
nile_Real_t t_1_3_y = t_31_y;
nile_Real_t t_32_a_x = t_1_1_x;
nile_Real_t t_32_a_y = t_1_1_y;
nile_Real_t t_32_b_x = t_1_2_x;
nile_Real_t t_32_b_y = t_1_2_y;
nile_Real_t t_32_c_x = t_1_3_x;
nile_Real_t t_32_c_y = t_1_3_y;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_32_a_x);
nile_Buffer_append(out, t_32_a_y);
nile_Buffer_append(out, t_32_b_x);
nile_Buffer_append(out, t_32_b_y);
nile_Buffer_append(out, t_32_c_x);
nile_Buffer_append(out, t_32_c_y);
	}

	if (in->eos) {
	}
	else {
		k->v_m_a = v_m_a;
		k->v_m_b = v_m_b;
		k->v_m_c = v_m_c;
		k->v_m_d = v_m_d;
		k->v_m_e = v_m_e;
		k->v_m_f = v_m_f;
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
	nile_Real_t v_min_x;
	nile_Real_t v_min_y;
	nile_Real_t v_max_x;
	nile_Real_t v_max_y;
} gezira_ClipBezier_t;

static nile_Kernel_t *
gezira_ClipBezier_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_ClipBezier_t *k = (gezira_ClipBezier_t *) k_;
	gezira_ClipBezier_t *clone = (gezira_ClipBezier_t *) nile_Kernel_clone(nl, k_);
	clone->v_min_x = k->v_min_x;
	clone->v_min_y = k->v_min_y;
	clone->v_max_x = k->v_max_x;
	clone->v_max_y = k->v_max_y;
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_ClipBezier(
	nile_t *nl, 
	nile_Real_t v_min_x, 
	nile_Real_t v_min_y, 
	nile_Real_t v_max_x, 
	nile_Real_t v_max_y
) {
	gezira_ClipBezier_t *k = NILE_KERNEL_NEW(nl, gezira_ClipBezier);
	k->v_min_x = v_min_x;
	k->v_min_y = v_min_y;
	k->v_max_x = v_max_x;
	k->v_max_y = v_max_y;
	return (nile_Kernel_t *) k;
}

static int 
gezira_ClipBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_ClipBezier_t *k = (gezira_ClipBezier_t *) k_;
	nile_Real_t v_min_x = k->v_min_x;
	nile_Real_t v_min_y = k->v_min_y;
	nile_Real_t v_max_x = k->v_max_x;
	nile_Real_t v_max_y = k->v_max_y;

	if (!k_->initialized) {
		k_->initialized = 1;
	}

	while (in->i < in->n) {
		nile_Real_t v_a_x = nile_Buffer_shift(in);
		nile_Real_t v_a_y = nile_Buffer_shift(in);
		nile_Real_t v_b_x = nile_Buffer_shift(in);
		nile_Real_t v_b_y = nile_Buffer_shift(in);
		nile_Real_t v_c_x = nile_Buffer_shift(in);
		nile_Real_t v_c_y = nile_Buffer_shift(in);
nile_Real_t t_1_x = nile_Real_min(v_a_x, v_b_x);
nile_Real_t t_1_y = nile_Real_min(v_a_y, v_b_y);
nile_Real_t t_2_x = nile_Real_min(t_1_x, v_c_x);
nile_Real_t t_2_y = nile_Real_min(t_1_y, v_c_y);
nile_Real_t v_bmin_x = t_2_x;
nile_Real_t v_bmin_y = t_2_y;
nile_Real_t t_3_x = nile_Real_max(v_a_x, v_b_x);
nile_Real_t t_3_y = nile_Real_max(v_a_y, v_b_y);
nile_Real_t t_4_x = nile_Real_max(t_3_x, v_c_x);
nile_Real_t t_4_y = nile_Real_max(t_3_y, v_c_y);
nile_Real_t v_bmax_x = t_4_x;
nile_Real_t v_bmax_y = t_4_y;
nile_Real_t t_5_x = nile_Real_leq(v_min_x, v_bmin_x);
nile_Real_t t_5_y = nile_Real_leq(v_min_y, v_bmin_y);
nile_Real_t t_6_x = nile_Real_leq(v_bmax_x, v_max_x);
nile_Real_t t_6_y = nile_Real_leq(v_bmax_y, v_max_y);
nile_Real_t t_7_x = nile_Real_and(t_5_x, t_6_x);
nile_Real_t t_7_y = nile_Real_and(t_5_y, t_6_y);
nile_Real_t t_8 = t_7_x;
t_8 = nile_Real_and(t_8, t_7_y);
if (t_8) {
nile_Real_t t_9_1_x = v_a_x;
nile_Real_t t_9_1_y = v_a_y;
nile_Real_t t_9_2_x = v_b_x;
nile_Real_t t_9_2_y = v_b_y;
nile_Real_t t_9_3_x = v_c_x;
nile_Real_t t_9_3_y = v_c_y;
nile_Real_t t_10_a_x = t_9_1_x;
nile_Real_t t_10_a_y = t_9_1_y;
nile_Real_t t_10_b_x = t_9_2_x;
nile_Real_t t_10_b_y = t_9_2_y;
nile_Real_t t_10_c_x = t_9_3_x;
nile_Real_t t_10_c_y = t_9_3_y;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_10_a_x);
nile_Buffer_append(out, t_10_a_y);
nile_Buffer_append(out, t_10_b_x);
nile_Buffer_append(out, t_10_b_y);
nile_Buffer_append(out, t_10_c_x);
nile_Buffer_append(out, t_10_c_y);
} else {
nile_Real_t t_11_x = nile_Real_leq(v_bmax_x, v_min_x);
nile_Real_t t_11_y = nile_Real_leq(v_bmax_y, v_min_y);
nile_Real_t t_12_x = nile_Real_leq(v_max_x, v_bmin_x);
nile_Real_t t_12_y = nile_Real_leq(v_max_y, v_bmin_y);
nile_Real_t t_13_x = nile_Real_or(t_11_x, t_12_x);
nile_Real_t t_13_y = nile_Real_or(t_11_y, t_12_y);
nile_Real_t t_14 = t_13_x;
t_14 = nile_Real_or(t_14, t_13_y);
if (t_14) {
nile_Real_t t_15_x = nile_Real_max(v_min_x, v_a_x);
nile_Real_t t_15_y = nile_Real_max(v_min_y, v_a_y);
nile_Real_t t_16_x = nile_Real_min(t_15_x, v_max_x);
nile_Real_t t_16_y = nile_Real_min(t_15_y, v_max_y);
nile_Real_t v_ca_x = t_16_x;
nile_Real_t v_ca_y = t_16_y;
nile_Real_t t_17_x = nile_Real_max(v_min_x, v_c_x);
nile_Real_t t_17_y = nile_Real_max(v_min_y, v_c_y);
nile_Real_t t_18_x = nile_Real_min(t_17_x, v_max_x);
nile_Real_t t_18_y = nile_Real_min(t_17_y, v_max_y);
nile_Real_t v_cc_x = t_18_x;
nile_Real_t v_cc_y = t_18_y;
nile_Real_t t_20_x = nile_Real_ave(v_ca_x, v_cc_x);
nile_Real_t t_20_y = nile_Real_ave(v_ca_y, v_cc_y);
nile_Real_t t_19_1_x = v_ca_x;
nile_Real_t t_19_1_y = v_ca_y;
nile_Real_t t_19_2_x = t_20_x;
nile_Real_t t_19_2_y = t_20_y;
nile_Real_t t_19_3_x = v_cc_x;
nile_Real_t t_19_3_y = v_cc_y;
nile_Real_t t_21_a_x = t_19_1_x;
nile_Real_t t_21_a_y = t_19_1_y;
nile_Real_t t_21_b_x = t_19_2_x;
nile_Real_t t_21_b_y = t_19_2_y;
nile_Real_t t_21_c_x = t_19_3_x;
nile_Real_t t_21_c_y = t_19_3_y;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_21_a_x);
nile_Buffer_append(out, t_21_a_y);
nile_Buffer_append(out, t_21_b_x);
nile_Buffer_append(out, t_21_b_y);
nile_Buffer_append(out, t_21_c_x);
nile_Buffer_append(out, t_21_c_y);
} else {
nile_Real_t t_22_x = nile_Real_ave(v_a_x, v_b_x);
nile_Real_t t_22_y = nile_Real_ave(v_a_y, v_b_y);
nile_Real_t t_23_x = nile_Real_ave(v_b_x, v_c_x);
nile_Real_t t_23_y = nile_Real_ave(v_b_y, v_c_y);
nile_Real_t t_24_x = nile_Real_ave(t_22_x, t_23_x);
nile_Real_t t_24_y = nile_Real_ave(t_22_y, t_23_y);
nile_Real_t v_abbc_x = t_24_x;
nile_Real_t v_abbc_y = t_24_y;
nile_Real_t t_25_x = nile_Real_sub(v_abbc_x, v_min_x);
nile_Real_t t_25_y = nile_Real_sub(v_abbc_y, v_min_y);
nile_Real_t t_26_x = nile_Real_abs(t_25_x);
nile_Real_t t_26_y = nile_Real_abs(t_25_y);
nile_Real_t t_27 = 0.1;
nile_Real_t t_28_x = t_27;
nile_Real_t t_28_y = t_27;
nile_Real_t t_29_x = nile_Real_lt(t_26_x, t_28_x);
nile_Real_t t_29_y = nile_Real_lt(t_26_y, t_28_y);
nile_Real_t v_nearmin_x = t_29_x;
nile_Real_t v_nearmin_y = t_29_y;
nile_Real_t t_30_x = nile_Real_sub(v_abbc_x, v_max_x);
nile_Real_t t_30_y = nile_Real_sub(v_abbc_y, v_max_y);
nile_Real_t t_31_x = nile_Real_abs(t_30_x);
nile_Real_t t_31_y = nile_Real_abs(t_30_y);
nile_Real_t t_32 = 0.1;
nile_Real_t t_33_x = t_32;
nile_Real_t t_33_y = t_32;
nile_Real_t t_34_x = nile_Real_lt(t_31_x, t_33_x);
nile_Real_t t_34_y = nile_Real_lt(t_31_y, t_33_y);
nile_Real_t v_nearmax_x = t_34_x;
nile_Real_t v_nearmax_y = t_34_y;
nile_Real_t t_35_x = v_nearmax_x ? v_max_x : v_abbc_x;
nile_Real_t t_35_y = v_nearmax_y ? v_max_y : v_abbc_y;
nile_Real_t t_36_x = v_nearmin_x ? v_min_x : t_35_x;
nile_Real_t t_36_y = v_nearmin_y ? v_min_y : t_35_y;
nile_Real_t v_m_x = t_36_x;
nile_Real_t v_m_y = t_36_y;
nile_Real_t t_38_x = nile_Real_ave(v_a_x, v_b_x);
nile_Real_t t_38_y = nile_Real_ave(v_a_y, v_b_y);
nile_Real_t t_37_1_x = v_a_x;
nile_Real_t t_37_1_y = v_a_y;
nile_Real_t t_37_2_x = t_38_x;
nile_Real_t t_37_2_y = t_38_y;
nile_Real_t t_37_3_x = v_m_x;
nile_Real_t t_37_3_y = v_m_y;
nile_Real_t t_39_a_x = t_37_1_x;
nile_Real_t t_39_a_y = t_37_1_y;
nile_Real_t t_39_b_x = t_37_2_x;
nile_Real_t t_39_b_y = t_37_2_y;
nile_Real_t t_39_c_x = t_37_3_x;
nile_Real_t t_39_c_y = t_37_3_y;
in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
nile_Buffer_prepend(in, t_39_a_x);
nile_Buffer_prepend(in, t_39_a_y);
nile_Buffer_prepend(in, t_39_b_x);
nile_Buffer_prepend(in, t_39_b_y);
nile_Buffer_prepend(in, t_39_c_x);
nile_Buffer_prepend(in, t_39_c_y);
in->i -= IN_QUANTUM;
nile_Real_t t_41_x = nile_Real_ave(v_b_x, v_c_x);
nile_Real_t t_41_y = nile_Real_ave(v_b_y, v_c_y);
nile_Real_t t_40_1_x = v_m_x;
nile_Real_t t_40_1_y = v_m_y;
nile_Real_t t_40_2_x = t_41_x;
nile_Real_t t_40_2_y = t_41_y;
nile_Real_t t_40_3_x = v_c_x;
nile_Real_t t_40_3_y = v_c_y;
nile_Real_t t_42_a_x = t_40_1_x;
nile_Real_t t_42_a_y = t_40_1_y;
nile_Real_t t_42_b_x = t_40_2_x;
nile_Real_t t_42_b_y = t_40_2_y;
nile_Real_t t_42_c_x = t_40_3_x;
nile_Real_t t_42_c_y = t_40_3_y;
in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
nile_Buffer_prepend(in, t_42_a_x);
nile_Buffer_prepend(in, t_42_a_y);
nile_Buffer_prepend(in, t_42_b_x);
nile_Buffer_prepend(in, t_42_b_y);
nile_Buffer_prepend(in, t_42_c_x);
nile_Buffer_prepend(in, t_42_c_y);
in->i -= IN_QUANTUM;
}
}
	}

	if (in->eos) {
	}
	else {
		k->v_min_x = v_min_x;
		k->v_min_y = v_min_y;
		k->v_max_x = v_max_x;
		k->v_max_y = v_max_y;
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

typedef struct {
	nile_Kernel_t base;
} gezira_DecomposeBezier_t;

static nile_Kernel_t *
gezira_DecomposeBezier_clone(nile_t *nl, nile_Kernel_t *k_) {
	gezira_DecomposeBezier_t *k = (gezira_DecomposeBezier_t *) k_;
	gezira_DecomposeBezier_t *clone = (gezira_DecomposeBezier_t *) nile_Kernel_clone(nl, k_);
	return (nile_Kernel_t *) clone;
}

nile_Kernel_t *
gezira_DecomposeBezier(nile_t *nl) {
	gezira_DecomposeBezier_t *k = NILE_KERNEL_NEW(nl, gezira_DecomposeBezier);
	return (nile_Kernel_t *) k;
}

static int 
gezira_DecomposeBezier_process(
	nile_t *nl,
	nile_Kernel_t *k_,
	nile_Buffer_t **in_,
	nile_Buffer_t **out_
) {
#define IN_QUANTUM 6
#define OUT_QUANTUM 4
	nile_Buffer_t *in = *in_;
	nile_Buffer_t *out = *out_;
	gezira_DecomposeBezier_t *k = (gezira_DecomposeBezier_t *) k_;

	if (!k_->initialized) {
		k_->initialized = 1;
	}

	while (in->i < in->n) {
		nile_Real_t v_a_x = nile_Buffer_shift(in);
		nile_Real_t v_a_y = nile_Buffer_shift(in);
		nile_Real_t v_b_x = nile_Buffer_shift(in);
		nile_Real_t v_b_y = nile_Buffer_shift(in);
		nile_Real_t v_c_x = nile_Buffer_shift(in);
		nile_Real_t v_c_y = nile_Buffer_shift(in);
nile_Real_t t_1_x = nile_Real_flr(v_a_x);
nile_Real_t t_1_y = nile_Real_flr(v_a_y);
nile_Real_t t_2_x = nile_Real_flr(v_c_x);
nile_Real_t t_2_y = nile_Real_flr(v_c_y);
nile_Real_t t_3_x = nile_Real_eq(t_1_x, t_2_x);
nile_Real_t t_3_y = nile_Real_eq(t_1_y, t_2_y);
nile_Real_t t_4_x = nile_Real_clg(v_a_x);
nile_Real_t t_4_y = nile_Real_clg(v_a_y);
nile_Real_t t_5_x = nile_Real_clg(v_c_x);
nile_Real_t t_5_y = nile_Real_clg(v_c_y);
nile_Real_t t_6_x = nile_Real_eq(t_4_x, t_5_x);
nile_Real_t t_6_y = nile_Real_eq(t_4_y, t_5_y);
nile_Real_t t_7_x = nile_Real_or(t_3_x, t_6_x);
nile_Real_t t_7_y = nile_Real_or(t_3_y, t_6_y);
nile_Real_t t_8 = t_7_x;
t_8 = nile_Real_and(t_8, t_7_y);
if (t_8) {
nile_Real_t t_9_x = nile_Real_flr(v_a_x);
nile_Real_t t_9_y = nile_Real_flr(v_a_y);
nile_Real_t t_10_x = nile_Real_flr(v_c_x);
nile_Real_t t_10_y = nile_Real_flr(v_c_y);
nile_Real_t t_11_x = nile_Real_min(t_9_x, t_10_x);
nile_Real_t t_11_y = nile_Real_min(t_9_y, t_10_y);
nile_Real_t v_p_x = t_11_x;
nile_Real_t v_p_y = t_11_y;
nile_Real_t t_12 = 1;
nile_Real_t t_13 = nile_Real_add(v_p_x, t_12);
nile_Real_t t_14 = nile_Real_ave(v_c_x, v_a_x);
nile_Real_t t_15 = nile_Real_sub(t_13, t_14);
nile_Real_t v_w = t_15;
nile_Real_t t_16 = nile_Real_sub(v_c_y, v_a_y);
nile_Real_t v_h = t_16;
nile_Real_t t_17_1 = v_p_x;
nile_Real_t t_17_2 = v_p_y;
nile_Real_t t_17_3 = v_w;
nile_Real_t t_17_4 = v_h;
nile_Real_t t_18_x = t_17_1;
nile_Real_t t_18_y = t_17_2;
nile_Real_t t_18_w = t_17_3;
nile_Real_t t_18_h = t_17_4;
out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
nile_Buffer_append(out, t_18_x);
nile_Buffer_append(out, t_18_y);
nile_Buffer_append(out, t_18_w);
nile_Buffer_append(out, t_18_h);
} else {
nile_Real_t t_19_x = nile_Real_ave(v_a_x, v_b_x);
nile_Real_t t_19_y = nile_Real_ave(v_a_y, v_b_y);
nile_Real_t t_20_x = nile_Real_ave(v_b_x, v_c_x);
nile_Real_t t_20_y = nile_Real_ave(v_b_y, v_c_y);
nile_Real_t t_21_x = nile_Real_ave(t_19_x, t_20_x);
nile_Real_t t_21_y = nile_Real_ave(t_19_y, t_20_y);
nile_Real_t v_abbc_x = t_21_x;
nile_Real_t v_abbc_y = t_21_y;
nile_Real_t t_22_x = nile_Real_flr(v_abbc_x);
nile_Real_t t_22_y = nile_Real_flr(v_abbc_y);
nile_Real_t v_min_x = t_22_x;
nile_Real_t v_min_y = t_22_y;
nile_Real_t t_23_x = nile_Real_clg(v_abbc_x);
nile_Real_t t_23_y = nile_Real_clg(v_abbc_y);
nile_Real_t v_max_x = t_23_x;
nile_Real_t v_max_y = t_23_y;
nile_Real_t t_24_x = nile_Real_sub(v_abbc_x, v_min_x);
nile_Real_t t_24_y = nile_Real_sub(v_abbc_y, v_min_y);
nile_Real_t t_25_x = nile_Real_abs(t_24_x);
nile_Real_t t_25_y = nile_Real_abs(t_24_y);
nile_Real_t t_26 = 0.1;
nile_Real_t t_27_x = t_26;
nile_Real_t t_27_y = t_26;
nile_Real_t t_28_x = nile_Real_lt(t_25_x, t_27_x);
nile_Real_t t_28_y = nile_Real_lt(t_25_y, t_27_y);
nile_Real_t v_nearmin_x = t_28_x;
nile_Real_t v_nearmin_y = t_28_y;
nile_Real_t t_29_x = nile_Real_sub(v_abbc_x, v_max_x);
nile_Real_t t_29_y = nile_Real_sub(v_abbc_y, v_max_y);
nile_Real_t t_30_x = nile_Real_abs(t_29_x);
nile_Real_t t_30_y = nile_Real_abs(t_29_y);
nile_Real_t t_31 = 0.1;
nile_Real_t t_32_x = t_31;
nile_Real_t t_32_y = t_31;
nile_Real_t t_33_x = nile_Real_lt(t_30_x, t_32_x);
nile_Real_t t_33_y = nile_Real_lt(t_30_y, t_32_y);
nile_Real_t v_nearmax_x = t_33_x;
nile_Real_t v_nearmax_y = t_33_y;
nile_Real_t t_34_x = v_nearmax_x ? v_max_x : v_abbc_x;
nile_Real_t t_34_y = v_nearmax_y ? v_max_y : v_abbc_y;
nile_Real_t t_35_x = v_nearmin_x ? v_min_x : t_34_x;
nile_Real_t t_35_y = v_nearmin_y ? v_min_y : t_34_y;
nile_Real_t v_m_x = t_35_x;
nile_Real_t v_m_y = t_35_y;
nile_Real_t t_37_x = nile_Real_ave(v_a_x, v_b_x);
nile_Real_t t_37_y = nile_Real_ave(v_a_y, v_b_y);
nile_Real_t t_36_1_x = v_a_x;
nile_Real_t t_36_1_y = v_a_y;
nile_Real_t t_36_2_x = t_37_x;
nile_Real_t t_36_2_y = t_37_y;
nile_Real_t t_36_3_x = v_m_x;
nile_Real_t t_36_3_y = v_m_y;
nile_Real_t t_38_a_x = t_36_1_x;
nile_Real_t t_38_a_y = t_36_1_y;
nile_Real_t t_38_b_x = t_36_2_x;
nile_Real_t t_38_b_y = t_36_2_y;
nile_Real_t t_38_c_x = t_36_3_x;
nile_Real_t t_38_c_y = t_36_3_y;
in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
nile_Buffer_prepend(in, t_38_a_x);
nile_Buffer_prepend(in, t_38_a_y);
nile_Buffer_prepend(in, t_38_b_x);
nile_Buffer_prepend(in, t_38_b_y);
nile_Buffer_prepend(in, t_38_c_x);
nile_Buffer_prepend(in, t_38_c_y);
in->i -= IN_QUANTUM;
nile_Real_t t_40_x = nile_Real_ave(v_b_x, v_c_x);
nile_Real_t t_40_y = nile_Real_ave(v_b_y, v_c_y);
nile_Real_t t_39_1_x = v_m_x;
nile_Real_t t_39_1_y = v_m_y;
nile_Real_t t_39_2_x = t_40_x;
nile_Real_t t_39_2_y = t_40_y;
nile_Real_t t_39_3_x = v_c_x;
nile_Real_t t_39_3_y = v_c_y;
nile_Real_t t_41_a_x = t_39_1_x;
nile_Real_t t_41_a_y = t_39_1_y;
nile_Real_t t_41_b_x = t_39_2_x;
nile_Real_t t_41_b_y = t_39_2_y;
nile_Real_t t_41_c_x = t_39_3_x;
nile_Real_t t_41_c_y = t_39_3_y;
in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
nile_Buffer_prepend(in, t_41_a_x);
nile_Buffer_prepend(in, t_41_a_y);
nile_Buffer_prepend(in, t_41_b_x);
nile_Buffer_prepend(in, t_41_b_y);
nile_Buffer_prepend(in, t_41_c_x);
nile_Buffer_prepend(in, t_41_c_y);
in->i -= IN_QUANTUM;
}
	}

	if (in->eos) {
	}
	else {
	}
	*in_ = in;
	*out_ = out;
	return NILE_INPUT_CONSUMED;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}


