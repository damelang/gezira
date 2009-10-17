#include <stdarg.h>
#include <stdlib.h>
#include "nile.h"

#define real nile_Real_t

#include <libkern/OSAtomic.h>
typedef OSSpinLock nile_Lock_t;
static inline void nile_Lock_init (nile_Lock_t *l) { *l = OS_SPINLOCK_INIT; }
static inline void nile_Lock_fini (nile_Lock_t *l) { }
static inline void nile_Lock_lock (nile_Lock_t *l) { OSSpinLockLock (l); }
static inline void nile_Lock_unlock (nile_Lock_t *l) { OSSpinLockUnlock (l); }

struct nile_ {
    char *memory;
    int msize;
    int nthreads;
    nile_Lock_t lock;
};

nile_t *
nile_begin (char *memory, int msize, int nthreads)
{
    nile_t *n;
    
    n = (nile_t *) memory;
    n->memory = memory + sizeof (nile_t); 
    n->msize = msize;
    n->nthreads = nthreads;
    nile_Lock_init (&n->lock);

    return n;
}

char *
nile_end (nile_t *n)
{
    nile_Lock_fini (&n->lock);
    return (char *) n;
}

void
nile_feed (nile_t *n, nile_Kernel_t *p, nile_Real_t *data, int ndata, int eos)
{
    /* TODO */
}

void
nile_reschedule (nile_t *n, nile_Kernel_t *k, nile_Buffer_t *in, int i)
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

    nile_Lock_lock (&n->lock);
        m = n->memory;
        n->memory += size;
        if (n->memory > ((char *) n) + n->msize)
            abort ();
    nile_Lock_unlock (&n->lock);

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
    nile_Lock_t lock;
    nile_Buffer_t *o;
    int j1;
    int j2;
} nile_Interleave_t ;

typedef struct {
    nile_Kernel_t kernel;
    nile_Interleave_t *parent;
    int quantum;
    int skip;
    int *j;
    int j_n;
} nile_Interleave__t;

static void
nile_Interleave__process (nile_t *n, nile_Kernel_t *k_,
                          nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_Interleave__t *k = (nile_Interleave__t *) k_;
    nile_Lock_t *lock = &k->parent->lock;
    int i_n = in->n;
    int j_n = k->j_n;
    int i = 0;

    while (i < i_n) {
        nile_Lock_lock (lock);
            nile_Buffer_t *o = k->parent->o;
            int j = *k->j;
        nile_Lock_unlock (lock);

        if (j == -1) {
            nile_reschedule (n, k_, in, i);
            break;
        }

        int i0 = i;
        while (i < i_n && j < j_n) {
            int q = k->quantum;
            while (q--)
                o->data[j++] = in->data[i++];
            j += k->skip;
        }
        int flush_needed = (in->eos && !(i < i_n)) || !(j < j_n);

        nile_Lock_lock (lock);
            o->n += i0 - i;
            if (flush_needed) {
                *k->j = -1;
                if (k->parent->j1 == k->parent->j2) {
                    nile_flush (n, k->parent->kernel.downstream, &k->parent->o);
                    k->parent->j1 = 0;
                    k->parent->j2 = k->parent->quantum1;
                }
            }
            else
                *k->j = j;
        nile_Lock_unlock (lock);
    }
}

nile_Kernel_t *
nile_Interleave_ (nile_t *n, nile_Interleave_t *parent,
                  int quantum, int skip, int *j)
{
    nile_Interleave__t *k;

    NILE_KERNEL_INIT (n, k, nile_Interleave_);
    k->parent = parent;
    k->quantum = quantum;
    k->skip = skip;
    k->j = j;
    k->j_n = NILE_BUFFER_SIZE - (quantum + skip) + *j + 1;

    return &k->kernel;
}

static void
nile_Interleave_process (nile_t *n, nile_Kernel_t *k_,
                         nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_Interleave_t *k = (nile_Interleave_t *) k_;
    nile_Buffer_t *in_;

    if (!k_->initialized) {
        k_->initialized = 1;
        nile_Lock_init (&k->lock);
        /* TODO nile_Lock_fini where/when? */
        k->o = NULL; /* TODO this needs to get a newly allocated buffer! */
        k->j1 = 0;
        k->j2 = k->quantum1;
        k->v_k1 = nile_Kernel_clone (n, k->v_k1);
        k->v_k2 = nile_Kernel_clone (n, k->v_k2);
        k->v_k1->downstream =
            nile_Interleave_ (n, k, k->quantum1, k->quantum2, &k->j1);
        k->v_k2->downstream =
            nile_Interleave_ (n, k, k->quantum2, k->quantum1, &k->j2);
    }

    in_ = in;
    nile_flush (n, k->v_k1, &in_); /* TODO we don't want a new buffer here! */
    in_ = in;
    nile_flush (n, k->v_k2, &in_); /* TODO we don't want a new buffer here! */
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
    int i = 0;
    real key = in->data[k->index];
    nile_Kernel_t *downstream = nile_Kernel_clone (n, k->v_k);
    nile_Buffer_t *o = *out;
    
    while (i < in->n) {
        real key_ = in->data[i + k->index];
        if (key_ == key)
            nile_flush_if_full (n, downstream, o, out, k->quantum);
        else {
            nile_flush (n, downstream, out);
            downstream = nile_Kernel_clone (n, k->v_k);
            key = key_;
        }
        int q = k->quantum;
        while (q--)
            o->data[o->n++] = in->data[i++];
    }

    nile_flush (n, downstream, out); /* TODO no new buffer need! */
}

nile_Kernel_t *
nile_GroupBy (nile_t *n, int index, int quantum, nile_Kernel_t *v_k)
{
    nile_GroupBy_t *k;

    NILE_KERNEL_INIT (n, k, nile_GroupBy);
    k->index = index;
    k->quantum = quantum;
    k->v_k = v_k;

    return nile_Pipeline (n, nile_SortBy (n, index, quantum), &k->kernel, NULL);
}

typedef struct nile_BufferList_ nile_BufferList_t;

struct nile_BufferList_ {
    nile_Buffer_t *o;
    nile_BufferList_t *tail;
};

typedef struct {
    nile_Kernel_t kernel;
    int index;
    int quantum;
    nile_BufferList_t *os;
} nile_SortBy_t;

static void
nile_SortBy_process (nile_t *n, nile_Kernel_t *k_,
                     nile_Buffer_t *in, nile_Buffer_t **out)
{
    nile_SortBy_t *k = (nile_SortBy_t *) k_;
    int i = 0;

    if (!k_->initialized) {
        k_->initialized = 1;
        k->os = (nile_BufferList_t *) nile_alloc (n, sizeof (nile_BufferList_t));
        k->os->o = NULL; /* FIXME need a new buffer here! */
        k->os->tail = NULL;
    }

    while (i < in->n) {
        nile_BufferList_t *os = k->os;
        real key = in->data[i + k->index];

        /* find the right buffer */
        while (os->tail != NULL && key > os->tail->o->data[k->index])
            os = os->tail;

        /* split the buffer if it's full */
        if (os->o->n > NILE_BUFFER_SIZE - k->quantum) {
            nile_BufferList_t *tail = (nile_BufferList_t *)
                nile_alloc (n, sizeof (nile_BufferList_t));
            tail->tail = os->tail;
            os->tail = tail;
            os->tail->o = NULL; /* FIXME need a new buffer here! */

            int j = os->o->n / k->quantum / 2 * k->quantum;
            while (j < os->o->n)
                os->tail->o->data[os->tail->o->n++] = os->o->data[j++];
            os->o->n -= os->tail->o->n;

            if (key > os->tail->o->data[k->index])
                os = os->tail;
        }

        /* insert new element */
        nile_Buffer_t *o = os->o;
        int j = o->n - k->quantum;
        while (j >= 0) {
            real j_key = o->data[j + k->index];
            if (j_key <= key)
                break;
            int jj = j + k->quantum;
            int q = k->quantum;
            while (q--)
                o->data[jj++] = o->data[j++];
            j = j - k->quantum - k->quantum;
        }
        j += k->quantum;
        int q = k->quantum;
        while (q--)
            o->data[j++] = in->data[i++];
        o->n += k->quantum;
    }

    if (in->eos) {
        nile_BufferList_t *os = k->os;
        while (os) {
            if (os->tail == NULL)
                os->o->eos = 1;
            nile_flush (n, k_->downstream, &os->o); /* FIXME don't want new buffer! */
            os = os->tail;
        }
    }
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
