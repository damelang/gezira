#include "gezira.h"

#define real nile_Real_t

/* 
   Sampler :: Point >> Color
*/

struct gezira_Sampler_ {
    nile_Kernel_t kernel;
};

nile_Kernel_t *
gezira_Sampler (nile_t *nl, gezira_Sampler_t *k)
{
    return &k->kernel;
}

void *
gezira_Sampler_clone (nile_t *nl, void *k_)
{
    gezira_Sampler_t *k = (gezira_Sampler_t *) k_;
    gezira_Sampler_t *clone = nile_Kernel_clone (nl, k_);
    return clone;
}

/*
    Compositor :: [Color, Color] >> Color
*/

struct gezira_Compositor_ {
    nile_Kernel_t kernel;
};

nile_Kernel_t *
gezira_Compositor (nile_t *nl, gezira_Compositor_t *k)
{
    return &k->kernel;
}

void *
gezira_Compositor_clone (nile_t *nl, void *k_)
{
    gezira_Compositor_t *k = (gezira_Compositor_t *) k_;
    gezira_Compositor_t *clone = nile_Kernel_clone (nl, k_);
    return clone;
}

/*
    Canvas :: (start : Point) : [Color, Real] >>|
*/

struct gezira_Canvas_ {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
};

nile_Kernel_t *
gezira_Canvas (nile_t *nl, gezira_Canvas_t *k,
               nile_Real_t v_start_x,
               nile_Real_t v_start_y)
{
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return &k->kernel;
}

void *
gezira_Canvas_clone (nile_t *nl, void *k_)
{
    gezira_Canvas_t *k = (gezira_Canvas_t *) k_;
    gezira_Canvas_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return clone;
}

/*
    CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
        ⇒ Interleave (s1, s2) → c
*/

typedef struct {
    gezira_Sampler_t sampler;
    gezira_Sampler_t *v_s1;
    gezira_Sampler_t *v_s2;
    gezira_Compositor_t *v_c;
} gezira_CompositeSamplers_t;

void *
gezira_CompositeSamplers_clone (nile_t *nl, void *k_)
{
    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    gezira_CompositeSamplers_t *clone = gezira_Sampler_clone (nl, k_);
    clone->v_s1 = k->v_s1->clone (nl, k->v_s1);
    clone->v_s2 = k->v_s2->clone (nl, k->v_s2);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return clone;
}

static int
gezira_CompositeSamplers_process (nile_t *nl, nile_Kernel_t *k_,
                                  nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    gezira_Sampler_t *v_s1 = k->v_s1;
    gezira_Sampler_t *v_s2 = k->v_s2;
    gezira_Compositor_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;

        nile_Kernel_t *p =
            nile_Pipeline (nl, 2,
                nile_Interleave (nl,
                    gezira_Sampler (nl, v_s1), 4,
                    gezira_Sampler (nl, v_s2), 4),
                gezira_Compositor (nl, v_c), NULL);

        p->downstream = k_->downstream;
        k_->downstream = p;
    }

    i = nile_forward (nl, k_, in, i, out);

    k->v_s1 = v_s1;
    k->v_s2 = v_s2;
    k->v_c = v_c;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Sampler_t *
gezira_CompositeSamplers (nile_t *nl,
                          gezira_Sampler_t *v_s1,
                          gezira_Sampler_t *v_s2,
                          gezira_Compositor_t *v_c)
{
    gezira_CompositeSamplers_t *k = NILE_KERNEL_NEW (nl, gezira_CompositeSamplers);
    k->v_s1 = v_s1;
    k->v_s2 = v_s2;
    k->v_c = v_c;
    return &k->sampler;
}

/*
   UniformColor (c : Color) : Sampler
    ∀ p
        >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]
*/

typedef struct {
    gezira_Sampler_t sampler;
    nile_Real_t v_c_a;
    nile_Real_t v_c_r;
    nile_Real_t v_c_g;
    nile_Real_t v_c_b;
} gezira_UniformColor_t;

void *
gezira_UniformColor_clone (nile_t *nl, void *k_)
{
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    gezira_UniformColor_t *clone = gezira_Sampler_clone (nl, k_);
    clone->v_c_a = k->v_c_a;
    clone->v_c_r = k->v_c_r;
    clone->v_c_g = k->v_c_g;
    clone->v_c_b = k->v_c_b;
    return clone;
}

static int
gezira_UniformColor_process (nile_t *nl, nile_Kernel_t *k_,
                             nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 2
#define OUT_QUANTUM 4
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    real v_c_a = k->v_c_a;
    real v_c_r = k->v_c_r;
    real v_c_g = k->v_c_g;
    real v_c_b = k->v_c_b;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (i < in->n) {
        NILE_CONSUME_2 (in, i, v_p_x, v_p_y);
        real t_1_a = v_c_a;
        real t_1_r = nile_Real_mul (v_c_a, v_c_r);
        real t_1_g = nile_Real_mul (v_c_a, v_c_g);
        real t_1_b = nile_Real_mul (v_c_a, v_c_b);
        nile_produce_4 (out, t_1_a, t_1_r, t_1_g, t_1_b);
        nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
    }

    k->v_c_a = v_c_a;
    k->v_c_r = v_c_r;
    k->v_c_g = v_c_g;
    k->v_c_b = v_c_b;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }
    
    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Sampler_t *
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
    return &k->sampler;
}

/*
    CompositeOver : Compositor 
        ∀ [a, b] 
            >> a + b × (1 - a.a) 
*/

typedef struct {
    gezira_Compositor_t compositor;
} gezira_CompositeOver_t;

void *
gezira_CompositeOver_clone (nile_t *nl, void *k_)
{
    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;
    gezira_CompositeOver_t *clone = gezira_Compositor_clone (nl, k_);
    return clone;
}

static int
gezira_CompositeOver_process (nile_t *nl, nile_Kernel_t *k_,
                              nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 8
#define OUT_QUANTUM 4
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_CompositeOver_t *k = (gezira_CompositeOver_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (i < in->n) {
        NILE_CONSUME_8 (in, i, v_a_a, v_a_r, v_a_g, v_a_b, v_b_a, v_b_r, v_b_g, v_b_b);
        real t_1_a = nile_Real_add (v_a_a, nile_Real_mul (v_b_a, nile_Real_sub (1, v_a_a)));
        real t_1_r = nile_Real_add (v_a_r, nile_Real_mul (v_b_r, nile_Real_sub (1, v_a_a)));
        real t_1_g = nile_Real_add (v_a_g, nile_Real_mul (v_b_g, nile_Real_sub (1, v_a_a)));
        real t_1_b = nile_Real_add (v_a_b, nile_Real_mul (v_b_b, nile_Real_sub (1, v_a_a)));
        nile_produce_4 (out, t_1_a, t_1_r, t_1_g, t_1_b);
        nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
    }

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

gezira_Compositor_t *
gezira_CompositeOver (nile_t *nl)
{
    gezira_CompositeOver_t *k = NILE_KERNEL_NEW (nl, gezira_CompositeOver);
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

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
    nile_Real_t v_x;
    nile_Real_t v_local;
    nile_Real_t v_run;
} gezira_FillBetweenEdges_t;

void *
gezira_FillBetweenEdges_clone (nile_t *nl, void *k_)
{
    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    gezira_FillBetweenEdges_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return clone;
}

static int
gezira_FillBetweenEdges_process (nile_t *nl, nile_Kernel_t *k_,
                                 nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 1
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_FillBetweenEdges_t *k = (gezira_FillBetweenEdges_t *) k_;
    real v_start_x = k->v_start_x;
    real v_start_y = k->v_start_y;
    real v_x = k->v_x;
    real v_local = k->v_local;
    real v_run = k->v_run;

    if (!k_->initialized) {
        k_->initialized = 1;
        v_x = v_start_x;
        v_local = 0;
        v_run = 0;
    }

    while (i < in->n) {
        real v_local_;
        real v_run_;
        NILE_CONSUME_4 (in, i, v_x_, v_y, v_w, v_h);
        real v_n = v_x_ - v_x;
        if (nile_Real_eq (v_n, 0)) {
            v_local_ = nile_Real_add (v_local, nile_Real_mul (v_w, v_h));
            v_run_ = nile_Real_add (v_run, v_h);
        }
        else {
            v_local_ = nile_Real_add (v_run, nile_Real_mul (v_w, v_h));
            v_run_ = nile_Real_add (v_run, v_h);
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            nile_produce_1 (out, t_1);
            nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
            nile_produce_1_repeat (nl, k_, out, OUT_QUANTUM,
                                   nile_Real_sub (v_n, 1),
                                   nile_Real_min (nile_Real_abs (v_run), 1));
        }
        v_x = v_x_;
        v_local = v_local_;
        v_run = v_run_;
    }

    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    k->v_x = v_x;
    k->v_local = v_local;
    k->v_run = v_run;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
        real v_start_x = k->v_start_x;
        real v_start_y = k->v_start_y;
        real v_x = k->v_x;
        real v_local = k->v_local;
        real v_run = k->v_run;

        if (nile_Real_neq (v_local, 0)) {
            real t_1 = nile_Real_min (nile_Real_abs (v_local), 1);
            nile_produce_1 (out, t_1);
            nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
        }
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_FillBetweenEdges (nile_t *nl,
                         nile_Real_t v_start_x,
                         nile_Real_t v_start_y)
{
    gezira_FillBetweenEdges_t *k = NILE_KERNEL_NEW (nl, gezira_FillBetweenEdges);
    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    return &k->kernel;
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
    nile_Kernel_t kernel;
    nile_Real_t v_start_x;
    nile_Real_t v_start_y;
    nile_Real_t v_x;
    nile_Real_t v_y;
} gezira_CreateSamplePoints_t;

void *
gezira_CreateSamplePoints_clone (nile_t *nl, void *k_)
{
    gezira_CreateSamplePoints_t *k = (gezira_CreateSamplePoints_t *) k_;
    gezira_CreateSamplePoints_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_start_x = k->v_start_x;
    clone->v_start_y = k->v_start_y;
    return clone;
}

static int
gezira_CreateSamplePoints_process (nile_t *nl, nile_Kernel_t *k_,
                                   nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 1
#define OUT_QUANTUM 2
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

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

    while (i < in->n) {
        real v_x_;
        NILE_CONSUME_1 (in, i, v_c);
        v_x_ = nile_Real_add (v_x, 1);
        nile_produce_2 (out, v_x, v_y);
        nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
        v_x = v_x_;
    }

    k->v_start_x = v_start_x;
    k->v_start_y = v_start_y;
    k->v_x = v_x;
    k->v_y = v_y;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
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
    return &k->kernel;
}

/*
    Render' (s : Sampler, c : Canvas) : EdgeContribution >>|
        & [p, w, h]
            ⇒ FillBetweenEdges (p) →
              Interleave (→ CreateSamplePoints (p + 0.5) → s, (→)) →
              c (p + 0.5)
*/

typedef struct {
    nile_Kernel_t kernel;
    gezira_Sampler_t *v_s;
    gezira_Canvas_t *v_c;
} gezira_Render__t;

void *
gezira_Render__clone (nile_t *nl, void *k_)
{
    gezira_Render__t *k = (gezira_Render__t *) k_;
    gezira_Render__t *clone = nile_Kernel_clone (nl, k_);
    clone->v_s = k->v_s->clone (nl, k->v_s);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return clone;
}

static int
gezira_Render__process (nile_t *nl, nile_Kernel_t *k_,
                        nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_Render__t *k = (gezira_Render__t *) k_;
    gezira_Sampler_t *v_s = k->v_s;
    gezira_Canvas_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;

        NILE_PEEK_4 (in, v_p_x, v_p_y, v_w, v_h);
        real t_1_x = nile_Real_add (v_p_x, 0.5);
        real t_1_y = nile_Real_add (v_p_y, 0.5);

        nile_Kernel_t *p =
            nile_Pipeline (nl, 3,
                gezira_FillBetweenEdges (nl, v_p_x, v_p_y),
                nile_Interleave (nl, 
                    nile_Pipeline (nl, 2,
                        gezira_CreateSamplePoints (nl, t_1_x, t_1_y),
                        gezira_Sampler (nl, v_s), NULL), 4,
                    nile_Pipeline (nl, NULL), 1),
                gezira_Canvas (nl, v_c, t_1_x, t_1_y), NULL);

        p->downstream = k_->downstream;
        k_->downstream = p;
    }

    i = nile_forward (nl, k_, in, i, out);

    k->v_s = v_s;
    k->v_c = v_c;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render_ (nile_t *nl,
                gezira_Sampler_t *v_s,
                gezira_Canvas_t *v_c)
{
    gezira_Render__t *k = NILE_KERNEL_NEW (nl, gezira_Render_);
    k->v_s = v_s;
    k->v_c = v_c;
    return &k->kernel;
}

/*
    Render (s : Sampler, c : Canvas) : EdgeContribution >>|
        ⇒ GroupBy (@p.y, SortBy (@p.x) → Render' (s, c))
*/

typedef struct {
    nile_Kernel_t kernel;
    gezira_Sampler_t *v_s;
    gezira_Canvas_t *v_c;
} gezira_Render_t;

void *
gezira_Render_clone (nile_t *nl, void *k_)
{
    gezira_Render_t *k = (gezira_Render_t *) k_;
    gezira_Render_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_s = k->v_s->clone (nl, k->v_s);
    clone->v_c = k->v_c->clone (nl, k->v_c);
    return clone;
}

static int
gezira_Render_process (nile_t *nl, nile_Kernel_t *k_,
                       nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 4
#define OUT_QUANTUM 0
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_Render_t *k = (gezira_Render_t *) k_;
    gezira_Sampler_t *v_s = k->v_s;
    gezira_Canvas_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;

        nile_Kernel_t *p = nile_GroupBy (nl, 1, 4, nile_Pipeline (nl, 2,
            nile_SortBy (nl, 0, 4),
            gezira_Render_ (nl, v_s, v_c), NULL));

        p->downstream = k_->downstream;
        k_->downstream = p;
    }

    i = nile_forward (nl, k_, in, i, out);

    k->v_s = v_s;
    k->v_c = v_c;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_Render (nile_t *nl,
               gezira_Sampler_t *v_s,
               gezira_Canvas_t *v_c)
{
    gezira_Render_t *k = NILE_KERNEL_NEW (nl, gezira_Render);
    k->v_s = v_s;
    k->v_c = v_c;
    return &k->kernel;
}

/*
    TransformBezier (m : Matrix) : Bezier >> Bezier
        ∀ [a, b, c]
            >> [m × a, m × b, m × c]
*/

typedef struct {
    nile_Kernel_t kernel;
    nile_Real_t v_m_a;
    nile_Real_t v_m_b;
    nile_Real_t v_m_c;
    nile_Real_t v_m_d;
    nile_Real_t v_m_e;
    nile_Real_t v_m_f;
} gezira_TransformBezier_t;

void *
gezira_TransformBezier_clone (nile_t *nl, void *k_)
{
    gezira_TransformBezier_t *k = (gezira_TransformBezier_t *) k_;
    gezira_TransformBezier_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_m_a = k->v_m_a; 
    clone->v_m_b = k->v_m_b; 
    clone->v_m_c = k->v_m_c; 
    clone->v_m_d = k->v_m_d; 
    clone->v_m_e = k->v_m_e; 
    clone->v_m_f = k->v_m_f; 
    return clone;
}

static int
gezira_TransformBezier_process (nile_t *nl, nile_Kernel_t *k_,
                                nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_TransformBezier_t *k = (gezira_TransformBezier_t *) k_;
    real v_m_a = k->v_m_a;
    real v_m_b = k->v_m_b;
    real v_m_c = k->v_m_c;
    real v_m_d = k->v_m_d;
    real v_m_e = k->v_m_e;
    real v_m_f = k->v_m_f;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (i < in->n) {
        NILE_CONSUME_6 (in, i, v_a_x, v_a_y, v_b_x, v_b_y, v_c_x, v_c_y);
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
        nile_produce_6 (out, t_1_x, t_1_y, t_2_x, t_2_y, t_3_x, t_3_y);
        nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
    }

    k->v_m_a = v_m_a;
    k->v_m_b = v_m_b;
    k->v_m_c = v_m_c;
    k->v_m_d = v_m_d;
    k->v_m_e = v_m_e;
    k->v_m_f = v_m_f;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_TransformBezier (nile_t *nl,
                        nile_Real_t v_m_a,
                        nile_Real_t v_m_b,
                        nile_Real_t v_m_c,
                        nile_Real_t v_m_d,
                        nile_Real_t v_m_e,
                        nile_Real_t v_m_f)
{
    gezira_TransformBezier_t *k = NILE_KERNEL_NEW (nl, gezira_TransformBezier);
    k->v_m_a = v_m_a;
    k->v_m_b = v_m_b;
    k->v_m_c = v_m_c;
    k->v_m_d = v_m_d;
    k->v_m_e = v_m_e;
    k->v_m_f = v_m_f;
    return &k->kernel;
}

/*
    ClipBezier (min, max : Point) : Bezier >> Bezier
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
    nile_Kernel_t kernel;
    nile_Real_t v_min_x;
    nile_Real_t v_min_y;
    nile_Real_t v_max_x;
    nile_Real_t v_max_y;
} gezira_ClipBezier_t;

void *
gezira_ClipBezier_clone (nile_t *nl, void *k_)
{
    gezira_ClipBezier_t *k = (gezira_ClipBezier_t *) k_;
    gezira_ClipBezier_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_min_x = k->v_min_x;
    clone->v_min_y = k->v_min_y;
    clone->v_max_x = k->v_max_x;
    clone->v_max_y = k->v_max_y;
    return clone;
}

static int
gezira_ClipBezier_process (nile_t *nl, nile_Kernel_t *k_,
                           nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_ClipBezier_t *k = (gezira_ClipBezier_t *) k_;
    real v_min_x = k->v_min_x;
    real v_min_y = k->v_min_y;
    real v_max_x = k->v_max_x;
    real v_max_y = k->v_max_y;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (i < in->n) {
        NILE_CONSUME_6 (in, i, v_a_x, v_a_y, v_b_x, v_b_y, v_c_x, v_c_y);
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
            nile_produce_6 (out, v_a_x, v_a_y, v_b_x, v_b_y, v_c_x, v_c_y);
            nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
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
                nile_produce_6 (out, v_ca_x, v_ca_y,
                                nile_Real_ave (v_ca_x, v_cc_x), nile_Real_ave (v_ca_y, v_cc_y),
                                v_cc_x, v_cc_y);
                nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
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
                nile_produce_6 (&r, v_a_x, v_a_y,
                                nile_Real_ave (v_a_x, v_b_x), nile_Real_ave (v_a_y, v_b_y),
                                v_m_x, v_m_y);
                nile_recurse_if_full (nl, k_, r, IN_QUANTUM, out);
                nile_produce_6 (&r, v_m_x, v_m_y, nile_Real_ave (v_b_x, v_c_x),
                                nile_Real_ave (v_b_y, v_c_y), v_c_x, v_c_y);
                nile_recurse_if_full (nl, k_, r, IN_QUANTUM, out);
            }
        }
    }

    k->v_min_x = v_min_x;
    k->v_min_y = v_min_y;
    k->v_max_x = v_max_x;
    k->v_max_y = v_max_y;

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_ClipBezier (nile_t *nl,
                   nile_Real_t v_min_x,
                   nile_Real_t v_min_y,
                   nile_Real_t v_max_x,
                   nile_Real_t v_max_y)
{
    gezira_ClipBezier_t *k = NILE_KERNEL_NEW (nl, gezira_ClipBezier);
    k->v_min_x = v_min_x;
    k->v_min_y = v_min_y;
    k->v_max_x = v_max_x;
    k->v_max_y = v_max_y;
    return &k->kernel;
}

/*
    DecomposeBezier : Bezier >> EdgeContribution
        ∀ [a, b, c]
            if ∧[ ⌊ a ⌋ = ⌊ c ⌋ ∨ ⌈ a ⌉ = ⌈ c ⌉ ]
                p = ⌊ a ⌋ ⋖ ⌊ c ⌋
                w = p.x + 1 - (c.x ~ a.x)
                h = c.y - a.y
                >> [p, w, h]
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
    nile_Kernel_t kernel;
} gezira_DecomposeBezier_t;

void *
gezira_DecomposeBezier_clone (nile_t *nl, void *k_)
{
    gezira_DecomposeBezier_t *k = (gezira_DecomposeBezier_t *) k_;
    gezira_DecomposeBezier_t *clone = nile_Kernel_clone (nl, k_);
    return clone;
}

static int
gezira_DecomposeBezier_process (nile_t *nl, nile_Kernel_t *k_,
                                nile_Buffer_t *in, int i, nile_Buffer_t **out)
{
#define IN_QUANTUM 6
#define OUT_QUANTUM 6
    nile_Buffer_t rbuffer;
    rbuffer.n = 0;
    rbuffer.eos = 0;
    nile_Buffer_t *r = &rbuffer;

    gezira_DecomposeBezier_t *k = (gezira_DecomposeBezier_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
    }

    while (i < in->n) {
        NILE_CONSUME_6 (in, i, v_a_x, v_a_y, v_b_x, v_b_y, v_c_x, v_c_y);
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
            nile_produce_4 (out, v_p_x, v_p_y, v_w, v_h);
            nile_flush_if_full (nl, k_, out, OUT_QUANTUM);
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
            nile_produce_6 (&r, v_a_x, v_a_y,
                            nile_Real_ave (v_a_x, v_b_x), nile_Real_ave (v_a_y, v_b_y),
                            v_m_x, v_m_y);
            nile_recurse_if_full (nl, k_, r, IN_QUANTUM, out);
            nile_produce_6 (&r, v_m_x, v_m_y, nile_Real_ave (v_b_x, v_c_x),
                              nile_Real_ave (v_b_y, v_c_y), v_c_x, v_c_y);
            nile_recurse_if_full (nl, k_, r, IN_QUANTUM, out);
        }
    }

    if (r->n != 0)
        nile_recurse (nl, k_, r, out);

    if (in->eos) {
    }

    return i;
#undef IN_QUANTUM
#undef OUT_QUANTUM
}

nile_Kernel_t *
gezira_DecomposeBezier (nile_t *nl)
{
    gezira_DecomposeBezier_t *k = NILE_KERNEL_NEW (nl, gezira_DecomposeBezier);
    return &k->kernel;
}
