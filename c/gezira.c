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

static void
UniformColor_process (nile_Kernel_t *k, nile_Buffer_t *in, nile_Buffer_t *out)
{
    /* TODO */
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
