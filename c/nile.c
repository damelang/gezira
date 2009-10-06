#include <stdlib.h>
#include <stdarg.h>
#include "nile.h"

struct nile_Context_ {
    /* TODO */
};

nile_Context_t *
nile_Context ()
{
    nile_Context_t *c = malloc (sizeof (nile_Context_t));
    /* TODO */
    return c;
}

void
nile_free_Context (nile_Context_t *c)
{
    /* TODO */
    free (c);
}

nile_Kernel_t *
nile_pipeline (nile_Kernel_t *k0, ...)
{
    va_list args;
    nile_Kernel_t *ki, *kj;

    va_start (args, k0); 
    ki = k0;
    while (ki) {
        ki->initialized = 0;
        kj = va_arg (args, nile_Kernel_t *);
        ki->downstream = kj ? kj : ki->downstream;
        ki = kj;
    }

    va_end (args);
    return k0;
}

void
nile_feed (nile_Context_t *c, nile_Kernel_t *k,
           nile_Real_t *data, int n, int eos)
{
    /* TODO */
}

void
nile_flush (nile_Context_t *c, nile_Kernel_t *k,
            nile_Buffer_t **out)
{
    /* TODO */
}

void
nile_forward (nile_Context_t *c, nile_Kernel_t *k,
              nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

static void
Id_process (nile_Context_t *c, nile_Kernel_t *k_,
            nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_forward (c, k_->downstream, in, out);
}

nile_Kernel_t *
nile_Id (nile_Id_t *k)
{
    k->kernel.process = Id_process;
    return &k->kernel;
}

static void
Interleave_process (nile_Context_t *c, nile_Kernel_t *k_,
                    nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

nile_Kernel_t *
nile_Interleave (nile_Interleave_t *k,
                 nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2)
{
    k->kernel.process = Interleave_process;
    k->v_k1 = k1;
    k->quantum1 = quantum1;
    k->v_k2 = k2;
    k->quantum2 = quantum2;
    /* TODO */
    return &k->kernel;
}

static void
GroupBy_process (nile_Context_t *c, nile_Kernel_t *k_,
                 nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

nile_Kernel_t *
nile_GroupBy (nile_GroupBy_t *k,
              int index,
              int quantum)
{
    k->kernel.process = GroupBy_process;
    k->index = index;
    k->quantum = quantum;
    /* TODO */
    return &k->kernel;
}

static void
SortBy_process (nile_Context_t *c, nile_Kernel_t *k_,
                nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

nile_Kernel_t *
nile_SortBy (nile_SortBy_t *k,
             int index,
             int quantum)
{
    k->kernel.process = SortBy_process;
    k->index = index;
    k->quantum = quantum;
    /* TODO */
    return &k->kernel;
}
