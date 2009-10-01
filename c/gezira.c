#include <stddef.h>
#include "gezira.h"

#define real nile_Real_t

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k,
                real start_x, real start_y)
{
    k->v_start_x = start_x;
    k->v_start_y = start_y;
    return &k->kernel;
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
#define IN_QUANTUM 1
#define OUT_QUANTUM 4
    gezira_UniformColor_t *k = (gezira_UniformColor_t *) k_;
    real v_start_x = k->sampler.v_start_x;
    real v_start_y = k->sampler.v_start_y;
    real v_c_a = k->v_c_a;
    real v_c_r = k->v_c_r;
    real v_c_g = k->v_c_g;
    real v_c_b = k->v_c_b;
    nile_Buffer_t *o = *out;
    int i = 0;

    while (i < in->n) {
        real v__ = in->data[i + 0];
        i += IN_QUANTUM;
        real v__1_a = v_c_a;
        real v__1_r = nile_Real_mul (v_c_a, v_c_r);
        real v__1_g = nile_Real_mul (v_c_a, v_c_g);
        real v__1_b = nile_Real_mul (v_c_a, v_c_b);
        o->data[o->n + 0] = v__1_a;
        o->data[o->n + 1] = v__1_r;
        o->data[o->n + 2] = v__1_g;
        o->data[o->n + 3] = v__1_b;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
    }
}

gezira_Sampler_t *
gezira_UniformColor (gezira_UniformColor_t *k,
                     real c_a, real c_r, real c_g, real c_b)
{
    k->sampler.kernel.process = UniformColor_process;
    k->v_c_a = c_a;
    k->v_c_r = c_r;
    k->v_c_g = c_g;
    k->v_c_b = c_b;
    return &k->sampler;
}

nile_Kernel_t *
gezira_Compositor (gezira_Compositor_t *k)
{
    return &k->kernel;
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
        real v__1_a = nile_Real_add (v_a_a, nile_Real_mul (v_b_a, nile_Real_sub (1, v_a_a)));
        real v__1_r = nile_Real_add (v_a_r, nile_Real_mul (v_b_r, nile_Real_sub (1, v_a_a)));
        real v__1_g = nile_Real_add (v_a_g, nile_Real_mul (v_b_g, nile_Real_sub (1, v_a_a)));
        real v__1_b = nile_Real_add (v_a_b, nile_Real_mul (v_b_b, nile_Real_sub (1, v_a_a)));
        o->data[o->n + 0] = v__1_a;
        o->data[o->n + 1] = v__1_r;
        o->data[o->n + 2] = v__1_g;
        o->data[o->n + 3] = v__1_b;
        o->n += OUT_QUANTUM;
        if (o->capacity < o->n + OUT_QUANTUM) {
            nile_flush (c, k_->downstream, out);
            o = *out;
        }
    }
}

gezira_Compositor_t *
gezira_CompositeOver (gezira_CompositeOver_t *k)
{
    k->compositor.kernel.process = CompositeOver_process;
    return &k->compositor;
}

/*
    CompositeSamplers (s1 : Sampler, s2 : Sampler, c : Compositor) : Sampler
        → Interleave (s1 (start), s2 (start)) → c
*/
static void
CompositeSamplers_process (nile_Context_t *c, nile_Kernel_t *k_,
                           nile_Buffer_t *in, nile_Buffer_t **out)
{
#define IN_QUANTUM 1
#define OUT_QUANTUM 4
    gezira_CompositeSamplers_t *k = (gezira_CompositeSamplers_t *) k_;
    real v_start_x = k->sampler.v_start_x;
    real v_start_y = k->sampler.v_start_y;
    gezira_Sampler_t *v_s1 = k->v_s1;
    gezira_Sampler_t *v_s2 = k->v_s2;
    gezira_Compositor_t *v_c = k->v_c;

    if (!k_->initialized) {
        k_->initialized = 1;
        k_->downstream =
            nile_pipeline (nile_Interleave (&k->p_1,
                                            gezira_Sampler (v_s1, v_start_x, v_start_y), 4,
                                            gezira_Sampler (v_s2, v_start_x, v_start_y), 4),
                           gezira_Compositor (v_c),
                           k_->downstream, NULL);
    }
    nile_forward (c, k_->downstream, in, out);
}

gezira_Sampler_t *
gezira_CompositeSamplers (gezira_CompositeSamplers_t *k,
                          gezira_Sampler_t *s1, gezira_Sampler_t *s2,
                          gezira_Compositor_t *c)
{
    k->sampler.kernel.process = CompositeSamplers_process;
    k->v_s1 = s1;
    k->v_s2 = s2;
    k->v_c = c;
    return &k->sampler;
}
