#include "gezira.h"

#define real nile_Real_t

nile_Kernel_t *
gezira_Sampler (gezira_Sampler_t *k,
                real start_x, real start_y)
{
    k->start_x = start_x;
    k->start_y = start_y;
    return &k->kernel;
}

/*
   UniformColor (c : Color) : Sampler
    ∀ _
        >> [c.a, c.a × c.r, c.a × c.g, c.a × c.b]
*/
static void
UniformColor_process (nile_Kernel_t *k, nile_Buffer_t *in, nile_Buffer_t **out)
{
    real v_start_x = ((gezira_Sampler_t *) k)->start_x;
    real v_start_y = ((gezira_Sampler_t *) k)->start_y;
    real v_c_a = ((gezira_UniformColor_t *) k)->c_a;
    real v_c_r = ((gezira_UniformColor_t *) k)->c_r;
    real v_c_g = ((gezira_UniformColor_t *) k)->c_g;
    real v_c_b = ((gezira_UniformColor_t *) k)->c_b;
    nile_Buffer_t *o = *out;
    int i = 0;

    while (i < in->n) {
        real v__ = in->data[i++];
        if (o->n > o->capacity - o->quantum) {
            nile_emit (out, k->downstream);
            o = *out;
        }
        o->data[o->n++] = v_c_a;
        o->data[o->n++] = v_c_a * v_c_r;
        o->data[o->n++] = v_c_a * v_c_g;
        o->data[o->n++] = v_c_a * v_c_b;
    }
}

gezira_Sampler_t *
gezira_UniformColor (gezira_UniformColor_t *k,
                     real c_a, real c_r, real c_g, real c_b)
{
    k->sampler.kernel.process = UniformColor_process;
    k->c_a = c_a;
    k->c_r = c_r;
    k->c_g = c_g;
    k->c_b = c_b;
    return &k->sampler;
}
