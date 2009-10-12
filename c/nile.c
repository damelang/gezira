#include <stdarg.h>
#include "nile.h"

struct nile_ {
    /* TODO */
};

nile_t *
nile_begin (char *memory, int size, int nthreads)
{
    nile_t *n = (nile_t *) memory;
    /* TODO */
    return n;
}

char *
nile_end (nile_t *n)
{
    /* TODO */
    return (char *) n;
}

void
nile_feed (nile_t *n, nile_Kernel_t *p, nile_Real_t *data, int ndata, int eos)
{
    /* TODO */
}

#if 0

typedef struct {
    nile_Kernel_t kernel;
    nile_Kernel_t *ks[10];
} nile_Pipeline_t;

void
nile_Pipeline_process (nile_t *n, nile_Kernel_t *k_,
                       nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_Pipeline_t *p = (nile_Pipeline_t *) k_;

    if (!k_->initialized) {
        int i;
        nile_Kernel_t *ki;

        /* TODO adjust for dynamically allocated array */
        for (i = 0; p->ks[i]; i++) {
            ki = nile_Kernel_clone (n, p->ks[i]);
            ki->downstream = k_->downstream;
            k_->downstream = ki;
        }
    }

    nile_forward (n, k_->downstream, in, out);
}

#endif

nile_Kernel_t *
nile_Pipeline (nile_t *n, int nk, nile_Kernel_t *k, ...)
{
#if 0
    va_list args;
    Pipeline_t *p;
    int i;

    va_start (args, k); 
    NILE_KERNEL_INIT (n, p, Pipeline);
    /* TODO dynamically allocate the pointer array */
    p->ks[0] = k;
    for (i = 1; k; i++)
        p->ks[i] = k = va_arg (args, nile_Kernel_t *);

    va_end (args);
    return &p->kernel;
#endif
    return NULL;
}

char *
nile_alloc (nile_t *n, int size)
{
    /* TODO */
    return NULL;
}

nile_Kernel_t *
nile_Kernel_clone (nile_t *n, nile_Kernel_t *k)
{
    int i;
    char *s;
    char *d;
        
    s = (char *) k;
    d = nile_alloc (n, k->size);
    for (i = 0; i < k->size; i++)
        d[i] = s[i];

    return (nile_Kernel_t *) d;
}

nile_Kernel_t *
nile_Id (nile_t *n)
{
    /* TODO */
    return NULL;
}

nile_Kernel_t *
nile_Interleave (nile_t *n, nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2)
{
    /* TODO */
    return NULL;
}

nile_Kernel_t *
nile_GroupBy (nile_t *n, int index, int quantum, nile_Kernel_t *k)
{
    /* TODO */
    return NULL;
}

nile_Kernel_t *
nile_SortBy (nile_t *n, int index, int quantum)
{
    /* TODO */
    return NULL;
}

#if 0

struct nile_Id_ {
    nile_Kernel_t kernel;
};

struct nile_Interleave_ {
    nile_Kernel_t kernel;
    nile_Kernel_t *v_k1;
    int quantum1;
    nile_Kernel_t *v_k2;
    int quantum2;
    /* TODO */
};

struct nile_GroupBy_ {
    nile_Kernel_t kernel;
    int index;
    int quantum;
    /* TODO */
};

struct nile_SortBy_ {
    nile_Kernel_t kernel;
    int index;
    int quantum;
    /* TODO */
};

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

#endif
