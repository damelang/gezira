#include <stdarg.h>
#include <stdlib.h>
#include "nile.h"

#include <libkern/OSAtomic.h>
#define NILE_LOCK_T OSSpinLock
#define NILE_LOCK_INIT(lock) (lock) = OS_SPINLOCK_INIT
#define NILE_LOCK_DESTROY(lock)
#define NILE_LOCK(lock) OSSpinLockLock (&(lock))
#define NILE_UNLOCK(lock) OSSpinLockUnlock (&(lock))

struct nile_ {
    char *memory;
    int msize;
    int nthreads;
    NILE_LOCK_T lock;
};

nile_t *
nile_begin (char *memory, int msize, int nthreads)
{
    nile_t *n;
    
    n = (nile_t *) memory;
    n->memory = memory + sizeof (nile_t); 
    n->msize = msize;
    n->nthreads = nthreads;
    NILE_LOCK_INIT (n->lock);

    return n;
}

char *
nile_end (nile_t *n)
{
    NILE_LOCK_DESTROY (n->lock);
    return (char *) n;
}

void
nile_feed (nile_t *n, nile_Kernel_t *p, nile_Real_t *data, int ndata, int eos)
{
    /* TODO */
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

char *
nile_alloc (nile_t *n, int size)
{
    char *m;

    NILE_LOCK (n->lock);
    m = n->memory;
    n->memory += size;
    if (n->memory > ((char *) n) + n->msize)
        abort ();
    NILE_UNLOCK (n->lock);

    return m;
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

typedef struct {
    nile_Kernel_t kernel;
    nile_Kernel_t *v_k1;
    int quantum1;
    nile_Kernel_t *v_k2;
    int quantum2;
} nile_Interleave_t ;

static void
nile_Interleave_process (nile_t *n, nile_Kernel_t *k_,
                         nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_Interleave_t *k = (nile_Interleave_t *) k_;
    /* TODO */
}

nile_Kernel_t *
nile_Interleave (nile_t *n, nile_Kernel_t *v_k1, int quantum1,
                 nile_Kernel_t *v_k2, int quantum2)
{
    nile_Interleave_t *k;
    NILE_KERNEL_INIT (n, k, nile_Interleave);
    k->v_k1 = v_k1;
    k->quantum1 = quantum1;
    k->v_k2 = v_k2;
    k->quantum2 = quantum2;
    return &k->kernel;
}

typedef struct {
    nile_Kernel_t kernel;
    int index;
    int quantum;
    nile_Kernel_t *v_k;
} nile_GroupBy_t;

static void
nile_GroupBy_process (nile_t *n, nile_Kernel_t *k_,
                      nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_GroupBy_t *k = (nile_GroupBy_t *) k_;
    /* TODO */
}

nile_Kernel_t *
nile_GroupBy (nile_t *n, int index, int quantum, nile_Kernel_t *v_k)
{
    nile_GroupBy_t *k;
    NILE_KERNEL_INIT (n, k, nile_GroupBy);
    k->index = index;
    k->quantum = quantum;
    k->v_k = v_k;
    return &k->kernel;
}

typedef struct {
    nile_Kernel_t kernel;
    int index;
    int quantum;
} nile_SortBy_t;

static void
nile_SortBy_process (nile_t *n, nile_Kernel_t *k_,
                     nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_SortBy_t *k = (nile_SortBy_t *) k_;
    /* TODO */
}

nile_Kernel_t *
nile_SortBy (nile_t *n, int index, int quantum)
{
    nile_SortBy_t *k;
    NILE_KERNEL_INIT (n, k, nile_SortBy);
    k->index = index;
    k->quantum = quantum;
    return &k->kernel;
}
