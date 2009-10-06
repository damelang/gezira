#include <stddef.h>
#include "gezira.h"

#define real nile_Real_t

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k)
{
    return &k->kernel;
}

nile_Kernel_t *
gezira_Compositor (gezira_Compositor_t *k)
{
    return &k->kernel;
}

nile_Kernel_t *
gezira_Canvas (gezira_Canvas_t *k,
               nile_Real_t start_x,
               nile_Real_t start_y)
{
    k->v_start_x = start_x;
    k->v_start_y = start_y;
    return &k->kernel;
}

/*
    CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
        → Interleave (s1, s2) → c
*/
static void
CompositeSamplers_process (nile_Context_t *c, nile_Kernel_t *k_,
                           nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 1
#define OUT_QUANTUM 4
    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    gezira_Sampler_t *v_s1 = k->v_s1;
    gezira_Sampler_t *v_s2 = k->v_s2;
    gezira_Compositor_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;
        k_->downstream =
            nile_pipeline (nile_Interleave (&k->p_1,
                                            gezira_Sampler (v_s1), 4,
                                            gezira_Sampler (v_s2), 4),
                           gezira_Compositor (v_c),
                           k_->downstream, NULL);
    }
    nile_forward (c, k_->downstream, in, out);
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Sampler_t *
gezira_CompositeSamplers (gezira_CompositeSamplers_t *k,
                          gezira_Sampler_t *s1,
                          gezira_Sampler_t *s2,
                          gezira_Compositor_t *c)
{
    k->sampler.kernel.process = CompositeSamplers_process;
    k->v_s1 = s1;
    k->v_s2 = s2;
    k->v_c = c;
    return &k->sampler;
}

/*
   UniformColor (c : Color) : Sampler
    ∀ _
        >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]
*/
static void
UniformColor_process (nile_Context_t *c, nile_Kernel_t *k_,
                      nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    real v_c_a = k->v_c_a;
    real v_c_r = k->v_c_r;
    real v_c_g = k->v_c_g;
    real v_c_b = k->v_c_b;
    nile_Buffer_t *o = *out;
    int i = 0;

    while (i < in->n) {
        real v___x = in->data[i + 0];
        real v___y = in->data[i + 1];
        i += IN_QUANTUM;
        real t_1_a = v_c_a;
        real t_1_r = nile_Real_mul (v_c_a, v_c_r);
        real t_1_g = nile_Real_mul (v_c_a, v_c_g);
        real t_1_b = nile_Real_mul (v_c_a, v_c_b);
        o->data[o->n + 0] = t_1_a;
        o->data[o->n + 1] = t_1_r;
        o->data[o->n + 2] = t_1_g;
        o->data[o->n + 3] = t_1_b;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
    }
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Sampler_t *
gezira_UniformColor (gezira_UniformColor_t *k,
                     nile_Real_t c_a, nile_Real_t c_r,
                     nile_Real_t c_g, nile_Real_t c_b)
{
    k->sampler.kernel.process = UniformColor_process;
    k->v_c_a = c_a;
    k->v_c_r = c_r;
    k->v_c_g = c_g;
    k->v_c_b = c_b;
    return &k->sampler;
}

/*
    CompositeOver : Compositor 
        ∀ [a, b] 
            >> a + b × (1 - a.a) 
*/
static void
CompositeOver_process (nile_Context_t *c, nile_Kernel_t *k_,
                       nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 8
#define OUT_QUANTUM 4
    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;
    nile_Buffer_t *o = *out;
    int i = 0;

    while (i < in->n) {
        real v_a_a = in->data[i + 0];
        real v_a_r = in->data[i + 1];
        real v_a_g = in->data[i + 2];
        real v_a_b = in->data[i + 3];
        real v_b_a = in->data[i + 4];
        real v_b_r = in->data[i + 5];
        real v_b_g = in->data[i + 6];
        real v_b_b = in->data[i + 7];
        i += IN_QUANTUM;
        real t_1_a = nile_Real_add (v_a_a, nile_Real_mul (v_b_a, nile_Real_sub (1, v_a_a)));
        real t_1_r = nile_Real_add (v_a_r, nile_Real_mul (v_b_r, nile_Real_sub (1, v_a_a)));
        real t_1_g = nile_Real_add (v_a_g, nile_Real_mul (v_b_g, nile_Real_sub (1, v_a_a)));
        real t_1_b = nile_Real_add (v_a_b, nile_Real_mul (v_b_b, nile_Real_sub (1, v_a_a)));
        o->data[o->n + 0] = t_1_a;
        o->data[o->n + 1] = t_1_r;
        o->data[o->n + 2] = t_1_g;
        o->data[o->n + 3] = t_1_b;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
    }
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Compositor_t *
gezira_CompositeOver (gezira_CompositeOver_t *k)
{
    k->compositor.kernel.process = CompositeOver_process;
    return &k->compositor;
}

/*
    FillBetweenEdges (start : Point) : EdgeContribution >> Real
        x = start.x
        local = 0
        run   = 0
        ∀ [[x', y], w, h]
            n = x' - x
            if n = 0
                local' = local + w × h
                run'   = run   + h
            else
                local' = run + w × h
                run'   = run + h
                >>        | local | ⋖ 1
                >(n - 1)> | run   | ⋖ 1
        if local ≠ 0
            >> | local | ⋖ 1
*/
static void
FillBetweenEdges_process (nile_Context_t *c, nile_Kernel_t *k_,
                          nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    real v_start_x = k->v_start_x;
    real v_start_y = k->v_start_y;
    real v_x = k->v_x;
    real v_local = k->v_local;
    real v_run = k->v_run;
    nile_Buffer_t *o = *out;
    int i = 0;

    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_start_x;
        v_local = 0;
        v_run = 0;
    }

    while (i < in->n) {
        real v_local_;
        real v_run_;
        real v_x_ = in->data[i + 0];
        real v_y = in->data[i + 1];
        real v_w = in->data[i + 2];
        real v_h = in->data[i + 3];
        i += IN_QUANTUM;
        real v_n = v_x_ - v_x;
        if (nile_Real_eq (v_n, 0)) {
            v_local_ = nile_Real_add (v_local, nile_Real_mul (v_w, v_h));
            v_run_ = nile_Real_add (v_run, v_h);
        }
        else {
            v_local_ = nile_Real_add (v_run, nile_Real_mul (v_w, v_h));
            v_run_ = nile_Real_add (v_run, v_h);
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            o->data[o->n + 0] = t_1;
            o->n += OUT_QUANTUM;
            if (o->capacity < o->n + OUT_QUANTUM) {
                nile_flush (c, k_->downstream, out);
                o = *out;
            }
            int n1 = nile_Real_sub (v_n, 1);
            for (;;) {
                int room = (o->capacity - o->n) / OUT_QUANTUM;
                int n2 = n1 < room ? n1 : room;
                int j;
                for (j = 0; j < n2; j++) {
                    real t_2 = nile_Real_min (nile_Real_abs (v_run), 1);
                    o->data[o->n + 0] = t_2;
                    o->n += OUT_QUANTUM;
                }
                n1 -= n2;
                if (n1 == 0)
                    break;
                nile_flush (c, k_->downstream, out);
                o = *out;
            }
        }
        v_x = v_x_;
        v_local = v_local_;
        v_run = v_run_;
    }

    if (in->eos) {
        if (nile_Real_neq (v_local, 0)) {
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            o->data[o->n + 0] = t_1;
            o->n += OUT_QUANTUM;
        }
    }
    else {
        k->v_x = v_x;
        k->v_local = v_local;
        k->v_run = v_run;
    }
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_FillBetweenEdges (gezira_FillBetweenEdges_t *k,
                         nile_Real_t start_x,
                         nile_Real_t start_y)
{
    k->kernel.process = FillBetweenEdges_process;
    k->v_start_x = start_x;
    k->v_start_y = start_y;
    return &k->kernel;
}

/*
    CreateSamplePoints (start : Point) : Real >> Point
        x = start.x
        y = start.y
        ∀ _
            x' = x + 1
            >> [x, y]
*/
static void
CreateSamplePoints_process (nile_Context_t *c, nile_Kernel_t *k_,
                             nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 1
#define OUT_QUANTUM 2
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    real v_start_x = k->v_start_x;
    real v_start_y = k->v_start_y;
    real v_x = k->v_x;
    real v_y = k->v_y;
    nile_Buffer_t *o = *out;
    int i = 0;

    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_start_x;
        v_y = v_start_y;
    }

    while (i < in->n) {
        real v_x_;
        real v__ = in->data[i + 0];
        i += IN_QUANTUM;
        v_x_ = nile_Real_add (v_x, 1);
        o->data[o->n + 0] = v_x;
        o->data[o->n + 1] = v_y;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
        v_x = v_x_;
    }

    if (in->eos) {
    }
    else {
        k->v_x = v_x;
        k->v_y = v_y;
    }
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_CreateSamplePoints (gezira_CreateSamplePoints_t *k,
                           nile_Real_t start_x,
                           nile_Real_t start_y)
{
    k->kernel.process = CreateSamplePoints_process;
    k->v_start_x = start_x;
    k->v_start_y = start_y;
    return &k->kernel;
}

/*
    & [p, _, _]
        → FillBetweenEdges (p) →
          Interleave (→ CreateSamplePoints (p + 0.5) → s, Id) →
          c (p + 0.5)
*/
static void
Render_1_process (nile_Context_t *c, nile_Kernel_t *k_,
                  nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    gezira_Render_1_t *k = (gezira_Render_1_t *) k_;
    gezira_Sampler_t *v_s = k->v_s;
    gezira_Canvas_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;
        real v_p_x = in->data[0];
        real v_p_y = in->data[1];
        real v__ = in->data[2];
        //real v__ = in->data[3];
        real t_1_x = nile_Real_add (v_p_x, 0.5);
        real t_1_y = nile_Real_add (v_p_y, 0.5);
        /* FIXME problem here, I want nile_combine or something here instead of nile_pipeline */
        nile_Kernel_t *t_2 = nile_pipeline (gezira_CreateSamplePoints (&k->p_3, t_1_x, t_1_y),
                                            gezira_Sampler (v_s), NULL);
        k_->downstream =
            nile_pipeline (gezira_FillBetweenEdges (&k->p_1, v_p_x, v_p_y),
                           nile_Interleave (&k->p_2, t_2, 4, nile_Id (&k->p_4), 1),
                           gezira_Canvas (v_c, t_1_x, t_1_y),
                           k_->downstream, NULL);
    }
    nile_forward (c, k_->downstream, in, out);
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render_1 (gezira_Render_1_t *k,
                 gezira_Sampler_t *s,
                 gezira_Canvas_t *c)
{
    k->kernel.process = Render_1_process;
    k->v_s = s;
    k->v_c = c;
    return &k->kernel;
}

/*
    Render (s : Sampler, c : Canvas) : EdgeContribution >>|
        → GroupBy (@p.y) → SortBy (@p.x) → Render_1 (s, c)
*/
static void
Render_process (nile_Context_t *c, nile_Kernel_t *k_,
                nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    gezira_Render_t *k = (gezira_Render_t *) k_;
    gezira_Sampler_t *v_s = k->v_s;
    gezira_Canvas_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;
        k_->downstream =
            nile_pipeline (nile_GroupBy (&k->p_1, 1, 4),
                           nile_SortBy (&k->p_2, 0, 4),
                           gezira_Render_1 (&k->p_3, v_s, v_c),
                           k_->downstream, NULL);
    }
    nile_forward (c, k_->downstream, in, out);
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render (gezira_Render_t *k,
               gezira_Sampler_t *s,
               gezira_Canvas_t *c)
{
    k->kernel.process = Render_process;
    k->v_s = s;
    k->v_c = c;
    return &k->kernel;
}

/*
    TransformBezier (m : Matrix) : Bezier >> Bezier
        ∀ [a, b, c]
            >> [m × a, m × b, m × c]
*/
static void
TransformBezier_process (nile_Context_t *c, nile_Kernel_t *k_,
                         nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    gezira_TransformBezier_t *k = (gezira_TransformBezier_t *) k_;
    real v_m_a = k->v_m_a;
    real v_m_b = k->v_m_b;
    real v_m_c = k->v_m_c;
    real v_m_d = k->v_m_d;
    real v_m_e = k->v_m_e;
    real v_m_f = k->v_m_f;
    nile_Buffer_t *o = *out;
    int i = 0;

    while (i < in->n) {
        real v_a_x = in->data[i + 0];
        real v_a_y = in->data[i + 1];
        real v_b_x = in->data[i + 2];
        real v_b_y = in->data[i + 3];
        real v_c_x = in->data[i + 4];
        real v_c_y = in->data[i + 5];
        i += IN_QUANTUM;
        real t_1_x = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_a, v_a_x),
                                                   nile_Real_mul (v_m_c, v_a_y)), v_m_e);
        real t_1_y = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_b, v_a_x),
                                                   nile_Real_mul (v_m_d, v_a_y)), v_m_f);
        real t_2_x = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_a, v_b_x),
                                                   nile_Real_mul (v_m_c, v_b_y)), v_m_e);
        real t_2_y = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_b, v_b_x),
                                                   nile_Real_mul (v_m_d, v_b_y)), v_m_f);
        real t_3_x = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_a, v_c_x),
                                                   nile_Real_mul (v_m_c, v_c_y)), v_m_e);
        real t_3_y = nile_Real_add (nile_Real_add (nile_Real_mul (v_m_b, v_c_x),
                                                   nile_Real_mul (v_m_d, v_c_y)), v_m_f);
        o->data[o->n + 0] = t_1_x;
        o->data[o->n + 1] = t_1_y;
        o->data[o->n + 2] = t_2_x;
        o->data[o->n + 3] = t_2_y;
        o->data[o->n + 4] = t_3_x;
        o->data[o->n + 5] = t_3_y;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
    }
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_TransformBezier (gezira_TransformBezier_t *k,
                        nile_Real_t m_a,
                        nile_Real_t m_b,
                        nile_Real_t m_c,
                        nile_Real_t m_d,
                        nile_Real_t m_e,
                        nile_Real_t m_f)
{
    k->kernel.process = TransformBezier_process;
    k->v_m_a = m_a;
    k->v_m_b = m_b;
    k->v_m_c = m_c;
    k->v_m_d = m_d;
    k->v_m_e = m_e;
    k->v_m_f = m_f;
    return &k->kernel;
}

static void
ClipBezier_process (nile_Context_t *c, nile_Kernel_t *k_,
                    nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

nile_Kernel_t *
gezira_ClipBezier (gezira_ClipBezier_t *k,
                   nile_Real_t min_x,
                   nile_Real_t min_y,
                   nile_Real_t max_x,
                   nile_Real_t max_y)
{
    k->kernel.process = ClipBezier_process;
    k->v_min_x = min_x;
    k->v_min_y = min_y;
    k->v_max_x = max_x;
    k->v_max_y = max_y;
    return &k->kernel;
}

static void
DecomposeBezier_process (nile_Context_t *c, nile_Kernel_t *k_,
                         nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

nile_Kernel_t *
gezira_DecomposeBezier (gezira_DecomposeBezier_t *k)
{
    k->kernel.process = DecomposeBezier_process;
    return &k->kernel;
}
