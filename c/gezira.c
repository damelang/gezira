#include <stddef.h>
#include "gezira.h"

nile_Kernel_t *gezira_Sampler_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Sampler_t *k = (gezira_Sampler_t *) k_;
    gezira_Sampler_t *clone = (gezira_Sampler_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_Compositor_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Compositor_t *k = (gezira_Compositor_t *) k_;
    gezira_Compositor_t *clone = (gezira_Compositor_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_M_a;
    nile_Real_t v_M_b;
    nile_Real_t v_M_c;
    nile_Real_t v_M_d;
    nile_Real_t v_M_e;
    nile_Real_t v_M_f;
} gezira_TransformPoints_t;

static nile_Kernel_t *gezira_TransformPoints_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_TransformPoints_t *k = (gezira_TransformPoints_t *) k_;
    gezira_TransformPoints_t *clone = (gezira_TransformPoints_t *) nile_Kernel_clone(nl, k_);
    clone->v_M_a = k->v_M_a;
    clone->v_M_b = k->v_M_b;
    clone->v_M_c = k->v_M_c;
    clone->v_M_d = k->v_M_d;
    clone->v_M_e = k->v_M_e;
    clone->v_M_f = k->v_M_f;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_TransformPoints(nile_t *nl, 
                                      nile_Real_t v_M_a, 
                                      nile_Real_t v_M_b, 
                                      nile_Real_t v_M_c, 
                                      nile_Real_t v_M_d, 
                                      nile_Real_t v_M_e, 
                                      nile_Real_t v_M_f) {
    gezira_TransformPoints_t *k = NILE_KERNEL_NEW(nl, gezira_TransformPoints);
    k->v_M_a = v_M_a;
    k->v_M_b = v_M_b;
    k->v_M_c = v_M_c;
    k->v_M_d = v_M_d;
    k->v_M_e = v_M_e;
    k->v_M_f = v_M_f;
    return (nile_Kernel_t *) k;
}

static int gezira_TransformPoints_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_TransformPoints_t *k = (gezira_TransformPoints_t *) k_;
    nile_Real_t v_M_a = k->v_M_a;
    nile_Real_t v_M_b = k->v_M_b;
    nile_Real_t v_M_c = k->v_M_c;
    nile_Real_t v_M_d = k->v_M_d;
    nile_Real_t v_M_e = k->v_M_e;
    nile_Real_t v_M_f = k->v_M_f;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_2 = nile_Real_mul(v_M_a, v_P_x);
        nile_Real_t t_3 = nile_Real_mul(v_M_c, v_P_y);
        nile_Real_t t_4 = nile_Real_add(t_2, t_3);
        nile_Real_t t_5 = nile_Real_add(t_4, v_M_e);
        nile_Real_t t_6 = nile_Real_mul(v_M_b, v_P_x);
        nile_Real_t t_7 = nile_Real_mul(v_M_d, v_P_y);
        nile_Real_t t_8 = nile_Real_add(t_6, t_7);
        nile_Real_t t_9 = nile_Real_add(t_8, v_M_f);
        nile_Real_t t_1_1 = t_5;
        nile_Real_t t_1_2 = t_9;
        nile_Real_t t_10_x = t_1_1;
        nile_Real_t t_10_y = t_1_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_10_x);
        nile_Buffer_append(out, t_10_y);
    }
    
    if (in->eos) {
    }
    else {
        k->v_M_a = v_M_a;
        k->v_M_b = v_M_b;
        k->v_M_c = v_M_c;
        k->v_M_d = v_M_d;
        k->v_M_e = v_M_e;
        k->v_M_f = v_M_f;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_M_a;
    nile_Real_t v_M_b;
    nile_Real_t v_M_c;
    nile_Real_t v_M_d;
    nile_Real_t v_M_e;
    nile_Real_t v_M_f;
} gezira_TransformBeziers_t;

static nile_Kernel_t *gezira_TransformBeziers_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_TransformBeziers_t *k = (gezira_TransformBeziers_t *) k_;
    gezira_TransformBeziers_t *clone = (gezira_TransformBeziers_t *) nile_Kernel_clone(nl, k_);
    clone->v_M_a = k->v_M_a;
    clone->v_M_b = k->v_M_b;
    clone->v_M_c = k->v_M_c;
    clone->v_M_d = k->v_M_d;
    clone->v_M_e = k->v_M_e;
    clone->v_M_f = k->v_M_f;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_TransformBeziers(nile_t *nl, 
                                       nile_Real_t v_M_a, 
                                       nile_Real_t v_M_b, 
                                       nile_Real_t v_M_c, 
                                       nile_Real_t v_M_d, 
                                       nile_Real_t v_M_e, 
                                       nile_Real_t v_M_f) {
    gezira_TransformBeziers_t *k = NILE_KERNEL_NEW(nl, gezira_TransformBeziers);
    k->v_M_a = v_M_a;
    k->v_M_b = v_M_b;
    k->v_M_c = v_M_c;
    k->v_M_d = v_M_d;
    k->v_M_e = v_M_e;
    k->v_M_f = v_M_f;
    return (nile_Kernel_t *) k;
}

static int gezira_TransformBeziers_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_TransformBeziers_t *k = (gezira_TransformBeziers_t *) k_;
    nile_Real_t v_M_a = k->v_M_a;
    nile_Real_t v_M_b = k->v_M_b;
    nile_Real_t v_M_c = k->v_M_c;
    nile_Real_t v_M_d = k->v_M_d;
    nile_Real_t v_M_e = k->v_M_e;
    nile_Real_t v_M_f = k->v_M_f;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_3 = nile_Real_mul(v_M_a, v_A_x);
        nile_Real_t t_4 = nile_Real_mul(v_M_c, v_A_y);
        nile_Real_t t_5 = nile_Real_add(t_3, t_4);
        nile_Real_t t_6 = nile_Real_add(t_5, v_M_e);
        nile_Real_t t_7 = nile_Real_mul(v_M_b, v_A_x);
        nile_Real_t t_8 = nile_Real_mul(v_M_d, v_A_y);
        nile_Real_t t_9 = nile_Real_add(t_7, t_8);
        nile_Real_t t_10 = nile_Real_add(t_9, v_M_f);
        nile_Real_t t_2_1 = t_6;
        nile_Real_t t_2_2 = t_10;
        nile_Real_t t_11_x = t_2_1;
        nile_Real_t t_11_y = t_2_2;
        nile_Real_t t_13 = nile_Real_mul(v_M_a, v_B_x);
        nile_Real_t t_14 = nile_Real_mul(v_M_c, v_B_y);
        nile_Real_t t_15 = nile_Real_add(t_13, t_14);
        nile_Real_t t_16 = nile_Real_add(t_15, v_M_e);
        nile_Real_t t_17 = nile_Real_mul(v_M_b, v_B_x);
        nile_Real_t t_18 = nile_Real_mul(v_M_d, v_B_y);
        nile_Real_t t_19 = nile_Real_add(t_17, t_18);
        nile_Real_t t_20 = nile_Real_add(t_19, v_M_f);
        nile_Real_t t_12_1 = t_16;
        nile_Real_t t_12_2 = t_20;
        nile_Real_t t_21_x = t_12_1;
        nile_Real_t t_21_y = t_12_2;
        nile_Real_t t_23 = nile_Real_mul(v_M_a, v_C_x);
        nile_Real_t t_24 = nile_Real_mul(v_M_c, v_C_y);
        nile_Real_t t_25 = nile_Real_add(t_23, t_24);
        nile_Real_t t_26 = nile_Real_add(t_25, v_M_e);
        nile_Real_t t_27 = nile_Real_mul(v_M_b, v_C_x);
        nile_Real_t t_28 = nile_Real_mul(v_M_d, v_C_y);
        nile_Real_t t_29 = nile_Real_add(t_27, t_28);
        nile_Real_t t_30 = nile_Real_add(t_29, v_M_f);
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
        k->v_M_a = v_M_a;
        k->v_M_b = v_M_b;
        k->v_M_c = v_M_c;
        k->v_M_d = v_M_d;
        k->v_M_e = v_M_e;
        k->v_M_f = v_M_f;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
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

static nile_Kernel_t *gezira_UniformColor_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    gezira_UniformColor_t *clone = (gezira_UniformColor_t *) nile_Kernel_clone(nl, k_);
    clone->v_c_a = k->v_c_a;
    clone->v_c_r = k->v_c_r;
    clone->v_c_g = k->v_c_g;
    clone->v_c_b = k->v_c_b;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_UniformColor(nile_t *nl, 
                                   nile_Real_t v_c_a, 
                                   nile_Real_t v_c_r, 
                                   nile_Real_t v_c_g, 
                                   nile_Real_t v_c_b) {
    gezira_UniformColor_t *k = NILE_KERNEL_NEW(nl, gezira_UniformColor);
    k->v_c_a = v_c_a;
    k->v_c_r = v_c_r;
    k->v_c_g = v_c_g;
    k->v_c_b = v_c_b;
    return (nile_Kernel_t *) k;
}

static int gezira_UniformColor_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_) {
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
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
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
    nile_Kernel_t *v_s1;
    nile_Kernel_t *v_s2;
    nile_Kernel_t *v_c;
} gezira_CompositeSamplers_t;

static nile_Kernel_t *gezira_CompositeSamplers_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    gezira_CompositeSamplers_t *clone = (gezira_CompositeSamplers_t *) nile_Kernel_clone(nl, k_);
    clone->v_s1 = k->v_s1->clone(nl, k->v_s1);
    clone->v_s2 = k->v_s2->clone(nl, k->v_s2);
    clone->v_c = k->v_c->clone(nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSamplers(nile_t *nl, 
                                        nile_Kernel_t *v_s1, 
                                        nile_Kernel_t *v_s2, 
                                        nile_Kernel_t *v_c) {
    gezira_CompositeSamplers_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSamplers);
    k->v_s1 = v_s1;
    k->v_s2 = v_s2;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSamplers_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
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
        ; /* no-op */
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
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_ClipBeziers_t;

static nile_Kernel_t *gezira_ClipBeziers_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_ClipBeziers_t *k = (gezira_ClipBeziers_t *) k_;
    gezira_ClipBeziers_t *clone = (gezira_ClipBeziers_t *) nile_Kernel_clone(nl, k_);
    clone->v_min_x = k->v_min_x;
    clone->v_min_y = k->v_min_y;
    clone->v_max_x = k->v_max_x;
    clone->v_max_y = k->v_max_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_ClipBeziers(nile_t *nl, 
                                  nile_Real_t v_min_x, 
                                  nile_Real_t v_min_y, 
                                  nile_Real_t v_max_x, 
                                  nile_Real_t v_max_y) {
    gezira_ClipBeziers_t *k = NILE_KERNEL_NEW(nl, gezira_ClipBeziers);
    k->v_min_x = v_min_x;
    k->v_min_y = v_min_y;
    k->v_max_x = v_max_x;
    k->v_max_y = v_max_y;
    return (nile_Kernel_t *) k;
}

static int gezira_ClipBeziers_process(nile_t *nl,
                                      nile_Kernel_t *k_,
                                      nile_Buffer_t **in_,
                                      nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_ClipBeziers_t *k = (gezira_ClipBeziers_t *) k_;
    nile_Real_t v_min_x = k->v_min_x;
    nile_Real_t v_min_y = k->v_min_y;
    nile_Real_t v_max_x = k->v_max_x;
    nile_Real_t v_max_y = k->v_max_y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = nile_Real_lt(v_A_x, v_B_x);
        nile_Real_t t_2 = t_1 ? v_A_x : v_B_x;
        nile_Real_t t_3 = nile_Real_lt(v_A_y, v_B_y);
        nile_Real_t t_4 = t_3 ? v_A_y : v_B_y;
        nile_Real_t t_5_1 = t_2;
        nile_Real_t t_5_2 = t_4;
        nile_Real_t t_6_x = t_5_1;
        nile_Real_t t_6_y = t_5_2;
        nile_Real_t t_7 = nile_Real_lt(t_6_x, v_C_x);
        nile_Real_t t_8 = t_7 ? t_6_x : v_C_x;
        nile_Real_t t_9 = nile_Real_lt(t_6_y, v_C_y);
        nile_Real_t t_10 = t_9 ? t_6_y : v_C_y;
        nile_Real_t t_11_1 = t_8;
        nile_Real_t t_11_2 = t_10;
        nile_Real_t t_12_x = t_11_1;
        nile_Real_t t_12_y = t_11_2;
        nile_Real_t v_bmin_x = t_12_x;
        nile_Real_t v_bmin_y = t_12_y;
        nile_Real_t t_13 = nile_Real_gt(v_A_x, v_B_x);
        nile_Real_t t_14 = t_13 ? v_A_x : v_B_x;
        nile_Real_t t_15 = nile_Real_gt(v_A_y, v_B_y);
        nile_Real_t t_16 = t_15 ? v_A_y : v_B_y;
        nile_Real_t t_17_1 = t_14;
        nile_Real_t t_17_2 = t_16;
        nile_Real_t t_18_x = t_17_1;
        nile_Real_t t_18_y = t_17_2;
        nile_Real_t t_19 = nile_Real_gt(t_18_x, v_C_x);
        nile_Real_t t_20 = t_19 ? t_18_x : v_C_x;
        nile_Real_t t_21 = nile_Real_gt(t_18_y, v_C_y);
        nile_Real_t t_22 = t_21 ? t_18_y : v_C_y;
        nile_Real_t t_23_1 = t_20;
        nile_Real_t t_23_2 = t_22;
        nile_Real_t t_24_x = t_23_1;
        nile_Real_t t_24_y = t_23_2;
        nile_Real_t v_bmax_x = t_24_x;
        nile_Real_t v_bmax_y = t_24_y;
        nile_Real_t t_25_x = nile_Real_leq(v_min_x, v_bmin_x);
        nile_Real_t t_25_y = nile_Real_leq(v_min_y, v_bmin_y);
        nile_Real_t t_26_x = nile_Real_leq(v_bmax_x, v_max_x);
        nile_Real_t t_26_y = nile_Real_leq(v_bmax_y, v_max_y);
        nile_Real_t t_27_x = nile_Real_and(t_25_x, t_26_x);
        nile_Real_t t_27_y = nile_Real_and(t_25_y, t_26_y);
        nile_Real_t v_inside_x = t_27_x;
        nile_Real_t v_inside_y = t_27_y;
        nile_Real_t t_28_x = nile_Real_leq(v_bmax_x, v_min_x);
        nile_Real_t t_28_y = nile_Real_leq(v_bmax_y, v_min_y);
        nile_Real_t t_29_x = nile_Real_leq(v_max_x, v_bmin_x);
        nile_Real_t t_29_y = nile_Real_leq(v_max_y, v_bmin_y);
        nile_Real_t t_30_x = nile_Real_or(t_28_x, t_29_x);
        nile_Real_t t_30_y = nile_Real_or(t_28_y, t_29_y);
        nile_Real_t v_outside_x = t_30_x;
        nile_Real_t v_outside_y = t_30_y;
        nile_Real_t t_31 = nile_Real_and(v_inside_x, v_inside_y);
        if (t_31) {
            nile_Real_t t_32_1_x = v_A_x;
            nile_Real_t t_32_1_y = v_A_y;
            nile_Real_t t_32_2_x = v_B_x;
            nile_Real_t t_32_2_y = v_B_y;
            nile_Real_t t_32_3_x = v_C_x;
            nile_Real_t t_32_3_y = v_C_y;
            nile_Real_t t_33_a_x = t_32_1_x;
            nile_Real_t t_33_a_y = t_32_1_y;
            nile_Real_t t_33_b_x = t_32_2_x;
            nile_Real_t t_33_b_y = t_32_2_y;
            nile_Real_t t_33_c_x = t_32_3_x;
            nile_Real_t t_33_c_y = t_32_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_33_a_x);
            nile_Buffer_append(out, t_33_a_y);
            nile_Buffer_append(out, t_33_b_x);
            nile_Buffer_append(out, t_33_b_y);
            nile_Buffer_append(out, t_33_c_x);
            nile_Buffer_append(out, t_33_c_y);
        }
        else {
            nile_Real_t t_34 = nile_Real_or(v_outside_x, v_outside_y);
            if (t_34) {
                nile_Real_t t_35 = nile_Real_gt(v_min_x, v_A_x);
                nile_Real_t t_36 = t_35 ? v_min_x : v_A_x;
                nile_Real_t t_37 = nile_Real_gt(v_min_y, v_A_y);
                nile_Real_t t_38 = t_37 ? v_min_y : v_A_y;
                nile_Real_t t_39_1 = t_36;
                nile_Real_t t_39_2 = t_38;
                nile_Real_t t_40_x = t_39_1;
                nile_Real_t t_40_y = t_39_2;
                nile_Real_t t_41 = nile_Real_lt(t_40_x, v_max_x);
                nile_Real_t t_42 = t_41 ? t_40_x : v_max_x;
                nile_Real_t t_43 = nile_Real_lt(t_40_y, v_max_y);
                nile_Real_t t_44 = t_43 ? t_40_y : v_max_y;
                nile_Real_t t_45_1 = t_42;
                nile_Real_t t_45_2 = t_44;
                nile_Real_t t_46_x = t_45_1;
                nile_Real_t t_46_y = t_45_2;
                nile_Real_t v_cA_x = t_46_x;
                nile_Real_t v_cA_y = t_46_y;
                nile_Real_t t_47 = nile_Real_gt(v_min_x, v_C_x);
                nile_Real_t t_48 = t_47 ? v_min_x : v_C_x;
                nile_Real_t t_49 = nile_Real_gt(v_min_y, v_C_y);
                nile_Real_t t_50 = t_49 ? v_min_y : v_C_y;
                nile_Real_t t_51_1 = t_48;
                nile_Real_t t_51_2 = t_50;
                nile_Real_t t_52_x = t_51_1;
                nile_Real_t t_52_y = t_51_2;
                nile_Real_t t_53 = nile_Real_lt(t_52_x, v_max_x);
                nile_Real_t t_54 = t_53 ? t_52_x : v_max_x;
                nile_Real_t t_55 = nile_Real_lt(t_52_y, v_max_y);
                nile_Real_t t_56 = t_55 ? t_52_y : v_max_y;
                nile_Real_t t_57_1 = t_54;
                nile_Real_t t_57_2 = t_56;
                nile_Real_t t_58_x = t_57_1;
                nile_Real_t t_58_y = t_57_2;
                nile_Real_t v_cC_x = t_58_x;
                nile_Real_t v_cC_y = t_58_y;
                nile_Real_t t_60 = nile_Real_add(v_cA_x, v_cC_x);
                nile_Real_t t_61 = 2;
                nile_Real_t t_62 = nile_Real_div(t_60, t_61);
                nile_Real_t t_63 = nile_Real_add(v_cA_y, v_cC_y);
                nile_Real_t t_64 = 2;
                nile_Real_t t_65 = nile_Real_div(t_63, t_64);
                nile_Real_t t_66_1 = t_62;
                nile_Real_t t_66_2 = t_65;
                nile_Real_t t_67_x = t_66_1;
                nile_Real_t t_67_y = t_66_2;
                nile_Real_t t_59_1_x = v_cA_x;
                nile_Real_t t_59_1_y = v_cA_y;
                nile_Real_t t_59_2_x = t_67_x;
                nile_Real_t t_59_2_y = t_67_y;
                nile_Real_t t_59_3_x = v_cC_x;
                nile_Real_t t_59_3_y = v_cC_y;
                nile_Real_t t_68_a_x = t_59_1_x;
                nile_Real_t t_68_a_y = t_59_1_y;
                nile_Real_t t_68_b_x = t_59_2_x;
                nile_Real_t t_68_b_y = t_59_2_y;
                nile_Real_t t_68_c_x = t_59_3_x;
                nile_Real_t t_68_c_y = t_59_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_68_a_x);
                nile_Buffer_append(out, t_68_a_y);
                nile_Buffer_append(out, t_68_b_x);
                nile_Buffer_append(out, t_68_b_y);
                nile_Buffer_append(out, t_68_c_x);
                nile_Buffer_append(out, t_68_c_y);
            }
            else {
                nile_Real_t t_69 = nile_Real_add(v_A_x, v_B_x);
                nile_Real_t t_70 = 2;
                nile_Real_t t_71 = nile_Real_div(t_69, t_70);
                nile_Real_t t_72 = nile_Real_add(v_A_y, v_B_y);
                nile_Real_t t_73 = 2;
                nile_Real_t t_74 = nile_Real_div(t_72, t_73);
                nile_Real_t t_75_1 = t_71;
                nile_Real_t t_75_2 = t_74;
                nile_Real_t t_76_x = t_75_1;
                nile_Real_t t_76_y = t_75_2;
                nile_Real_t t_77 = nile_Real_add(v_B_x, v_C_x);
                nile_Real_t t_78 = 2;
                nile_Real_t t_79 = nile_Real_div(t_77, t_78);
                nile_Real_t t_80 = nile_Real_add(v_B_y, v_C_y);
                nile_Real_t t_81 = 2;
                nile_Real_t t_82 = nile_Real_div(t_80, t_81);
                nile_Real_t t_83_1 = t_79;
                nile_Real_t t_83_2 = t_82;
                nile_Real_t t_84_x = t_83_1;
                nile_Real_t t_84_y = t_83_2;
                nile_Real_t t_85 = nile_Real_add(t_76_x, t_84_x);
                nile_Real_t t_86 = 2;
                nile_Real_t t_87 = nile_Real_div(t_85, t_86);
                nile_Real_t t_88 = nile_Real_add(t_76_y, t_84_y);
                nile_Real_t t_89 = 2;
                nile_Real_t t_90 = nile_Real_div(t_88, t_89);
                nile_Real_t t_91_1 = t_87;
                nile_Real_t t_91_2 = t_90;
                nile_Real_t t_92_x = t_91_1;
                nile_Real_t t_92_y = t_91_2;
                nile_Real_t v_ABBC_x = t_92_x;
                nile_Real_t v_ABBC_y = t_92_y;
                nile_Real_t t_93_x = nile_Real_sub(v_ABBC_x, v_min_x);
                nile_Real_t t_93_y = nile_Real_sub(v_ABBC_y, v_min_y);
                nile_Real_t t_94 = 0;
                nile_Real_t t_95 = nile_Real_lt(t_93_x, t_94);
                nile_Real_t t_96 = nile_Real_neg(t_93_x);
                nile_Real_t t_97 = t_95 ? t_96 : t_93_x;
                nile_Real_t t_98 = 0;
                nile_Real_t t_99 = nile_Real_lt(t_93_y, t_98);
                nile_Real_t t_100 = nile_Real_neg(t_93_y);
                nile_Real_t t_101 = t_99 ? t_100 : t_93_y;
                nile_Real_t t_102_1 = t_97;
                nile_Real_t t_102_2 = t_101;
                nile_Real_t t_103_x = t_102_1;
                nile_Real_t t_103_y = t_102_2;
                nile_Real_t t_104 = 0.1;
                nile_Real_t t_105_x = t_104;
                nile_Real_t t_105_y = t_104;
                nile_Real_t t_106_x = nile_Real_lt(t_103_x, t_105_x);
                nile_Real_t t_106_y = nile_Real_lt(t_103_y, t_105_y);
                nile_Real_t v_nearmin_x = t_106_x;
                nile_Real_t v_nearmin_y = t_106_y;
                nile_Real_t t_107_x = nile_Real_sub(v_ABBC_x, v_max_x);
                nile_Real_t t_107_y = nile_Real_sub(v_ABBC_y, v_max_y);
                nile_Real_t t_108 = 0;
                nile_Real_t t_109 = nile_Real_lt(t_107_x, t_108);
                nile_Real_t t_110 = nile_Real_neg(t_107_x);
                nile_Real_t t_111 = t_109 ? t_110 : t_107_x;
                nile_Real_t t_112 = 0;
                nile_Real_t t_113 = nile_Real_lt(t_107_y, t_112);
                nile_Real_t t_114 = nile_Real_neg(t_107_y);
                nile_Real_t t_115 = t_113 ? t_114 : t_107_y;
                nile_Real_t t_116_1 = t_111;
                nile_Real_t t_116_2 = t_115;
                nile_Real_t t_117_x = t_116_1;
                nile_Real_t t_117_y = t_116_2;
                nile_Real_t t_118 = 0.1;
                nile_Real_t t_119_x = t_118;
                nile_Real_t t_119_y = t_118;
                nile_Real_t t_120_x = nile_Real_lt(t_117_x, t_119_x);
                nile_Real_t t_120_y = nile_Real_lt(t_117_y, t_119_y);
                nile_Real_t v_nearmax_x = t_120_x;
                nile_Real_t v_nearmax_y = t_120_y;
                nile_Real_t t_121_x = v_nearmax_x ? v_max_x : v_ABBC_x;
                nile_Real_t t_121_y = v_nearmax_y ? v_max_y : v_ABBC_y;
                nile_Real_t t_122_x = v_nearmin_x ? v_min_x : t_121_x;
                nile_Real_t t_122_y = v_nearmin_y ? v_min_y : t_121_y;
                nile_Real_t v_M_x = t_122_x;
                nile_Real_t v_M_y = t_122_y;
                nile_Real_t t_124 = nile_Real_add(v_A_x, v_B_x);
                nile_Real_t t_125 = 2;
                nile_Real_t t_126 = nile_Real_div(t_124, t_125);
                nile_Real_t t_127 = nile_Real_add(v_A_y, v_B_y);
                nile_Real_t t_128 = 2;
                nile_Real_t t_129 = nile_Real_div(t_127, t_128);
                nile_Real_t t_130_1 = t_126;
                nile_Real_t t_130_2 = t_129;
                nile_Real_t t_131_x = t_130_1;
                nile_Real_t t_131_y = t_130_2;
                nile_Real_t t_123_1_x = v_A_x;
                nile_Real_t t_123_1_y = v_A_y;
                nile_Real_t t_123_2_x = t_131_x;
                nile_Real_t t_123_2_y = t_131_y;
                nile_Real_t t_123_3_x = v_M_x;
                nile_Real_t t_123_3_y = v_M_y;
                nile_Real_t t_132_a_x = t_123_1_x;
                nile_Real_t t_132_a_y = t_123_1_y;
                nile_Real_t t_132_b_x = t_123_2_x;
                nile_Real_t t_132_b_y = t_123_2_y;
                nile_Real_t t_132_c_x = t_123_3_x;
                nile_Real_t t_132_c_y = t_123_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_132_a_x);
                nile_Buffer_prepend(in, t_132_a_y);
                nile_Buffer_prepend(in, t_132_b_x);
                nile_Buffer_prepend(in, t_132_b_y);
                nile_Buffer_prepend(in, t_132_c_x);
                nile_Buffer_prepend(in, t_132_c_y);
                in->i -= IN_QUANTUM;
                nile_Real_t t_134 = nile_Real_add(v_B_x, v_C_x);
                nile_Real_t t_135 = 2;
                nile_Real_t t_136 = nile_Real_div(t_134, t_135);
                nile_Real_t t_137 = nile_Real_add(v_B_y, v_C_y);
                nile_Real_t t_138 = 2;
                nile_Real_t t_139 = nile_Real_div(t_137, t_138);
                nile_Real_t t_140_1 = t_136;
                nile_Real_t t_140_2 = t_139;
                nile_Real_t t_141_x = t_140_1;
                nile_Real_t t_141_y = t_140_2;
                nile_Real_t t_133_1_x = v_M_x;
                nile_Real_t t_133_1_y = v_M_y;
                nile_Real_t t_133_2_x = t_141_x;
                nile_Real_t t_133_2_y = t_141_y;
                nile_Real_t t_133_3_x = v_C_x;
                nile_Real_t t_133_3_y = v_C_y;
                nile_Real_t t_142_a_x = t_133_1_x;
                nile_Real_t t_142_a_y = t_133_1_y;
                nile_Real_t t_142_b_x = t_133_2_x;
                nile_Real_t t_142_b_y = t_133_2_y;
                nile_Real_t t_142_c_x = t_133_3_x;
                nile_Real_t t_142_c_y = t_133_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_142_a_x);
                nile_Buffer_prepend(in, t_142_a_y);
                nile_Buffer_prepend(in, t_142_b_x);
                nile_Buffer_prepend(in, t_142_b_y);
                nile_Buffer_prepend(in, t_142_c_x);
                nile_Buffer_prepend(in, t_142_c_y);
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
} gezira_CompositeClear_t;

static nile_Kernel_t *gezira_CompositeClear_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeClear_t *k = (gezira_CompositeClear_t *) k_;
    gezira_CompositeClear_t *clone = (gezira_CompositeClear_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeClear(nile_t *nl) {
    gezira_CompositeClear_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeClear);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeClear_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeClear_t *k = (gezira_CompositeClear_t *) k_;
    
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
        nile_Real_t t_1 = 0;
        nile_Real_t t_2_a = t_1;
        nile_Real_t t_2_r = t_1;
        nile_Real_t t_2_g = t_1;
        nile_Real_t t_2_b = t_1;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_2_a);
        nile_Buffer_append(out, t_2_r);
        nile_Buffer_append(out, t_2_g);
        nile_Buffer_append(out, t_2_b);
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
} gezira_CompositeSrc_t;

static nile_Kernel_t *gezira_CompositeSrc_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSrc_t *k = (gezira_CompositeSrc_t *) k_;
    gezira_CompositeSrc_t *clone = (gezira_CompositeSrc_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSrc(nile_t *nl) {
    gezira_CompositeSrc_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSrc);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSrc_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSrc_t *k = (gezira_CompositeSrc_t *) k_;
    
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
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, v_a_a);
        nile_Buffer_append(out, v_a_r);
        nile_Buffer_append(out, v_a_g);
        nile_Buffer_append(out, v_a_b);
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
} gezira_CompositeDst_t;

static nile_Kernel_t *gezira_CompositeDst_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDst_t *k = (gezira_CompositeDst_t *) k_;
    gezira_CompositeDst_t *clone = (gezira_CompositeDst_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDst(nile_t *nl) {
    gezira_CompositeDst_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDst);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDst_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDst_t *k = (gezira_CompositeDst_t *) k_;
    
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
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, v_b_a);
        nile_Buffer_append(out, v_b_r);
        nile_Buffer_append(out, v_b_g);
        nile_Buffer_append(out, v_b_b);
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
} gezira_CompositeOver_t;

static nile_Kernel_t *gezira_CompositeOver_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;
    gezira_CompositeOver_t *clone = (gezira_CompositeOver_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeOver(nile_t *nl) {
    gezira_CompositeOver_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeOver);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeOver_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_) {
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
} gezira_CompositeDstOver_t;

static nile_Kernel_t *gezira_CompositeDstOver_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDstOver_t *k = (gezira_CompositeDstOver_t *) k_;
    gezira_CompositeDstOver_t *clone = (gezira_CompositeDstOver_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDstOver(nile_t *nl) {
    gezira_CompositeDstOver_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDstOver);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDstOver_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDstOver_t *k = (gezira_CompositeDstOver_t *) k_;
    
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
        nile_Real_t t_2 = nile_Real_sub(t_1, v_b_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        nile_Real_t t_5_a = nile_Real_add(v_b_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_add(v_b_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_add(v_b_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_add(v_b_b, t_4_b);
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
} gezira_CompositeSrcIn_t;

static nile_Kernel_t *gezira_CompositeSrcIn_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSrcIn_t *k = (gezira_CompositeSrcIn_t *) k_;
    gezira_CompositeSrcIn_t *clone = (gezira_CompositeSrcIn_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSrcIn(nile_t *nl) {
    gezira_CompositeSrcIn_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSrcIn);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSrcIn_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSrcIn_t *k = (gezira_CompositeSrcIn_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_2_a);
        nile_Buffer_append(out, t_2_r);
        nile_Buffer_append(out, t_2_g);
        nile_Buffer_append(out, t_2_b);
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
} gezira_CompositeDstIn_t;

static nile_Kernel_t *gezira_CompositeDstIn_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDstIn_t *k = (gezira_CompositeDstIn_t *) k_;
    gezira_CompositeDstIn_t *clone = (gezira_CompositeDstIn_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDstIn(nile_t *nl) {
    gezira_CompositeDstIn_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDstIn);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDstIn_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDstIn_t *k = (gezira_CompositeDstIn_t *) k_;
    
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
        nile_Real_t t_1_a = v_a_a;
        nile_Real_t t_1_r = v_a_a;
        nile_Real_t t_1_g = v_a_a;
        nile_Real_t t_1_b = v_a_a;
        nile_Real_t t_2_a = nile_Real_mul(v_b_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_b_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_b_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_b_b, t_1_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_2_a);
        nile_Buffer_append(out, t_2_r);
        nile_Buffer_append(out, t_2_g);
        nile_Buffer_append(out, t_2_b);
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
} gezira_CompositeSrcOut_t;

static nile_Kernel_t *gezira_CompositeSrcOut_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSrcOut_t *k = (gezira_CompositeSrcOut_t *) k_;
    gezira_CompositeSrcOut_t *clone = (gezira_CompositeSrcOut_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSrcOut(nile_t *nl) {
    gezira_CompositeSrcOut_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSrcOut);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSrcOut_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSrcOut_t *k = (gezira_CompositeSrcOut_t *) k_;
    
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
        nile_Real_t t_2 = nile_Real_sub(t_1, v_b_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_4_a);
        nile_Buffer_append(out, t_4_r);
        nile_Buffer_append(out, t_4_g);
        nile_Buffer_append(out, t_4_b);
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
} gezira_CompositeDstOut_t;

static nile_Kernel_t *gezira_CompositeDstOut_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDstOut_t *k = (gezira_CompositeDstOut_t *) k_;
    gezira_CompositeDstOut_t *clone = (gezira_CompositeDstOut_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDstOut(nile_t *nl) {
    gezira_CompositeDstOut_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDstOut);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDstOut_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDstOut_t *k = (gezira_CompositeDstOut_t *) k_;
    
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
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_4_a);
        nile_Buffer_append(out, t_4_r);
        nile_Buffer_append(out, t_4_g);
        nile_Buffer_append(out, t_4_b);
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
} gezira_CompositeSrcAtop_t;

static nile_Kernel_t *gezira_CompositeSrcAtop_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSrcAtop_t *k = (gezira_CompositeSrcAtop_t *) k_;
    gezira_CompositeSrcAtop_t *clone = (gezira_CompositeSrcAtop_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSrcAtop(nile_t *nl) {
    gezira_CompositeSrcAtop_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSrcAtop);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSrcAtop_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSrcAtop_t *k = (gezira_CompositeSrcAtop_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3 = 1;
        nile_Real_t t_4 = nile_Real_sub(t_3, v_a_a);
        nile_Real_t t_5_a = t_4;
        nile_Real_t t_5_r = t_4;
        nile_Real_t t_5_g = t_4;
        nile_Real_t t_5_b = t_4;
        nile_Real_t t_6_a = nile_Real_mul(v_b_a, t_5_a);
        nile_Real_t t_6_r = nile_Real_mul(v_b_r, t_5_r);
        nile_Real_t t_6_g = nile_Real_mul(v_b_g, t_5_g);
        nile_Real_t t_6_b = nile_Real_mul(v_b_b, t_5_b);
        nile_Real_t t_7_a = nile_Real_add(t_2_a, t_6_a);
        nile_Real_t t_7_r = nile_Real_add(t_2_r, t_6_r);
        nile_Real_t t_7_g = nile_Real_add(t_2_g, t_6_g);
        nile_Real_t t_7_b = nile_Real_add(t_2_b, t_6_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_7_a);
        nile_Buffer_append(out, t_7_r);
        nile_Buffer_append(out, t_7_g);
        nile_Buffer_append(out, t_7_b);
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
} gezira_CompositeDstAtop_t;

static nile_Kernel_t *gezira_CompositeDstAtop_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDstAtop_t *k = (gezira_CompositeDstAtop_t *) k_;
    gezira_CompositeDstAtop_t *clone = (gezira_CompositeDstAtop_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDstAtop(nile_t *nl) {
    gezira_CompositeDstAtop_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDstAtop);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDstAtop_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDstAtop_t *k = (gezira_CompositeDstAtop_t *) k_;
    
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
        nile_Real_t t_1_a = v_a_a;
        nile_Real_t t_1_r = v_a_a;
        nile_Real_t t_1_g = v_a_a;
        nile_Real_t t_1_b = v_a_a;
        nile_Real_t t_2_a = nile_Real_mul(v_b_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_b_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_b_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_b_b, t_1_b);
        nile_Real_t t_3 = 1;
        nile_Real_t t_4 = nile_Real_sub(t_3, v_b_a);
        nile_Real_t t_5_a = t_4;
        nile_Real_t t_5_r = t_4;
        nile_Real_t t_5_g = t_4;
        nile_Real_t t_5_b = t_4;
        nile_Real_t t_6_a = nile_Real_mul(v_a_a, t_5_a);
        nile_Real_t t_6_r = nile_Real_mul(v_a_r, t_5_r);
        nile_Real_t t_6_g = nile_Real_mul(v_a_g, t_5_g);
        nile_Real_t t_6_b = nile_Real_mul(v_a_b, t_5_b);
        nile_Real_t t_7_a = nile_Real_add(t_2_a, t_6_a);
        nile_Real_t t_7_r = nile_Real_add(t_2_r, t_6_r);
        nile_Real_t t_7_g = nile_Real_add(t_2_g, t_6_g);
        nile_Real_t t_7_b = nile_Real_add(t_2_b, t_6_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_7_a);
        nile_Buffer_append(out, t_7_r);
        nile_Buffer_append(out, t_7_g);
        nile_Buffer_append(out, t_7_b);
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
} gezira_CompositeXor_t;

static nile_Kernel_t *gezira_CompositeXor_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeXor_t *k = (gezira_CompositeXor_t *) k_;
    gezira_CompositeXor_t *clone = (gezira_CompositeXor_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeXor(nile_t *nl) {
    gezira_CompositeXor_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeXor);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeXor_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeXor_t *k = (gezira_CompositeXor_t *) k_;
    
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
        nile_Real_t t_2 = nile_Real_sub(t_1, v_b_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        nile_Real_t t_5 = 1;
        nile_Real_t t_6 = nile_Real_sub(t_5, v_a_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(v_b_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_mul(v_b_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_mul(v_b_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_mul(v_b_b, t_7_b);
        nile_Real_t t_9_a = nile_Real_add(t_4_a, t_8_a);
        nile_Real_t t_9_r = nile_Real_add(t_4_r, t_8_r);
        nile_Real_t t_9_g = nile_Real_add(t_4_g, t_8_g);
        nile_Real_t t_9_b = nile_Real_add(t_4_b, t_8_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_9_a);
        nile_Buffer_append(out, t_9_r);
        nile_Buffer_append(out, t_9_g);
        nile_Buffer_append(out, t_9_b);
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
} gezira_CompositePlus_t;

static nile_Kernel_t *gezira_CompositePlus_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositePlus_t *k = (gezira_CompositePlus_t *) k_;
    gezira_CompositePlus_t *clone = (gezira_CompositePlus_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositePlus(nile_t *nl) {
    gezira_CompositePlus_t *k = NILE_KERNEL_NEW(nl, gezira_CompositePlus);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositePlus_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositePlus_t *k = (gezira_CompositePlus_t *) k_;
    
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
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = 1;
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4 = nile_Real_lt(t_1_a, t_3_a);
        nile_Real_t t_5 = t_4 ? t_1_a : t_3_a;
        nile_Real_t t_6 = nile_Real_lt(t_1_r, t_3_r);
        nile_Real_t t_7 = t_6 ? t_1_r : t_3_r;
        nile_Real_t t_8 = nile_Real_lt(t_1_g, t_3_g);
        nile_Real_t t_9 = t_8 ? t_1_g : t_3_g;
        nile_Real_t t_10 = nile_Real_lt(t_1_b, t_3_b);
        nile_Real_t t_11 = t_10 ? t_1_b : t_3_b;
        nile_Real_t t_12_1 = t_5;
        nile_Real_t t_12_2 = t_7;
        nile_Real_t t_12_3 = t_9;
        nile_Real_t t_12_4 = t_11;
        nile_Real_t t_13_a = t_12_1;
        nile_Real_t t_13_r = t_12_2;
        nile_Real_t t_13_g = t_12_3;
        nile_Real_t t_13_b = t_12_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_13_a);
        nile_Buffer_append(out, t_13_r);
        nile_Buffer_append(out, t_13_g);
        nile_Buffer_append(out, t_13_b);
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
} gezira_CompositeMultiply_t;

static nile_Kernel_t *gezira_CompositeMultiply_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeMultiply_t *k = (gezira_CompositeMultiply_t *) k_;
    gezira_CompositeMultiply_t *clone = (gezira_CompositeMultiply_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeMultiply(nile_t *nl) {
    gezira_CompositeMultiply_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeMultiply);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeMultiply_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeMultiply_t *k = (gezira_CompositeMultiply_t *) k_;
    
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
        nile_Real_t t_1_a = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_mul(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_mul(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_mul(v_a_b, v_b_b);
        nile_Real_t t_2 = 1;
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_a);
        nile_Real_t t_4_a = t_3;
        nile_Real_t t_4_r = t_3;
        nile_Real_t t_4_g = t_3;
        nile_Real_t t_4_b = t_3;
        nile_Real_t t_5_a = nile_Real_mul(v_a_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_mul(v_a_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_mul(v_a_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_mul(v_a_b, t_4_b);
        nile_Real_t t_6 = 1;
        nile_Real_t t_7 = nile_Real_sub(t_6, v_a_a);
        nile_Real_t t_8_a = t_7;
        nile_Real_t t_8_r = t_7;
        nile_Real_t t_8_g = t_7;
        nile_Real_t t_8_b = t_7;
        nile_Real_t t_9_a = nile_Real_mul(v_b_a, t_8_a);
        nile_Real_t t_9_r = nile_Real_mul(v_b_r, t_8_r);
        nile_Real_t t_9_g = nile_Real_mul(v_b_g, t_8_g);
        nile_Real_t t_9_b = nile_Real_mul(v_b_b, t_8_b);
        nile_Real_t t_10_a = nile_Real_add(t_5_a, t_9_a);
        nile_Real_t t_10_r = nile_Real_add(t_5_r, t_9_r);
        nile_Real_t t_10_g = nile_Real_add(t_5_g, t_9_g);
        nile_Real_t t_10_b = nile_Real_add(t_5_b, t_9_b);
        nile_Real_t t_11_a = nile_Real_add(t_1_a, t_10_a);
        nile_Real_t t_11_r = nile_Real_add(t_1_r, t_10_r);
        nile_Real_t t_11_g = nile_Real_add(t_1_g, t_10_g);
        nile_Real_t t_11_b = nile_Real_add(t_1_b, t_10_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_11_a);
        nile_Buffer_append(out, t_11_r);
        nile_Buffer_append(out, t_11_g);
        nile_Buffer_append(out, t_11_b);
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
} gezira_CompositeScreen_t;

static nile_Kernel_t *gezira_CompositeScreen_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeScreen_t *k = (gezira_CompositeScreen_t *) k_;
    gezira_CompositeScreen_t *clone = (gezira_CompositeScreen_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeScreen(nile_t *nl) {
    gezira_CompositeScreen_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeScreen);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeScreen_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeScreen_t *k = (gezira_CompositeScreen_t *) k_;
    
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
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, v_b_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, v_b_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, v_b_b);
        nile_Real_t t_3_a = nile_Real_sub(t_1_a, t_2_a);
        nile_Real_t t_3_r = nile_Real_sub(t_1_r, t_2_r);
        nile_Real_t t_3_g = nile_Real_sub(t_1_g, t_2_g);
        nile_Real_t t_3_b = nile_Real_sub(t_1_b, t_2_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_3_a);
        nile_Buffer_append(out, t_3_r);
        nile_Buffer_append(out, t_3_g);
        nile_Buffer_append(out, t_3_b);
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
} gezira_CompositeOverlay_t;

static nile_Kernel_t *gezira_CompositeOverlay_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeOverlay_t *k = (gezira_CompositeOverlay_t *) k_;
    gezira_CompositeOverlay_t *clone = (gezira_CompositeOverlay_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeOverlay(nile_t *nl) {
    gezira_CompositeOverlay_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeOverlay);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeOverlay_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeOverlay_t *k = (gezira_CompositeOverlay_t *) k_;
    
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
        nile_Real_t t_1 = 2;
        nile_Real_t t_2_a = t_1;
        nile_Real_t t_2_r = t_1;
        nile_Real_t t_2_g = t_1;
        nile_Real_t t_2_b = t_1;
        nile_Real_t t_3_a = nile_Real_mul(t_2_a, v_a_a);
        nile_Real_t t_3_r = nile_Real_mul(t_2_r, v_a_r);
        nile_Real_t t_3_g = nile_Real_mul(t_2_g, v_a_g);
        nile_Real_t t_3_b = nile_Real_mul(t_2_b, v_a_b);
        nile_Real_t t_4_a = nile_Real_mul(t_3_a, v_b_a);
        nile_Real_t t_4_r = nile_Real_mul(t_3_r, v_b_r);
        nile_Real_t t_4_g = nile_Real_mul(t_3_g, v_b_g);
        nile_Real_t t_4_b = nile_Real_mul(t_3_b, v_b_b);
        nile_Real_t t_5 = 1;
        nile_Real_t t_6 = nile_Real_sub(t_5, v_b_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(v_a_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_mul(v_a_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_mul(v_a_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_mul(v_a_b, t_7_b);
        nile_Real_t t_9 = 1;
        nile_Real_t t_10 = nile_Real_sub(t_9, v_a_a);
        nile_Real_t t_11_a = t_10;
        nile_Real_t t_11_r = t_10;
        nile_Real_t t_11_g = t_10;
        nile_Real_t t_11_b = t_10;
        nile_Real_t t_12_a = nile_Real_mul(v_b_a, t_11_a);
        nile_Real_t t_12_r = nile_Real_mul(v_b_r, t_11_r);
        nile_Real_t t_12_g = nile_Real_mul(v_b_g, t_11_g);
        nile_Real_t t_12_b = nile_Real_mul(v_b_b, t_11_b);
        nile_Real_t t_13_a = nile_Real_add(t_8_a, t_12_a);
        nile_Real_t t_13_r = nile_Real_add(t_8_r, t_12_r);
        nile_Real_t t_13_g = nile_Real_add(t_8_g, t_12_g);
        nile_Real_t t_13_b = nile_Real_add(t_8_b, t_12_b);
        nile_Real_t t_14_a = nile_Real_add(t_4_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_add(t_4_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_add(t_4_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_add(t_4_b, t_13_b);
        nile_Real_t v_c_a = t_14_a;
        nile_Real_t v_c_r = t_14_r;
        nile_Real_t v_c_g = t_14_g;
        nile_Real_t v_c_b = t_14_b;
        nile_Real_t t_15 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_16 = 2;
        nile_Real_t t_17_a = v_b_a;
        nile_Real_t t_17_r = v_b_a;
        nile_Real_t t_17_g = v_b_a;
        nile_Real_t t_17_b = v_b_a;
        nile_Real_t t_18_a = nile_Real_sub(t_17_a, v_b_a);
        nile_Real_t t_18_r = nile_Real_sub(t_17_r, v_b_r);
        nile_Real_t t_18_g = nile_Real_sub(t_17_g, v_b_g);
        nile_Real_t t_18_b = nile_Real_sub(t_17_b, v_b_b);
        nile_Real_t t_19_a = t_16;
        nile_Real_t t_19_r = t_16;
        nile_Real_t t_19_g = t_16;
        nile_Real_t t_19_b = t_16;
        nile_Real_t t_20_a = nile_Real_mul(t_19_a, t_18_a);
        nile_Real_t t_20_r = nile_Real_mul(t_19_r, t_18_r);
        nile_Real_t t_20_g = nile_Real_mul(t_19_g, t_18_g);
        nile_Real_t t_20_b = nile_Real_mul(t_19_b, t_18_b);
        nile_Real_t t_21_a = v_a_a;
        nile_Real_t t_21_r = v_a_a;
        nile_Real_t t_21_g = v_a_a;
        nile_Real_t t_21_b = v_a_a;
        nile_Real_t t_22_a = nile_Real_sub(t_21_a, v_a_a);
        nile_Real_t t_22_r = nile_Real_sub(t_21_r, v_a_r);
        nile_Real_t t_22_g = nile_Real_sub(t_21_g, v_a_g);
        nile_Real_t t_22_b = nile_Real_sub(t_21_b, v_a_b);
        nile_Real_t t_23_a = nile_Real_mul(t_20_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_mul(t_20_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_mul(t_20_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_mul(t_20_b, t_22_b);
        nile_Real_t t_24_a = t_15;
        nile_Real_t t_24_r = t_15;
        nile_Real_t t_24_g = t_15;
        nile_Real_t t_24_b = t_15;
        nile_Real_t t_25_a = nile_Real_sub(t_24_a, t_23_a);
        nile_Real_t t_25_r = nile_Real_sub(t_24_r, t_23_r);
        nile_Real_t t_25_g = nile_Real_sub(t_24_g, t_23_g);
        nile_Real_t t_25_b = nile_Real_sub(t_24_b, t_23_b);
        nile_Real_t t_26 = 1;
        nile_Real_t t_27 = nile_Real_sub(t_26, v_b_a);
        nile_Real_t t_28_a = t_27;
        nile_Real_t t_28_r = t_27;
        nile_Real_t t_28_g = t_27;
        nile_Real_t t_28_b = t_27;
        nile_Real_t t_29_a = nile_Real_mul(v_a_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_mul(v_a_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_mul(v_a_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_mul(v_a_b, t_28_b);
        nile_Real_t t_30 = 1;
        nile_Real_t t_31 = nile_Real_sub(t_30, v_a_a);
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33_a = nile_Real_mul(v_b_a, t_32_a);
        nile_Real_t t_33_r = nile_Real_mul(v_b_r, t_32_r);
        nile_Real_t t_33_g = nile_Real_mul(v_b_g, t_32_g);
        nile_Real_t t_33_b = nile_Real_mul(v_b_b, t_32_b);
        nile_Real_t t_34_a = nile_Real_add(t_29_a, t_33_a);
        nile_Real_t t_34_r = nile_Real_add(t_29_r, t_33_r);
        nile_Real_t t_34_g = nile_Real_add(t_29_g, t_33_g);
        nile_Real_t t_34_b = nile_Real_add(t_29_b, t_33_b);
        nile_Real_t t_35_a = nile_Real_add(t_25_a, t_34_a);
        nile_Real_t t_35_r = nile_Real_add(t_25_r, t_34_r);
        nile_Real_t t_35_g = nile_Real_add(t_25_g, t_34_g);
        nile_Real_t t_35_b = nile_Real_add(t_25_b, t_34_b);
        nile_Real_t v_d_a = t_35_a;
        nile_Real_t v_d_r = t_35_r;
        nile_Real_t v_d_g = t_35_g;
        nile_Real_t v_d_b = t_35_b;
        nile_Real_t t_36 = 2;
        nile_Real_t t_37_a = t_36;
        nile_Real_t t_37_r = t_36;
        nile_Real_t t_37_g = t_36;
        nile_Real_t t_37_b = t_36;
        nile_Real_t t_38_a = nile_Real_mul(t_37_a, v_b_a);
        nile_Real_t t_38_r = nile_Real_mul(t_37_r, v_b_r);
        nile_Real_t t_38_g = nile_Real_mul(t_37_g, v_b_g);
        nile_Real_t t_38_b = nile_Real_mul(t_37_b, v_b_b);
        nile_Real_t t_39_a = v_b_a;
        nile_Real_t t_39_r = v_b_a;
        nile_Real_t t_39_g = v_b_a;
        nile_Real_t t_39_b = v_b_a;
        nile_Real_t t_40_a = nile_Real_lt(t_38_a, t_39_a);
        nile_Real_t t_40_r = nile_Real_lt(t_38_r, t_39_r);
        nile_Real_t t_40_g = nile_Real_lt(t_38_g, t_39_g);
        nile_Real_t t_40_b = nile_Real_lt(t_38_b, t_39_b);
        nile_Real_t t_41_a = t_40_a ? v_c_a : v_d_a;
        nile_Real_t t_41_r = t_40_r ? v_c_r : v_d_r;
        nile_Real_t t_41_g = t_40_g ? v_c_g : v_d_g;
        nile_Real_t t_41_b = t_40_b ? v_c_b : v_d_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_41_a);
        nile_Buffer_append(out, t_41_r);
        nile_Buffer_append(out, t_41_g);
        nile_Buffer_append(out, t_41_b);
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
} gezira_CompositeDarken_t;

static nile_Kernel_t *gezira_CompositeDarken_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDarken_t *k = (gezira_CompositeDarken_t *) k_;
    gezira_CompositeDarken_t *clone = (gezira_CompositeDarken_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDarken(nile_t *nl) {
    gezira_CompositeDarken_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDarken);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDarken_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDarken_t *k = (gezira_CompositeDarken_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3_a = v_a_a;
        nile_Real_t t_3_r = v_a_a;
        nile_Real_t t_3_g = v_a_a;
        nile_Real_t t_3_b = v_a_a;
        nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
        nile_Real_t t_5 = nile_Real_lt(t_2_a, t_4_a);
        nile_Real_t t_6 = t_5 ? t_2_a : t_4_a;
        nile_Real_t t_7 = nile_Real_lt(t_2_r, t_4_r);
        nile_Real_t t_8 = t_7 ? t_2_r : t_4_r;
        nile_Real_t t_9 = nile_Real_lt(t_2_g, t_4_g);
        nile_Real_t t_10 = t_9 ? t_2_g : t_4_g;
        nile_Real_t t_11 = nile_Real_lt(t_2_b, t_4_b);
        nile_Real_t t_12 = t_11 ? t_2_b : t_4_b;
        nile_Real_t t_13_1 = t_6;
        nile_Real_t t_13_2 = t_8;
        nile_Real_t t_13_3 = t_10;
        nile_Real_t t_13_4 = t_12;
        nile_Real_t t_14_a = t_13_1;
        nile_Real_t t_14_r = t_13_2;
        nile_Real_t t_14_g = t_13_3;
        nile_Real_t t_14_b = t_13_4;
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = 1;
        nile_Real_t t_20 = nile_Real_sub(t_19, v_a_a);
        nile_Real_t t_21_a = t_20;
        nile_Real_t t_21_r = t_20;
        nile_Real_t t_21_g = t_20;
        nile_Real_t t_21_b = t_20;
        nile_Real_t t_22_a = nile_Real_mul(v_b_a, t_21_a);
        nile_Real_t t_22_r = nile_Real_mul(v_b_r, t_21_r);
        nile_Real_t t_22_g = nile_Real_mul(v_b_g, t_21_g);
        nile_Real_t t_22_b = nile_Real_mul(v_b_b, t_21_b);
        nile_Real_t t_23_a = nile_Real_add(t_18_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_add(t_18_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_add(t_18_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_add(t_18_b, t_22_b);
        nile_Real_t t_24_a = nile_Real_add(t_14_a, t_23_a);
        nile_Real_t t_24_r = nile_Real_add(t_14_r, t_23_r);
        nile_Real_t t_24_g = nile_Real_add(t_14_g, t_23_g);
        nile_Real_t t_24_b = nile_Real_add(t_14_b, t_23_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_24_a);
        nile_Buffer_append(out, t_24_r);
        nile_Buffer_append(out, t_24_g);
        nile_Buffer_append(out, t_24_b);
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
} gezira_CompositeLighten_t;

static nile_Kernel_t *gezira_CompositeLighten_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeLighten_t *k = (gezira_CompositeLighten_t *) k_;
    gezira_CompositeLighten_t *clone = (gezira_CompositeLighten_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeLighten(nile_t *nl) {
    gezira_CompositeLighten_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeLighten);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeLighten_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeLighten_t *k = (gezira_CompositeLighten_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3_a = v_a_a;
        nile_Real_t t_3_r = v_a_a;
        nile_Real_t t_3_g = v_a_a;
        nile_Real_t t_3_b = v_a_a;
        nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
        nile_Real_t t_5 = nile_Real_gt(t_2_a, t_4_a);
        nile_Real_t t_6 = t_5 ? t_2_a : t_4_a;
        nile_Real_t t_7 = nile_Real_gt(t_2_r, t_4_r);
        nile_Real_t t_8 = t_7 ? t_2_r : t_4_r;
        nile_Real_t t_9 = nile_Real_gt(t_2_g, t_4_g);
        nile_Real_t t_10 = t_9 ? t_2_g : t_4_g;
        nile_Real_t t_11 = nile_Real_gt(t_2_b, t_4_b);
        nile_Real_t t_12 = t_11 ? t_2_b : t_4_b;
        nile_Real_t t_13_1 = t_6;
        nile_Real_t t_13_2 = t_8;
        nile_Real_t t_13_3 = t_10;
        nile_Real_t t_13_4 = t_12;
        nile_Real_t t_14_a = t_13_1;
        nile_Real_t t_14_r = t_13_2;
        nile_Real_t t_14_g = t_13_3;
        nile_Real_t t_14_b = t_13_4;
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = 1;
        nile_Real_t t_20 = nile_Real_sub(t_19, v_a_a);
        nile_Real_t t_21_a = t_20;
        nile_Real_t t_21_r = t_20;
        nile_Real_t t_21_g = t_20;
        nile_Real_t t_21_b = t_20;
        nile_Real_t t_22_a = nile_Real_mul(v_b_a, t_21_a);
        nile_Real_t t_22_r = nile_Real_mul(v_b_r, t_21_r);
        nile_Real_t t_22_g = nile_Real_mul(v_b_g, t_21_g);
        nile_Real_t t_22_b = nile_Real_mul(v_b_b, t_21_b);
        nile_Real_t t_23_a = nile_Real_add(t_18_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_add(t_18_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_add(t_18_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_add(t_18_b, t_22_b);
        nile_Real_t t_24_a = nile_Real_add(t_14_a, t_23_a);
        nile_Real_t t_24_r = nile_Real_add(t_14_r, t_23_r);
        nile_Real_t t_24_g = nile_Real_add(t_14_g, t_23_g);
        nile_Real_t t_24_b = nile_Real_add(t_14_b, t_23_b);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_24_a);
        nile_Buffer_append(out, t_24_r);
        nile_Buffer_append(out, t_24_g);
        nile_Buffer_append(out, t_24_b);
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
} gezira_CompositeColorDodge_t;

static nile_Kernel_t *gezira_CompositeColorDodge_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeColorDodge_t *k = (gezira_CompositeColorDodge_t *) k_;
    gezira_CompositeColorDodge_t *clone = (gezira_CompositeColorDodge_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeColorDodge(nile_t *nl) {
    gezira_CompositeColorDodge_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeColorDodge);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeColorDodge_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeColorDodge_t *k = (gezira_CompositeColorDodge_t *) k_;
    
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
        nile_Real_t t_1 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_2 = 1;
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_a);
        nile_Real_t t_4_a = t_3;
        nile_Real_t t_4_r = t_3;
        nile_Real_t t_4_g = t_3;
        nile_Real_t t_4_b = t_3;
        nile_Real_t t_5_a = nile_Real_mul(v_a_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_mul(v_a_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_mul(v_a_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_mul(v_a_b, t_4_b);
        nile_Real_t t_6 = 1;
        nile_Real_t t_7 = nile_Real_sub(t_6, v_a_a);
        nile_Real_t t_8_a = t_7;
        nile_Real_t t_8_r = t_7;
        nile_Real_t t_8_g = t_7;
        nile_Real_t t_8_b = t_7;
        nile_Real_t t_9_a = nile_Real_mul(v_b_a, t_8_a);
        nile_Real_t t_9_r = nile_Real_mul(v_b_r, t_8_r);
        nile_Real_t t_9_g = nile_Real_mul(v_b_g, t_8_g);
        nile_Real_t t_9_b = nile_Real_mul(v_b_b, t_8_b);
        nile_Real_t t_10_a = nile_Real_add(t_5_a, t_9_a);
        nile_Real_t t_10_r = nile_Real_add(t_5_r, t_9_r);
        nile_Real_t t_10_g = nile_Real_add(t_5_g, t_9_g);
        nile_Real_t t_10_b = nile_Real_add(t_5_b, t_9_b);
        nile_Real_t t_11_a = t_1;
        nile_Real_t t_11_r = t_1;
        nile_Real_t t_11_g = t_1;
        nile_Real_t t_11_b = t_1;
        nile_Real_t t_12_a = nile_Real_add(t_11_a, t_10_a);
        nile_Real_t t_12_r = nile_Real_add(t_11_r, t_10_r);
        nile_Real_t t_12_g = nile_Real_add(t_11_g, t_10_g);
        nile_Real_t t_12_b = nile_Real_add(t_11_b, t_10_b);
        nile_Real_t v_c_a = t_12_a;
        nile_Real_t v_c_r = t_12_r;
        nile_Real_t v_c_g = t_12_g;
        nile_Real_t v_c_b = t_12_b;
        nile_Real_t t_13_a = v_a_a;
        nile_Real_t t_13_r = v_a_a;
        nile_Real_t t_13_g = v_a_a;
        nile_Real_t t_13_b = v_a_a;
        nile_Real_t t_14_a = nile_Real_mul(v_b_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_mul(v_b_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_mul(v_b_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_mul(v_b_b, t_13_b);
        nile_Real_t t_15 = 1;
        nile_Real_t t_16_a = v_a_a;
        nile_Real_t t_16_r = v_a_a;
        nile_Real_t t_16_g = v_a_a;
        nile_Real_t t_16_b = v_a_a;
        nile_Real_t t_17_a = nile_Real_div(v_a_a, t_16_a);
        nile_Real_t t_17_r = nile_Real_div(v_a_r, t_16_r);
        nile_Real_t t_17_g = nile_Real_div(v_a_g, t_16_g);
        nile_Real_t t_17_b = nile_Real_div(v_a_b, t_16_b);
        nile_Real_t t_18_a = t_15;
        nile_Real_t t_18_r = t_15;
        nile_Real_t t_18_g = t_15;
        nile_Real_t t_18_b = t_15;
        nile_Real_t t_19_a = nile_Real_sub(t_18_a, t_17_a);
        nile_Real_t t_19_r = nile_Real_sub(t_18_r, t_17_r);
        nile_Real_t t_19_g = nile_Real_sub(t_18_g, t_17_g);
        nile_Real_t t_19_b = nile_Real_sub(t_18_b, t_17_b);
        nile_Real_t t_20_a = nile_Real_div(t_14_a, t_19_a);
        nile_Real_t t_20_r = nile_Real_div(t_14_r, t_19_r);
        nile_Real_t t_20_g = nile_Real_div(t_14_g, t_19_g);
        nile_Real_t t_20_b = nile_Real_div(t_14_b, t_19_b);
        nile_Real_t t_21 = 1;
        nile_Real_t t_22 = nile_Real_sub(t_21, v_b_a);
        nile_Real_t t_23_a = t_22;
        nile_Real_t t_23_r = t_22;
        nile_Real_t t_23_g = t_22;
        nile_Real_t t_23_b = t_22;
        nile_Real_t t_24_a = nile_Real_mul(v_a_a, t_23_a);
        nile_Real_t t_24_r = nile_Real_mul(v_a_r, t_23_r);
        nile_Real_t t_24_g = nile_Real_mul(v_a_g, t_23_g);
        nile_Real_t t_24_b = nile_Real_mul(v_a_b, t_23_b);
        nile_Real_t t_25 = 1;
        nile_Real_t t_26 = nile_Real_sub(t_25, v_a_a);
        nile_Real_t t_27_a = t_26;
        nile_Real_t t_27_r = t_26;
        nile_Real_t t_27_g = t_26;
        nile_Real_t t_27_b = t_26;
        nile_Real_t t_28_a = nile_Real_mul(v_b_a, t_27_a);
        nile_Real_t t_28_r = nile_Real_mul(v_b_r, t_27_r);
        nile_Real_t t_28_g = nile_Real_mul(v_b_g, t_27_g);
        nile_Real_t t_28_b = nile_Real_mul(v_b_b, t_27_b);
        nile_Real_t t_29_a = nile_Real_add(t_24_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_add(t_24_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_add(t_24_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_add(t_24_b, t_28_b);
        nile_Real_t t_30_a = nile_Real_add(t_20_a, t_29_a);
        nile_Real_t t_30_r = nile_Real_add(t_20_r, t_29_r);
        nile_Real_t t_30_g = nile_Real_add(t_20_g, t_29_g);
        nile_Real_t t_30_b = nile_Real_add(t_20_b, t_29_b);
        nile_Real_t t_31 = 1;
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33 = nile_Real_lt(t_30_a, t_32_a);
        nile_Real_t t_34 = t_33 ? t_30_a : t_32_a;
        nile_Real_t t_35 = nile_Real_lt(t_30_r, t_32_r);
        nile_Real_t t_36 = t_35 ? t_30_r : t_32_r;
        nile_Real_t t_37 = nile_Real_lt(t_30_g, t_32_g);
        nile_Real_t t_38 = t_37 ? t_30_g : t_32_g;
        nile_Real_t t_39 = nile_Real_lt(t_30_b, t_32_b);
        nile_Real_t t_40 = t_39 ? t_30_b : t_32_b;
        nile_Real_t t_41_1 = t_34;
        nile_Real_t t_41_2 = t_36;
        nile_Real_t t_41_3 = t_38;
        nile_Real_t t_41_4 = t_40;
        nile_Real_t t_42_a = t_41_1;
        nile_Real_t t_42_r = t_41_2;
        nile_Real_t t_42_g = t_41_3;
        nile_Real_t t_42_b = t_41_4;
        nile_Real_t v_d_a = t_42_a;
        nile_Real_t v_d_r = t_42_r;
        nile_Real_t v_d_g = t_42_g;
        nile_Real_t v_d_b = t_42_b;
        nile_Real_t t_43_a = v_b_a;
        nile_Real_t t_43_r = v_b_a;
        nile_Real_t t_43_g = v_b_a;
        nile_Real_t t_43_b = v_b_a;
        nile_Real_t t_44_a = nile_Real_mul(v_a_a, t_43_a);
        nile_Real_t t_44_r = nile_Real_mul(v_a_r, t_43_r);
        nile_Real_t t_44_g = nile_Real_mul(v_a_g, t_43_g);
        nile_Real_t t_44_b = nile_Real_mul(v_a_b, t_43_b);
        nile_Real_t t_45_a = v_a_a;
        nile_Real_t t_45_r = v_a_a;
        nile_Real_t t_45_g = v_a_a;
        nile_Real_t t_45_b = v_a_a;
        nile_Real_t t_46_a = nile_Real_mul(v_b_a, t_45_a);
        nile_Real_t t_46_r = nile_Real_mul(v_b_r, t_45_r);
        nile_Real_t t_46_g = nile_Real_mul(v_b_g, t_45_g);
        nile_Real_t t_46_b = nile_Real_mul(v_b_b, t_45_b);
        nile_Real_t t_47_a = nile_Real_add(t_44_a, t_46_a);
        nile_Real_t t_47_r = nile_Real_add(t_44_r, t_46_r);
        nile_Real_t t_47_g = nile_Real_add(t_44_g, t_46_g);
        nile_Real_t t_47_b = nile_Real_add(t_44_b, t_46_b);
        nile_Real_t t_48 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_49_a = t_48;
        nile_Real_t t_49_r = t_48;
        nile_Real_t t_49_g = t_48;
        nile_Real_t t_49_b = t_48;
        nile_Real_t t_50_a = nile_Real_geq(t_47_a, t_49_a);
        nile_Real_t t_50_r = nile_Real_geq(t_47_r, t_49_r);
        nile_Real_t t_50_g = nile_Real_geq(t_47_g, t_49_g);
        nile_Real_t t_50_b = nile_Real_geq(t_47_b, t_49_b);
        nile_Real_t t_51_a = t_50_a ? v_c_a : v_d_a;
        nile_Real_t t_51_r = t_50_r ? v_c_r : v_d_r;
        nile_Real_t t_51_g = t_50_g ? v_c_g : v_d_g;
        nile_Real_t t_51_b = t_50_b ? v_c_b : v_d_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_51_a);
        nile_Buffer_append(out, t_51_r);
        nile_Buffer_append(out, t_51_g);
        nile_Buffer_append(out, t_51_b);
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
} gezira_CompositeColorBurn_t;

static nile_Kernel_t *gezira_CompositeColorBurn_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeColorBurn_t *k = (gezira_CompositeColorBurn_t *) k_;
    gezira_CompositeColorBurn_t *clone = (gezira_CompositeColorBurn_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeColorBurn(nile_t *nl) {
    gezira_CompositeColorBurn_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeColorBurn);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeColorBurn_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeColorBurn_t *k = (gezira_CompositeColorBurn_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3_a = v_a_a;
        nile_Real_t t_3_r = v_a_a;
        nile_Real_t t_3_g = v_a_a;
        nile_Real_t t_3_b = v_a_a;
        nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
        nile_Real_t t_5_a = nile_Real_add(t_2_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_add(t_2_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_add(t_2_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_add(t_2_b, t_4_b);
        nile_Real_t t_6 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_sub(t_5_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_sub(t_5_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_sub(t_5_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_sub(t_5_b, t_7_b);
        nile_Real_t t_9_a = v_a_a;
        nile_Real_t t_9_r = v_a_a;
        nile_Real_t t_9_g = v_a_a;
        nile_Real_t t_9_b = v_a_a;
        nile_Real_t t_10_a = nile_Real_mul(t_9_a, t_8_a);
        nile_Real_t t_10_r = nile_Real_mul(t_9_r, t_8_r);
        nile_Real_t t_10_g = nile_Real_mul(t_9_g, t_8_g);
        nile_Real_t t_10_b = nile_Real_mul(t_9_b, t_8_b);
        nile_Real_t t_11_a = nile_Real_div(t_10_a, v_a_a);
        nile_Real_t t_11_r = nile_Real_div(t_10_r, v_a_r);
        nile_Real_t t_11_g = nile_Real_div(t_10_g, v_a_g);
        nile_Real_t t_11_b = nile_Real_div(t_10_b, v_a_b);
        nile_Real_t t_12 = 1;
        nile_Real_t t_13 = nile_Real_sub(t_12, v_b_a);
        nile_Real_t t_14_a = t_13;
        nile_Real_t t_14_r = t_13;
        nile_Real_t t_14_g = t_13;
        nile_Real_t t_14_b = t_13;
        nile_Real_t t_15_a = nile_Real_mul(v_a_a, t_14_a);
        nile_Real_t t_15_r = nile_Real_mul(v_a_r, t_14_r);
        nile_Real_t t_15_g = nile_Real_mul(v_a_g, t_14_g);
        nile_Real_t t_15_b = nile_Real_mul(v_a_b, t_14_b);
        nile_Real_t t_16 = 1;
        nile_Real_t t_17 = nile_Real_sub(t_16, v_a_a);
        nile_Real_t t_18_a = t_17;
        nile_Real_t t_18_r = t_17;
        nile_Real_t t_18_g = t_17;
        nile_Real_t t_18_b = t_17;
        nile_Real_t t_19_a = nile_Real_mul(v_b_a, t_18_a);
        nile_Real_t t_19_r = nile_Real_mul(v_b_r, t_18_r);
        nile_Real_t t_19_g = nile_Real_mul(v_b_g, t_18_g);
        nile_Real_t t_19_b = nile_Real_mul(v_b_b, t_18_b);
        nile_Real_t t_20_a = nile_Real_add(t_15_a, t_19_a);
        nile_Real_t t_20_r = nile_Real_add(t_15_r, t_19_r);
        nile_Real_t t_20_g = nile_Real_add(t_15_g, t_19_g);
        nile_Real_t t_20_b = nile_Real_add(t_15_b, t_19_b);
        nile_Real_t t_21_a = nile_Real_add(t_11_a, t_20_a);
        nile_Real_t t_21_r = nile_Real_add(t_11_r, t_20_r);
        nile_Real_t t_21_g = nile_Real_add(t_11_g, t_20_g);
        nile_Real_t t_21_b = nile_Real_add(t_11_b, t_20_b);
        nile_Real_t v_c_a = t_21_a;
        nile_Real_t v_c_r = t_21_r;
        nile_Real_t v_c_g = t_21_g;
        nile_Real_t v_c_b = t_21_b;
        nile_Real_t t_22_a = v_b_a;
        nile_Real_t t_22_r = v_b_a;
        nile_Real_t t_22_g = v_b_a;
        nile_Real_t t_22_b = v_b_a;
        nile_Real_t t_23_a = nile_Real_mul(v_a_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_mul(v_a_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_mul(v_a_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_mul(v_a_b, t_22_b);
        nile_Real_t t_24_a = v_a_a;
        nile_Real_t t_24_r = v_a_a;
        nile_Real_t t_24_g = v_a_a;
        nile_Real_t t_24_b = v_a_a;
        nile_Real_t t_25_a = nile_Real_mul(v_b_a, t_24_a);
        nile_Real_t t_25_r = nile_Real_mul(v_b_r, t_24_r);
        nile_Real_t t_25_g = nile_Real_mul(v_b_g, t_24_g);
        nile_Real_t t_25_b = nile_Real_mul(v_b_b, t_24_b);
        nile_Real_t t_26_a = nile_Real_add(t_23_a, t_25_a);
        nile_Real_t t_26_r = nile_Real_add(t_23_r, t_25_r);
        nile_Real_t t_26_g = nile_Real_add(t_23_g, t_25_g);
        nile_Real_t t_26_b = nile_Real_add(t_23_b, t_25_b);
        nile_Real_t t_27 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_28_a = t_27;
        nile_Real_t t_28_r = t_27;
        nile_Real_t t_28_g = t_27;
        nile_Real_t t_28_b = t_27;
        nile_Real_t t_29_a = nile_Real_leq(t_26_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_leq(t_26_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_leq(t_26_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_leq(t_26_b, t_28_b);
        nile_Real_t t_30 = 1;
        nile_Real_t t_31 = nile_Real_sub(t_30, v_b_a);
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33_a = nile_Real_mul(v_a_a, t_32_a);
        nile_Real_t t_33_r = nile_Real_mul(v_a_r, t_32_r);
        nile_Real_t t_33_g = nile_Real_mul(v_a_g, t_32_g);
        nile_Real_t t_33_b = nile_Real_mul(v_a_b, t_32_b);
        nile_Real_t t_34 = 1;
        nile_Real_t t_35 = nile_Real_sub(t_34, v_a_a);
        nile_Real_t t_36_a = t_35;
        nile_Real_t t_36_r = t_35;
        nile_Real_t t_36_g = t_35;
        nile_Real_t t_36_b = t_35;
        nile_Real_t t_37_a = nile_Real_mul(v_b_a, t_36_a);
        nile_Real_t t_37_r = nile_Real_mul(v_b_r, t_36_r);
        nile_Real_t t_37_g = nile_Real_mul(v_b_g, t_36_g);
        nile_Real_t t_37_b = nile_Real_mul(v_b_b, t_36_b);
        nile_Real_t t_38_a = nile_Real_add(t_33_a, t_37_a);
        nile_Real_t t_38_r = nile_Real_add(t_33_r, t_37_r);
        nile_Real_t t_38_g = nile_Real_add(t_33_g, t_37_g);
        nile_Real_t t_38_b = nile_Real_add(t_33_b, t_37_b);
        nile_Real_t t_39_a = t_29_a ? t_38_a : v_c_a;
        nile_Real_t t_39_r = t_29_r ? t_38_r : v_c_r;
        nile_Real_t t_39_g = t_29_g ? t_38_g : v_c_g;
        nile_Real_t t_39_b = t_29_b ? t_38_b : v_c_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_39_a);
        nile_Buffer_append(out, t_39_r);
        nile_Buffer_append(out, t_39_g);
        nile_Buffer_append(out, t_39_b);
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
} gezira_CompositeHardLight_t;

static nile_Kernel_t *gezira_CompositeHardLight_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeHardLight_t *k = (gezira_CompositeHardLight_t *) k_;
    gezira_CompositeHardLight_t *clone = (gezira_CompositeHardLight_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeHardLight(nile_t *nl) {
    gezira_CompositeHardLight_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeHardLight);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeHardLight_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeHardLight_t *k = (gezira_CompositeHardLight_t *) k_;
    
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
        nile_Real_t t_1 = 2;
        nile_Real_t t_2_a = t_1;
        nile_Real_t t_2_r = t_1;
        nile_Real_t t_2_g = t_1;
        nile_Real_t t_2_b = t_1;
        nile_Real_t t_3_a = nile_Real_mul(t_2_a, v_a_a);
        nile_Real_t t_3_r = nile_Real_mul(t_2_r, v_a_r);
        nile_Real_t t_3_g = nile_Real_mul(t_2_g, v_a_g);
        nile_Real_t t_3_b = nile_Real_mul(t_2_b, v_a_b);
        nile_Real_t t_4_a = nile_Real_mul(t_3_a, v_b_a);
        nile_Real_t t_4_r = nile_Real_mul(t_3_r, v_b_r);
        nile_Real_t t_4_g = nile_Real_mul(t_3_g, v_b_g);
        nile_Real_t t_4_b = nile_Real_mul(t_3_b, v_b_b);
        nile_Real_t t_5 = 1;
        nile_Real_t t_6 = nile_Real_sub(t_5, v_b_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(v_a_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_mul(v_a_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_mul(v_a_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_mul(v_a_b, t_7_b);
        nile_Real_t t_9 = 1;
        nile_Real_t t_10 = nile_Real_sub(t_9, v_a_a);
        nile_Real_t t_11_a = t_10;
        nile_Real_t t_11_r = t_10;
        nile_Real_t t_11_g = t_10;
        nile_Real_t t_11_b = t_10;
        nile_Real_t t_12_a = nile_Real_mul(v_b_a, t_11_a);
        nile_Real_t t_12_r = nile_Real_mul(v_b_r, t_11_r);
        nile_Real_t t_12_g = nile_Real_mul(v_b_g, t_11_g);
        nile_Real_t t_12_b = nile_Real_mul(v_b_b, t_11_b);
        nile_Real_t t_13_a = nile_Real_add(t_8_a, t_12_a);
        nile_Real_t t_13_r = nile_Real_add(t_8_r, t_12_r);
        nile_Real_t t_13_g = nile_Real_add(t_8_g, t_12_g);
        nile_Real_t t_13_b = nile_Real_add(t_8_b, t_12_b);
        nile_Real_t t_14_a = nile_Real_add(t_4_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_add(t_4_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_add(t_4_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_add(t_4_b, t_13_b);
        nile_Real_t v_c_a = t_14_a;
        nile_Real_t v_c_r = t_14_r;
        nile_Real_t v_c_g = t_14_g;
        nile_Real_t v_c_b = t_14_b;
        nile_Real_t t_15 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_16 = 2;
        nile_Real_t t_17_a = v_b_a;
        nile_Real_t t_17_r = v_b_a;
        nile_Real_t t_17_g = v_b_a;
        nile_Real_t t_17_b = v_b_a;
        nile_Real_t t_18_a = nile_Real_sub(t_17_a, v_b_a);
        nile_Real_t t_18_r = nile_Real_sub(t_17_r, v_b_r);
        nile_Real_t t_18_g = nile_Real_sub(t_17_g, v_b_g);
        nile_Real_t t_18_b = nile_Real_sub(t_17_b, v_b_b);
        nile_Real_t t_19_a = t_16;
        nile_Real_t t_19_r = t_16;
        nile_Real_t t_19_g = t_16;
        nile_Real_t t_19_b = t_16;
        nile_Real_t t_20_a = nile_Real_mul(t_19_a, t_18_a);
        nile_Real_t t_20_r = nile_Real_mul(t_19_r, t_18_r);
        nile_Real_t t_20_g = nile_Real_mul(t_19_g, t_18_g);
        nile_Real_t t_20_b = nile_Real_mul(t_19_b, t_18_b);
        nile_Real_t t_21_a = v_a_a;
        nile_Real_t t_21_r = v_a_a;
        nile_Real_t t_21_g = v_a_a;
        nile_Real_t t_21_b = v_a_a;
        nile_Real_t t_22_a = nile_Real_sub(t_21_a, v_a_a);
        nile_Real_t t_22_r = nile_Real_sub(t_21_r, v_a_r);
        nile_Real_t t_22_g = nile_Real_sub(t_21_g, v_a_g);
        nile_Real_t t_22_b = nile_Real_sub(t_21_b, v_a_b);
        nile_Real_t t_23_a = nile_Real_mul(t_20_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_mul(t_20_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_mul(t_20_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_mul(t_20_b, t_22_b);
        nile_Real_t t_24_a = t_15;
        nile_Real_t t_24_r = t_15;
        nile_Real_t t_24_g = t_15;
        nile_Real_t t_24_b = t_15;
        nile_Real_t t_25_a = nile_Real_sub(t_24_a, t_23_a);
        nile_Real_t t_25_r = nile_Real_sub(t_24_r, t_23_r);
        nile_Real_t t_25_g = nile_Real_sub(t_24_g, t_23_g);
        nile_Real_t t_25_b = nile_Real_sub(t_24_b, t_23_b);
        nile_Real_t t_26 = 1;
        nile_Real_t t_27 = nile_Real_sub(t_26, v_b_a);
        nile_Real_t t_28_a = t_27;
        nile_Real_t t_28_r = t_27;
        nile_Real_t t_28_g = t_27;
        nile_Real_t t_28_b = t_27;
        nile_Real_t t_29_a = nile_Real_mul(v_a_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_mul(v_a_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_mul(v_a_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_mul(v_a_b, t_28_b);
        nile_Real_t t_30 = 1;
        nile_Real_t t_31 = nile_Real_sub(t_30, v_a_a);
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33_a = nile_Real_mul(v_b_a, t_32_a);
        nile_Real_t t_33_r = nile_Real_mul(v_b_r, t_32_r);
        nile_Real_t t_33_g = nile_Real_mul(v_b_g, t_32_g);
        nile_Real_t t_33_b = nile_Real_mul(v_b_b, t_32_b);
        nile_Real_t t_34_a = nile_Real_add(t_29_a, t_33_a);
        nile_Real_t t_34_r = nile_Real_add(t_29_r, t_33_r);
        nile_Real_t t_34_g = nile_Real_add(t_29_g, t_33_g);
        nile_Real_t t_34_b = nile_Real_add(t_29_b, t_33_b);
        nile_Real_t t_35_a = nile_Real_add(t_25_a, t_34_a);
        nile_Real_t t_35_r = nile_Real_add(t_25_r, t_34_r);
        nile_Real_t t_35_g = nile_Real_add(t_25_g, t_34_g);
        nile_Real_t t_35_b = nile_Real_add(t_25_b, t_34_b);
        nile_Real_t v_d_a = t_35_a;
        nile_Real_t v_d_r = t_35_r;
        nile_Real_t v_d_g = t_35_g;
        nile_Real_t v_d_b = t_35_b;
        nile_Real_t t_36 = 2;
        nile_Real_t t_37_a = t_36;
        nile_Real_t t_37_r = t_36;
        nile_Real_t t_37_g = t_36;
        nile_Real_t t_37_b = t_36;
        nile_Real_t t_38_a = nile_Real_mul(t_37_a, v_a_a);
        nile_Real_t t_38_r = nile_Real_mul(t_37_r, v_a_r);
        nile_Real_t t_38_g = nile_Real_mul(t_37_g, v_a_g);
        nile_Real_t t_38_b = nile_Real_mul(t_37_b, v_a_b);
        nile_Real_t t_39_a = v_a_a;
        nile_Real_t t_39_r = v_a_a;
        nile_Real_t t_39_g = v_a_a;
        nile_Real_t t_39_b = v_a_a;
        nile_Real_t t_40_a = nile_Real_lt(t_38_a, t_39_a);
        nile_Real_t t_40_r = nile_Real_lt(t_38_r, t_39_r);
        nile_Real_t t_40_g = nile_Real_lt(t_38_g, t_39_g);
        nile_Real_t t_40_b = nile_Real_lt(t_38_b, t_39_b);
        nile_Real_t t_41_a = t_40_a ? v_c_a : v_d_a;
        nile_Real_t t_41_r = t_40_r ? v_c_r : v_d_r;
        nile_Real_t t_41_g = t_40_g ? v_c_g : v_d_g;
        nile_Real_t t_41_b = t_40_b ? v_c_b : v_d_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_41_a);
        nile_Buffer_append(out, t_41_r);
        nile_Buffer_append(out, t_41_g);
        nile_Buffer_append(out, t_41_b);
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
} gezira_CompositeSoftLight_t;

static nile_Kernel_t *gezira_CompositeSoftLight_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSoftLight_t *k = (gezira_CompositeSoftLight_t *) k_;
    gezira_CompositeSoftLight_t *clone = (gezira_CompositeSoftLight_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSoftLight(nile_t *nl) {
    gezira_CompositeSoftLight_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSoftLight);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSoftLight_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSoftLight_t *k = (gezira_CompositeSoftLight_t *) k_;
    
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
        nile_Real_t t_2_a = v_b_a;
        nile_Real_t t_2_r = v_b_a;
        nile_Real_t t_2_g = v_b_a;
        nile_Real_t t_2_b = v_b_a;
        nile_Real_t t_3_a = nile_Real_div(v_b_a, t_2_a);
        nile_Real_t t_3_r = nile_Real_div(v_b_r, t_2_r);
        nile_Real_t t_3_g = nile_Real_div(v_b_g, t_2_g);
        nile_Real_t t_3_b = nile_Real_div(v_b_b, t_2_b);
        nile_Real_t t_4_a = t_1;
        nile_Real_t t_4_r = t_1;
        nile_Real_t t_4_g = t_1;
        nile_Real_t t_4_b = t_1;
        nile_Real_t t_5_a = nile_Real_sub(t_4_a, t_3_a);
        nile_Real_t t_5_r = nile_Real_sub(t_4_r, t_3_r);
        nile_Real_t t_5_g = nile_Real_sub(t_4_g, t_3_g);
        nile_Real_t t_5_b = nile_Real_sub(t_4_b, t_3_b);
        nile_Real_t t_6 = 2;
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(t_7_a, v_a_a);
        nile_Real_t t_8_r = nile_Real_mul(t_7_r, v_a_r);
        nile_Real_t t_8_g = nile_Real_mul(t_7_g, v_a_g);
        nile_Real_t t_8_b = nile_Real_mul(t_7_b, v_a_b);
        nile_Real_t t_9_a = v_a_a;
        nile_Real_t t_9_r = v_a_a;
        nile_Real_t t_9_g = v_a_a;
        nile_Real_t t_9_b = v_a_a;
        nile_Real_t t_10_a = nile_Real_sub(t_8_a, t_9_a);
        nile_Real_t t_10_r = nile_Real_sub(t_8_r, t_9_r);
        nile_Real_t t_10_g = nile_Real_sub(t_8_g, t_9_g);
        nile_Real_t t_10_b = nile_Real_sub(t_8_b, t_9_b);
        nile_Real_t t_11_a = nile_Real_mul(t_5_a, t_10_a);
        nile_Real_t t_11_r = nile_Real_mul(t_5_r, t_10_r);
        nile_Real_t t_11_g = nile_Real_mul(t_5_g, t_10_g);
        nile_Real_t t_11_b = nile_Real_mul(t_5_b, t_10_b);
        nile_Real_t v_c_a = t_11_a;
        nile_Real_t v_c_r = t_11_r;
        nile_Real_t v_c_g = t_11_g;
        nile_Real_t v_c_b = t_11_b;
        nile_Real_t t_12_a = v_a_a;
        nile_Real_t t_12_r = v_a_a;
        nile_Real_t t_12_g = v_a_a;
        nile_Real_t t_12_b = v_a_a;
        nile_Real_t t_13_a = nile_Real_sub(t_12_a, v_c_a);
        nile_Real_t t_13_r = nile_Real_sub(t_12_r, v_c_r);
        nile_Real_t t_13_g = nile_Real_sub(t_12_g, v_c_g);
        nile_Real_t t_13_b = nile_Real_sub(t_12_b, v_c_b);
        nile_Real_t t_14_a = nile_Real_mul(v_b_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_mul(v_b_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_mul(v_b_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_mul(v_b_b, t_13_b);
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = 1;
        nile_Real_t t_20 = nile_Real_sub(t_19, v_a_a);
        nile_Real_t t_21_a = t_20;
        nile_Real_t t_21_r = t_20;
        nile_Real_t t_21_g = t_20;
        nile_Real_t t_21_b = t_20;
        nile_Real_t t_22_a = nile_Real_mul(v_b_a, t_21_a);
        nile_Real_t t_22_r = nile_Real_mul(v_b_r, t_21_r);
        nile_Real_t t_22_g = nile_Real_mul(v_b_g, t_21_g);
        nile_Real_t t_22_b = nile_Real_mul(v_b_b, t_21_b);
        nile_Real_t t_23_a = nile_Real_add(t_18_a, t_22_a);
        nile_Real_t t_23_r = nile_Real_add(t_18_r, t_22_r);
        nile_Real_t t_23_g = nile_Real_add(t_18_g, t_22_g);
        nile_Real_t t_23_b = nile_Real_add(t_18_b, t_22_b);
        nile_Real_t t_24_a = nile_Real_add(t_14_a, t_23_a);
        nile_Real_t t_24_r = nile_Real_add(t_14_r, t_23_r);
        nile_Real_t t_24_g = nile_Real_add(t_14_g, t_23_g);
        nile_Real_t t_24_b = nile_Real_add(t_14_b, t_23_b);
        nile_Real_t v_d_a = t_24_a;
        nile_Real_t v_d_r = t_24_r;
        nile_Real_t v_d_g = t_24_g;
        nile_Real_t v_d_b = t_24_b;
        nile_Real_t t_25 = 3;
        nile_Real_t t_26 = 8;
        nile_Real_t t_27_a = t_26;
        nile_Real_t t_27_r = t_26;
        nile_Real_t t_27_g = t_26;
        nile_Real_t t_27_b = t_26;
        nile_Real_t t_28_a = nile_Real_mul(t_27_a, v_b_a);
        nile_Real_t t_28_r = nile_Real_mul(t_27_r, v_b_r);
        nile_Real_t t_28_g = nile_Real_mul(t_27_g, v_b_g);
        nile_Real_t t_28_b = nile_Real_mul(t_27_b, v_b_b);
        nile_Real_t t_29_a = v_b_a;
        nile_Real_t t_29_r = v_b_a;
        nile_Real_t t_29_g = v_b_a;
        nile_Real_t t_29_b = v_b_a;
        nile_Real_t t_30_a = nile_Real_div(t_28_a, t_29_a);
        nile_Real_t t_30_r = nile_Real_div(t_28_r, t_29_r);
        nile_Real_t t_30_g = nile_Real_div(t_28_g, t_29_g);
        nile_Real_t t_30_b = nile_Real_div(t_28_b, t_29_b);
        nile_Real_t t_31_a = t_25;
        nile_Real_t t_31_r = t_25;
        nile_Real_t t_31_g = t_25;
        nile_Real_t t_31_b = t_25;
        nile_Real_t t_32_a = nile_Real_sub(t_31_a, t_30_a);
        nile_Real_t t_32_r = nile_Real_sub(t_31_r, t_30_r);
        nile_Real_t t_32_g = nile_Real_sub(t_31_g, t_30_g);
        nile_Real_t t_32_b = nile_Real_sub(t_31_b, t_30_b);
        nile_Real_t t_33_a = nile_Real_mul(v_c_a, t_32_a);
        nile_Real_t t_33_r = nile_Real_mul(v_c_r, t_32_r);
        nile_Real_t t_33_g = nile_Real_mul(v_c_g, t_32_g);
        nile_Real_t t_33_b = nile_Real_mul(v_c_b, t_32_b);
        nile_Real_t t_34_a = v_a_a;
        nile_Real_t t_34_r = v_a_a;
        nile_Real_t t_34_g = v_a_a;
        nile_Real_t t_34_b = v_a_a;
        nile_Real_t t_35_a = nile_Real_sub(t_34_a, t_33_a);
        nile_Real_t t_35_r = nile_Real_sub(t_34_r, t_33_r);
        nile_Real_t t_35_g = nile_Real_sub(t_34_g, t_33_g);
        nile_Real_t t_35_b = nile_Real_sub(t_34_b, t_33_b);
        nile_Real_t t_36_a = nile_Real_mul(v_b_a, t_35_a);
        nile_Real_t t_36_r = nile_Real_mul(v_b_r, t_35_r);
        nile_Real_t t_36_g = nile_Real_mul(v_b_g, t_35_g);
        nile_Real_t t_36_b = nile_Real_mul(v_b_b, t_35_b);
        nile_Real_t t_37 = 1;
        nile_Real_t t_38 = nile_Real_sub(t_37, v_b_a);
        nile_Real_t t_39_a = t_38;
        nile_Real_t t_39_r = t_38;
        nile_Real_t t_39_g = t_38;
        nile_Real_t t_39_b = t_38;
        nile_Real_t t_40_a = nile_Real_mul(v_a_a, t_39_a);
        nile_Real_t t_40_r = nile_Real_mul(v_a_r, t_39_r);
        nile_Real_t t_40_g = nile_Real_mul(v_a_g, t_39_g);
        nile_Real_t t_40_b = nile_Real_mul(v_a_b, t_39_b);
        nile_Real_t t_41 = 1;
        nile_Real_t t_42 = nile_Real_sub(t_41, v_a_a);
        nile_Real_t t_43_a = t_42;
        nile_Real_t t_43_r = t_42;
        nile_Real_t t_43_g = t_42;
        nile_Real_t t_43_b = t_42;
        nile_Real_t t_44_a = nile_Real_mul(v_b_a, t_43_a);
        nile_Real_t t_44_r = nile_Real_mul(v_b_r, t_43_r);
        nile_Real_t t_44_g = nile_Real_mul(v_b_g, t_43_g);
        nile_Real_t t_44_b = nile_Real_mul(v_b_b, t_43_b);
        nile_Real_t t_45_a = nile_Real_add(t_40_a, t_44_a);
        nile_Real_t t_45_r = nile_Real_add(t_40_r, t_44_r);
        nile_Real_t t_45_g = nile_Real_add(t_40_g, t_44_g);
        nile_Real_t t_45_b = nile_Real_add(t_40_b, t_44_b);
        nile_Real_t t_46_a = nile_Real_add(t_36_a, t_45_a);
        nile_Real_t t_46_r = nile_Real_add(t_36_r, t_45_r);
        nile_Real_t t_46_g = nile_Real_add(t_36_g, t_45_g);
        nile_Real_t t_46_b = nile_Real_add(t_36_b, t_45_b);
        nile_Real_t v_e_a = t_46_a;
        nile_Real_t v_e_r = t_46_r;
        nile_Real_t v_e_g = t_46_g;
        nile_Real_t v_e_b = t_46_b;
        nile_Real_t t_47_a = v_a_a;
        nile_Real_t t_47_r = v_a_a;
        nile_Real_t t_47_g = v_a_a;
        nile_Real_t t_47_b = v_a_a;
        nile_Real_t t_48_a = nile_Real_mul(v_b_a, t_47_a);
        nile_Real_t t_48_r = nile_Real_mul(v_b_r, t_47_r);
        nile_Real_t t_48_g = nile_Real_mul(v_b_g, t_47_g);
        nile_Real_t t_48_b = nile_Real_mul(v_b_b, t_47_b);
        nile_Real_t t_49_a = v_b_a;
        nile_Real_t t_49_r = v_b_a;
        nile_Real_t t_49_g = v_b_a;
        nile_Real_t t_49_b = v_b_a;
        nile_Real_t t_50_a = nile_Real_div(v_b_a, t_49_a);
        nile_Real_t t_50_r = nile_Real_div(v_b_r, t_49_r);
        nile_Real_t t_50_g = nile_Real_div(v_b_g, t_49_g);
        nile_Real_t t_50_b = nile_Real_div(v_b_b, t_49_b);
        nile_Real_t t_51_a = nile_Real_sqr(t_50_a);
        nile_Real_t t_51_r = nile_Real_sqr(t_50_r);
        nile_Real_t t_51_g = nile_Real_sqr(t_50_g);
        nile_Real_t t_51_b = nile_Real_sqr(t_50_b);
        nile_Real_t t_52_a = v_b_a;
        nile_Real_t t_52_r = v_b_a;
        nile_Real_t t_52_g = v_b_a;
        nile_Real_t t_52_b = v_b_a;
        nile_Real_t t_53_a = nile_Real_mul(t_51_a, t_52_a);
        nile_Real_t t_53_r = nile_Real_mul(t_51_r, t_52_r);
        nile_Real_t t_53_g = nile_Real_mul(t_51_g, t_52_g);
        nile_Real_t t_53_b = nile_Real_mul(t_51_b, t_52_b);
        nile_Real_t t_54_a = nile_Real_sub(t_53_a, v_b_a);
        nile_Real_t t_54_r = nile_Real_sub(t_53_r, v_b_r);
        nile_Real_t t_54_g = nile_Real_sub(t_53_g, v_b_g);
        nile_Real_t t_54_b = nile_Real_sub(t_53_b, v_b_b);
        nile_Real_t t_55 = 2;
        nile_Real_t t_56_a = t_55;
        nile_Real_t t_56_r = t_55;
        nile_Real_t t_56_g = t_55;
        nile_Real_t t_56_b = t_55;
        nile_Real_t t_57_a = nile_Real_mul(t_56_a, v_a_a);
        nile_Real_t t_57_r = nile_Real_mul(t_56_r, v_a_r);
        nile_Real_t t_57_g = nile_Real_mul(t_56_g, v_a_g);
        nile_Real_t t_57_b = nile_Real_mul(t_56_b, v_a_b);
        nile_Real_t t_58_a = v_a_a;
        nile_Real_t t_58_r = v_a_a;
        nile_Real_t t_58_g = v_a_a;
        nile_Real_t t_58_b = v_a_a;
        nile_Real_t t_59_a = nile_Real_sub(t_57_a, t_58_a);
        nile_Real_t t_59_r = nile_Real_sub(t_57_r, t_58_r);
        nile_Real_t t_59_g = nile_Real_sub(t_57_g, t_58_g);
        nile_Real_t t_59_b = nile_Real_sub(t_57_b, t_58_b);
        nile_Real_t t_60_a = nile_Real_mul(t_54_a, t_59_a);
        nile_Real_t t_60_r = nile_Real_mul(t_54_r, t_59_r);
        nile_Real_t t_60_g = nile_Real_mul(t_54_g, t_59_g);
        nile_Real_t t_60_b = nile_Real_mul(t_54_b, t_59_b);
        nile_Real_t t_61_a = nile_Real_add(t_48_a, t_60_a);
        nile_Real_t t_61_r = nile_Real_add(t_48_r, t_60_r);
        nile_Real_t t_61_g = nile_Real_add(t_48_g, t_60_g);
        nile_Real_t t_61_b = nile_Real_add(t_48_b, t_60_b);
        nile_Real_t t_62 = 1;
        nile_Real_t t_63 = nile_Real_sub(t_62, v_b_a);
        nile_Real_t t_64_a = t_63;
        nile_Real_t t_64_r = t_63;
        nile_Real_t t_64_g = t_63;
        nile_Real_t t_64_b = t_63;
        nile_Real_t t_65_a = nile_Real_mul(v_a_a, t_64_a);
        nile_Real_t t_65_r = nile_Real_mul(v_a_r, t_64_r);
        nile_Real_t t_65_g = nile_Real_mul(v_a_g, t_64_g);
        nile_Real_t t_65_b = nile_Real_mul(v_a_b, t_64_b);
        nile_Real_t t_66 = 1;
        nile_Real_t t_67 = nile_Real_sub(t_66, v_a_a);
        nile_Real_t t_68_a = t_67;
        nile_Real_t t_68_r = t_67;
        nile_Real_t t_68_g = t_67;
        nile_Real_t t_68_b = t_67;
        nile_Real_t t_69_a = nile_Real_mul(v_b_a, t_68_a);
        nile_Real_t t_69_r = nile_Real_mul(v_b_r, t_68_r);
        nile_Real_t t_69_g = nile_Real_mul(v_b_g, t_68_g);
        nile_Real_t t_69_b = nile_Real_mul(v_b_b, t_68_b);
        nile_Real_t t_70_a = nile_Real_add(t_65_a, t_69_a);
        nile_Real_t t_70_r = nile_Real_add(t_65_r, t_69_r);
        nile_Real_t t_70_g = nile_Real_add(t_65_g, t_69_g);
        nile_Real_t t_70_b = nile_Real_add(t_65_b, t_69_b);
        nile_Real_t t_71_a = nile_Real_add(t_61_a, t_70_a);
        nile_Real_t t_71_r = nile_Real_add(t_61_r, t_70_r);
        nile_Real_t t_71_g = nile_Real_add(t_61_g, t_70_g);
        nile_Real_t t_71_b = nile_Real_add(t_61_b, t_70_b);
        nile_Real_t v_f_a = t_71_a;
        nile_Real_t v_f_r = t_71_r;
        nile_Real_t v_f_g = t_71_g;
        nile_Real_t v_f_b = t_71_b;
        nile_Real_t t_72 = 2;
        nile_Real_t t_73_a = t_72;
        nile_Real_t t_73_r = t_72;
        nile_Real_t t_73_g = t_72;
        nile_Real_t t_73_b = t_72;
        nile_Real_t t_74_a = nile_Real_mul(t_73_a, v_a_a);
        nile_Real_t t_74_r = nile_Real_mul(t_73_r, v_a_r);
        nile_Real_t t_74_g = nile_Real_mul(t_73_g, v_a_g);
        nile_Real_t t_74_b = nile_Real_mul(t_73_b, v_a_b);
        nile_Real_t t_75_a = v_a_a;
        nile_Real_t t_75_r = v_a_a;
        nile_Real_t t_75_g = v_a_a;
        nile_Real_t t_75_b = v_a_a;
        nile_Real_t t_76_a = nile_Real_lt(t_74_a, t_75_a);
        nile_Real_t t_76_r = nile_Real_lt(t_74_r, t_75_r);
        nile_Real_t t_76_g = nile_Real_lt(t_74_g, t_75_g);
        nile_Real_t t_76_b = nile_Real_lt(t_74_b, t_75_b);
        nile_Real_t t_77 = 8;
        nile_Real_t t_78_a = t_77;
        nile_Real_t t_78_r = t_77;
        nile_Real_t t_78_g = t_77;
        nile_Real_t t_78_b = t_77;
        nile_Real_t t_79_a = nile_Real_mul(v_b_a, t_78_a);
        nile_Real_t t_79_r = nile_Real_mul(v_b_r, t_78_r);
        nile_Real_t t_79_g = nile_Real_mul(v_b_g, t_78_g);
        nile_Real_t t_79_b = nile_Real_mul(v_b_b, t_78_b);
        nile_Real_t t_80_a = v_b_a;
        nile_Real_t t_80_r = v_b_a;
        nile_Real_t t_80_g = v_b_a;
        nile_Real_t t_80_b = v_b_a;
        nile_Real_t t_81_a = nile_Real_leq(t_79_a, t_80_a);
        nile_Real_t t_81_r = nile_Real_leq(t_79_r, t_80_r);
        nile_Real_t t_81_g = nile_Real_leq(t_79_g, t_80_g);
        nile_Real_t t_81_b = nile_Real_leq(t_79_b, t_80_b);
        nile_Real_t t_82_a = t_81_a ? v_e_a : v_f_a;
        nile_Real_t t_82_r = t_81_r ? v_e_r : v_f_r;
        nile_Real_t t_82_g = t_81_g ? v_e_g : v_f_g;
        nile_Real_t t_82_b = t_81_b ? v_e_b : v_f_b;
        nile_Real_t t_83_a = t_76_a ? v_d_a : t_82_a;
        nile_Real_t t_83_r = t_76_r ? v_d_r : t_82_r;
        nile_Real_t t_83_g = t_76_g ? v_d_g : t_82_g;
        nile_Real_t t_83_b = t_76_b ? v_d_b : t_82_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_83_a);
        nile_Buffer_append(out, t_83_r);
        nile_Buffer_append(out, t_83_g);
        nile_Buffer_append(out, t_83_b);
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
} gezira_CompositeDifference_t;

static nile_Kernel_t *gezira_CompositeDifference_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeDifference_t *k = (gezira_CompositeDifference_t *) k_;
    gezira_CompositeDifference_t *clone = (gezira_CompositeDifference_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeDifference(nile_t *nl) {
    gezira_CompositeDifference_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeDifference);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeDifference_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeDifference_t *k = (gezira_CompositeDifference_t *) k_;
    
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
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = 2;
        nile_Real_t t_3_a = v_b_a;
        nile_Real_t t_3_r = v_b_a;
        nile_Real_t t_3_g = v_b_a;
        nile_Real_t t_3_b = v_b_a;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        nile_Real_t t_5_a = v_a_a;
        nile_Real_t t_5_r = v_a_a;
        nile_Real_t t_5_g = v_a_a;
        nile_Real_t t_5_b = v_a_a;
        nile_Real_t t_6_a = nile_Real_mul(v_b_a, t_5_a);
        nile_Real_t t_6_r = nile_Real_mul(v_b_r, t_5_r);
        nile_Real_t t_6_g = nile_Real_mul(v_b_g, t_5_g);
        nile_Real_t t_6_b = nile_Real_mul(v_b_b, t_5_b);
        nile_Real_t t_7 = nile_Real_lt(t_4_a, t_6_a);
        nile_Real_t t_8 = t_7 ? t_4_a : t_6_a;
        nile_Real_t t_9 = nile_Real_lt(t_4_r, t_6_r);
        nile_Real_t t_10 = t_9 ? t_4_r : t_6_r;
        nile_Real_t t_11 = nile_Real_lt(t_4_g, t_6_g);
        nile_Real_t t_12 = t_11 ? t_4_g : t_6_g;
        nile_Real_t t_13 = nile_Real_lt(t_4_b, t_6_b);
        nile_Real_t t_14 = t_13 ? t_4_b : t_6_b;
        nile_Real_t t_15_1 = t_8;
        nile_Real_t t_15_2 = t_10;
        nile_Real_t t_15_3 = t_12;
        nile_Real_t t_15_4 = t_14;
        nile_Real_t t_16_a = t_15_1;
        nile_Real_t t_16_r = t_15_2;
        nile_Real_t t_16_g = t_15_3;
        nile_Real_t t_16_b = t_15_4;
        nile_Real_t t_17_a = t_2;
        nile_Real_t t_17_r = t_2;
        nile_Real_t t_17_g = t_2;
        nile_Real_t t_17_b = t_2;
        nile_Real_t t_18_a = nile_Real_mul(t_17_a, t_16_a);
        nile_Real_t t_18_r = nile_Real_mul(t_17_r, t_16_r);
        nile_Real_t t_18_g = nile_Real_mul(t_17_g, t_16_g);
        nile_Real_t t_18_b = nile_Real_mul(t_17_b, t_16_b);
        nile_Real_t t_19_a = nile_Real_sub(t_1_a, t_18_a);
        nile_Real_t t_19_r = nile_Real_sub(t_1_r, t_18_r);
        nile_Real_t t_19_g = nile_Real_sub(t_1_g, t_18_g);
        nile_Real_t t_19_b = nile_Real_sub(t_1_b, t_18_b);
        nile_Real_t v_c_a = t_19_a;
        nile_Real_t v_c_r = t_19_r;
        nile_Real_t v_c_g = t_19_g;
        nile_Real_t v_c_b = t_19_b;
        nile_Real_t t_21 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_22 = nile_Real_add(v_c_a, t_21);
        nile_Real_t t_20_1 = t_22;
        nile_Real_t t_20_2 = v_c_r;
        nile_Real_t t_20_3 = v_c_g;
        nile_Real_t t_20_4 = v_c_b;
        nile_Real_t t_23_a = t_20_1;
        nile_Real_t t_23_r = t_20_2;
        nile_Real_t t_23_g = t_20_3;
        nile_Real_t t_23_b = t_20_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_23_a);
        nile_Buffer_append(out, t_23_r);
        nile_Buffer_append(out, t_23_g);
        nile_Buffer_append(out, t_23_b);
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
} gezira_CompositeExclusion_t;

static nile_Kernel_t *gezira_CompositeExclusion_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeExclusion_t *k = (gezira_CompositeExclusion_t *) k_;
    gezira_CompositeExclusion_t *clone = (gezira_CompositeExclusion_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeExclusion(nile_t *nl) {
    gezira_CompositeExclusion_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeExclusion);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeExclusion_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeExclusion_t *k = (gezira_CompositeExclusion_t *) k_;
    
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
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3_a = v_a_a;
        nile_Real_t t_3_r = v_a_a;
        nile_Real_t t_3_g = v_a_a;
        nile_Real_t t_3_b = v_a_a;
        nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
        nile_Real_t t_5_a = nile_Real_add(t_2_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_add(t_2_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_add(t_2_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_add(t_2_b, t_4_b);
        nile_Real_t t_6 = 2;
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(t_7_a, v_a_a);
        nile_Real_t t_8_r = nile_Real_mul(t_7_r, v_a_r);
        nile_Real_t t_8_g = nile_Real_mul(t_7_g, v_a_g);
        nile_Real_t t_8_b = nile_Real_mul(t_7_b, v_a_b);
        nile_Real_t t_9_a = nile_Real_mul(t_8_a, v_b_a);
        nile_Real_t t_9_r = nile_Real_mul(t_8_r, v_b_r);
        nile_Real_t t_9_g = nile_Real_mul(t_8_g, v_b_g);
        nile_Real_t t_9_b = nile_Real_mul(t_8_b, v_b_b);
        nile_Real_t t_10_a = nile_Real_sub(t_5_a, t_9_a);
        nile_Real_t t_10_r = nile_Real_sub(t_5_r, t_9_r);
        nile_Real_t t_10_g = nile_Real_sub(t_5_g, t_9_g);
        nile_Real_t t_10_b = nile_Real_sub(t_5_b, t_9_b);
        nile_Real_t t_11 = 1;
        nile_Real_t t_12 = nile_Real_sub(t_11, v_b_a);
        nile_Real_t t_13_a = t_12;
        nile_Real_t t_13_r = t_12;
        nile_Real_t t_13_g = t_12;
        nile_Real_t t_13_b = t_12;
        nile_Real_t t_14_a = nile_Real_mul(v_a_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_mul(v_a_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_mul(v_a_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_mul(v_a_b, t_13_b);
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_sub(t_15, v_a_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_b_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_b_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_b_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_b_b, t_17_b);
        nile_Real_t t_19_a = nile_Real_add(t_14_a, t_18_a);
        nile_Real_t t_19_r = nile_Real_add(t_14_r, t_18_r);
        nile_Real_t t_19_g = nile_Real_add(t_14_g, t_18_g);
        nile_Real_t t_19_b = nile_Real_add(t_14_b, t_18_b);
        nile_Real_t t_20_a = nile_Real_add(t_10_a, t_19_a);
        nile_Real_t t_20_r = nile_Real_add(t_10_r, t_19_r);
        nile_Real_t t_20_g = nile_Real_add(t_10_g, t_19_g);
        nile_Real_t t_20_b = nile_Real_add(t_10_b, t_19_b);
        nile_Real_t v_c_a = t_20_a;
        nile_Real_t v_c_r = t_20_r;
        nile_Real_t v_c_g = t_20_g;
        nile_Real_t v_c_b = t_20_b;
        nile_Real_t t_22 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_23 = nile_Real_add(v_c_a, t_22);
        nile_Real_t t_21_1 = t_23;
        nile_Real_t t_21_2 = v_c_r;
        nile_Real_t t_21_3 = v_c_g;
        nile_Real_t t_21_4 = v_c_b;
        nile_Real_t t_24_a = t_21_1;
        nile_Real_t t_24_r = t_21_2;
        nile_Real_t t_24_g = t_21_3;
        nile_Real_t t_24_b = t_21_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_24_a);
        nile_Buffer_append(out, t_24_r);
        nile_Buffer_append(out, t_24_g);
        nile_Buffer_append(out, t_24_b);
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
} gezira_CompositeSubtract_t;

static nile_Kernel_t *gezira_CompositeSubtract_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeSubtract_t *k = (gezira_CompositeSubtract_t *) k_;
    gezira_CompositeSubtract_t *clone = (gezira_CompositeSubtract_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeSubtract(nile_t *nl) {
    gezira_CompositeSubtract_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeSubtract);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeSubtract_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeSubtract_t *k = (gezira_CompositeSubtract_t *) k_;
    
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
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = 1;
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_sub(t_1_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_sub(t_1_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_sub(t_1_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_sub(t_1_b, t_3_b);
        nile_Real_t t_5 = 0;
        nile_Real_t t_6_a = t_5;
        nile_Real_t t_6_r = t_5;
        nile_Real_t t_6_g = t_5;
        nile_Real_t t_6_b = t_5;
        nile_Real_t t_7 = nile_Real_gt(t_4_a, t_6_a);
        nile_Real_t t_8 = t_7 ? t_4_a : t_6_a;
        nile_Real_t t_9 = nile_Real_gt(t_4_r, t_6_r);
        nile_Real_t t_10 = t_9 ? t_4_r : t_6_r;
        nile_Real_t t_11 = nile_Real_gt(t_4_g, t_6_g);
        nile_Real_t t_12 = t_11 ? t_4_g : t_6_g;
        nile_Real_t t_13 = nile_Real_gt(t_4_b, t_6_b);
        nile_Real_t t_14 = t_13 ? t_4_b : t_6_b;
        nile_Real_t t_15_1 = t_8;
        nile_Real_t t_15_2 = t_10;
        nile_Real_t t_15_3 = t_12;
        nile_Real_t t_15_4 = t_14;
        nile_Real_t t_16_a = t_15_1;
        nile_Real_t t_16_r = t_15_2;
        nile_Real_t t_16_g = t_15_3;
        nile_Real_t t_16_b = t_15_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_16_a);
        nile_Buffer_append(out, t_16_r);
        nile_Buffer_append(out, t_16_g);
        nile_Buffer_append(out, t_16_b);
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
} gezira_CompositeInvert_t;

static nile_Kernel_t *gezira_CompositeInvert_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CompositeInvert_t *k = (gezira_CompositeInvert_t *) k_;
    gezira_CompositeInvert_t *clone = (gezira_CompositeInvert_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CompositeInvert(nile_t *nl) {
    gezira_CompositeInvert_t *k = NILE_KERNEL_NEW(nl, gezira_CompositeInvert);
    return (nile_Kernel_t *) k;
}

static int gezira_CompositeInvert_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 8
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeInvert_t *k = (gezira_CompositeInvert_t *) k_;
    
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
        nile_Real_t t_2 = 1;
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_r);
        nile_Real_t t_4 = 1;
        nile_Real_t t_5 = nile_Real_sub(t_4, v_b_g);
        nile_Real_t t_6 = 1;
        nile_Real_t t_7 = nile_Real_sub(t_6, v_b_b);
        nile_Real_t t_1_1 = v_b_a;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_1_3 = t_5;
        nile_Real_t t_1_4 = t_7;
        nile_Real_t t_8_a = t_1_1;
        nile_Real_t t_8_r = t_1_2;
        nile_Real_t t_8_g = t_1_3;
        nile_Real_t t_8_b = t_1_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_8_a);
        nile_Buffer_append(out, t_8_r);
        nile_Buffer_append(out, t_8_g);
        nile_Buffer_append(out, t_8_b);
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
    nile_Real_t v_n;
    nile_Real_t v_sum_a;
    nile_Real_t v_sum_r;
    nile_Real_t v_sum_g;
    nile_Real_t v_sum_b;
    nile_Real_t v_i;
} gezira_SumWeightedColors_t;

static nile_Kernel_t *gezira_SumWeightedColors_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_SumWeightedColors_t *k = (gezira_SumWeightedColors_t *) k_;
    gezira_SumWeightedColors_t *clone = (gezira_SumWeightedColors_t *) nile_Kernel_clone(nl, k_);
    clone->v_n = k->v_n;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_SumWeightedColors(nile_t *nl, 
                                        nile_Real_t v_n) {
    gezira_SumWeightedColors_t *k = NILE_KERNEL_NEW(nl, gezira_SumWeightedColors);
    k->v_n = v_n;
    return (nile_Kernel_t *) k;
}

static int gezira_SumWeightedColors_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 5
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_SumWeightedColors_t *k = (gezira_SumWeightedColors_t *) k_;
    nile_Real_t v_n = k->v_n;
    nile_Real_t v_sum_a = k->v_sum_a;
    nile_Real_t v_sum__a;
    nile_Real_t v_sum_r = k->v_sum_r;
    nile_Real_t v_sum__r;
    nile_Real_t v_sum_g = k->v_sum_g;
    nile_Real_t v_sum__g;
    nile_Real_t v_sum_b = k->v_sum_b;
    nile_Real_t v_sum__b;
    nile_Real_t v_i = k->v_i;
    nile_Real_t v_i_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        nile_Real_t t_4 = 0;
        nile_Real_t t_5_a = t_4;
        nile_Real_t t_5_r = t_4;
        nile_Real_t t_5_g = t_4;
        nile_Real_t t_5_b = t_4;
        v_sum_a = t_5_a;
        v_sum_r = t_5_r;
        v_sum_g = t_5_g;
        v_sum_b = t_5_b;
        nile_Real_t t_6 = 1;
        v_i = t_6;
    }
    
    while (in->i < in->n) {
        v_sum__a = v_sum_a;
        v_sum__r = v_sum_r;
        v_sum__g = v_sum_g;
        v_sum__b = v_sum_b;
        v_i_ = v_i;
        nile_Real_t v_c_a = nile_Buffer_shift(in);
        nile_Real_t v_c_r = nile_Buffer_shift(in);
        nile_Real_t v_c_g = nile_Buffer_shift(in);
        nile_Real_t v_c_b = nile_Buffer_shift(in);
        nile_Real_t v_w = nile_Buffer_shift(in);
        nile_Real_t t_7 = nile_Real_eq(v_i, v_n);
        if (t_7) {
            nile_Real_t t_8 = 0;
            nile_Real_t t_9_a = v_w;
            nile_Real_t t_9_r = v_w;
            nile_Real_t t_9_g = v_w;
            nile_Real_t t_9_b = v_w;
            nile_Real_t t_10_a = nile_Real_mul(v_c_a, t_9_a);
            nile_Real_t t_10_r = nile_Real_mul(v_c_r, t_9_r);
            nile_Real_t t_10_g = nile_Real_mul(v_c_g, t_9_g);
            nile_Real_t t_10_b = nile_Real_mul(v_c_b, t_9_b);
            nile_Real_t t_11_a = nile_Real_add(v_sum_a, t_10_a);
            nile_Real_t t_11_r = nile_Real_add(v_sum_r, t_10_r);
            nile_Real_t t_11_g = nile_Real_add(v_sum_g, t_10_g);
            nile_Real_t t_11_b = nile_Real_add(v_sum_b, t_10_b);
            nile_Real_t t_12_a = t_8;
            nile_Real_t t_12_r = t_8;
            nile_Real_t t_12_g = t_8;
            nile_Real_t t_12_b = t_8;
            nile_Real_t t_13 = nile_Real_gt(t_12_a, t_11_a);
            nile_Real_t t_14 = t_13 ? t_12_a : t_11_a;
            nile_Real_t t_15 = nile_Real_gt(t_12_r, t_11_r);
            nile_Real_t t_16 = t_15 ? t_12_r : t_11_r;
            nile_Real_t t_17 = nile_Real_gt(t_12_g, t_11_g);
            nile_Real_t t_18 = t_17 ? t_12_g : t_11_g;
            nile_Real_t t_19 = nile_Real_gt(t_12_b, t_11_b);
            nile_Real_t t_20 = t_19 ? t_12_b : t_11_b;
            nile_Real_t t_21_1 = t_14;
            nile_Real_t t_21_2 = t_16;
            nile_Real_t t_21_3 = t_18;
            nile_Real_t t_21_4 = t_20;
            nile_Real_t t_22_a = t_21_1;
            nile_Real_t t_22_r = t_21_2;
            nile_Real_t t_22_g = t_21_3;
            nile_Real_t t_22_b = t_21_4;
            nile_Real_t t_23 = 1;
            nile_Real_t t_24_a = t_23;
            nile_Real_t t_24_r = t_23;
            nile_Real_t t_24_g = t_23;
            nile_Real_t t_24_b = t_23;
            nile_Real_t t_25 = nile_Real_lt(t_22_a, t_24_a);
            nile_Real_t t_26 = t_25 ? t_22_a : t_24_a;
            nile_Real_t t_27 = nile_Real_lt(t_22_r, t_24_r);
            nile_Real_t t_28 = t_27 ? t_22_r : t_24_r;
            nile_Real_t t_29 = nile_Real_lt(t_22_g, t_24_g);
            nile_Real_t t_30 = t_29 ? t_22_g : t_24_g;
            nile_Real_t t_31 = nile_Real_lt(t_22_b, t_24_b);
            nile_Real_t t_32 = t_31 ? t_22_b : t_24_b;
            nile_Real_t t_33_1 = t_26;
            nile_Real_t t_33_2 = t_28;
            nile_Real_t t_33_3 = t_30;
            nile_Real_t t_33_4 = t_32;
            nile_Real_t t_34_a = t_33_1;
            nile_Real_t t_34_r = t_33_2;
            nile_Real_t t_34_g = t_33_3;
            nile_Real_t t_34_b = t_33_4;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_34_a);
            nile_Buffer_append(out, t_34_r);
            nile_Buffer_append(out, t_34_g);
            nile_Buffer_append(out, t_34_b);
            nile_Real_t t_35 = 0;
            nile_Real_t t_36_a = t_35;
            nile_Real_t t_36_r = t_35;
            nile_Real_t t_36_g = t_35;
            nile_Real_t t_36_b = t_35;
            v_sum__a = t_36_a;
            v_sum__r = t_36_r;
            v_sum__g = t_36_g;
            v_sum__b = t_36_b;
            nile_Real_t t_37 = 1;
            v_i_ = t_37;
        }
        else {
            nile_Real_t t_38_a = v_w;
            nile_Real_t t_38_r = v_w;
            nile_Real_t t_38_g = v_w;
            nile_Real_t t_38_b = v_w;
            nile_Real_t t_39_a = nile_Real_mul(v_c_a, t_38_a);
            nile_Real_t t_39_r = nile_Real_mul(v_c_r, t_38_r);
            nile_Real_t t_39_g = nile_Real_mul(v_c_g, t_38_g);
            nile_Real_t t_39_b = nile_Real_mul(v_c_b, t_38_b);
            nile_Real_t t_40_a = nile_Real_add(v_sum_a, t_39_a);
            nile_Real_t t_40_r = nile_Real_add(v_sum_r, t_39_r);
            nile_Real_t t_40_g = nile_Real_add(v_sum_g, t_39_g);
            nile_Real_t t_40_b = nile_Real_add(v_sum_b, t_39_b);
            v_sum__a = t_40_a;
            v_sum__r = t_40_r;
            v_sum__g = t_40_g;
            v_sum__b = t_40_b;
            nile_Real_t t_41 = 1;
            nile_Real_t t_42 = nile_Real_add(v_i, t_41);
            v_i_ = t_42;
        }
        v_sum_a = v_sum__a;
        v_sum_r = v_sum__r;
        v_sum_g = v_sum__g;
        v_sum_b = v_sum__b;
        v_i = v_i_;
    }
    
    if (in->eos) {
    }
    else {
        k->v_n = v_n;
        k->v_sum_a = v_sum_a;
        k->v_sum_r = v_sum_r;
        k->v_sum_g = v_sum_g;
        k->v_sum_b = v_sum_b;
        k->v_i = v_i;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
} gezira_BilinearFilterPoints_t;

static nile_Kernel_t *gezira_BilinearFilterPoints_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BilinearFilterPoints_t *k = (gezira_BilinearFilterPoints_t *) k_;
    gezira_BilinearFilterPoints_t *clone = (gezira_BilinearFilterPoints_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BilinearFilterPoints(nile_t *nl) {
    gezira_BilinearFilterPoints_t *k = NILE_KERNEL_NEW(nl, gezira_BilinearFilterPoints);
    return (nile_Kernel_t *) k;
}

static int gezira_BilinearFilterPoints_process(nile_t *nl,
                                               nile_Kernel_t *k_,
                                               nile_Buffer_t **in_,
                                               nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BilinearFilterPoints_t *k = (gezira_BilinearFilterPoints_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0.5;
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = 0.5;
        nile_Real_t t_6_x = t_5;
        nile_Real_t t_6_y = t_5;
        nile_Real_t t_7_x = nile_Real_add(t_4_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_add(t_4_y, t_6_y);
        nile_Real_t v_S_x = t_7_x;
        nile_Real_t v_S_y = t_7_y;
        nile_Real_t v_x = v_S_x;
        nile_Real_t v_y = v_S_y;
        nile_Real_t t_8_1 = v_x;
        nile_Real_t t_8_2 = v_y;
        nile_Real_t t_9_x = t_8_1;
        nile_Real_t t_9_y = t_8_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_9_x);
        nile_Buffer_append(out, t_9_y);
        nile_Real_t t_11 = 1;
        nile_Real_t t_12 = nile_Real_add(v_x, t_11);
        nile_Real_t t_10_1 = t_12;
        nile_Real_t t_10_2 = v_y;
        nile_Real_t t_13_x = t_10_1;
        nile_Real_t t_13_y = t_10_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_13_x);
        nile_Buffer_append(out, t_13_y);
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_add(v_y, t_15);
        nile_Real_t t_14_1 = v_x;
        nile_Real_t t_14_2 = t_16;
        nile_Real_t t_17_x = t_14_1;
        nile_Real_t t_17_y = t_14_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_17_x);
        nile_Buffer_append(out, t_17_y);
        nile_Real_t t_19 = 1;
        nile_Real_t t_20 = nile_Real_add(v_x, t_19);
        nile_Real_t t_21 = 1;
        nile_Real_t t_22 = nile_Real_add(v_y, t_21);
        nile_Real_t t_18_1 = t_20;
        nile_Real_t t_18_2 = t_22;
        nile_Real_t t_23_x = t_18_1;
        nile_Real_t t_23_y = t_18_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_23_x);
        nile_Buffer_append(out, t_23_y);
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
} gezira_BilinearFilterWeights_t;

static nile_Kernel_t *gezira_BilinearFilterWeights_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BilinearFilterWeights_t *k = (gezira_BilinearFilterWeights_t *) k_;
    gezira_BilinearFilterWeights_t *clone = (gezira_BilinearFilterWeights_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BilinearFilterWeights(nile_t *nl) {
    gezira_BilinearFilterWeights_t *k = NILE_KERNEL_NEW(nl, gezira_BilinearFilterWeights);
    return (nile_Kernel_t *) k;
}

static int gezira_BilinearFilterWeights_process(nile_t *nl,
                                                nile_Kernel_t *k_,
                                                nile_Buffer_t **in_,
                                                nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BilinearFilterWeights_t *k = (gezira_BilinearFilterWeights_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0.5;
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5_x = nile_Real_sub(v_P_x, t_4_x);
        nile_Real_t t_5_y = nile_Real_sub(v_P_y, t_4_y);
        nile_Real_t t_6 = 0.5;
        nile_Real_t t_7_x = t_6;
        nile_Real_t t_7_y = t_6;
        nile_Real_t t_8_x = nile_Real_sub(t_5_x, t_7_x);
        nile_Real_t t_8_y = nile_Real_sub(t_5_y, t_7_y);
        nile_Real_t v_S_x = t_8_x;
        nile_Real_t v_S_y = t_8_y;
        nile_Real_t v_u = v_S_x;
        nile_Real_t v_v = v_S_y;
        nile_Real_t t_9 = 1;
        nile_Real_t t_10 = nile_Real_sub(t_9, v_u);
        nile_Real_t t_11 = 1;
        nile_Real_t t_12 = nile_Real_sub(t_11, v_v);
        nile_Real_t t_13 = nile_Real_mul(t_10, t_12);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_13);
        nile_Real_t t_14 = 1;
        nile_Real_t t_15 = nile_Real_sub(t_14, v_v);
        nile_Real_t t_16 = nile_Real_mul(v_u, t_15);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_16);
        nile_Real_t t_17 = 1;
        nile_Real_t t_18 = nile_Real_sub(t_17, v_u);
        nile_Real_t t_19 = nile_Real_mul(t_18, v_v);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_19);
        nile_Real_t t_20 = nile_Real_mul(v_u, v_v);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_20);
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
    nile_Kernel_t *v_s;
} gezira_BilinearFilter_t;

static nile_Kernel_t *gezira_BilinearFilter_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BilinearFilter_t *k = (gezira_BilinearFilter_t *) k_;
    gezira_BilinearFilter_t *clone = (gezira_BilinearFilter_t *) nile_Kernel_clone(nl, k_);
    clone->v_s = k->v_s->clone(nl, k->v_s);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BilinearFilter(nile_t *nl, 
                                     nile_Kernel_t *v_s) {
    gezira_BilinearFilter_t *k = NILE_KERNEL_NEW(nl, gezira_BilinearFilter);
    k->v_s = v_s;
    return (nile_Kernel_t *) k;
}

static int gezira_BilinearFilter_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BilinearFilter_t *k = (gezira_BilinearFilter_t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        ; /* no-op */
        nile_Kernel_t *t_1 = nile_Pipeline(nl, gezira_BilinearFilterPoints(nl), v_s, NULL);
        nile_Real_t t_2 = 4;
        nile_Kernel_t *t_3 = gezira_BilinearFilterWeights(nl);
        nile_Real_t t_4 = 1;
        nile_Kernel_t *t_5 = nile_Interleave(nl, t_1, t_2, t_3, t_4);
        nile_Real_t t_6 = 4;
        nile_Kernel_t *t_7 = gezira_SumWeightedColors(nl, t_6);
        nile_Kernel_t *t_8 = nile_Pipeline(nl, t_5, t_7, NULL);
        nile_Kernel_t *f = t_8;
        f->downstream = k_->downstream;
        k_->downstream = f;
    }
    
    return NILE_INPUT_FORWARD;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
} gezira_KeysWeights_t;

static nile_Kernel_t *gezira_KeysWeights_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_KeysWeights_t *k = (gezira_KeysWeights_t *) k_;
    gezira_KeysWeights_t *clone = (gezira_KeysWeights_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_KeysWeights(nile_t *nl) {
    gezira_KeysWeights_t *k = NILE_KERNEL_NEW(nl, gezira_KeysWeights);
    return (nile_Kernel_t *) k;
}

static int gezira_KeysWeights_process(nile_t *nl,
                                      nile_Kernel_t *k_,
                                      nile_Buffer_t **in_,
                                      nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_KeysWeights_t *k = (gezira_KeysWeights_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_D_x = nile_Buffer_shift(in);
        nile_Real_t v_D_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0;
        nile_Real_t t_2 = nile_Real_lt(v_D_x, t_1);
        nile_Real_t t_3 = nile_Real_neg(v_D_x);
        nile_Real_t t_4 = t_2 ? t_3 : v_D_x;
        nile_Real_t t_5 = 0;
        nile_Real_t t_6 = nile_Real_lt(v_D_y, t_5);
        nile_Real_t t_7 = nile_Real_neg(v_D_y);
        nile_Real_t t_8 = t_6 ? t_7 : v_D_y;
        nile_Real_t t_9_1 = t_4;
        nile_Real_t t_9_2 = t_8;
        nile_Real_t t_10_x = t_9_1;
        nile_Real_t t_10_y = t_9_2;
        nile_Real_t v_T_x = t_10_x;
        nile_Real_t v_T_y = t_10_y;
        nile_Real_t t_11 = 1;
        nile_Real_t t_12_x = t_11;
        nile_Real_t t_12_y = t_11;
        nile_Real_t t_13_x = nile_Real_lt(v_T_x, t_12_x);
        nile_Real_t t_13_y = nile_Real_lt(v_T_y, t_12_y);
        nile_Real_t t_14 = 1.5;
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_mul(t_15_x, v_T_x);
        nile_Real_t t_16_y = nile_Real_mul(t_15_y, v_T_y);
        nile_Real_t t_17_x = nile_Real_mul(t_16_x, v_T_x);
        nile_Real_t t_17_y = nile_Real_mul(t_16_y, v_T_y);
        nile_Real_t t_18_x = nile_Real_mul(t_17_x, v_T_x);
        nile_Real_t t_18_y = nile_Real_mul(t_17_y, v_T_y);
        nile_Real_t t_19 = 2.5;
        nile_Real_t t_20_x = t_19;
        nile_Real_t t_20_y = t_19;
        nile_Real_t t_21_x = nile_Real_mul(t_20_x, v_T_x);
        nile_Real_t t_21_y = nile_Real_mul(t_20_y, v_T_y);
        nile_Real_t t_22_x = nile_Real_mul(t_21_x, v_T_x);
        nile_Real_t t_22_y = nile_Real_mul(t_21_y, v_T_y);
        nile_Real_t t_23_x = nile_Real_sub(t_18_x, t_22_x);
        nile_Real_t t_23_y = nile_Real_sub(t_18_y, t_22_y);
        nile_Real_t t_24 = 1;
        nile_Real_t t_25_x = t_24;
        nile_Real_t t_25_y = t_24;
        nile_Real_t t_26_x = nile_Real_add(t_23_x, t_25_x);
        nile_Real_t t_26_y = nile_Real_add(t_23_y, t_25_y);
        nile_Real_t t_27 = 2;
        nile_Real_t t_28_x = t_27;
        nile_Real_t t_28_y = t_27;
        nile_Real_t t_29_x = nile_Real_lt(v_T_x, t_28_x);
        nile_Real_t t_29_y = nile_Real_lt(v_T_y, t_28_y);
        nile_Real_t t_30 = 0.5;
        nile_Real_t t_31 = nile_Real_neg(t_30);
        nile_Real_t t_32_x = t_31;
        nile_Real_t t_32_y = t_31;
        nile_Real_t t_33_x = nile_Real_mul(t_32_x, v_T_x);
        nile_Real_t t_33_y = nile_Real_mul(t_32_y, v_T_y);
        nile_Real_t t_34_x = nile_Real_mul(t_33_x, v_T_x);
        nile_Real_t t_34_y = nile_Real_mul(t_33_y, v_T_y);
        nile_Real_t t_35_x = nile_Real_mul(t_34_x, v_T_x);
        nile_Real_t t_35_y = nile_Real_mul(t_34_y, v_T_y);
        nile_Real_t t_36 = 2.5;
        nile_Real_t t_37_x = t_36;
        nile_Real_t t_37_y = t_36;
        nile_Real_t t_38_x = nile_Real_mul(t_37_x, v_T_x);
        nile_Real_t t_38_y = nile_Real_mul(t_37_y, v_T_y);
        nile_Real_t t_39_x = nile_Real_mul(t_38_x, v_T_x);
        nile_Real_t t_39_y = nile_Real_mul(t_38_y, v_T_y);
        nile_Real_t t_40_x = nile_Real_add(t_35_x, t_39_x);
        nile_Real_t t_40_y = nile_Real_add(t_35_y, t_39_y);
        nile_Real_t t_41 = 4;
        nile_Real_t t_42_x = t_41;
        nile_Real_t t_42_y = t_41;
        nile_Real_t t_43_x = nile_Real_mul(t_42_x, v_T_x);
        nile_Real_t t_43_y = nile_Real_mul(t_42_y, v_T_y);
        nile_Real_t t_44_x = nile_Real_sub(t_40_x, t_43_x);
        nile_Real_t t_44_y = nile_Real_sub(t_40_y, t_43_y);
        nile_Real_t t_45 = 2;
        nile_Real_t t_46_x = t_45;
        nile_Real_t t_46_y = t_45;
        nile_Real_t t_47_x = nile_Real_add(t_44_x, t_46_x);
        nile_Real_t t_47_y = nile_Real_add(t_44_y, t_46_y);
        nile_Real_t t_48 = 0;
        nile_Real_t t_49_x = t_48;
        nile_Real_t t_49_y = t_48;
        nile_Real_t t_50_x = t_29_x ? t_47_x : t_49_x;
        nile_Real_t t_50_y = t_29_y ? t_47_y : t_49_y;
        nile_Real_t t_51_x = t_13_x ? t_26_x : t_50_x;
        nile_Real_t t_51_y = t_13_y ? t_26_y : t_50_y;
        nile_Real_t v_S_x = t_51_x;
        nile_Real_t v_S_y = t_51_y;
        nile_Real_t t_52 = nile_Real_mul(v_S_x, v_S_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_52);
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
} gezira_BicubicFilterPoints_t;

static nile_Kernel_t *gezira_BicubicFilterPoints_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BicubicFilterPoints_t *k = (gezira_BicubicFilterPoints_t *) k_;
    gezira_BicubicFilterPoints_t *clone = (gezira_BicubicFilterPoints_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BicubicFilterPoints(nile_t *nl) {
    gezira_BicubicFilterPoints_t *k = NILE_KERNEL_NEW(nl, gezira_BicubicFilterPoints);
    return (nile_Kernel_t *) k;
}

static int gezira_BicubicFilterPoints_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BicubicFilterPoints_t *k = (gezira_BicubicFilterPoints_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0.5;
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = 0.5;
        nile_Real_t t_6_x = t_5;
        nile_Real_t t_6_y = t_5;
        nile_Real_t t_7_x = nile_Real_add(t_4_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_add(t_4_y, t_6_y);
        nile_Real_t v_S_x = t_7_x;
        nile_Real_t v_S_y = t_7_y;
        nile_Real_t v_x = v_S_x;
        nile_Real_t v_y = v_S_y;
        nile_Real_t t_9 = 1;
        nile_Real_t t_10 = nile_Real_sub(v_x, t_9);
        nile_Real_t t_11 = 1;
        nile_Real_t t_12 = nile_Real_sub(v_y, t_11);
        nile_Real_t t_8_1 = t_10;
        nile_Real_t t_8_2 = t_12;
        nile_Real_t t_13_x = t_8_1;
        nile_Real_t t_13_y = t_8_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_13_x);
        nile_Buffer_append(out, t_13_y);
        nile_Real_t t_15 = 1;
        nile_Real_t t_16 = nile_Real_sub(v_y, t_15);
        nile_Real_t t_14_1 = v_x;
        nile_Real_t t_14_2 = t_16;
        nile_Real_t t_17_x = t_14_1;
        nile_Real_t t_17_y = t_14_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_17_x);
        nile_Buffer_append(out, t_17_y);
        nile_Real_t t_19 = 1;
        nile_Real_t t_20 = nile_Real_add(v_x, t_19);
        nile_Real_t t_21 = 1;
        nile_Real_t t_22 = nile_Real_sub(v_y, t_21);
        nile_Real_t t_18_1 = t_20;
        nile_Real_t t_18_2 = t_22;
        nile_Real_t t_23_x = t_18_1;
        nile_Real_t t_23_y = t_18_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_23_x);
        nile_Buffer_append(out, t_23_y);
        nile_Real_t t_25 = 2;
        nile_Real_t t_26 = nile_Real_add(v_x, t_25);
        nile_Real_t t_27 = 1;
        nile_Real_t t_28 = nile_Real_sub(v_y, t_27);
        nile_Real_t t_24_1 = t_26;
        nile_Real_t t_24_2 = t_28;
        nile_Real_t t_29_x = t_24_1;
        nile_Real_t t_29_y = t_24_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_29_x);
        nile_Buffer_append(out, t_29_y);
        nile_Real_t t_31 = 1;
        nile_Real_t t_32 = nile_Real_sub(v_x, t_31);
        nile_Real_t t_30_1 = t_32;
        nile_Real_t t_30_2 = v_y;
        nile_Real_t t_33_x = t_30_1;
        nile_Real_t t_33_y = t_30_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_33_x);
        nile_Buffer_append(out, t_33_y);
        nile_Real_t t_34_1 = v_x;
        nile_Real_t t_34_2 = v_y;
        nile_Real_t t_35_x = t_34_1;
        nile_Real_t t_35_y = t_34_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_35_x);
        nile_Buffer_append(out, t_35_y);
        nile_Real_t t_37 = 1;
        nile_Real_t t_38 = nile_Real_add(v_x, t_37);
        nile_Real_t t_36_1 = t_38;
        nile_Real_t t_36_2 = v_y;
        nile_Real_t t_39_x = t_36_1;
        nile_Real_t t_39_y = t_36_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_39_x);
        nile_Buffer_append(out, t_39_y);
        nile_Real_t t_41 = 2;
        nile_Real_t t_42 = nile_Real_add(v_x, t_41);
        nile_Real_t t_40_1 = t_42;
        nile_Real_t t_40_2 = v_y;
        nile_Real_t t_43_x = t_40_1;
        nile_Real_t t_43_y = t_40_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_43_x);
        nile_Buffer_append(out, t_43_y);
        nile_Real_t t_45 = 1;
        nile_Real_t t_46 = nile_Real_sub(v_x, t_45);
        nile_Real_t t_47 = 1;
        nile_Real_t t_48 = nile_Real_add(v_y, t_47);
        nile_Real_t t_44_1 = t_46;
        nile_Real_t t_44_2 = t_48;
        nile_Real_t t_49_x = t_44_1;
        nile_Real_t t_49_y = t_44_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_49_x);
        nile_Buffer_append(out, t_49_y);
        nile_Real_t t_51 = 1;
        nile_Real_t t_52 = nile_Real_add(v_y, t_51);
        nile_Real_t t_50_1 = v_x;
        nile_Real_t t_50_2 = t_52;
        nile_Real_t t_53_x = t_50_1;
        nile_Real_t t_53_y = t_50_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_53_x);
        nile_Buffer_append(out, t_53_y);
        nile_Real_t t_55 = 1;
        nile_Real_t t_56 = nile_Real_add(v_x, t_55);
        nile_Real_t t_57 = 1;
        nile_Real_t t_58 = nile_Real_add(v_y, t_57);
        nile_Real_t t_54_1 = t_56;
        nile_Real_t t_54_2 = t_58;
        nile_Real_t t_59_x = t_54_1;
        nile_Real_t t_59_y = t_54_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_59_x);
        nile_Buffer_append(out, t_59_y);
        nile_Real_t t_61 = 2;
        nile_Real_t t_62 = nile_Real_add(v_x, t_61);
        nile_Real_t t_63 = 1;
        nile_Real_t t_64 = nile_Real_add(v_y, t_63);
        nile_Real_t t_60_1 = t_62;
        nile_Real_t t_60_2 = t_64;
        nile_Real_t t_65_x = t_60_1;
        nile_Real_t t_65_y = t_60_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_65_x);
        nile_Buffer_append(out, t_65_y);
        nile_Real_t t_67 = 1;
        nile_Real_t t_68 = nile_Real_sub(v_x, t_67);
        nile_Real_t t_69 = 2;
        nile_Real_t t_70 = nile_Real_add(v_y, t_69);
        nile_Real_t t_66_1 = t_68;
        nile_Real_t t_66_2 = t_70;
        nile_Real_t t_71_x = t_66_1;
        nile_Real_t t_71_y = t_66_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_71_x);
        nile_Buffer_append(out, t_71_y);
        nile_Real_t t_73 = 2;
        nile_Real_t t_74 = nile_Real_add(v_y, t_73);
        nile_Real_t t_72_1 = v_x;
        nile_Real_t t_72_2 = t_74;
        nile_Real_t t_75_x = t_72_1;
        nile_Real_t t_75_y = t_72_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_75_x);
        nile_Buffer_append(out, t_75_y);
        nile_Real_t t_77 = 1;
        nile_Real_t t_78 = nile_Real_add(v_x, t_77);
        nile_Real_t t_79 = 2;
        nile_Real_t t_80 = nile_Real_add(v_y, t_79);
        nile_Real_t t_76_1 = t_78;
        nile_Real_t t_76_2 = t_80;
        nile_Real_t t_81_x = t_76_1;
        nile_Real_t t_81_y = t_76_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_81_x);
        nile_Buffer_append(out, t_81_y);
        nile_Real_t t_83 = 2;
        nile_Real_t t_84 = nile_Real_add(v_x, t_83);
        nile_Real_t t_85 = 2;
        nile_Real_t t_86 = nile_Real_add(v_y, t_85);
        nile_Real_t t_82_1 = t_84;
        nile_Real_t t_82_2 = t_86;
        nile_Real_t t_87_x = t_82_1;
        nile_Real_t t_87_y = t_82_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_87_x);
        nile_Buffer_append(out, t_87_y);
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
} gezira_BicubicFilterDeltas_t;

static nile_Kernel_t *gezira_BicubicFilterDeltas_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BicubicFilterDeltas_t *k = (gezira_BicubicFilterDeltas_t *) k_;
    gezira_BicubicFilterDeltas_t *clone = (gezira_BicubicFilterDeltas_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BicubicFilterDeltas(nile_t *nl) {
    gezira_BicubicFilterDeltas_t *k = NILE_KERNEL_NEW(nl, gezira_BicubicFilterDeltas);
    return (nile_Kernel_t *) k;
}

static int gezira_BicubicFilterDeltas_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BicubicFilterDeltas_t *k = (gezira_BicubicFilterDeltas_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0.5;
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = 0.5;
        nile_Real_t t_6_x = t_5;
        nile_Real_t t_6_y = t_5;
        nile_Real_t t_7_x = nile_Real_add(t_4_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_add(t_4_y, t_6_y);
        nile_Real_t v_S_x = t_7_x;
        nile_Real_t v_S_y = t_7_y;
        nile_Real_t v_x = v_S_x;
        nile_Real_t v_y = v_S_y;
        nile_Real_t t_9 = 1;
        nile_Real_t t_10 = nile_Real_sub(v_x, t_9);
        nile_Real_t t_11 = 1;
        nile_Real_t t_12 = nile_Real_sub(v_y, t_11);
        nile_Real_t t_8_1 = t_10;
        nile_Real_t t_8_2 = t_12;
        nile_Real_t t_13_x = t_8_1;
        nile_Real_t t_13_y = t_8_2;
        nile_Real_t t_14_x = nile_Real_sub(t_13_x, v_P_x);
        nile_Real_t t_14_y = nile_Real_sub(t_13_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_14_x);
        nile_Buffer_append(out, t_14_y);
        nile_Real_t t_16 = 1;
        nile_Real_t t_17 = nile_Real_sub(v_y, t_16);
        nile_Real_t t_15_1 = v_x;
        nile_Real_t t_15_2 = t_17;
        nile_Real_t t_18_x = t_15_1;
        nile_Real_t t_18_y = t_15_2;
        nile_Real_t t_19_x = nile_Real_sub(t_18_x, v_P_x);
        nile_Real_t t_19_y = nile_Real_sub(t_18_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_19_x);
        nile_Buffer_append(out, t_19_y);
        nile_Real_t t_21 = 1;
        nile_Real_t t_22 = nile_Real_add(v_x, t_21);
        nile_Real_t t_23 = 1;
        nile_Real_t t_24 = nile_Real_sub(v_y, t_23);
        nile_Real_t t_20_1 = t_22;
        nile_Real_t t_20_2 = t_24;
        nile_Real_t t_25_x = t_20_1;
        nile_Real_t t_25_y = t_20_2;
        nile_Real_t t_26_x = nile_Real_sub(t_25_x, v_P_x);
        nile_Real_t t_26_y = nile_Real_sub(t_25_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_26_x);
        nile_Buffer_append(out, t_26_y);
        nile_Real_t t_28 = 2;
        nile_Real_t t_29 = nile_Real_add(v_x, t_28);
        nile_Real_t t_30 = 1;
        nile_Real_t t_31 = nile_Real_sub(v_y, t_30);
        nile_Real_t t_27_1 = t_29;
        nile_Real_t t_27_2 = t_31;
        nile_Real_t t_32_x = t_27_1;
        nile_Real_t t_32_y = t_27_2;
        nile_Real_t t_33_x = nile_Real_sub(t_32_x, v_P_x);
        nile_Real_t t_33_y = nile_Real_sub(t_32_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_33_x);
        nile_Buffer_append(out, t_33_y);
        nile_Real_t t_35 = 1;
        nile_Real_t t_36 = nile_Real_sub(v_x, t_35);
        nile_Real_t t_34_1 = t_36;
        nile_Real_t t_34_2 = v_y;
        nile_Real_t t_37_x = t_34_1;
        nile_Real_t t_37_y = t_34_2;
        nile_Real_t t_38_x = nile_Real_sub(t_37_x, v_P_x);
        nile_Real_t t_38_y = nile_Real_sub(t_37_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_38_x);
        nile_Buffer_append(out, t_38_y);
        nile_Real_t t_39_1 = v_x;
        nile_Real_t t_39_2 = v_y;
        nile_Real_t t_40_x = t_39_1;
        nile_Real_t t_40_y = t_39_2;
        nile_Real_t t_41_x = nile_Real_sub(t_40_x, v_P_x);
        nile_Real_t t_41_y = nile_Real_sub(t_40_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_41_x);
        nile_Buffer_append(out, t_41_y);
        nile_Real_t t_43 = 1;
        nile_Real_t t_44 = nile_Real_add(v_x, t_43);
        nile_Real_t t_42_1 = t_44;
        nile_Real_t t_42_2 = v_y;
        nile_Real_t t_45_x = t_42_1;
        nile_Real_t t_45_y = t_42_2;
        nile_Real_t t_46_x = nile_Real_sub(t_45_x, v_P_x);
        nile_Real_t t_46_y = nile_Real_sub(t_45_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_46_x);
        nile_Buffer_append(out, t_46_y);
        nile_Real_t t_48 = 2;
        nile_Real_t t_49 = nile_Real_add(v_x, t_48);
        nile_Real_t t_47_1 = t_49;
        nile_Real_t t_47_2 = v_y;
        nile_Real_t t_50_x = t_47_1;
        nile_Real_t t_50_y = t_47_2;
        nile_Real_t t_51_x = nile_Real_sub(t_50_x, v_P_x);
        nile_Real_t t_51_y = nile_Real_sub(t_50_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_51_x);
        nile_Buffer_append(out, t_51_y);
        nile_Real_t t_53 = 1;
        nile_Real_t t_54 = nile_Real_sub(v_x, t_53);
        nile_Real_t t_55 = 1;
        nile_Real_t t_56 = nile_Real_add(v_y, t_55);
        nile_Real_t t_52_1 = t_54;
        nile_Real_t t_52_2 = t_56;
        nile_Real_t t_57_x = t_52_1;
        nile_Real_t t_57_y = t_52_2;
        nile_Real_t t_58_x = nile_Real_sub(t_57_x, v_P_x);
        nile_Real_t t_58_y = nile_Real_sub(t_57_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_58_x);
        nile_Buffer_append(out, t_58_y);
        nile_Real_t t_60 = 1;
        nile_Real_t t_61 = nile_Real_add(v_y, t_60);
        nile_Real_t t_59_1 = v_x;
        nile_Real_t t_59_2 = t_61;
        nile_Real_t t_62_x = t_59_1;
        nile_Real_t t_62_y = t_59_2;
        nile_Real_t t_63_x = nile_Real_sub(t_62_x, v_P_x);
        nile_Real_t t_63_y = nile_Real_sub(t_62_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_63_x);
        nile_Buffer_append(out, t_63_y);
        nile_Real_t t_65 = 1;
        nile_Real_t t_66 = nile_Real_add(v_x, t_65);
        nile_Real_t t_67 = 1;
        nile_Real_t t_68 = nile_Real_add(v_y, t_67);
        nile_Real_t t_64_1 = t_66;
        nile_Real_t t_64_2 = t_68;
        nile_Real_t t_69_x = t_64_1;
        nile_Real_t t_69_y = t_64_2;
        nile_Real_t t_70_x = nile_Real_sub(t_69_x, v_P_x);
        nile_Real_t t_70_y = nile_Real_sub(t_69_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_70_x);
        nile_Buffer_append(out, t_70_y);
        nile_Real_t t_72 = 2;
        nile_Real_t t_73 = nile_Real_add(v_x, t_72);
        nile_Real_t t_74 = 1;
        nile_Real_t t_75 = nile_Real_add(v_y, t_74);
        nile_Real_t t_71_1 = t_73;
        nile_Real_t t_71_2 = t_75;
        nile_Real_t t_76_x = t_71_1;
        nile_Real_t t_76_y = t_71_2;
        nile_Real_t t_77_x = nile_Real_sub(t_76_x, v_P_x);
        nile_Real_t t_77_y = nile_Real_sub(t_76_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_77_x);
        nile_Buffer_append(out, t_77_y);
        nile_Real_t t_79 = 1;
        nile_Real_t t_80 = nile_Real_sub(v_x, t_79);
        nile_Real_t t_81 = 2;
        nile_Real_t t_82 = nile_Real_add(v_y, t_81);
        nile_Real_t t_78_1 = t_80;
        nile_Real_t t_78_2 = t_82;
        nile_Real_t t_83_x = t_78_1;
        nile_Real_t t_83_y = t_78_2;
        nile_Real_t t_84_x = nile_Real_sub(t_83_x, v_P_x);
        nile_Real_t t_84_y = nile_Real_sub(t_83_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_84_x);
        nile_Buffer_append(out, t_84_y);
        nile_Real_t t_86 = 2;
        nile_Real_t t_87 = nile_Real_add(v_y, t_86);
        nile_Real_t t_85_1 = v_x;
        nile_Real_t t_85_2 = t_87;
        nile_Real_t t_88_x = t_85_1;
        nile_Real_t t_88_y = t_85_2;
        nile_Real_t t_89_x = nile_Real_sub(t_88_x, v_P_x);
        nile_Real_t t_89_y = nile_Real_sub(t_88_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_89_x);
        nile_Buffer_append(out, t_89_y);
        nile_Real_t t_91 = 1;
        nile_Real_t t_92 = nile_Real_add(v_x, t_91);
        nile_Real_t t_93 = 2;
        nile_Real_t t_94 = nile_Real_add(v_y, t_93);
        nile_Real_t t_90_1 = t_92;
        nile_Real_t t_90_2 = t_94;
        nile_Real_t t_95_x = t_90_1;
        nile_Real_t t_95_y = t_90_2;
        nile_Real_t t_96_x = nile_Real_sub(t_95_x, v_P_x);
        nile_Real_t t_96_y = nile_Real_sub(t_95_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_96_x);
        nile_Buffer_append(out, t_96_y);
        nile_Real_t t_98 = 2;
        nile_Real_t t_99 = nile_Real_add(v_x, t_98);
        nile_Real_t t_100 = 2;
        nile_Real_t t_101 = nile_Real_add(v_y, t_100);
        nile_Real_t t_97_1 = t_99;
        nile_Real_t t_97_2 = t_101;
        nile_Real_t t_102_x = t_97_1;
        nile_Real_t t_102_y = t_97_2;
        nile_Real_t t_103_x = nile_Real_sub(t_102_x, v_P_x);
        nile_Real_t t_103_y = nile_Real_sub(t_102_y, v_P_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_103_x);
        nile_Buffer_append(out, t_103_y);
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
    nile_Kernel_t *v_s;
} gezira_BicubicFilter_t;

static nile_Kernel_t *gezira_BicubicFilter_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_BicubicFilter_t *k = (gezira_BicubicFilter_t *) k_;
    gezira_BicubicFilter_t *clone = (gezira_BicubicFilter_t *) nile_Kernel_clone(nl, k_);
    clone->v_s = k->v_s->clone(nl, k->v_s);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_BicubicFilter(nile_t *nl, 
                                    nile_Kernel_t *v_s) {
    gezira_BicubicFilter_t *k = NILE_KERNEL_NEW(nl, gezira_BicubicFilter);
    k->v_s = v_s;
    return (nile_Kernel_t *) k;
}

static int gezira_BicubicFilter_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_BicubicFilter_t *k = (gezira_BicubicFilter_t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        ; /* no-op */
        nile_Kernel_t *t_1 = nile_Pipeline(nl, gezira_BicubicFilterPoints(nl), v_s, NULL);
        nile_Real_t t_2 = 4;
        nile_Kernel_t *t_3 = nile_Pipeline(nl, gezira_BicubicFilterDeltas(nl), gezira_KeysWeights(nl), NULL);
        nile_Real_t t_4 = 1;
        nile_Kernel_t *t_5 = nile_Interleave(nl, t_1, t_2, t_3, t_4);
        nile_Real_t t_6 = 16;
        nile_Kernel_t *t_7 = gezira_SumWeightedColors(nl, t_6);
        nile_Kernel_t *t_8 = nile_Pipeline(nl, t_5, t_7, NULL);
        nile_Kernel_t *f = t_8;
        f->downstream = k_->downstream;
        k_->downstream = f;
    }
    
    return NILE_INPUT_FORWARD;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

nile_Kernel_t *gezira_GradientShape_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientShape_t *k = (gezira_GradientShape_t *) k_;
    gezira_GradientShape_t *clone = (gezira_GradientShape_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientExtendMode_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientExtendMode_t *k = (gezira_GradientExtendMode_t *) k_;
    gezira_GradientExtendMode_t *clone = (gezira_GradientExtendMode_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientColor_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientColor_t *k = (gezira_GradientColor_t *) k_;
    gezira_GradientColor_t *clone = (gezira_GradientColor_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_s00;
    nile_Real_t v_dsdx;
    nile_Real_t v_dsdy;
} gezira_LinearGradientShape_t;

static nile_Kernel_t *gezira_LinearGradientShape_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_LinearGradientShape_t *k = (gezira_LinearGradientShape_t *) k_;
    gezira_LinearGradientShape_t *clone = (gezira_LinearGradientShape_t *) nile_Kernel_clone(nl, k_);
    clone->v_s00 = k->v_s00;
    clone->v_dsdx = k->v_dsdx;
    clone->v_dsdy = k->v_dsdy;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_LinearGradientShape(nile_t *nl, 
                                          nile_Real_t v_s00, 
                                          nile_Real_t v_dsdx, 
                                          nile_Real_t v_dsdy) {
    gezira_LinearGradientShape_t *k = NILE_KERNEL_NEW(nl, gezira_LinearGradientShape);
    k->v_s00 = v_s00;
    k->v_dsdx = v_dsdx;
    k->v_dsdy = v_dsdy;
    return (nile_Kernel_t *) k;
}

static int gezira_LinearGradientShape_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_LinearGradientShape_t *k = (gezira_LinearGradientShape_t *) k_;
    nile_Real_t v_s00 = k->v_s00;
    nile_Real_t v_dsdx = k->v_dsdx;
    nile_Real_t v_dsdy = k->v_dsdy;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_x = nile_Buffer_shift(in);
        nile_Real_t v_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = nile_Real_mul(v_x, v_dsdx);
        nile_Real_t t_2 = nile_Real_add(v_s00, t_1);
        nile_Real_t t_3 = nile_Real_mul(v_y, v_dsdy);
        nile_Real_t t_4 = nile_Real_add(t_2, t_3);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_4);
    }
    
    if (in->eos) {
    }
    else {
        k->v_s00 = v_s00;
        k->v_dsdx = v_dsdx;
        k->v_dsdy = v_dsdy;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_C_x;
    nile_Real_t v_C_y;
    nile_Real_t v_r;
} gezira_RadialGradientShape_t;

static nile_Kernel_t *gezira_RadialGradientShape_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_RadialGradientShape_t *k = (gezira_RadialGradientShape_t *) k_;
    gezira_RadialGradientShape_t *clone = (gezira_RadialGradientShape_t *) nile_Kernel_clone(nl, k_);
    clone->v_C_x = k->v_C_x;
    clone->v_C_y = k->v_C_y;
    clone->v_r = k->v_r;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_RadialGradientShape(nile_t *nl, 
                                          nile_Real_t v_C_x, 
                                          nile_Real_t v_C_y, 
                                          nile_Real_t v_r) {
    gezira_RadialGradientShape_t *k = NILE_KERNEL_NEW(nl, gezira_RadialGradientShape);
    k->v_C_x = v_C_x;
    k->v_C_y = v_C_y;
    k->v_r = v_r;
    return (nile_Kernel_t *) k;
}

static int gezira_RadialGradientShape_process(nile_t *nl,
                                              nile_Kernel_t *k_,
                                              nile_Buffer_t **in_,
                                              nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_RadialGradientShape_t *k = (gezira_RadialGradientShape_t *) k_;
    nile_Real_t v_C_x = k->v_C_x;
    nile_Real_t v_C_y = k->v_C_y;
    nile_Real_t v_r = k->v_r;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1_x = nile_Real_sub(v_P_x, v_C_x);
        nile_Real_t t_1_y = nile_Real_sub(v_P_y, v_C_y);
        nile_Real_t t_2_x = t_1_x;
        nile_Real_t t_2_y = t_1_y;
        nile_Real_t t_3 = nile_Real_mul(t_2_x, t_2_x);
        nile_Real_t t_4 = nile_Real_mul(t_2_y, t_2_y);
        nile_Real_t t_5 = nile_Real_add(t_3, t_4);
        nile_Real_t t_6 = nile_Real_sqr(t_5);
        nile_Real_t t_7 = nile_Real_div(t_6, v_r);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_7);
    }
    
    if (in->eos) {
    }
    else {
        k->v_C_x = v_C_x;
        k->v_C_y = v_C_y;
        k->v_r = v_r;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
} gezira_GradientExtendPad_t;

static nile_Kernel_t *gezira_GradientExtendPad_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientExtendPad_t *k = (gezira_GradientExtendPad_t *) k_;
    gezira_GradientExtendPad_t *clone = (gezira_GradientExtendPad_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientExtendPad(nile_t *nl) {
    gezira_GradientExtendPad_t *k = NILE_KERNEL_NEW(nl, gezira_GradientExtendPad);
    return (nile_Kernel_t *) k;
}

static int gezira_GradientExtendPad_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 1
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientExtendPad_t *k = (gezira_GradientExtendPad_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_s = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0;
        nile_Real_t t_2 = nile_Real_gt(t_1, v_s);
        nile_Real_t t_3 = t_2 ? t_1 : v_s;
        nile_Real_t t_4 = 1;
        nile_Real_t t_5 = nile_Real_lt(t_3, t_4);
        nile_Real_t t_6 = t_5 ? t_3 : t_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_6);
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
} gezira_GradientExtendRepeat_t;

static nile_Kernel_t *gezira_GradientExtendRepeat_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientExtendRepeat_t *k = (gezira_GradientExtendRepeat_t *) k_;
    gezira_GradientExtendRepeat_t *clone = (gezira_GradientExtendRepeat_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientExtendRepeat(nile_t *nl) {
    gezira_GradientExtendRepeat_t *k = NILE_KERNEL_NEW(nl, gezira_GradientExtendRepeat);
    return (nile_Kernel_t *) k;
}

static int gezira_GradientExtendRepeat_process(nile_t *nl,
                                               nile_Kernel_t *k_,
                                               nile_Buffer_t **in_,
                                               nile_Buffer_t **out_) {
    #define IN_QUANTUM 1
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientExtendRepeat_t *k = (gezira_GradientExtendRepeat_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_s = nile_Buffer_shift(in);
        nile_Real_t t_1 = nile_Real_flr(v_s);
        nile_Real_t t_2 = nile_Real_sub(v_s, t_1);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_2);
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
} gezira_GradientExtendReflect_t;

static nile_Kernel_t *gezira_GradientExtendReflect_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientExtendReflect_t *k = (gezira_GradientExtendReflect_t *) k_;
    gezira_GradientExtendReflect_t *clone = (gezira_GradientExtendReflect_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientExtendReflect(nile_t *nl) {
    gezira_GradientExtendReflect_t *k = NILE_KERNEL_NEW(nl, gezira_GradientExtendReflect);
    return (nile_Kernel_t *) k;
}

static int gezira_GradientExtendReflect_process(nile_t *nl,
                                                nile_Kernel_t *k_,
                                                nile_Buffer_t **in_,
                                                nile_Buffer_t **out_) {
    #define IN_QUANTUM 1
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientExtendReflect_t *k = (gezira_GradientExtendReflect_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_s = nile_Buffer_shift(in);
        nile_Real_t t_1 = 1;
        nile_Real_t t_2 = nile_Real_sub(v_s, t_1);
        nile_Real_t t_3 = 0;
        nile_Real_t t_4 = nile_Real_lt(t_2, t_3);
        nile_Real_t t_5 = nile_Real_neg(t_2);
        nile_Real_t t_6 = t_4 ? t_5 : t_2;
        nile_Real_t t_7 = 2;
        nile_Real_t t_8 = 1;
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_neq(t_7, t_9);
        nile_Real_t t_11 = t_10 ? t_7 : t_8;
        nile_Real_t t_12 = nile_Real_div(t_6, t_11);
        nile_Real_t t_13 = nile_Real_flr(t_12);
        nile_Real_t t_14 = nile_Real_mul(t_13, t_7);
        nile_Real_t t_15 = nile_Real_sub(t_6, t_14);
        nile_Real_t t_16 = 1;
        nile_Real_t t_17 = nile_Real_sub(t_15, t_16);
        nile_Real_t t_18 = 0;
        nile_Real_t t_19 = nile_Real_lt(t_17, t_18);
        nile_Real_t t_20 = nile_Real_neg(t_17);
        nile_Real_t t_21 = t_19 ? t_20 : t_17;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_21);
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
} gezira_GradientColorBegin_t;

static nile_Kernel_t *gezira_GradientColorBegin_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientColorBegin_t *k = (gezira_GradientColorBegin_t *) k_;
    gezira_GradientColorBegin_t *clone = (gezira_GradientColorBegin_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientColorBegin(nile_t *nl) {
    gezira_GradientColorBegin_t *k = NILE_KERNEL_NEW(nl, gezira_GradientColorBegin);
    return (nile_Kernel_t *) k;
}

static int gezira_GradientColorBegin_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 1
    #define OUT_QUANTUM 5
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientColorBegin_t *k = (gezira_GradientColorBegin_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_s = nile_Buffer_shift(in);
        nile_Real_t t_2 = 0;
        nile_Real_t t_1_1 = v_s;
        nile_Real_t t_1_2 = t_2;
        nile_Real_t t_3_1 = t_1_1;
        nile_Real_t t_3_2_a = t_1_2;
        nile_Real_t t_3_2_r = t_1_2;
        nile_Real_t t_3_2_g = t_1_2;
        nile_Real_t t_3_2_b = t_1_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_3_1);
        nile_Buffer_append(out, t_3_2_a);
        nile_Buffer_append(out, t_3_2_r);
        nile_Buffer_append(out, t_3_2_g);
        nile_Buffer_append(out, t_3_2_b);
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
    nile_Real_t v_c0_a;
    nile_Real_t v_c0_r;
    nile_Real_t v_c0_g;
    nile_Real_t v_c0_b;
    nile_Real_t v_dcds_a;
    nile_Real_t v_dcds_r;
    nile_Real_t v_dcds_g;
    nile_Real_t v_dcds_b;
    nile_Real_t v_l;
} gezira_GradientColorSpan_t;

static nile_Kernel_t *gezira_GradientColorSpan_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientColorSpan_t *k = (gezira_GradientColorSpan_t *) k_;
    gezira_GradientColorSpan_t *clone = (gezira_GradientColorSpan_t *) nile_Kernel_clone(nl, k_);
    clone->v_c0_a = k->v_c0_a;
    clone->v_c0_r = k->v_c0_r;
    clone->v_c0_g = k->v_c0_g;
    clone->v_c0_b = k->v_c0_b;
    clone->v_dcds_a = k->v_dcds_a;
    clone->v_dcds_r = k->v_dcds_r;
    clone->v_dcds_g = k->v_dcds_g;
    clone->v_dcds_b = k->v_dcds_b;
    clone->v_l = k->v_l;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientColorSpan(nile_t *nl, 
                                        nile_Real_t v_c0_a, 
                                        nile_Real_t v_c0_r, 
                                        nile_Real_t v_c0_g, 
                                        nile_Real_t v_c0_b, 
                                        nile_Real_t v_dcds_a, 
                                        nile_Real_t v_dcds_r, 
                                        nile_Real_t v_dcds_g, 
                                        nile_Real_t v_dcds_b, 
                                        nile_Real_t v_l) {
    gezira_GradientColorSpan_t *k = NILE_KERNEL_NEW(nl, gezira_GradientColorSpan);
    k->v_c0_a = v_c0_a;
    k->v_c0_r = v_c0_r;
    k->v_c0_g = v_c0_g;
    k->v_c0_b = v_c0_b;
    k->v_dcds_a = v_dcds_a;
    k->v_dcds_r = v_dcds_r;
    k->v_dcds_g = v_dcds_g;
    k->v_dcds_b = v_dcds_b;
    k->v_l = v_l;
    return (nile_Kernel_t *) k;
}

static int gezira_GradientColorSpan_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 5
    #define OUT_QUANTUM 5
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientColorSpan_t *k = (gezira_GradientColorSpan_t *) k_;
    nile_Real_t v_c0_a = k->v_c0_a;
    nile_Real_t v_c0_r = k->v_c0_r;
    nile_Real_t v_c0_g = k->v_c0_g;
    nile_Real_t v_c0_b = k->v_c0_b;
    nile_Real_t v_dcds_a = k->v_dcds_a;
    nile_Real_t v_dcds_r = k->v_dcds_r;
    nile_Real_t v_dcds_g = k->v_dcds_g;
    nile_Real_t v_dcds_b = k->v_dcds_b;
    nile_Real_t v_l = k->v_l;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_s = nile_Buffer_shift(in);
        nile_Real_t v_c_a = nile_Buffer_shift(in);
        nile_Real_t v_c_r = nile_Buffer_shift(in);
        nile_Real_t v_c_g = nile_Buffer_shift(in);
        nile_Real_t v_c_b = nile_Buffer_shift(in);
        nile_Real_t t_1_a = v_s;
        nile_Real_t t_1_r = v_s;
        nile_Real_t t_1_g = v_s;
        nile_Real_t t_1_b = v_s;
        nile_Real_t t_2_a = nile_Real_mul(t_1_a, v_dcds_a);
        nile_Real_t t_2_r = nile_Real_mul(t_1_r, v_dcds_r);
        nile_Real_t t_2_g = nile_Real_mul(t_1_g, v_dcds_g);
        nile_Real_t t_2_b = nile_Real_mul(t_1_b, v_dcds_b);
        nile_Real_t t_3_a = nile_Real_add(v_c0_a, t_2_a);
        nile_Real_t t_3_r = nile_Real_add(v_c0_r, t_2_r);
        nile_Real_t t_3_g = nile_Real_add(v_c0_g, t_2_g);
        nile_Real_t t_3_b = nile_Real_add(v_c0_b, t_2_b);
        nile_Real_t v_d_a = t_3_a;
        nile_Real_t v_d_r = t_3_r;
        nile_Real_t v_d_g = t_3_g;
        nile_Real_t v_d_b = t_3_b;
        nile_Real_t t_5 = nile_Real_sub(v_s, v_l);
        nile_Real_t t_6 = 0;
        nile_Real_t t_7 = nile_Real_lt(v_s, t_6);
        nile_Real_t t_8_a = t_7;
        nile_Real_t t_8_r = t_7;
        nile_Real_t t_8_g = t_7;
        nile_Real_t t_8_b = t_7;
        nile_Real_t t_9_a = t_8_a ? v_c_a : v_d_a;
        nile_Real_t t_9_r = t_8_r ? v_c_r : v_d_r;
        nile_Real_t t_9_g = t_8_g ? v_c_g : v_d_g;
        nile_Real_t t_9_b = t_8_b ? v_c_b : v_d_b;
        nile_Real_t t_4_1 = t_5;
        nile_Real_t t_4_2_a = t_9_a;
        nile_Real_t t_4_2_r = t_9_r;
        nile_Real_t t_4_2_g = t_9_g;
        nile_Real_t t_4_2_b = t_9_b;
        nile_Real_t t_10_1 = t_4_1;
        nile_Real_t t_10_2_a = t_4_2_a;
        nile_Real_t t_10_2_r = t_4_2_r;
        nile_Real_t t_10_2_g = t_4_2_g;
        nile_Real_t t_10_2_b = t_4_2_b;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_10_1);
        nile_Buffer_append(out, t_10_2_a);
        nile_Buffer_append(out, t_10_2_r);
        nile_Buffer_append(out, t_10_2_g);
        nile_Buffer_append(out, t_10_2_b);
    }
    
    if (in->eos) {
    }
    else {
        k->v_c0_a = v_c0_a;
        k->v_c0_r = v_c0_r;
        k->v_c0_g = v_c0_g;
        k->v_c0_b = v_c0_b;
        k->v_dcds_a = v_dcds_a;
        k->v_dcds_r = v_dcds_r;
        k->v_dcds_g = v_dcds_g;
        k->v_dcds_b = v_dcds_b;
        k->v_l = v_l;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
} gezira_GradientColorEnd_t;

static nile_Kernel_t *gezira_GradientColorEnd_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_GradientColorEnd_t *k = (gezira_GradientColorEnd_t *) k_;
    gezira_GradientColorEnd_t *clone = (gezira_GradientColorEnd_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_GradientColorEnd(nile_t *nl) {
    gezira_GradientColorEnd_t *k = NILE_KERNEL_NEW(nl, gezira_GradientColorEnd);
    return (nile_Kernel_t *) k;
}

static int gezira_GradientColorEnd_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 5
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_GradientColorEnd_t *k = (gezira_GradientColorEnd_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t t_1;
        t_1 = nile_Buffer_shift(in);
        nile_Real_t v_c_a = nile_Buffer_shift(in);
        nile_Real_t v_c_r = nile_Buffer_shift(in);
        nile_Real_t v_c_g = nile_Buffer_shift(in);
        nile_Real_t v_c_b = nile_Buffer_shift(in);
        nile_Real_t t_3 = nile_Real_mul(v_c_a, v_c_r);
        nile_Real_t t_4 = nile_Real_mul(v_c_a, v_c_g);
        nile_Real_t t_5 = nile_Real_mul(v_c_a, v_c_b);
        nile_Real_t t_2_1 = v_c_a;
        nile_Real_t t_2_2 = t_3;
        nile_Real_t t_2_3 = t_4;
        nile_Real_t t_2_4 = t_5;
        nile_Real_t t_6_a = t_2_1;
        nile_Real_t t_6_r = t_2_2;
        nile_Real_t t_6_g = t_2_3;
        nile_Real_t t_6_b = t_2_4;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_6_a);
        nile_Buffer_append(out, t_6_r);
        nile_Buffer_append(out, t_6_g);
        nile_Buffer_append(out, t_6_b);
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
    nile_Kernel_t *v_s;
    nile_Kernel_t *v_m;
    nile_Kernel_t *v_c;
} gezira_Gradient_t;

static nile_Kernel_t *gezira_Gradient_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Gradient_t *k = (gezira_Gradient_t *) k_;
    gezira_Gradient_t *clone = (gezira_Gradient_t *) nile_Kernel_clone(nl, k_);
    clone->v_s = k->v_s->clone(nl, k->v_s);
    clone->v_m = k->v_m->clone(nl, k->v_m);
    clone->v_c = k->v_c->clone(nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_Gradient(nile_t *nl, 
                               nile_Kernel_t *v_s, 
                               nile_Kernel_t *v_m, 
                               nile_Kernel_t *v_c) {
    gezira_Gradient_t *k = NILE_KERNEL_NEW(nl, gezira_Gradient);
    k->v_s = v_s;
    k->v_m = v_m;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

static int gezira_Gradient_process(nile_t *nl,
                                   nile_Kernel_t *k_,
                                   nile_Buffer_t **in_,
                                   nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_Gradient_t *k = (gezira_Gradient_t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    nile_Kernel_t *v_m = k->v_m;
    nile_Kernel_t *v_c = k->v_c;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        ; /* no-op */
        nile_Kernel_t *t_1 = nile_Pipeline(nl, v_c, gezira_GradientColorEnd(nl), NULL);
        nile_Kernel_t *t_2 = nile_Pipeline(nl, gezira_GradientColorBegin(nl), t_1, NULL);
        nile_Kernel_t *t_3 = nile_Pipeline(nl, v_m, t_2, NULL);
        nile_Kernel_t *t_4 = nile_Pipeline(nl, v_s, t_3, NULL);
        nile_Kernel_t *f = t_4;
        f->downstream = k_->downstream;
        k_->downstream = f;
    }
    
    return NILE_INPUT_FORWARD;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

nile_Kernel_t *gezira_ImageExtendMode_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_ImageExtendMode_t *k = (gezira_ImageExtendMode_t *) k_;
    gezira_ImageExtendMode_t *clone = (gezira_ImageExtendMode_t *) nile_Kernel_clone(nl, k_);
    clone->v_D_x = k->v_D_x;
    clone->v_D_y = k->v_D_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_ImageExtendMode(nile_t *nl, 
                                      nile_Kernel_t *k_, 
                                      nile_Real_t v_D_x, 
                                      nile_Real_t v_D_y) {
    gezira_ImageExtendMode_t *k = (gezira_ImageExtendMode_t *) k_;
    k->v_D_x = v_D_x;
    k->v_D_y = v_D_y;
    return (nile_Kernel_t *) k;
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendPad_t;

static nile_Kernel_t *gezira_ImageExtendPad_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_ImageExtendPad_t *k = (gezira_ImageExtendPad_t *) k_;
    gezira_ImageExtendPad_t *clone = (gezira_ImageExtendPad_t *) nile_Kernel_clone(nl, k_);
    clone->v_D_x = k->v_D_x;
    clone->v_D_y = k->v_D_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_ImageExtendPad(nile_t *nl, 
                                     nile_Real_t v_D_x, 
                                     nile_Real_t v_D_y) {
    gezira_ImageExtendPad_t *k = NILE_KERNEL_NEW(nl, gezira_ImageExtendPad);
    k->v_D_x = v_D_x;
    k->v_D_y = v_D_y;
    return (nile_Kernel_t *) k;
}

static int gezira_ImageExtendPad_process(nile_t *nl,
                                         nile_Kernel_t *k_,
                                         nile_Buffer_t **in_,
                                         nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_ImageExtendPad_t *k = (gezira_ImageExtendPad_t *) k_;
    nile_Real_t v_D_x = k->v_D_x;
    nile_Real_t v_D_y = k->v_D_y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1 = 0;
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3 = nile_Real_gt(t_2_x, v_P_x);
        nile_Real_t t_4 = t_3 ? t_2_x : v_P_x;
        nile_Real_t t_5 = nile_Real_gt(t_2_y, v_P_y);
        nile_Real_t t_6 = t_5 ? t_2_y : v_P_y;
        nile_Real_t t_7_1 = t_4;
        nile_Real_t t_7_2 = t_6;
        nile_Real_t t_8_x = t_7_1;
        nile_Real_t t_8_y = t_7_2;
        nile_Real_t t_9 = nile_Real_lt(t_8_x, v_D_x);
        nile_Real_t t_10 = t_9 ? t_8_x : v_D_x;
        nile_Real_t t_11 = nile_Real_lt(t_8_y, v_D_y);
        nile_Real_t t_12 = t_11 ? t_8_y : v_D_y;
        nile_Real_t t_13_1 = t_10;
        nile_Real_t t_13_2 = t_12;
        nile_Real_t t_14_x = t_13_1;
        nile_Real_t t_14_y = t_13_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_14_x);
        nile_Buffer_append(out, t_14_y);
    }
    
    if (in->eos) {
    }
    else {
        k->v_D_x = v_D_x;
        k->v_D_y = v_D_y;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendRepeat_t;

static nile_Kernel_t *gezira_ImageExtendRepeat_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_ImageExtendRepeat_t *k = (gezira_ImageExtendRepeat_t *) k_;
    gezira_ImageExtendRepeat_t *clone = (gezira_ImageExtendRepeat_t *) nile_Kernel_clone(nl, k_);
    clone->v_D_x = k->v_D_x;
    clone->v_D_y = k->v_D_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_ImageExtendRepeat(nile_t *nl, 
                                        nile_Real_t v_D_x, 
                                        nile_Real_t v_D_y) {
    gezira_ImageExtendRepeat_t *k = NILE_KERNEL_NEW(nl, gezira_ImageExtendRepeat);
    k->v_D_x = v_D_x;
    k->v_D_y = v_D_y;
    return (nile_Kernel_t *) k;
}

static int gezira_ImageExtendRepeat_process(nile_t *nl,
                                            nile_Kernel_t *k_,
                                            nile_Buffer_t **in_,
                                            nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_ImageExtendRepeat_t *k = (gezira_ImageExtendRepeat_t *) k_;
    nile_Real_t v_D_x = k->v_D_x;
    nile_Real_t v_D_y = k->v_D_y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1_x = nile_Real_div(v_P_x, v_D_x);
        nile_Real_t t_1_y = nile_Real_div(v_P_y, v_D_y);
        nile_Real_t v_Q_x = t_1_x;
        nile_Real_t v_Q_y = t_1_y;
        nile_Real_t t_2_x = nile_Real_flr(v_Q_x);
        nile_Real_t t_2_y = nile_Real_flr(v_Q_y);
        nile_Real_t t_3_x = nile_Real_sub(v_Q_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_Q_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_mul(t_3_x, v_D_x);
        nile_Real_t t_4_y = nile_Real_mul(t_3_y, v_D_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_4_x);
        nile_Buffer_append(out, t_4_y);
    }
    
    if (in->eos) {
    }
    else {
        k->v_D_x = v_D_x;
        k->v_D_y = v_D_y;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendReflect_t;

static nile_Kernel_t *gezira_ImageExtendReflect_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_ImageExtendReflect_t *k = (gezira_ImageExtendReflect_t *) k_;
    gezira_ImageExtendReflect_t *clone = (gezira_ImageExtendReflect_t *) nile_Kernel_clone(nl, k_);
    clone->v_D_x = k->v_D_x;
    clone->v_D_y = k->v_D_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_ImageExtendReflect(nile_t *nl, 
                                         nile_Real_t v_D_x, 
                                         nile_Real_t v_D_y) {
    gezira_ImageExtendReflect_t *k = NILE_KERNEL_NEW(nl, gezira_ImageExtendReflect);
    k->v_D_x = v_D_x;
    k->v_D_y = v_D_y;
    return (nile_Kernel_t *) k;
}

static int gezira_ImageExtendReflect_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 2
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_ImageExtendReflect_t *k = (gezira_ImageExtendReflect_t *) k_;
    nile_Real_t v_D_x = k->v_D_x;
    nile_Real_t v_D_y = k->v_D_y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_P_x = nile_Buffer_shift(in);
        nile_Real_t v_P_y = nile_Buffer_shift(in);
        nile_Real_t t_1_x = nile_Real_div(v_P_x, v_D_x);
        nile_Real_t t_1_y = nile_Real_div(v_P_y, v_D_y);
        nile_Real_t v_Q_x = t_1_x;
        nile_Real_t v_Q_y = t_1_y;
        nile_Real_t t_2 = 1;
        nile_Real_t t_3_x = t_2;
        nile_Real_t t_3_y = t_2;
        nile_Real_t t_4_x = nile_Real_sub(v_Q_x, t_3_x);
        nile_Real_t t_4_y = nile_Real_sub(v_Q_y, t_3_y);
        nile_Real_t t_5 = 0;
        nile_Real_t t_6 = nile_Real_lt(t_4_x, t_5);
        nile_Real_t t_7 = nile_Real_neg(t_4_x);
        nile_Real_t t_8 = t_6 ? t_7 : t_4_x;
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_lt(t_4_y, t_9);
        nile_Real_t t_11 = nile_Real_neg(t_4_y);
        nile_Real_t t_12 = t_10 ? t_11 : t_4_y;
        nile_Real_t t_13_1 = t_8;
        nile_Real_t t_13_2 = t_12;
        nile_Real_t t_14_x = t_13_1;
        nile_Real_t t_14_y = t_13_2;
        nile_Real_t t_15 = 2;
        nile_Real_t t_16_x = t_15;
        nile_Real_t t_16_y = t_15;
        nile_Real_t t_17 = 1;
        nile_Real_t t_18 = 0;
        nile_Real_t t_19 = nile_Real_neq(t_16_x, t_18);
        nile_Real_t t_20 = t_19 ? t_16_x : t_17;
        nile_Real_t t_21 = nile_Real_div(t_14_x, t_20);
        nile_Real_t t_22 = nile_Real_flr(t_21);
        nile_Real_t t_23 = nile_Real_mul(t_22, t_16_x);
        nile_Real_t t_24 = nile_Real_sub(t_14_x, t_23);
        nile_Real_t t_25 = 1;
        nile_Real_t t_26 = 0;
        nile_Real_t t_27 = nile_Real_neq(t_16_y, t_26);
        nile_Real_t t_28 = t_27 ? t_16_y : t_25;
        nile_Real_t t_29 = nile_Real_div(t_14_y, t_28);
        nile_Real_t t_30 = nile_Real_flr(t_29);
        nile_Real_t t_31 = nile_Real_mul(t_30, t_16_y);
        nile_Real_t t_32 = nile_Real_sub(t_14_y, t_31);
        nile_Real_t t_33_1 = t_24;
        nile_Real_t t_33_2 = t_32;
        nile_Real_t t_34_x = t_33_1;
        nile_Real_t t_34_y = t_33_2;
        nile_Real_t t_35 = 1;
        nile_Real_t t_36_x = t_35;
        nile_Real_t t_36_y = t_35;
        nile_Real_t t_37_x = nile_Real_sub(t_34_x, t_36_x);
        nile_Real_t t_37_y = nile_Real_sub(t_34_y, t_36_y);
        nile_Real_t t_38 = 0;
        nile_Real_t t_39 = nile_Real_lt(t_37_x, t_38);
        nile_Real_t t_40 = nile_Real_neg(t_37_x);
        nile_Real_t t_41 = t_39 ? t_40 : t_37_x;
        nile_Real_t t_42 = 0;
        nile_Real_t t_43 = nile_Real_lt(t_37_y, t_42);
        nile_Real_t t_44 = nile_Real_neg(t_37_y);
        nile_Real_t t_45 = t_43 ? t_44 : t_37_y;
        nile_Real_t t_46_1 = t_41;
        nile_Real_t t_46_2 = t_45;
        nile_Real_t t_47_x = t_46_1;
        nile_Real_t t_47_y = t_46_2;
        nile_Real_t t_48_x = nile_Real_mul(t_47_x, v_D_x);
        nile_Real_t t_48_y = nile_Real_mul(t_47_y, v_D_y);
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_48_x);
        nile_Buffer_append(out, t_48_y);
    }
    
    if (in->eos) {
    }
    else {
        k->v_D_x = v_D_x;
        k->v_D_y = v_D_y;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

nile_Kernel_t *gezira_Canvas_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
    gezira_Canvas_t *clone = (gezira_Canvas_t *) nile_Kernel_clone(nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_Canvas(nile_t *nl, 
                             nile_Kernel_t *k_, 
                             nile_Real_t v_start_x, 
                             nile_Real_t v_start_y) {
    gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return (nile_Kernel_t *) k;
}

typedef struct {
    nile_Kernel_t base;
} gezira_DecomposeBeziers_t;

static nile_Kernel_t *gezira_DecomposeBeziers_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_DecomposeBeziers_t *k = (gezira_DecomposeBeziers_t *) k_;
    gezira_DecomposeBeziers_t *clone = (gezira_DecomposeBeziers_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_DecomposeBeziers(nile_t *nl) {
    gezira_DecomposeBeziers_t *k = NILE_KERNEL_NEW(nl, gezira_DecomposeBeziers);
    return (nile_Kernel_t *) k;
}

static int gezira_DecomposeBeziers_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_DecomposeBeziers_t *k = (gezira_DecomposeBeziers_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_1_x = nile_Real_flr(v_A_x);
        nile_Real_t t_1_y = nile_Real_flr(v_A_y);
        nile_Real_t t_2_x = nile_Real_flr(v_C_x);
        nile_Real_t t_2_y = nile_Real_flr(v_C_y);
        nile_Real_t t_3_x = nile_Real_eq(t_1_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_eq(t_1_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_clg(v_A_x);
        nile_Real_t t_4_y = nile_Real_clg(v_A_y);
        nile_Real_t t_5_x = nile_Real_clg(v_C_x);
        nile_Real_t t_5_y = nile_Real_clg(v_C_y);
        nile_Real_t t_6_x = nile_Real_eq(t_4_x, t_5_x);
        nile_Real_t t_6_y = nile_Real_eq(t_4_y, t_5_y);
        nile_Real_t t_7_x = nile_Real_or(t_3_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_or(t_3_y, t_6_y);
        nile_Real_t v_inside_x = t_7_x;
        nile_Real_t v_inside_y = t_7_y;
        nile_Real_t t_8 = nile_Real_and(v_inside_x, v_inside_y);
        if (t_8) {
            nile_Real_t t_9_x = nile_Real_flr(v_A_x);
            nile_Real_t t_9_y = nile_Real_flr(v_A_y);
            nile_Real_t t_10_x = nile_Real_flr(v_C_x);
            nile_Real_t t_10_y = nile_Real_flr(v_C_y);
            nile_Real_t t_11 = nile_Real_lt(t_9_x, t_10_x);
            nile_Real_t t_12 = t_11 ? t_9_x : t_10_x;
            nile_Real_t t_13 = nile_Real_lt(t_9_y, t_10_y);
            nile_Real_t t_14 = t_13 ? t_9_y : t_10_y;
            nile_Real_t t_15_1 = t_12;
            nile_Real_t t_15_2 = t_14;
            nile_Real_t t_16_x = t_15_1;
            nile_Real_t t_16_y = t_15_2;
            nile_Real_t v_P_x = t_16_x;
            nile_Real_t v_P_y = t_16_y;
            nile_Real_t t_17 = 1;
            nile_Real_t t_18 = nile_Real_add(v_P_x, t_17);
            nile_Real_t t_19 = nile_Real_add(v_C_x, v_A_x);
            nile_Real_t t_20 = 2;
            nile_Real_t t_21 = nile_Real_div(t_19, t_20);
            nile_Real_t t_22 = nile_Real_sub(t_18, t_21);
            nile_Real_t v_w = t_22;
            nile_Real_t t_23 = nile_Real_sub(v_C_y, v_A_y);
            nile_Real_t v_h = t_23;
            nile_Real_t t_24_1 = v_P_x;
            nile_Real_t t_24_2 = v_P_y;
            nile_Real_t t_24_3 = v_w;
            nile_Real_t t_24_4 = v_h;
            nile_Real_t t_25_x = t_24_1;
            nile_Real_t t_25_y = t_24_2;
            nile_Real_t t_25_w = t_24_3;
            nile_Real_t t_25_h = t_24_4;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_25_x);
            nile_Buffer_append(out, t_25_y);
            nile_Buffer_append(out, t_25_w);
            nile_Buffer_append(out, t_25_h);
        }
        else {
            nile_Real_t t_26 = nile_Real_add(v_A_x, v_B_x);
            nile_Real_t t_27 = 2;
            nile_Real_t t_28 = nile_Real_div(t_26, t_27);
            nile_Real_t t_29 = nile_Real_add(v_A_y, v_B_y);
            nile_Real_t t_30 = 2;
            nile_Real_t t_31 = nile_Real_div(t_29, t_30);
            nile_Real_t t_32_1 = t_28;
            nile_Real_t t_32_2 = t_31;
            nile_Real_t t_33_x = t_32_1;
            nile_Real_t t_33_y = t_32_2;
            nile_Real_t t_34 = nile_Real_add(v_B_x, v_C_x);
            nile_Real_t t_35 = 2;
            nile_Real_t t_36 = nile_Real_div(t_34, t_35);
            nile_Real_t t_37 = nile_Real_add(v_B_y, v_C_y);
            nile_Real_t t_38 = 2;
            nile_Real_t t_39 = nile_Real_div(t_37, t_38);
            nile_Real_t t_40_1 = t_36;
            nile_Real_t t_40_2 = t_39;
            nile_Real_t t_41_x = t_40_1;
            nile_Real_t t_41_y = t_40_2;
            nile_Real_t t_42 = nile_Real_add(t_33_x, t_41_x);
            nile_Real_t t_43 = 2;
            nile_Real_t t_44 = nile_Real_div(t_42, t_43);
            nile_Real_t t_45 = nile_Real_add(t_33_y, t_41_y);
            nile_Real_t t_46 = 2;
            nile_Real_t t_47 = nile_Real_div(t_45, t_46);
            nile_Real_t t_48_1 = t_44;
            nile_Real_t t_48_2 = t_47;
            nile_Real_t t_49_x = t_48_1;
            nile_Real_t t_49_y = t_48_2;
            nile_Real_t v_ABBC_x = t_49_x;
            nile_Real_t v_ABBC_y = t_49_y;
            nile_Real_t t_50_x = nile_Real_flr(v_ABBC_x);
            nile_Real_t t_50_y = nile_Real_flr(v_ABBC_y);
            nile_Real_t v_min_x = t_50_x;
            nile_Real_t v_min_y = t_50_y;
            nile_Real_t t_51_x = nile_Real_clg(v_ABBC_x);
            nile_Real_t t_51_y = nile_Real_clg(v_ABBC_y);
            nile_Real_t v_max_x = t_51_x;
            nile_Real_t v_max_y = t_51_y;
            nile_Real_t t_52_x = nile_Real_sub(v_ABBC_x, v_min_x);
            nile_Real_t t_52_y = nile_Real_sub(v_ABBC_y, v_min_y);
            nile_Real_t t_53 = 0;
            nile_Real_t t_54 = nile_Real_lt(t_52_x, t_53);
            nile_Real_t t_55 = nile_Real_neg(t_52_x);
            nile_Real_t t_56 = t_54 ? t_55 : t_52_x;
            nile_Real_t t_57 = 0;
            nile_Real_t t_58 = nile_Real_lt(t_52_y, t_57);
            nile_Real_t t_59 = nile_Real_neg(t_52_y);
            nile_Real_t t_60 = t_58 ? t_59 : t_52_y;
            nile_Real_t t_61_1 = t_56;
            nile_Real_t t_61_2 = t_60;
            nile_Real_t t_62_x = t_61_1;
            nile_Real_t t_62_y = t_61_2;
            nile_Real_t t_63 = 0.1;
            nile_Real_t t_64_x = t_63;
            nile_Real_t t_64_y = t_63;
            nile_Real_t t_65_x = nile_Real_lt(t_62_x, t_64_x);
            nile_Real_t t_65_y = nile_Real_lt(t_62_y, t_64_y);
            nile_Real_t v_nearmin_x = t_65_x;
            nile_Real_t v_nearmin_y = t_65_y;
            nile_Real_t t_66_x = nile_Real_sub(v_ABBC_x, v_max_x);
            nile_Real_t t_66_y = nile_Real_sub(v_ABBC_y, v_max_y);
            nile_Real_t t_67 = 0;
            nile_Real_t t_68 = nile_Real_lt(t_66_x, t_67);
            nile_Real_t t_69 = nile_Real_neg(t_66_x);
            nile_Real_t t_70 = t_68 ? t_69 : t_66_x;
            nile_Real_t t_71 = 0;
            nile_Real_t t_72 = nile_Real_lt(t_66_y, t_71);
            nile_Real_t t_73 = nile_Real_neg(t_66_y);
            nile_Real_t t_74 = t_72 ? t_73 : t_66_y;
            nile_Real_t t_75_1 = t_70;
            nile_Real_t t_75_2 = t_74;
            nile_Real_t t_76_x = t_75_1;
            nile_Real_t t_76_y = t_75_2;
            nile_Real_t t_77 = 0.1;
            nile_Real_t t_78_x = t_77;
            nile_Real_t t_78_y = t_77;
            nile_Real_t t_79_x = nile_Real_lt(t_76_x, t_78_x);
            nile_Real_t t_79_y = nile_Real_lt(t_76_y, t_78_y);
            nile_Real_t v_nearmax_x = t_79_x;
            nile_Real_t v_nearmax_y = t_79_y;
            nile_Real_t t_80_x = v_nearmax_x ? v_max_x : v_ABBC_x;
            nile_Real_t t_80_y = v_nearmax_y ? v_max_y : v_ABBC_y;
            nile_Real_t t_81_x = v_nearmin_x ? v_min_x : t_80_x;
            nile_Real_t t_81_y = v_nearmin_y ? v_min_y : t_80_y;
            nile_Real_t v_M_x = t_81_x;
            nile_Real_t v_M_y = t_81_y;
            nile_Real_t t_83 = nile_Real_add(v_A_x, v_B_x);
            nile_Real_t t_84 = 2;
            nile_Real_t t_85 = nile_Real_div(t_83, t_84);
            nile_Real_t t_86 = nile_Real_add(v_A_y, v_B_y);
            nile_Real_t t_87 = 2;
            nile_Real_t t_88 = nile_Real_div(t_86, t_87);
            nile_Real_t t_89_1 = t_85;
            nile_Real_t t_89_2 = t_88;
            nile_Real_t t_90_x = t_89_1;
            nile_Real_t t_90_y = t_89_2;
            nile_Real_t t_82_1_x = v_A_x;
            nile_Real_t t_82_1_y = v_A_y;
            nile_Real_t t_82_2_x = t_90_x;
            nile_Real_t t_82_2_y = t_90_y;
            nile_Real_t t_82_3_x = v_M_x;
            nile_Real_t t_82_3_y = v_M_y;
            nile_Real_t t_91_a_x = t_82_1_x;
            nile_Real_t t_91_a_y = t_82_1_y;
            nile_Real_t t_91_b_x = t_82_2_x;
            nile_Real_t t_91_b_y = t_82_2_y;
            nile_Real_t t_91_c_x = t_82_3_x;
            nile_Real_t t_91_c_y = t_82_3_y;
            in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
            nile_Buffer_prepend(in, t_91_a_x);
            nile_Buffer_prepend(in, t_91_a_y);
            nile_Buffer_prepend(in, t_91_b_x);
            nile_Buffer_prepend(in, t_91_b_y);
            nile_Buffer_prepend(in, t_91_c_x);
            nile_Buffer_prepend(in, t_91_c_y);
            in->i -= IN_QUANTUM;
            nile_Real_t t_93 = nile_Real_add(v_B_x, v_C_x);
            nile_Real_t t_94 = 2;
            nile_Real_t t_95 = nile_Real_div(t_93, t_94);
            nile_Real_t t_96 = nile_Real_add(v_B_y, v_C_y);
            nile_Real_t t_97 = 2;
            nile_Real_t t_98 = nile_Real_div(t_96, t_97);
            nile_Real_t t_99_1 = t_95;
            nile_Real_t t_99_2 = t_98;
            nile_Real_t t_100_x = t_99_1;
            nile_Real_t t_100_y = t_99_2;
            nile_Real_t t_92_1_x = v_M_x;
            nile_Real_t t_92_1_y = v_M_y;
            nile_Real_t t_92_2_x = t_100_x;
            nile_Real_t t_92_2_y = t_100_y;
            nile_Real_t t_92_3_x = v_C_x;
            nile_Real_t t_92_3_y = v_C_y;
            nile_Real_t t_101_a_x = t_92_1_x;
            nile_Real_t t_101_a_y = t_92_1_y;
            nile_Real_t t_101_b_x = t_92_2_x;
            nile_Real_t t_101_b_y = t_92_2_y;
            nile_Real_t t_101_c_x = t_92_3_x;
            nile_Real_t t_101_c_y = t_92_3_y;
            in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
            nile_Buffer_prepend(in, t_101_a_x);
            nile_Buffer_prepend(in, t_101_a_y);
            nile_Buffer_prepend(in, t_101_b_x);
            nile_Buffer_prepend(in, t_101_b_y);
            nile_Buffer_prepend(in, t_101_c_x);
            nile_Buffer_prepend(in, t_101_c_y);
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

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_x0;
    nile_Real_t v_x;
    nile_Real_t v_local;
    nile_Real_t v_run;
} gezira_FillBetweenEdges_t;

static nile_Kernel_t *gezira_FillBetweenEdges_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    gezira_FillBetweenEdges_t *clone = (gezira_FillBetweenEdges_t *) nile_Kernel_clone(nl, k_);
    clone->v_x0 = k->v_x0;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_FillBetweenEdges(nile_t *nl, 
                                       nile_Real_t v_x0) {
    gezira_FillBetweenEdges_t *k = NILE_KERNEL_NEW(nl, gezira_FillBetweenEdges);
    k->v_x0 = v_x0;
    return (nile_Kernel_t *) k;
}

static int gezira_FillBetweenEdges_process(nile_t *nl,
                                           nile_Kernel_t *k_,
                                           nile_Buffer_t **in_,
                                           nile_Buffer_t **out_) {
    #define IN_QUANTUM 4
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    nile_Real_t v_x0 = k->v_x0;
    nile_Real_t v_x = k->v_x;
    nile_Real_t v_x_;
    nile_Real_t v_local = k->v_local;
    nile_Real_t v_local_;
    nile_Real_t v_run = k->v_run;
    nile_Real_t v_run_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_x0;
        nile_Real_t t_3 = 0;
        v_local = t_3;
        nile_Real_t t_4 = 0;
        v_run = t_4;
    }
    
    while (in->i < in->n) {
        v_x_ = v_x;
        v_local_ = v_local;
        v_run_ = v_run;
        nile_Real_t t_5;
        v_x_ = nile_Buffer_shift(in);
        t_5 = nile_Buffer_shift(in);
        nile_Real_t v_w = nile_Buffer_shift(in);
        nile_Real_t v_h = nile_Buffer_shift(in);
        nile_Real_t t_6 = nile_Real_sub(v_x_, v_x);
        nile_Real_t v_n = t_6;
        nile_Real_t t_7 = nile_Real_add(v_run, v_h);
        v_run_ = t_7;
        nile_Real_t t_8 = 0;
        nile_Real_t t_9 = nile_Real_eq(v_n, t_8);
        if (t_9) {
            nile_Real_t t_10 = nile_Real_mul(v_w, v_h);
            nile_Real_t t_11 = nile_Real_add(v_local, t_10);
            v_local_ = t_11;
        }
        else {
            nile_Real_t t_12 = nile_Real_mul(v_w, v_h);
            nile_Real_t t_13 = nile_Real_add(v_run, t_12);
            v_local_ = t_13;
            nile_Real_t t_14 = 0;
            nile_Real_t t_15 = nile_Real_lt(v_local, t_14);
            nile_Real_t t_16 = nile_Real_neg(v_local);
            nile_Real_t t_17 = t_15 ? t_16 : v_local;
            nile_Real_t t_18 = 1;
            nile_Real_t t_19 = nile_Real_lt(t_17, t_18);
            nile_Real_t t_20 = t_19 ? t_17 : t_18;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_20);
            nile_Real_t t_21 = 1;
            nile_Real_t t_22 = nile_Real_sub(v_n, t_21);
            nile_Real_t t_23 = 0;
            nile_Real_t t_24 = nile_Real_lt(v_run, t_23);
            nile_Real_t t_25 = nile_Real_neg(v_run);
            nile_Real_t t_26 = t_24 ? t_25 : v_run;
            nile_Real_t t_27 = 1;
            nile_Real_t t_28 = nile_Real_lt(t_26, t_27);
            nile_Real_t t_29 = t_28 ? t_26 : t_27;
            out = nile_Buffer_append_repeat(nl, out, t_29, t_22, k_);
        }
        v_x = v_x_;
        v_local = v_local_;
        v_run = v_run_;
    }
    
    if (in->eos) {
        nile_Real_t t_30 = 0;
        nile_Real_t t_31 = nile_Real_neq(v_local, t_30);
        if (t_31) {
            nile_Real_t t_32 = 0;
            nile_Real_t t_33 = nile_Real_lt(v_local, t_32);
            nile_Real_t t_34 = nile_Real_neg(v_local);
            nile_Real_t t_35 = t_33 ? t_34 : v_local;
            nile_Real_t t_36 = 1;
            nile_Real_t t_37 = nile_Real_lt(t_35, t_36);
            nile_Real_t t_38 = t_37 ? t_35 : t_36;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_38);
        }
        else {
            ; /* no-op */
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

static nile_Kernel_t *gezira_CreateSamplePoints_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    gezira_CreateSamplePoints_t *clone = (gezira_CreateSamplePoints_t *) nile_Kernel_clone(nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_CreateSamplePoints(nile_t *nl, 
                                         nile_Real_t v_start_x, 
                                         nile_Real_t v_start_y) {
    gezira_CreateSamplePoints_t *k = NILE_KERNEL_NEW(nl, gezira_CreateSamplePoints);
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return (nile_Kernel_t *) k;
}

static int gezira_CreateSamplePoints_process(nile_t *nl,
                                             nile_Kernel_t *k_,
                                             nile_Buffer_t **in_,
                                             nile_Buffer_t **out_) {
    #define IN_QUANTUM 1
    #define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    nile_Real_t v_start_x = k->v_start_x;
    nile_Real_t v_start_y = k->v_start_y;
    nile_Real_t v_x = k->v_x;
    nile_Real_t v_x_;
    nile_Real_t v_y = k->v_y;
    nile_Real_t v_y_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_start_x;
        v_y = v_start_y;
    }
    
    while (in->i < in->n) {
        v_x_ = v_x;
        v_y_ = v_y;
        nile_Real_t t_1;
        t_1 = nile_Buffer_shift(in);
        nile_Real_t t_2_1 = v_x;
        nile_Real_t t_2_2 = v_y;
        nile_Real_t t_3_x = t_2_1;
        nile_Real_t t_3_y = t_2_2;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_3_x);
        nile_Buffer_append(out, t_3_y);
        nile_Real_t t_4 = 1;
        nile_Real_t t_5 = nile_Real_add(v_x, t_4);
        v_x_ = t_5;
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
    nile_Real_t v_x;
    nile_Real_t v_y;
    nile_Real_t v_start_1;
    nile_Real_t v_start_2;
} gezira_Render__t;

static nile_Kernel_t *gezira_Render__clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Render__t *k = (gezira_Render__t *) k_;
    gezira_Render__t *clone = (gezira_Render__t *) nile_Kernel_clone(nl, k_);
    clone->v_s = k->v_s->clone(nl, k->v_s);
    clone->v_c = k->v_c->clone(nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_Render_(nile_t *nl, 
                              nile_Kernel_t *v_s, 
                              nile_Kernel_t *v_c) {
    gezira_Render__t *k = NILE_KERNEL_NEW(nl, gezira_Render_);
    k->v_s = v_s;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

static int gezira_Render__process(nile_t *nl,
                                  nile_Kernel_t *k_,
                                  nile_Buffer_t **in_,
                                  nile_Buffer_t **out_) {
    #define IN_QUANTUM 4
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_Render__t *k = (gezira_Render__t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    nile_Kernel_t *v_c = k->v_c;
    nile_Real_t v_x = k->v_x;
    nile_Real_t v_x_;
    nile_Real_t v_y = k->v_y;
    nile_Real_t v_y_;
    nile_Real_t v_start_1 = k->v_start_1;
    nile_Real_t v_start__1;
    nile_Real_t v_start_2 = k->v_start_2;
    nile_Real_t v_start__2;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        nile_Real_t t_5;
        nile_Real_t t_6;
        v_x = in->data[in->i++];
        v_y = in->data[in->i++];
        t_5 = in->data[in->i++];
        t_6 = in->data[in->i++];
        in->i -= 4;
        nile_Real_t t_7_1 = v_x;
        nile_Real_t t_7_2 = v_y;
        nile_Real_t t_8 = 0.5;
        nile_Real_t t_9_1 = t_8;
        nile_Real_t t_9_2 = t_8;
        nile_Real_t t_10_1 = nile_Real_add(t_7_1, t_9_1);
        nile_Real_t t_10_2 = nile_Real_add(t_7_2, t_9_2);
        v_start_1 = t_10_1;
        v_start_2 = t_10_2;
        ; /* no-op */
        nile_Kernel_t *t_11 = gezira_FillBetweenEdges(nl, v_x);
        nile_Real_t t_12_x = v_start_1;
        nile_Real_t t_12_y = v_start_2;
        nile_Kernel_t *t_13 = gezira_CreateSamplePoints(nl, t_12_x, t_12_y);
        nile_Kernel_t *t_14 = nile_Pipeline(nl, t_13, v_s, NULL);
        nile_Real_t t_15 = 4;
        nile_Kernel_t *t_16 = nile_Pipeline(nl, NULL);
        nile_Real_t t_17 = 1;
        nile_Kernel_t *t_18 = nile_Interleave(nl, t_14, t_15, t_16, t_17);
        nile_Real_t t_19_x = v_start_1;
        nile_Real_t t_19_y = v_start_2;
        nile_Kernel_t *t_20 = gezira_Canvas(nl, v_c, t_19_x, t_19_y);
        nile_Kernel_t *t_21 = nile_Pipeline(nl, t_18, t_20, NULL);
        nile_Kernel_t *t_22 = nile_Pipeline(nl, t_11, t_21, NULL);
        nile_Kernel_t *f = t_22;
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

static nile_Kernel_t *gezira_Render_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_Render_t *k = (gezira_Render_t *) k_;
    gezira_Render_t *clone = (gezira_Render_t *) nile_Kernel_clone(nl, k_);
    clone->v_s = k->v_s->clone(nl, k->v_s);
    clone->v_c = k->v_c->clone(nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_Render(nile_t *nl, 
                             nile_Kernel_t *v_s, 
                             nile_Kernel_t *v_c) {
    gezira_Render_t *k = NILE_KERNEL_NEW(nl, gezira_Render);
    k->v_s = v_s;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

static int gezira_Render_process(nile_t *nl,
                                 nile_Kernel_t *k_,
                                 nile_Buffer_t **in_,
                                 nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_Render_t *k = (gezira_Render_t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    nile_Kernel_t *v_c = k->v_c;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        ; /* no-op */
        nile_Real_t t_1 = 1;
        nile_Real_t t_2 = 4;
        nile_Kernel_t *t_3 = nile_GroupBy(nl, t_1, t_2);
        nile_Real_t t_4 = 0;
        nile_Real_t t_5 = 4;
        nile_Kernel_t *t_6 = nile_SortBy(nl, t_4, t_5);
        nile_Kernel_t *t_7 = gezira_Render_(nl, v_s, v_c);
        nile_Kernel_t *t_8 = nile_Pipeline(nl, t_6, t_7, NULL);
        nile_Kernel_t *t_9 = nile_Pipeline(nl, t_3, t_8, NULL);
        nile_Kernel_t *t_10 = nile_Pipeline(nl, gezira_DecomposeBeziers(nl), t_9, NULL);
        nile_Kernel_t *f = t_10;
        f->downstream = k_->downstream;
        k_->downstream = f;
    }
    
    return NILE_INPUT_FORWARD;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

nile_Kernel_t *gezira_StrokeJoin_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_StrokeJoin_t *k = (gezira_StrokeJoin_t *) k_;
    gezira_StrokeJoin_t *clone = (gezira_StrokeJoin_t *) nile_Kernel_clone(nl, k_);
    clone->v_o = k->v_o;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_StrokeJoin(nile_t *nl, 
                                 nile_Kernel_t *k_, 
                                 nile_Real_t v_o) {
    gezira_StrokeJoin_t *k = (gezira_StrokeJoin_t *) k_;
    k->v_o = v_o;
    return (nile_Kernel_t *) k;
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_o;
} gezira_StrokeOffset_t;

static nile_Kernel_t *gezira_StrokeOffset_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_StrokeOffset_t *k = (gezira_StrokeOffset_t *) k_;
    gezira_StrokeOffset_t *clone = (gezira_StrokeOffset_t *) nile_Kernel_clone(nl, k_);
    clone->v_o = k->v_o;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_StrokeOffset(nile_t *nl, 
                                   nile_Real_t v_o) {
    gezira_StrokeOffset_t *k = NILE_KERNEL_NEW(nl, gezira_StrokeOffset);
    k->v_o = v_o;
    return (nile_Kernel_t *) k;
}

static int gezira_StrokeOffset_process(nile_t *nl,
                                       nile_Kernel_t *k_,
                                       nile_Buffer_t **in_,
                                       nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_StrokeOffset_t *k = (gezira_StrokeOffset_t *) k_;
    nile_Real_t v_o = k->v_o;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_2 = nile_Real_sub(v_A_y, v_B_y);
        nile_Real_t t_3 = nile_Real_sub(v_B_x, v_A_x);
        nile_Real_t t_1_1 = t_2;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        nile_Real_t t_5 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_6 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_7 = nile_Real_add(t_5, t_6);
        nile_Real_t t_8 = nile_Real_sqr(t_7);
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_neq(t_8, t_9);
        nile_Real_t t_11 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_12 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_13 = nile_Real_add(t_11, t_12);
        nile_Real_t t_14 = nile_Real_sqr(t_13);
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_div(t_4_x, t_15_x);
        nile_Real_t t_16_y = nile_Real_div(t_4_y, t_15_y);
        nile_Real_t t_17 = 0;
        nile_Real_t t_18_x = t_17;
        nile_Real_t t_18_y = t_17;
        nile_Real_t t_19_x = t_10;
        nile_Real_t t_19_y = t_10;
        nile_Real_t t_20_x = t_19_x ? t_16_x : t_18_x;
        nile_Real_t t_20_y = t_19_y ? t_16_y : t_18_y;
        nile_Real_t v_u_x = t_20_x;
        nile_Real_t v_u_y = t_20_y;
        nile_Real_t t_22 = nile_Real_sub(v_B_y, v_C_y);
        nile_Real_t t_23 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_21_1 = t_22;
        nile_Real_t t_21_2 = t_23;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        nile_Real_t t_25 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_26 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_27 = nile_Real_add(t_25, t_26);
        nile_Real_t t_28 = nile_Real_sqr(t_27);
        nile_Real_t t_29 = 0;
        nile_Real_t t_30 = nile_Real_neq(t_28, t_29);
        nile_Real_t t_31 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_32 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_33 = nile_Real_add(t_31, t_32);
        nile_Real_t t_34 = nile_Real_sqr(t_33);
        nile_Real_t t_35_x = t_34;
        nile_Real_t t_35_y = t_34;
        nile_Real_t t_36_x = nile_Real_div(t_24_x, t_35_x);
        nile_Real_t t_36_y = nile_Real_div(t_24_y, t_35_y);
        nile_Real_t t_37 = 0;
        nile_Real_t t_38_x = t_37;
        nile_Real_t t_38_y = t_37;
        nile_Real_t t_39_x = t_30;
        nile_Real_t t_39_y = t_30;
        nile_Real_t t_40_x = t_39_x ? t_36_x : t_38_x;
        nile_Real_t t_40_y = t_39_y ? t_36_y : t_38_y;
        nile_Real_t v_v_x = t_40_x;
        nile_Real_t v_v_y = t_40_y;
        nile_Real_t t_41 = nile_Real_add(v_A_x, v_B_x);
        nile_Real_t t_42 = 2;
        nile_Real_t t_43 = nile_Real_div(t_41, t_42);
        nile_Real_t t_44 = nile_Real_add(v_A_y, v_B_y);
        nile_Real_t t_45 = 2;
        nile_Real_t t_46 = nile_Real_div(t_44, t_45);
        nile_Real_t t_47_1 = t_43;
        nile_Real_t t_47_2 = t_46;
        nile_Real_t t_48_x = t_47_1;
        nile_Real_t t_48_y = t_47_2;
        nile_Real_t t_49 = nile_Real_add(v_B_x, v_C_x);
        nile_Real_t t_50 = 2;
        nile_Real_t t_51 = nile_Real_div(t_49, t_50);
        nile_Real_t t_52 = nile_Real_add(v_B_y, v_C_y);
        nile_Real_t t_53 = 2;
        nile_Real_t t_54 = nile_Real_div(t_52, t_53);
        nile_Real_t t_55_1 = t_51;
        nile_Real_t t_55_2 = t_54;
        nile_Real_t t_56_x = t_55_1;
        nile_Real_t t_56_y = t_55_2;
        nile_Real_t t_57 = nile_Real_add(t_48_x, t_56_x);
        nile_Real_t t_58 = 2;
        nile_Real_t t_59 = nile_Real_div(t_57, t_58);
        nile_Real_t t_60 = nile_Real_add(t_48_y, t_56_y);
        nile_Real_t t_61 = 2;
        nile_Real_t t_62 = nile_Real_div(t_60, t_61);
        nile_Real_t t_63_1 = t_59;
        nile_Real_t t_63_2 = t_62;
        nile_Real_t t_64_x = t_63_1;
        nile_Real_t t_64_y = t_63_2;
        nile_Real_t v_M_x = t_64_x;
        nile_Real_t v_M_y = t_64_y;
        nile_Real_t t_65 = nile_Real_mul(v_u_x, v_v_x);
        nile_Real_t t_66 = nile_Real_mul(v_u_y, v_v_y);
        nile_Real_t t_67 = nile_Real_add(t_65, t_66);
        nile_Real_t t_68 = 0.9;
        nile_Real_t t_69 = nile_Real_gt(t_67, t_68);
        if (t_69) {
            nile_Real_t t_70 = nile_Real_add(v_A_x, v_B_x);
            nile_Real_t t_71 = 2;
            nile_Real_t t_72 = nile_Real_div(t_70, t_71);
            nile_Real_t t_73 = nile_Real_add(v_A_y, v_B_y);
            nile_Real_t t_74 = 2;
            nile_Real_t t_75 = nile_Real_div(t_73, t_74);
            nile_Real_t t_76_1 = t_72;
            nile_Real_t t_76_2 = t_75;
            nile_Real_t t_77_x = t_76_1;
            nile_Real_t t_77_y = t_76_2;
            nile_Real_t t_78 = nile_Real_add(v_B_x, v_C_x);
            nile_Real_t t_79 = 2;
            nile_Real_t t_80 = nile_Real_div(t_78, t_79);
            nile_Real_t t_81 = nile_Real_add(v_B_y, v_C_y);
            nile_Real_t t_82 = 2;
            nile_Real_t t_83 = nile_Real_div(t_81, t_82);
            nile_Real_t t_84_1 = t_80;
            nile_Real_t t_84_2 = t_83;
            nile_Real_t t_85_x = t_84_1;
            nile_Real_t t_85_y = t_84_2;
            nile_Real_t t_87 = nile_Real_sub(t_77_y, t_85_y);
            nile_Real_t t_88 = nile_Real_sub(t_85_x, t_77_x);
            nile_Real_t t_86_1 = t_87;
            nile_Real_t t_86_2 = t_88;
            nile_Real_t t_89_x = t_86_1;
            nile_Real_t t_89_y = t_86_2;
            nile_Real_t t_90 = nile_Real_mul(t_89_x, t_89_x);
            nile_Real_t t_91 = nile_Real_mul(t_89_y, t_89_y);
            nile_Real_t t_92 = nile_Real_add(t_90, t_91);
            nile_Real_t t_93 = nile_Real_sqr(t_92);
            nile_Real_t t_94 = 0;
            nile_Real_t t_95 = nile_Real_neq(t_93, t_94);
            nile_Real_t t_96 = nile_Real_mul(t_89_x, t_89_x);
            nile_Real_t t_97 = nile_Real_mul(t_89_y, t_89_y);
            nile_Real_t t_98 = nile_Real_add(t_96, t_97);
            nile_Real_t t_99 = nile_Real_sqr(t_98);
            nile_Real_t t_100_x = t_99;
            nile_Real_t t_100_y = t_99;
            nile_Real_t t_101_x = nile_Real_div(t_89_x, t_100_x);
            nile_Real_t t_101_y = nile_Real_div(t_89_y, t_100_y);
            nile_Real_t t_102 = 0;
            nile_Real_t t_103_x = t_102;
            nile_Real_t t_103_y = t_102;
            nile_Real_t t_104_x = t_95;
            nile_Real_t t_104_y = t_95;
            nile_Real_t t_105_x = t_104_x ? t_101_x : t_103_x;
            nile_Real_t t_105_y = t_104_y ? t_101_y : t_103_y;
            nile_Real_t v_w_x = t_105_x;
            nile_Real_t v_w_y = t_105_y;
            nile_Real_t t_106_x = v_o;
            nile_Real_t t_106_y = v_o;
            nile_Real_t t_107_x = nile_Real_mul(t_106_x, v_u_x);
            nile_Real_t t_107_y = nile_Real_mul(t_106_y, v_u_y);
            nile_Real_t t_108_x = t_107_x;
            nile_Real_t t_108_y = t_107_y;
            nile_Real_t t_109_x = nile_Real_add(v_A_x, t_108_x);
            nile_Real_t t_109_y = nile_Real_add(v_A_y, t_108_y);
            nile_Real_t v_D_x = t_109_x;
            nile_Real_t v_D_y = t_109_y;
            nile_Real_t t_110_x = v_o;
            nile_Real_t t_110_y = v_o;
            nile_Real_t t_111_x = nile_Real_mul(t_110_x, v_v_x);
            nile_Real_t t_111_y = nile_Real_mul(t_110_y, v_v_y);
            nile_Real_t t_112_x = t_111_x;
            nile_Real_t t_112_y = t_111_y;
            nile_Real_t t_113_x = nile_Real_add(v_C_x, t_112_x);
            nile_Real_t t_113_y = nile_Real_add(v_C_y, t_112_y);
            nile_Real_t v_F_x = t_113_x;
            nile_Real_t v_F_y = t_113_y;
            nile_Real_t t_114_x = v_o;
            nile_Real_t t_114_y = v_o;
            nile_Real_t t_115_x = nile_Real_mul(t_114_x, v_w_x);
            nile_Real_t t_115_y = nile_Real_mul(t_114_y, v_w_y);
            nile_Real_t t_116_x = t_115_x;
            nile_Real_t t_116_y = t_115_y;
            nile_Real_t t_117_x = nile_Real_add(v_M_x, t_116_x);
            nile_Real_t t_117_y = nile_Real_add(v_M_y, t_116_y);
            nile_Real_t v_N_x = t_117_x;
            nile_Real_t v_N_y = t_117_y;
            nile_Real_t t_118 = 2;
            nile_Real_t t_119_x = t_118;
            nile_Real_t t_119_y = t_118;
            nile_Real_t t_120_x = nile_Real_mul(t_119_x, v_N_x);
            nile_Real_t t_120_y = nile_Real_mul(t_119_y, v_N_y);
            nile_Real_t t_121 = nile_Real_add(v_D_x, v_F_x);
            nile_Real_t t_122 = 2;
            nile_Real_t t_123 = nile_Real_div(t_121, t_122);
            nile_Real_t t_124 = nile_Real_add(v_D_y, v_F_y);
            nile_Real_t t_125 = 2;
            nile_Real_t t_126 = nile_Real_div(t_124, t_125);
            nile_Real_t t_127_1 = t_123;
            nile_Real_t t_127_2 = t_126;
            nile_Real_t t_128_x = t_127_1;
            nile_Real_t t_128_y = t_127_2;
            nile_Real_t t_129_x = nile_Real_sub(t_120_x, t_128_x);
            nile_Real_t t_129_y = nile_Real_sub(t_120_y, t_128_y);
            nile_Real_t v_E_x = t_129_x;
            nile_Real_t v_E_y = t_129_y;
            nile_Real_t t_130_1_x = v_D_x;
            nile_Real_t t_130_1_y = v_D_y;
            nile_Real_t t_130_2_x = v_E_x;
            nile_Real_t t_130_2_y = v_E_y;
            nile_Real_t t_130_3_x = v_F_x;
            nile_Real_t t_130_3_y = v_F_y;
            nile_Real_t t_131_a_x = t_130_1_x;
            nile_Real_t t_131_a_y = t_130_1_y;
            nile_Real_t t_131_b_x = t_130_2_x;
            nile_Real_t t_131_b_y = t_130_2_y;
            nile_Real_t t_131_c_x = t_130_3_x;
            nile_Real_t t_131_c_y = t_130_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_131_a_x);
            nile_Buffer_append(out, t_131_a_y);
            nile_Buffer_append(out, t_131_b_x);
            nile_Buffer_append(out, t_131_b_y);
            nile_Buffer_append(out, t_131_c_x);
            nile_Buffer_append(out, t_131_c_y);
        }
        else {
            nile_Real_t t_132 = 0;
            nile_Real_t t_133_x = t_132;
            nile_Real_t t_133_y = t_132;
            nile_Real_t t_134 = nile_Real_eq(v_u_x, t_133_x);
            nile_Real_t t_135 = nile_Real_eq(v_u_y, t_133_y);
            nile_Real_t t_136 = nile_Real_and(t_134, t_135);
            nile_Real_t t_137 = 0;
            nile_Real_t t_138 = nile_Real_eq(t_136, t_137);
            nile_Real_t t_139 = 0;
            nile_Real_t t_140_x = t_139;
            nile_Real_t t_140_y = t_139;
            nile_Real_t t_141 = nile_Real_eq(v_v_x, t_140_x);
            nile_Real_t t_142 = nile_Real_eq(v_v_y, t_140_y);
            nile_Real_t t_143 = nile_Real_and(t_141, t_142);
            nile_Real_t t_144 = 0;
            nile_Real_t t_145 = nile_Real_eq(t_143, t_144);
            nile_Real_t t_146 = nile_Real_and(t_138, t_145);
            if (t_146) {
                nile_Real_t t_148 = nile_Real_add(v_A_x, v_B_x);
                nile_Real_t t_149 = 2;
                nile_Real_t t_150 = nile_Real_div(t_148, t_149);
                nile_Real_t t_151 = nile_Real_add(v_A_y, v_B_y);
                nile_Real_t t_152 = 2;
                nile_Real_t t_153 = nile_Real_div(t_151, t_152);
                nile_Real_t t_154_1 = t_150;
                nile_Real_t t_154_2 = t_153;
                nile_Real_t t_155_x = t_154_1;
                nile_Real_t t_155_y = t_154_2;
                nile_Real_t t_147_1_x = v_A_x;
                nile_Real_t t_147_1_y = v_A_y;
                nile_Real_t t_147_2_x = t_155_x;
                nile_Real_t t_147_2_y = t_155_y;
                nile_Real_t t_147_3_x = v_M_x;
                nile_Real_t t_147_3_y = v_M_y;
                nile_Real_t t_156_a_x = t_147_1_x;
                nile_Real_t t_156_a_y = t_147_1_y;
                nile_Real_t t_156_b_x = t_147_2_x;
                nile_Real_t t_156_b_y = t_147_2_y;
                nile_Real_t t_156_c_x = t_147_3_x;
                nile_Real_t t_156_c_y = t_147_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_156_a_x);
                nile_Buffer_prepend(in, t_156_a_y);
                nile_Buffer_prepend(in, t_156_b_x);
                nile_Buffer_prepend(in, t_156_b_y);
                nile_Buffer_prepend(in, t_156_c_x);
                nile_Buffer_prepend(in, t_156_c_y);
                in->i -= IN_QUANTUM;
                nile_Real_t t_158 = nile_Real_add(v_B_x, v_C_x);
                nile_Real_t t_159 = 2;
                nile_Real_t t_160 = nile_Real_div(t_158, t_159);
                nile_Real_t t_161 = nile_Real_add(v_B_y, v_C_y);
                nile_Real_t t_162 = 2;
                nile_Real_t t_163 = nile_Real_div(t_161, t_162);
                nile_Real_t t_164_1 = t_160;
                nile_Real_t t_164_2 = t_163;
                nile_Real_t t_165_x = t_164_1;
                nile_Real_t t_165_y = t_164_2;
                nile_Real_t t_157_1_x = v_M_x;
                nile_Real_t t_157_1_y = v_M_y;
                nile_Real_t t_157_2_x = t_165_x;
                nile_Real_t t_157_2_y = t_165_y;
                nile_Real_t t_157_3_x = v_C_x;
                nile_Real_t t_157_3_y = v_C_y;
                nile_Real_t t_166_a_x = t_157_1_x;
                nile_Real_t t_166_a_y = t_157_1_y;
                nile_Real_t t_166_b_x = t_157_2_x;
                nile_Real_t t_166_b_y = t_157_2_y;
                nile_Real_t t_166_c_x = t_157_3_x;
                nile_Real_t t_166_c_y = t_157_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_166_a_x);
                nile_Buffer_prepend(in, t_166_a_y);
                nile_Buffer_prepend(in, t_166_b_x);
                nile_Buffer_prepend(in, t_166_b_y);
                nile_Buffer_prepend(in, t_166_c_x);
                nile_Buffer_prepend(in, t_166_c_y);
                in->i -= IN_QUANTUM;
            }
            else {
                ; /* no-op */
            }
        }
    }
    
    if (in->eos) {
    }
    else {
        k->v_o = v_o;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_o;
    nile_Real_t v_l;
    nile_Real_t v_d;
} gezira_StrokeJoinMiter_t;

static nile_Kernel_t *gezira_StrokeJoinMiter_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_StrokeJoinMiter_t *k = (gezira_StrokeJoinMiter_t *) k_;
    gezira_StrokeJoinMiter_t *clone = (gezira_StrokeJoinMiter_t *) gezira_StrokeJoin_clone(nl, k_);
    clone->v_l = k->v_l;
    clone->v_d = k->v_d;
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_StrokeJoinMiter(nile_t *nl, 
                                      nile_Real_t v_l, 
                                      nile_Real_t v_d) {
    gezira_StrokeJoinMiter_t *k = NILE_KERNEL_NEW(nl, gezira_StrokeJoinMiter);
    k->v_l = v_l;
    k->v_d = v_d;
    return (nile_Kernel_t *) k;
}

static int gezira_StrokeJoinMiter_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 12
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_StrokeJoinMiter_t *k = (gezira_StrokeJoinMiter_t *) k_;
    nile_Real_t v_o = k->v_o;
    nile_Real_t v_l = k->v_l;
    nile_Real_t v_d = k->v_d;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t v_D_x = nile_Buffer_shift(in);
        nile_Real_t v_D_y = nile_Buffer_shift(in);
        nile_Real_t v_E_x = nile_Buffer_shift(in);
        nile_Real_t v_E_y = nile_Buffer_shift(in);
        nile_Real_t v_F_x = nile_Buffer_shift(in);
        nile_Real_t v_F_y = nile_Buffer_shift(in);
        nile_Real_t t_2 = nile_Real_sub(v_B_y, v_C_y);
        nile_Real_t t_3 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_1_1 = t_2;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        nile_Real_t t_5 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_6 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_7 = nile_Real_add(t_5, t_6);
        nile_Real_t t_8 = nile_Real_sqr(t_7);
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_neq(t_8, t_9);
        nile_Real_t t_11 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_12 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_13 = nile_Real_add(t_11, t_12);
        nile_Real_t t_14 = nile_Real_sqr(t_13);
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_div(t_4_x, t_15_x);
        nile_Real_t t_16_y = nile_Real_div(t_4_y, t_15_y);
        nile_Real_t t_17 = 0;
        nile_Real_t t_18_x = t_17;
        nile_Real_t t_18_y = t_17;
        nile_Real_t t_19_x = t_10;
        nile_Real_t t_19_y = t_10;
        nile_Real_t t_20_x = t_19_x ? t_16_x : t_18_x;
        nile_Real_t t_20_y = t_19_y ? t_16_y : t_18_y;
        nile_Real_t v_u_x = t_20_x;
        nile_Real_t v_u_y = t_20_y;
        nile_Real_t t_22 = nile_Real_sub(v_D_y, v_E_y);
        nile_Real_t t_23 = nile_Real_sub(v_E_x, v_D_x);
        nile_Real_t t_21_1 = t_22;
        nile_Real_t t_21_2 = t_23;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        nile_Real_t t_25 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_26 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_27 = nile_Real_add(t_25, t_26);
        nile_Real_t t_28 = nile_Real_sqr(t_27);
        nile_Real_t t_29 = 0;
        nile_Real_t t_30 = nile_Real_neq(t_28, t_29);
        nile_Real_t t_31 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_32 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_33 = nile_Real_add(t_31, t_32);
        nile_Real_t t_34 = nile_Real_sqr(t_33);
        nile_Real_t t_35_x = t_34;
        nile_Real_t t_35_y = t_34;
        nile_Real_t t_36_x = nile_Real_div(t_24_x, t_35_x);
        nile_Real_t t_36_y = nile_Real_div(t_24_y, t_35_y);
        nile_Real_t t_37 = 0;
        nile_Real_t t_38_x = t_37;
        nile_Real_t t_38_y = t_37;
        nile_Real_t t_39_x = t_30;
        nile_Real_t t_39_y = t_30;
        nile_Real_t t_40_x = t_39_x ? t_36_x : t_38_x;
        nile_Real_t t_40_y = t_39_y ? t_36_y : t_38_y;
        nile_Real_t v_v_x = t_40_x;
        nile_Real_t v_v_y = t_40_y;
        nile_Real_t t_42 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_43 = nile_Real_sub(v_C_y, v_B_y);
        nile_Real_t t_41_1 = t_42;
        nile_Real_t t_41_2 = t_43;
        nile_Real_t t_44_x = t_41_1;
        nile_Real_t t_44_y = t_41_2;
        nile_Real_t t_45 = nile_Real_mul(t_44_x, t_44_x);
        nile_Real_t t_46 = nile_Real_mul(t_44_y, t_44_y);
        nile_Real_t t_47 = nile_Real_add(t_45, t_46);
        nile_Real_t t_48 = nile_Real_sqr(t_47);
        nile_Real_t t_49 = 0;
        nile_Real_t t_50 = nile_Real_neq(t_48, t_49);
        nile_Real_t t_51 = nile_Real_mul(t_44_x, t_44_x);
        nile_Real_t t_52 = nile_Real_mul(t_44_y, t_44_y);
        nile_Real_t t_53 = nile_Real_add(t_51, t_52);
        nile_Real_t t_54 = nile_Real_sqr(t_53);
        nile_Real_t t_55_x = t_54;
        nile_Real_t t_55_y = t_54;
        nile_Real_t t_56_x = nile_Real_div(t_44_x, t_55_x);
        nile_Real_t t_56_y = nile_Real_div(t_44_y, t_55_y);
        nile_Real_t t_57 = 0;
        nile_Real_t t_58_x = t_57;
        nile_Real_t t_58_y = t_57;
        nile_Real_t t_59_x = t_50;
        nile_Real_t t_59_y = t_50;
        nile_Real_t t_60_x = t_59_x ? t_56_x : t_58_x;
        nile_Real_t t_60_y = t_59_y ? t_56_y : t_58_y;
        nile_Real_t v_x_x = t_60_x;
        nile_Real_t v_x_y = t_60_y;
        nile_Real_t t_62 = nile_Real_sub(v_D_x, v_E_x);
        nile_Real_t t_63 = nile_Real_sub(v_D_y, v_E_y);
        nile_Real_t t_61_1 = t_62;
        nile_Real_t t_61_2 = t_63;
        nile_Real_t t_64_x = t_61_1;
        nile_Real_t t_64_y = t_61_2;
        nile_Real_t t_65 = nile_Real_mul(t_64_x, t_64_x);
        nile_Real_t t_66 = nile_Real_mul(t_64_y, t_64_y);
        nile_Real_t t_67 = nile_Real_add(t_65, t_66);
        nile_Real_t t_68 = nile_Real_sqr(t_67);
        nile_Real_t t_69 = 0;
        nile_Real_t t_70 = nile_Real_neq(t_68, t_69);
        nile_Real_t t_71 = nile_Real_mul(t_64_x, t_64_x);
        nile_Real_t t_72 = nile_Real_mul(t_64_y, t_64_y);
        nile_Real_t t_73 = nile_Real_add(t_71, t_72);
        nile_Real_t t_74 = nile_Real_sqr(t_73);
        nile_Real_t t_75_x = t_74;
        nile_Real_t t_75_y = t_74;
        nile_Real_t t_76_x = nile_Real_div(t_64_x, t_75_x);
        nile_Real_t t_76_y = nile_Real_div(t_64_y, t_75_y);
        nile_Real_t t_77 = 0;
        nile_Real_t t_78_x = t_77;
        nile_Real_t t_78_y = t_77;
        nile_Real_t t_79_x = t_70;
        nile_Real_t t_79_y = t_70;
        nile_Real_t t_80_x = t_79_x ? t_76_x : t_78_x;
        nile_Real_t t_80_y = t_79_y ? t_76_y : t_78_y;
        nile_Real_t v_y_x = t_80_x;
        nile_Real_t v_y_y = t_80_y;
        nile_Real_t t_81_x = nile_Real_add(v_x_x, v_y_x);
        nile_Real_t t_81_y = nile_Real_add(v_x_y, v_y_y);
        nile_Real_t t_82 = nile_Real_mul(t_81_x, t_81_x);
        nile_Real_t t_83 = nile_Real_mul(t_81_y, t_81_y);
        nile_Real_t t_84 = nile_Real_add(t_82, t_83);
        nile_Real_t t_85 = nile_Real_sqr(t_84);
        nile_Real_t t_86 = 0;
        nile_Real_t t_87 = nile_Real_neq(t_85, t_86);
        nile_Real_t t_88 = nile_Real_mul(t_81_x, t_81_x);
        nile_Real_t t_89 = nile_Real_mul(t_81_y, t_81_y);
        nile_Real_t t_90 = nile_Real_add(t_88, t_89);
        nile_Real_t t_91 = nile_Real_sqr(t_90);
        nile_Real_t t_92_x = t_91;
        nile_Real_t t_92_y = t_91;
        nile_Real_t t_93_x = nile_Real_div(t_81_x, t_92_x);
        nile_Real_t t_93_y = nile_Real_div(t_81_y, t_92_y);
        nile_Real_t t_94 = 0;
        nile_Real_t t_95_x = t_94;
        nile_Real_t t_95_y = t_94;
        nile_Real_t t_96_x = t_87;
        nile_Real_t t_96_y = t_87;
        nile_Real_t t_97_x = t_96_x ? t_93_x : t_95_x;
        nile_Real_t t_97_y = t_96_y ? t_93_y : t_95_y;
        nile_Real_t t_98 = 0;
        nile_Real_t t_99_x = t_98;
        nile_Real_t t_99_y = t_98;
        nile_Real_t t_100 = nile_Real_eq(t_97_x, t_99_x);
        nile_Real_t t_101 = nile_Real_eq(t_97_y, t_99_y);
        nile_Real_t t_102 = nile_Real_and(t_100, t_101);
        nile_Real_t t_103 = 0;
        nile_Real_t t_104 = nile_Real_eq(t_102, t_103);
        nile_Real_t t_105_x = t_104;
        nile_Real_t t_105_y = t_104;
        nile_Real_t t_106_x = t_105_x ? t_97_x : v_u_x;
        nile_Real_t t_106_y = t_105_y ? t_97_y : v_u_y;
        nile_Real_t v_w_x = t_106_x;
        nile_Real_t v_w_y = t_106_y;
        nile_Real_t t_107_x = v_o;
        nile_Real_t t_107_y = v_o;
        nile_Real_t t_108_x = nile_Real_mul(t_107_x, v_u_x);
        nile_Real_t t_108_y = nile_Real_mul(t_107_y, v_u_y);
        nile_Real_t t_109_x = t_108_x;
        nile_Real_t t_109_y = t_108_y;
        nile_Real_t t_110_x = nile_Real_add(v_C_x, t_109_x);
        nile_Real_t t_110_y = nile_Real_add(v_C_y, t_109_y);
        nile_Real_t v_G_x = t_110_x;
        nile_Real_t v_G_y = t_110_y;
        nile_Real_t t_111_x = v_o;
        nile_Real_t t_111_y = v_o;
        nile_Real_t t_112_x = nile_Real_mul(t_111_x, v_v_x);
        nile_Real_t t_112_y = nile_Real_mul(t_111_y, v_v_y);
        nile_Real_t t_113_x = t_112_x;
        nile_Real_t t_113_y = t_112_y;
        nile_Real_t t_114_x = nile_Real_add(v_C_x, t_113_x);
        nile_Real_t t_114_y = nile_Real_add(v_C_y, t_113_y);
        nile_Real_t v_J_x = t_114_x;
        nile_Real_t v_J_y = t_114_y;
        nile_Real_t t_115 = nile_Real_mul(v_u_x, v_w_x);
        nile_Real_t t_116 = nile_Real_mul(v_u_y, v_w_y);
        nile_Real_t t_117 = nile_Real_add(t_115, t_116);
        nile_Real_t t_118 = 0.01;
        nile_Real_t t_119 = nile_Real_neg(t_118);
        nile_Real_t t_120 = nile_Real_lt(t_117, t_119);
        if (t_120) {
            nile_Real_t t_122 = nile_Real_add(v_G_x, v_J_x);
            nile_Real_t t_123 = 2;
            nile_Real_t t_124 = nile_Real_div(t_122, t_123);
            nile_Real_t t_125 = nile_Real_add(v_G_y, v_J_y);
            nile_Real_t t_126 = 2;
            nile_Real_t t_127 = nile_Real_div(t_125, t_126);
            nile_Real_t t_128_1 = t_124;
            nile_Real_t t_128_2 = t_127;
            nile_Real_t t_129_x = t_128_1;
            nile_Real_t t_129_y = t_128_2;
            nile_Real_t t_121_1_x = v_G_x;
            nile_Real_t t_121_1_y = v_G_y;
            nile_Real_t t_121_2_x = t_129_x;
            nile_Real_t t_121_2_y = t_129_y;
            nile_Real_t t_121_3_x = v_J_x;
            nile_Real_t t_121_3_y = v_J_y;
            nile_Real_t t_130_a_x = t_121_1_x;
            nile_Real_t t_130_a_y = t_121_1_y;
            nile_Real_t t_130_b_x = t_121_2_x;
            nile_Real_t t_130_b_y = t_121_2_y;
            nile_Real_t t_130_c_x = t_121_3_x;
            nile_Real_t t_130_c_y = t_121_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_130_a_x);
            nile_Buffer_append(out, t_130_a_y);
            nile_Buffer_append(out, t_130_b_x);
            nile_Buffer_append(out, t_130_b_y);
            nile_Buffer_append(out, t_130_c_x);
            nile_Buffer_append(out, t_130_c_y);
        }
        else {
            nile_Real_t t_131 = nile_Real_mul(v_u_x, v_w_x);
            nile_Real_t t_132 = nile_Real_mul(v_u_y, v_w_y);
            nile_Real_t t_133 = nile_Real_add(t_131, t_132);
            nile_Real_t t_134 = nile_Real_leq(t_133, v_l);
            if (t_134) {
                nile_Real_t t_135 = nile_Real_mul(v_x_x, v_w_x);
                nile_Real_t t_136 = nile_Real_mul(v_x_y, v_w_y);
                nile_Real_t t_137 = nile_Real_add(t_135, t_136);
                nile_Real_t t_138 = nile_Real_mul(v_d, t_137);
                nile_Real_t v_p = t_138;
                nile_Real_t t_139_x = v_p;
                nile_Real_t t_139_y = v_p;
                nile_Real_t t_140_x = nile_Real_mul(t_139_x, v_x_x);
                nile_Real_t t_140_y = nile_Real_mul(t_139_y, v_x_y);
                nile_Real_t t_141_x = t_140_x;
                nile_Real_t t_141_y = t_140_y;
                nile_Real_t t_142_x = nile_Real_add(v_G_x, t_141_x);
                nile_Real_t t_142_y = nile_Real_add(v_G_y, t_141_y);
                nile_Real_t v_H_x = t_142_x;
                nile_Real_t v_H_y = t_142_y;
                nile_Real_t t_143_x = v_p;
                nile_Real_t t_143_y = v_p;
                nile_Real_t t_144_x = nile_Real_mul(t_143_x, v_y_x);
                nile_Real_t t_144_y = nile_Real_mul(t_143_y, v_y_y);
                nile_Real_t t_145_x = t_144_x;
                nile_Real_t t_145_y = t_144_y;
                nile_Real_t t_146_x = nile_Real_add(v_J_x, t_145_x);
                nile_Real_t t_146_y = nile_Real_add(v_J_y, t_145_y);
                nile_Real_t v_I_x = t_146_x;
                nile_Real_t v_I_y = t_146_y;
                nile_Real_t t_148 = nile_Real_add(v_G_x, v_H_x);
                nile_Real_t t_149 = 2;
                nile_Real_t t_150 = nile_Real_div(t_148, t_149);
                nile_Real_t t_151 = nile_Real_add(v_G_y, v_H_y);
                nile_Real_t t_152 = 2;
                nile_Real_t t_153 = nile_Real_div(t_151, t_152);
                nile_Real_t t_154_1 = t_150;
                nile_Real_t t_154_2 = t_153;
                nile_Real_t t_155_x = t_154_1;
                nile_Real_t t_155_y = t_154_2;
                nile_Real_t t_147_1_x = v_G_x;
                nile_Real_t t_147_1_y = v_G_y;
                nile_Real_t t_147_2_x = t_155_x;
                nile_Real_t t_147_2_y = t_155_y;
                nile_Real_t t_147_3_x = v_H_x;
                nile_Real_t t_147_3_y = v_H_y;
                nile_Real_t t_156_a_x = t_147_1_x;
                nile_Real_t t_156_a_y = t_147_1_y;
                nile_Real_t t_156_b_x = t_147_2_x;
                nile_Real_t t_156_b_y = t_147_2_y;
                nile_Real_t t_156_c_x = t_147_3_x;
                nile_Real_t t_156_c_y = t_147_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_156_a_x);
                nile_Buffer_append(out, t_156_a_y);
                nile_Buffer_append(out, t_156_b_x);
                nile_Buffer_append(out, t_156_b_y);
                nile_Buffer_append(out, t_156_c_x);
                nile_Buffer_append(out, t_156_c_y);
                nile_Real_t t_158 = nile_Real_add(v_H_x, v_I_x);
                nile_Real_t t_159 = 2;
                nile_Real_t t_160 = nile_Real_div(t_158, t_159);
                nile_Real_t t_161 = nile_Real_add(v_H_y, v_I_y);
                nile_Real_t t_162 = 2;
                nile_Real_t t_163 = nile_Real_div(t_161, t_162);
                nile_Real_t t_164_1 = t_160;
                nile_Real_t t_164_2 = t_163;
                nile_Real_t t_165_x = t_164_1;
                nile_Real_t t_165_y = t_164_2;
                nile_Real_t t_157_1_x = v_H_x;
                nile_Real_t t_157_1_y = v_H_y;
                nile_Real_t t_157_2_x = t_165_x;
                nile_Real_t t_157_2_y = t_165_y;
                nile_Real_t t_157_3_x = v_I_x;
                nile_Real_t t_157_3_y = v_I_y;
                nile_Real_t t_166_a_x = t_157_1_x;
                nile_Real_t t_166_a_y = t_157_1_y;
                nile_Real_t t_166_b_x = t_157_2_x;
                nile_Real_t t_166_b_y = t_157_2_y;
                nile_Real_t t_166_c_x = t_157_3_x;
                nile_Real_t t_166_c_y = t_157_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_166_a_x);
                nile_Buffer_append(out, t_166_a_y);
                nile_Buffer_append(out, t_166_b_x);
                nile_Buffer_append(out, t_166_b_y);
                nile_Buffer_append(out, t_166_c_x);
                nile_Buffer_append(out, t_166_c_y);
                nile_Real_t t_168 = nile_Real_add(v_I_x, v_J_x);
                nile_Real_t t_169 = 2;
                nile_Real_t t_170 = nile_Real_div(t_168, t_169);
                nile_Real_t t_171 = nile_Real_add(v_I_y, v_J_y);
                nile_Real_t t_172 = 2;
                nile_Real_t t_173 = nile_Real_div(t_171, t_172);
                nile_Real_t t_174_1 = t_170;
                nile_Real_t t_174_2 = t_173;
                nile_Real_t t_175_x = t_174_1;
                nile_Real_t t_175_y = t_174_2;
                nile_Real_t t_167_1_x = v_I_x;
                nile_Real_t t_167_1_y = v_I_y;
                nile_Real_t t_167_2_x = t_175_x;
                nile_Real_t t_167_2_y = t_175_y;
                nile_Real_t t_167_3_x = v_J_x;
                nile_Real_t t_167_3_y = v_J_y;
                nile_Real_t t_176_a_x = t_167_1_x;
                nile_Real_t t_176_a_y = t_167_1_y;
                nile_Real_t t_176_b_x = t_167_2_x;
                nile_Real_t t_176_b_y = t_167_2_y;
                nile_Real_t t_176_c_x = t_167_3_x;
                nile_Real_t t_176_c_y = t_167_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_176_a_x);
                nile_Buffer_append(out, t_176_a_y);
                nile_Buffer_append(out, t_176_b_x);
                nile_Buffer_append(out, t_176_b_y);
                nile_Buffer_append(out, t_176_c_x);
                nile_Buffer_append(out, t_176_c_y);
            }
            else {
                nile_Real_t t_177 = nile_Real_mul(v_u_x, v_w_x);
                nile_Real_t t_178 = nile_Real_mul(v_u_y, v_w_y);
                nile_Real_t t_179 = nile_Real_add(t_177, t_178);
                nile_Real_t t_180 = nile_Real_div(v_o, t_179);
                nile_Real_t v_q = t_180;
                nile_Real_t t_181_x = v_q;
                nile_Real_t t_181_y = v_q;
                nile_Real_t t_182_x = nile_Real_mul(t_181_x, v_w_x);
                nile_Real_t t_182_y = nile_Real_mul(t_181_y, v_w_y);
                nile_Real_t t_183_x = t_182_x;
                nile_Real_t t_183_y = t_182_y;
                nile_Real_t t_184_x = nile_Real_add(v_C_x, t_183_x);
                nile_Real_t t_184_y = nile_Real_add(v_C_y, t_183_y);
                nile_Real_t v_N_x = t_184_x;
                nile_Real_t v_N_y = t_184_y;
                nile_Real_t t_186 = nile_Real_add(v_G_x, v_N_x);
                nile_Real_t t_187 = 2;
                nile_Real_t t_188 = nile_Real_div(t_186, t_187);
                nile_Real_t t_189 = nile_Real_add(v_G_y, v_N_y);
                nile_Real_t t_190 = 2;
                nile_Real_t t_191 = nile_Real_div(t_189, t_190);
                nile_Real_t t_192_1 = t_188;
                nile_Real_t t_192_2 = t_191;
                nile_Real_t t_193_x = t_192_1;
                nile_Real_t t_193_y = t_192_2;
                nile_Real_t t_185_1_x = v_G_x;
                nile_Real_t t_185_1_y = v_G_y;
                nile_Real_t t_185_2_x = t_193_x;
                nile_Real_t t_185_2_y = t_193_y;
                nile_Real_t t_185_3_x = v_N_x;
                nile_Real_t t_185_3_y = v_N_y;
                nile_Real_t t_194_a_x = t_185_1_x;
                nile_Real_t t_194_a_y = t_185_1_y;
                nile_Real_t t_194_b_x = t_185_2_x;
                nile_Real_t t_194_b_y = t_185_2_y;
                nile_Real_t t_194_c_x = t_185_3_x;
                nile_Real_t t_194_c_y = t_185_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_194_a_x);
                nile_Buffer_append(out, t_194_a_y);
                nile_Buffer_append(out, t_194_b_x);
                nile_Buffer_append(out, t_194_b_y);
                nile_Buffer_append(out, t_194_c_x);
                nile_Buffer_append(out, t_194_c_y);
                nile_Real_t t_196 = nile_Real_add(v_N_x, v_J_x);
                nile_Real_t t_197 = 2;
                nile_Real_t t_198 = nile_Real_div(t_196, t_197);
                nile_Real_t t_199 = nile_Real_add(v_N_y, v_J_y);
                nile_Real_t t_200 = 2;
                nile_Real_t t_201 = nile_Real_div(t_199, t_200);
                nile_Real_t t_202_1 = t_198;
                nile_Real_t t_202_2 = t_201;
                nile_Real_t t_203_x = t_202_1;
                nile_Real_t t_203_y = t_202_2;
                nile_Real_t t_195_1_x = v_N_x;
                nile_Real_t t_195_1_y = v_N_y;
                nile_Real_t t_195_2_x = t_203_x;
                nile_Real_t t_195_2_y = t_203_y;
                nile_Real_t t_195_3_x = v_J_x;
                nile_Real_t t_195_3_y = v_J_y;
                nile_Real_t t_204_a_x = t_195_1_x;
                nile_Real_t t_204_a_y = t_195_1_y;
                nile_Real_t t_204_b_x = t_195_2_x;
                nile_Real_t t_204_b_y = t_195_2_y;
                nile_Real_t t_204_c_x = t_195_3_x;
                nile_Real_t t_204_c_y = t_195_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_204_a_x);
                nile_Buffer_append(out, t_204_a_y);
                nile_Buffer_append(out, t_204_b_x);
                nile_Buffer_append(out, t_204_b_y);
                nile_Buffer_append(out, t_204_c_x);
                nile_Buffer_append(out, t_204_c_y);
            }
        }
    }
    
    if (in->eos) {
    }
    else {
        k->v_l = v_l;
        k->v_d = v_d;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_o;
} gezira_StrokeJoinRound_t;

static nile_Kernel_t *gezira_StrokeJoinRound_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_StrokeJoinRound_t *k = (gezira_StrokeJoinRound_t *) k_;
    gezira_StrokeJoinRound_t *clone = (gezira_StrokeJoinRound_t *) gezira_StrokeJoin_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_StrokeJoinRound(nile_t *nl) {
    gezira_StrokeJoinRound_t *k = NILE_KERNEL_NEW(nl, gezira_StrokeJoinRound);
    return (nile_Kernel_t *) k;
}

static int gezira_StrokeJoinRound_process(nile_t *nl,
                                          nile_Kernel_t *k_,
                                          nile_Buffer_t **in_,
                                          nile_Buffer_t **out_) {
    #define IN_QUANTUM 12
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_StrokeJoinRound_t *k = (gezira_StrokeJoinRound_t *) k_;
    nile_Real_t v_o = k->v_o;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t v_D_x = nile_Buffer_shift(in);
        nile_Real_t v_D_y = nile_Buffer_shift(in);
        nile_Real_t v_E_x = nile_Buffer_shift(in);
        nile_Real_t v_E_y = nile_Buffer_shift(in);
        nile_Real_t v_F_x = nile_Buffer_shift(in);
        nile_Real_t v_F_y = nile_Buffer_shift(in);
        nile_Real_t t_2 = nile_Real_sub(v_B_y, v_C_y);
        nile_Real_t t_3 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_1_1 = t_2;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        nile_Real_t t_5 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_6 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_7 = nile_Real_add(t_5, t_6);
        nile_Real_t t_8 = nile_Real_sqr(t_7);
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_neq(t_8, t_9);
        nile_Real_t t_11 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_12 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_13 = nile_Real_add(t_11, t_12);
        nile_Real_t t_14 = nile_Real_sqr(t_13);
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_div(t_4_x, t_15_x);
        nile_Real_t t_16_y = nile_Real_div(t_4_y, t_15_y);
        nile_Real_t t_17 = 0;
        nile_Real_t t_18_x = t_17;
        nile_Real_t t_18_y = t_17;
        nile_Real_t t_19_x = t_10;
        nile_Real_t t_19_y = t_10;
        nile_Real_t t_20_x = t_19_x ? t_16_x : t_18_x;
        nile_Real_t t_20_y = t_19_y ? t_16_y : t_18_y;
        nile_Real_t v_u_x = t_20_x;
        nile_Real_t v_u_y = t_20_y;
        nile_Real_t t_22 = nile_Real_sub(v_D_y, v_E_y);
        nile_Real_t t_23 = nile_Real_sub(v_E_x, v_D_x);
        nile_Real_t t_21_1 = t_22;
        nile_Real_t t_21_2 = t_23;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        nile_Real_t t_25 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_26 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_27 = nile_Real_add(t_25, t_26);
        nile_Real_t t_28 = nile_Real_sqr(t_27);
        nile_Real_t t_29 = 0;
        nile_Real_t t_30 = nile_Real_neq(t_28, t_29);
        nile_Real_t t_31 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_32 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_33 = nile_Real_add(t_31, t_32);
        nile_Real_t t_34 = nile_Real_sqr(t_33);
        nile_Real_t t_35_x = t_34;
        nile_Real_t t_35_y = t_34;
        nile_Real_t t_36_x = nile_Real_div(t_24_x, t_35_x);
        nile_Real_t t_36_y = nile_Real_div(t_24_y, t_35_y);
        nile_Real_t t_37 = 0;
        nile_Real_t t_38_x = t_37;
        nile_Real_t t_38_y = t_37;
        nile_Real_t t_39_x = t_30;
        nile_Real_t t_39_y = t_30;
        nile_Real_t t_40_x = t_39_x ? t_36_x : t_38_x;
        nile_Real_t t_40_y = t_39_y ? t_36_y : t_38_y;
        nile_Real_t v_v_x = t_40_x;
        nile_Real_t v_v_y = t_40_y;
        nile_Real_t t_42 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_43 = nile_Real_sub(v_C_y, v_B_y);
        nile_Real_t t_41_1 = t_42;
        nile_Real_t t_41_2 = t_43;
        nile_Real_t t_44_x = t_41_1;
        nile_Real_t t_44_y = t_41_2;
        nile_Real_t t_45 = nile_Real_mul(t_44_x, t_44_x);
        nile_Real_t t_46 = nile_Real_mul(t_44_y, t_44_y);
        nile_Real_t t_47 = nile_Real_add(t_45, t_46);
        nile_Real_t t_48 = nile_Real_sqr(t_47);
        nile_Real_t t_49 = 0;
        nile_Real_t t_50 = nile_Real_neq(t_48, t_49);
        nile_Real_t t_51 = nile_Real_mul(t_44_x, t_44_x);
        nile_Real_t t_52 = nile_Real_mul(t_44_y, t_44_y);
        nile_Real_t t_53 = nile_Real_add(t_51, t_52);
        nile_Real_t t_54 = nile_Real_sqr(t_53);
        nile_Real_t t_55_x = t_54;
        nile_Real_t t_55_y = t_54;
        nile_Real_t t_56_x = nile_Real_div(t_44_x, t_55_x);
        nile_Real_t t_56_y = nile_Real_div(t_44_y, t_55_y);
        nile_Real_t t_57 = 0;
        nile_Real_t t_58_x = t_57;
        nile_Real_t t_58_y = t_57;
        nile_Real_t t_59_x = t_50;
        nile_Real_t t_59_y = t_50;
        nile_Real_t t_60_x = t_59_x ? t_56_x : t_58_x;
        nile_Real_t t_60_y = t_59_y ? t_56_y : t_58_y;
        nile_Real_t v_x_x = t_60_x;
        nile_Real_t v_x_y = t_60_y;
        nile_Real_t t_62 = nile_Real_sub(v_D_x, v_E_x);
        nile_Real_t t_63 = nile_Real_sub(v_D_y, v_E_y);
        nile_Real_t t_61_1 = t_62;
        nile_Real_t t_61_2 = t_63;
        nile_Real_t t_64_x = t_61_1;
        nile_Real_t t_64_y = t_61_2;
        nile_Real_t t_65 = nile_Real_mul(t_64_x, t_64_x);
        nile_Real_t t_66 = nile_Real_mul(t_64_y, t_64_y);
        nile_Real_t t_67 = nile_Real_add(t_65, t_66);
        nile_Real_t t_68 = nile_Real_sqr(t_67);
        nile_Real_t t_69 = 0;
        nile_Real_t t_70 = nile_Real_neq(t_68, t_69);
        nile_Real_t t_71 = nile_Real_mul(t_64_x, t_64_x);
        nile_Real_t t_72 = nile_Real_mul(t_64_y, t_64_y);
        nile_Real_t t_73 = nile_Real_add(t_71, t_72);
        nile_Real_t t_74 = nile_Real_sqr(t_73);
        nile_Real_t t_75_x = t_74;
        nile_Real_t t_75_y = t_74;
        nile_Real_t t_76_x = nile_Real_div(t_64_x, t_75_x);
        nile_Real_t t_76_y = nile_Real_div(t_64_y, t_75_y);
        nile_Real_t t_77 = 0;
        nile_Real_t t_78_x = t_77;
        nile_Real_t t_78_y = t_77;
        nile_Real_t t_79_x = t_70;
        nile_Real_t t_79_y = t_70;
        nile_Real_t t_80_x = t_79_x ? t_76_x : t_78_x;
        nile_Real_t t_80_y = t_79_y ? t_76_y : t_78_y;
        nile_Real_t v_y_x = t_80_x;
        nile_Real_t v_y_y = t_80_y;
        nile_Real_t t_81_x = nile_Real_add(v_x_x, v_y_x);
        nile_Real_t t_81_y = nile_Real_add(v_x_y, v_y_y);
        nile_Real_t t_82 = nile_Real_mul(t_81_x, t_81_x);
        nile_Real_t t_83 = nile_Real_mul(t_81_y, t_81_y);
        nile_Real_t t_84 = nile_Real_add(t_82, t_83);
        nile_Real_t t_85 = nile_Real_sqr(t_84);
        nile_Real_t t_86 = 0;
        nile_Real_t t_87 = nile_Real_neq(t_85, t_86);
        nile_Real_t t_88 = nile_Real_mul(t_81_x, t_81_x);
        nile_Real_t t_89 = nile_Real_mul(t_81_y, t_81_y);
        nile_Real_t t_90 = nile_Real_add(t_88, t_89);
        nile_Real_t t_91 = nile_Real_sqr(t_90);
        nile_Real_t t_92_x = t_91;
        nile_Real_t t_92_y = t_91;
        nile_Real_t t_93_x = nile_Real_div(t_81_x, t_92_x);
        nile_Real_t t_93_y = nile_Real_div(t_81_y, t_92_y);
        nile_Real_t t_94 = 0;
        nile_Real_t t_95_x = t_94;
        nile_Real_t t_95_y = t_94;
        nile_Real_t t_96_x = t_87;
        nile_Real_t t_96_y = t_87;
        nile_Real_t t_97_x = t_96_x ? t_93_x : t_95_x;
        nile_Real_t t_97_y = t_96_y ? t_93_y : t_95_y;
        nile_Real_t t_98 = 0;
        nile_Real_t t_99_x = t_98;
        nile_Real_t t_99_y = t_98;
        nile_Real_t t_100 = nile_Real_eq(t_97_x, t_99_x);
        nile_Real_t t_101 = nile_Real_eq(t_97_y, t_99_y);
        nile_Real_t t_102 = nile_Real_and(t_100, t_101);
        nile_Real_t t_103 = 0;
        nile_Real_t t_104 = nile_Real_eq(t_102, t_103);
        nile_Real_t t_105_x = t_104;
        nile_Real_t t_105_y = t_104;
        nile_Real_t t_106_x = t_105_x ? t_97_x : v_u_x;
        nile_Real_t t_106_y = t_105_y ? t_97_y : v_u_y;
        nile_Real_t v_w_x = t_106_x;
        nile_Real_t v_w_y = t_106_y;
        nile_Real_t t_107_x = v_o;
        nile_Real_t t_107_y = v_o;
        nile_Real_t t_108_x = nile_Real_mul(t_107_x, v_u_x);
        nile_Real_t t_108_y = nile_Real_mul(t_107_y, v_u_y);
        nile_Real_t t_109_x = t_108_x;
        nile_Real_t t_109_y = t_108_y;
        nile_Real_t t_110_x = nile_Real_add(v_C_x, t_109_x);
        nile_Real_t t_110_y = nile_Real_add(v_C_y, t_109_y);
        nile_Real_t v_G_x = t_110_x;
        nile_Real_t v_G_y = t_110_y;
        nile_Real_t t_111_x = v_o;
        nile_Real_t t_111_y = v_o;
        nile_Real_t t_112_x = nile_Real_mul(t_111_x, v_v_x);
        nile_Real_t t_112_y = nile_Real_mul(t_111_y, v_v_y);
        nile_Real_t t_113_x = t_112_x;
        nile_Real_t t_113_y = t_112_y;
        nile_Real_t t_114_x = nile_Real_add(v_C_x, t_113_x);
        nile_Real_t t_114_y = nile_Real_add(v_C_y, t_113_y);
        nile_Real_t v_J_x = t_114_x;
        nile_Real_t v_J_y = t_114_y;
        nile_Real_t t_115 = nile_Real_mul(v_u_x, v_w_x);
        nile_Real_t t_116 = nile_Real_mul(v_u_y, v_w_y);
        nile_Real_t t_117 = nile_Real_add(t_115, t_116);
        nile_Real_t t_118 = 0.01;
        nile_Real_t t_119 = nile_Real_neg(t_118);
        nile_Real_t t_120 = nile_Real_lt(t_117, t_119);
        if (t_120) {
            nile_Real_t t_122 = nile_Real_add(v_G_x, v_J_x);
            nile_Real_t t_123 = 2;
            nile_Real_t t_124 = nile_Real_div(t_122, t_123);
            nile_Real_t t_125 = nile_Real_add(v_G_y, v_J_y);
            nile_Real_t t_126 = 2;
            nile_Real_t t_127 = nile_Real_div(t_125, t_126);
            nile_Real_t t_128_1 = t_124;
            nile_Real_t t_128_2 = t_127;
            nile_Real_t t_129_x = t_128_1;
            nile_Real_t t_129_y = t_128_2;
            nile_Real_t t_121_1_x = v_G_x;
            nile_Real_t t_121_1_y = v_G_y;
            nile_Real_t t_121_2_x = t_129_x;
            nile_Real_t t_121_2_y = t_129_y;
            nile_Real_t t_121_3_x = v_J_x;
            nile_Real_t t_121_3_y = v_J_y;
            nile_Real_t t_130_a_x = t_121_1_x;
            nile_Real_t t_130_a_y = t_121_1_y;
            nile_Real_t t_130_b_x = t_121_2_x;
            nile_Real_t t_130_b_y = t_121_2_y;
            nile_Real_t t_130_c_x = t_121_3_x;
            nile_Real_t t_130_c_y = t_121_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_130_a_x);
            nile_Buffer_append(out, t_130_a_y);
            nile_Buffer_append(out, t_130_b_x);
            nile_Buffer_append(out, t_130_b_y);
            nile_Buffer_append(out, t_130_c_x);
            nile_Buffer_append(out, t_130_c_y);
        }
        else {
            nile_Real_t t_131 = nile_Real_mul(v_u_x, v_w_x);
            nile_Real_t t_132 = nile_Real_mul(v_u_y, v_w_y);
            nile_Real_t t_133 = nile_Real_add(t_131, t_132);
            nile_Real_t t_134 = 0.9;
            nile_Real_t t_135 = nile_Real_lt(t_133, t_134);
            if (t_135) {
                nile_Real_t t_137_x = nile_Real_neg(v_w_x);
                nile_Real_t t_137_y = nile_Real_neg(v_w_y);
                nile_Real_t t_136_1 = v_w_y;
                nile_Real_t t_136_2 = t_137_x;
                nile_Real_t v_z_1 = t_136_1;
                nile_Real_t v_z_2 = t_136_2;
                nile_Real_t t_139_1_x = v_A_x;
                nile_Real_t t_139_1_y = v_A_y;
                nile_Real_t t_139_2_x = v_B_x;
                nile_Real_t t_139_2_y = v_B_y;
                nile_Real_t t_139_3_x = v_C_x;
                nile_Real_t t_139_3_y = v_C_y;
                nile_Real_t t_141_x = v_z_1;
                nile_Real_t t_141_y = v_z_2;
                nile_Real_t t_142_x = nile_Real_add(v_C_x, t_141_x);
                nile_Real_t t_142_y = nile_Real_add(v_C_y, t_141_y);
                nile_Real_t t_143_x = v_z_1;
                nile_Real_t t_143_y = v_z_2;
                nile_Real_t t_144_x = nile_Real_add(v_C_x, t_143_x);
                nile_Real_t t_144_y = nile_Real_add(v_C_y, t_143_y);
                nile_Real_t t_140_1_x = v_C_x;
                nile_Real_t t_140_1_y = v_C_y;
                nile_Real_t t_140_2_x = t_142_x;
                nile_Real_t t_140_2_y = t_142_y;
                nile_Real_t t_140_3_x = t_144_x;
                nile_Real_t t_140_3_y = t_144_y;
                nile_Real_t t_138_1_1_x = t_139_1_x;
                nile_Real_t t_138_1_1_y = t_139_1_y;
                nile_Real_t t_138_1_2_x = t_139_2_x;
                nile_Real_t t_138_1_2_y = t_139_2_y;
                nile_Real_t t_138_1_3_x = t_139_3_x;
                nile_Real_t t_138_1_3_y = t_139_3_y;
                nile_Real_t t_138_2_1_x = t_140_1_x;
                nile_Real_t t_138_2_1_y = t_140_1_y;
                nile_Real_t t_138_2_2_x = t_140_2_x;
                nile_Real_t t_138_2_2_y = t_140_2_y;
                nile_Real_t t_138_2_3_x = t_140_3_x;
                nile_Real_t t_138_2_3_y = t_140_3_y;
                nile_Real_t t_145_1_a_x = t_138_1_1_x;
                nile_Real_t t_145_1_a_y = t_138_1_1_y;
                nile_Real_t t_145_1_b_x = t_138_1_2_x;
                nile_Real_t t_145_1_b_y = t_138_1_2_y;
                nile_Real_t t_145_1_c_x = t_138_1_3_x;
                nile_Real_t t_145_1_c_y = t_138_1_3_y;
                nile_Real_t t_145_2_a_x = t_138_2_1_x;
                nile_Real_t t_145_2_a_y = t_138_2_1_y;
                nile_Real_t t_145_2_b_x = t_138_2_2_x;
                nile_Real_t t_145_2_b_y = t_138_2_2_y;
                nile_Real_t t_145_2_c_x = t_138_2_3_x;
                nile_Real_t t_145_2_c_y = t_138_2_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_145_1_a_x);
                nile_Buffer_prepend(in, t_145_1_a_y);
                nile_Buffer_prepend(in, t_145_1_b_x);
                nile_Buffer_prepend(in, t_145_1_b_y);
                nile_Buffer_prepend(in, t_145_1_c_x);
                nile_Buffer_prepend(in, t_145_1_c_y);
                nile_Buffer_prepend(in, t_145_2_a_x);
                nile_Buffer_prepend(in, t_145_2_a_y);
                nile_Buffer_prepend(in, t_145_2_b_x);
                nile_Buffer_prepend(in, t_145_2_b_y);
                nile_Buffer_prepend(in, t_145_2_c_x);
                nile_Buffer_prepend(in, t_145_2_c_y);
                in->i -= IN_QUANTUM;
                nile_Real_t t_148_x = v_z_1;
                nile_Real_t t_148_y = v_z_2;
                nile_Real_t t_149_x = nile_Real_sub(v_C_x, t_148_x);
                nile_Real_t t_149_y = nile_Real_sub(v_C_y, t_148_y);
                nile_Real_t t_150_x = v_z_1;
                nile_Real_t t_150_y = v_z_2;
                nile_Real_t t_151_x = nile_Real_sub(v_C_x, t_150_x);
                nile_Real_t t_151_y = nile_Real_sub(v_C_y, t_150_y);
                nile_Real_t t_147_1_x = t_149_x;
                nile_Real_t t_147_1_y = t_149_y;
                nile_Real_t t_147_2_x = t_151_x;
                nile_Real_t t_147_2_y = t_151_y;
                nile_Real_t t_147_3_x = v_C_x;
                nile_Real_t t_147_3_y = v_C_y;
                nile_Real_t t_152_1_x = v_D_x;
                nile_Real_t t_152_1_y = v_D_y;
                nile_Real_t t_152_2_x = v_E_x;
                nile_Real_t t_152_2_y = v_E_y;
                nile_Real_t t_152_3_x = v_F_x;
                nile_Real_t t_152_3_y = v_F_y;
                nile_Real_t t_146_1_1_x = t_147_1_x;
                nile_Real_t t_146_1_1_y = t_147_1_y;
                nile_Real_t t_146_1_2_x = t_147_2_x;
                nile_Real_t t_146_1_2_y = t_147_2_y;
                nile_Real_t t_146_1_3_x = t_147_3_x;
                nile_Real_t t_146_1_3_y = t_147_3_y;
                nile_Real_t t_146_2_1_x = t_152_1_x;
                nile_Real_t t_146_2_1_y = t_152_1_y;
                nile_Real_t t_146_2_2_x = t_152_2_x;
                nile_Real_t t_146_2_2_y = t_152_2_y;
                nile_Real_t t_146_2_3_x = t_152_3_x;
                nile_Real_t t_146_2_3_y = t_152_3_y;
                nile_Real_t t_153_1_a_x = t_146_1_1_x;
                nile_Real_t t_153_1_a_y = t_146_1_1_y;
                nile_Real_t t_153_1_b_x = t_146_1_2_x;
                nile_Real_t t_153_1_b_y = t_146_1_2_y;
                nile_Real_t t_153_1_c_x = t_146_1_3_x;
                nile_Real_t t_153_1_c_y = t_146_1_3_y;
                nile_Real_t t_153_2_a_x = t_146_2_1_x;
                nile_Real_t t_153_2_a_y = t_146_2_1_y;
                nile_Real_t t_153_2_b_x = t_146_2_2_x;
                nile_Real_t t_153_2_b_y = t_146_2_2_y;
                nile_Real_t t_153_2_c_x = t_146_2_3_x;
                nile_Real_t t_153_2_c_y = t_146_2_3_y;
                in = nile_Buffer_prepare_to_prepend(nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend(in, t_153_1_a_x);
                nile_Buffer_prepend(in, t_153_1_a_y);
                nile_Buffer_prepend(in, t_153_1_b_x);
                nile_Buffer_prepend(in, t_153_1_b_y);
                nile_Buffer_prepend(in, t_153_1_c_x);
                nile_Buffer_prepend(in, t_153_1_c_y);
                nile_Buffer_prepend(in, t_153_2_a_x);
                nile_Buffer_prepend(in, t_153_2_a_y);
                nile_Buffer_prepend(in, t_153_2_b_x);
                nile_Buffer_prepend(in, t_153_2_b_y);
                nile_Buffer_prepend(in, t_153_2_c_x);
                nile_Buffer_prepend(in, t_153_2_c_y);
                in->i -= IN_QUANTUM;
            }
            else {
                nile_Real_t t_154_x = v_o;
                nile_Real_t t_154_y = v_o;
                nile_Real_t t_155_x = nile_Real_mul(t_154_x, v_w_x);
                nile_Real_t t_155_y = nile_Real_mul(t_154_y, v_w_y);
                nile_Real_t t_156_x = t_155_x;
                nile_Real_t t_156_y = t_155_y;
                nile_Real_t t_157_x = nile_Real_add(v_C_x, t_156_x);
                nile_Real_t t_157_y = nile_Real_add(v_C_y, t_156_y);
                nile_Real_t v_N_x = t_157_x;
                nile_Real_t v_N_y = t_157_y;
                nile_Real_t t_158 = 2;
                nile_Real_t t_159_x = t_158;
                nile_Real_t t_159_y = t_158;
                nile_Real_t t_160_x = nile_Real_mul(t_159_x, v_N_x);
                nile_Real_t t_160_y = nile_Real_mul(t_159_y, v_N_y);
                nile_Real_t t_161 = nile_Real_add(v_G_x, v_J_x);
                nile_Real_t t_162 = 2;
                nile_Real_t t_163 = nile_Real_div(t_161, t_162);
                nile_Real_t t_164 = nile_Real_add(v_G_y, v_J_y);
                nile_Real_t t_165 = 2;
                nile_Real_t t_166 = nile_Real_div(t_164, t_165);
                nile_Real_t t_167_1 = t_163;
                nile_Real_t t_167_2 = t_166;
                nile_Real_t t_168_x = t_167_1;
                nile_Real_t t_168_y = t_167_2;
                nile_Real_t t_169_x = nile_Real_sub(t_160_x, t_168_x);
                nile_Real_t t_169_y = nile_Real_sub(t_160_y, t_168_y);
                nile_Real_t v_H_x = t_169_x;
                nile_Real_t v_H_y = t_169_y;
                nile_Real_t t_170_1_x = v_G_x;
                nile_Real_t t_170_1_y = v_G_y;
                nile_Real_t t_170_2_x = v_H_x;
                nile_Real_t t_170_2_y = v_H_y;
                nile_Real_t t_170_3_x = v_J_x;
                nile_Real_t t_170_3_y = v_J_y;
                nile_Real_t t_171_a_x = t_170_1_x;
                nile_Real_t t_171_a_y = t_170_1_y;
                nile_Real_t t_171_b_x = t_170_2_x;
                nile_Real_t t_171_b_y = t_170_2_y;
                nile_Real_t t_171_c_x = t_170_3_x;
                nile_Real_t t_171_c_y = t_170_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_171_a_x);
                nile_Buffer_append(out, t_171_a_y);
                nile_Buffer_append(out, t_171_b_x);
                nile_Buffer_append(out, t_171_b_y);
                nile_Buffer_append(out, t_171_c_x);
                nile_Buffer_append(out, t_171_c_y);
            }
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

typedef struct {
    nile_Kernel_t base;
} gezira_PrepareBeziersForStroke_t;

static nile_Kernel_t *gezira_PrepareBeziersForStroke_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_PrepareBeziersForStroke_t *k = (gezira_PrepareBeziersForStroke_t *) k_;
    gezira_PrepareBeziersForStroke_t *clone = (gezira_PrepareBeziersForStroke_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_PrepareBeziersForStroke(nile_t *nl) {
    gezira_PrepareBeziersForStroke_t *k = NILE_KERNEL_NEW(nl, gezira_PrepareBeziersForStroke);
    return (nile_Kernel_t *) k;
}

static int gezira_PrepareBeziersForStroke_process(nile_t *nl,
                                                  nile_Kernel_t *k_,
                                                  nile_Buffer_t **in_,
                                                  nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_PrepareBeziersForStroke_t *k = (gezira_PrepareBeziersForStroke_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_2 = nile_Real_sub(v_A_y, v_B_y);
        nile_Real_t t_3 = nile_Real_sub(v_B_x, v_A_x);
        nile_Real_t t_1_1 = t_2;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        nile_Real_t t_5 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_6 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_7 = nile_Real_add(t_5, t_6);
        nile_Real_t t_8 = nile_Real_sqr(t_7);
        nile_Real_t t_9 = 0;
        nile_Real_t t_10 = nile_Real_neq(t_8, t_9);
        nile_Real_t t_11 = nile_Real_mul(t_4_x, t_4_x);
        nile_Real_t t_12 = nile_Real_mul(t_4_y, t_4_y);
        nile_Real_t t_13 = nile_Real_add(t_11, t_12);
        nile_Real_t t_14 = nile_Real_sqr(t_13);
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_div(t_4_x, t_15_x);
        nile_Real_t t_16_y = nile_Real_div(t_4_y, t_15_y);
        nile_Real_t t_17 = 0;
        nile_Real_t t_18_x = t_17;
        nile_Real_t t_18_y = t_17;
        nile_Real_t t_19_x = t_10;
        nile_Real_t t_19_y = t_10;
        nile_Real_t t_20_x = t_19_x ? t_16_x : t_18_x;
        nile_Real_t t_20_y = t_19_y ? t_16_y : t_18_y;
        nile_Real_t v_u_x = t_20_x;
        nile_Real_t v_u_y = t_20_y;
        nile_Real_t t_22 = nile_Real_sub(v_B_y, v_C_y);
        nile_Real_t t_23 = nile_Real_sub(v_C_x, v_B_x);
        nile_Real_t t_21_1 = t_22;
        nile_Real_t t_21_2 = t_23;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        nile_Real_t t_25 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_26 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_27 = nile_Real_add(t_25, t_26);
        nile_Real_t t_28 = nile_Real_sqr(t_27);
        nile_Real_t t_29 = 0;
        nile_Real_t t_30 = nile_Real_neq(t_28, t_29);
        nile_Real_t t_31 = nile_Real_mul(t_24_x, t_24_x);
        nile_Real_t t_32 = nile_Real_mul(t_24_y, t_24_y);
        nile_Real_t t_33 = nile_Real_add(t_31, t_32);
        nile_Real_t t_34 = nile_Real_sqr(t_33);
        nile_Real_t t_35_x = t_34;
        nile_Real_t t_35_y = t_34;
        nile_Real_t t_36_x = nile_Real_div(t_24_x, t_35_x);
        nile_Real_t t_36_y = nile_Real_div(t_24_y, t_35_y);
        nile_Real_t t_37 = 0;
        nile_Real_t t_38_x = t_37;
        nile_Real_t t_38_y = t_37;
        nile_Real_t t_39_x = t_30;
        nile_Real_t t_39_y = t_30;
        nile_Real_t t_40_x = t_39_x ? t_36_x : t_38_x;
        nile_Real_t t_40_y = t_39_y ? t_36_y : t_38_y;
        nile_Real_t v_v_x = t_40_x;
        nile_Real_t v_v_y = t_40_y;
        nile_Real_t t_41 = nile_Real_mul(v_u_x, v_v_x);
        nile_Real_t t_42 = nile_Real_mul(v_u_y, v_v_y);
        nile_Real_t t_43 = nile_Real_add(t_41, t_42);
        nile_Real_t t_44 = 0.9999;
        nile_Real_t t_45 = nile_Real_neg(t_44);
        nile_Real_t t_46 = nile_Real_lt(t_43, t_45);
        if (t_46) {
            nile_Real_t t_47_x = nile_Real_sub(v_A_x, v_B_x);
            nile_Real_t t_47_y = nile_Real_sub(v_A_y, v_B_y);
            nile_Real_t t_48 = 2;
            nile_Real_t t_49_x = t_48;
            nile_Real_t t_49_y = t_48;
            nile_Real_t t_50_x = nile_Real_mul(t_49_x, v_B_x);
            nile_Real_t t_50_y = nile_Real_mul(t_49_y, v_B_y);
            nile_Real_t t_51_x = nile_Real_sub(v_A_x, t_50_x);
            nile_Real_t t_51_y = nile_Real_sub(v_A_y, t_50_y);
            nile_Real_t t_52_x = nile_Real_add(t_51_x, v_C_x);
            nile_Real_t t_52_y = nile_Real_add(t_51_y, v_C_y);
            nile_Real_t t_53 = 1;
            nile_Real_t t_54_x = t_53;
            nile_Real_t t_54_y = t_53;
            nile_Real_t t_55 = 0;
            nile_Real_t t_56 = nile_Real_neq(t_52_x, t_55);
            nile_Real_t t_57 = t_56 ? t_52_x : t_54_x;
            nile_Real_t t_58 = 0;
            nile_Real_t t_59 = nile_Real_neq(t_52_y, t_58);
            nile_Real_t t_60 = t_59 ? t_52_y : t_54_y;
            nile_Real_t t_61_1 = t_57;
            nile_Real_t t_61_2 = t_60;
            nile_Real_t t_62_x = t_61_1;
            nile_Real_t t_62_y = t_61_2;
            nile_Real_t t_63_x = nile_Real_div(t_47_x, t_62_x);
            nile_Real_t t_63_y = nile_Real_div(t_47_y, t_62_y);
            nile_Real_t v_L_x = t_63_x;
            nile_Real_t v_L_y = t_63_y;
            nile_Real_t t_64 = 0;
            nile_Real_t t_65 = nile_Real_neq(v_L_x, t_64);
            nile_Real_t t_66 = t_65 ? v_L_x : v_L_y;
            nile_Real_t v_t = t_66;
            nile_Real_t t_67 = 1;
            nile_Real_t t_68 = nile_Real_sub(t_67, v_t);
            nile_Real_t t_69 = 1;
            nile_Real_t t_70 = nile_Real_sub(t_69, v_t);
            nile_Real_t t_71 = nile_Real_mul(t_68, t_70);
            nile_Real_t t_72_x = t_71;
            nile_Real_t t_72_y = t_71;
            nile_Real_t t_73_x = nile_Real_mul(t_72_x, v_A_x);
            nile_Real_t t_73_y = nile_Real_mul(t_72_y, v_A_y);
            nile_Real_t t_74 = 2;
            nile_Real_t t_75 = 1;
            nile_Real_t t_76 = nile_Real_sub(t_75, v_t);
            nile_Real_t t_77 = nile_Real_mul(t_74, t_76);
            nile_Real_t t_78 = nile_Real_mul(t_77, v_t);
            nile_Real_t t_79_x = t_78;
            nile_Real_t t_79_y = t_78;
            nile_Real_t t_80_x = nile_Real_mul(t_79_x, v_B_x);
            nile_Real_t t_80_y = nile_Real_mul(t_79_y, v_B_y);
            nile_Real_t t_81_x = nile_Real_add(t_73_x, t_80_x);
            nile_Real_t t_81_y = nile_Real_add(t_73_y, t_80_y);
            nile_Real_t t_82 = nile_Real_mul(v_t, v_t);
            nile_Real_t t_83_x = t_82;
            nile_Real_t t_83_y = t_82;
            nile_Real_t t_84_x = nile_Real_mul(t_83_x, v_C_x);
            nile_Real_t t_84_y = nile_Real_mul(t_83_y, v_C_y);
            nile_Real_t t_85_x = nile_Real_add(t_81_x, t_84_x);
            nile_Real_t t_85_y = nile_Real_add(t_81_y, t_84_y);
            nile_Real_t v_M_x = t_85_x;
            nile_Real_t v_M_y = t_85_y;
            nile_Real_t t_87 = nile_Real_add(v_A_x, v_M_x);
            nile_Real_t t_88 = 2;
            nile_Real_t t_89 = nile_Real_div(t_87, t_88);
            nile_Real_t t_90 = nile_Real_add(v_A_y, v_M_y);
            nile_Real_t t_91 = 2;
            nile_Real_t t_92 = nile_Real_div(t_90, t_91);
            nile_Real_t t_93_1 = t_89;
            nile_Real_t t_93_2 = t_92;
            nile_Real_t t_94_x = t_93_1;
            nile_Real_t t_94_y = t_93_2;
            nile_Real_t t_86_1_x = v_A_x;
            nile_Real_t t_86_1_y = v_A_y;
            nile_Real_t t_86_2_x = t_94_x;
            nile_Real_t t_86_2_y = t_94_y;
            nile_Real_t t_86_3_x = v_M_x;
            nile_Real_t t_86_3_y = v_M_y;
            nile_Real_t t_95_a_x = t_86_1_x;
            nile_Real_t t_95_a_y = t_86_1_y;
            nile_Real_t t_95_b_x = t_86_2_x;
            nile_Real_t t_95_b_y = t_86_2_y;
            nile_Real_t t_95_c_x = t_86_3_x;
            nile_Real_t t_95_c_y = t_86_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_95_a_x);
            nile_Buffer_append(out, t_95_a_y);
            nile_Buffer_append(out, t_95_b_x);
            nile_Buffer_append(out, t_95_b_y);
            nile_Buffer_append(out, t_95_c_x);
            nile_Buffer_append(out, t_95_c_y);
            nile_Real_t t_97 = nile_Real_add(v_M_x, v_C_x);
            nile_Real_t t_98 = 2;
            nile_Real_t t_99 = nile_Real_div(t_97, t_98);
            nile_Real_t t_100 = nile_Real_add(v_M_y, v_C_y);
            nile_Real_t t_101 = 2;
            nile_Real_t t_102 = nile_Real_div(t_100, t_101);
            nile_Real_t t_103_1 = t_99;
            nile_Real_t t_103_2 = t_102;
            nile_Real_t t_104_x = t_103_1;
            nile_Real_t t_104_y = t_103_2;
            nile_Real_t t_96_1_x = v_M_x;
            nile_Real_t t_96_1_y = v_M_y;
            nile_Real_t t_96_2_x = t_104_x;
            nile_Real_t t_96_2_y = t_104_y;
            nile_Real_t t_96_3_x = v_C_x;
            nile_Real_t t_96_3_y = v_C_y;
            nile_Real_t t_105_a_x = t_96_1_x;
            nile_Real_t t_105_a_y = t_96_1_y;
            nile_Real_t t_105_b_x = t_96_2_x;
            nile_Real_t t_105_b_y = t_96_2_y;
            nile_Real_t t_105_c_x = t_96_3_x;
            nile_Real_t t_105_c_y = t_96_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_105_a_x);
            nile_Buffer_append(out, t_105_a_y);
            nile_Buffer_append(out, t_105_b_x);
            nile_Buffer_append(out, t_105_b_y);
            nile_Buffer_append(out, t_105_c_x);
            nile_Buffer_append(out, t_105_c_y);
        }
        else {
            nile_Real_t t_106 = 0;
            nile_Real_t t_107_x = t_106;
            nile_Real_t t_107_y = t_106;
            nile_Real_t t_108 = nile_Real_eq(v_u_x, t_107_x);
            nile_Real_t t_109 = nile_Real_eq(v_u_y, t_107_y);
            nile_Real_t t_110 = nile_Real_and(t_108, t_109);
            nile_Real_t t_111 = 0;
            nile_Real_t t_112_x = t_111;
            nile_Real_t t_112_y = t_111;
            nile_Real_t t_113 = nile_Real_eq(v_v_x, t_112_x);
            nile_Real_t t_114 = nile_Real_eq(v_v_y, t_112_y);
            nile_Real_t t_115 = nile_Real_and(t_113, t_114);
            nile_Real_t t_116 = nile_Real_or(t_110, t_115);
            if (t_116) {
                nile_Real_t t_117 = nile_Real_add(v_A_x, v_C_x);
                nile_Real_t t_118 = 2;
                nile_Real_t t_119 = nile_Real_div(t_117, t_118);
                nile_Real_t t_120 = nile_Real_add(v_A_y, v_C_y);
                nile_Real_t t_121 = 2;
                nile_Real_t t_122 = nile_Real_div(t_120, t_121);
                nile_Real_t t_123_1 = t_119;
                nile_Real_t t_123_2 = t_122;
                nile_Real_t t_124_x = t_123_1;
                nile_Real_t t_124_y = t_123_2;
                nile_Real_t v_M_x = t_124_x;
                nile_Real_t v_M_y = t_124_y;
                nile_Real_t t_126 = nile_Real_sub(v_A_y, v_M_y);
                nile_Real_t t_127 = nile_Real_sub(v_M_x, v_A_x);
                nile_Real_t t_125_1 = t_126;
                nile_Real_t t_125_2 = t_127;
                nile_Real_t t_128_x = t_125_1;
                nile_Real_t t_128_y = t_125_2;
                nile_Real_t t_129 = nile_Real_mul(t_128_x, t_128_x);
                nile_Real_t t_130 = nile_Real_mul(t_128_y, t_128_y);
                nile_Real_t t_131 = nile_Real_add(t_129, t_130);
                nile_Real_t t_132 = nile_Real_sqr(t_131);
                nile_Real_t t_133 = 0;
                nile_Real_t t_134 = nile_Real_neq(t_132, t_133);
                nile_Real_t t_135 = nile_Real_mul(t_128_x, t_128_x);
                nile_Real_t t_136 = nile_Real_mul(t_128_y, t_128_y);
                nile_Real_t t_137 = nile_Real_add(t_135, t_136);
                nile_Real_t t_138 = nile_Real_sqr(t_137);
                nile_Real_t t_139_x = t_138;
                nile_Real_t t_139_y = t_138;
                nile_Real_t t_140_x = nile_Real_div(t_128_x, t_139_x);
                nile_Real_t t_140_y = nile_Real_div(t_128_y, t_139_y);
                nile_Real_t t_141 = 0;
                nile_Real_t t_142_x = t_141;
                nile_Real_t t_142_y = t_141;
                nile_Real_t t_143_x = t_134;
                nile_Real_t t_143_y = t_134;
                nile_Real_t t_144_x = t_143_x ? t_140_x : t_142_x;
                nile_Real_t t_144_y = t_143_y ? t_140_y : t_142_y;
                nile_Real_t t_145 = 0;
                nile_Real_t t_146_x = t_145;
                nile_Real_t t_146_y = t_145;
                nile_Real_t t_147 = nile_Real_eq(t_144_x, t_146_x);
                nile_Real_t t_148 = nile_Real_eq(t_144_y, t_146_y);
                nile_Real_t t_149 = nile_Real_and(t_147, t_148);
                nile_Real_t t_150 = 0;
                nile_Real_t t_151 = nile_Real_eq(t_149, t_150);
                nile_Real_t t_153 = nile_Real_sub(v_M_y, v_C_y);
                nile_Real_t t_154 = nile_Real_sub(v_C_x, v_M_x);
                nile_Real_t t_152_1 = t_153;
                nile_Real_t t_152_2 = t_154;
                nile_Real_t t_155_x = t_152_1;
                nile_Real_t t_155_y = t_152_2;
                nile_Real_t t_156 = nile_Real_mul(t_155_x, t_155_x);
                nile_Real_t t_157 = nile_Real_mul(t_155_y, t_155_y);
                nile_Real_t t_158 = nile_Real_add(t_156, t_157);
                nile_Real_t t_159 = nile_Real_sqr(t_158);
                nile_Real_t t_160 = 0;
                nile_Real_t t_161 = nile_Real_neq(t_159, t_160);
                nile_Real_t t_162 = nile_Real_mul(t_155_x, t_155_x);
                nile_Real_t t_163 = nile_Real_mul(t_155_y, t_155_y);
                nile_Real_t t_164 = nile_Real_add(t_162, t_163);
                nile_Real_t t_165 = nile_Real_sqr(t_164);
                nile_Real_t t_166_x = t_165;
                nile_Real_t t_166_y = t_165;
                nile_Real_t t_167_x = nile_Real_div(t_155_x, t_166_x);
                nile_Real_t t_167_y = nile_Real_div(t_155_y, t_166_y);
                nile_Real_t t_168 = 0;
                nile_Real_t t_169_x = t_168;
                nile_Real_t t_169_y = t_168;
                nile_Real_t t_170_x = t_161;
                nile_Real_t t_170_y = t_161;
                nile_Real_t t_171_x = t_170_x ? t_167_x : t_169_x;
                nile_Real_t t_171_y = t_170_y ? t_167_y : t_169_y;
                nile_Real_t t_172 = 0;
                nile_Real_t t_173_x = t_172;
                nile_Real_t t_173_y = t_172;
                nile_Real_t t_174 = nile_Real_eq(t_171_x, t_173_x);
                nile_Real_t t_175 = nile_Real_eq(t_171_y, t_173_y);
                nile_Real_t t_176 = nile_Real_and(t_174, t_175);
                nile_Real_t t_177 = 0;
                nile_Real_t t_178 = nile_Real_eq(t_176, t_177);
                nile_Real_t t_179 = nile_Real_and(t_151, t_178);
                if (t_179) {
                    nile_Real_t t_180_1_x = v_A_x;
                    nile_Real_t t_180_1_y = v_A_y;
                    nile_Real_t t_180_2_x = v_M_x;
                    nile_Real_t t_180_2_y = v_M_y;
                    nile_Real_t t_180_3_x = v_C_x;
                    nile_Real_t t_180_3_y = v_C_y;
                    nile_Real_t t_181_a_x = t_180_1_x;
                    nile_Real_t t_181_a_y = t_180_1_y;
                    nile_Real_t t_181_b_x = t_180_2_x;
                    nile_Real_t t_181_b_y = t_180_2_y;
                    nile_Real_t t_181_c_x = t_180_3_x;
                    nile_Real_t t_181_c_y = t_180_3_y;
                    out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                    nile_Buffer_append(out, t_181_a_x);
                    nile_Buffer_append(out, t_181_a_y);
                    nile_Buffer_append(out, t_181_b_x);
                    nile_Buffer_append(out, t_181_b_y);
                    nile_Buffer_append(out, t_181_c_x);
                    nile_Buffer_append(out, t_181_c_y);
                }
                else {
                    ; /* no-op */
                }
            }
            else {
                nile_Real_t t_182_1_x = v_A_x;
                nile_Real_t t_182_1_y = v_A_y;
                nile_Real_t t_182_2_x = v_B_x;
                nile_Real_t t_182_2_y = v_B_y;
                nile_Real_t t_182_3_x = v_C_x;
                nile_Real_t t_182_3_y = v_C_y;
                nile_Real_t t_183_a_x = t_182_1_x;
                nile_Real_t t_183_a_y = t_182_1_y;
                nile_Real_t t_183_b_x = t_182_2_x;
                nile_Real_t t_183_b_y = t_182_2_y;
                nile_Real_t t_183_c_x = t_182_3_x;
                nile_Real_t t_183_c_y = t_182_3_y;
                out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append(out, t_183_a_x);
                nile_Buffer_append(out, t_183_a_y);
                nile_Buffer_append(out, t_183_b_x);
                nile_Buffer_append(out, t_183_b_y);
                nile_Buffer_append(out, t_183_c_x);
                nile_Buffer_append(out, t_183_c_y);
            }
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

typedef struct {
    nile_Kernel_t base;
} gezira_PrepareBeziersForOffset_t;

static nile_Kernel_t *gezira_PrepareBeziersForOffset_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_PrepareBeziersForOffset_t *k = (gezira_PrepareBeziersForOffset_t *) k_;
    gezira_PrepareBeziersForOffset_t *clone = (gezira_PrepareBeziersForOffset_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_PrepareBeziersForOffset(nile_t *nl) {
    gezira_PrepareBeziersForOffset_t *k = NILE_KERNEL_NEW(nl, gezira_PrepareBeziersForOffset);
    return (nile_Kernel_t *) k;
}

static int gezira_PrepareBeziersForOffset_process(nile_t *nl,
                                                  nile_Kernel_t *k_,
                                                  nile_Buffer_t **in_,
                                                  nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_PrepareBeziersForOffset_t *k = (gezira_PrepareBeziersForOffset_t *) k_;
    
    if (!k_->initialized) {
        k_->initialized = 1;
    }
    
    while (in->i < in->n) {
        nile_Real_t v_A_x = nile_Buffer_shift(in);
        nile_Real_t v_A_y = nile_Buffer_shift(in);
        nile_Real_t v_B_x = nile_Buffer_shift(in);
        nile_Real_t v_B_y = nile_Buffer_shift(in);
        nile_Real_t v_C_x = nile_Buffer_shift(in);
        nile_Real_t v_C_y = nile_Buffer_shift(in);
        nile_Real_t t_1_1_x = v_A_x;
        nile_Real_t t_1_1_y = v_A_y;
        nile_Real_t t_1_2_x = v_B_x;
        nile_Real_t t_1_2_y = v_B_y;
        nile_Real_t t_1_3_x = v_C_x;
        nile_Real_t t_1_3_y = v_C_y;
        nile_Real_t t_2_a_x = t_1_1_x;
        nile_Real_t t_2_a_y = t_1_1_y;
        nile_Real_t t_2_b_x = t_1_2_x;
        nile_Real_t t_2_b_y = t_1_2_y;
        nile_Real_t t_2_c_x = t_1_3_x;
        nile_Real_t t_2_c_y = t_1_3_y;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_2_a_x);
        nile_Buffer_append(out, t_2_a_y);
        nile_Buffer_append(out, t_2_b_x);
        nile_Buffer_append(out, t_2_b_y);
        nile_Buffer_append(out, t_2_c_x);
        nile_Buffer_append(out, t_2_c_y);
        nile_Real_t t_3_1_x = v_C_x;
        nile_Real_t t_3_1_y = v_C_y;
        nile_Real_t t_3_2_x = v_B_x;
        nile_Real_t t_3_2_y = v_B_y;
        nile_Real_t t_3_3_x = v_A_x;
        nile_Real_t t_3_3_y = v_A_y;
        nile_Real_t t_4_a_x = t_3_1_x;
        nile_Real_t t_4_a_y = t_3_1_y;
        nile_Real_t t_4_b_x = t_3_2_x;
        nile_Real_t t_4_b_y = t_3_2_y;
        nile_Real_t t_4_c_x = t_3_3_x;
        nile_Real_t t_4_c_y = t_3_3_y;
        out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append(out, t_4_a_x);
        nile_Buffer_append(out, t_4_a_y);
        nile_Buffer_append(out, t_4_b_x);
        nile_Buffer_append(out, t_4_b_y);
        nile_Buffer_append(out, t_4_c_x);
        nile_Buffer_append(out, t_4_c_y);
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
    nile_Real_t v_A_x;
    nile_Real_t v_A_y;
    nile_Real_t v_B_x;
    nile_Real_t v_B_y;
    nile_Real_t v_C_x;
    nile_Real_t v_C_y;
    nile_Real_t v_first;
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
    nile_Real_t v_E_x;
    nile_Real_t v_E_y;
    nile_Real_t v_F_x;
    nile_Real_t v_F_y;
} gezira_PrepareBeziersForJoin_t;

static nile_Kernel_t *gezira_PrepareBeziersForJoin_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_PrepareBeziersForJoin_t *k = (gezira_PrepareBeziersForJoin_t *) k_;
    gezira_PrepareBeziersForJoin_t *clone = (gezira_PrepareBeziersForJoin_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_PrepareBeziersForJoin(nile_t *nl) {
    gezira_PrepareBeziersForJoin_t *k = NILE_KERNEL_NEW(nl, gezira_PrepareBeziersForJoin);
    return (nile_Kernel_t *) k;
}

static int gezira_PrepareBeziersForJoin_process(nile_t *nl,
                                                nile_Kernel_t *k_,
                                                nile_Buffer_t **in_,
                                                nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 12
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_PrepareBeziersForJoin_t *k = (gezira_PrepareBeziersForJoin_t *) k_;
    nile_Real_t v_A_x = k->v_A_x;
    nile_Real_t v_A__x;
    nile_Real_t v_A_y = k->v_A_y;
    nile_Real_t v_A__y;
    nile_Real_t v_B_x = k->v_B_x;
    nile_Real_t v_B__x;
    nile_Real_t v_B_y = k->v_B_y;
    nile_Real_t v_B__y;
    nile_Real_t v_C_x = k->v_C_x;
    nile_Real_t v_C__x;
    nile_Real_t v_C_y = k->v_C_y;
    nile_Real_t v_C__y;
    nile_Real_t v_first = k->v_first;
    nile_Real_t v_first_;
    nile_Real_t v_D_x = k->v_D_x;
    nile_Real_t v_D__x;
    nile_Real_t v_D_y = k->v_D_y;
    nile_Real_t v_D__y;
    nile_Real_t v_E_x = k->v_E_x;
    nile_Real_t v_E__x;
    nile_Real_t v_E_y = k->v_E_y;
    nile_Real_t v_E__y;
    nile_Real_t v_F_x = k->v_F_x;
    nile_Real_t v_F__x;
    nile_Real_t v_F_y = k->v_F_y;
    nile_Real_t v_F__y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        v_A_x = in->data[in->i++];
        v_A_y = in->data[in->i++];
        v_B_x = in->data[in->i++];
        v_B_y = in->data[in->i++];
        v_C_x = in->data[in->i++];
        v_C_y = in->data[in->i++];
        in->i -= 6;
        nile_Real_t t_8 = 1;
        v_first = t_8;
        nile_Real_t t_9 = 0;
        nile_Real_t t_10_x = t_9;
        nile_Real_t t_10_y = t_9;
        v_D_x = t_10_x;
        v_D_y = t_10_y;
        nile_Real_t t_11 = 0;
        nile_Real_t t_12_x = t_11;
        nile_Real_t t_12_y = t_11;
        v_E_x = t_12_x;
        v_E_y = t_12_y;
        nile_Real_t t_13 = 0;
        nile_Real_t t_14_x = t_13;
        nile_Real_t t_14_y = t_13;
        v_F_x = t_14_x;
        v_F_y = t_14_y;
    }
    
    while (in->i < in->n) {
        v_A__x = v_A_x;
        v_A__y = v_A_y;
        v_B__x = v_B_x;
        v_B__y = v_B_y;
        v_C__x = v_C_x;
        v_C__y = v_C_y;
        v_first_ = v_first;
        v_D__x = v_D_x;
        v_D__y = v_D_y;
        v_E__x = v_E_x;
        v_E__y = v_E_y;
        v_F__x = v_F_x;
        v_F__y = v_F_y;
        v_D__x = nile_Buffer_shift(in);
        v_D__y = nile_Buffer_shift(in);
        v_E__x = nile_Buffer_shift(in);
        v_E__y = nile_Buffer_shift(in);
        v_F__x = nile_Buffer_shift(in);
        v_F__y = nile_Buffer_shift(in);
        if (v_first) {
            nile_Real_t t_15 = 0;
            v_first_ = t_15;
        }
        else {
            nile_Real_t t_17_1_x = v_D_x;
            nile_Real_t t_17_1_y = v_D_y;
            nile_Real_t t_17_2_x = v_E_x;
            nile_Real_t t_17_2_y = v_E_y;
            nile_Real_t t_17_3_x = v_F_x;
            nile_Real_t t_17_3_y = v_F_y;
            nile_Real_t t_18_1_x = v_D__x;
            nile_Real_t t_18_1_y = v_D__y;
            nile_Real_t t_18_2_x = v_E__x;
            nile_Real_t t_18_2_y = v_E__y;
            nile_Real_t t_18_3_x = v_F__x;
            nile_Real_t t_18_3_y = v_F__y;
            nile_Real_t t_16_1_1_x = t_17_1_x;
            nile_Real_t t_16_1_1_y = t_17_1_y;
            nile_Real_t t_16_1_2_x = t_17_2_x;
            nile_Real_t t_16_1_2_y = t_17_2_y;
            nile_Real_t t_16_1_3_x = t_17_3_x;
            nile_Real_t t_16_1_3_y = t_17_3_y;
            nile_Real_t t_16_2_1_x = t_18_1_x;
            nile_Real_t t_16_2_1_y = t_18_1_y;
            nile_Real_t t_16_2_2_x = t_18_2_x;
            nile_Real_t t_16_2_2_y = t_18_2_y;
            nile_Real_t t_16_2_3_x = t_18_3_x;
            nile_Real_t t_16_2_3_y = t_18_3_y;
            nile_Real_t t_19_1_a_x = t_16_1_1_x;
            nile_Real_t t_19_1_a_y = t_16_1_1_y;
            nile_Real_t t_19_1_b_x = t_16_1_2_x;
            nile_Real_t t_19_1_b_y = t_16_1_2_y;
            nile_Real_t t_19_1_c_x = t_16_1_3_x;
            nile_Real_t t_19_1_c_y = t_16_1_3_y;
            nile_Real_t t_19_2_a_x = t_16_2_1_x;
            nile_Real_t t_19_2_a_y = t_16_2_1_y;
            nile_Real_t t_19_2_b_x = t_16_2_2_x;
            nile_Real_t t_19_2_b_y = t_16_2_2_y;
            nile_Real_t t_19_2_c_x = t_16_2_3_x;
            nile_Real_t t_19_2_c_y = t_16_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_19_1_a_x);
            nile_Buffer_append(out, t_19_1_a_y);
            nile_Buffer_append(out, t_19_1_b_x);
            nile_Buffer_append(out, t_19_1_b_y);
            nile_Buffer_append(out, t_19_1_c_x);
            nile_Buffer_append(out, t_19_1_c_y);
            nile_Buffer_append(out, t_19_2_a_x);
            nile_Buffer_append(out, t_19_2_a_y);
            nile_Buffer_append(out, t_19_2_b_x);
            nile_Buffer_append(out, t_19_2_b_y);
            nile_Buffer_append(out, t_19_2_c_x);
            nile_Buffer_append(out, t_19_2_c_y);
            nile_Real_t t_21_1_x = v_F__x;
            nile_Real_t t_21_1_y = v_F__y;
            nile_Real_t t_21_2_x = v_E__x;
            nile_Real_t t_21_2_y = v_E__y;
            nile_Real_t t_21_3_x = v_D__x;
            nile_Real_t t_21_3_y = v_D__y;
            nile_Real_t t_22_1_x = v_F_x;
            nile_Real_t t_22_1_y = v_F_y;
            nile_Real_t t_22_2_x = v_E_x;
            nile_Real_t t_22_2_y = v_E_y;
            nile_Real_t t_22_3_x = v_D_x;
            nile_Real_t t_22_3_y = v_D_y;
            nile_Real_t t_20_1_1_x = t_21_1_x;
            nile_Real_t t_20_1_1_y = t_21_1_y;
            nile_Real_t t_20_1_2_x = t_21_2_x;
            nile_Real_t t_20_1_2_y = t_21_2_y;
            nile_Real_t t_20_1_3_x = t_21_3_x;
            nile_Real_t t_20_1_3_y = t_21_3_y;
            nile_Real_t t_20_2_1_x = t_22_1_x;
            nile_Real_t t_20_2_1_y = t_22_1_y;
            nile_Real_t t_20_2_2_x = t_22_2_x;
            nile_Real_t t_20_2_2_y = t_22_2_y;
            nile_Real_t t_20_2_3_x = t_22_3_x;
            nile_Real_t t_20_2_3_y = t_22_3_y;
            nile_Real_t t_23_1_a_x = t_20_1_1_x;
            nile_Real_t t_23_1_a_y = t_20_1_1_y;
            nile_Real_t t_23_1_b_x = t_20_1_2_x;
            nile_Real_t t_23_1_b_y = t_20_1_2_y;
            nile_Real_t t_23_1_c_x = t_20_1_3_x;
            nile_Real_t t_23_1_c_y = t_20_1_3_y;
            nile_Real_t t_23_2_a_x = t_20_2_1_x;
            nile_Real_t t_23_2_a_y = t_20_2_1_y;
            nile_Real_t t_23_2_b_x = t_20_2_2_x;
            nile_Real_t t_23_2_b_y = t_20_2_2_y;
            nile_Real_t t_23_2_c_x = t_20_2_3_x;
            nile_Real_t t_23_2_c_y = t_20_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_23_1_a_x);
            nile_Buffer_append(out, t_23_1_a_y);
            nile_Buffer_append(out, t_23_1_b_x);
            nile_Buffer_append(out, t_23_1_b_y);
            nile_Buffer_append(out, t_23_1_c_x);
            nile_Buffer_append(out, t_23_1_c_y);
            nile_Buffer_append(out, t_23_2_a_x);
            nile_Buffer_append(out, t_23_2_a_y);
            nile_Buffer_append(out, t_23_2_b_x);
            nile_Buffer_append(out, t_23_2_b_y);
            nile_Buffer_append(out, t_23_2_c_x);
            nile_Buffer_append(out, t_23_2_c_y);
        }
        v_A_x = v_A__x;
        v_A_y = v_A__y;
        v_B_x = v_B__x;
        v_B_y = v_B__y;
        v_C_x = v_C__x;
        v_C_y = v_C__y;
        v_first = v_first_;
        v_D_x = v_D__x;
        v_D_y = v_D__y;
        v_E_x = v_E__x;
        v_E_y = v_E__y;
        v_F_x = v_F__x;
        v_F_y = v_F__y;
    }
    
    if (in->eos) {
        nile_Real_t t_24 = nile_Real_eq(v_A_x, v_F_x);
        nile_Real_t t_25 = nile_Real_eq(v_A_y, v_F_y);
        nile_Real_t t_26 = nile_Real_and(t_24, t_25);
        nile_Real_t t_27 = 0;
        nile_Real_t t_28 = nile_Real_eq(v_first, t_27);
        nile_Real_t t_29 = nile_Real_and(t_26, t_28);
        if (t_29) {
            nile_Real_t t_31_1_x = v_D_x;
            nile_Real_t t_31_1_y = v_D_y;
            nile_Real_t t_31_2_x = v_E_x;
            nile_Real_t t_31_2_y = v_E_y;
            nile_Real_t t_31_3_x = v_F_x;
            nile_Real_t t_31_3_y = v_F_y;
            nile_Real_t t_32_1_x = v_A_x;
            nile_Real_t t_32_1_y = v_A_y;
            nile_Real_t t_32_2_x = v_B_x;
            nile_Real_t t_32_2_y = v_B_y;
            nile_Real_t t_32_3_x = v_C_x;
            nile_Real_t t_32_3_y = v_C_y;
            nile_Real_t t_30_1_1_x = t_31_1_x;
            nile_Real_t t_30_1_1_y = t_31_1_y;
            nile_Real_t t_30_1_2_x = t_31_2_x;
            nile_Real_t t_30_1_2_y = t_31_2_y;
            nile_Real_t t_30_1_3_x = t_31_3_x;
            nile_Real_t t_30_1_3_y = t_31_3_y;
            nile_Real_t t_30_2_1_x = t_32_1_x;
            nile_Real_t t_30_2_1_y = t_32_1_y;
            nile_Real_t t_30_2_2_x = t_32_2_x;
            nile_Real_t t_30_2_2_y = t_32_2_y;
            nile_Real_t t_30_2_3_x = t_32_3_x;
            nile_Real_t t_30_2_3_y = t_32_3_y;
            nile_Real_t t_33_1_a_x = t_30_1_1_x;
            nile_Real_t t_33_1_a_y = t_30_1_1_y;
            nile_Real_t t_33_1_b_x = t_30_1_2_x;
            nile_Real_t t_33_1_b_y = t_30_1_2_y;
            nile_Real_t t_33_1_c_x = t_30_1_3_x;
            nile_Real_t t_33_1_c_y = t_30_1_3_y;
            nile_Real_t t_33_2_a_x = t_30_2_1_x;
            nile_Real_t t_33_2_a_y = t_30_2_1_y;
            nile_Real_t t_33_2_b_x = t_30_2_2_x;
            nile_Real_t t_33_2_b_y = t_30_2_2_y;
            nile_Real_t t_33_2_c_x = t_30_2_3_x;
            nile_Real_t t_33_2_c_y = t_30_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_33_1_a_x);
            nile_Buffer_append(out, t_33_1_a_y);
            nile_Buffer_append(out, t_33_1_b_x);
            nile_Buffer_append(out, t_33_1_b_y);
            nile_Buffer_append(out, t_33_1_c_x);
            nile_Buffer_append(out, t_33_1_c_y);
            nile_Buffer_append(out, t_33_2_a_x);
            nile_Buffer_append(out, t_33_2_a_y);
            nile_Buffer_append(out, t_33_2_b_x);
            nile_Buffer_append(out, t_33_2_b_y);
            nile_Buffer_append(out, t_33_2_c_x);
            nile_Buffer_append(out, t_33_2_c_y);
            nile_Real_t t_35_1_x = v_C_x;
            nile_Real_t t_35_1_y = v_C_y;
            nile_Real_t t_35_2_x = v_B_x;
            nile_Real_t t_35_2_y = v_B_y;
            nile_Real_t t_35_3_x = v_A_x;
            nile_Real_t t_35_3_y = v_A_y;
            nile_Real_t t_36_1_x = v_F_x;
            nile_Real_t t_36_1_y = v_F_y;
            nile_Real_t t_36_2_x = v_E_x;
            nile_Real_t t_36_2_y = v_E_y;
            nile_Real_t t_36_3_x = v_D_x;
            nile_Real_t t_36_3_y = v_D_y;
            nile_Real_t t_34_1_1_x = t_35_1_x;
            nile_Real_t t_34_1_1_y = t_35_1_y;
            nile_Real_t t_34_1_2_x = t_35_2_x;
            nile_Real_t t_34_1_2_y = t_35_2_y;
            nile_Real_t t_34_1_3_x = t_35_3_x;
            nile_Real_t t_34_1_3_y = t_35_3_y;
            nile_Real_t t_34_2_1_x = t_36_1_x;
            nile_Real_t t_34_2_1_y = t_36_1_y;
            nile_Real_t t_34_2_2_x = t_36_2_x;
            nile_Real_t t_34_2_2_y = t_36_2_y;
            nile_Real_t t_34_2_3_x = t_36_3_x;
            nile_Real_t t_34_2_3_y = t_36_3_y;
            nile_Real_t t_37_1_a_x = t_34_1_1_x;
            nile_Real_t t_37_1_a_y = t_34_1_1_y;
            nile_Real_t t_37_1_b_x = t_34_1_2_x;
            nile_Real_t t_37_1_b_y = t_34_1_2_y;
            nile_Real_t t_37_1_c_x = t_34_1_3_x;
            nile_Real_t t_37_1_c_y = t_34_1_3_y;
            nile_Real_t t_37_2_a_x = t_34_2_1_x;
            nile_Real_t t_37_2_a_y = t_34_2_1_y;
            nile_Real_t t_37_2_b_x = t_34_2_2_x;
            nile_Real_t t_37_2_b_y = t_34_2_2_y;
            nile_Real_t t_37_2_c_x = t_34_2_3_x;
            nile_Real_t t_37_2_c_y = t_34_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_37_1_a_x);
            nile_Buffer_append(out, t_37_1_a_y);
            nile_Buffer_append(out, t_37_1_b_x);
            nile_Buffer_append(out, t_37_1_b_y);
            nile_Buffer_append(out, t_37_1_c_x);
            nile_Buffer_append(out, t_37_1_c_y);
            nile_Buffer_append(out, t_37_2_a_x);
            nile_Buffer_append(out, t_37_2_a_y);
            nile_Buffer_append(out, t_37_2_b_x);
            nile_Buffer_append(out, t_37_2_b_y);
            nile_Buffer_append(out, t_37_2_c_x);
            nile_Buffer_append(out, t_37_2_c_y);
        }
        else {
            ; /* no-op */
        }
    }
    else {
        k->v_A_x = v_A_x;
        k->v_A_y = v_A_y;
        k->v_B_x = v_B_x;
        k->v_B_y = v_B_y;
        k->v_C_x = v_C_x;
        k->v_C_y = v_C_y;
        k->v_first = v_first;
        k->v_D_x = v_D_x;
        k->v_D_y = v_D_y;
        k->v_E_x = v_E_x;
        k->v_E_y = v_E_y;
        k->v_F_x = v_F_x;
        k->v_F_y = v_F_y;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_A_x;
    nile_Real_t v_A_y;
    nile_Real_t v_B_x;
    nile_Real_t v_B_y;
    nile_Real_t v_C_x;
    nile_Real_t v_C_y;
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
    nile_Real_t v_E_x;
    nile_Real_t v_E_y;
    nile_Real_t v_F_x;
    nile_Real_t v_F_y;
} gezira_PrepareBeziersForCap_t;

static nile_Kernel_t *gezira_PrepareBeziersForCap_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_PrepareBeziersForCap_t *k = (gezira_PrepareBeziersForCap_t *) k_;
    gezira_PrepareBeziersForCap_t *clone = (gezira_PrepareBeziersForCap_t *) nile_Kernel_clone(nl, k_);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_PrepareBeziersForCap(nile_t *nl) {
    gezira_PrepareBeziersForCap_t *k = NILE_KERNEL_NEW(nl, gezira_PrepareBeziersForCap);
    return (nile_Kernel_t *) k;
}

static int gezira_PrepareBeziersForCap_process(nile_t *nl,
                                               nile_Kernel_t *k_,
                                               nile_Buffer_t **in_,
                                               nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 12
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_PrepareBeziersForCap_t *k = (gezira_PrepareBeziersForCap_t *) k_;
    nile_Real_t v_A_x = k->v_A_x;
    nile_Real_t v_A__x;
    nile_Real_t v_A_y = k->v_A_y;
    nile_Real_t v_A__y;
    nile_Real_t v_B_x = k->v_B_x;
    nile_Real_t v_B__x;
    nile_Real_t v_B_y = k->v_B_y;
    nile_Real_t v_B__y;
    nile_Real_t v_C_x = k->v_C_x;
    nile_Real_t v_C__x;
    nile_Real_t v_C_y = k->v_C_y;
    nile_Real_t v_C__y;
    nile_Real_t v_D_x = k->v_D_x;
    nile_Real_t v_D__x;
    nile_Real_t v_D_y = k->v_D_y;
    nile_Real_t v_D__y;
    nile_Real_t v_E_x = k->v_E_x;
    nile_Real_t v_E__x;
    nile_Real_t v_E_y = k->v_E_y;
    nile_Real_t v_E__y;
    nile_Real_t v_F_x = k->v_F_x;
    nile_Real_t v_F__x;
    nile_Real_t v_F_y = k->v_F_y;
    nile_Real_t v_F__y;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        v_A_x = in->data[in->i++];
        v_A_y = in->data[in->i++];
        v_B_x = in->data[in->i++];
        v_B_y = in->data[in->i++];
        v_C_x = in->data[in->i++];
        v_C_y = in->data[in->i++];
        in->i -= 6;
        nile_Real_t t_7 = 0;
        nile_Real_t t_8_x = t_7;
        nile_Real_t t_8_y = t_7;
        v_D_x = t_8_x;
        v_D_y = t_8_y;
        nile_Real_t t_9 = 0;
        nile_Real_t t_10_x = t_9;
        nile_Real_t t_10_y = t_9;
        v_E_x = t_10_x;
        v_E_y = t_10_y;
        nile_Real_t t_11 = 0;
        nile_Real_t t_12_x = t_11;
        nile_Real_t t_12_y = t_11;
        v_F_x = t_12_x;
        v_F_y = t_12_y;
    }
    
    while (in->i < in->n) {
        v_A__x = v_A_x;
        v_A__y = v_A_y;
        v_B__x = v_B_x;
        v_B__y = v_B_y;
        v_C__x = v_C_x;
        v_C__y = v_C_y;
        v_D__x = v_D_x;
        v_D__y = v_D_y;
        v_E__x = v_E_x;
        v_E__y = v_E_y;
        v_F__x = v_F_x;
        v_F__y = v_F_y;
        v_D__x = nile_Buffer_shift(in);
        v_D__y = nile_Buffer_shift(in);
        v_E__x = nile_Buffer_shift(in);
        v_E__y = nile_Buffer_shift(in);
        v_F__x = nile_Buffer_shift(in);
        v_F__y = nile_Buffer_shift(in);
        v_A_x = v_A__x;
        v_A_y = v_A__y;
        v_B_x = v_B__x;
        v_B_y = v_B__y;
        v_C_x = v_C__x;
        v_C_y = v_C__y;
        v_D_x = v_D__x;
        v_D_y = v_D__y;
        v_E_x = v_E__x;
        v_E_y = v_E__y;
        v_F_x = v_F__x;
        v_F_y = v_F__y;
    }
    
    if (in->eos) {
        nile_Real_t t_13 = nile_Real_eq(v_A_x, v_F_x);
        nile_Real_t t_14 = nile_Real_eq(v_A_y, v_F_y);
        nile_Real_t t_15 = nile_Real_and(t_13, t_14);
        nile_Real_t t_16 = 0;
        nile_Real_t t_17 = nile_Real_eq(t_15, t_16);
        if (t_17) {
            nile_Real_t t_19_1_x = v_C_x;
            nile_Real_t t_19_1_y = v_C_y;
            nile_Real_t t_19_2_x = v_B_x;
            nile_Real_t t_19_2_y = v_B_y;
            nile_Real_t t_19_3_x = v_A_x;
            nile_Real_t t_19_3_y = v_A_y;
            nile_Real_t t_20_1_x = v_A_x;
            nile_Real_t t_20_1_y = v_A_y;
            nile_Real_t t_20_2_x = v_B_x;
            nile_Real_t t_20_2_y = v_B_y;
            nile_Real_t t_20_3_x = v_C_x;
            nile_Real_t t_20_3_y = v_C_y;
            nile_Real_t t_18_1_1_x = t_19_1_x;
            nile_Real_t t_18_1_1_y = t_19_1_y;
            nile_Real_t t_18_1_2_x = t_19_2_x;
            nile_Real_t t_18_1_2_y = t_19_2_y;
            nile_Real_t t_18_1_3_x = t_19_3_x;
            nile_Real_t t_18_1_3_y = t_19_3_y;
            nile_Real_t t_18_2_1_x = t_20_1_x;
            nile_Real_t t_18_2_1_y = t_20_1_y;
            nile_Real_t t_18_2_2_x = t_20_2_x;
            nile_Real_t t_18_2_2_y = t_20_2_y;
            nile_Real_t t_18_2_3_x = t_20_3_x;
            nile_Real_t t_18_2_3_y = t_20_3_y;
            nile_Real_t t_21_1_a_x = t_18_1_1_x;
            nile_Real_t t_21_1_a_y = t_18_1_1_y;
            nile_Real_t t_21_1_b_x = t_18_1_2_x;
            nile_Real_t t_21_1_b_y = t_18_1_2_y;
            nile_Real_t t_21_1_c_x = t_18_1_3_x;
            nile_Real_t t_21_1_c_y = t_18_1_3_y;
            nile_Real_t t_21_2_a_x = t_18_2_1_x;
            nile_Real_t t_21_2_a_y = t_18_2_1_y;
            nile_Real_t t_21_2_b_x = t_18_2_2_x;
            nile_Real_t t_21_2_b_y = t_18_2_2_y;
            nile_Real_t t_21_2_c_x = t_18_2_3_x;
            nile_Real_t t_21_2_c_y = t_18_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_21_1_a_x);
            nile_Buffer_append(out, t_21_1_a_y);
            nile_Buffer_append(out, t_21_1_b_x);
            nile_Buffer_append(out, t_21_1_b_y);
            nile_Buffer_append(out, t_21_1_c_x);
            nile_Buffer_append(out, t_21_1_c_y);
            nile_Buffer_append(out, t_21_2_a_x);
            nile_Buffer_append(out, t_21_2_a_y);
            nile_Buffer_append(out, t_21_2_b_x);
            nile_Buffer_append(out, t_21_2_b_y);
            nile_Buffer_append(out, t_21_2_c_x);
            nile_Buffer_append(out, t_21_2_c_y);
            nile_Real_t t_23_1_x = v_D_x;
            nile_Real_t t_23_1_y = v_D_y;
            nile_Real_t t_23_2_x = v_E_x;
            nile_Real_t t_23_2_y = v_E_y;
            nile_Real_t t_23_3_x = v_F_x;
            nile_Real_t t_23_3_y = v_F_y;
            nile_Real_t t_24_1_x = v_F_x;
            nile_Real_t t_24_1_y = v_F_y;
            nile_Real_t t_24_2_x = v_E_x;
            nile_Real_t t_24_2_y = v_E_y;
            nile_Real_t t_24_3_x = v_D_x;
            nile_Real_t t_24_3_y = v_D_y;
            nile_Real_t t_22_1_1_x = t_23_1_x;
            nile_Real_t t_22_1_1_y = t_23_1_y;
            nile_Real_t t_22_1_2_x = t_23_2_x;
            nile_Real_t t_22_1_2_y = t_23_2_y;
            nile_Real_t t_22_1_3_x = t_23_3_x;
            nile_Real_t t_22_1_3_y = t_23_3_y;
            nile_Real_t t_22_2_1_x = t_24_1_x;
            nile_Real_t t_22_2_1_y = t_24_1_y;
            nile_Real_t t_22_2_2_x = t_24_2_x;
            nile_Real_t t_22_2_2_y = t_24_2_y;
            nile_Real_t t_22_2_3_x = t_24_3_x;
            nile_Real_t t_22_2_3_y = t_24_3_y;
            nile_Real_t t_25_1_a_x = t_22_1_1_x;
            nile_Real_t t_25_1_a_y = t_22_1_1_y;
            nile_Real_t t_25_1_b_x = t_22_1_2_x;
            nile_Real_t t_25_1_b_y = t_22_1_2_y;
            nile_Real_t t_25_1_c_x = t_22_1_3_x;
            nile_Real_t t_25_1_c_y = t_22_1_3_y;
            nile_Real_t t_25_2_a_x = t_22_2_1_x;
            nile_Real_t t_25_2_a_y = t_22_2_1_y;
            nile_Real_t t_25_2_b_x = t_22_2_2_x;
            nile_Real_t t_25_2_b_y = t_22_2_2_y;
            nile_Real_t t_25_2_c_x = t_22_2_3_x;
            nile_Real_t t_25_2_c_y = t_22_2_3_y;
            out = nile_Buffer_prepare_to_append(nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append(out, t_25_1_a_x);
            nile_Buffer_append(out, t_25_1_a_y);
            nile_Buffer_append(out, t_25_1_b_x);
            nile_Buffer_append(out, t_25_1_b_y);
            nile_Buffer_append(out, t_25_1_c_x);
            nile_Buffer_append(out, t_25_1_c_y);
            nile_Buffer_append(out, t_25_2_a_x);
            nile_Buffer_append(out, t_25_2_a_y);
            nile_Buffer_append(out, t_25_2_b_x);
            nile_Buffer_append(out, t_25_2_b_y);
            nile_Buffer_append(out, t_25_2_c_x);
            nile_Buffer_append(out, t_25_2_c_y);
        }
        else {
            ; /* no-op */
        }
    }
    else {
        k->v_A_x = v_A_x;
        k->v_A_y = v_A_y;
        k->v_B_x = v_B_x;
        k->v_B_y = v_B_y;
        k->v_C_x = v_C_x;
        k->v_C_y = v_C_y;
        k->v_D_x = v_D_x;
        k->v_D_y = v_D_y;
        k->v_E_x = v_E_x;
        k->v_E_y = v_E_y;
        k->v_F_x = v_F_x;
        k->v_F_y = v_F_y;
    }
    *in_ = in;
    *out_ = out;
    return NILE_INPUT_CONSUMED;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_o;
    nile_Kernel_t *v_j;
    nile_Kernel_t *v_c;
} gezira_StrokeBeziers_t;

static nile_Kernel_t *gezira_StrokeBeziers_clone(nile_t *nl, nile_Kernel_t *k_) {
    gezira_StrokeBeziers_t *k = (gezira_StrokeBeziers_t *) k_;
    gezira_StrokeBeziers_t *clone = (gezira_StrokeBeziers_t *) nile_Kernel_clone(nl, k_);
    clone->v_o = k->v_o;
    clone->v_j = k->v_j->clone(nl, k->v_j);
    clone->v_c = k->v_c->clone(nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

nile_Kernel_t *gezira_StrokeBeziers(nile_t *nl, 
                                    nile_Real_t v_o, 
                                    nile_Kernel_t *v_j, 
                                    nile_Kernel_t *v_c) {
    gezira_StrokeBeziers_t *k = NILE_KERNEL_NEW(nl, gezira_StrokeBeziers);
    k->v_o = v_o;
    k->v_j = v_j;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

static int gezira_StrokeBeziers_process(nile_t *nl,
                                        nile_Kernel_t *k_,
                                        nile_Buffer_t **in_,
                                        nile_Buffer_t **out_) {
    #define IN_QUANTUM 6
    #define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_StrokeBeziers_t *k = (gezira_StrokeBeziers_t *) k_;
    nile_Real_t v_o = k->v_o;
    nile_Kernel_t *v_j = k->v_j;
    nile_Kernel_t *v_c = k->v_c;
    
    if (!k_->initialized) {
        k_->initialized = 1;
        ; /* no-op */
        nile_Kernel_t *t_1 = gezira_StrokeOffset(nl, v_o);
        nile_Kernel_t *t_2 = nile_Pipeline(nl, gezira_PrepareBeziersForOffset(nl), t_1, NULL);
        nile_Kernel_t *t_3 = gezira_StrokeJoin(nl, v_j, v_o);
        nile_Kernel_t *t_4 = nile_Pipeline(nl, gezira_PrepareBeziersForJoin(nl), t_3, NULL);
        nile_Kernel_t *t_5 = gezira_StrokeJoin(nl, v_c, v_o);
        nile_Kernel_t *t_6 = nile_Pipeline(nl, gezira_PrepareBeziersForCap(nl), t_5, NULL);
        nile_Kernel_t *t_7 = nile_Mix(nl, t_4, t_6);
        nile_Kernel_t *t_8 = nile_Mix(nl, t_2, t_7);
        nile_Kernel_t *t_9 = nile_Pipeline(nl, gezira_PrepareBeziersForStroke(nl), t_8, NULL);
        nile_Kernel_t *f = t_9;
        f->downstream = k_->downstream;
        k_->downstream = f;
    }
    
    return NILE_INPUT_FORWARD;
    #undef IN_QUANTUM
    #undef OUT_QUANTUM
}

