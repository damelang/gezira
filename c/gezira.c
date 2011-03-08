#define NILE_INCLUDE_PROCESS_API
#include "nile.h"
#include "gezira.h"

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
    nile_Real_t v_M_a;
    nile_Real_t v_M_b;
    nile_Real_t v_M_c;
    nile_Real_t v_M_d;
    nile_Real_t v_M_e;
    nile_Real_t v_M_f;
} gezira_TransformPoints_vars_t;

static nile_Buffer_t *
gezira_TransformPoints_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_TransformPoints_vars_t *vars = nile_Process_vars (p);
    gezira_TransformPoints_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_TransformPoints_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_TransformPoints_vars_t *vars = nile_Process_vars (p);
    gezira_TransformPoints_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_TransformPoints_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real_mul(v.v_M_a, v_P_x);
        nile_Real_t t_3 = nile_Real_mul(v.v_M_c, v_P_y);
        nile_Real_t t_4 = nile_Real_add(t_2, t_3);
        nile_Real_t t_5 = nile_Real_add(t_4, v.v_M_e);
        nile_Real_t t_6 = nile_Real_mul(v.v_M_b, v_P_x);
        nile_Real_t t_7 = nile_Real_mul(v.v_M_d, v_P_y);
        nile_Real_t t_8 = nile_Real_add(t_6, t_7);
        nile_Real_t t_9 = nile_Real_add(t_8, v.v_M_f);
        nile_Real_t t_1_1 = t_5;
        nile_Real_t t_1_2 = t_9;
        nile_Real_t t_10_x = t_1_1;
        nile_Real_t t_10_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_10_x);
        nile_Buffer_push_tail(out, t_10_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_TransformPoints_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_TransformPoints_vars_t *vars = nile_Process_vars (p);
    gezira_TransformPoints_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_TransformPoints (nile_Process_t *p, 
                        float v_M_a, 
                        float v_M_b, 
                        float v_M_c, 
                        float v_M_d, 
                        float v_M_e, 
                        float v_M_f)
{
    gezira_TransformPoints_vars_t *vars;
    gezira_TransformPoints_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_TransformPoints_prologue, gezira_TransformPoints_body, gezira_TransformPoints_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_M_a = nile_Real (v_M_a);
        v.v_M_b = nile_Real (v_M_b);
        v.v_M_c = nile_Real (v_M_c);
        v.v_M_d = nile_Real (v_M_d);
        v.v_M_e = nile_Real (v_M_e);
        v.v_M_f = nile_Real (v_M_f);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 6
#define OUT_QUANTUM 6

typedef struct {
    nile_Real_t v_M_a;
    nile_Real_t v_M_b;
    nile_Real_t v_M_c;
    nile_Real_t v_M_d;
    nile_Real_t v_M_e;
    nile_Real_t v_M_f;
} gezira_TransformBeziers_vars_t;

static nile_Buffer_t *
gezira_TransformBeziers_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_TransformBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_TransformBeziers_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_TransformBeziers_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_TransformBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_TransformBeziers_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_TransformBeziers_vars_t v_ = v;
        nile_Real_t v_A_x = nile_Buffer_pop_head(in);
        nile_Real_t v_A_y = nile_Buffer_pop_head(in);
        nile_Real_t v_B_x = nile_Buffer_pop_head(in);
        nile_Real_t v_B_y = nile_Buffer_pop_head(in);
        nile_Real_t v_C_x = nile_Buffer_pop_head(in);
        nile_Real_t v_C_y = nile_Buffer_pop_head(in);
        nile_Real_t t_3 = nile_Real_mul(v.v_M_a, v_A_x);
        nile_Real_t t_4 = nile_Real_mul(v.v_M_c, v_A_y);
        nile_Real_t t_5 = nile_Real_add(t_3, t_4);
        nile_Real_t t_6 = nile_Real_add(t_5, v.v_M_e);
        nile_Real_t t_7 = nile_Real_mul(v.v_M_b, v_A_x);
        nile_Real_t t_8 = nile_Real_mul(v.v_M_d, v_A_y);
        nile_Real_t t_9 = nile_Real_add(t_7, t_8);
        nile_Real_t t_10 = nile_Real_add(t_9, v.v_M_f);
        nile_Real_t t_2_1 = t_6;
        nile_Real_t t_2_2 = t_10;
        nile_Real_t t_11_x = t_2_1;
        nile_Real_t t_11_y = t_2_2;
        nile_Real_t t_13 = nile_Real_mul(v.v_M_a, v_B_x);
        nile_Real_t t_14 = nile_Real_mul(v.v_M_c, v_B_y);
        nile_Real_t t_15 = nile_Real_add(t_13, t_14);
        nile_Real_t t_16 = nile_Real_add(t_15, v.v_M_e);
        nile_Real_t t_17 = nile_Real_mul(v.v_M_b, v_B_x);
        nile_Real_t t_18 = nile_Real_mul(v.v_M_d, v_B_y);
        nile_Real_t t_19 = nile_Real_add(t_17, t_18);
        nile_Real_t t_20 = nile_Real_add(t_19, v.v_M_f);
        nile_Real_t t_12_1 = t_16;
        nile_Real_t t_12_2 = t_20;
        nile_Real_t t_21_x = t_12_1;
        nile_Real_t t_21_y = t_12_2;
        nile_Real_t t_23 = nile_Real_mul(v.v_M_a, v_C_x);
        nile_Real_t t_24 = nile_Real_mul(v.v_M_c, v_C_y);
        nile_Real_t t_25 = nile_Real_add(t_23, t_24);
        nile_Real_t t_26 = nile_Real_add(t_25, v.v_M_e);
        nile_Real_t t_27 = nile_Real_mul(v.v_M_b, v_C_x);
        nile_Real_t t_28 = nile_Real_mul(v.v_M_d, v_C_y);
        nile_Real_t t_29 = nile_Real_add(t_27, t_28);
        nile_Real_t t_30 = nile_Real_add(t_29, v.v_M_f);
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
        nile_Real_t t_32_A_x = t_1_1_x;
        nile_Real_t t_32_A_y = t_1_1_y;
        nile_Real_t t_32_B_x = t_1_2_x;
        nile_Real_t t_32_B_y = t_1_2_y;
        nile_Real_t t_32_C_x = t_1_3_x;
        nile_Real_t t_32_C_y = t_1_3_y;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_32_A_x);
        nile_Buffer_push_tail(out, t_32_A_y);
        nile_Buffer_push_tail(out, t_32_B_x);
        nile_Buffer_push_tail(out, t_32_B_y);
        nile_Buffer_push_tail(out, t_32_C_x);
        nile_Buffer_push_tail(out, t_32_C_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_TransformBeziers_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_TransformBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_TransformBeziers_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_TransformBeziers (nile_Process_t *p, 
                         float v_M_a, 
                         float v_M_b, 
                         float v_M_c, 
                         float v_M_d, 
                         float v_M_e, 
                         float v_M_f)
{
    gezira_TransformBeziers_vars_t *vars;
    gezira_TransformBeziers_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_TransformBeziers_prologue, gezira_TransformBeziers_body, gezira_TransformBeziers_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_M_a = nile_Real (v_M_a);
        v.v_M_b = nile_Real (v_M_b);
        v.v_M_c = nile_Real (v_M_c);
        v.v_M_d = nile_Real (v_M_d);
        v.v_M_e = nile_Real (v_M_e);
        v.v_M_f = nile_Real (v_M_f);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_C_a;
    nile_Real_t v_C_r;
    nile_Real_t v_C_g;
    nile_Real_t v_C_b;
} gezira_UniformColor_vars_t;

static nile_Buffer_t *
gezira_UniformColor_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_UniformColor_vars_t *vars = nile_Process_vars (p);
    gezira_UniformColor_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_UniformColor_body (nile_Process_t *p,
                          nile_Buffer_t *in,
                          nile_Buffer_t *out)
{
    gezira_UniformColor_vars_t *vars = nile_Process_vars (p);
    gezira_UniformColor_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_UniformColor_vars_t v_ = v;
        nile_Real_t t_1_x;
        nile_Real_t t_1_y;
        t_1_x = nile_Buffer_pop_head(in);
        t_1_y = nile_Buffer_pop_head(in);
        nile_Real_t t_3 = nile_Real_mul(v.v_C_a, v.v_C_r);
        nile_Real_t t_4 = nile_Real_mul(v.v_C_a, v.v_C_g);
        nile_Real_t t_5 = nile_Real_mul(v.v_C_a, v.v_C_b);
        nile_Real_t t_2_1 = v.v_C_a;
        nile_Real_t t_2_2 = t_3;
        nile_Real_t t_2_3 = t_4;
        nile_Real_t t_2_4 = t_5;
        nile_Real_t t_6_a = t_2_1;
        nile_Real_t t_6_r = t_2_2;
        nile_Real_t t_6_g = t_2_3;
        nile_Real_t t_6_b = t_2_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_6_a);
        nile_Buffer_push_tail(out, t_6_r);
        nile_Buffer_push_tail(out, t_6_g);
        nile_Buffer_push_tail(out, t_6_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_UniformColor_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_UniformColor_vars_t *vars = nile_Process_vars (p);
    gezira_UniformColor_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_UniformColor (nile_Process_t *p, 
                     float v_C_a, 
                     float v_C_r, 
                     float v_C_g, 
                     float v_C_b)
{
    gezira_UniformColor_vars_t *vars;
    gezira_UniformColor_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_UniformColor_prologue, gezira_UniformColor_body, gezira_UniformColor_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_C_a = nile_Real (v_C_a);
        v.v_C_r = nile_Real (v_C_r);
        v.v_C_g = nile_Real (v_C_g);
        v.v_C_b = nile_Real (v_C_b);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Process_t *v_t1;
    nile_Process_t *v_t2;
    nile_Process_t *v_c;
} gezira_CompositeTextures_vars_t;

static nile_Buffer_t *
gezira_CompositeTextures_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeTextures_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeTextures_vars_t v = *vars;
    ; /* no-op */
    nile_Real_t t_1 = nile_Real (4);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = nile_DupZip(p, v.v_t1, nile_Real_toi (t_1), v.v_t2, nile_Real_toi (t_2));
    nile_Process_t *t_4 = nile_Process_pipe (t_3, v.v_c, NILE_NULL);
    return nile_Process_swap (p, t_4, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeTextures_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_CompositeTextures_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeTextures_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_CompositeTextures_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeTextures_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeTextures_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_CompositeTextures (nile_Process_t *p, 
                          nile_Process_t *v_t1, 
                          nile_Process_t *v_t2, 
                          nile_Process_t *v_c)
{
    gezira_CompositeTextures_vars_t *vars;
    gezira_CompositeTextures_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeTextures_prologue, gezira_CompositeTextures_body, gezira_CompositeTextures_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_t1 = v_t1;
        v.v_t2 = v_t2;
        v.v_c = v_c;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 6
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_CalculateBounds_vars_t;

static nile_Buffer_t *
gezira_CalculateBounds_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CalculateBounds_vars_t *vars = nile_Process_vars (p);
    gezira_CalculateBounds_vars_t v = *vars;
    nile_Real_t t_6 = nile_Real (999999);
    nile_Real_t t_7_x = t_6;
    nile_Real_t t_7_y = t_6;
    v.v_min_x = t_7_x;
    v.v_min_y = t_7_y;
    nile_Real_t t_8 = nile_Real (999999);
    nile_Real_t t_9 = nile_Real_neg(t_8);
    nile_Real_t t_10_x = t_9;
    nile_Real_t t_10_y = t_9;
    v.v_max_x = t_10_x;
    v.v_max_y = t_10_y;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CalculateBounds_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CalculateBounds_vars_t *vars = nile_Process_vars (p);
    gezira_CalculateBounds_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CalculateBounds_vars_t v_ = v;
        nile_Real_t v_A_x = nile_Buffer_pop_head(in);
        nile_Real_t v_A_y = nile_Buffer_pop_head(in);
        nile_Real_t v_B_x = nile_Buffer_pop_head(in);
        nile_Real_t v_B_y = nile_Buffer_pop_head(in);
        nile_Real_t v_C_x = nile_Buffer_pop_head(in);
        nile_Real_t v_C_y = nile_Buffer_pop_head(in);
        nile_Real_t t_11 = nile_Real_lt(v.v_min_x, v_A_x);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? v.v_min_x : v_A_x;
        nile_Real_t t_13 = nile_Real_lt(v.v_min_y, v_A_y);
        nile_Real_t t_14 = nile_Real_nz (t_13) ? v.v_min_y : v_A_y;
        nile_Real_t t_15_1 = t_12;
        nile_Real_t t_15_2 = t_14;
        nile_Real_t t_16_x = t_15_1;
        nile_Real_t t_16_y = t_15_2;
        nile_Real_t t_17 = nile_Real_lt(t_16_x, v_B_x);
        nile_Real_t t_18 = nile_Real_nz (t_17) ? t_16_x : v_B_x;
        nile_Real_t t_19 = nile_Real_lt(t_16_y, v_B_y);
        nile_Real_t t_20 = nile_Real_nz (t_19) ? t_16_y : v_B_y;
        nile_Real_t t_21_1 = t_18;
        nile_Real_t t_21_2 = t_20;
        nile_Real_t t_22_x = t_21_1;
        nile_Real_t t_22_y = t_21_2;
        nile_Real_t t_23 = nile_Real_lt(t_22_x, v_C_x);
        nile_Real_t t_24 = nile_Real_nz (t_23) ? t_22_x : v_C_x;
        nile_Real_t t_25 = nile_Real_lt(t_22_y, v_C_y);
        nile_Real_t t_26 = nile_Real_nz (t_25) ? t_22_y : v_C_y;
        nile_Real_t t_27_1 = t_24;
        nile_Real_t t_27_2 = t_26;
        nile_Real_t t_28_x = t_27_1;
        nile_Real_t t_28_y = t_27_2;
        v_.v_min_x = t_28_x;
        v_.v_min_y = t_28_y;
        nile_Real_t t_29 = nile_Real_gt(v.v_max_x, v_A_x);
        nile_Real_t t_30 = nile_Real_nz (t_29) ? v.v_max_x : v_A_x;
        nile_Real_t t_31 = nile_Real_gt(v.v_max_y, v_A_y);
        nile_Real_t t_32 = nile_Real_nz (t_31) ? v.v_max_y : v_A_y;
        nile_Real_t t_33_1 = t_30;
        nile_Real_t t_33_2 = t_32;
        nile_Real_t t_34_x = t_33_1;
        nile_Real_t t_34_y = t_33_2;
        nile_Real_t t_35 = nile_Real_gt(t_34_x, v_B_x);
        nile_Real_t t_36 = nile_Real_nz (t_35) ? t_34_x : v_B_x;
        nile_Real_t t_37 = nile_Real_gt(t_34_y, v_B_y);
        nile_Real_t t_38 = nile_Real_nz (t_37) ? t_34_y : v_B_y;
        nile_Real_t t_39_1 = t_36;
        nile_Real_t t_39_2 = t_38;
        nile_Real_t t_40_x = t_39_1;
        nile_Real_t t_40_y = t_39_2;
        nile_Real_t t_41 = nile_Real_gt(t_40_x, v_C_x);
        nile_Real_t t_42 = nile_Real_nz (t_41) ? t_40_x : v_C_x;
        nile_Real_t t_43 = nile_Real_gt(t_40_y, v_C_y);
        nile_Real_t t_44 = nile_Real_nz (t_43) ? t_40_y : v_C_y;
        nile_Real_t t_45_1 = t_42;
        nile_Real_t t_45_2 = t_44;
        nile_Real_t t_46_x = t_45_1;
        nile_Real_t t_46_y = t_45_2;
        v_.v_max_x = t_46_x;
        v_.v_max_y = t_46_y;
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CalculateBounds_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CalculateBounds_vars_t *vars = nile_Process_vars (p);
    gezira_CalculateBounds_vars_t v = *vars;
    nile_Real_t t_47_1_x = v.v_min_x;
    nile_Real_t t_47_1_y = v.v_min_y;
    nile_Real_t t_47_2_x = v.v_max_x;
    nile_Real_t t_47_2_y = v.v_max_y;
    nile_Real_t t_48_1_x = t_47_1_x;
    nile_Real_t t_48_1_y = t_47_1_y;
    nile_Real_t t_48_2_x = t_47_2_x;
    nile_Real_t t_48_2_y = t_47_2_y;
    if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
        out = nile_Process_append_output (p, out);
    nile_Buffer_push_tail(out, t_48_1_x);
    nile_Buffer_push_tail(out, t_48_1_y);
    nile_Buffer_push_tail(out, t_48_2_x);
    nile_Buffer_push_tail(out, t_48_2_y);
    return out;
}

nile_Process_t *
gezira_CalculateBounds (nile_Process_t *p)
{
    gezira_CalculateBounds_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CalculateBounds_prologue, gezira_CalculateBounds_body, gezira_CalculateBounds_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 6
#define OUT_QUANTUM 6

typedef struct {
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_ClipBeziers_vars_t;

static nile_Buffer_t *
gezira_ClipBeziers_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ClipBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_ClipBeziers_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ClipBeziers_body (nile_Process_t *p,
                         nile_Buffer_t *in,
                         nile_Buffer_t *out)
{
    gezira_ClipBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_ClipBeziers_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ClipBeziers_vars_t v_ = v;
        nile_Real_t v_A_x = nile_Buffer_pop_head(in);
        nile_Real_t v_A_y = nile_Buffer_pop_head(in);
        nile_Real_t v_B_x = nile_Buffer_pop_head(in);
        nile_Real_t v_B_y = nile_Buffer_pop_head(in);
        nile_Real_t v_C_x = nile_Buffer_pop_head(in);
        nile_Real_t v_C_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real_lt(v_A_x, v_B_x);
        nile_Real_t t_2 = nile_Real_nz (t_1) ? v_A_x : v_B_x;
        nile_Real_t t_3 = nile_Real_lt(v_A_y, v_B_y);
        nile_Real_t t_4 = nile_Real_nz (t_3) ? v_A_y : v_B_y;
        nile_Real_t t_5_1 = t_2;
        nile_Real_t t_5_2 = t_4;
        nile_Real_t t_6_x = t_5_1;
        nile_Real_t t_6_y = t_5_2;
        nile_Real_t t_7 = nile_Real_lt(t_6_x, v_C_x);
        nile_Real_t t_8 = nile_Real_nz (t_7) ? t_6_x : v_C_x;
        nile_Real_t t_9 = nile_Real_lt(t_6_y, v_C_y);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_6_y : v_C_y;
        nile_Real_t t_11_1 = t_8;
        nile_Real_t t_11_2 = t_10;
        nile_Real_t t_12_x = t_11_1;
        nile_Real_t t_12_y = t_11_2;
        nile_Real_t v_bmin_x = t_12_x;
        nile_Real_t v_bmin_y = t_12_y;
        nile_Real_t t_13 = nile_Real_gt(v_A_x, v_B_x);
        nile_Real_t t_14 = nile_Real_nz (t_13) ? v_A_x : v_B_x;
        nile_Real_t t_15 = nile_Real_gt(v_A_y, v_B_y);
        nile_Real_t t_16 = nile_Real_nz (t_15) ? v_A_y : v_B_y;
        nile_Real_t t_17_1 = t_14;
        nile_Real_t t_17_2 = t_16;
        nile_Real_t t_18_x = t_17_1;
        nile_Real_t t_18_y = t_17_2;
        nile_Real_t t_19 = nile_Real_gt(t_18_x, v_C_x);
        nile_Real_t t_20 = nile_Real_nz (t_19) ? t_18_x : v_C_x;
        nile_Real_t t_21 = nile_Real_gt(t_18_y, v_C_y);
        nile_Real_t t_22 = nile_Real_nz (t_21) ? t_18_y : v_C_y;
        nile_Real_t t_23_1 = t_20;
        nile_Real_t t_23_2 = t_22;
        nile_Real_t t_24_x = t_23_1;
        nile_Real_t t_24_y = t_23_2;
        nile_Real_t v_bmax_x = t_24_x;
        nile_Real_t v_bmax_y = t_24_y;
        nile_Real_t t_25_x = nile_Real_leq(v.v_min_x, v_bmin_x);
        nile_Real_t t_25_y = nile_Real_leq(v.v_min_y, v_bmin_y);
        nile_Real_t t_26_x = nile_Real_leq(v_bmax_x, v.v_max_x);
        nile_Real_t t_26_y = nile_Real_leq(v_bmax_y, v.v_max_y);
        nile_Real_t t_27_x = nile_Real_and(t_25_x, t_26_x);
        nile_Real_t t_27_y = nile_Real_and(t_25_y, t_26_y);
        nile_Real_t v_inside_x = t_27_x;
        nile_Real_t v_inside_y = t_27_y;
        nile_Real_t t_28_x = nile_Real_leq(v_bmax_x, v.v_min_x);
        nile_Real_t t_28_y = nile_Real_leq(v_bmax_y, v.v_min_y);
        nile_Real_t t_29_x = nile_Real_leq(v.v_max_x, v_bmin_x);
        nile_Real_t t_29_y = nile_Real_leq(v.v_max_y, v_bmin_y);
        nile_Real_t t_30_x = nile_Real_or(t_28_x, t_29_x);
        nile_Real_t t_30_y = nile_Real_or(t_28_y, t_29_y);
        nile_Real_t v_outside_x = t_30_x;
        nile_Real_t v_outside_y = t_30_y;
        nile_Real_t t_31 = nile_Real_and(v_inside_x, v_inside_y);
        if (nile_Real_nz (t_31)) {
            nile_Real_t t_32_1_x = v_A_x;
            nile_Real_t t_32_1_y = v_A_y;
            nile_Real_t t_32_2_x = v_B_x;
            nile_Real_t t_32_2_y = v_B_y;
            nile_Real_t t_32_3_x = v_C_x;
            nile_Real_t t_32_3_y = v_C_y;
            nile_Real_t t_33_A_x = t_32_1_x;
            nile_Real_t t_33_A_y = t_32_1_y;
            nile_Real_t t_33_B_x = t_32_2_x;
            nile_Real_t t_33_B_y = t_32_2_y;
            nile_Real_t t_33_C_x = t_32_3_x;
            nile_Real_t t_33_C_y = t_32_3_y;
            if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                out = nile_Process_append_output (p, out);
            nile_Buffer_push_tail(out, t_33_A_x);
            nile_Buffer_push_tail(out, t_33_A_y);
            nile_Buffer_push_tail(out, t_33_B_x);
            nile_Buffer_push_tail(out, t_33_B_y);
            nile_Buffer_push_tail(out, t_33_C_x);
            nile_Buffer_push_tail(out, t_33_C_y);
        }
        else {
            nile_Real_t t_34 = nile_Real_or(v_outside_x, v_outside_y);
            if (nile_Real_nz (t_34)) {
                nile_Real_t t_35 = nile_Real_gt(v.v_min_x, v_A_x);
                nile_Real_t t_36 = nile_Real_nz (t_35) ? v.v_min_x : v_A_x;
                nile_Real_t t_37 = nile_Real_gt(v.v_min_y, v_A_y);
                nile_Real_t t_38 = nile_Real_nz (t_37) ? v.v_min_y : v_A_y;
                nile_Real_t t_39_1 = t_36;
                nile_Real_t t_39_2 = t_38;
                nile_Real_t t_40_x = t_39_1;
                nile_Real_t t_40_y = t_39_2;
                nile_Real_t t_41 = nile_Real_lt(t_40_x, v.v_max_x);
                nile_Real_t t_42 = nile_Real_nz (t_41) ? t_40_x : v.v_max_x;
                nile_Real_t t_43 = nile_Real_lt(t_40_y, v.v_max_y);
                nile_Real_t t_44 = nile_Real_nz (t_43) ? t_40_y : v.v_max_y;
                nile_Real_t t_45_1 = t_42;
                nile_Real_t t_45_2 = t_44;
                nile_Real_t t_46_x = t_45_1;
                nile_Real_t t_46_y = t_45_2;
                nile_Real_t v_cA_x = t_46_x;
                nile_Real_t v_cA_y = t_46_y;
                nile_Real_t t_47 = nile_Real_gt(v.v_min_x, v_C_x);
                nile_Real_t t_48 = nile_Real_nz (t_47) ? v.v_min_x : v_C_x;
                nile_Real_t t_49 = nile_Real_gt(v.v_min_y, v_C_y);
                nile_Real_t t_50 = nile_Real_nz (t_49) ? v.v_min_y : v_C_y;
                nile_Real_t t_51_1 = t_48;
                nile_Real_t t_51_2 = t_50;
                nile_Real_t t_52_x = t_51_1;
                nile_Real_t t_52_y = t_51_2;
                nile_Real_t t_53 = nile_Real_lt(t_52_x, v.v_max_x);
                nile_Real_t t_54 = nile_Real_nz (t_53) ? t_52_x : v.v_max_x;
                nile_Real_t t_55 = nile_Real_lt(t_52_y, v.v_max_y);
                nile_Real_t t_56 = nile_Real_nz (t_55) ? t_52_y : v.v_max_y;
                nile_Real_t t_57_1 = t_54;
                nile_Real_t t_57_2 = t_56;
                nile_Real_t t_58_x = t_57_1;
                nile_Real_t t_58_y = t_57_2;
                nile_Real_t v_cC_x = t_58_x;
                nile_Real_t v_cC_y = t_58_y;
                nile_Real_t t_60 = nile_Real_add(v_cA_x, v_cC_x);
                nile_Real_t t_61 = nile_Real (2);
                nile_Real_t t_62 = nile_Real_div(t_60, t_61);
                nile_Real_t t_63 = nile_Real_add(v_cA_y, v_cC_y);
                nile_Real_t t_64 = nile_Real (2);
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
                nile_Real_t t_68_A_x = t_59_1_x;
                nile_Real_t t_68_A_y = t_59_1_y;
                nile_Real_t t_68_B_x = t_59_2_x;
                nile_Real_t t_68_B_y = t_59_2_y;
                nile_Real_t t_68_C_x = t_59_3_x;
                nile_Real_t t_68_C_y = t_59_3_y;
                if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                    out = nile_Process_append_output (p, out);
                nile_Buffer_push_tail(out, t_68_A_x);
                nile_Buffer_push_tail(out, t_68_A_y);
                nile_Buffer_push_tail(out, t_68_B_x);
                nile_Buffer_push_tail(out, t_68_B_y);
                nile_Buffer_push_tail(out, t_68_C_x);
                nile_Buffer_push_tail(out, t_68_C_y);
            }
            else {
                nile_Real_t t_69 = nile_Real_add(v_A_x, v_B_x);
                nile_Real_t t_70 = nile_Real (2);
                nile_Real_t t_71 = nile_Real_div(t_69, t_70);
                nile_Real_t t_72 = nile_Real_add(v_A_y, v_B_y);
                nile_Real_t t_73 = nile_Real (2);
                nile_Real_t t_74 = nile_Real_div(t_72, t_73);
                nile_Real_t t_75_1 = t_71;
                nile_Real_t t_75_2 = t_74;
                nile_Real_t t_76_x = t_75_1;
                nile_Real_t t_76_y = t_75_2;
                nile_Real_t t_77 = nile_Real_add(v_B_x, v_C_x);
                nile_Real_t t_78 = nile_Real (2);
                nile_Real_t t_79 = nile_Real_div(t_77, t_78);
                nile_Real_t t_80 = nile_Real_add(v_B_y, v_C_y);
                nile_Real_t t_81 = nile_Real (2);
                nile_Real_t t_82 = nile_Real_div(t_80, t_81);
                nile_Real_t t_83_1 = t_79;
                nile_Real_t t_83_2 = t_82;
                nile_Real_t t_84_x = t_83_1;
                nile_Real_t t_84_y = t_83_2;
                nile_Real_t t_85 = nile_Real_add(t_76_x, t_84_x);
                nile_Real_t t_86 = nile_Real (2);
                nile_Real_t t_87 = nile_Real_div(t_85, t_86);
                nile_Real_t t_88 = nile_Real_add(t_76_y, t_84_y);
                nile_Real_t t_89 = nile_Real (2);
                nile_Real_t t_90 = nile_Real_div(t_88, t_89);
                nile_Real_t t_91_1 = t_87;
                nile_Real_t t_91_2 = t_90;
                nile_Real_t t_92_x = t_91_1;
                nile_Real_t t_92_y = t_91_2;
                nile_Real_t v_ABBC_x = t_92_x;
                nile_Real_t v_ABBC_y = t_92_y;
                nile_Real_t t_93_x = nile_Real_sub(v_ABBC_x, v.v_min_x);
                nile_Real_t t_93_y = nile_Real_sub(v_ABBC_y, v.v_min_y);
                nile_Real_t t_94 = nile_Real (0);
                nile_Real_t t_95 = nile_Real_lt(t_93_x, t_94);
                nile_Real_t t_96 = nile_Real_neg(t_93_x);
                nile_Real_t t_97 = nile_Real_nz (t_95) ? t_96 : t_93_x;
                nile_Real_t t_98 = nile_Real (0);
                nile_Real_t t_99 = nile_Real_lt(t_93_y, t_98);
                nile_Real_t t_100 = nile_Real_neg(t_93_y);
                nile_Real_t t_101 = nile_Real_nz (t_99) ? t_100 : t_93_y;
                nile_Real_t t_102_1 = t_97;
                nile_Real_t t_102_2 = t_101;
                nile_Real_t t_103_x = t_102_1;
                nile_Real_t t_103_y = t_102_2;
                nile_Real_t t_104 = nile_Real (0.1);
                nile_Real_t t_105_x = t_104;
                nile_Real_t t_105_y = t_104;
                nile_Real_t t_106_x = nile_Real_lt(t_103_x, t_105_x);
                nile_Real_t t_106_y = nile_Real_lt(t_103_y, t_105_y);
                nile_Real_t v_nearmin_x = t_106_x;
                nile_Real_t v_nearmin_y = t_106_y;
                nile_Real_t t_107_x = nile_Real_sub(v_ABBC_x, v.v_max_x);
                nile_Real_t t_107_y = nile_Real_sub(v_ABBC_y, v.v_max_y);
                nile_Real_t t_108 = nile_Real (0);
                nile_Real_t t_109 = nile_Real_lt(t_107_x, t_108);
                nile_Real_t t_110 = nile_Real_neg(t_107_x);
                nile_Real_t t_111 = nile_Real_nz (t_109) ? t_110 : t_107_x;
                nile_Real_t t_112 = nile_Real (0);
                nile_Real_t t_113 = nile_Real_lt(t_107_y, t_112);
                nile_Real_t t_114 = nile_Real_neg(t_107_y);
                nile_Real_t t_115 = nile_Real_nz (t_113) ? t_114 : t_107_y;
                nile_Real_t t_116_1 = t_111;
                nile_Real_t t_116_2 = t_115;
                nile_Real_t t_117_x = t_116_1;
                nile_Real_t t_117_y = t_116_2;
                nile_Real_t t_118 = nile_Real (0.1);
                nile_Real_t t_119_x = t_118;
                nile_Real_t t_119_y = t_118;
                nile_Real_t t_120_x = nile_Real_lt(t_117_x, t_119_x);
                nile_Real_t t_120_y = nile_Real_lt(t_117_y, t_119_y);
                nile_Real_t v_nearmax_x = t_120_x;
                nile_Real_t v_nearmax_y = t_120_y;
                nile_Real_t t_121_x = nile_Real_nz (v_nearmax_x) ? v.v_max_x : v_ABBC_x;
                nile_Real_t t_121_y = nile_Real_nz (v_nearmax_y) ? v.v_max_y : v_ABBC_y;
                nile_Real_t t_122_x = nile_Real_nz (v_nearmin_x) ? v.v_min_x : t_121_x;
                nile_Real_t t_122_y = nile_Real_nz (v_nearmin_y) ? v.v_min_y : t_121_y;
                nile_Real_t v_M_x = t_122_x;
                nile_Real_t v_M_y = t_122_y;
                nile_Real_t t_124 = nile_Real_add(v_B_x, v_C_x);
                nile_Real_t t_125 = nile_Real (2);
                nile_Real_t t_126 = nile_Real_div(t_124, t_125);
                nile_Real_t t_127 = nile_Real_add(v_B_y, v_C_y);
                nile_Real_t t_128 = nile_Real (2);
                nile_Real_t t_129 = nile_Real_div(t_127, t_128);
                nile_Real_t t_130_1 = t_126;
                nile_Real_t t_130_2 = t_129;
                nile_Real_t t_131_x = t_130_1;
                nile_Real_t t_131_y = t_130_2;
                nile_Real_t t_123_1_x = v_M_x;
                nile_Real_t t_123_1_y = v_M_y;
                nile_Real_t t_123_2_x = t_131_x;
                nile_Real_t t_123_2_y = t_131_y;
                nile_Real_t t_123_3_x = v_C_x;
                nile_Real_t t_123_3_y = v_C_y;
                nile_Real_t t_132_A_x = t_123_1_x;
                nile_Real_t t_132_A_y = t_123_1_y;
                nile_Real_t t_132_B_x = t_123_2_x;
                nile_Real_t t_132_B_y = t_123_2_y;
                nile_Real_t t_132_C_x = t_123_3_x;
                nile_Real_t t_132_C_y = t_123_3_y;
                if (nile_Buffer_headroom (in) < IN_QUANTUM)
                    in = nile_Process_prefix_input (p, in);
                nile_Buffer_push_head(in, t_132_C_y);
                nile_Buffer_push_head(in, t_132_C_x);
                nile_Buffer_push_head(in, t_132_B_y);
                nile_Buffer_push_head(in, t_132_B_x);
                nile_Buffer_push_head(in, t_132_A_y);
                nile_Buffer_push_head(in, t_132_A_x);
                nile_Real_t t_134 = nile_Real_add(v_A_x, v_B_x);
                nile_Real_t t_135 = nile_Real (2);
                nile_Real_t t_136 = nile_Real_div(t_134, t_135);
                nile_Real_t t_137 = nile_Real_add(v_A_y, v_B_y);
                nile_Real_t t_138 = nile_Real (2);
                nile_Real_t t_139 = nile_Real_div(t_137, t_138);
                nile_Real_t t_140_1 = t_136;
                nile_Real_t t_140_2 = t_139;
                nile_Real_t t_141_x = t_140_1;
                nile_Real_t t_141_y = t_140_2;
                nile_Real_t t_133_1_x = v_A_x;
                nile_Real_t t_133_1_y = v_A_y;
                nile_Real_t t_133_2_x = t_141_x;
                nile_Real_t t_133_2_y = t_141_y;
                nile_Real_t t_133_3_x = v_M_x;
                nile_Real_t t_133_3_y = v_M_y;
                nile_Real_t t_142_A_x = t_133_1_x;
                nile_Real_t t_142_A_y = t_133_1_y;
                nile_Real_t t_142_B_x = t_133_2_x;
                nile_Real_t t_142_B_y = t_133_2_y;
                nile_Real_t t_142_C_x = t_133_3_x;
                nile_Real_t t_142_C_y = t_133_3_y;
                if (nile_Buffer_headroom (in) < IN_QUANTUM)
                    in = nile_Process_prefix_input (p, in);
                nile_Buffer_push_head(in, t_142_C_y);
                nile_Buffer_push_head(in, t_142_C_x);
                nile_Buffer_push_head(in, t_142_B_y);
                nile_Buffer_push_head(in, t_142_B_x);
                nile_Buffer_push_head(in, t_142_A_y);
                nile_Buffer_push_head(in, t_142_A_x);
            }
        }
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ClipBeziers_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ClipBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_ClipBeziers_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ClipBeziers (nile_Process_t *p, 
                    float v_min_x, 
                    float v_min_y, 
                    float v_max_x, 
                    float v_max_y)
{
    gezira_ClipBeziers_vars_t *vars;
    gezira_ClipBeziers_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ClipBeziers_prologue, gezira_ClipBeziers_body, gezira_ClipBeziers_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_min_x = nile_Real (v_min_x);
        v.v_min_y = nile_Real (v_min_y);
        v.v_max_x = nile_Real (v_max_x);
        v.v_max_y = nile_Real (v_max_y);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeClear_vars_t;

static nile_Buffer_t *
gezira_CompositeClear_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeClear_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeClear_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeClear_body (nile_Process_t *p,
                            nile_Buffer_t *in,
                            nile_Buffer_t *out)
{
    gezira_CompositeClear_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeClear_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeClear_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0);
        nile_Real_t t_2_a = t_1;
        nile_Real_t t_2_r = t_1;
        nile_Real_t t_2_g = t_1;
        nile_Real_t t_2_b = t_1;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_2_a);
        nile_Buffer_push_tail(out, t_2_r);
        nile_Buffer_push_tail(out, t_2_g);
        nile_Buffer_push_tail(out, t_2_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeClear_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeClear_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeClear_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeClear (nile_Process_t *p)
{
    gezira_CompositeClear_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeClear_prologue, gezira_CompositeClear_body, gezira_CompositeClear_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSrc_vars_t;

static nile_Buffer_t *
gezira_CompositeSrc_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrc_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrc_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrc_body (nile_Process_t *p,
                          nile_Buffer_t *in,
                          nile_Buffer_t *out)
{
    gezira_CompositeSrc_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrc_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSrc_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, v_a_a);
        nile_Buffer_push_tail(out, v_a_r);
        nile_Buffer_push_tail(out, v_a_g);
        nile_Buffer_push_tail(out, v_a_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrc_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrc_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrc_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSrc (nile_Process_t *p)
{
    gezira_CompositeSrc_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSrc_prologue, gezira_CompositeSrc_body, gezira_CompositeSrc_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDst_vars_t;

static nile_Buffer_t *
gezira_CompositeDst_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDst_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDst_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDst_body (nile_Process_t *p,
                          nile_Buffer_t *in,
                          nile_Buffer_t *out)
{
    gezira_CompositeDst_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDst_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDst_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, v_b_a);
        nile_Buffer_push_tail(out, v_b_r);
        nile_Buffer_push_tail(out, v_b_g);
        nile_Buffer_push_tail(out, v_b_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDst_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDst_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDst_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDst (nile_Process_t *p)
{
    gezira_CompositeDst_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDst_prologue, gezira_CompositeDst_body, gezira_CompositeDst_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeOver_vars_t;

static nile_Buffer_t *
gezira_CompositeOver_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOver_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeOver_body (nile_Process_t *p,
                           nile_Buffer_t *in,
                           nile_Buffer_t *out)
{
    gezira_CompositeOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOver_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeOver_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_5_a);
        nile_Buffer_push_tail(out, t_5_r);
        nile_Buffer_push_tail(out, t_5_g);
        nile_Buffer_push_tail(out, t_5_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeOver_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOver_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeOver (nile_Process_t *p)
{
    gezira_CompositeOver_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeOver_prologue, gezira_CompositeOver_body, gezira_CompositeOver_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDstOver_vars_t;

static nile_Buffer_t *
gezira_CompositeDstOver_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOver_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstOver_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_CompositeDstOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOver_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDstOver_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_5_a);
        nile_Buffer_push_tail(out, t_5_r);
        nile_Buffer_push_tail(out, t_5_g);
        nile_Buffer_push_tail(out, t_5_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstOver_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstOver_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOver_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDstOver (nile_Process_t *p)
{
    gezira_CompositeDstOver_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDstOver_prologue, gezira_CompositeDstOver_body, gezira_CompositeDstOver_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSrcIn_vars_t;

static nile_Buffer_t *
gezira_CompositeSrcIn_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcIn_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcIn_body (nile_Process_t *p,
                            nile_Buffer_t *in,
                            nile_Buffer_t *out)
{
    gezira_CompositeSrcIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcIn_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSrcIn_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_2_a);
        nile_Buffer_push_tail(out, t_2_r);
        nile_Buffer_push_tail(out, t_2_g);
        nile_Buffer_push_tail(out, t_2_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcIn_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcIn_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSrcIn (nile_Process_t *p)
{
    gezira_CompositeSrcIn_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSrcIn_prologue, gezira_CompositeSrcIn_body, gezira_CompositeSrcIn_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDstIn_vars_t;

static nile_Buffer_t *
gezira_CompositeDstIn_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstIn_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstIn_body (nile_Process_t *p,
                            nile_Buffer_t *in,
                            nile_Buffer_t *out)
{
    gezira_CompositeDstIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstIn_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDstIn_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = v_a_a;
        nile_Real_t t_1_r = v_a_a;
        nile_Real_t t_1_g = v_a_a;
        nile_Real_t t_1_b = v_a_a;
        nile_Real_t t_2_a = nile_Real_mul(v_b_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_b_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_b_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_b_b, t_1_b);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_2_a);
        nile_Buffer_push_tail(out, t_2_r);
        nile_Buffer_push_tail(out, t_2_g);
        nile_Buffer_push_tail(out, t_2_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstIn_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstIn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstIn_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDstIn (nile_Process_t *p)
{
    gezira_CompositeDstIn_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDstIn_prologue, gezira_CompositeDstIn_body, gezira_CompositeDstIn_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSrcOut_vars_t;

static nile_Buffer_t *
gezira_CompositeSrcOut_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcOut_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcOut_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CompositeSrcOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcOut_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSrcOut_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real_sub(t_1, v_b_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_a);
        nile_Buffer_push_tail(out, t_4_r);
        nile_Buffer_push_tail(out, t_4_g);
        nile_Buffer_push_tail(out, t_4_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcOut_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcOut_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSrcOut (nile_Process_t *p)
{
    gezira_CompositeSrcOut_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSrcOut_prologue, gezira_CompositeSrcOut_body, gezira_CompositeSrcOut_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDstOut_vars_t;

static nile_Buffer_t *
gezira_CompositeDstOut_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOut_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstOut_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CompositeDstOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOut_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDstOut_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real_sub(t_1, v_a_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_b_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_b_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_b_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_b_b, t_3_b);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_a);
        nile_Buffer_push_tail(out, t_4_r);
        nile_Buffer_push_tail(out, t_4_g);
        nile_Buffer_push_tail(out, t_4_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstOut_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstOut_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstOut_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDstOut (nile_Process_t *p)
{
    gezira_CompositeDstOut_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDstOut_prologue, gezira_CompositeDstOut_body, gezira_CompositeDstOut_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSrcAtop_vars_t;

static nile_Buffer_t *
gezira_CompositeSrcAtop_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcAtop_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcAtop_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_CompositeSrcAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcAtop_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSrcAtop_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = v_b_a;
        nile_Real_t t_1_r = v_b_a;
        nile_Real_t t_1_g = v_b_a;
        nile_Real_t t_1_b = v_b_a;
        nile_Real_t t_2_a = nile_Real_mul(v_a_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_a_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_a_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_a_b, t_1_b);
        nile_Real_t t_3 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_7_a);
        nile_Buffer_push_tail(out, t_7_r);
        nile_Buffer_push_tail(out, t_7_g);
        nile_Buffer_push_tail(out, t_7_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSrcAtop_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSrcAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSrcAtop_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSrcAtop (nile_Process_t *p)
{
    gezira_CompositeSrcAtop_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSrcAtop_prologue, gezira_CompositeSrcAtop_body, gezira_CompositeSrcAtop_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDstAtop_vars_t;

static nile_Buffer_t *
gezira_CompositeDstAtop_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstAtop_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstAtop_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_CompositeDstAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstAtop_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDstAtop_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = v_a_a;
        nile_Real_t t_1_r = v_a_a;
        nile_Real_t t_1_g = v_a_a;
        nile_Real_t t_1_b = v_a_a;
        nile_Real_t t_2_a = nile_Real_mul(v_b_a, t_1_a);
        nile_Real_t t_2_r = nile_Real_mul(v_b_r, t_1_r);
        nile_Real_t t_2_g = nile_Real_mul(v_b_g, t_1_g);
        nile_Real_t t_2_b = nile_Real_mul(v_b_b, t_1_b);
        nile_Real_t t_3 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_7_a);
        nile_Buffer_push_tail(out, t_7_r);
        nile_Buffer_push_tail(out, t_7_g);
        nile_Buffer_push_tail(out, t_7_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDstAtop_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDstAtop_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDstAtop_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDstAtop (nile_Process_t *p)
{
    gezira_CompositeDstAtop_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDstAtop_prologue, gezira_CompositeDstAtop_body, gezira_CompositeDstAtop_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeXor_vars_t;

static nile_Buffer_t *
gezira_CompositeXor_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeXor_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeXor_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeXor_body (nile_Process_t *p,
                          nile_Buffer_t *in,
                          nile_Buffer_t *out)
{
    gezira_CompositeXor_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeXor_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeXor_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real_sub(t_1, v_b_a);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_mul(v_a_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_mul(v_a_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_mul(v_a_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_mul(v_a_b, t_3_b);
        nile_Real_t t_5 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_9_a);
        nile_Buffer_push_tail(out, t_9_r);
        nile_Buffer_push_tail(out, t_9_g);
        nile_Buffer_push_tail(out, t_9_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeXor_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeXor_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeXor_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeXor (nile_Process_t *p)
{
    gezira_CompositeXor_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeXor_prologue, gezira_CompositeXor_body, gezira_CompositeXor_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositePlus_vars_t;

static nile_Buffer_t *
gezira_CompositePlus_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositePlus_vars_t *vars = nile_Process_vars (p);
    gezira_CompositePlus_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositePlus_body (nile_Process_t *p,
                           nile_Buffer_t *in,
                           nile_Buffer_t *out)
{
    gezira_CompositePlus_vars_t *vars = nile_Process_vars (p);
    gezira_CompositePlus_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositePlus_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4 = nile_Real_lt(t_1_a, t_3_a);
        nile_Real_t t_5 = nile_Real_nz (t_4) ? t_1_a : t_3_a;
        nile_Real_t t_6 = nile_Real_lt(t_1_r, t_3_r);
        nile_Real_t t_7 = nile_Real_nz (t_6) ? t_1_r : t_3_r;
        nile_Real_t t_8 = nile_Real_lt(t_1_g, t_3_g);
        nile_Real_t t_9 = nile_Real_nz (t_8) ? t_1_g : t_3_g;
        nile_Real_t t_10 = nile_Real_lt(t_1_b, t_3_b);
        nile_Real_t t_11 = nile_Real_nz (t_10) ? t_1_b : t_3_b;
        nile_Real_t t_12_1 = t_5;
        nile_Real_t t_12_2 = t_7;
        nile_Real_t t_12_3 = t_9;
        nile_Real_t t_12_4 = t_11;
        nile_Real_t t_13_a = t_12_1;
        nile_Real_t t_13_r = t_12_2;
        nile_Real_t t_13_g = t_12_3;
        nile_Real_t t_13_b = t_12_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_13_a);
        nile_Buffer_push_tail(out, t_13_r);
        nile_Buffer_push_tail(out, t_13_g);
        nile_Buffer_push_tail(out, t_13_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositePlus_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositePlus_vars_t *vars = nile_Process_vars (p);
    gezira_CompositePlus_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositePlus (nile_Process_t *p)
{
    gezira_CompositePlus_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositePlus_prologue, gezira_CompositePlus_body, gezira_CompositePlus_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeMultiply_vars_t;

static nile_Buffer_t *
gezira_CompositeMultiply_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeMultiply_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeMultiply_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeMultiply_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_CompositeMultiply_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeMultiply_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeMultiply_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_mul(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_mul(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_mul(v_a_b, v_b_b);
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_a);
        nile_Real_t t_4_a = t_3;
        nile_Real_t t_4_r = t_3;
        nile_Real_t t_4_g = t_3;
        nile_Real_t t_4_b = t_3;
        nile_Real_t t_5_a = nile_Real_mul(v_a_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_mul(v_a_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_mul(v_a_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_mul(v_a_b, t_4_b);
        nile_Real_t t_6 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_11_a);
        nile_Buffer_push_tail(out, t_11_r);
        nile_Buffer_push_tail(out, t_11_g);
        nile_Buffer_push_tail(out, t_11_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeMultiply_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeMultiply_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeMultiply_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeMultiply (nile_Process_t *p)
{
    gezira_CompositeMultiply_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeMultiply_prologue, gezira_CompositeMultiply_body, gezira_CompositeMultiply_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeScreen_vars_t;

static nile_Buffer_t *
gezira_CompositeScreen_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeScreen_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeScreen_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeScreen_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CompositeScreen_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeScreen_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeScreen_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_3_a);
        nile_Buffer_push_tail(out, t_3_r);
        nile_Buffer_push_tail(out, t_3_g);
        nile_Buffer_push_tail(out, t_3_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeScreen_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeScreen_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeScreen_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeScreen (nile_Process_t *p)
{
    gezira_CompositeScreen_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeScreen_prologue, gezira_CompositeScreen_body, gezira_CompositeScreen_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeOverlay_vars_t;

static nile_Buffer_t *
gezira_CompositeOverlay_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeOverlay_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOverlay_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeOverlay_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_CompositeOverlay_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOverlay_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeOverlay_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (2);
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
        nile_Real_t t_5 = nile_Real (1);
        nile_Real_t t_6 = nile_Real_sub(t_5, v_b_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(v_a_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_mul(v_a_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_mul(v_a_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_mul(v_a_b, t_7_b);
        nile_Real_t t_9 = nile_Real (1);
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
        nile_Real_t t_16 = nile_Real (2);
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
        nile_Real_t t_26 = nile_Real (1);
        nile_Real_t t_27 = nile_Real_sub(t_26, v_b_a);
        nile_Real_t t_28_a = t_27;
        nile_Real_t t_28_r = t_27;
        nile_Real_t t_28_g = t_27;
        nile_Real_t t_28_b = t_27;
        nile_Real_t t_29_a = nile_Real_mul(v_a_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_mul(v_a_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_mul(v_a_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_mul(v_a_b, t_28_b);
        nile_Real_t t_30 = nile_Real (1);
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
        nile_Real_t t_36 = nile_Real (2);
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
        nile_Real_t t_41_a = nile_Real_nz (t_40_a) ? v_c_a : v_d_a;
        nile_Real_t t_41_r = nile_Real_nz (t_40_r) ? v_c_r : v_d_r;
        nile_Real_t t_41_g = nile_Real_nz (t_40_g) ? v_c_g : v_d_g;
        nile_Real_t t_41_b = nile_Real_nz (t_40_b) ? v_c_b : v_d_b;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_41_a);
        nile_Buffer_push_tail(out, t_41_r);
        nile_Buffer_push_tail(out, t_41_g);
        nile_Buffer_push_tail(out, t_41_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeOverlay_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeOverlay_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeOverlay_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeOverlay (nile_Process_t *p)
{
    gezira_CompositeOverlay_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeOverlay_prologue, gezira_CompositeOverlay_body, gezira_CompositeOverlay_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDarken_vars_t;

static nile_Buffer_t *
gezira_CompositeDarken_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDarken_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDarken_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDarken_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CompositeDarken_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDarken_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDarken_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
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
        nile_Real_t t_6 = nile_Real_nz (t_5) ? t_2_a : t_4_a;
        nile_Real_t t_7 = nile_Real_lt(t_2_r, t_4_r);
        nile_Real_t t_8 = nile_Real_nz (t_7) ? t_2_r : t_4_r;
        nile_Real_t t_9 = nile_Real_lt(t_2_g, t_4_g);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_2_g : t_4_g;
        nile_Real_t t_11 = nile_Real_lt(t_2_b, t_4_b);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? t_2_b : t_4_b;
        nile_Real_t t_13_1 = t_6;
        nile_Real_t t_13_2 = t_8;
        nile_Real_t t_13_3 = t_10;
        nile_Real_t t_13_4 = t_12;
        nile_Real_t t_14_a = t_13_1;
        nile_Real_t t_14_r = t_13_2;
        nile_Real_t t_14_g = t_13_3;
        nile_Real_t t_14_b = t_13_4;
        nile_Real_t t_15 = nile_Real (1);
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_24_a);
        nile_Buffer_push_tail(out, t_24_r);
        nile_Buffer_push_tail(out, t_24_g);
        nile_Buffer_push_tail(out, t_24_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDarken_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDarken_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDarken_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDarken (nile_Process_t *p)
{
    gezira_CompositeDarken_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDarken_prologue, gezira_CompositeDarken_body, gezira_CompositeDarken_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeLighten_vars_t;

static nile_Buffer_t *
gezira_CompositeLighten_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeLighten_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeLighten_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeLighten_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_CompositeLighten_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeLighten_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeLighten_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
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
        nile_Real_t t_6 = nile_Real_nz (t_5) ? t_2_a : t_4_a;
        nile_Real_t t_7 = nile_Real_gt(t_2_r, t_4_r);
        nile_Real_t t_8 = nile_Real_nz (t_7) ? t_2_r : t_4_r;
        nile_Real_t t_9 = nile_Real_gt(t_2_g, t_4_g);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_2_g : t_4_g;
        nile_Real_t t_11 = nile_Real_gt(t_2_b, t_4_b);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? t_2_b : t_4_b;
        nile_Real_t t_13_1 = t_6;
        nile_Real_t t_13_2 = t_8;
        nile_Real_t t_13_3 = t_10;
        nile_Real_t t_13_4 = t_12;
        nile_Real_t t_14_a = t_13_1;
        nile_Real_t t_14_r = t_13_2;
        nile_Real_t t_14_g = t_13_3;
        nile_Real_t t_14_b = t_13_4;
        nile_Real_t t_15 = nile_Real (1);
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_24_a);
        nile_Buffer_push_tail(out, t_24_r);
        nile_Buffer_push_tail(out, t_24_g);
        nile_Buffer_push_tail(out, t_24_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeLighten_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeLighten_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeLighten_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeLighten (nile_Process_t *p)
{
    gezira_CompositeLighten_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeLighten_prologue, gezira_CompositeLighten_body, gezira_CompositeLighten_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeColorDodge_vars_t;

static nile_Buffer_t *
gezira_CompositeColorDodge_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeColorDodge_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorDodge_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeColorDodge_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_CompositeColorDodge_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorDodge_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeColorDodge_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real_mul(v_a_a, v_b_a);
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_a);
        nile_Real_t t_4_a = t_3;
        nile_Real_t t_4_r = t_3;
        nile_Real_t t_4_g = t_3;
        nile_Real_t t_4_b = t_3;
        nile_Real_t t_5_a = nile_Real_mul(v_a_a, t_4_a);
        nile_Real_t t_5_r = nile_Real_mul(v_a_r, t_4_r);
        nile_Real_t t_5_g = nile_Real_mul(v_a_g, t_4_g);
        nile_Real_t t_5_b = nile_Real_mul(v_a_b, t_4_b);
        nile_Real_t t_6 = nile_Real (1);
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
        nile_Real_t t_15 = nile_Real (1);
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
        nile_Real_t t_21 = nile_Real (1);
        nile_Real_t t_22 = nile_Real_sub(t_21, v_b_a);
        nile_Real_t t_23_a = t_22;
        nile_Real_t t_23_r = t_22;
        nile_Real_t t_23_g = t_22;
        nile_Real_t t_23_b = t_22;
        nile_Real_t t_24_a = nile_Real_mul(v_a_a, t_23_a);
        nile_Real_t t_24_r = nile_Real_mul(v_a_r, t_23_r);
        nile_Real_t t_24_g = nile_Real_mul(v_a_g, t_23_g);
        nile_Real_t t_24_b = nile_Real_mul(v_a_b, t_23_b);
        nile_Real_t t_25 = nile_Real (1);
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
        nile_Real_t t_31 = nile_Real (1);
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33 = nile_Real_lt(t_30_a, t_32_a);
        nile_Real_t t_34 = nile_Real_nz (t_33) ? t_30_a : t_32_a;
        nile_Real_t t_35 = nile_Real_lt(t_30_r, t_32_r);
        nile_Real_t t_36 = nile_Real_nz (t_35) ? t_30_r : t_32_r;
        nile_Real_t t_37 = nile_Real_lt(t_30_g, t_32_g);
        nile_Real_t t_38 = nile_Real_nz (t_37) ? t_30_g : t_32_g;
        nile_Real_t t_39 = nile_Real_lt(t_30_b, t_32_b);
        nile_Real_t t_40 = nile_Real_nz (t_39) ? t_30_b : t_32_b;
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
        nile_Real_t t_51_a = nile_Real_nz (t_50_a) ? v_c_a : v_d_a;
        nile_Real_t t_51_r = nile_Real_nz (t_50_r) ? v_c_r : v_d_r;
        nile_Real_t t_51_g = nile_Real_nz (t_50_g) ? v_c_g : v_d_g;
        nile_Real_t t_51_b = nile_Real_nz (t_50_b) ? v_c_b : v_d_b;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_51_a);
        nile_Buffer_push_tail(out, t_51_r);
        nile_Buffer_push_tail(out, t_51_g);
        nile_Buffer_push_tail(out, t_51_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeColorDodge_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeColorDodge_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorDodge_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeColorDodge (nile_Process_t *p)
{
    gezira_CompositeColorDodge_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeColorDodge_prologue, gezira_CompositeColorDodge_body, gezira_CompositeColorDodge_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeColorBurn_vars_t;

static nile_Buffer_t *
gezira_CompositeColorBurn_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeColorBurn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorBurn_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeColorBurn_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_CompositeColorBurn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorBurn_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeColorBurn_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
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
        nile_Real_t t_12 = nile_Real (1);
        nile_Real_t t_13 = nile_Real_sub(t_12, v_b_a);
        nile_Real_t t_14_a = t_13;
        nile_Real_t t_14_r = t_13;
        nile_Real_t t_14_g = t_13;
        nile_Real_t t_14_b = t_13;
        nile_Real_t t_15_a = nile_Real_mul(v_a_a, t_14_a);
        nile_Real_t t_15_r = nile_Real_mul(v_a_r, t_14_r);
        nile_Real_t t_15_g = nile_Real_mul(v_a_g, t_14_g);
        nile_Real_t t_15_b = nile_Real_mul(v_a_b, t_14_b);
        nile_Real_t t_16 = nile_Real (1);
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
        nile_Real_t t_30 = nile_Real (1);
        nile_Real_t t_31 = nile_Real_sub(t_30, v_b_a);
        nile_Real_t t_32_a = t_31;
        nile_Real_t t_32_r = t_31;
        nile_Real_t t_32_g = t_31;
        nile_Real_t t_32_b = t_31;
        nile_Real_t t_33_a = nile_Real_mul(v_a_a, t_32_a);
        nile_Real_t t_33_r = nile_Real_mul(v_a_r, t_32_r);
        nile_Real_t t_33_g = nile_Real_mul(v_a_g, t_32_g);
        nile_Real_t t_33_b = nile_Real_mul(v_a_b, t_32_b);
        nile_Real_t t_34 = nile_Real (1);
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
        nile_Real_t t_39_a = nile_Real_nz (t_29_a) ? t_38_a : v_c_a;
        nile_Real_t t_39_r = nile_Real_nz (t_29_r) ? t_38_r : v_c_r;
        nile_Real_t t_39_g = nile_Real_nz (t_29_g) ? t_38_g : v_c_g;
        nile_Real_t t_39_b = nile_Real_nz (t_29_b) ? t_38_b : v_c_b;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_39_a);
        nile_Buffer_push_tail(out, t_39_r);
        nile_Buffer_push_tail(out, t_39_g);
        nile_Buffer_push_tail(out, t_39_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeColorBurn_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeColorBurn_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeColorBurn_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeColorBurn (nile_Process_t *p)
{
    gezira_CompositeColorBurn_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeColorBurn_prologue, gezira_CompositeColorBurn_body, gezira_CompositeColorBurn_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeHardLight_vars_t;

static nile_Buffer_t *
gezira_CompositeHardLight_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeHardLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeHardLight_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeHardLight_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_CompositeHardLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeHardLight_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeHardLight_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (2);
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
        nile_Real_t t_5 = nile_Real (1);
        nile_Real_t t_6 = nile_Real_sub(t_5, v_b_a);
        nile_Real_t t_7_a = t_6;
        nile_Real_t t_7_r = t_6;
        nile_Real_t t_7_g = t_6;
        nile_Real_t t_7_b = t_6;
        nile_Real_t t_8_a = nile_Real_mul(v_a_a, t_7_a);
        nile_Real_t t_8_r = nile_Real_mul(v_a_r, t_7_r);
        nile_Real_t t_8_g = nile_Real_mul(v_a_g, t_7_g);
        nile_Real_t t_8_b = nile_Real_mul(v_a_b, t_7_b);
        nile_Real_t t_9 = nile_Real (1);
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
        nile_Real_t t_16 = nile_Real (2);
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
        nile_Real_t t_26 = nile_Real (1);
        nile_Real_t t_27 = nile_Real_sub(t_26, v_b_a);
        nile_Real_t t_28_a = t_27;
        nile_Real_t t_28_r = t_27;
        nile_Real_t t_28_g = t_27;
        nile_Real_t t_28_b = t_27;
        nile_Real_t t_29_a = nile_Real_mul(v_a_a, t_28_a);
        nile_Real_t t_29_r = nile_Real_mul(v_a_r, t_28_r);
        nile_Real_t t_29_g = nile_Real_mul(v_a_g, t_28_g);
        nile_Real_t t_29_b = nile_Real_mul(v_a_b, t_28_b);
        nile_Real_t t_30 = nile_Real (1);
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
        nile_Real_t t_36 = nile_Real (2);
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
        nile_Real_t t_41_a = nile_Real_nz (t_40_a) ? v_c_a : v_d_a;
        nile_Real_t t_41_r = nile_Real_nz (t_40_r) ? v_c_r : v_d_r;
        nile_Real_t t_41_g = nile_Real_nz (t_40_g) ? v_c_g : v_d_g;
        nile_Real_t t_41_b = nile_Real_nz (t_40_b) ? v_c_b : v_d_b;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_41_a);
        nile_Buffer_push_tail(out, t_41_r);
        nile_Buffer_push_tail(out, t_41_g);
        nile_Buffer_push_tail(out, t_41_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeHardLight_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeHardLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeHardLight_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeHardLight (nile_Process_t *p)
{
    gezira_CompositeHardLight_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeHardLight_prologue, gezira_CompositeHardLight_body, gezira_CompositeHardLight_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSoftLight_vars_t;

static nile_Buffer_t *
gezira_CompositeSoftLight_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSoftLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSoftLight_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSoftLight_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_CompositeSoftLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSoftLight_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSoftLight_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
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
        nile_Real_t t_6 = nile_Real (2);
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
        nile_Real_t t_15 = nile_Real (1);
        nile_Real_t t_16 = nile_Real_sub(t_15, v_b_a);
        nile_Real_t t_17_a = t_16;
        nile_Real_t t_17_r = t_16;
        nile_Real_t t_17_g = t_16;
        nile_Real_t t_17_b = t_16;
        nile_Real_t t_18_a = nile_Real_mul(v_a_a, t_17_a);
        nile_Real_t t_18_r = nile_Real_mul(v_a_r, t_17_r);
        nile_Real_t t_18_g = nile_Real_mul(v_a_g, t_17_g);
        nile_Real_t t_18_b = nile_Real_mul(v_a_b, t_17_b);
        nile_Real_t t_19 = nile_Real (1);
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
        nile_Real_t t_25 = nile_Real (3);
        nile_Real_t t_26 = nile_Real (8);
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
        nile_Real_t t_37 = nile_Real (1);
        nile_Real_t t_38 = nile_Real_sub(t_37, v_b_a);
        nile_Real_t t_39_a = t_38;
        nile_Real_t t_39_r = t_38;
        nile_Real_t t_39_g = t_38;
        nile_Real_t t_39_b = t_38;
        nile_Real_t t_40_a = nile_Real_mul(v_a_a, t_39_a);
        nile_Real_t t_40_r = nile_Real_mul(v_a_r, t_39_r);
        nile_Real_t t_40_g = nile_Real_mul(v_a_g, t_39_g);
        nile_Real_t t_40_b = nile_Real_mul(v_a_b, t_39_b);
        nile_Real_t t_41 = nile_Real (1);
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
        nile_Real_t t_51_a = nile_Real_sqt(t_50_a);
        nile_Real_t t_51_r = nile_Real_sqt(t_50_r);
        nile_Real_t t_51_g = nile_Real_sqt(t_50_g);
        nile_Real_t t_51_b = nile_Real_sqt(t_50_b);
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
        nile_Real_t t_55 = nile_Real (2);
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
        nile_Real_t t_62 = nile_Real (1);
        nile_Real_t t_63 = nile_Real_sub(t_62, v_b_a);
        nile_Real_t t_64_a = t_63;
        nile_Real_t t_64_r = t_63;
        nile_Real_t t_64_g = t_63;
        nile_Real_t t_64_b = t_63;
        nile_Real_t t_65_a = nile_Real_mul(v_a_a, t_64_a);
        nile_Real_t t_65_r = nile_Real_mul(v_a_r, t_64_r);
        nile_Real_t t_65_g = nile_Real_mul(v_a_g, t_64_g);
        nile_Real_t t_65_b = nile_Real_mul(v_a_b, t_64_b);
        nile_Real_t t_66 = nile_Real (1);
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
        nile_Real_t t_72 = nile_Real (2);
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
        nile_Real_t t_77 = nile_Real (8);
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
        nile_Real_t t_82_a = nile_Real_nz (t_81_a) ? v_e_a : v_f_a;
        nile_Real_t t_82_r = nile_Real_nz (t_81_r) ? v_e_r : v_f_r;
        nile_Real_t t_82_g = nile_Real_nz (t_81_g) ? v_e_g : v_f_g;
        nile_Real_t t_82_b = nile_Real_nz (t_81_b) ? v_e_b : v_f_b;
        nile_Real_t t_83_a = nile_Real_nz (t_76_a) ? v_d_a : t_82_a;
        nile_Real_t t_83_r = nile_Real_nz (t_76_r) ? v_d_r : t_82_r;
        nile_Real_t t_83_g = nile_Real_nz (t_76_g) ? v_d_g : t_82_g;
        nile_Real_t t_83_b = nile_Real_nz (t_76_b) ? v_d_b : t_82_b;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_83_a);
        nile_Buffer_push_tail(out, t_83_r);
        nile_Buffer_push_tail(out, t_83_g);
        nile_Buffer_push_tail(out, t_83_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSoftLight_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSoftLight_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSoftLight_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSoftLight (nile_Process_t *p)
{
    gezira_CompositeSoftLight_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSoftLight_prologue, gezira_CompositeSoftLight_body, gezira_CompositeSoftLight_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeDifference_vars_t;

static nile_Buffer_t *
gezira_CompositeDifference_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDifference_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDifference_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDifference_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_CompositeDifference_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDifference_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeDifference_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = nile_Real (2);
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
        nile_Real_t t_8 = nile_Real_nz (t_7) ? t_4_a : t_6_a;
        nile_Real_t t_9 = nile_Real_lt(t_4_r, t_6_r);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_4_r : t_6_r;
        nile_Real_t t_11 = nile_Real_lt(t_4_g, t_6_g);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? t_4_g : t_6_g;
        nile_Real_t t_13 = nile_Real_lt(t_4_b, t_6_b);
        nile_Real_t t_14 = nile_Real_nz (t_13) ? t_4_b : t_6_b;
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_23_a);
        nile_Buffer_push_tail(out, t_23_r);
        nile_Buffer_push_tail(out, t_23_g);
        nile_Buffer_push_tail(out, t_23_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeDifference_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeDifference_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeDifference_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeDifference (nile_Process_t *p)
{
    gezira_CompositeDifference_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeDifference_prologue, gezira_CompositeDifference_body, gezira_CompositeDifference_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeExclusion_vars_t;

static nile_Buffer_t *
gezira_CompositeExclusion_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeExclusion_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeExclusion_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeExclusion_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_CompositeExclusion_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeExclusion_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeExclusion_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
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
        nile_Real_t t_6 = nile_Real (2);
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
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12 = nile_Real_sub(t_11, v_b_a);
        nile_Real_t t_13_a = t_12;
        nile_Real_t t_13_r = t_12;
        nile_Real_t t_13_g = t_12;
        nile_Real_t t_13_b = t_12;
        nile_Real_t t_14_a = nile_Real_mul(v_a_a, t_13_a);
        nile_Real_t t_14_r = nile_Real_mul(v_a_r, t_13_r);
        nile_Real_t t_14_g = nile_Real_mul(v_a_g, t_13_g);
        nile_Real_t t_14_b = nile_Real_mul(v_a_b, t_13_b);
        nile_Real_t t_15 = nile_Real (1);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_24_a);
        nile_Buffer_push_tail(out, t_24_r);
        nile_Buffer_push_tail(out, t_24_g);
        nile_Buffer_push_tail(out, t_24_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeExclusion_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeExclusion_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeExclusion_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeExclusion (nile_Process_t *p)
{
    gezira_CompositeExclusion_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeExclusion_prologue, gezira_CompositeExclusion_body, gezira_CompositeExclusion_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeSubtract_vars_t;

static nile_Buffer_t *
gezira_CompositeSubtract_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSubtract_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSubtract_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSubtract_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_CompositeSubtract_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSubtract_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeSubtract_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = nile_Real_add(v_a_a, v_b_a);
        nile_Real_t t_1_r = nile_Real_add(v_a_r, v_b_r);
        nile_Real_t t_1_g = nile_Real_add(v_a_g, v_b_g);
        nile_Real_t t_1_b = nile_Real_add(v_a_b, v_b_b);
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3_a = t_2;
        nile_Real_t t_3_r = t_2;
        nile_Real_t t_3_g = t_2;
        nile_Real_t t_3_b = t_2;
        nile_Real_t t_4_a = nile_Real_sub(t_1_a, t_3_a);
        nile_Real_t t_4_r = nile_Real_sub(t_1_r, t_3_r);
        nile_Real_t t_4_g = nile_Real_sub(t_1_g, t_3_g);
        nile_Real_t t_4_b = nile_Real_sub(t_1_b, t_3_b);
        nile_Real_t t_5 = nile_Real (0);
        nile_Real_t t_6_a = t_5;
        nile_Real_t t_6_r = t_5;
        nile_Real_t t_6_g = t_5;
        nile_Real_t t_6_b = t_5;
        nile_Real_t t_7 = nile_Real_gt(t_4_a, t_6_a);
        nile_Real_t t_8 = nile_Real_nz (t_7) ? t_4_a : t_6_a;
        nile_Real_t t_9 = nile_Real_gt(t_4_r, t_6_r);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_4_r : t_6_r;
        nile_Real_t t_11 = nile_Real_gt(t_4_g, t_6_g);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? t_4_g : t_6_g;
        nile_Real_t t_13 = nile_Real_gt(t_4_b, t_6_b);
        nile_Real_t t_14 = nile_Real_nz (t_13) ? t_4_b : t_6_b;
        nile_Real_t t_15_1 = t_8;
        nile_Real_t t_15_2 = t_10;
        nile_Real_t t_15_3 = t_12;
        nile_Real_t t_15_4 = t_14;
        nile_Real_t t_16_a = t_15_1;
        nile_Real_t t_16_r = t_15_2;
        nile_Real_t t_16_g = t_15_3;
        nile_Real_t t_16_b = t_15_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16_a);
        nile_Buffer_push_tail(out, t_16_r);
        nile_Buffer_push_tail(out, t_16_g);
        nile_Buffer_push_tail(out, t_16_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeSubtract_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeSubtract_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeSubtract_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeSubtract (nile_Process_t *p)
{
    gezira_CompositeSubtract_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeSubtract_prologue, gezira_CompositeSubtract_body, gezira_CompositeSubtract_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 8
#define OUT_QUANTUM 4

typedef struct {
} gezira_CompositeInvert_vars_t;

static nile_Buffer_t *
gezira_CompositeInvert_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeInvert_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeInvert_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeInvert_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_CompositeInvert_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeInvert_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CompositeInvert_vars_t v_ = v;
        nile_Real_t v_a_a = nile_Buffer_pop_head(in);
        nile_Real_t v_a_r = nile_Buffer_pop_head(in);
        nile_Real_t v_a_g = nile_Buffer_pop_head(in);
        nile_Real_t v_a_b = nile_Buffer_pop_head(in);
        nile_Real_t v_b_a = nile_Buffer_pop_head(in);
        nile_Real_t v_b_r = nile_Buffer_pop_head(in);
        nile_Real_t v_b_g = nile_Buffer_pop_head(in);
        nile_Real_t v_b_b = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3 = nile_Real_sub(t_2, v_b_r);
        nile_Real_t t_4 = nile_Real (1);
        nile_Real_t t_5 = nile_Real_sub(t_4, v_b_g);
        nile_Real_t t_6 = nile_Real (1);
        nile_Real_t t_7 = nile_Real_sub(t_6, v_b_b);
        nile_Real_t t_1_1 = v_b_a;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_1_3 = t_5;
        nile_Real_t t_1_4 = t_7;
        nile_Real_t t_8_a = t_1_1;
        nile_Real_t t_8_r = t_1_2;
        nile_Real_t t_8_g = t_1_3;
        nile_Real_t t_8_b = t_1_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_a);
        nile_Buffer_push_tail(out, t_8_r);
        nile_Buffer_push_tail(out, t_8_g);
        nile_Buffer_push_tail(out, t_8_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CompositeInvert_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CompositeInvert_vars_t *vars = nile_Process_vars (p);
    gezira_CompositeInvert_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_CompositeInvert (nile_Process_t *p)
{
    gezira_CompositeInvert_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CompositeInvert_prologue, gezira_CompositeInvert_body, gezira_CompositeInvert_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_a;
} gezira_InverseOver_vars_t;

static nile_Buffer_t *
gezira_InverseOver_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_InverseOver_vars_t *vars = nile_Process_vars (p);
    gezira_InverseOver_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_InverseOver_body (nile_Process_t *p,
                         nile_Buffer_t *in,
                         nile_Buffer_t *out)
{
    gezira_InverseOver_vars_t *vars = nile_Process_vars (p);
    gezira_InverseOver_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_InverseOver_vars_t v_ = v;
        nile_Real_t v_C_a = nile_Buffer_pop_head(in);
        nile_Real_t v_C_r = nile_Buffer_pop_head(in);
        nile_Real_t v_C_g = nile_Buffer_pop_head(in);
        nile_Real_t v_C_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real (0);
        nile_Real_t t_3 = nile_Real_neq(v_C_a, t_2);
        nile_Real_t t_4 = nile_Real_nz (t_3) ? v_C_a : t_1;
        nile_Real_t t_5_a = t_4;
        nile_Real_t t_5_r = t_4;
        nile_Real_t t_5_g = t_4;
        nile_Real_t t_5_b = t_4;
        nile_Real_t t_6_a = nile_Real_div(v_C_a, t_5_a);
        nile_Real_t t_6_r = nile_Real_div(v_C_r, t_5_r);
        nile_Real_t t_6_g = nile_Real_div(v_C_g, t_5_g);
        nile_Real_t t_6_b = nile_Real_div(v_C_b, t_5_b);
        nile_Real_t v_D_a = t_6_a;
        nile_Real_t v_D_r = t_6_r;
        nile_Real_t v_D_g = t_6_g;
        nile_Real_t v_D_b = t_6_b;
        nile_Real_t t_7 = nile_Real (1);
        nile_Real_t t_8_a = t_7;
        nile_Real_t t_8_r = t_7;
        nile_Real_t t_8_g = t_7;
        nile_Real_t t_8_b = t_7;
        nile_Real_t t_9_a = nile_Real_sub(t_8_a, v_D_a);
        nile_Real_t t_9_r = nile_Real_sub(t_8_r, v_D_r);
        nile_Real_t t_9_g = nile_Real_sub(t_8_g, v_D_g);
        nile_Real_t t_9_b = nile_Real_sub(t_8_b, v_D_b);
        nile_Real_t t_10_a = v.v_a;
        nile_Real_t t_10_r = v.v_a;
        nile_Real_t t_10_g = v.v_a;
        nile_Real_t t_10_b = v.v_a;
        nile_Real_t t_11_a = nile_Real_mul(t_10_a, t_9_a);
        nile_Real_t t_11_r = nile_Real_mul(t_10_r, t_9_r);
        nile_Real_t t_11_g = nile_Real_mul(t_10_g, t_9_g);
        nile_Real_t t_11_b = nile_Real_mul(t_10_b, t_9_b);
        nile_Real_t t_12 = nile_Real (1);
        nile_Real_t t_13 = nile_Real_sub(t_12, v.v_a);
        nile_Real_t t_14_a = t_13;
        nile_Real_t t_14_r = t_13;
        nile_Real_t t_14_g = t_13;
        nile_Real_t t_14_b = t_13;
        nile_Real_t t_15_a = nile_Real_mul(t_14_a, v_D_a);
        nile_Real_t t_15_r = nile_Real_mul(t_14_r, v_D_r);
        nile_Real_t t_15_g = nile_Real_mul(t_14_g, v_D_g);
        nile_Real_t t_15_b = nile_Real_mul(t_14_b, v_D_b);
        nile_Real_t t_16_a = nile_Real_add(t_11_a, t_15_a);
        nile_Real_t t_16_r = nile_Real_add(t_11_r, t_15_r);
        nile_Real_t t_16_g = nile_Real_add(t_11_g, t_15_g);
        nile_Real_t t_16_b = nile_Real_add(t_11_b, t_15_b);
        nile_Real_t v_E_a = t_16_a;
        nile_Real_t v_E_r = t_16_r;
        nile_Real_t v_E_g = t_16_g;
        nile_Real_t v_E_b = t_16_b;
        nile_Real_t t_18 = nile_Real_mul(v_C_a, v_E_r);
        nile_Real_t t_19 = nile_Real_mul(v_C_a, v_E_g);
        nile_Real_t t_20 = nile_Real_mul(v_C_a, v_E_b);
        nile_Real_t t_17_1 = v_C_a;
        nile_Real_t t_17_2 = t_18;
        nile_Real_t t_17_3 = t_19;
        nile_Real_t t_17_4 = t_20;
        nile_Real_t t_21_a = t_17_1;
        nile_Real_t t_21_r = t_17_2;
        nile_Real_t t_21_g = t_17_3;
        nile_Real_t t_21_b = t_17_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_21_a);
        nile_Buffer_push_tail(out, t_21_r);
        nile_Buffer_push_tail(out, t_21_g);
        nile_Buffer_push_tail(out, t_21_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_InverseOver_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_InverseOver_vars_t *vars = nile_Process_vars (p);
    gezira_InverseOver_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_InverseOver (nile_Process_t *p, 
                    float v_a)
{
    gezira_InverseOver_vars_t *vars;
    gezira_InverseOver_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_InverseOver_prologue, gezira_InverseOver_body, gezira_InverseOver_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_a = nile_Real (v_a);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_a;
} gezira_ContrastiveOver_vars_t;

static nile_Buffer_t *
gezira_ContrastiveOver_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ContrastiveOver_vars_t *vars = nile_Process_vars (p);
    gezira_ContrastiveOver_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ContrastiveOver_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_ContrastiveOver_vars_t *vars = nile_Process_vars (p);
    gezira_ContrastiveOver_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ContrastiveOver_vars_t v_ = v;
        nile_Real_t v_C_a = nile_Buffer_pop_head(in);
        nile_Real_t v_C_r = nile_Buffer_pop_head(in);
        nile_Real_t v_C_g = nile_Buffer_pop_head(in);
        nile_Real_t v_C_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real (0);
        nile_Real_t t_3 = nile_Real_neq(v_C_a, t_2);
        nile_Real_t t_4 = nile_Real_nz (t_3) ? v_C_a : t_1;
        nile_Real_t t_5_a = t_4;
        nile_Real_t t_5_r = t_4;
        nile_Real_t t_5_g = t_4;
        nile_Real_t t_5_b = t_4;
        nile_Real_t t_6_a = nile_Real_div(v_C_a, t_5_a);
        nile_Real_t t_6_r = nile_Real_div(v_C_r, t_5_r);
        nile_Real_t t_6_g = nile_Real_div(v_C_g, t_5_g);
        nile_Real_t t_6_b = nile_Real_div(v_C_b, t_5_b);
        nile_Real_t v_D_a = t_6_a;
        nile_Real_t v_D_r = t_6_r;
        nile_Real_t v_D_g = t_6_g;
        nile_Real_t v_D_b = t_6_b;
        nile_Real_t t_8 = nile_Real (1);
        nile_Real_t t_9 = nile_Real (1);
        nile_Real_t t_10 = nile_Real (4);
        nile_Real_t t_11 = nile_Real_div(t_9, t_10);
        nile_Real_t t_12 = nile_Real_lt(v_D_r, t_11);
        nile_Real_t t_13 = nile_Real (1);
        nile_Real_t t_14 = nile_Real (2);
        nile_Real_t t_15 = nile_Real_div(t_13, t_14);
        nile_Real_t t_16 = nile_Real (0);
        nile_Real_t t_17 = nile_Real_nz (t_12) ? t_15 : t_16;
        nile_Real_t t_18 = nile_Real (1);
        nile_Real_t t_19 = nile_Real (2);
        nile_Real_t t_20 = nile_Real_div(t_18, t_19);
        nile_Real_t t_21 = nile_Real_lt(v_D_g, t_20);
        nile_Real_t t_22 = nile_Real (5);
        nile_Real_t t_23 = nile_Real (8);
        nile_Real_t t_24 = nile_Real_div(t_22, t_23);
        nile_Real_t t_25 = nile_Real (3);
        nile_Real_t t_26 = nile_Real (8);
        nile_Real_t t_27 = nile_Real_div(t_25, t_26);
        nile_Real_t t_28 = nile_Real_nz (t_21) ? t_24 : t_27;
        nile_Real_t t_29 = nile_Real (3);
        nile_Real_t t_30 = nile_Real (4);
        nile_Real_t t_31 = nile_Real_div(t_29, t_30);
        nile_Real_t t_32 = nile_Real_lt(v_D_b, t_31);
        nile_Real_t t_33 = nile_Real (1);
        nile_Real_t t_34 = nile_Real (1);
        nile_Real_t t_35 = nile_Real (2);
        nile_Real_t t_36 = nile_Real_div(t_34, t_35);
        nile_Real_t t_37 = nile_Real_nz (t_32) ? t_33 : t_36;
        nile_Real_t t_7_1 = t_8;
        nile_Real_t t_7_2 = t_17;
        nile_Real_t t_7_3 = t_28;
        nile_Real_t t_7_4 = t_37;
        nile_Real_t t_38_a = t_7_1;
        nile_Real_t t_38_r = t_7_2;
        nile_Real_t t_38_g = t_7_3;
        nile_Real_t t_38_b = t_7_4;
        nile_Real_t v_E_a = t_38_a;
        nile_Real_t v_E_r = t_38_r;
        nile_Real_t v_E_g = t_38_g;
        nile_Real_t v_E_b = t_38_b;
        nile_Real_t t_39 = nile_Real (1);
        nile_Real_t t_40 = nile_Real_sub(t_39, v.v_a);
        nile_Real_t t_41_a = t_40;
        nile_Real_t t_41_r = t_40;
        nile_Real_t t_41_g = t_40;
        nile_Real_t t_41_b = t_40;
        nile_Real_t t_42_a = nile_Real_mul(t_41_a, v_D_a);
        nile_Real_t t_42_r = nile_Real_mul(t_41_r, v_D_r);
        nile_Real_t t_42_g = nile_Real_mul(t_41_g, v_D_g);
        nile_Real_t t_42_b = nile_Real_mul(t_41_b, v_D_b);
        nile_Real_t t_43_a = v.v_a;
        nile_Real_t t_43_r = v.v_a;
        nile_Real_t t_43_g = v.v_a;
        nile_Real_t t_43_b = v.v_a;
        nile_Real_t t_44_a = nile_Real_mul(t_43_a, v_E_a);
        nile_Real_t t_44_r = nile_Real_mul(t_43_r, v_E_r);
        nile_Real_t t_44_g = nile_Real_mul(t_43_g, v_E_g);
        nile_Real_t t_44_b = nile_Real_mul(t_43_b, v_E_b);
        nile_Real_t t_45_a = nile_Real_add(t_42_a, t_44_a);
        nile_Real_t t_45_r = nile_Real_add(t_42_r, t_44_r);
        nile_Real_t t_45_g = nile_Real_add(t_42_g, t_44_g);
        nile_Real_t t_45_b = nile_Real_add(t_42_b, t_44_b);
        nile_Real_t v_F_a = t_45_a;
        nile_Real_t v_F_r = t_45_r;
        nile_Real_t v_F_g = t_45_g;
        nile_Real_t v_F_b = t_45_b;
        nile_Real_t t_47 = nile_Real_mul(v_C_a, v_F_r);
        nile_Real_t t_48 = nile_Real_mul(v_C_a, v_F_g);
        nile_Real_t t_49 = nile_Real_mul(v_C_a, v_F_b);
        nile_Real_t t_46_1 = v_C_a;
        nile_Real_t t_46_2 = t_47;
        nile_Real_t t_46_3 = t_48;
        nile_Real_t t_46_4 = t_49;
        nile_Real_t t_50_a = t_46_1;
        nile_Real_t t_50_r = t_46_2;
        nile_Real_t t_50_g = t_46_3;
        nile_Real_t t_50_b = t_46_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_50_a);
        nile_Buffer_push_tail(out, t_50_r);
        nile_Buffer_push_tail(out, t_50_g);
        nile_Buffer_push_tail(out, t_50_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ContrastiveOver_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ContrastiveOver_vars_t *vars = nile_Process_vars (p);
    gezira_ContrastiveOver_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ContrastiveOver (nile_Process_t *p, 
                        float v_a)
{
    gezira_ContrastiveOver_vars_t *vars;
    gezira_ContrastiveOver_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ContrastiveOver_prologue, gezira_ContrastiveOver_body, gezira_ContrastiveOver_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_a = nile_Real (v_a);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 5
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_n;
    nile_Real_t v_sum_a;
    nile_Real_t v_sum_r;
    nile_Real_t v_sum_g;
    nile_Real_t v_sum_b;
    nile_Real_t v_i;
} gezira_SumWeightedColors_vars_t;

static nile_Buffer_t *
gezira_SumWeightedColors_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_SumWeightedColors_vars_t *vars = nile_Process_vars (p);
    gezira_SumWeightedColors_vars_t v = *vars;
    nile_Real_t t_4 = nile_Real (0);
    nile_Real_t t_5_a = t_4;
    nile_Real_t t_5_r = t_4;
    nile_Real_t t_5_g = t_4;
    nile_Real_t t_5_b = t_4;
    v.v_sum_a = t_5_a;
    v.v_sum_r = t_5_r;
    v.v_sum_g = t_5_g;
    v.v_sum_b = t_5_b;
    nile_Real_t t_6 = nile_Real (1);
    v.v_i = t_6;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_SumWeightedColors_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_SumWeightedColors_vars_t *vars = nile_Process_vars (p);
    gezira_SumWeightedColors_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_SumWeightedColors_vars_t v_ = v;
        nile_Real_t v_C_a = nile_Buffer_pop_head(in);
        nile_Real_t v_C_r = nile_Buffer_pop_head(in);
        nile_Real_t v_C_g = nile_Buffer_pop_head(in);
        nile_Real_t v_C_b = nile_Buffer_pop_head(in);
        nile_Real_t v_w = nile_Buffer_pop_head(in);
        nile_Real_t t_7 = nile_Real_eq(v.v_i, v.v_n);
        if (nile_Real_nz (t_7)) {
            nile_Real_t t_8 = nile_Real (0);
            nile_Real_t t_9_a = v_w;
            nile_Real_t t_9_r = v_w;
            nile_Real_t t_9_g = v_w;
            nile_Real_t t_9_b = v_w;
            nile_Real_t t_10_a = nile_Real_mul(v_C_a, t_9_a);
            nile_Real_t t_10_r = nile_Real_mul(v_C_r, t_9_r);
            nile_Real_t t_10_g = nile_Real_mul(v_C_g, t_9_g);
            nile_Real_t t_10_b = nile_Real_mul(v_C_b, t_9_b);
            nile_Real_t t_11_a = nile_Real_add(v.v_sum_a, t_10_a);
            nile_Real_t t_11_r = nile_Real_add(v.v_sum_r, t_10_r);
            nile_Real_t t_11_g = nile_Real_add(v.v_sum_g, t_10_g);
            nile_Real_t t_11_b = nile_Real_add(v.v_sum_b, t_10_b);
            nile_Real_t t_12_a = t_8;
            nile_Real_t t_12_r = t_8;
            nile_Real_t t_12_g = t_8;
            nile_Real_t t_12_b = t_8;
            nile_Real_t t_13 = nile_Real_gt(t_12_a, t_11_a);
            nile_Real_t t_14 = nile_Real_nz (t_13) ? t_12_a : t_11_a;
            nile_Real_t t_15 = nile_Real_gt(t_12_r, t_11_r);
            nile_Real_t t_16 = nile_Real_nz (t_15) ? t_12_r : t_11_r;
            nile_Real_t t_17 = nile_Real_gt(t_12_g, t_11_g);
            nile_Real_t t_18 = nile_Real_nz (t_17) ? t_12_g : t_11_g;
            nile_Real_t t_19 = nile_Real_gt(t_12_b, t_11_b);
            nile_Real_t t_20 = nile_Real_nz (t_19) ? t_12_b : t_11_b;
            nile_Real_t t_21_1 = t_14;
            nile_Real_t t_21_2 = t_16;
            nile_Real_t t_21_3 = t_18;
            nile_Real_t t_21_4 = t_20;
            nile_Real_t t_22_a = t_21_1;
            nile_Real_t t_22_r = t_21_2;
            nile_Real_t t_22_g = t_21_3;
            nile_Real_t t_22_b = t_21_4;
            nile_Real_t t_23 = nile_Real (1);
            nile_Real_t t_24_a = t_23;
            nile_Real_t t_24_r = t_23;
            nile_Real_t t_24_g = t_23;
            nile_Real_t t_24_b = t_23;
            nile_Real_t t_25 = nile_Real_lt(t_22_a, t_24_a);
            nile_Real_t t_26 = nile_Real_nz (t_25) ? t_22_a : t_24_a;
            nile_Real_t t_27 = nile_Real_lt(t_22_r, t_24_r);
            nile_Real_t t_28 = nile_Real_nz (t_27) ? t_22_r : t_24_r;
            nile_Real_t t_29 = nile_Real_lt(t_22_g, t_24_g);
            nile_Real_t t_30 = nile_Real_nz (t_29) ? t_22_g : t_24_g;
            nile_Real_t t_31 = nile_Real_lt(t_22_b, t_24_b);
            nile_Real_t t_32 = nile_Real_nz (t_31) ? t_22_b : t_24_b;
            nile_Real_t t_33_1 = t_26;
            nile_Real_t t_33_2 = t_28;
            nile_Real_t t_33_3 = t_30;
            nile_Real_t t_33_4 = t_32;
            nile_Real_t t_34_a = t_33_1;
            nile_Real_t t_34_r = t_33_2;
            nile_Real_t t_34_g = t_33_3;
            nile_Real_t t_34_b = t_33_4;
            if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                out = nile_Process_append_output (p, out);
            nile_Buffer_push_tail(out, t_34_a);
            nile_Buffer_push_tail(out, t_34_r);
            nile_Buffer_push_tail(out, t_34_g);
            nile_Buffer_push_tail(out, t_34_b);
            nile_Real_t t_35 = nile_Real (0);
            nile_Real_t t_36_a = t_35;
            nile_Real_t t_36_r = t_35;
            nile_Real_t t_36_g = t_35;
            nile_Real_t t_36_b = t_35;
            v_.v_sum_a = t_36_a;
            v_.v_sum_r = t_36_r;
            v_.v_sum_g = t_36_g;
            v_.v_sum_b = t_36_b;
            nile_Real_t t_37 = nile_Real (1);
            v_.v_i = t_37;
        }
        else {
            nile_Real_t t_38_a = v_w;
            nile_Real_t t_38_r = v_w;
            nile_Real_t t_38_g = v_w;
            nile_Real_t t_38_b = v_w;
            nile_Real_t t_39_a = nile_Real_mul(v_C_a, t_38_a);
            nile_Real_t t_39_r = nile_Real_mul(v_C_r, t_38_r);
            nile_Real_t t_39_g = nile_Real_mul(v_C_g, t_38_g);
            nile_Real_t t_39_b = nile_Real_mul(v_C_b, t_38_b);
            nile_Real_t t_40_a = nile_Real_add(v.v_sum_a, t_39_a);
            nile_Real_t t_40_r = nile_Real_add(v.v_sum_r, t_39_r);
            nile_Real_t t_40_g = nile_Real_add(v.v_sum_g, t_39_g);
            nile_Real_t t_40_b = nile_Real_add(v.v_sum_b, t_39_b);
            v_.v_sum_a = t_40_a;
            v_.v_sum_r = t_40_r;
            v_.v_sum_g = t_40_g;
            v_.v_sum_b = t_40_b;
            nile_Real_t t_41 = nile_Real (1);
            nile_Real_t t_42 = nile_Real_add(v.v_i, t_41);
            v_.v_i = t_42;
        }
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_SumWeightedColors_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_SumWeightedColors_vars_t *vars = nile_Process_vars (p);
    gezira_SumWeightedColors_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_SumWeightedColors (nile_Process_t *p, 
                          float v_n)
{
    gezira_SumWeightedColors_vars_t *vars;
    gezira_SumWeightedColors_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_SumWeightedColors_prologue, gezira_SumWeightedColors_body, gezira_SumWeightedColors_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_n = nile_Real (v_n);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_BilinearFilterPoints_vars_t;

static nile_Buffer_t *
gezira_BilinearFilterPoints_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterPoints_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilterPoints_body (nile_Process_t *p,
                                  nile_Buffer_t *in,
                                  nile_Buffer_t *out)
{
    gezira_BilinearFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterPoints_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_BilinearFilterPoints_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0.5);
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = nile_Real (0.5);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_9_x);
        nile_Buffer_push_tail(out, t_9_y);
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12 = nile_Real_add(v_x, t_11);
        nile_Real_t t_10_1 = t_12;
        nile_Real_t t_10_2 = v_y;
        nile_Real_t t_13_x = t_10_1;
        nile_Real_t t_13_y = t_10_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_13_x);
        nile_Buffer_push_tail(out, t_13_y);
        nile_Real_t t_15 = nile_Real (1);
        nile_Real_t t_16 = nile_Real_add(v_y, t_15);
        nile_Real_t t_14_1 = v_x;
        nile_Real_t t_14_2 = t_16;
        nile_Real_t t_17_x = t_14_1;
        nile_Real_t t_17_y = t_14_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_17_x);
        nile_Buffer_push_tail(out, t_17_y);
        nile_Real_t t_19 = nile_Real (1);
        nile_Real_t t_20 = nile_Real_add(v_x, t_19);
        nile_Real_t t_21 = nile_Real (1);
        nile_Real_t t_22 = nile_Real_add(v_y, t_21);
        nile_Real_t t_18_1 = t_20;
        nile_Real_t t_18_2 = t_22;
        nile_Real_t t_23_x = t_18_1;
        nile_Real_t t_23_y = t_18_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_23_x);
        nile_Buffer_push_tail(out, t_23_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilterPoints_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterPoints_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_BilinearFilterPoints (nile_Process_t *p)
{
    gezira_BilinearFilterPoints_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BilinearFilterPoints_prologue, gezira_BilinearFilterPoints_body, gezira_BilinearFilterPoints_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
} gezira_BilinearFilterWeights_vars_t;

static nile_Buffer_t *
gezira_BilinearFilterWeights_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterWeights_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilterWeights_body (nile_Process_t *p,
                                   nile_Buffer_t *in,
                                   nile_Buffer_t *out)
{
    gezira_BilinearFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterWeights_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_BilinearFilterWeights_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0.5);
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5_x = nile_Real_sub(v_P_x, t_4_x);
        nile_Real_t t_5_y = nile_Real_sub(v_P_y, t_4_y);
        nile_Real_t t_6 = nile_Real (0.5);
        nile_Real_t t_7_x = t_6;
        nile_Real_t t_7_y = t_6;
        nile_Real_t t_8_x = nile_Real_sub(t_5_x, t_7_x);
        nile_Real_t t_8_y = nile_Real_sub(t_5_y, t_7_y);
        nile_Real_t v_S_x = t_8_x;
        nile_Real_t v_S_y = t_8_y;
        nile_Real_t v_u = v_S_x;
        nile_Real_t v_v = v_S_y;
        nile_Real_t t_9 = nile_Real (1);
        nile_Real_t t_10 = nile_Real_sub(t_9, v_u);
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12 = nile_Real_sub(t_11, v_v);
        nile_Real_t t_13 = nile_Real_mul(t_10, t_12);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_13);
        nile_Real_t t_14 = nile_Real (1);
        nile_Real_t t_15 = nile_Real_sub(t_14, v_v);
        nile_Real_t t_16 = nile_Real_mul(v_u, t_15);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16);
        nile_Real_t t_17 = nile_Real (1);
        nile_Real_t t_18 = nile_Real_sub(t_17, v_u);
        nile_Real_t t_19 = nile_Real_mul(t_18, v_v);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_19);
        nile_Real_t t_20 = nile_Real_mul(v_u, v_v);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_20);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilterWeights_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilterWeights_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_BilinearFilterWeights (nile_Process_t *p)
{
    gezira_BilinearFilterWeights_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BilinearFilterWeights_prologue, gezira_BilinearFilterWeights_body, gezira_BilinearFilterWeights_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Process_t *v_t;
} gezira_BilinearFilter_vars_t;

static nile_Buffer_t *
gezira_BilinearFilter_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilter_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_BilinearFilterPoints(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_BilinearFilterWeights(p);
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (4);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilter_body (nile_Process_t *p,
                            nile_Buffer_t *in,
                            nile_Buffer_t *out)
{
    gezira_BilinearFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilter_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_BilinearFilter_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BilinearFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BilinearFilter_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_BilinearFilter (nile_Process_t *p, 
                       nile_Process_t *v_t)
{
    gezira_BilinearFilter_vars_t *vars;
    gezira_BilinearFilter_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BilinearFilter_prologue, gezira_BilinearFilter_body, gezira_BilinearFilter_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_BicubicFilterPoints_vars_t;

static nile_Buffer_t *
gezira_BicubicFilterPoints_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterPoints_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterPoints_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_BicubicFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterPoints_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_BicubicFilterPoints_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0.5);
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = nile_Real (0.5);
        nile_Real_t t_6_x = t_5;
        nile_Real_t t_6_y = t_5;
        nile_Real_t t_7_x = nile_Real_add(t_4_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_add(t_4_y, t_6_y);
        nile_Real_t v_S_x = t_7_x;
        nile_Real_t v_S_y = t_7_y;
        nile_Real_t v_x = v_S_x;
        nile_Real_t v_y = v_S_y;
        nile_Real_t t_9 = nile_Real (1);
        nile_Real_t t_10 = nile_Real_sub(v_x, t_9);
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12 = nile_Real_sub(v_y, t_11);
        nile_Real_t t_8_1 = t_10;
        nile_Real_t t_8_2 = t_12;
        nile_Real_t t_13_x = t_8_1;
        nile_Real_t t_13_y = t_8_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_13_x);
        nile_Buffer_push_tail(out, t_13_y);
        nile_Real_t t_15 = nile_Real (1);
        nile_Real_t t_16 = nile_Real_sub(v_y, t_15);
        nile_Real_t t_14_1 = v_x;
        nile_Real_t t_14_2 = t_16;
        nile_Real_t t_17_x = t_14_1;
        nile_Real_t t_17_y = t_14_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_17_x);
        nile_Buffer_push_tail(out, t_17_y);
        nile_Real_t t_19 = nile_Real (1);
        nile_Real_t t_20 = nile_Real_add(v_x, t_19);
        nile_Real_t t_21 = nile_Real (1);
        nile_Real_t t_22 = nile_Real_sub(v_y, t_21);
        nile_Real_t t_18_1 = t_20;
        nile_Real_t t_18_2 = t_22;
        nile_Real_t t_23_x = t_18_1;
        nile_Real_t t_23_y = t_18_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_23_x);
        nile_Buffer_push_tail(out, t_23_y);
        nile_Real_t t_25 = nile_Real (2);
        nile_Real_t t_26 = nile_Real_add(v_x, t_25);
        nile_Real_t t_27 = nile_Real (1);
        nile_Real_t t_28 = nile_Real_sub(v_y, t_27);
        nile_Real_t t_24_1 = t_26;
        nile_Real_t t_24_2 = t_28;
        nile_Real_t t_29_x = t_24_1;
        nile_Real_t t_29_y = t_24_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_29_x);
        nile_Buffer_push_tail(out, t_29_y);
        nile_Real_t t_31 = nile_Real (1);
        nile_Real_t t_32 = nile_Real_sub(v_x, t_31);
        nile_Real_t t_30_1 = t_32;
        nile_Real_t t_30_2 = v_y;
        nile_Real_t t_33_x = t_30_1;
        nile_Real_t t_33_y = t_30_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_33_x);
        nile_Buffer_push_tail(out, t_33_y);
        nile_Real_t t_34_1 = v_x;
        nile_Real_t t_34_2 = v_y;
        nile_Real_t t_35_x = t_34_1;
        nile_Real_t t_35_y = t_34_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_35_x);
        nile_Buffer_push_tail(out, t_35_y);
        nile_Real_t t_37 = nile_Real (1);
        nile_Real_t t_38 = nile_Real_add(v_x, t_37);
        nile_Real_t t_36_1 = t_38;
        nile_Real_t t_36_2 = v_y;
        nile_Real_t t_39_x = t_36_1;
        nile_Real_t t_39_y = t_36_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_39_x);
        nile_Buffer_push_tail(out, t_39_y);
        nile_Real_t t_41 = nile_Real (2);
        nile_Real_t t_42 = nile_Real_add(v_x, t_41);
        nile_Real_t t_40_1 = t_42;
        nile_Real_t t_40_2 = v_y;
        nile_Real_t t_43_x = t_40_1;
        nile_Real_t t_43_y = t_40_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_43_x);
        nile_Buffer_push_tail(out, t_43_y);
        nile_Real_t t_45 = nile_Real (1);
        nile_Real_t t_46 = nile_Real_sub(v_x, t_45);
        nile_Real_t t_47 = nile_Real (1);
        nile_Real_t t_48 = nile_Real_add(v_y, t_47);
        nile_Real_t t_44_1 = t_46;
        nile_Real_t t_44_2 = t_48;
        nile_Real_t t_49_x = t_44_1;
        nile_Real_t t_49_y = t_44_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_49_x);
        nile_Buffer_push_tail(out, t_49_y);
        nile_Real_t t_51 = nile_Real (1);
        nile_Real_t t_52 = nile_Real_add(v_y, t_51);
        nile_Real_t t_50_1 = v_x;
        nile_Real_t t_50_2 = t_52;
        nile_Real_t t_53_x = t_50_1;
        nile_Real_t t_53_y = t_50_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_53_x);
        nile_Buffer_push_tail(out, t_53_y);
        nile_Real_t t_55 = nile_Real (1);
        nile_Real_t t_56 = nile_Real_add(v_x, t_55);
        nile_Real_t t_57 = nile_Real (1);
        nile_Real_t t_58 = nile_Real_add(v_y, t_57);
        nile_Real_t t_54_1 = t_56;
        nile_Real_t t_54_2 = t_58;
        nile_Real_t t_59_x = t_54_1;
        nile_Real_t t_59_y = t_54_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_59_x);
        nile_Buffer_push_tail(out, t_59_y);
        nile_Real_t t_61 = nile_Real (2);
        nile_Real_t t_62 = nile_Real_add(v_x, t_61);
        nile_Real_t t_63 = nile_Real (1);
        nile_Real_t t_64 = nile_Real_add(v_y, t_63);
        nile_Real_t t_60_1 = t_62;
        nile_Real_t t_60_2 = t_64;
        nile_Real_t t_65_x = t_60_1;
        nile_Real_t t_65_y = t_60_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_65_x);
        nile_Buffer_push_tail(out, t_65_y);
        nile_Real_t t_67 = nile_Real (1);
        nile_Real_t t_68 = nile_Real_sub(v_x, t_67);
        nile_Real_t t_69 = nile_Real (2);
        nile_Real_t t_70 = nile_Real_add(v_y, t_69);
        nile_Real_t t_66_1 = t_68;
        nile_Real_t t_66_2 = t_70;
        nile_Real_t t_71_x = t_66_1;
        nile_Real_t t_71_y = t_66_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_71_x);
        nile_Buffer_push_tail(out, t_71_y);
        nile_Real_t t_73 = nile_Real (2);
        nile_Real_t t_74 = nile_Real_add(v_y, t_73);
        nile_Real_t t_72_1 = v_x;
        nile_Real_t t_72_2 = t_74;
        nile_Real_t t_75_x = t_72_1;
        nile_Real_t t_75_y = t_72_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_75_x);
        nile_Buffer_push_tail(out, t_75_y);
        nile_Real_t t_77 = nile_Real (1);
        nile_Real_t t_78 = nile_Real_add(v_x, t_77);
        nile_Real_t t_79 = nile_Real (2);
        nile_Real_t t_80 = nile_Real_add(v_y, t_79);
        nile_Real_t t_76_1 = t_78;
        nile_Real_t t_76_2 = t_80;
        nile_Real_t t_81_x = t_76_1;
        nile_Real_t t_81_y = t_76_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_81_x);
        nile_Buffer_push_tail(out, t_81_y);
        nile_Real_t t_83 = nile_Real (2);
        nile_Real_t t_84 = nile_Real_add(v_x, t_83);
        nile_Real_t t_85 = nile_Real (2);
        nile_Real_t t_86 = nile_Real_add(v_y, t_85);
        nile_Real_t t_82_1 = t_84;
        nile_Real_t t_82_2 = t_86;
        nile_Real_t t_87_x = t_82_1;
        nile_Real_t t_87_y = t_82_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_87_x);
        nile_Buffer_push_tail(out, t_87_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterPoints_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterPoints_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterPoints_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_BicubicFilterPoints (nile_Process_t *p)
{
    gezira_BicubicFilterPoints_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BicubicFilterPoints_prologue, gezira_BicubicFilterPoints_body, gezira_BicubicFilterPoints_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_BicubicFilterDeltas_vars_t;

static nile_Buffer_t *
gezira_BicubicFilterDeltas_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterDeltas_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterDeltas_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterDeltas_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_BicubicFilterDeltas_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterDeltas_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_BicubicFilterDeltas_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0.5);
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3_x = nile_Real_sub(v_P_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_P_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_flr(t_3_x);
        nile_Real_t t_4_y = nile_Real_flr(t_3_y);
        nile_Real_t t_5 = nile_Real (0.5);
        nile_Real_t t_6_x = t_5;
        nile_Real_t t_6_y = t_5;
        nile_Real_t t_7_x = nile_Real_add(t_4_x, t_6_x);
        nile_Real_t t_7_y = nile_Real_add(t_4_y, t_6_y);
        nile_Real_t v_S_x = t_7_x;
        nile_Real_t v_S_y = t_7_y;
        nile_Real_t v_x = v_S_x;
        nile_Real_t v_y = v_S_y;
        nile_Real_t t_9 = nile_Real (1);
        nile_Real_t t_10 = nile_Real_sub(v_x, t_9);
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12 = nile_Real_sub(v_y, t_11);
        nile_Real_t t_8_1 = t_10;
        nile_Real_t t_8_2 = t_12;
        nile_Real_t t_13_x = t_8_1;
        nile_Real_t t_13_y = t_8_2;
        nile_Real_t t_14_x = nile_Real_sub(t_13_x, v_P_x);
        nile_Real_t t_14_y = nile_Real_sub(t_13_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_14_x);
        nile_Buffer_push_tail(out, t_14_y);
        nile_Real_t t_16 = nile_Real (1);
        nile_Real_t t_17 = nile_Real_sub(v_y, t_16);
        nile_Real_t t_15_1 = v_x;
        nile_Real_t t_15_2 = t_17;
        nile_Real_t t_18_x = t_15_1;
        nile_Real_t t_18_y = t_15_2;
        nile_Real_t t_19_x = nile_Real_sub(t_18_x, v_P_x);
        nile_Real_t t_19_y = nile_Real_sub(t_18_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_19_x);
        nile_Buffer_push_tail(out, t_19_y);
        nile_Real_t t_21 = nile_Real (1);
        nile_Real_t t_22 = nile_Real_add(v_x, t_21);
        nile_Real_t t_23 = nile_Real (1);
        nile_Real_t t_24 = nile_Real_sub(v_y, t_23);
        nile_Real_t t_20_1 = t_22;
        nile_Real_t t_20_2 = t_24;
        nile_Real_t t_25_x = t_20_1;
        nile_Real_t t_25_y = t_20_2;
        nile_Real_t t_26_x = nile_Real_sub(t_25_x, v_P_x);
        nile_Real_t t_26_y = nile_Real_sub(t_25_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_26_x);
        nile_Buffer_push_tail(out, t_26_y);
        nile_Real_t t_28 = nile_Real (2);
        nile_Real_t t_29 = nile_Real_add(v_x, t_28);
        nile_Real_t t_30 = nile_Real (1);
        nile_Real_t t_31 = nile_Real_sub(v_y, t_30);
        nile_Real_t t_27_1 = t_29;
        nile_Real_t t_27_2 = t_31;
        nile_Real_t t_32_x = t_27_1;
        nile_Real_t t_32_y = t_27_2;
        nile_Real_t t_33_x = nile_Real_sub(t_32_x, v_P_x);
        nile_Real_t t_33_y = nile_Real_sub(t_32_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_33_x);
        nile_Buffer_push_tail(out, t_33_y);
        nile_Real_t t_35 = nile_Real (1);
        nile_Real_t t_36 = nile_Real_sub(v_x, t_35);
        nile_Real_t t_34_1 = t_36;
        nile_Real_t t_34_2 = v_y;
        nile_Real_t t_37_x = t_34_1;
        nile_Real_t t_37_y = t_34_2;
        nile_Real_t t_38_x = nile_Real_sub(t_37_x, v_P_x);
        nile_Real_t t_38_y = nile_Real_sub(t_37_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_38_x);
        nile_Buffer_push_tail(out, t_38_y);
        nile_Real_t t_39_1 = v_x;
        nile_Real_t t_39_2 = v_y;
        nile_Real_t t_40_x = t_39_1;
        nile_Real_t t_40_y = t_39_2;
        nile_Real_t t_41_x = nile_Real_sub(t_40_x, v_P_x);
        nile_Real_t t_41_y = nile_Real_sub(t_40_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_41_x);
        nile_Buffer_push_tail(out, t_41_y);
        nile_Real_t t_43 = nile_Real (1);
        nile_Real_t t_44 = nile_Real_add(v_x, t_43);
        nile_Real_t t_42_1 = t_44;
        nile_Real_t t_42_2 = v_y;
        nile_Real_t t_45_x = t_42_1;
        nile_Real_t t_45_y = t_42_2;
        nile_Real_t t_46_x = nile_Real_sub(t_45_x, v_P_x);
        nile_Real_t t_46_y = nile_Real_sub(t_45_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_46_x);
        nile_Buffer_push_tail(out, t_46_y);
        nile_Real_t t_48 = nile_Real (2);
        nile_Real_t t_49 = nile_Real_add(v_x, t_48);
        nile_Real_t t_47_1 = t_49;
        nile_Real_t t_47_2 = v_y;
        nile_Real_t t_50_x = t_47_1;
        nile_Real_t t_50_y = t_47_2;
        nile_Real_t t_51_x = nile_Real_sub(t_50_x, v_P_x);
        nile_Real_t t_51_y = nile_Real_sub(t_50_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_51_x);
        nile_Buffer_push_tail(out, t_51_y);
        nile_Real_t t_53 = nile_Real (1);
        nile_Real_t t_54 = nile_Real_sub(v_x, t_53);
        nile_Real_t t_55 = nile_Real (1);
        nile_Real_t t_56 = nile_Real_add(v_y, t_55);
        nile_Real_t t_52_1 = t_54;
        nile_Real_t t_52_2 = t_56;
        nile_Real_t t_57_x = t_52_1;
        nile_Real_t t_57_y = t_52_2;
        nile_Real_t t_58_x = nile_Real_sub(t_57_x, v_P_x);
        nile_Real_t t_58_y = nile_Real_sub(t_57_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_58_x);
        nile_Buffer_push_tail(out, t_58_y);
        nile_Real_t t_60 = nile_Real (1);
        nile_Real_t t_61 = nile_Real_add(v_y, t_60);
        nile_Real_t t_59_1 = v_x;
        nile_Real_t t_59_2 = t_61;
        nile_Real_t t_62_x = t_59_1;
        nile_Real_t t_62_y = t_59_2;
        nile_Real_t t_63_x = nile_Real_sub(t_62_x, v_P_x);
        nile_Real_t t_63_y = nile_Real_sub(t_62_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_63_x);
        nile_Buffer_push_tail(out, t_63_y);
        nile_Real_t t_65 = nile_Real (1);
        nile_Real_t t_66 = nile_Real_add(v_x, t_65);
        nile_Real_t t_67 = nile_Real (1);
        nile_Real_t t_68 = nile_Real_add(v_y, t_67);
        nile_Real_t t_64_1 = t_66;
        nile_Real_t t_64_2 = t_68;
        nile_Real_t t_69_x = t_64_1;
        nile_Real_t t_69_y = t_64_2;
        nile_Real_t t_70_x = nile_Real_sub(t_69_x, v_P_x);
        nile_Real_t t_70_y = nile_Real_sub(t_69_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_70_x);
        nile_Buffer_push_tail(out, t_70_y);
        nile_Real_t t_72 = nile_Real (2);
        nile_Real_t t_73 = nile_Real_add(v_x, t_72);
        nile_Real_t t_74 = nile_Real (1);
        nile_Real_t t_75 = nile_Real_add(v_y, t_74);
        nile_Real_t t_71_1 = t_73;
        nile_Real_t t_71_2 = t_75;
        nile_Real_t t_76_x = t_71_1;
        nile_Real_t t_76_y = t_71_2;
        nile_Real_t t_77_x = nile_Real_sub(t_76_x, v_P_x);
        nile_Real_t t_77_y = nile_Real_sub(t_76_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_77_x);
        nile_Buffer_push_tail(out, t_77_y);
        nile_Real_t t_79 = nile_Real (1);
        nile_Real_t t_80 = nile_Real_sub(v_x, t_79);
        nile_Real_t t_81 = nile_Real (2);
        nile_Real_t t_82 = nile_Real_add(v_y, t_81);
        nile_Real_t t_78_1 = t_80;
        nile_Real_t t_78_2 = t_82;
        nile_Real_t t_83_x = t_78_1;
        nile_Real_t t_83_y = t_78_2;
        nile_Real_t t_84_x = nile_Real_sub(t_83_x, v_P_x);
        nile_Real_t t_84_y = nile_Real_sub(t_83_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_84_x);
        nile_Buffer_push_tail(out, t_84_y);
        nile_Real_t t_86 = nile_Real (2);
        nile_Real_t t_87 = nile_Real_add(v_y, t_86);
        nile_Real_t t_85_1 = v_x;
        nile_Real_t t_85_2 = t_87;
        nile_Real_t t_88_x = t_85_1;
        nile_Real_t t_88_y = t_85_2;
        nile_Real_t t_89_x = nile_Real_sub(t_88_x, v_P_x);
        nile_Real_t t_89_y = nile_Real_sub(t_88_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_89_x);
        nile_Buffer_push_tail(out, t_89_y);
        nile_Real_t t_91 = nile_Real (1);
        nile_Real_t t_92 = nile_Real_add(v_x, t_91);
        nile_Real_t t_93 = nile_Real (2);
        nile_Real_t t_94 = nile_Real_add(v_y, t_93);
        nile_Real_t t_90_1 = t_92;
        nile_Real_t t_90_2 = t_94;
        nile_Real_t t_95_x = t_90_1;
        nile_Real_t t_95_y = t_90_2;
        nile_Real_t t_96_x = nile_Real_sub(t_95_x, v_P_x);
        nile_Real_t t_96_y = nile_Real_sub(t_95_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_96_x);
        nile_Buffer_push_tail(out, t_96_y);
        nile_Real_t t_98 = nile_Real (2);
        nile_Real_t t_99 = nile_Real_add(v_x, t_98);
        nile_Real_t t_100 = nile_Real (2);
        nile_Real_t t_101 = nile_Real_add(v_y, t_100);
        nile_Real_t t_97_1 = t_99;
        nile_Real_t t_97_2 = t_101;
        nile_Real_t t_102_x = t_97_1;
        nile_Real_t t_102_y = t_97_2;
        nile_Real_t t_103_x = nile_Real_sub(t_102_x, v_P_x);
        nile_Real_t t_103_y = nile_Real_sub(t_102_y, v_P_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_103_x);
        nile_Buffer_push_tail(out, t_103_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterDeltas_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterDeltas_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterDeltas_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_BicubicFilterDeltas (nile_Process_t *p)
{
    gezira_BicubicFilterDeltas_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BicubicFilterDeltas_prologue, gezira_BicubicFilterDeltas_body, gezira_BicubicFilterDeltas_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
} gezira_BicubicFilterWeights_vars_t;

static nile_Buffer_t *
gezira_BicubicFilterWeights_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterWeights_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterWeights_body (nile_Process_t *p,
                                  nile_Buffer_t *in,
                                  nile_Buffer_t *out)
{
    gezira_BicubicFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterWeights_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_BicubicFilterWeights_vars_t v_ = v;
        nile_Real_t v_D_x = nile_Buffer_pop_head(in);
        nile_Real_t v_D_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0);
        nile_Real_t t_2 = nile_Real_lt(v_D_x, t_1);
        nile_Real_t t_3 = nile_Real_neg(v_D_x);
        nile_Real_t t_4 = nile_Real_nz (t_2) ? t_3 : v_D_x;
        nile_Real_t t_5 = nile_Real (0);
        nile_Real_t t_6 = nile_Real_lt(v_D_y, t_5);
        nile_Real_t t_7 = nile_Real_neg(v_D_y);
        nile_Real_t t_8 = nile_Real_nz (t_6) ? t_7 : v_D_y;
        nile_Real_t t_9_1 = t_4;
        nile_Real_t t_9_2 = t_8;
        nile_Real_t t_10_x = t_9_1;
        nile_Real_t t_10_y = t_9_2;
        nile_Real_t v_T_x = t_10_x;
        nile_Real_t v_T_y = t_10_y;
        nile_Real_t t_11 = nile_Real (1);
        nile_Real_t t_12_x = t_11;
        nile_Real_t t_12_y = t_11;
        nile_Real_t t_13_x = nile_Real_lt(v_T_x, t_12_x);
        nile_Real_t t_13_y = nile_Real_lt(v_T_y, t_12_y);
        nile_Real_t t_14 = nile_Real (1.5);
        nile_Real_t t_15_x = t_14;
        nile_Real_t t_15_y = t_14;
        nile_Real_t t_16_x = nile_Real_mul(t_15_x, v_T_x);
        nile_Real_t t_16_y = nile_Real_mul(t_15_y, v_T_y);
        nile_Real_t t_17_x = nile_Real_mul(t_16_x, v_T_x);
        nile_Real_t t_17_y = nile_Real_mul(t_16_y, v_T_y);
        nile_Real_t t_18_x = nile_Real_mul(t_17_x, v_T_x);
        nile_Real_t t_18_y = nile_Real_mul(t_17_y, v_T_y);
        nile_Real_t t_19 = nile_Real (2.5);
        nile_Real_t t_20_x = t_19;
        nile_Real_t t_20_y = t_19;
        nile_Real_t t_21_x = nile_Real_mul(t_20_x, v_T_x);
        nile_Real_t t_21_y = nile_Real_mul(t_20_y, v_T_y);
        nile_Real_t t_22_x = nile_Real_mul(t_21_x, v_T_x);
        nile_Real_t t_22_y = nile_Real_mul(t_21_y, v_T_y);
        nile_Real_t t_23_x = nile_Real_sub(t_18_x, t_22_x);
        nile_Real_t t_23_y = nile_Real_sub(t_18_y, t_22_y);
        nile_Real_t t_24 = nile_Real (1);
        nile_Real_t t_25_x = t_24;
        nile_Real_t t_25_y = t_24;
        nile_Real_t t_26_x = nile_Real_add(t_23_x, t_25_x);
        nile_Real_t t_26_y = nile_Real_add(t_23_y, t_25_y);
        nile_Real_t t_27 = nile_Real (2);
        nile_Real_t t_28_x = t_27;
        nile_Real_t t_28_y = t_27;
        nile_Real_t t_29_x = nile_Real_lt(v_T_x, t_28_x);
        nile_Real_t t_29_y = nile_Real_lt(v_T_y, t_28_y);
        nile_Real_t t_30 = nile_Real (0.5);
        nile_Real_t t_31 = nile_Real_neg(t_30);
        nile_Real_t t_32_x = t_31;
        nile_Real_t t_32_y = t_31;
        nile_Real_t t_33_x = nile_Real_mul(t_32_x, v_T_x);
        nile_Real_t t_33_y = nile_Real_mul(t_32_y, v_T_y);
        nile_Real_t t_34_x = nile_Real_mul(t_33_x, v_T_x);
        nile_Real_t t_34_y = nile_Real_mul(t_33_y, v_T_y);
        nile_Real_t t_35_x = nile_Real_mul(t_34_x, v_T_x);
        nile_Real_t t_35_y = nile_Real_mul(t_34_y, v_T_y);
        nile_Real_t t_36 = nile_Real (2.5);
        nile_Real_t t_37_x = t_36;
        nile_Real_t t_37_y = t_36;
        nile_Real_t t_38_x = nile_Real_mul(t_37_x, v_T_x);
        nile_Real_t t_38_y = nile_Real_mul(t_37_y, v_T_y);
        nile_Real_t t_39_x = nile_Real_mul(t_38_x, v_T_x);
        nile_Real_t t_39_y = nile_Real_mul(t_38_y, v_T_y);
        nile_Real_t t_40_x = nile_Real_add(t_35_x, t_39_x);
        nile_Real_t t_40_y = nile_Real_add(t_35_y, t_39_y);
        nile_Real_t t_41 = nile_Real (4);
        nile_Real_t t_42_x = t_41;
        nile_Real_t t_42_y = t_41;
        nile_Real_t t_43_x = nile_Real_mul(t_42_x, v_T_x);
        nile_Real_t t_43_y = nile_Real_mul(t_42_y, v_T_y);
        nile_Real_t t_44_x = nile_Real_sub(t_40_x, t_43_x);
        nile_Real_t t_44_y = nile_Real_sub(t_40_y, t_43_y);
        nile_Real_t t_45 = nile_Real (2);
        nile_Real_t t_46_x = t_45;
        nile_Real_t t_46_y = t_45;
        nile_Real_t t_47_x = nile_Real_add(t_44_x, t_46_x);
        nile_Real_t t_47_y = nile_Real_add(t_44_y, t_46_y);
        nile_Real_t t_48 = nile_Real (0);
        nile_Real_t t_49_x = t_48;
        nile_Real_t t_49_y = t_48;
        nile_Real_t t_50_x = nile_Real_nz (t_29_x) ? t_47_x : t_49_x;
        nile_Real_t t_50_y = nile_Real_nz (t_29_y) ? t_47_y : t_49_y;
        nile_Real_t t_51_x = nile_Real_nz (t_13_x) ? t_26_x : t_50_x;
        nile_Real_t t_51_y = nile_Real_nz (t_13_y) ? t_26_y : t_50_y;
        nile_Real_t v_S_x = t_51_x;
        nile_Real_t v_S_y = t_51_y;
        nile_Real_t t_52 = nile_Real_mul(v_S_x, v_S_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_52);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilterWeights_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilterWeights_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilterWeights_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_BicubicFilterWeights (nile_Process_t *p)
{
    gezira_BicubicFilterWeights_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BicubicFilterWeights_prologue, gezira_BicubicFilterWeights_body, gezira_BicubicFilterWeights_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Process_t *v_t;
} gezira_BicubicFilter_vars_t;

static nile_Buffer_t *
gezira_BicubicFilter_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilter_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_BicubicFilterPoints(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = nile_Process_pipe (gezira_BicubicFilterDeltas(p), gezira_BicubicFilterWeights(p), NILE_NULL);
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (16);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilter_body (nile_Process_t *p,
                           nile_Buffer_t *in,
                           nile_Buffer_t *out)
{
    gezira_BicubicFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilter_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_BicubicFilter_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_BicubicFilter_vars_t *vars = nile_Process_vars (p);
    gezira_BicubicFilter_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_BicubicFilter (nile_Process_t *p, 
                      nile_Process_t *v_t)
{
    gezira_BicubicFilter_vars_t *vars;
    gezira_BicubicFilter_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_BicubicFilter_prologue, gezira_BicubicFilter_body, gezira_BicubicFilter_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur5x1Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur5x1Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1Points_body (nile_Process_t *p,
                                   nile_Buffer_t *in,
                                   nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur5x1Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (2);
        nile_Real_t t_3 = nile_Real_sub(v_x, t_2);
        nile_Real_t t_1_1 = t_3;
        nile_Real_t t_1_2 = v_y;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (1);
        nile_Real_t t_7 = nile_Real_sub(v_x, t_6);
        nile_Real_t t_5_1 = t_7;
        nile_Real_t t_5_2 = v_y;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_9_1 = v_x;
        nile_Real_t t_9_2 = v_y;
        nile_Real_t t_10_x = t_9_1;
        nile_Real_t t_10_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_10_x);
        nile_Buffer_push_tail(out, t_10_y);
        nile_Real_t t_12 = nile_Real (1);
        nile_Real_t t_13 = nile_Real_add(v_x, t_12);
        nile_Real_t t_11_1 = t_13;
        nile_Real_t t_11_2 = v_y;
        nile_Real_t t_14_x = t_11_1;
        nile_Real_t t_14_y = t_11_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_14_x);
        nile_Buffer_push_tail(out, t_14_y);
        nile_Real_t t_16 = nile_Real (2);
        nile_Real_t t_17 = nile_Real_add(v_x, t_16);
        nile_Real_t t_15_1 = t_17;
        nile_Real_t t_15_2 = v_y;
        nile_Real_t t_18_x = t_15_1;
        nile_Real_t t_18_y = t_15_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_18_x);
        nile_Buffer_push_tail(out, t_18_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur5x1Points (nile_Process_t *p)
{
    gezira_GaussianBlur5x1Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur5x1Points_prologue, gezira_GaussianBlur5x1Points_body, gezira_GaussianBlur5x1Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur1x5Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x5Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x5Points_body (nile_Process_t *p,
                                   nile_Buffer_t *in,
                                   nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur1x5Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (2);
        nile_Real_t t_3 = nile_Real_sub(v_y, t_2);
        nile_Real_t t_1_1 = v_x;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (1);
        nile_Real_t t_7 = nile_Real_sub(v_y, t_6);
        nile_Real_t t_5_1 = v_x;
        nile_Real_t t_5_2 = t_7;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_9_1 = v_x;
        nile_Real_t t_9_2 = v_y;
        nile_Real_t t_10_x = t_9_1;
        nile_Real_t t_10_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_10_x);
        nile_Buffer_push_tail(out, t_10_y);
        nile_Real_t t_12 = nile_Real (1);
        nile_Real_t t_13 = nile_Real_add(v_y, t_12);
        nile_Real_t t_11_1 = v_x;
        nile_Real_t t_11_2 = t_13;
        nile_Real_t t_14_x = t_11_1;
        nile_Real_t t_14_y = t_11_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_14_x);
        nile_Buffer_push_tail(out, t_14_y);
        nile_Real_t t_16 = nile_Real (2);
        nile_Real_t t_17 = nile_Real_add(v_y, t_16);
        nile_Real_t t_15_1 = v_x;
        nile_Real_t t_15_2 = t_17;
        nile_Real_t t_18_x = t_15_1;
        nile_Real_t t_18_y = t_15_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_18_x);
        nile_Buffer_push_tail(out, t_18_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x5Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x5Points (nile_Process_t *p)
{
    gezira_GaussianBlur1x5Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x5Points_prologue, gezira_GaussianBlur1x5Points_body, gezira_GaussianBlur1x5Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
    nile_Real_t v_f;
    nile_Real_t v_a;
    nile_Real_t v_s;
} gezira_GaussianBlur5x1Weights_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur5x1Weights_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Weights_vars_t v = *vars;
    nile_Real_t t_7 = nile_Real (16);
    nile_Real_t t_8 = nile_Real_mul(t_7, v.v_f);
    v.v_a = t_8;
    nile_Real_t t_9 = nile_Real (16);
    nile_Real_t t_10 = nile_Real (5);
    nile_Real_t t_11 = nile_Real_mul(t_10, v.v_a);
    nile_Real_t t_12 = nile_Real_add(t_9, t_11);
    v.v_s = t_12;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1Weights_body (nile_Process_t *p,
                                    nile_Buffer_t *in,
                                    nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Weights_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur5x1Weights_vars_t v_ = v;
        nile_Real_t t_13_x;
        nile_Real_t t_13_y;
        t_13_x = nile_Buffer_pop_head(in);
        t_13_y = nile_Buffer_pop_head(in);
        nile_Real_t t_14 = nile_Real (1);
        nile_Real_t t_15 = nile_Real_add(v.v_a, t_14);
        nile_Real_t t_16 = nile_Real_div(t_15, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16);
        nile_Real_t t_17 = nile_Real (4);
        nile_Real_t t_18 = nile_Real_add(v.v_a, t_17);
        nile_Real_t t_19 = nile_Real_div(t_18, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_19);
        nile_Real_t t_20 = nile_Real (6);
        nile_Real_t t_21 = nile_Real_add(v.v_a, t_20);
        nile_Real_t t_22 = nile_Real_div(t_21, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_22);
        nile_Real_t t_23 = nile_Real (4);
        nile_Real_t t_24 = nile_Real_add(v.v_a, t_23);
        nile_Real_t t_25 = nile_Real_div(t_24, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_25);
        nile_Real_t t_26 = nile_Real (1);
        nile_Real_t t_27 = nile_Real_add(v.v_a, t_26);
        nile_Real_t t_28 = nile_Real_div(t_27, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_28);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1Weights_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1Weights_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur5x1Weights (nile_Process_t *p, 
                               float v_f)
{
    gezira_GaussianBlur5x1Weights_vars_t *vars;
    gezira_GaussianBlur5x1Weights_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur5x1Weights_prologue, gezira_GaussianBlur5x1Weights_body, gezira_GaussianBlur5x1Weights_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur5x1_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur5x1_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur5x1Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur5x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (5);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur5x1_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur5x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur5x1_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur5x1 (nile_Process_t *p, 
                        float v_f, 
                        nile_Process_t *v_t)
{
    gezira_GaussianBlur5x1_vars_t *vars;
    gezira_GaussianBlur5x1_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur5x1_prologue, gezira_GaussianBlur5x1_body, gezira_GaussianBlur5x1_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur1x5_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x5_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur1x5Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur5x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (5);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x5_body (nile_Process_t *p,
                             nile_Buffer_t *in,
                             nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x5_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x5_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x5_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x5 (nile_Process_t *p, 
                        float v_f, 
                        nile_Process_t *v_t)
{
    gezira_GaussianBlur1x5_vars_t *vars;
    gezira_GaussianBlur1x5_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x5_prologue, gezira_GaussianBlur1x5_body, gezira_GaussianBlur1x5_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur11x1Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur11x1Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1Points_body (nile_Process_t *p,
                                    nile_Buffer_t *in,
                                    nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur11x1Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (5);
        nile_Real_t t_3 = nile_Real_sub(v_x, t_2);
        nile_Real_t t_1_1 = t_3;
        nile_Real_t t_1_2 = v_y;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (4);
        nile_Real_t t_7 = nile_Real_sub(v_x, t_6);
        nile_Real_t t_5_1 = t_7;
        nile_Real_t t_5_2 = v_y;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_10 = nile_Real (3);
        nile_Real_t t_11 = nile_Real_sub(v_x, t_10);
        nile_Real_t t_9_1 = t_11;
        nile_Real_t t_9_2 = v_y;
        nile_Real_t t_12_x = t_9_1;
        nile_Real_t t_12_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_12_x);
        nile_Buffer_push_tail(out, t_12_y);
        nile_Real_t t_14 = nile_Real (2);
        nile_Real_t t_15 = nile_Real_sub(v_x, t_14);
        nile_Real_t t_13_1 = t_15;
        nile_Real_t t_13_2 = v_y;
        nile_Real_t t_16_x = t_13_1;
        nile_Real_t t_16_y = t_13_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16_x);
        nile_Buffer_push_tail(out, t_16_y);
        nile_Real_t t_18 = nile_Real (1);
        nile_Real_t t_19 = nile_Real_sub(v_x, t_18);
        nile_Real_t t_17_1 = t_19;
        nile_Real_t t_17_2 = v_y;
        nile_Real_t t_20_x = t_17_1;
        nile_Real_t t_20_y = t_17_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_20_x);
        nile_Buffer_push_tail(out, t_20_y);
        nile_Real_t t_21_1 = v_x;
        nile_Real_t t_21_2 = v_y;
        nile_Real_t t_22_x = t_21_1;
        nile_Real_t t_22_y = t_21_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_22_x);
        nile_Buffer_push_tail(out, t_22_y);
        nile_Real_t t_24 = nile_Real (1);
        nile_Real_t t_25 = nile_Real_add(v_x, t_24);
        nile_Real_t t_23_1 = t_25;
        nile_Real_t t_23_2 = v_y;
        nile_Real_t t_26_x = t_23_1;
        nile_Real_t t_26_y = t_23_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_26_x);
        nile_Buffer_push_tail(out, t_26_y);
        nile_Real_t t_28 = nile_Real (2);
        nile_Real_t t_29 = nile_Real_add(v_x, t_28);
        nile_Real_t t_27_1 = t_29;
        nile_Real_t t_27_2 = v_y;
        nile_Real_t t_30_x = t_27_1;
        nile_Real_t t_30_y = t_27_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_30_x);
        nile_Buffer_push_tail(out, t_30_y);
        nile_Real_t t_32 = nile_Real (3);
        nile_Real_t t_33 = nile_Real_add(v_x, t_32);
        nile_Real_t t_31_1 = t_33;
        nile_Real_t t_31_2 = v_y;
        nile_Real_t t_34_x = t_31_1;
        nile_Real_t t_34_y = t_31_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_34_x);
        nile_Buffer_push_tail(out, t_34_y);
        nile_Real_t t_36 = nile_Real (4);
        nile_Real_t t_37 = nile_Real_add(v_x, t_36);
        nile_Real_t t_35_1 = t_37;
        nile_Real_t t_35_2 = v_y;
        nile_Real_t t_38_x = t_35_1;
        nile_Real_t t_38_y = t_35_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_38_x);
        nile_Buffer_push_tail(out, t_38_y);
        nile_Real_t t_40 = nile_Real (5);
        nile_Real_t t_41 = nile_Real_add(v_x, t_40);
        nile_Real_t t_39_1 = t_41;
        nile_Real_t t_39_2 = v_y;
        nile_Real_t t_42_x = t_39_1;
        nile_Real_t t_42_y = t_39_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_42_x);
        nile_Buffer_push_tail(out, t_42_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur11x1Points (nile_Process_t *p)
{
    gezira_GaussianBlur11x1Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur11x1Points_prologue, gezira_GaussianBlur11x1Points_body, gezira_GaussianBlur11x1Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur1x11Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x11Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x11Points_body (nile_Process_t *p,
                                    nile_Buffer_t *in,
                                    nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur1x11Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (5);
        nile_Real_t t_3 = nile_Real_sub(v_y, t_2);
        nile_Real_t t_1_1 = v_x;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (4);
        nile_Real_t t_7 = nile_Real_sub(v_y, t_6);
        nile_Real_t t_5_1 = v_x;
        nile_Real_t t_5_2 = t_7;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_10 = nile_Real (3);
        nile_Real_t t_11 = nile_Real_sub(v_y, t_10);
        nile_Real_t t_9_1 = v_x;
        nile_Real_t t_9_2 = t_11;
        nile_Real_t t_12_x = t_9_1;
        nile_Real_t t_12_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_12_x);
        nile_Buffer_push_tail(out, t_12_y);
        nile_Real_t t_14 = nile_Real (2);
        nile_Real_t t_15 = nile_Real_sub(v_y, t_14);
        nile_Real_t t_13_1 = v_x;
        nile_Real_t t_13_2 = t_15;
        nile_Real_t t_16_x = t_13_1;
        nile_Real_t t_16_y = t_13_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16_x);
        nile_Buffer_push_tail(out, t_16_y);
        nile_Real_t t_18 = nile_Real (1);
        nile_Real_t t_19 = nile_Real_sub(v_y, t_18);
        nile_Real_t t_17_1 = v_x;
        nile_Real_t t_17_2 = t_19;
        nile_Real_t t_20_x = t_17_1;
        nile_Real_t t_20_y = t_17_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_20_x);
        nile_Buffer_push_tail(out, t_20_y);
        nile_Real_t t_21_1 = v_x;
        nile_Real_t t_21_2 = v_y;
        nile_Real_t t_22_x = t_21_1;
        nile_Real_t t_22_y = t_21_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_22_x);
        nile_Buffer_push_tail(out, t_22_y);
        nile_Real_t t_24 = nile_Real (1);
        nile_Real_t t_25 = nile_Real_add(v_y, t_24);
        nile_Real_t t_23_1 = v_x;
        nile_Real_t t_23_2 = t_25;
        nile_Real_t t_26_x = t_23_1;
        nile_Real_t t_26_y = t_23_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_26_x);
        nile_Buffer_push_tail(out, t_26_y);
        nile_Real_t t_28 = nile_Real (2);
        nile_Real_t t_29 = nile_Real_add(v_y, t_28);
        nile_Real_t t_27_1 = v_x;
        nile_Real_t t_27_2 = t_29;
        nile_Real_t t_30_x = t_27_1;
        nile_Real_t t_30_y = t_27_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_30_x);
        nile_Buffer_push_tail(out, t_30_y);
        nile_Real_t t_32 = nile_Real (3);
        nile_Real_t t_33 = nile_Real_add(v_y, t_32);
        nile_Real_t t_31_1 = v_x;
        nile_Real_t t_31_2 = t_33;
        nile_Real_t t_34_x = t_31_1;
        nile_Real_t t_34_y = t_31_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_34_x);
        nile_Buffer_push_tail(out, t_34_y);
        nile_Real_t t_36 = nile_Real (4);
        nile_Real_t t_37 = nile_Real_add(v_y, t_36);
        nile_Real_t t_35_1 = v_x;
        nile_Real_t t_35_2 = t_37;
        nile_Real_t t_38_x = t_35_1;
        nile_Real_t t_38_y = t_35_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_38_x);
        nile_Buffer_push_tail(out, t_38_y);
        nile_Real_t t_40 = nile_Real (5);
        nile_Real_t t_41 = nile_Real_add(v_y, t_40);
        nile_Real_t t_39_1 = v_x;
        nile_Real_t t_39_2 = t_41;
        nile_Real_t t_42_x = t_39_1;
        nile_Real_t t_42_y = t_39_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_42_x);
        nile_Buffer_push_tail(out, t_42_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x11Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x11Points (nile_Process_t *p)
{
    gezira_GaussianBlur1x11Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x11Points_prologue, gezira_GaussianBlur1x11Points_body, gezira_GaussianBlur1x11Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
    nile_Real_t v_f;
    nile_Real_t v_a;
    nile_Real_t v_s;
} gezira_GaussianBlur11x1Weights_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur11x1Weights_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Weights_vars_t v = *vars;
    nile_Real_t t_7 = nile_Real (1024);
    nile_Real_t t_8 = nile_Real_mul(t_7, v.v_f);
    v.v_a = t_8;
    nile_Real_t t_9 = nile_Real (1024);
    nile_Real_t t_10 = nile_Real (11);
    nile_Real_t t_11 = nile_Real_mul(t_10, v.v_a);
    nile_Real_t t_12 = nile_Real_add(t_9, t_11);
    v.v_s = t_12;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1Weights_body (nile_Process_t *p,
                                     nile_Buffer_t *in,
                                     nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Weights_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur11x1Weights_vars_t v_ = v;
        nile_Real_t t_13_x;
        nile_Real_t t_13_y;
        t_13_x = nile_Buffer_pop_head(in);
        t_13_y = nile_Buffer_pop_head(in);
        nile_Real_t t_14 = nile_Real (1);
        nile_Real_t t_15 = nile_Real_add(v.v_a, t_14);
        nile_Real_t t_16 = nile_Real_div(t_15, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16);
        nile_Real_t t_17 = nile_Real (10);
        nile_Real_t t_18 = nile_Real_add(v.v_a, t_17);
        nile_Real_t t_19 = nile_Real_div(t_18, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_19);
        nile_Real_t t_20 = nile_Real (45);
        nile_Real_t t_21 = nile_Real_add(v.v_a, t_20);
        nile_Real_t t_22 = nile_Real_div(t_21, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_22);
        nile_Real_t t_23 = nile_Real (120);
        nile_Real_t t_24 = nile_Real_add(v.v_a, t_23);
        nile_Real_t t_25 = nile_Real_div(t_24, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_25);
        nile_Real_t t_26 = nile_Real (210);
        nile_Real_t t_27 = nile_Real_add(v.v_a, t_26);
        nile_Real_t t_28 = nile_Real_div(t_27, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_28);
        nile_Real_t t_29 = nile_Real (252);
        nile_Real_t t_30 = nile_Real_add(v.v_a, t_29);
        nile_Real_t t_31 = nile_Real_div(t_30, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_31);
        nile_Real_t t_32 = nile_Real (210);
        nile_Real_t t_33 = nile_Real_add(v.v_a, t_32);
        nile_Real_t t_34 = nile_Real_div(t_33, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_34);
        nile_Real_t t_35 = nile_Real (120);
        nile_Real_t t_36 = nile_Real_add(v.v_a, t_35);
        nile_Real_t t_37 = nile_Real_div(t_36, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_37);
        nile_Real_t t_38 = nile_Real (45);
        nile_Real_t t_39 = nile_Real_add(v.v_a, t_38);
        nile_Real_t t_40 = nile_Real_div(t_39, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_40);
        nile_Real_t t_41 = nile_Real (10);
        nile_Real_t t_42 = nile_Real_add(v.v_a, t_41);
        nile_Real_t t_43 = nile_Real_div(t_42, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_43);
        nile_Real_t t_44 = nile_Real (1);
        nile_Real_t t_45 = nile_Real_add(v.v_a, t_44);
        nile_Real_t t_46 = nile_Real_div(t_45, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_46);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1Weights_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1Weights_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur11x1Weights (nile_Process_t *p, 
                                float v_f)
{
    gezira_GaussianBlur11x1Weights_vars_t *vars;
    gezira_GaussianBlur11x1Weights_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur11x1Weights_prologue, gezira_GaussianBlur11x1Weights_body, gezira_GaussianBlur11x1Weights_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur11x1_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur11x1_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur11x1Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur11x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (11);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur11x1_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur11x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur11x1_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur11x1 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t)
{
    gezira_GaussianBlur11x1_vars_t *vars;
    gezira_GaussianBlur11x1_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur11x1_prologue, gezira_GaussianBlur11x1_body, gezira_GaussianBlur11x1_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur1x11_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x11_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur1x11Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur11x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (11);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x11_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x11_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x11_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x11_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x11 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t)
{
    gezira_GaussianBlur1x11_vars_t *vars;
    gezira_GaussianBlur1x11_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x11_prologue, gezira_GaussianBlur1x11_body, gezira_GaussianBlur1x11_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur21x1Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur21x1Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1Points_body (nile_Process_t *p,
                                    nile_Buffer_t *in,
                                    nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur21x1Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (10);
        nile_Real_t t_3 = nile_Real_sub(v_x, t_2);
        nile_Real_t t_1_1 = t_3;
        nile_Real_t t_1_2 = v_y;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (9);
        nile_Real_t t_7 = nile_Real_sub(v_x, t_6);
        nile_Real_t t_5_1 = t_7;
        nile_Real_t t_5_2 = v_y;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_10 = nile_Real (8);
        nile_Real_t t_11 = nile_Real_sub(v_x, t_10);
        nile_Real_t t_9_1 = t_11;
        nile_Real_t t_9_2 = v_y;
        nile_Real_t t_12_x = t_9_1;
        nile_Real_t t_12_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_12_x);
        nile_Buffer_push_tail(out, t_12_y);
        nile_Real_t t_14 = nile_Real (7);
        nile_Real_t t_15 = nile_Real_sub(v_x, t_14);
        nile_Real_t t_13_1 = t_15;
        nile_Real_t t_13_2 = v_y;
        nile_Real_t t_16_x = t_13_1;
        nile_Real_t t_16_y = t_13_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16_x);
        nile_Buffer_push_tail(out, t_16_y);
        nile_Real_t t_18 = nile_Real (6);
        nile_Real_t t_19 = nile_Real_sub(v_x, t_18);
        nile_Real_t t_17_1 = t_19;
        nile_Real_t t_17_2 = v_y;
        nile_Real_t t_20_x = t_17_1;
        nile_Real_t t_20_y = t_17_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_20_x);
        nile_Buffer_push_tail(out, t_20_y);
        nile_Real_t t_22 = nile_Real (5);
        nile_Real_t t_23 = nile_Real_sub(v_x, t_22);
        nile_Real_t t_21_1 = t_23;
        nile_Real_t t_21_2 = v_y;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_24_x);
        nile_Buffer_push_tail(out, t_24_y);
        nile_Real_t t_26 = nile_Real (4);
        nile_Real_t t_27 = nile_Real_sub(v_x, t_26);
        nile_Real_t t_25_1 = t_27;
        nile_Real_t t_25_2 = v_y;
        nile_Real_t t_28_x = t_25_1;
        nile_Real_t t_28_y = t_25_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_28_x);
        nile_Buffer_push_tail(out, t_28_y);
        nile_Real_t t_30 = nile_Real (3);
        nile_Real_t t_31 = nile_Real_sub(v_x, t_30);
        nile_Real_t t_29_1 = t_31;
        nile_Real_t t_29_2 = v_y;
        nile_Real_t t_32_x = t_29_1;
        nile_Real_t t_32_y = t_29_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_32_x);
        nile_Buffer_push_tail(out, t_32_y);
        nile_Real_t t_34 = nile_Real (2);
        nile_Real_t t_35 = nile_Real_sub(v_x, t_34);
        nile_Real_t t_33_1 = t_35;
        nile_Real_t t_33_2 = v_y;
        nile_Real_t t_36_x = t_33_1;
        nile_Real_t t_36_y = t_33_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_36_x);
        nile_Buffer_push_tail(out, t_36_y);
        nile_Real_t t_38 = nile_Real (1);
        nile_Real_t t_39 = nile_Real_sub(v_x, t_38);
        nile_Real_t t_37_1 = t_39;
        nile_Real_t t_37_2 = v_y;
        nile_Real_t t_40_x = t_37_1;
        nile_Real_t t_40_y = t_37_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_40_x);
        nile_Buffer_push_tail(out, t_40_y);
        nile_Real_t t_41_1 = v_x;
        nile_Real_t t_41_2 = v_y;
        nile_Real_t t_42_x = t_41_1;
        nile_Real_t t_42_y = t_41_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_42_x);
        nile_Buffer_push_tail(out, t_42_y);
        nile_Real_t t_44 = nile_Real (1);
        nile_Real_t t_45 = nile_Real_add(v_x, t_44);
        nile_Real_t t_43_1 = t_45;
        nile_Real_t t_43_2 = v_y;
        nile_Real_t t_46_x = t_43_1;
        nile_Real_t t_46_y = t_43_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_46_x);
        nile_Buffer_push_tail(out, t_46_y);
        nile_Real_t t_48 = nile_Real (2);
        nile_Real_t t_49 = nile_Real_add(v_x, t_48);
        nile_Real_t t_47_1 = t_49;
        nile_Real_t t_47_2 = v_y;
        nile_Real_t t_50_x = t_47_1;
        nile_Real_t t_50_y = t_47_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_50_x);
        nile_Buffer_push_tail(out, t_50_y);
        nile_Real_t t_52 = nile_Real (3);
        nile_Real_t t_53 = nile_Real_add(v_x, t_52);
        nile_Real_t t_51_1 = t_53;
        nile_Real_t t_51_2 = v_y;
        nile_Real_t t_54_x = t_51_1;
        nile_Real_t t_54_y = t_51_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_54_x);
        nile_Buffer_push_tail(out, t_54_y);
        nile_Real_t t_56 = nile_Real (4);
        nile_Real_t t_57 = nile_Real_add(v_x, t_56);
        nile_Real_t t_55_1 = t_57;
        nile_Real_t t_55_2 = v_y;
        nile_Real_t t_58_x = t_55_1;
        nile_Real_t t_58_y = t_55_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_58_x);
        nile_Buffer_push_tail(out, t_58_y);
        nile_Real_t t_60 = nile_Real (5);
        nile_Real_t t_61 = nile_Real_add(v_x, t_60);
        nile_Real_t t_59_1 = t_61;
        nile_Real_t t_59_2 = v_y;
        nile_Real_t t_62_x = t_59_1;
        nile_Real_t t_62_y = t_59_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_62_x);
        nile_Buffer_push_tail(out, t_62_y);
        nile_Real_t t_64 = nile_Real (6);
        nile_Real_t t_65 = nile_Real_add(v_x, t_64);
        nile_Real_t t_63_1 = t_65;
        nile_Real_t t_63_2 = v_y;
        nile_Real_t t_66_x = t_63_1;
        nile_Real_t t_66_y = t_63_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_66_x);
        nile_Buffer_push_tail(out, t_66_y);
        nile_Real_t t_68 = nile_Real (7);
        nile_Real_t t_69 = nile_Real_add(v_x, t_68);
        nile_Real_t t_67_1 = t_69;
        nile_Real_t t_67_2 = v_y;
        nile_Real_t t_70_x = t_67_1;
        nile_Real_t t_70_y = t_67_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_70_x);
        nile_Buffer_push_tail(out, t_70_y);
        nile_Real_t t_72 = nile_Real (8);
        nile_Real_t t_73 = nile_Real_add(v_x, t_72);
        nile_Real_t t_71_1 = t_73;
        nile_Real_t t_71_2 = v_y;
        nile_Real_t t_74_x = t_71_1;
        nile_Real_t t_74_y = t_71_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_74_x);
        nile_Buffer_push_tail(out, t_74_y);
        nile_Real_t t_76 = nile_Real (9);
        nile_Real_t t_77 = nile_Real_add(v_x, t_76);
        nile_Real_t t_75_1 = t_77;
        nile_Real_t t_75_2 = v_y;
        nile_Real_t t_78_x = t_75_1;
        nile_Real_t t_78_y = t_75_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_78_x);
        nile_Buffer_push_tail(out, t_78_y);
        nile_Real_t t_80 = nile_Real (10);
        nile_Real_t t_81 = nile_Real_add(v_x, t_80);
        nile_Real_t t_79_1 = t_81;
        nile_Real_t t_79_2 = v_y;
        nile_Real_t t_82_x = t_79_1;
        nile_Real_t t_82_y = t_79_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_82_x);
        nile_Buffer_push_tail(out, t_82_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur21x1Points (nile_Process_t *p)
{
    gezira_GaussianBlur21x1Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur21x1Points_prologue, gezira_GaussianBlur21x1Points_body, gezira_GaussianBlur21x1Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
} gezira_GaussianBlur1x21Points_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x21Points_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21Points_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x21Points_body (nile_Process_t *p,
                                    nile_Buffer_t *in,
                                    nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21Points_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur1x21Points_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (10);
        nile_Real_t t_3 = nile_Real_sub(v_y, t_2);
        nile_Real_t t_1_1 = v_x;
        nile_Real_t t_1_2 = t_3;
        nile_Real_t t_4_x = t_1_1;
        nile_Real_t t_4_y = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        nile_Real_t t_6 = nile_Real (9);
        nile_Real_t t_7 = nile_Real_sub(v_y, t_6);
        nile_Real_t t_5_1 = v_x;
        nile_Real_t t_5_2 = t_7;
        nile_Real_t t_8_x = t_5_1;
        nile_Real_t t_8_y = t_5_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_8_x);
        nile_Buffer_push_tail(out, t_8_y);
        nile_Real_t t_10 = nile_Real (8);
        nile_Real_t t_11 = nile_Real_sub(v_y, t_10);
        nile_Real_t t_9_1 = v_x;
        nile_Real_t t_9_2 = t_11;
        nile_Real_t t_12_x = t_9_1;
        nile_Real_t t_12_y = t_9_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_12_x);
        nile_Buffer_push_tail(out, t_12_y);
        nile_Real_t t_14 = nile_Real (7);
        nile_Real_t t_15 = nile_Real_sub(v_y, t_14);
        nile_Real_t t_13_1 = v_x;
        nile_Real_t t_13_2 = t_15;
        nile_Real_t t_16_x = t_13_1;
        nile_Real_t t_16_y = t_13_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16_x);
        nile_Buffer_push_tail(out, t_16_y);
        nile_Real_t t_18 = nile_Real (6);
        nile_Real_t t_19 = nile_Real_sub(v_y, t_18);
        nile_Real_t t_17_1 = v_x;
        nile_Real_t t_17_2 = t_19;
        nile_Real_t t_20_x = t_17_1;
        nile_Real_t t_20_y = t_17_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_20_x);
        nile_Buffer_push_tail(out, t_20_y);
        nile_Real_t t_22 = nile_Real (5);
        nile_Real_t t_23 = nile_Real_sub(v_y, t_22);
        nile_Real_t t_21_1 = v_x;
        nile_Real_t t_21_2 = t_23;
        nile_Real_t t_24_x = t_21_1;
        nile_Real_t t_24_y = t_21_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_24_x);
        nile_Buffer_push_tail(out, t_24_y);
        nile_Real_t t_26 = nile_Real (4);
        nile_Real_t t_27 = nile_Real_sub(v_y, t_26);
        nile_Real_t t_25_1 = v_x;
        nile_Real_t t_25_2 = t_27;
        nile_Real_t t_28_x = t_25_1;
        nile_Real_t t_28_y = t_25_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_28_x);
        nile_Buffer_push_tail(out, t_28_y);
        nile_Real_t t_30 = nile_Real (3);
        nile_Real_t t_31 = nile_Real_sub(v_y, t_30);
        nile_Real_t t_29_1 = v_x;
        nile_Real_t t_29_2 = t_31;
        nile_Real_t t_32_x = t_29_1;
        nile_Real_t t_32_y = t_29_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_32_x);
        nile_Buffer_push_tail(out, t_32_y);
        nile_Real_t t_34 = nile_Real (2);
        nile_Real_t t_35 = nile_Real_sub(v_y, t_34);
        nile_Real_t t_33_1 = v_x;
        nile_Real_t t_33_2 = t_35;
        nile_Real_t t_36_x = t_33_1;
        nile_Real_t t_36_y = t_33_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_36_x);
        nile_Buffer_push_tail(out, t_36_y);
        nile_Real_t t_38 = nile_Real (1);
        nile_Real_t t_39 = nile_Real_sub(v_y, t_38);
        nile_Real_t t_37_1 = v_x;
        nile_Real_t t_37_2 = t_39;
        nile_Real_t t_40_x = t_37_1;
        nile_Real_t t_40_y = t_37_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_40_x);
        nile_Buffer_push_tail(out, t_40_y);
        nile_Real_t t_41_1 = v_x;
        nile_Real_t t_41_2 = v_y;
        nile_Real_t t_42_x = t_41_1;
        nile_Real_t t_42_y = t_41_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_42_x);
        nile_Buffer_push_tail(out, t_42_y);
        nile_Real_t t_44 = nile_Real (1);
        nile_Real_t t_45 = nile_Real_add(v_y, t_44);
        nile_Real_t t_43_1 = v_x;
        nile_Real_t t_43_2 = t_45;
        nile_Real_t t_46_x = t_43_1;
        nile_Real_t t_46_y = t_43_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_46_x);
        nile_Buffer_push_tail(out, t_46_y);
        nile_Real_t t_48 = nile_Real (2);
        nile_Real_t t_49 = nile_Real_add(v_y, t_48);
        nile_Real_t t_47_1 = v_x;
        nile_Real_t t_47_2 = t_49;
        nile_Real_t t_50_x = t_47_1;
        nile_Real_t t_50_y = t_47_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_50_x);
        nile_Buffer_push_tail(out, t_50_y);
        nile_Real_t t_52 = nile_Real (3);
        nile_Real_t t_53 = nile_Real_add(v_y, t_52);
        nile_Real_t t_51_1 = v_x;
        nile_Real_t t_51_2 = t_53;
        nile_Real_t t_54_x = t_51_1;
        nile_Real_t t_54_y = t_51_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_54_x);
        nile_Buffer_push_tail(out, t_54_y);
        nile_Real_t t_56 = nile_Real (4);
        nile_Real_t t_57 = nile_Real_add(v_y, t_56);
        nile_Real_t t_55_1 = v_x;
        nile_Real_t t_55_2 = t_57;
        nile_Real_t t_58_x = t_55_1;
        nile_Real_t t_58_y = t_55_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_58_x);
        nile_Buffer_push_tail(out, t_58_y);
        nile_Real_t t_60 = nile_Real (5);
        nile_Real_t t_61 = nile_Real_add(v_y, t_60);
        nile_Real_t t_59_1 = v_x;
        nile_Real_t t_59_2 = t_61;
        nile_Real_t t_62_x = t_59_1;
        nile_Real_t t_62_y = t_59_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_62_x);
        nile_Buffer_push_tail(out, t_62_y);
        nile_Real_t t_64 = nile_Real (6);
        nile_Real_t t_65 = nile_Real_add(v_y, t_64);
        nile_Real_t t_63_1 = v_x;
        nile_Real_t t_63_2 = t_65;
        nile_Real_t t_66_x = t_63_1;
        nile_Real_t t_66_y = t_63_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_66_x);
        nile_Buffer_push_tail(out, t_66_y);
        nile_Real_t t_68 = nile_Real (7);
        nile_Real_t t_69 = nile_Real_add(v_y, t_68);
        nile_Real_t t_67_1 = v_x;
        nile_Real_t t_67_2 = t_69;
        nile_Real_t t_70_x = t_67_1;
        nile_Real_t t_70_y = t_67_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_70_x);
        nile_Buffer_push_tail(out, t_70_y);
        nile_Real_t t_72 = nile_Real (8);
        nile_Real_t t_73 = nile_Real_add(v_y, t_72);
        nile_Real_t t_71_1 = v_x;
        nile_Real_t t_71_2 = t_73;
        nile_Real_t t_74_x = t_71_1;
        nile_Real_t t_74_y = t_71_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_74_x);
        nile_Buffer_push_tail(out, t_74_y);
        nile_Real_t t_76 = nile_Real (9);
        nile_Real_t t_77 = nile_Real_add(v_y, t_76);
        nile_Real_t t_75_1 = v_x;
        nile_Real_t t_75_2 = t_77;
        nile_Real_t t_78_x = t_75_1;
        nile_Real_t t_78_y = t_75_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_78_x);
        nile_Buffer_push_tail(out, t_78_y);
        nile_Real_t t_80 = nile_Real (10);
        nile_Real_t t_81 = nile_Real_add(v_y, t_80);
        nile_Real_t t_79_1 = v_x;
        nile_Real_t t_79_2 = t_81;
        nile_Real_t t_82_x = t_79_1;
        nile_Real_t t_82_y = t_79_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_82_x);
        nile_Buffer_push_tail(out, t_82_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x21Points_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21Points_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21Points_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x21Points (nile_Process_t *p)
{
    gezira_GaussianBlur1x21Points_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x21Points_prologue, gezira_GaussianBlur1x21Points_body, gezira_GaussianBlur1x21Points_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
    nile_Real_t v_f;
    nile_Real_t v_a;
    nile_Real_t v_s;
} gezira_GaussianBlur21x1Weights_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur21x1Weights_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Weights_vars_t v = *vars;
    nile_Real_t t_7 = nile_Real (1048576);
    nile_Real_t t_8 = nile_Real_mul(t_7, v.v_f);
    v.v_a = t_8;
    nile_Real_t t_9 = nile_Real (1048576);
    nile_Real_t t_10 = nile_Real (21);
    nile_Real_t t_11 = nile_Real_mul(t_10, v.v_a);
    nile_Real_t t_12 = nile_Real_add(t_9, t_11);
    v.v_s = t_12;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1Weights_body (nile_Process_t *p,
                                     nile_Buffer_t *in,
                                     nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Weights_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GaussianBlur21x1Weights_vars_t v_ = v;
        nile_Real_t t_13_x;
        nile_Real_t t_13_y;
        t_13_x = nile_Buffer_pop_head(in);
        t_13_y = nile_Buffer_pop_head(in);
        nile_Real_t t_14 = nile_Real (1);
        nile_Real_t t_15 = nile_Real_add(v.v_a, t_14);
        nile_Real_t t_16 = nile_Real_div(t_15, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_16);
        nile_Real_t t_17 = nile_Real (20);
        nile_Real_t t_18 = nile_Real_add(v.v_a, t_17);
        nile_Real_t t_19 = nile_Real_div(t_18, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_19);
        nile_Real_t t_20 = nile_Real (190);
        nile_Real_t t_21 = nile_Real_add(v.v_a, t_20);
        nile_Real_t t_22 = nile_Real_div(t_21, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_22);
        nile_Real_t t_23 = nile_Real (1140);
        nile_Real_t t_24 = nile_Real_add(v.v_a, t_23);
        nile_Real_t t_25 = nile_Real_div(t_24, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_25);
        nile_Real_t t_26 = nile_Real (4845);
        nile_Real_t t_27 = nile_Real_add(v.v_a, t_26);
        nile_Real_t t_28 = nile_Real_div(t_27, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_28);
        nile_Real_t t_29 = nile_Real (15504);
        nile_Real_t t_30 = nile_Real_add(v.v_a, t_29);
        nile_Real_t t_31 = nile_Real_div(t_30, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_31);
        nile_Real_t t_32 = nile_Real (38760);
        nile_Real_t t_33 = nile_Real_add(v.v_a, t_32);
        nile_Real_t t_34 = nile_Real_div(t_33, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_34);
        nile_Real_t t_35 = nile_Real (77520);
        nile_Real_t t_36 = nile_Real_add(v.v_a, t_35);
        nile_Real_t t_37 = nile_Real_div(t_36, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_37);
        nile_Real_t t_38 = nile_Real (125970);
        nile_Real_t t_39 = nile_Real_add(v.v_a, t_38);
        nile_Real_t t_40 = nile_Real_div(t_39, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_40);
        nile_Real_t t_41 = nile_Real (167960);
        nile_Real_t t_42 = nile_Real_add(v.v_a, t_41);
        nile_Real_t t_43 = nile_Real_div(t_42, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_43);
        nile_Real_t t_44 = nile_Real (184756);
        nile_Real_t t_45 = nile_Real_add(v.v_a, t_44);
        nile_Real_t t_46 = nile_Real_div(t_45, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_46);
        nile_Real_t t_47 = nile_Real (167960);
        nile_Real_t t_48 = nile_Real_add(v.v_a, t_47);
        nile_Real_t t_49 = nile_Real_div(t_48, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_49);
        nile_Real_t t_50 = nile_Real (125970);
        nile_Real_t t_51 = nile_Real_add(v.v_a, t_50);
        nile_Real_t t_52 = nile_Real_div(t_51, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_52);
        nile_Real_t t_53 = nile_Real (77520);
        nile_Real_t t_54 = nile_Real_add(v.v_a, t_53);
        nile_Real_t t_55 = nile_Real_div(t_54, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_55);
        nile_Real_t t_56 = nile_Real (38760);
        nile_Real_t t_57 = nile_Real_add(v.v_a, t_56);
        nile_Real_t t_58 = nile_Real_div(t_57, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_58);
        nile_Real_t t_59 = nile_Real (15504);
        nile_Real_t t_60 = nile_Real_add(v.v_a, t_59);
        nile_Real_t t_61 = nile_Real_div(t_60, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_61);
        nile_Real_t t_62 = nile_Real (4845);
        nile_Real_t t_63 = nile_Real_add(v.v_a, t_62);
        nile_Real_t t_64 = nile_Real_div(t_63, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_64);
        nile_Real_t t_65 = nile_Real (1140);
        nile_Real_t t_66 = nile_Real_add(v.v_a, t_65);
        nile_Real_t t_67 = nile_Real_div(t_66, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_67);
        nile_Real_t t_68 = nile_Real (190);
        nile_Real_t t_69 = nile_Real_add(v.v_a, t_68);
        nile_Real_t t_70 = nile_Real_div(t_69, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_70);
        nile_Real_t t_71 = nile_Real (20);
        nile_Real_t t_72 = nile_Real_add(v.v_a, t_71);
        nile_Real_t t_73 = nile_Real_div(t_72, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_73);
        nile_Real_t t_74 = nile_Real (1);
        nile_Real_t t_75 = nile_Real_add(v.v_a, t_74);
        nile_Real_t t_76 = nile_Real_div(t_75, v.v_s);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_76);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1Weights_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1Weights_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1Weights_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GaussianBlur21x1Weights (nile_Process_t *p, 
                                float v_f)
{
    gezira_GaussianBlur21x1Weights_vars_t *vars;
    gezira_GaussianBlur21x1Weights_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur21x1Weights_prologue, gezira_GaussianBlur21x1Weights_body, gezira_GaussianBlur21x1Weights_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur21x1_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur21x1_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur21x1Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur21x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (21);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur21x1_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur21x1_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur21x1_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur21x1 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t)
{
    gezira_GaussianBlur21x1_vars_t *vars;
    gezira_GaussianBlur21x1_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur21x1_prologue, gezira_GaussianBlur21x1_body, gezira_GaussianBlur21x1_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_f;
    nile_Process_t *v_t;
} gezira_GaussianBlur1x21_vars_t;

static nile_Buffer_t *
gezira_GaussianBlur1x21_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_GaussianBlur1x21Points(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = gezira_GaussianBlur21x1Weights(p, nile_Real_tof (v.v_f));
    nile_Real_t t_4 = nile_Real (1);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Real_t t_6 = nile_Real (21);
    nile_Process_t *t_7 = gezira_SumWeightedColors(p, nile_Real_tof (t_6));
    nile_Process_t *t_8 = nile_Process_pipe (t_5, t_7, NILE_NULL);
    return nile_Process_swap (p, t_8, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x21_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_GaussianBlur1x21_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GaussianBlur1x21_vars_t *vars = nile_Process_vars (p);
    gezira_GaussianBlur1x21_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_GaussianBlur1x21 (nile_Process_t *p, 
                         float v_f, 
                         nile_Process_t *v_t)
{
    gezira_GaussianBlur1x21_vars_t *vars;
    gezira_GaussianBlur1x21_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GaussianBlur1x21_prologue, gezira_GaussianBlur1x21_body, gezira_GaussianBlur1x21_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_f = nile_Real (v_f);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
    nile_Real_t v_s00;
    nile_Real_t v_dsdx;
    nile_Real_t v_dsdy;
} gezira_LinearGradientShape_vars_t;

static nile_Buffer_t *
gezira_LinearGradientShape_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_LinearGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_LinearGradientShape_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_LinearGradientShape_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_LinearGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_LinearGradientShape_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_LinearGradientShape_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real_mul(v_x, v.v_dsdx);
        nile_Real_t t_2 = nile_Real_add(v.v_s00, t_1);
        nile_Real_t t_3 = nile_Real_mul(v_y, v.v_dsdy);
        nile_Real_t t_4 = nile_Real_add(t_2, t_3);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_LinearGradientShape_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_LinearGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_LinearGradientShape_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_LinearGradientShape (nile_Process_t *p, 
                            float v_s00, 
                            float v_dsdx, 
                            float v_dsdy)
{
    gezira_LinearGradientShape_vars_t *vars;
    gezira_LinearGradientShape_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_LinearGradientShape_prologue, gezira_LinearGradientShape_body, gezira_LinearGradientShape_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_s00 = nile_Real (v_s00);
        v.v_dsdx = nile_Real (v_dsdx);
        v.v_dsdy = nile_Real (v_dsdy);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 1

typedef struct {
    nile_Real_t v_C_x;
    nile_Real_t v_C_y;
    nile_Real_t v_r;
} gezira_RadialGradientShape_vars_t;

static nile_Buffer_t *
gezira_RadialGradientShape_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_RadialGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_RadialGradientShape_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_RadialGradientShape_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_RadialGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_RadialGradientShape_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_RadialGradientShape_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1_x = nile_Real_sub(v_P_x, v.v_C_x);
        nile_Real_t t_1_y = nile_Real_sub(v_P_y, v.v_C_y);
        nile_Real_t t_2_x = t_1_x;
        nile_Real_t t_2_y = t_1_y;
        nile_Real_t t_3 = nile_Real_mul(t_2_x, t_2_x);
        nile_Real_t t_4 = nile_Real_mul(t_2_y, t_2_y);
        nile_Real_t t_5 = nile_Real_add(t_3, t_4);
        nile_Real_t t_6 = nile_Real_sqt(t_5);
        nile_Real_t t_7 = nile_Real_div(t_6, v.v_r);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_7);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_RadialGradientShape_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_RadialGradientShape_vars_t *vars = nile_Process_vars (p);
    gezira_RadialGradientShape_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_RadialGradientShape (nile_Process_t *p, 
                            float v_C_x, 
                            float v_C_y, 
                            float v_r)
{
    gezira_RadialGradientShape_vars_t *vars;
    gezira_RadialGradientShape_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_RadialGradientShape_prologue, gezira_RadialGradientShape_body, gezira_RadialGradientShape_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_C_x = nile_Real (v_C_x);
        v.v_C_y = nile_Real (v_C_y);
        v.v_r = nile_Real (v_r);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 1
#define OUT_QUANTUM 1

typedef struct {
} gezira_GradientExtendPad_vars_t;

static nile_Buffer_t *
gezira_GradientExtendPad_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendPad_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendPad_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_GradientExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendPad_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientExtendPad_vars_t v_ = v;
        nile_Real_t v_s = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0);
        nile_Real_t t_2 = nile_Real_gt(t_1, v_s);
        nile_Real_t t_3 = nile_Real_nz (t_2) ? t_1 : v_s;
        nile_Real_t t_4 = nile_Real (1);
        nile_Real_t t_5 = nile_Real_lt(t_3, t_4);
        nile_Real_t t_6 = nile_Real_nz (t_5) ? t_3 : t_4;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_6);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendPad_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendPad_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientExtendPad (nile_Process_t *p)
{
    gezira_GradientExtendPad_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientExtendPad_prologue, gezira_GradientExtendPad_body, gezira_GradientExtendPad_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 1
#define OUT_QUANTUM 1

typedef struct {
} gezira_GradientExtendRepeat_vars_t;

static nile_Buffer_t *
gezira_GradientExtendRepeat_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendRepeat_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendRepeat_body (nile_Process_t *p,
                                  nile_Buffer_t *in,
                                  nile_Buffer_t *out)
{
    gezira_GradientExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendRepeat_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientExtendRepeat_vars_t v_ = v;
        nile_Real_t v_s = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real_flr(v_s);
        nile_Real_t t_2 = nile_Real_sub(v_s, t_1);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_2);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendRepeat_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendRepeat_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientExtendRepeat (nile_Process_t *p)
{
    gezira_GradientExtendRepeat_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientExtendRepeat_prologue, gezira_GradientExtendRepeat_body, gezira_GradientExtendRepeat_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 1
#define OUT_QUANTUM 1

typedef struct {
} gezira_GradientExtendReflect_vars_t;

static nile_Buffer_t *
gezira_GradientExtendReflect_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendReflect_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendReflect_body (nile_Process_t *p,
                                   nile_Buffer_t *in,
                                   nile_Buffer_t *out)
{
    gezira_GradientExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendReflect_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientExtendReflect_vars_t v_ = v;
        nile_Real_t v_s = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (1);
        nile_Real_t t_2 = nile_Real_sub(v_s, t_1);
        nile_Real_t t_3 = nile_Real (0);
        nile_Real_t t_4 = nile_Real_lt(t_2, t_3);
        nile_Real_t t_5 = nile_Real_neg(t_2);
        nile_Real_t t_6 = nile_Real_nz (t_4) ? t_5 : t_2;
        nile_Real_t t_7 = nile_Real (2);
        nile_Real_t t_8 = nile_Real (1);
        nile_Real_t t_9 = nile_Real (0);
        nile_Real_t t_10 = nile_Real_neq(t_7, t_9);
        nile_Real_t t_11 = nile_Real_nz (t_10) ? t_7 : t_8;
        nile_Real_t t_12 = nile_Real_div(t_6, t_11);
        nile_Real_t t_13 = nile_Real_flr(t_12);
        nile_Real_t t_14 = nile_Real_mul(t_13, t_7);
        nile_Real_t t_15 = nile_Real_sub(t_6, t_14);
        nile_Real_t t_16 = nile_Real (1);
        nile_Real_t t_17 = nile_Real_sub(t_15, t_16);
        nile_Real_t t_18 = nile_Real (0);
        nile_Real_t t_19 = nile_Real_lt(t_17, t_18);
        nile_Real_t t_20 = nile_Real_neg(t_17);
        nile_Real_t t_21 = nile_Real_nz (t_19) ? t_20 : t_17;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_21);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientExtendReflect_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_GradientExtendReflect_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientExtendReflect (nile_Process_t *p)
{
    gezira_GradientExtendReflect_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientExtendReflect_prologue, gezira_GradientExtendReflect_body, gezira_GradientExtendReflect_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 1
#define OUT_QUANTUM 5

typedef struct {
} gezira_GradientColorBegin_vars_t;

static nile_Buffer_t *
gezira_GradientColorBegin_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorBegin_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorBegin_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorBegin_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_GradientColorBegin_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorBegin_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientColorBegin_vars_t v_ = v;
        nile_Real_t v_s = nile_Buffer_pop_head(in);
        nile_Real_t t_2 = nile_Real (0);
        nile_Real_t t_1_1 = v_s;
        nile_Real_t t_1_2 = t_2;
        nile_Real_t t_3_1 = t_1_1;
        nile_Real_t t_3_2_a = t_1_2;
        nile_Real_t t_3_2_r = t_1_2;
        nile_Real_t t_3_2_g = t_1_2;
        nile_Real_t t_3_2_b = t_1_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_3_1);
        nile_Buffer_push_tail(out, t_3_2_a);
        nile_Buffer_push_tail(out, t_3_2_r);
        nile_Buffer_push_tail(out, t_3_2_g);
        nile_Buffer_push_tail(out, t_3_2_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorBegin_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorBegin_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorBegin_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientColorBegin (nile_Process_t *p)
{
    gezira_GradientColorBegin_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientColorBegin_prologue, gezira_GradientColorBegin_body, gezira_GradientColorBegin_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 5
#define OUT_QUANTUM 5

typedef struct {
    nile_Real_t v_c0_a;
    nile_Real_t v_c0_r;
    nile_Real_t v_c0_g;
    nile_Real_t v_c0_b;
    nile_Real_t v_dcds_a;
    nile_Real_t v_dcds_r;
    nile_Real_t v_dcds_g;
    nile_Real_t v_dcds_b;
    nile_Real_t v_l;
} gezira_GradientColorSpan_vars_t;

static nile_Buffer_t *
gezira_GradientColorSpan_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorSpan_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorSpan_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorSpan_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_GradientColorSpan_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorSpan_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientColorSpan_vars_t v_ = v;
        nile_Real_t v_s = nile_Buffer_pop_head(in);
        nile_Real_t v_c_a = nile_Buffer_pop_head(in);
        nile_Real_t v_c_r = nile_Buffer_pop_head(in);
        nile_Real_t v_c_g = nile_Buffer_pop_head(in);
        nile_Real_t v_c_b = nile_Buffer_pop_head(in);
        nile_Real_t t_1_a = v_s;
        nile_Real_t t_1_r = v_s;
        nile_Real_t t_1_g = v_s;
        nile_Real_t t_1_b = v_s;
        nile_Real_t t_2_a = nile_Real_mul(t_1_a, v.v_dcds_a);
        nile_Real_t t_2_r = nile_Real_mul(t_1_r, v.v_dcds_r);
        nile_Real_t t_2_g = nile_Real_mul(t_1_g, v.v_dcds_g);
        nile_Real_t t_2_b = nile_Real_mul(t_1_b, v.v_dcds_b);
        nile_Real_t t_3_a = nile_Real_add(v.v_c0_a, t_2_a);
        nile_Real_t t_3_r = nile_Real_add(v.v_c0_r, t_2_r);
        nile_Real_t t_3_g = nile_Real_add(v.v_c0_g, t_2_g);
        nile_Real_t t_3_b = nile_Real_add(v.v_c0_b, t_2_b);
        nile_Real_t v_d_a = t_3_a;
        nile_Real_t v_d_r = t_3_r;
        nile_Real_t v_d_g = t_3_g;
        nile_Real_t v_d_b = t_3_b;
        nile_Real_t t_5 = nile_Real_sub(v_s, v.v_l);
        nile_Real_t t_6 = nile_Real (0);
        nile_Real_t t_7 = nile_Real_lt(v_s, t_6);
        nile_Real_t t_8_a = t_7;
        nile_Real_t t_8_r = t_7;
        nile_Real_t t_8_g = t_7;
        nile_Real_t t_8_b = t_7;
        nile_Real_t t_9_a = nile_Real_nz (t_8_a) ? v_c_a : v_d_a;
        nile_Real_t t_9_r = nile_Real_nz (t_8_r) ? v_c_r : v_d_r;
        nile_Real_t t_9_g = nile_Real_nz (t_8_g) ? v_c_g : v_d_g;
        nile_Real_t t_9_b = nile_Real_nz (t_8_b) ? v_c_b : v_d_b;
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_10_1);
        nile_Buffer_push_tail(out, t_10_2_a);
        nile_Buffer_push_tail(out, t_10_2_r);
        nile_Buffer_push_tail(out, t_10_2_g);
        nile_Buffer_push_tail(out, t_10_2_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorSpan_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorSpan_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorSpan_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientColorSpan (nile_Process_t *p, 
                          float v_c0_a, 
                          float v_c0_r, 
                          float v_c0_g, 
                          float v_c0_b, 
                          float v_dcds_a, 
                          float v_dcds_r, 
                          float v_dcds_g, 
                          float v_dcds_b, 
                          float v_l)
{
    gezira_GradientColorSpan_vars_t *vars;
    gezira_GradientColorSpan_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientColorSpan_prologue, gezira_GradientColorSpan_body, gezira_GradientColorSpan_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_c0_a = nile_Real (v_c0_a);
        v.v_c0_r = nile_Real (v_c0_r);
        v.v_c0_g = nile_Real (v_c0_g);
        v.v_c0_b = nile_Real (v_c0_b);
        v.v_dcds_a = nile_Real (v_dcds_a);
        v.v_dcds_r = nile_Real (v_dcds_r);
        v.v_dcds_g = nile_Real (v_dcds_g);
        v.v_dcds_b = nile_Real (v_dcds_b);
        v.v_l = nile_Real (v_l);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 5
#define OUT_QUANTUM 4

typedef struct {
} gezira_GradientColorEnd_vars_t;

static nile_Buffer_t *
gezira_GradientColorEnd_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorEnd_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorEnd_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorEnd_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_GradientColorEnd_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorEnd_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_GradientColorEnd_vars_t v_ = v;
        nile_Real_t t_1;
        t_1 = nile_Buffer_pop_head(in);
        nile_Real_t v_c_a = nile_Buffer_pop_head(in);
        nile_Real_t v_c_r = nile_Buffer_pop_head(in);
        nile_Real_t v_c_g = nile_Buffer_pop_head(in);
        nile_Real_t v_c_b = nile_Buffer_pop_head(in);
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
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_6_a);
        nile_Buffer_push_tail(out, t_6_r);
        nile_Buffer_push_tail(out, t_6_g);
        nile_Buffer_push_tail(out, t_6_b);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_GradientColorEnd_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_GradientColorEnd_vars_t *vars = nile_Process_vars (p);
    gezira_GradientColorEnd_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_GradientColorEnd (nile_Process_t *p)
{
    gezira_GradientColorEnd_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_GradientColorEnd_prologue, gezira_GradientColorEnd_body, gezira_GradientColorEnd_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 4

typedef struct {
    nile_Process_t *v_s;
    nile_Process_t *v_m;
    nile_Process_t *v_c;
} gezira_Gradient_vars_t;

static nile_Buffer_t *
gezira_Gradient_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Gradient_vars_t *vars = nile_Process_vars (p);
    gezira_Gradient_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (v.v_c, gezira_GradientColorEnd(p), NILE_NULL);
    nile_Process_t *t_2 = nile_Process_pipe (gezira_GradientColorBegin(p), t_1, NILE_NULL);
    nile_Process_t *t_3 = nile_Process_pipe (v.v_m, t_2, NILE_NULL);
    nile_Process_t *t_4 = nile_Process_pipe (v.v_s, t_3, NILE_NULL);
    return nile_Process_swap (p, t_4, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_Gradient_body (nile_Process_t *p,
                      nile_Buffer_t *in,
                      nile_Buffer_t *out)
{
    gezira_Gradient_vars_t *vars = nile_Process_vars (p);
    gezira_Gradient_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_Gradient_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Gradient_vars_t *vars = nile_Process_vars (p);
    gezira_Gradient_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_Gradient (nile_Process_t *p, 
                 nile_Process_t *v_s, 
                 nile_Process_t *v_m, 
                 nile_Process_t *v_c)
{
    gezira_Gradient_vars_t *vars;
    gezira_Gradient_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_Gradient_prologue, gezira_Gradient_body, gezira_Gradient_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_s = v_s;
        v.v_m = v_m;
        v.v_c = v_c;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendPad_vars_t;

static nile_Buffer_t *
gezira_ImageExtendPad_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendPad_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendPad_body (nile_Process_t *p,
                            nile_Buffer_t *in,
                            nile_Buffer_t *out)
{
    gezira_ImageExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendPad_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ImageExtendPad_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1 = nile_Real (0);
        nile_Real_t t_2_x = t_1;
        nile_Real_t t_2_y = t_1;
        nile_Real_t t_3 = nile_Real_gt(t_2_x, v_P_x);
        nile_Real_t t_4 = nile_Real_nz (t_3) ? t_2_x : v_P_x;
        nile_Real_t t_5 = nile_Real_gt(t_2_y, v_P_y);
        nile_Real_t t_6 = nile_Real_nz (t_5) ? t_2_y : v_P_y;
        nile_Real_t t_7_1 = t_4;
        nile_Real_t t_7_2 = t_6;
        nile_Real_t t_8_x = t_7_1;
        nile_Real_t t_8_y = t_7_2;
        nile_Real_t t_9 = nile_Real_lt(t_8_x, v.v_D_x);
        nile_Real_t t_10 = nile_Real_nz (t_9) ? t_8_x : v.v_D_x;
        nile_Real_t t_11 = nile_Real_lt(t_8_y, v.v_D_y);
        nile_Real_t t_12 = nile_Real_nz (t_11) ? t_8_y : v.v_D_y;
        nile_Real_t t_13_1 = t_10;
        nile_Real_t t_13_2 = t_12;
        nile_Real_t t_14_x = t_13_1;
        nile_Real_t t_14_y = t_13_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_14_x);
        nile_Buffer_push_tail(out, t_14_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendPad_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendPad_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendPad_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ImageExtendPad (nile_Process_t *p, 
                       float v_D_x, 
                       float v_D_y)
{
    gezira_ImageExtendPad_vars_t *vars;
    gezira_ImageExtendPad_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ImageExtendPad_prologue, gezira_ImageExtendPad_body, gezira_ImageExtendPad_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_D_x = nile_Real (v_D_x);
        v.v_D_y = nile_Real (v_D_y);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendRepeat_vars_t;

static nile_Buffer_t *
gezira_ImageExtendRepeat_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendRepeat_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendRepeat_body (nile_Process_t *p,
                               nile_Buffer_t *in,
                               nile_Buffer_t *out)
{
    gezira_ImageExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendRepeat_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ImageExtendRepeat_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1_x = nile_Real_div(v_P_x, v.v_D_x);
        nile_Real_t t_1_y = nile_Real_div(v_P_y, v.v_D_y);
        nile_Real_t v_Q_x = t_1_x;
        nile_Real_t v_Q_y = t_1_y;
        nile_Real_t t_2_x = nile_Real_flr(v_Q_x);
        nile_Real_t t_2_y = nile_Real_flr(v_Q_y);
        nile_Real_t t_3_x = nile_Real_sub(v_Q_x, t_2_x);
        nile_Real_t t_3_y = nile_Real_sub(v_Q_y, t_2_y);
        nile_Real_t t_4_x = nile_Real_mul(t_3_x, v.v_D_x);
        nile_Real_t t_4_y = nile_Real_mul(t_3_y, v.v_D_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendRepeat_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendRepeat_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendRepeat_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ImageExtendRepeat (nile_Process_t *p, 
                          float v_D_x, 
                          float v_D_y)
{
    gezira_ImageExtendRepeat_vars_t *vars;
    gezira_ImageExtendRepeat_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ImageExtendRepeat_prologue, gezira_ImageExtendRepeat_body, gezira_ImageExtendRepeat_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_D_x = nile_Real (v_D_x);
        v.v_D_y = nile_Real (v_D_y);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 2
#define OUT_QUANTUM 2

typedef struct {
    nile_Real_t v_D_x;
    nile_Real_t v_D_y;
} gezira_ImageExtendReflect_vars_t;

static nile_Buffer_t *
gezira_ImageExtendReflect_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendReflect_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendReflect_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_ImageExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendReflect_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ImageExtendReflect_vars_t v_ = v;
        nile_Real_t v_P_x = nile_Buffer_pop_head(in);
        nile_Real_t v_P_y = nile_Buffer_pop_head(in);
        nile_Real_t t_1_x = nile_Real_div(v_P_x, v.v_D_x);
        nile_Real_t t_1_y = nile_Real_div(v_P_y, v.v_D_y);
        nile_Real_t v_Q_x = t_1_x;
        nile_Real_t v_Q_y = t_1_y;
        nile_Real_t t_2 = nile_Real (1);
        nile_Real_t t_3_x = t_2;
        nile_Real_t t_3_y = t_2;
        nile_Real_t t_4_x = nile_Real_sub(v_Q_x, t_3_x);
        nile_Real_t t_4_y = nile_Real_sub(v_Q_y, t_3_y);
        nile_Real_t t_5 = nile_Real (0);
        nile_Real_t t_6 = nile_Real_lt(t_4_x, t_5);
        nile_Real_t t_7 = nile_Real_neg(t_4_x);
        nile_Real_t t_8 = nile_Real_nz (t_6) ? t_7 : t_4_x;
        nile_Real_t t_9 = nile_Real (0);
        nile_Real_t t_10 = nile_Real_lt(t_4_y, t_9);
        nile_Real_t t_11 = nile_Real_neg(t_4_y);
        nile_Real_t t_12 = nile_Real_nz (t_10) ? t_11 : t_4_y;
        nile_Real_t t_13_1 = t_8;
        nile_Real_t t_13_2 = t_12;
        nile_Real_t t_14_x = t_13_1;
        nile_Real_t t_14_y = t_13_2;
        nile_Real_t t_15 = nile_Real (2);
        nile_Real_t t_16_x = t_15;
        nile_Real_t t_16_y = t_15;
        nile_Real_t t_17 = nile_Real (1);
        nile_Real_t t_18 = nile_Real (0);
        nile_Real_t t_19 = nile_Real_neq(t_16_x, t_18);
        nile_Real_t t_20 = nile_Real_nz (t_19) ? t_16_x : t_17;
        nile_Real_t t_21 = nile_Real_div(t_14_x, t_20);
        nile_Real_t t_22 = nile_Real_flr(t_21);
        nile_Real_t t_23 = nile_Real_mul(t_22, t_16_x);
        nile_Real_t t_24 = nile_Real_sub(t_14_x, t_23);
        nile_Real_t t_25 = nile_Real (1);
        nile_Real_t t_26 = nile_Real (0);
        nile_Real_t t_27 = nile_Real_neq(t_16_y, t_26);
        nile_Real_t t_28 = nile_Real_nz (t_27) ? t_16_y : t_25;
        nile_Real_t t_29 = nile_Real_div(t_14_y, t_28);
        nile_Real_t t_30 = nile_Real_flr(t_29);
        nile_Real_t t_31 = nile_Real_mul(t_30, t_16_y);
        nile_Real_t t_32 = nile_Real_sub(t_14_y, t_31);
        nile_Real_t t_33_1 = t_24;
        nile_Real_t t_33_2 = t_32;
        nile_Real_t t_34_x = t_33_1;
        nile_Real_t t_34_y = t_33_2;
        nile_Real_t t_35 = nile_Real (1);
        nile_Real_t t_36_x = t_35;
        nile_Real_t t_36_y = t_35;
        nile_Real_t t_37_x = nile_Real_sub(t_34_x, t_36_x);
        nile_Real_t t_37_y = nile_Real_sub(t_34_y, t_36_y);
        nile_Real_t t_38 = nile_Real (0);
        nile_Real_t t_39 = nile_Real_lt(t_37_x, t_38);
        nile_Real_t t_40 = nile_Real_neg(t_37_x);
        nile_Real_t t_41 = nile_Real_nz (t_39) ? t_40 : t_37_x;
        nile_Real_t t_42 = nile_Real (0);
        nile_Real_t t_43 = nile_Real_lt(t_37_y, t_42);
        nile_Real_t t_44 = nile_Real_neg(t_37_y);
        nile_Real_t t_45 = nile_Real_nz (t_43) ? t_44 : t_37_y;
        nile_Real_t t_46_1 = t_41;
        nile_Real_t t_46_2 = t_45;
        nile_Real_t t_47_x = t_46_1;
        nile_Real_t t_47_y = t_46_2;
        nile_Real_t t_48_x = nile_Real_mul(t_47_x, v.v_D_x);
        nile_Real_t t_48_y = nile_Real_mul(t_47_y, v.v_D_y);
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_48_x);
        nile_Buffer_push_tail(out, t_48_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ImageExtendReflect_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ImageExtendReflect_vars_t *vars = nile_Process_vars (p);
    gezira_ImageExtendReflect_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ImageExtendReflect (nile_Process_t *p, 
                           float v_D_x, 
                           float v_D_y)
{
    gezira_ImageExtendReflect_vars_t *vars;
    gezira_ImageExtendReflect_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ImageExtendReflect_prologue, gezira_ImageExtendReflect_body, gezira_ImageExtendReflect_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_D_x = nile_Real (v_D_x);
        v.v_D_y = nile_Real (v_D_y);
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 6
#define OUT_QUANTUM 4

typedef struct {
} gezira_DecomposeBeziers_vars_t;

static nile_Buffer_t *
gezira_DecomposeBeziers_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_DecomposeBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_DecomposeBeziers_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_DecomposeBeziers_body (nile_Process_t *p,
                              nile_Buffer_t *in,
                              nile_Buffer_t *out)
{
    gezira_DecomposeBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_DecomposeBeziers_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_DecomposeBeziers_vars_t v_ = v;
        nile_Real_t v_A_x = nile_Buffer_pop_head(in);
        nile_Real_t v_A_y = nile_Buffer_pop_head(in);
        nile_Real_t v_B_x = nile_Buffer_pop_head(in);
        nile_Real_t v_B_y = nile_Buffer_pop_head(in);
        nile_Real_t v_C_x = nile_Buffer_pop_head(in);
        nile_Real_t v_C_y = nile_Buffer_pop_head(in);
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
        if (nile_Real_nz (t_8)) {
            nile_Real_t t_9_x = nile_Real_flr(v_A_x);
            nile_Real_t t_9_y = nile_Real_flr(v_A_y);
            nile_Real_t t_10_x = nile_Real_flr(v_C_x);
            nile_Real_t t_10_y = nile_Real_flr(v_C_y);
            nile_Real_t t_11 = nile_Real_lt(t_9_x, t_10_x);
            nile_Real_t t_12 = nile_Real_nz (t_11) ? t_9_x : t_10_x;
            nile_Real_t t_13 = nile_Real_lt(t_9_y, t_10_y);
            nile_Real_t t_14 = nile_Real_nz (t_13) ? t_9_y : t_10_y;
            nile_Real_t t_15_1 = t_12;
            nile_Real_t t_15_2 = t_14;
            nile_Real_t t_16_x = t_15_1;
            nile_Real_t t_16_y = t_15_2;
            nile_Real_t v_P_x = t_16_x;
            nile_Real_t v_P_y = t_16_y;
            nile_Real_t t_17 = nile_Real (1);
            nile_Real_t t_18 = nile_Real_add(v_P_x, t_17);
            nile_Real_t t_19 = nile_Real_add(v_C_x, v_A_x);
            nile_Real_t t_20 = nile_Real (2);
            nile_Real_t t_21 = nile_Real_div(t_19, t_20);
            nile_Real_t t_22 = nile_Real_sub(t_18, t_21);
            nile_Real_t v_w = t_22;
            nile_Real_t t_23 = nile_Real_sub(v_C_y, v_A_y);
            nile_Real_t v_h = t_23;
            nile_Real_t t_25 = nile_Real (1);
            nile_Real_t t_26 = nile_Real (2);
            nile_Real_t t_27 = nile_Real_div(t_25, t_26);
            nile_Real_t t_28 = nile_Real_add(v_P_x, t_27);
            nile_Real_t t_29 = nile_Real (1);
            nile_Real_t t_30 = nile_Real (2);
            nile_Real_t t_31 = nile_Real_div(t_29, t_30);
            nile_Real_t t_32 = nile_Real_add(v_P_y, t_31);
            nile_Real_t t_33 = nile_Real_mul(v_w, v_h);
            nile_Real_t t_24_1 = t_28;
            nile_Real_t t_24_2 = t_32;
            nile_Real_t t_24_3 = t_33;
            nile_Real_t t_24_4 = v_h;
            nile_Real_t t_34_x = t_24_1;
            nile_Real_t t_34_y = t_24_2;
            nile_Real_t t_34_a = t_24_3;
            nile_Real_t t_34_h = t_24_4;
            if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                out = nile_Process_append_output (p, out);
            nile_Buffer_push_tail(out, t_34_x);
            nile_Buffer_push_tail(out, t_34_y);
            nile_Buffer_push_tail(out, t_34_a);
            nile_Buffer_push_tail(out, t_34_h);
        }
        else {
            nile_Real_t t_35 = nile_Real_add(v_A_x, v_B_x);
            nile_Real_t t_36 = nile_Real (2);
            nile_Real_t t_37 = nile_Real_div(t_35, t_36);
            nile_Real_t t_38 = nile_Real_add(v_A_y, v_B_y);
            nile_Real_t t_39 = nile_Real (2);
            nile_Real_t t_40 = nile_Real_div(t_38, t_39);
            nile_Real_t t_41_1 = t_37;
            nile_Real_t t_41_2 = t_40;
            nile_Real_t t_42_x = t_41_1;
            nile_Real_t t_42_y = t_41_2;
            nile_Real_t t_43 = nile_Real_add(v_B_x, v_C_x);
            nile_Real_t t_44 = nile_Real (2);
            nile_Real_t t_45 = nile_Real_div(t_43, t_44);
            nile_Real_t t_46 = nile_Real_add(v_B_y, v_C_y);
            nile_Real_t t_47 = nile_Real (2);
            nile_Real_t t_48 = nile_Real_div(t_46, t_47);
            nile_Real_t t_49_1 = t_45;
            nile_Real_t t_49_2 = t_48;
            nile_Real_t t_50_x = t_49_1;
            nile_Real_t t_50_y = t_49_2;
            nile_Real_t t_51 = nile_Real_add(t_42_x, t_50_x);
            nile_Real_t t_52 = nile_Real (2);
            nile_Real_t t_53 = nile_Real_div(t_51, t_52);
            nile_Real_t t_54 = nile_Real_add(t_42_y, t_50_y);
            nile_Real_t t_55 = nile_Real (2);
            nile_Real_t t_56 = nile_Real_div(t_54, t_55);
            nile_Real_t t_57_1 = t_53;
            nile_Real_t t_57_2 = t_56;
            nile_Real_t t_58_x = t_57_1;
            nile_Real_t t_58_y = t_57_2;
            nile_Real_t v_ABBC_x = t_58_x;
            nile_Real_t v_ABBC_y = t_58_y;
            nile_Real_t t_59_x = nile_Real_flr(v_ABBC_x);
            nile_Real_t t_59_y = nile_Real_flr(v_ABBC_y);
            nile_Real_t v_min_x = t_59_x;
            nile_Real_t v_min_y = t_59_y;
            nile_Real_t t_60_x = nile_Real_clg(v_ABBC_x);
            nile_Real_t t_60_y = nile_Real_clg(v_ABBC_y);
            nile_Real_t v_max_x = t_60_x;
            nile_Real_t v_max_y = t_60_y;
            nile_Real_t t_61_x = nile_Real_sub(v_ABBC_x, v_min_x);
            nile_Real_t t_61_y = nile_Real_sub(v_ABBC_y, v_min_y);
            nile_Real_t t_62 = nile_Real (0);
            nile_Real_t t_63 = nile_Real_lt(t_61_x, t_62);
            nile_Real_t t_64 = nile_Real_neg(t_61_x);
            nile_Real_t t_65 = nile_Real_nz (t_63) ? t_64 : t_61_x;
            nile_Real_t t_66 = nile_Real (0);
            nile_Real_t t_67 = nile_Real_lt(t_61_y, t_66);
            nile_Real_t t_68 = nile_Real_neg(t_61_y);
            nile_Real_t t_69 = nile_Real_nz (t_67) ? t_68 : t_61_y;
            nile_Real_t t_70_1 = t_65;
            nile_Real_t t_70_2 = t_69;
            nile_Real_t t_71_x = t_70_1;
            nile_Real_t t_71_y = t_70_2;
            nile_Real_t t_72 = nile_Real (0.1);
            nile_Real_t t_73_x = t_72;
            nile_Real_t t_73_y = t_72;
            nile_Real_t t_74_x = nile_Real_lt(t_71_x, t_73_x);
            nile_Real_t t_74_y = nile_Real_lt(t_71_y, t_73_y);
            nile_Real_t v_nearmin_x = t_74_x;
            nile_Real_t v_nearmin_y = t_74_y;
            nile_Real_t t_75_x = nile_Real_sub(v_ABBC_x, v_max_x);
            nile_Real_t t_75_y = nile_Real_sub(v_ABBC_y, v_max_y);
            nile_Real_t t_76 = nile_Real (0);
            nile_Real_t t_77 = nile_Real_lt(t_75_x, t_76);
            nile_Real_t t_78 = nile_Real_neg(t_75_x);
            nile_Real_t t_79 = nile_Real_nz (t_77) ? t_78 : t_75_x;
            nile_Real_t t_80 = nile_Real (0);
            nile_Real_t t_81 = nile_Real_lt(t_75_y, t_80);
            nile_Real_t t_82 = nile_Real_neg(t_75_y);
            nile_Real_t t_83 = nile_Real_nz (t_81) ? t_82 : t_75_y;
            nile_Real_t t_84_1 = t_79;
            nile_Real_t t_84_2 = t_83;
            nile_Real_t t_85_x = t_84_1;
            nile_Real_t t_85_y = t_84_2;
            nile_Real_t t_86 = nile_Real (0.1);
            nile_Real_t t_87_x = t_86;
            nile_Real_t t_87_y = t_86;
            nile_Real_t t_88_x = nile_Real_lt(t_85_x, t_87_x);
            nile_Real_t t_88_y = nile_Real_lt(t_85_y, t_87_y);
            nile_Real_t v_nearmax_x = t_88_x;
            nile_Real_t v_nearmax_y = t_88_y;
            nile_Real_t t_89_x = nile_Real_nz (v_nearmax_x) ? v_max_x : v_ABBC_x;
            nile_Real_t t_89_y = nile_Real_nz (v_nearmax_y) ? v_max_y : v_ABBC_y;
            nile_Real_t t_90_x = nile_Real_nz (v_nearmin_x) ? v_min_x : t_89_x;
            nile_Real_t t_90_y = nile_Real_nz (v_nearmin_y) ? v_min_y : t_89_y;
            nile_Real_t v_M_x = t_90_x;
            nile_Real_t v_M_y = t_90_y;
            nile_Real_t t_92 = nile_Real_add(v_B_x, v_C_x);
            nile_Real_t t_93 = nile_Real (2);
            nile_Real_t t_94 = nile_Real_div(t_92, t_93);
            nile_Real_t t_95 = nile_Real_add(v_B_y, v_C_y);
            nile_Real_t t_96 = nile_Real (2);
            nile_Real_t t_97 = nile_Real_div(t_95, t_96);
            nile_Real_t t_98_1 = t_94;
            nile_Real_t t_98_2 = t_97;
            nile_Real_t t_99_x = t_98_1;
            nile_Real_t t_99_y = t_98_2;
            nile_Real_t t_91_1_x = v_M_x;
            nile_Real_t t_91_1_y = v_M_y;
            nile_Real_t t_91_2_x = t_99_x;
            nile_Real_t t_91_2_y = t_99_y;
            nile_Real_t t_91_3_x = v_C_x;
            nile_Real_t t_91_3_y = v_C_y;
            nile_Real_t t_100_A_x = t_91_1_x;
            nile_Real_t t_100_A_y = t_91_1_y;
            nile_Real_t t_100_B_x = t_91_2_x;
            nile_Real_t t_100_B_y = t_91_2_y;
            nile_Real_t t_100_C_x = t_91_3_x;
            nile_Real_t t_100_C_y = t_91_3_y;
            if (nile_Buffer_headroom (in) < IN_QUANTUM)
                in = nile_Process_prefix_input (p, in);
            nile_Buffer_push_head(in, t_100_C_y);
            nile_Buffer_push_head(in, t_100_C_x);
            nile_Buffer_push_head(in, t_100_B_y);
            nile_Buffer_push_head(in, t_100_B_x);
            nile_Buffer_push_head(in, t_100_A_y);
            nile_Buffer_push_head(in, t_100_A_x);
            nile_Real_t t_102 = nile_Real_add(v_A_x, v_B_x);
            nile_Real_t t_103 = nile_Real (2);
            nile_Real_t t_104 = nile_Real_div(t_102, t_103);
            nile_Real_t t_105 = nile_Real_add(v_A_y, v_B_y);
            nile_Real_t t_106 = nile_Real (2);
            nile_Real_t t_107 = nile_Real_div(t_105, t_106);
            nile_Real_t t_108_1 = t_104;
            nile_Real_t t_108_2 = t_107;
            nile_Real_t t_109_x = t_108_1;
            nile_Real_t t_109_y = t_108_2;
            nile_Real_t t_101_1_x = v_A_x;
            nile_Real_t t_101_1_y = v_A_y;
            nile_Real_t t_101_2_x = t_109_x;
            nile_Real_t t_101_2_y = t_109_y;
            nile_Real_t t_101_3_x = v_M_x;
            nile_Real_t t_101_3_y = v_M_y;
            nile_Real_t t_110_A_x = t_101_1_x;
            nile_Real_t t_110_A_y = t_101_1_y;
            nile_Real_t t_110_B_x = t_101_2_x;
            nile_Real_t t_110_B_y = t_101_2_y;
            nile_Real_t t_110_C_x = t_101_3_x;
            nile_Real_t t_110_C_y = t_101_3_y;
            if (nile_Buffer_headroom (in) < IN_QUANTUM)
                in = nile_Process_prefix_input (p, in);
            nile_Buffer_push_head(in, t_110_C_y);
            nile_Buffer_push_head(in, t_110_C_x);
            nile_Buffer_push_head(in, t_110_B_y);
            nile_Buffer_push_head(in, t_110_B_x);
            nile_Buffer_push_head(in, t_110_A_y);
            nile_Buffer_push_head(in, t_110_A_x);
        }
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_DecomposeBeziers_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_DecomposeBeziers_vars_t *vars = nile_Process_vars (p);
    gezira_DecomposeBeziers_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_DecomposeBeziers (nile_Process_t *p)
{
    gezira_DecomposeBeziers_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_DecomposeBeziers_prologue, gezira_DecomposeBeziers_body, gezira_DecomposeBeziers_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 4

typedef struct {
    nile_Real_t v_x;
    nile_Real_t v_y;
    nile_Real_t v_A;
    nile_Real_t v_H;
} gezira_CombineEdgeSamples_vars_t;

static nile_Buffer_t *
gezira_CombineEdgeSamples_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CombineEdgeSamples_vars_t *vars = nile_Process_vars (p);
    gezira_CombineEdgeSamples_vars_t v = *vars;
    nile_Real_t t_5 = nile_Real (0);
    v.v_x = t_5;
    nile_Real_t t_6 = nile_Real (0);
    v.v_y = t_6;
    nile_Real_t t_7 = nile_Real (0);
    v.v_A = t_7;
    nile_Real_t t_8 = nile_Real (0);
    v.v_H = t_8;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CombineEdgeSamples_body (nile_Process_t *p,
                                nile_Buffer_t *in,
                                nile_Buffer_t *out)
{
    gezira_CombineEdgeSamples_vars_t *vars = nile_Process_vars (p);
    gezira_CombineEdgeSamples_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_CombineEdgeSamples_vars_t v_ = v;
        v_.v_x = nile_Buffer_pop_head(in);
        v_.v_y = nile_Buffer_pop_head(in);
        nile_Real_t v_a = nile_Buffer_pop_head(in);
        nile_Real_t v_h = nile_Buffer_pop_head(in);
        nile_Real_t t_9 = nile_Real_eq(v_.v_y, v.v_y);
        if (nile_Real_nz (t_9)) {
            nile_Real_t t_10 = nile_Real_eq(v_.v_x, v.v_x);
            if (nile_Real_nz (t_10)) {
                nile_Real_t t_11 = nile_Real_add(v.v_A, v_a);
                v_.v_A = t_11;
                nile_Real_t t_12 = nile_Real_add(v.v_H, v_h);
                v_.v_H = t_12;
            }
            else {
                nile_Real_t t_13 = nile_Real (0);
                nile_Real_t t_14 = nile_Real_lt(v.v_H, t_13);
                nile_Real_t t_15 = nile_Real_neg(v.v_H);
                nile_Real_t t_16 = nile_Real_nz (t_14) ? t_15 : v.v_H;
                nile_Real_t t_17 = nile_Real (0.5);
                nile_Real_t t_18 = nile_Real_gt(t_16, t_17);
                nile_Real_t t_19 = nile_Real_sub(v_.v_x, v.v_x);
                nile_Real_t t_20 = nile_Real (1);
                nile_Real_t t_21 = nile_Real_sub(t_19, t_20);
                nile_Real_t t_22 = nile_Real (0);
                nile_Real_t t_23 = nile_Real_nz (t_18) ? t_21 : t_22;
                nile_Real_t v_l = t_23;
                nile_Real_t t_25 = nile_Real (0);
                nile_Real_t t_26 = nile_Real_lt(v.v_A, t_25);
                nile_Real_t t_27 = nile_Real_neg(v.v_A);
                nile_Real_t t_28 = nile_Real_nz (t_26) ? t_27 : v.v_A;
                nile_Real_t t_29 = nile_Real (1);
                nile_Real_t t_30 = nile_Real_lt(t_28, t_29);
                nile_Real_t t_31 = nile_Real_nz (t_30) ? t_28 : t_29;
                nile_Real_t t_24_1 = v.v_x;
                nile_Real_t t_24_2 = v.v_y;
                nile_Real_t t_24_3 = t_31;
                nile_Real_t t_24_4 = v_l;
                nile_Real_t t_32_x = t_24_1;
                nile_Real_t t_32_y = t_24_2;
                nile_Real_t t_32_c = t_24_3;
                nile_Real_t t_32_l = t_24_4;
                if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                    out = nile_Process_append_output (p, out);
                nile_Buffer_push_tail(out, t_32_x);
                nile_Buffer_push_tail(out, t_32_y);
                nile_Buffer_push_tail(out, t_32_c);
                nile_Buffer_push_tail(out, t_32_l);
                nile_Real_t t_33 = nile_Real_add(v.v_H, v_a);
                v_.v_A = t_33;
                nile_Real_t t_34 = nile_Real_add(v.v_H, v_h);
                v_.v_H = t_34;
            }
        }
        else {
            nile_Real_t t_36 = nile_Real (0);
            nile_Real_t t_37 = nile_Real_lt(v.v_A, t_36);
            nile_Real_t t_38 = nile_Real_neg(v.v_A);
            nile_Real_t t_39 = nile_Real_nz (t_37) ? t_38 : v.v_A;
            nile_Real_t t_40 = nile_Real (1);
            nile_Real_t t_41 = nile_Real_lt(t_39, t_40);
            nile_Real_t t_42 = nile_Real_nz (t_41) ? t_39 : t_40;
            nile_Real_t t_43 = nile_Real (0);
            nile_Real_t t_35_1 = v.v_x;
            nile_Real_t t_35_2 = v.v_y;
            nile_Real_t t_35_3 = t_42;
            nile_Real_t t_35_4 = t_43;
            nile_Real_t t_44_x = t_35_1;
            nile_Real_t t_44_y = t_35_2;
            nile_Real_t t_44_c = t_35_3;
            nile_Real_t t_44_l = t_35_4;
            if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                out = nile_Process_append_output (p, out);
            nile_Buffer_push_tail(out, t_44_x);
            nile_Buffer_push_tail(out, t_44_y);
            nile_Buffer_push_tail(out, t_44_c);
            nile_Buffer_push_tail(out, t_44_l);
            v_.v_A = v_a;
            v_.v_H = v_h;
        }
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_CombineEdgeSamples_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_CombineEdgeSamples_vars_t *vars = nile_Process_vars (p);
    gezira_CombineEdgeSamples_vars_t v = *vars;
    nile_Real_t t_46 = nile_Real (0);
    nile_Real_t t_47 = nile_Real_lt(v.v_A, t_46);
    nile_Real_t t_48 = nile_Real_neg(v.v_A);
    nile_Real_t t_49 = nile_Real_nz (t_47) ? t_48 : v.v_A;
    nile_Real_t t_50 = nile_Real (1);
    nile_Real_t t_51 = nile_Real_lt(t_49, t_50);
    nile_Real_t t_52 = nile_Real_nz (t_51) ? t_49 : t_50;
    nile_Real_t t_53 = nile_Real (0);
    nile_Real_t t_45_1 = v.v_x;
    nile_Real_t t_45_2 = v.v_y;
    nile_Real_t t_45_3 = t_52;
    nile_Real_t t_45_4 = t_53;
    nile_Real_t t_54_x = t_45_1;
    nile_Real_t t_54_y = t_45_2;
    nile_Real_t t_54_c = t_45_3;
    nile_Real_t t_54_l = t_45_4;
    if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
        out = nile_Process_append_output (p, out);
    nile_Buffer_push_tail(out, t_54_x);
    nile_Buffer_push_tail(out, t_54_y);
    nile_Buffer_push_tail(out, t_54_c);
    nile_Buffer_push_tail(out, t_54_l);
    return out;
}

nile_Process_t *
gezira_CombineEdgeSamples (nile_Process_t *p)
{
    gezira_CombineEdgeSamples_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_CombineEdgeSamples_prologue, gezira_CombineEdgeSamples_body, gezira_CombineEdgeSamples_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 6
#define OUT_QUANTUM 4

typedef struct {
} gezira_Rasterize_vars_t;

static nile_Buffer_t *
gezira_Rasterize_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Rasterize_vars_t *vars = nile_Process_vars (p);
    gezira_Rasterize_vars_t v = *vars;
    ; /* no-op */
    nile_Real_t t_1 = nile_Real (0);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = nile_SortBy(p, nile_Real_toi (t_2), nile_Real_toi (t_1));
    nile_Real_t t_4 = nile_Real (1);
    nile_Real_t t_5 = nile_Real (4);
    nile_Process_t *t_6 = nile_SortBy(p, nile_Real_toi (t_5), nile_Real_toi (t_4));
    nile_Process_t *t_7 = nile_Process_pipe (t_6, gezira_CombineEdgeSamples(p), NILE_NULL);
    nile_Process_t *t_8 = nile_Process_pipe (t_3, t_7, NILE_NULL);
    nile_Process_t *t_9 = nile_Process_pipe (gezira_DecomposeBeziers(p), t_8, NILE_NULL);
    return nile_Process_swap (p, t_9, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_Rasterize_body (nile_Process_t *p,
                       nile_Buffer_t *in,
                       nile_Buffer_t *out)
{
    gezira_Rasterize_vars_t *vars = nile_Process_vars (p);
    gezira_Rasterize_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_Rasterize_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_Rasterize_vars_t *vars = nile_Process_vars (p);
    gezira_Rasterize_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_Rasterize (nile_Process_t *p)
{
    gezira_Rasterize_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_Rasterize_prologue, gezira_Rasterize_body, gezira_Rasterize_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 4

typedef struct {
} gezira_ExpandSpans_vars_t;

static nile_Buffer_t *
gezira_ExpandSpans_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ExpandSpans_vars_t *vars = nile_Process_vars (p);
    gezira_ExpandSpans_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ExpandSpans_body (nile_Process_t *p,
                         nile_Buffer_t *in,
                         nile_Buffer_t *out)
{
    gezira_ExpandSpans_vars_t *vars = nile_Process_vars (p);
    gezira_ExpandSpans_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ExpandSpans_vars_t v_ = v;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        nile_Real_t v_c = nile_Buffer_pop_head(in);
        nile_Real_t v_l = nile_Buffer_pop_head(in);
        if (nile_Real_nz (v_c)) {
            nile_Real_t t_2 = nile_Real (1);
            nile_Real_t t_3 = nile_Real_sub(t_2, v_c);
            nile_Real_t t_1_1 = v_x;
            nile_Real_t t_1_2 = v_y;
            nile_Real_t t_1_3 = v_c;
            nile_Real_t t_1_4 = t_3;
            nile_Real_t t_4_x = t_1_1;
            nile_Real_t t_4_y = t_1_2;
            nile_Real_t t_4_c = t_1_3;
            nile_Real_t t_4_ic = t_1_4;
            if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
                out = nile_Process_append_output (p, out);
            nile_Buffer_push_tail(out, t_4_x);
            nile_Buffer_push_tail(out, t_4_y);
            nile_Buffer_push_tail(out, t_4_c);
            nile_Buffer_push_tail(out, t_4_ic);
        }
        else {
            ; /* no-op */
        }
        nile_Real_t t_5 = nile_Real (0);
        nile_Real_t t_6 = nile_Real_gt(v_l, t_5);
        if (nile_Real_nz (t_6)) {
            nile_Real_t t_8 = nile_Real (1);
            nile_Real_t t_9 = nile_Real_add(v_x, t_8);
            nile_Real_t t_10 = nile_Real (1);
            nile_Real_t t_11 = nile_Real (1);
            nile_Real_t t_12 = nile_Real_sub(v_l, t_11);
            nile_Real_t t_7_1 = t_9;
            nile_Real_t t_7_2 = v_y;
            nile_Real_t t_7_3 = t_10;
            nile_Real_t t_7_4 = t_12;
            nile_Real_t t_13_x = t_7_1;
            nile_Real_t t_13_y = t_7_2;
            nile_Real_t t_13_c = t_7_3;
            nile_Real_t t_13_l = t_7_4;
            if (nile_Buffer_headroom (in) < IN_QUANTUM)
                in = nile_Process_prefix_input (p, in);
            nile_Buffer_push_head(in, t_13_l);
            nile_Buffer_push_head(in, t_13_c);
            nile_Buffer_push_head(in, t_13_y);
            nile_Buffer_push_head(in, t_13_x);
        }
        else {
            ; /* no-op */
        }
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ExpandSpans_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ExpandSpans_vars_t *vars = nile_Process_vars (p);
    gezira_ExpandSpans_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ExpandSpans (nile_Process_t *p)
{
    gezira_ExpandSpans_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ExpandSpans_prologue, gezira_ExpandSpans_body, gezira_ExpandSpans_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 2

typedef struct {
} gezira_ExtractSamplePoints_vars_t;

static nile_Buffer_t *
gezira_ExtractSamplePoints_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ExtractSamplePoints_vars_t *vars = nile_Process_vars (p);
    gezira_ExtractSamplePoints_vars_t v = *vars;
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ExtractSamplePoints_body (nile_Process_t *p,
                                 nile_Buffer_t *in,
                                 nile_Buffer_t *out)
{
    gezira_ExtractSamplePoints_vars_t *vars = nile_Process_vars (p);
    gezira_ExtractSamplePoints_vars_t v = *vars;
    
    while (!nile_Buffer_is_empty (in) && !nile_Buffer_quota_hit (out)) {
        gezira_ExtractSamplePoints_vars_t v_ = v;
        nile_Real_t t_1;
        nile_Real_t t_2;
        nile_Real_t v_x = nile_Buffer_pop_head(in);
        nile_Real_t v_y = nile_Buffer_pop_head(in);
        t_1 = nile_Buffer_pop_head(in);
        t_2 = nile_Buffer_pop_head(in);
        nile_Real_t t_3_1 = v_x;
        nile_Real_t t_3_2 = v_y;
        nile_Real_t t_4_x = t_3_1;
        nile_Real_t t_4_y = t_3_2;
        if (nile_Buffer_tailroom (out) < OUT_QUANTUM)
            out = nile_Process_append_output (p, out);
        nile_Buffer_push_tail(out, t_4_x);
        nile_Buffer_push_tail(out, t_4_y);
        v = v_;
    }
    
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ExtractSamplePoints_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ExtractSamplePoints_vars_t *vars = nile_Process_vars (p);
    gezira_ExtractSamplePoints_vars_t v = *vars;
    return out;
}

nile_Process_t *
gezira_ExtractSamplePoints (nile_Process_t *p)
{
    gezira_ExtractSamplePoints_vars_t *vars;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ExtractSamplePoints_prologue, gezira_ExtractSamplePoints_body, gezira_ExtractSamplePoints_epilogue);
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

#define IN_QUANTUM 4
#define OUT_QUANTUM 8

typedef struct {
    nile_Process_t *v_t;
} gezira_ApplyTexture_vars_t;

static nile_Buffer_t *
gezira_ApplyTexture_prologue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ApplyTexture_vars_t *vars = nile_Process_vars (p);
    gezira_ApplyTexture_vars_t v = *vars;
    ; /* no-op */
    nile_Process_t *t_1 = nile_Process_pipe (gezira_ExtractSamplePoints(p), v.v_t, NILE_NULL);
    nile_Real_t t_2 = nile_Real (4);
    nile_Process_t *t_3 = nile_Process_pipe (NILE_NULL);
    nile_Real_t t_4 = nile_Real (4);
    nile_Process_t *t_5 = nile_DupZip(p, t_1, nile_Real_toi (t_2), t_3, nile_Real_toi (t_4));
    nile_Process_t *t_6 = nile_Process_pipe (gezira_ExpandSpans(p), t_5, NILE_NULL);
    return nile_Process_swap (p, t_6, out);
    *vars = v;
    return out;
}

static nile_Buffer_t *
gezira_ApplyTexture_body (nile_Process_t *p,
                          nile_Buffer_t *in,
                          nile_Buffer_t *out)
{
    gezira_ApplyTexture_vars_t *vars = nile_Process_vars (p);
    gezira_ApplyTexture_vars_t v = *vars;
    
    return out;
}

static nile_Buffer_t *
gezira_ApplyTexture_epilogue (nile_Process_t *p, nile_Buffer_t *out)
{
    gezira_ApplyTexture_vars_t *vars = nile_Process_vars (p);
    gezira_ApplyTexture_vars_t v = *vars;
    ; /* no-op */
    return out;
}

nile_Process_t *
gezira_ApplyTexture (nile_Process_t *p, 
                     nile_Process_t *v_t)
{
    gezira_ApplyTexture_vars_t *vars;
    gezira_ApplyTexture_vars_t v;
    p = nile_Process (p, IN_QUANTUM, sizeof (*vars), gezira_ApplyTexture_prologue, gezira_ApplyTexture_body, gezira_ApplyTexture_epilogue);
    if (p) {
        vars = nile_Process_vars (p);
        v.v_t = v_t;
        *vars = v;
    }
    return p;
}

#undef IN_QUANTUM
#undef OUT_QUANTUM

