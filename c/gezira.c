#include <stddef.h>
#include "gezira.h"

#define real nile_Real_t

/*
    Canvas :: (start : Point) : [Color, Real] >>|
*/

nile_Kernel_t *
gezira_Canvas (nile_t *nl, nile_Kernel_t *k_,
               nile_Real_t v_start_x,
               nile_Real_t v_start_y)
{
    gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return k_;
}

nile_Kernel_t *
gezira_Canvas_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
    gezira_Canvas_t *clone =
        (gezira_Canvas_t *) nile_Kernel_clone (nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return (nile_Kernel_t *) clone;
}

/*
    CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
        ⇒ Interleave (s1, s2) → c
*/

typedef struct {
    nile_Kernel_t base;
    nile_Kernel_t *v_s1;
    nile_Kernel_t *v_s2;
    nile_Kernel_t *v_c;
} gezira_CompositeSamplers_t;

static nile_Kernel_t *
gezira_CompositeSamplers_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    gezira_CompositeSamplers_t *clone =
        (gezira_CompositeSamplers_t *) nile_Kernel_clone (nl, k_);
    clone->v_s1 = k->v_s1->clone (nl, k->v_s1);
    clone->v_s2 = k->v_s2->clone (nl, k->v_s2);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

static int
gezira_CompositeSamplers_process (nile_t *nl, nile_Kernel_t *k_,
                                  nile_Buffer_t **in_, nile_Buffer_t **out_)
{
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

        nile_Kernel_t *f =
            nile_Pipeline (nl,
                nile_Interleave (nl, v_s1, 4, v_s2, 4), v_c, NULL);

        f->downstream = k_->downstream;
        k_->downstream = f;
    }

    return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_CompositeSamplers (nile_t *nl,
                          nile_Kernel_t *v_s1,
                          nile_Kernel_t *v_s2,
                          nile_Kernel_t *v_c)
{
    gezira_CompositeSamplers_t *k = NILE_KERNEL_NEW (nl, gezira_CompositeSamplers);
    k->v_s1 = v_s1;
    k->v_s2 = v_s2;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

/*
   UniformColor (c : Color) : Sampler
       ∀ p
           >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]
*/

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_c_a;
    nile_Real_t v_c_r;
    nile_Real_t v_c_g;
    nile_Real_t v_c_b;
} gezira_UniformColor_t;

static nile_Kernel_t *
gezira_UniformColor_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    gezira_UniformColor_t *clone =
        (gezira_UniformColor_t *) nile_Kernel_clone (nl, k_);
    clone->v_c_a = k->v_c_a;
    clone->v_c_r = k->v_c_r;
    clone->v_c_g = k->v_c_g;
    clone->v_c_b = k->v_c_b;
    return (nile_Kernel_t *) clone;
}

static int
gezira_UniformColor_process (nile_t *nl, nile_Kernel_t *k_,
                             nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    real v_c_a = k->v_c_a;
    real v_c_r = k->v_c_r;
    real v_c_g = k->v_c_g;
    real v_c_b = k->v_c_b;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (in->i < in->n) {
        real v_p_x = nile_Buffer_shift (in);
        real v_p_y = nile_Buffer_shift (in);
        real t_1_a = v_c_a;
        real t_1_r = nile_Real_mul (v_c_a, v_c_r);
        real t_1_g = nile_Real_mul (v_c_a, v_c_g);
        real t_1_b = nile_Real_mul (v_c_a, v_c_b);
        out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append (out, t_1_a);
        nile_Buffer_append (out, t_1_r);
        nile_Buffer_append (out, t_1_g);
        nile_Buffer_append (out, t_1_b);
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

nile_Kernel_t *
gezira_UniformColor (nile_t *nl,
                     nile_Real_t c_a,
                     nile_Real_t c_r,
                     nile_Real_t c_g,
                     nile_Real_t c_b)
{
    gezira_UniformColor_t *k = NILE_KERNEL_NEW (nl, gezira_UniformColor);
    k->v_c_a = c_a;
    k->v_c_r = c_r;
    k->v_c_g = c_g;
    k->v_c_b = c_b;
    return (nile_Kernel_t *) k;
}

/*
    CompositeOver : Compositor 
        ∀ [a, b] 
            >> a + b × (1 - a.a) 
*/

typedef struct {
    nile_Kernel_t base;
} gezira_CompositeOver_t;

static nile_Kernel_t *
gezira_CompositeOver_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;
    gezira_CompositeOver_t *clone =
        (gezira_CompositeOver_t *) nile_Kernel_clone (nl, k_);
    return (nile_Kernel_t *) clone;
}

static int
gezira_CompositeOver_process (nile_t *nl, nile_Kernel_t *k_,
                              nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 8
#define OUT_QUANTUM 4
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (in->i < in->n) {
        real v_a_a = nile_Buffer_shift (in);
        real v_a_r = nile_Buffer_shift (in);
        real v_a_g = nile_Buffer_shift (in);
        real v_a_b = nile_Buffer_shift (in);
        real v_b_a = nile_Buffer_shift (in);
        real v_b_r = nile_Buffer_shift (in);
        real v_b_g = nile_Buffer_shift (in);
        real v_b_b = nile_Buffer_shift (in);
        real t_1_a = nile_Real_add (v_a_a, nile_Real_mul (v_b_a, nile_Real_sub (1, v_a_a)));
        real t_1_r = nile_Real_add (v_a_r, nile_Real_mul (v_b_r, nile_Real_sub (1, v_a_a)));
        real t_1_g = nile_Real_add (v_a_g, nile_Real_mul (v_b_g, nile_Real_sub (1, v_a_a)));
        real t_1_b = nile_Real_add (v_a_b, nile_Real_mul (v_b_b, nile_Real_sub (1, v_a_a)));
        out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append (out, t_1_a);
        nile_Buffer_append (out, t_1_r);
        nile_Buffer_append (out, t_1_g);
        nile_Buffer_append (out, t_1_b);
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

nile_Kernel_t *
gezira_CompositeOver (nile_t *nl)
{
    gezira_CompositeOver_t *k = NILE_KERNEL_NEW (nl, gezira_CompositeOver);
    return (nile_Kernel_t *) k;
}

/*
    FillBetweenEdges (x0 : Real) : EdgeContribution >> Real
        x = x0
        local = 0
        run   = 0
        ∀ [x', y, w, h]
            n = x' - x
            run' = run + h
            if n = 0
                local' = local + w × h
            else
                local' = run + w × h
                >>        | local | ⋖ 1
                >(n - 1)> | run   | ⋖ 1
        if local ≠ 0
            >> | local | ⋖ 1
*/

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_x0;
    nile_Real_t v_x;
    nile_Real_t v_local;
    nile_Real_t v_run;
} gezira_FillBetweenEdges_t;

static nile_Kernel_t *
gezira_FillBetweenEdges_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    gezira_FillBetweenEdges_t *clone =
        (gezira_FillBetweenEdges_t *) nile_Kernel_clone (nl, k_);
    clone->v_x0 = k->v_x0;
    return (nile_Kernel_t *) clone;
}

static int
gezira_FillBetweenEdges_process (nile_t *nl, nile_Kernel_t *k_,
                                 nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    real v_x0 = k->v_x0;
    real v_x = k->v_x;
    real v_local = k->v_local;
    real v_run = k->v_run;

    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_x0;
        v_local = 0;
        v_run = 0;
    }

    while (in->i < in->n) {
        real v_local_;
        real v_run_;
        real v_x_;
             v_x_ = nile_Buffer_shift (in);
        real v_y  = nile_Buffer_shift (in);
        real v_w  = nile_Buffer_shift (in);
        real v_h  = nile_Buffer_shift (in);
        real v_n = v_x_ - v_x;
        v_run_ = nile_Real_add (v_run, v_h);
        if (nile_Real_eq (v_n, 0)) {
            v_local_ = nile_Real_add (v_local, nile_Real_mul (v_w, v_h));
        }
        else {
            v_local_ = nile_Real_add (v_run, nile_Real_mul (v_w, v_h));
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append (out, t_1);
            out = nile_Buffer_append_repeat (nl, out,
                                             nile_Real_min (nile_Real_abs (v_run), 1),
                                             nile_Real_sub (v_n, 1), k_);
        }
        v_x = v_x_;
        v_local = v_local_;
        v_run = v_run_;
    }

    if (in->eos) {
        if (nile_Real_neq (v_local, 0)) {
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append (out, t_1);
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

nile_Kernel_t *
gezira_FillBetweenEdges (nile_t *nl,
                         nile_Real_t v_x0)
{
    gezira_FillBetweenEdges_t *k = NILE_KERNEL_NEW (nl, gezira_FillBetweenEdges);
    k->v_x0 = v_x0;
    return (nile_Kernel_t *) k;
}

/*
    CreateSamplePoints (start : Point) : Real >> Point
        x = start.x
        y = start.y
        ∀ c
            x' = x + 1
            >> [x, y]
*/

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
    nile_Real_t v_x;
    nile_Real_t v_y;
} gezira_CreateSamplePoints_t;

static nile_Kernel_t *
gezira_CreateSamplePoints_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    gezira_CreateSamplePoints_t *clone =
        (gezira_CreateSamplePoints_t *) nile_Kernel_clone (nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return (nile_Kernel_t *) clone;
}

static int
gezira_CreateSamplePoints_process (nile_t *nl, nile_Kernel_t *k_,
                                   nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 1
#define OUT_QUANTUM 2
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    real v_start_x = k->v_start_x;
    real v_start_y = k->v_start_y;
    real v_x = k->v_x;
    real v_y = k->v_y;

    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_start_x;
        v_y = v_start_y;
    }

    while (in->i < in->n) {
        real v_x_;
        real v_c = nile_Buffer_shift (in);
        v_x_ = nile_Real_add (v_x, 1);
        out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append (out, v_x);
        nile_Buffer_append (out, v_y);
        v_x = v_x_;
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

nile_Kernel_t *
gezira_CreateSamplePoints (nile_t *nl,
                           nile_Real_t v_start_x,
                           nile_Real_t v_start_y)
{
    gezira_CreateSamplePoints_t *k = NILE_KERNEL_NEW (nl, gezira_CreateSamplePoints);
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return (nile_Kernel_t *) k;
}

/*
    Render' (s : Sampler, c : Canvas) : EdgeContribution >>|
        & [x, y, w, h]
            p = [x, y] + 0.5
            ⇒ FillBetweenEdges (x) →
              Interleave (CreateSamplePoints (p) → s, (→)) →
              c (p)
*/

typedef struct {
    nile_Kernel_t base;
    nile_Kernel_t *v_s;
    nile_Kernel_t *v_c;
} gezira_Render__t;

static nile_Kernel_t *
gezira_Render__clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_Render__t *k = (gezira_Render__t *) k_;
    gezira_Render__t *clone =
        (gezira_Render__t *) nile_Kernel_clone (nl, k_);
    clone->v_s = k->v_s->clone (nl, k->v_s);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

static int
gezira_Render__process (nile_t *nl, nile_Kernel_t *k_,
                        nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_Render__t *k = (gezira_Render__t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    nile_Kernel_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;
        real v_x = nile_Buffer_peek (in, 0);
        real v_y = nile_Buffer_peek (in, 1);
        real v_w = nile_Buffer_peek (in, 2);
        real v_h = nile_Buffer_peek (in, 3);
        real v_p_0 = nile_Real_add (v_x, 0.5);
        real v_p_1 = nile_Real_add (v_y, 0.5);

        nile_Kernel_t *f = nile_Pipeline (nl,
            gezira_FillBetweenEdges (nl, v_x),
            nile_Interleave (nl,
                nile_Pipeline (nl,
                    gezira_CreateSamplePoints (nl, v_p_0, v_p_1), v_s, NULL),
                4,
                nile_Pipeline (nl, NULL),
                1),
            gezira_Canvas (nl, v_c, v_p_0, v_p_1), NULL);

        f->downstream = k_->downstream;
        k_->downstream = f;
    }

    return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render_ (nile_t *nl,
                nile_Kernel_t *v_s,
                nile_Kernel_t *v_c)
{
    gezira_Render__t *k = NILE_KERNEL_NEW (nl, gezira_Render_);
    k->v_s = v_s;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

/*
    Render (s : Sampler, c : Canvas) : EdgeContribution >>|
        ⇒ GroupBy (@y) → (SortBy (@x) → Render' (s, c))
*/

typedef struct {
    nile_Kernel_t base;
    nile_Kernel_t *v_s;
    nile_Kernel_t *v_c;
} gezira_Render_t;

static nile_Kernel_t *
gezira_Render_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_Render_t *k = (gezira_Render_t *) k_;
    gezira_Render_t *clone =
        (gezira_Render_t *) nile_Kernel_clone (nl, k_);
    clone->v_s = k->v_s->clone (nl, k->v_s);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return (nile_Kernel_t *) clone;
}

static int
gezira_Render_process (nile_t *nl, nile_Kernel_t *k_,
                       nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_Render_t *k = (gezira_Render_t *) k_;
    nile_Kernel_t *v_s = k->v_s;
    nile_Kernel_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;

        nile_Kernel_t *f = nile_Pipeline (nl,
            nile_GroupBy (nl, 1, 4),
            nile_Pipeline (nl,
                nile_SortBy (nl, 0, 4),
                gezira_Render_ (nl, v_s, v_c),
                NULL),
            NULL);

        f->downstream = k_->downstream;
        k_->downstream = f;
    }

    return NILE_INPUT_FORWARD;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render (nile_t *nl,
               nile_Kernel_t *v_s,
               nile_Kernel_t *v_c)
{
    gezira_Render_t *k = NILE_KERNEL_NEW (nl, gezira_Render);
    k->v_s = v_s;
    k->v_c = v_c;
    return (nile_Kernel_t *) k;
}

/*
    TransformBeziers (m : Matrix) : Bezier >> Bezier
        ∀ [a, b, c]
            >> [m × a, m × b, m × c]
*/

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_m_a;
    nile_Real_t v_m_b;
    nile_Real_t v_m_c;
    nile_Real_t v_m_d;
    nile_Real_t v_m_e;
    nile_Real_t v_m_f;
} gezira_TransformBeziers_t;

static nile_Kernel_t *
gezira_TransformBeziers_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_TransformBeziers_t *k = (gezira_TransformBeziers_t *) k_;
    gezira_TransformBeziers_t *clone =
        (gezira_TransformBeziers_t *) nile_Kernel_clone (nl, k_);
    clone->v_m_a = k->v_m_a; 
    clone->v_m_b = k->v_m_b; 
    clone->v_m_c = k->v_m_c; 
    clone->v_m_d = k->v_m_d; 
    clone->v_m_e = k->v_m_e; 
    clone->v_m_f = k->v_m_f; 
    return (nile_Kernel_t *) clone;
}

static int
gezira_TransformBeziers_process (nile_t *nl, nile_Kernel_t *k_,
                                nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_TransformBeziers_t *k = (gezira_TransformBeziers_t *) k_;
    real v_m_a = k->v_m_a;
    real v_m_b = k->v_m_b;
    real v_m_c = k->v_m_c;
    real v_m_d = k->v_m_d;
    real v_m_e = k->v_m_e;
    real v_m_f = k->v_m_f;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (in->i < in->n) {
        real v_a_x = nile_Buffer_shift (in);
        real v_a_y = nile_Buffer_shift (in);
        real v_b_x = nile_Buffer_shift (in);
        real v_b_y = nile_Buffer_shift (in);
        real v_c_x = nile_Buffer_shift (in);
        real v_c_y = nile_Buffer_shift (in);
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
        out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
        nile_Buffer_append (out, t_1_x);
        nile_Buffer_append (out, t_1_y);
        nile_Buffer_append (out, t_2_x);
        nile_Buffer_append (out, t_2_y);
        nile_Buffer_append (out, t_3_x);
        nile_Buffer_append (out, t_3_y);
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

nile_Kernel_t *
gezira_TransformBeziers (nile_t *nl,
                        nile_Real_t v_m_a,
                        nile_Real_t v_m_b,
                        nile_Real_t v_m_c,
                        nile_Real_t v_m_d,
                        nile_Real_t v_m_e,
                        nile_Real_t v_m_f)
{
    gezira_TransformBeziers_t *k = NILE_KERNEL_NEW (nl, gezira_TransformBeziers);
    k->v_m_a = v_m_a;
    k->v_m_b = v_m_b;
    k->v_m_c = v_m_c;
    k->v_m_d = v_m_d;
    k->v_m_e = v_m_e;
    k->v_m_f = v_m_f;
    return (nile_Kernel_t *) k;
}

/*
    ClipBeziers (min, max : Point) : Bezier >> Bezier
        ∀ [a, b, c]
            bmin = a ⋖ b ⋖ c
            bmax = a ⋗ b ⋗ c
            if ∧[ min ≤ bmin ∧ bmax ≤ max ]
                >> [a, b, c]
            else if ∨[ bmax ≤ min ∨ max ≤ bmin ]
                ca = min ⋗ a ⋖ max
                cc = min ⋗ c ⋖ max
                >> [ca, ca ~ cc, cc]
            else 
                abbc    = (a ~ b) ~ (b ~ c)
                nearmin = | abbc - min | < 0.1
                nearmax = | abbc - max | < 0.1
                m       = min ?(nearmin)? (max ?(nearmax)? abbc)
                << [a, a ~ b, m] << [m, b ~ c, c]
*/

typedef struct {
    nile_Kernel_t base;
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_ClipBeziers_t;

static nile_Kernel_t *
gezira_ClipBeziers_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_ClipBeziers_t *k = (gezira_ClipBeziers_t *) k_;
    gezira_ClipBeziers_t *clone =
        (gezira_ClipBeziers_t *) nile_Kernel_clone (nl, k_);
    clone->v_min_x = k->v_min_x;
    clone->v_min_y = k->v_min_y;
    clone->v_max_x = k->v_max_x;
    clone->v_max_y = k->v_max_y;
    return (nile_Kernel_t *) clone;
}

static int
gezira_ClipBeziers_process (nile_t *nl, nile_Kernel_t *k_,
                           nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_ClipBeziers_t *k = (gezira_ClipBeziers_t *) k_;
    real v_min_x = k->v_min_x;
    real v_min_y = k->v_min_y;
    real v_max_x = k->v_max_x;
    real v_max_y = k->v_max_y;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (in->i < in->n) {
        real v_a_x = nile_Buffer_shift (in);
        real v_a_y = nile_Buffer_shift (in);
        real v_b_x = nile_Buffer_shift (in);
        real v_b_y = nile_Buffer_shift (in);
        real v_c_x = nile_Buffer_shift (in);
        real v_c_y = nile_Buffer_shift (in);
        real v_bmin_x = nile_Real_min (v_a_x, nile_Real_min (v_b_x, v_c_x));
        real v_bmin_y = nile_Real_min (v_a_y, nile_Real_min (v_b_y, v_c_y));
        real v_bmax_x = nile_Real_max (v_a_x, nile_Real_max (v_b_x, v_c_x));
        real v_bmax_y = nile_Real_max (v_a_y, nile_Real_max (v_b_y, v_c_y));
        real t_1_0 = nile_Real_leq (v_min_x, v_bmin_x);
        real t_1_1 = nile_Real_leq (v_min_y, v_bmin_y);
        real t_2_0 = nile_Real_leq (v_bmax_x, v_max_x);
        real t_2_1 = nile_Real_leq (v_bmax_y, v_max_y);
        real t_3_0 = nile_Real_and (t_1_0, t_2_0);
        real t_3_1 = nile_Real_and (t_1_1, t_2_1);
        real t_4 = nile_Real_and (t_3_0, t_3_1);
        if (t_4) {
            out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append (out, v_a_x);
            nile_Buffer_append (out, v_a_y);
            nile_Buffer_append (out, v_b_x);
            nile_Buffer_append (out, v_b_y);
            nile_Buffer_append (out, v_c_x);
            nile_Buffer_append (out, v_c_y);
        }
        else {
            real t_5_0 = nile_Real_leq (v_bmax_x, v_min_x);
            real t_5_1 = nile_Real_leq (v_bmax_y, v_min_y);
            real t_6_0 = nile_Real_leq (v_max_x, v_bmin_x);
            real t_6_1 = nile_Real_leq (v_max_y, v_bmin_y);
            real t_7_0 = nile_Real_or (t_5_0, t_6_0);
            real t_7_1 = nile_Real_or (t_5_1, t_6_1);
            real t_8 = nile_Real_or (t_7_0, t_7_1);
            if (t_8) {
                real v_ca_x = nile_Real_min (nile_Real_max (v_min_x, v_a_x), v_max_x);
                real v_ca_y = nile_Real_min (nile_Real_max (v_min_y, v_a_y), v_max_y);
                real v_cc_x = nile_Real_min (nile_Real_max (v_min_x, v_c_x), v_max_x);
                real v_cc_y = nile_Real_min (nile_Real_max (v_min_y, v_c_y), v_max_y);
                out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
                nile_Buffer_append (out, v_ca_x);
                nile_Buffer_append (out, v_ca_y);
                nile_Buffer_append (out, nile_Real_ave (v_ca_x, v_cc_x));
                nile_Buffer_append (out, nile_Real_ave (v_ca_y, v_cc_y));
                nile_Buffer_append (out, v_cc_x);
                nile_Buffer_append (out, v_cc_y);
            }
            else {
                real v_abbc_x = nile_Real_ave (nile_Real_ave (v_a_x, v_b_x),
                                               nile_Real_ave (v_b_x, v_c_x));
                real v_abbc_y = nile_Real_ave (nile_Real_ave (v_a_y, v_b_y),
                                               nile_Real_ave (v_b_y, v_c_y));
                real v_nearmin_x =
                    nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_x, v_min_x)), 0.1);
                real v_nearmin_y =
                    nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_y, v_min_y)), 0.1);
                real v_nearmax_x =
                    nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_x, v_max_x)), 0.1);
                real v_nearmax_y =
                    nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_y, v_max_y)), 0.1);
                real v_m_x = nile_Real_sel (v_min_x, v_nearmin_x,
                             nile_Real_sel (v_max_x, v_nearmax_x, v_abbc_x));
                real v_m_y = nile_Real_sel (v_min_y, v_nearmin_y,
                             nile_Real_sel (v_max_y, v_nearmax_y, v_abbc_y));

                in = nile_Buffer_prepare_to_prepend (nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend (in, v_a_x);
                nile_Buffer_prepend (in, v_a_y);
                nile_Buffer_prepend (in, nile_Real_ave (v_a_x, v_b_x));
                nile_Buffer_prepend (in, nile_Real_ave (v_a_y, v_b_y));
                nile_Buffer_prepend (in, v_m_x);
                nile_Buffer_prepend (in, v_m_y);
                in->i -= IN_QUANTUM;

                in = nile_Buffer_prepare_to_prepend (nl, in, IN_QUANTUM, k_);
                nile_Buffer_prepend (in, v_m_x);
                nile_Buffer_prepend (in, v_m_y);
                nile_Buffer_prepend (in, nile_Real_ave (v_b_x, v_c_x));
                nile_Buffer_prepend (in, nile_Real_ave (v_b_y, v_c_y));
                nile_Buffer_prepend (in, v_c_x);
                nile_Buffer_prepend (in, v_c_y);
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

nile_Kernel_t *
gezira_ClipBeziers (nile_t *nl,
                   nile_Real_t v_min_x,
                   nile_Real_t v_min_y,
                   nile_Real_t v_max_x,
                   nile_Real_t v_max_y)
{
    gezira_ClipBeziers_t *k = NILE_KERNEL_NEW (nl, gezira_ClipBeziers);
    k->v_min_x = v_min_x;
    k->v_min_y = v_min_y;
    k->v_max_x = v_max_x;
    k->v_max_y = v_max_y;
    return (nile_Kernel_t *) k;
}

/*
    DecomposeBeziers : Bezier >> EdgeContribution
        ∀ [a, b, c]
            if ∧[ ⌊ a ⌋ = ⌊ c ⌋ ∨ ⌈ a ⌉ = ⌈ c ⌉ ]
                p = ⌊ a ⌋ ⋖ ⌊ c ⌋
                w = p.x + 1 - (c.x ~ a.x)
                h = c.y - a.y
                >> [p.x, p.y, w, h]
            else
                abbc    = (a ~ b) ~ (b ~ c)
                min     = ⌊ abbc ⌋
                max     = ⌈ abbc ⌉
                nearmin = | abbc - min | < 0.1
                nearmax = | abbc - max | < 0.1
                m       = min ?(nearmin)? (max ?(nearmax)? abbc)
                << [a, a ~ b, m] << [m, b ~ c, c]
*/

typedef struct {
    nile_Kernel_t base;
} gezira_DecomposeBeziers_t;

static nile_Kernel_t *
gezira_DecomposeBeziers_clone (nile_t *nl, nile_Kernel_t *k_)
{
    gezira_DecomposeBeziers_t *k = (gezira_DecomposeBeziers_t *) k_;
    gezira_DecomposeBeziers_t *clone =
        (gezira_DecomposeBeziers_t *) nile_Kernel_clone (nl, k_);
    return (nile_Kernel_t *) clone;
}

static int
gezira_DecomposeBeziers_process (nile_t *nl, nile_Kernel_t *k_,
                                nile_Buffer_t **in_, nile_Buffer_t **out_)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t *in = *in_;
    nile_Buffer_t *out = *out_;
    gezira_DecomposeBeziers_t *k = (gezira_DecomposeBeziers_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (in->i < in->n) {
        real v_a_x = nile_Buffer_shift (in);
        real v_a_y = nile_Buffer_shift (in);
        real v_b_x = nile_Buffer_shift (in);
        real v_b_y = nile_Buffer_shift (in);
        real v_c_x = nile_Buffer_shift (in);
        real v_c_y = nile_Buffer_shift (in);
        real t_1_x = nile_Real_flr (v_a_x);
        real t_1_y = nile_Real_flr (v_a_y);
        real t_2_x = nile_Real_flr (v_c_x);
        real t_2_y = nile_Real_flr (v_c_y);
        real t_3_x = nile_Real_clg (v_a_x);
        real t_3_y = nile_Real_clg (v_a_y);
        real t_4_x = nile_Real_clg (v_c_x);
        real t_4_y = nile_Real_clg (v_c_y);
        real t_5_0 = nile_Real_eq (t_1_x, t_2_x);
        real t_5_1 = nile_Real_eq (t_1_y, t_2_y);
        real t_6_0 = nile_Real_eq (t_3_x, t_4_x);
        real t_6_1 = nile_Real_eq (t_3_y, t_4_y);
        real t_7_0 = nile_Real_or (t_5_0, t_6_0);
        real t_7_1 = nile_Real_or (t_5_1, t_6_1);
        real t_8 = nile_Real_and (t_7_0, t_7_1);
        if (t_8) {
            real v_p_x = nile_Real_min (t_1_x, t_2_x);
            real v_p_y = nile_Real_min (t_1_y, t_2_y);
            real t_9 = nile_Real_ave (v_c_x, v_a_x);
            real v_w = nile_Real_sub (nile_Real_add (v_p_x, 1), t_9);
            real v_h = nile_Real_sub (v_c_y, v_a_y);
            out = nile_Buffer_prepare_to_append (nl, out, OUT_QUANTUM, k_);
            nile_Buffer_append (out, v_p_x);
            nile_Buffer_append (out, v_p_y);
            nile_Buffer_append (out, v_w);
            nile_Buffer_append (out, v_h);
        }
        else {
            real v_abbc_x = nile_Real_ave (nile_Real_ave (v_a_x, v_b_x),
                                           nile_Real_ave (v_b_x, v_c_x));
            real v_abbc_y = nile_Real_ave (nile_Real_ave (v_a_y, v_b_y),
                                           nile_Real_ave (v_b_y, v_c_y));
            real v_min_x = nile_Real_flr (v_abbc_x);
            real v_min_y = nile_Real_flr (v_abbc_y);
            real v_max_x = nile_Real_clg (v_abbc_x);
            real v_max_y = nile_Real_clg (v_abbc_y);
            real v_nearmin_x =
                nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_x, v_min_x)), 0.1);
            real v_nearmin_y =
                nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_y, v_min_y)), 0.1);
            real v_nearmax_x =
                nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_x, v_max_x)), 0.1);
            real v_nearmax_y =
                nile_Real_lt (nile_Real_abs (nile_Real_sub (v_abbc_y, v_max_y)), 0.1);
            real v_m_x = nile_Real_sel (v_min_x, v_nearmin_x,
                         nile_Real_sel (v_max_x, v_nearmax_x, v_abbc_x));
            real v_m_y = nile_Real_sel (v_min_y, v_nearmin_y,
                         nile_Real_sel (v_max_y, v_nearmax_y, v_abbc_y));

            in = nile_Buffer_prepare_to_prepend (nl, in, IN_QUANTUM, k_);
            nile_Buffer_prepend (in, v_a_x);
            nile_Buffer_prepend (in, v_a_y);
            nile_Buffer_prepend (in, nile_Real_ave (v_a_x, v_b_x));
            nile_Buffer_prepend (in, nile_Real_ave (v_a_y, v_b_y));
            nile_Buffer_prepend (in, v_m_x);
            nile_Buffer_prepend (in, v_m_y);
            in->i -= IN_QUANTUM;

            in = nile_Buffer_prepare_to_prepend (nl, in, IN_QUANTUM, k_);
            nile_Buffer_prepend (in, v_m_x);
            nile_Buffer_prepend (in, v_m_y);
            nile_Buffer_prepend (in, nile_Real_ave (v_b_x, v_c_x));
            nile_Buffer_prepend (in, nile_Real_ave (v_b_y, v_c_y));
            nile_Buffer_prepend (in, v_c_x);
            nile_Buffer_prepend (in, v_c_y);
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

nile_Kernel_t *
gezira_DecomposeBeziers (nile_t *nl)
{
    gezira_DecomposeBeziers_t *k = NILE_KERNEL_NEW (nl, gezira_DecomposeBeziers);
    return (nile_Kernel_t *) k;
}
