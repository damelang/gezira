#include <stdarg.h>
#include <stdlib.h>
#include <libkern/OSAtomic.h>
#include "nile.h"

struct nile_ {
    char *memory;
    int msize;
    int nthreads;
    OSSpinLock lock;
};

nile_t *
nile_begin (char *memory, int msize, int nthreads)
{
    nile_t *n;
    
    n = (nile_t *) memory;
    n->memory = memory + sizeof (nile_t); 
    n->msize = msize;
    n->nthreads = nthreads;
    n->lock = OS_SPINLOCK_INIT;

    return n;
}

char *
nile_end (nile_t *n)
{
    return (char *) n;
}

void
nile_feed (nile_t *n, nile_Kernel_t *p, nile_Real_t *data, int ndata, int eos)
{
    /* TODO */
}

typedef struct {
    nile_Kernel_t kernel;
    nile_Kernel_t **ks;
    int n;
} nile_Pipeline_t;

void
nile_Pipeline_process (nile_t *n, nile_Kernel_t *k_,
                       nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_Pipeline_t *k = (nile_Pipeline_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
        int i;
        for (i = k->n - 1; i >= 0; i--) {
            nile_Kernel_t *ki = nile_Kernel_clone (n, k->ks[i]);
            ki->downstream = k_->downstream;
            k_->downstream = ki;
        }
    }

    nile_forward (n, k_->downstream, in, out);
}

nile_Kernel_t *
nile_Pipeline (nile_t *n, ...)
{
    va_list args;
    nile_Pipeline_t *k;
    nile_Kernel_t *ki;
    int i;

    va_start (args, n); 
    NILE_KERNEL_INIT (n, k, nile_Pipeline);
    ki = va_arg (args, nile_Kernel_t *);
    for (k->n = 0; ki != NULL; k->n++)
        ki = va_arg (args, nile_Kernel_t *);
    va_end (args);

    va_start (args, n); 
    k->ks = (nile_Kernel_t **) nile_alloc (n, k->n * sizeof (nile_Kernel_t *));
    for (i = 0; i < k->n; i++)
        k->ks[i] = va_arg (args, nile_Kernel_t *);
    va_end (args);

    return &k->kernel;
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

char *
nile_alloc (nile_t *n, int size)
{
    char *m;

    OSSpinLockLock (&n->lock);
    m = n->memory;
    n->memory += size;
    if (n->memory > ((char *) n) + n->msize)
        abort ();
    OSSpinLockUnlock (&n->lock);

    return m;
}

void
nile_forward (nile_t *n, nile_Kernel_t *k,
              nile_Buffer_t *in, nile_Buffer_t **out)
{
    /* TODO */
}

void
nile_flush (nile_t *n, nile_Kernel_t *k, nile_Buffer_t **out)
{
    /* TODO */
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
