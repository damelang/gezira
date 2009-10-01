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
    ki->initialized = 0;
    kj = va_arg (args, nile_Kernel_t *);
    while (kj == NULL) {
        ki->downstream = kj;
        ki = kj;
        ki->initialized = 0;
        kj = va_arg (args, nile_Kernel_t *);
    }

    va_end (args);
    return k0;
}

void
nile_feed (nile_Kernel_t *k, nile_Real_t *data, int n, nile_Context_t *c)
{
    /* TODO */
}

void
nile_flush (nile_Kernel_t *k, nile_Buffer_t **out, nile_Context_t *c)
{
    /* TODO */
}

nile_Kernel_t *
nile_Interleave (nile_Interleave_t *k,
                 nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2)
{
    k->v_k1 = k1;
    k->v_quantum1 = quantum1;
    k->v_k2 = k2;
    k->v_quantum2 = quantum2;
    /* TODO */
    return &k->kernel;
}
