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
    int nthreads;

    nile_Lock_t memlock;
    char *mem;
    char *memend;
    void *freelist;

    nile_Lock_t kernellock;
    nile_Kernel_t *ready;
};

nile_t *
nile_begin (int nthreads, char *mem, int memsize)
{
    nile_t *nl = (nile_t *) mem;
    nl->nthreads = nthreads;
    
    nile_Lock_init (&nl->memlock);
    nl->mem = mem + sizeof (nile_t); 
    nl->memend = mem + memsize;
    nl->freelist = NULL;

    nile_Lock_init (&nl->kernellock);
    nl->ready = NULL;

    return nl;
}

void
nile_feed (nile_t *nl, nile_Kernel_t *k, nile_Real_t *data, int n, int eos)
{
    nile_Buffer_t *in;
    int i = 0;

    while (n) {
        in = nile_Buffer_new (nl);
        while (i < n && in->n < NILE_BUFFER_SIZE)
            in->data[in->n++] = data[i++];
        n -= in->n;
        if (n == 0)
            in->eos = eos;
        nile_deliver (nl, k, in);
    }
}

void
nile_sync (nile_t *nl)
{
    /* TODO wait on the threads */
}

char *
nile_end (nile_t *nl)
{
    /* TODO kill the threads */
    nile_Lock_fini (&nl->memlock);
    nile_Lock_fini (&nl->kernellock);
    return (char *) nl;
}

static inline void
nile_signal_kernel_ready (nile_t *nl)
{
    /* TODO */
}

static inline void
nile_wait_for_kernel_ready (nile_t *nl)
{
    /* TODO */
}

static inline void *
nile_alloc (nile_t *nl)
{
    void *v;
    nile_Lock_lock (&nl->memlock);
    {
        v = nl->freelist;
        if (v == NULL) {
            v = nl->mem;
            nl->mem += sizeof (nile_Buffer_t);
            if (nl->mem > nl->memend)
                abort ();
        }
        else
            nl->freelist = *((void **) v);
    }
    nile_Lock_unlock (&nl->memlock);
    return v;
}

static inline void
nile_free (nile_t *nl, void *v)
{
    nile_Lock_lock (&nl->memlock);
    {
        *((void **) v) = nl->freelist;
        nl->freelist = v;
    }
    nile_Lock_unlock (&nl->memlock);
}

nile_Buffer_t *
nile_Buffer_new (nile_t *nl)
{
    nile_Buffer_t *b = nile_alloc (nl);
    b->next = NULL;
    b->i = 0;
    b->n = 0;
    b->eos = 0;
    return b;
}

nile_Buffer_t *
nile_Buffer_clone (nile_t *nl, nile_Buffer_t *b)
{
    int i;
    nile_Buffer_t *clone = nile_Buffer_new (nl);
    clone->i = b->i;
    clone->n = b->n;
    clone->eos = b->eos;
    for (i = b->i; i < b->n; i++)
        clone->data[i] = b->data[i];
    return clone;
}

void
nile_Buffer_free (nile_t *nl, nile_Buffer_t *b)
{
    nile_free (nl, b);
}

nile_Kernel_t *
nile_Kernel_new (nile_t *nl, nile_Kernel_process_t process,
                             nile_Kernel_clone_t clone)
{
    nile_Kernel_t *k = nile_alloc (nl);
    k->next = NULL;
    k->process = process;
    k->clone = clone;
    k->downstream = NULL;
    k->inbox = NULL;
    k->initialized = 0;
    return k;
}

void
nile_Kernel_free (nile_t *nl, nile_Kernel_t *k)
{
    nile_free (nl, k);
}

void
nile_Kernel_pause (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *b, int *pause)
{
    nile_Lock_lock (&nl->kernellock);
    {
        b->next = k->inbox;
        k->inbox = b;
    }
    nile_Lock_unlock (&nl->kernellock);
    *pause = 1;
}

void
nile_Kernel_resume (nile_t *nl, nile_Kernel_t *k)
{
    nile_Lock_lock (&nl->kernellock);
    {
        k->next = nl->ready;
        nl->ready = k;
        nile_signal_kernel_ready (nl);
    }
    nile_Lock_unlock (&nl->kernellock);
}

void
nile_deliver (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *b)
{
    nile_Lock_lock (&nl->kernellock);
    {
        nile_Buffer_t *inbox = k->inbox;
        if (inbox == NULL) {
            k->inbox = b;
            nile_Kernel_t *ready = nl->ready;
            if (ready == NULL)
                nl->ready = k;
            else {
                while (ready->next != NULL)
                    ready = ready->next;
                ready->next = k;
            }
            nile_signal_kernel_ready (nl);
        }
        else {
            while (inbox->next != NULL)
                inbox = inbox->next;
            inbox->next = b;
        }
    }
    nile_Lock_unlock (&nl->kernellock);
}

static void 
nile_loop (nile_t *nl)
{
    for (;;) {
        nile_Kernel_t *k;
        nile_wait_for_kernel_ready (nl);
        nile_Lock_lock (&nl->kernellock);
        {
            k = nl->ready;
            nl->ready = k->next;
            k->next = NULL;
        }
        nile_Lock_unlock (&nl->kernellock);

        nile_Buffer_t *in;
        nile_Lock_lock (&nl->kernellock);
        {
            in = k->inbox;
            k->inbox = in->next;
        }
        nile_Lock_unlock (&nl->kernellock);

        int eos;
        int pause = 0;
        nile_Buffer_t *out = NULL;
        while (in != NULL) {
            eos = in->eos;
            out = k->process (nl, k, in, out, &pause);
            if (pause)
                break;
            nile_Lock_lock (&nl->kernellock);
            {
                in = k->inbox;
                k->inbox = in ? in->next : NULL;
            }
            nile_Lock_unlock (&nl->kernellock);
        }

        nile_Kernel_t *downstream = k->downstream;
        if (eos && !pause) {
            nile_Kernel_free (nl, k);
            if (out)
                out->eos = 1;
        }
        if (out)
            nile_deliver (nl, downstream, out);
    }
}

typedef struct {
    nile_Kernel_t base;
    int n;
    nile_Kernel_t *ks[20];
} nile_Pipeline_t;

static void *
nile_Pipeline_clone (nile_t *nl, void *k_)
{
    nile_Pipeline_t *k = (nile_Pipeline_t *) k_;
    nile_Pipeline_t *clone = nile_Kernel_clone (nl, k_);
    int i;

    for (i = 0; i < k->n; i++)
        clone->ks[clone->n++] = k->ks[i]->clone (nl, k->ks[i]);

    return clone;
}

static nile_Buffer_t *
nile_Pipeline_process (nile_t *nl, nile_Kernel_t *k_,
                       nile_Buffer_t *in, nile_Buffer_t *out, int *pause)
{
    nile_Pipeline_t *k = (nile_Pipeline_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
        int i;
        for (i = k->n - 1; i >= 0; i--) {
            k->ks[i]->downstream = k_->downstream;
            k_->downstream = k->ks[i];
        }
    }

    nile_deliver (nl, k_->downstream, in);

    return out;
}

nile_Kernel_t *
nile_Pipeline (nile_t *nl, ...)
{
    va_list args;
    nile_Kernel_t *ki;
    nile_Pipeline_t *k = NILE_KERNEL_NEW (nl, nile_Pipeline);

    va_start (args, nl); 
    ki = va_arg (args, nile_Kernel_t *);
    for (k->n = 0; ki != NULL; k->n++) {
        k->ks[k->n] = ki;
        ki = va_arg (args, nile_Kernel_t *);
    }
    va_end (args);

    return &k->base;
}

typedef struct {
    nile_Kernel_t base;
    nile_Kernel_t *v_k1;
    int quantum1;
    nile_Kernel_t *v_k2;
    int quantum2;
} nile_Interleave_t;

static void *
nile_Interleave_clone (nile_t *nl, void *k_)
{
    nile_Interleave_t *k = (nile_Interleave_t *) k_;
    nile_Interleave_t *clone = nile_Kernel_clone (nl, k_);
    clone->v_k1 = k->v_k1->clone (nl, k->v_k1);
    clone->quantum1 = k->quantum1; 
    clone->v_k2 = k->v_k2->clone (nl, k->v_k2); 
    clone->quantum2 = k->quantum2; 
    return clone;
}

typedef struct {
    nile_Kernel_t base;
    nile_Lock_t lock;
    nile_Buffer_t *out;
} nile_Interleave__shared_t;

typedef struct nile_Interleave__ nile_Interleave__t;

struct nile_Interleave__ {
    nile_Kernel_t base;
    nile_Interleave__shared_t *shared;
    nile_Interleave__t *sibling;
    int quantum;
    int skip;
    int j;
    int j0;
    int n;
};

static void *
nile_Interleave__clone (nile_t *nl, void *k_)
{
    /* You can't clone this type of kernel,
       it is created just-in-time during pipelining.
     */
    return NULL;
}

static nile_Buffer_t *
nile_Interleave__process (nile_t *nl, nile_Kernel_t *k_,
                          nile_Buffer_t *in, nile_Buffer_t *unused, int *pause)
{
    nile_Interleave__t *k = (nile_Interleave__t *) k_;
    nile_Lock_t *lock = &k->shared->lock;
    nile_Buffer_t *out;
    int done = 0;
    int j;

    while (in->i < in->n) {
        nile_Lock_lock (lock);
        {
            out = k->shared->out;
            j = k->j;
        }
        nile_Lock_unlock (lock);

        if (j == -1) {
            nile_Kernel_pause (nl, k_, in, pause);
            return unused;
        }

        int i0 = in->i;
        while (in->i < in->n && j < k->n) {
            int q = k->quantum;
            while (q--)
                out->data[j++] = in->data[in->i++];
            j += k->skip;
        }
        int flush_needed = (in->eos && !(in->i < in->n)) || !(j < k->n);

        nile_Lock_lock (lock);
        {
            out->n += in->i - i0;
            if (flush_needed) {
                k->j = -1;
                if (k->sibling->j == -1) {
                    done = in->eos && !(in->i < in->n);
                    if (done)
                        out->eos = 1;
                    nile_deliver (nl, k_->downstream, out);
                    if (!done) {
                        k->shared->out = nile_Buffer_new (nl);
                        k->j = k->j0;
                        k->sibling->j = k->sibling->j0;
                        nile_Kernel_resume (nl, &k->sibling->base);
                    }
                }
            }
            else
                k->j = j;
        }
        nile_Lock_unlock (lock);
    }

    if (done) {
        nile_Lock_fini (lock);
        nile_Kernel_free (nl, &k->shared->base);
    }

    nile_Buffer_free (nl, in);
    return unused;
}

static nile_Interleave__t *
nile_Interleave_ (nile_t *nl, nile_Interleave__shared_t *shared, int quantum,
                  int skip, int j0, nile_Kernel_t *downstream)
{
    nile_Interleave__t *k = NILE_KERNEL_NEW (nl, nile_Interleave_);
    k->shared = shared;
    k->quantum = quantum;
    k->skip = skip;
    k->j = j0;
    k->j0 = j0;
    k->n = NILE_BUFFER_SIZE - (quantum + skip) + j0 + 1;
    k->base.downstream = downstream;
    return k;
}

static nile_Buffer_t *
nile_Interleave_process (nile_t *nl, nile_Kernel_t *k_,
                         nile_Buffer_t *in, nile_Buffer_t *out, int *pause)
{
    nile_Interleave_t *k = (nile_Interleave_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
        nile_Interleave__shared_t *shared =
            (nile_Interleave__shared_t *) nile_Kernel_new (nl, NULL, NULL);
        nile_Lock_init (&shared->lock);
        shared->out = nile_Buffer_new (nl);
        nile_Interleave__t *child1 =
            nile_Interleave_ (nl, shared, k->quantum1, k->quantum2, 0, k_->downstream);
        nile_Interleave__t *child2 =
            nile_Interleave_ (nl, shared, k->quantum2, k->quantum1, k->quantum1, k_->downstream);
        child1->sibling = child2;
        child2->sibling = child1;
        k->v_k1->downstream = &child1->base;
        k->v_k2->downstream = &child2->base;
    }

    nile_deliver (nl, k->v_k1, nile_Buffer_clone (nl, in));
    nile_deliver (nl, k->v_k2, in);

    return out;
}

nile_Kernel_t *
nile_Interleave (nile_t *nl, nile_Kernel_t *v_k1, int quantum1,
                 nile_Kernel_t *v_k2, int quantum2)
{
    nile_Interleave_t *k = NILE_KERNEL_NEW (nl, nile_Interleave);
    k->v_k1 = v_k1;
    k->quantum1 = quantum1;
    k->v_k2 = v_k2;
    k->quantum2 = quantum2;
    return &k->base;
}

typedef struct {
    nile_Kernel_t base;
    int index;
    int quantum;
    nile_Kernel_t *v_k;
    real key;
} nile_GroupBy_t;

static void *
nile_GroupBy_clone (nile_t *nl, void *k_)
{
    nile_GroupBy_t *k = (nile_GroupBy_t *) k_;
    nile_GroupBy_t *clone = nile_Kernel_clone (nl, k_);
    clone->index = k->index;
    clone->quantum = k->quantum;
    clone->v_k = k->v_k->clone (nl, k->v_k);
    return clone;
}

static nile_Buffer_t *
nile_GroupBy_process (nile_t *nl, nile_Kernel_t *k_,
                      nile_Buffer_t *in, nile_Buffer_t *out, int *pause)
{
    nile_GroupBy_t *k = (nile_GroupBy_t *) k_;
    out = out ? out : nile_Buffer_new (nl);

    if (!k_->initialized) {
        k_->initialized = 1;
        k->key = in->data[k->index];
    }
    k_->downstream = k->v_k;
    
    while (in->i < in->n) {
        real key = in->data[in->i + k->index];
        if (key != k->key) {
            k->key = key;
            out->eos = 1;
            k_->downstream = nile_Kernel_clone (nl, k_->downstream);
            nile_Kernel_pause (nl, k_, in, pause);
            break;
        }
        int q = k->quantum;
        while (q--)
            out->data[out->n++] = in->data[in->i++];
        out = nile_flush_if_full (nl, k_, out, k->quantum);
    }

    nile_Buffer_free (nl, in);
    return out;
}

nile_Kernel_t *
nile_GroupBy (nile_t *nl, int index, int quantum, nile_Kernel_t *v_k)
{
    nile_GroupBy_t *k = NILE_KERNEL_NEW (nl, nile_GroupBy);
    k->index = index;
    k->quantum = quantum;
    k->v_k = v_k;
    return nile_Pipeline (nl, nile_SortBy (nl, index, quantum), &k->base, NULL);
}

typedef struct {
    nile_Kernel_t base;
    int index;
    int quantum;
    nile_Buffer_t *out;
} nile_SortBy_t;

static void *
nile_SortBy_clone (nile_t *nl, void *k_)
{
    nile_SortBy_t *k = (nile_SortBy_t *) k_;
    nile_SortBy_t *clone = nile_Kernel_clone (nl, k_);
    clone->index = k->index;
    clone->quantum = k->quantum;
    return clone;
}

static nile_Buffer_t *
nile_SortBy_process (nile_t *nl, nile_Kernel_t *k_,
                     nile_Buffer_t *in, nile_Buffer_t *unused, int *pause)
{
    nile_SortBy_t *k = (nile_SortBy_t *) k_;

    if (!k_->initialized) {
        k_->initialized = 1;
        k->out = nile_Buffer_new (nl);
    }

    while (in->i < in->n) {
        nile_Buffer_t *out = k->out;
        real key = in->data[in->i + k->index];

        /* find the right buffer */
        while (out->next != NULL && key > out->next->data[k->index])
            out = out->next;

        /* split the buffer if it's full */
        if (out->n > NILE_BUFFER_SIZE - k->quantum) {
            nile_Buffer_t *next = nile_Buffer_new (nl);
            next->next = out->next;
            out->next = next;

            int j = out->n / k->quantum / 2 * k->quantum;
            while (j < out->n)
                out->next->data[out->next->n++] = out->data[j++];
            out->n -= out->next->n;

            if (key > out->next->data[k->index])
                out = out->next;
        }

        /* insert new element */
        int j = out->n - k->quantum;
        while (j >= 0) {
            if (key >= out->data[j + k->index])
                break;
            int jj = j + k->quantum;
            int q = k->quantum;
            while (q--)
                out->data[jj++] = out->data[j++];
            j = j - k->quantum - k->quantum;
        }
        j += k->quantum;
        int q = k->quantum;
        while (q--)
            out->data[j++] = in->data[in->i++];
        out->n += k->quantum;
    }

    nile_Buffer_free (nl, in);
    if (in->eos)
        return k->out;
    else 
        return unused;
}

nile_Kernel_t *
nile_SortBy (nile_t *nl, int index, int quantum)
{
    nile_SortBy_t *k = NILE_KERNEL_NEW (nl, nile_SortBy);
    k->index = index;
    k->quantum = quantum;
    return &k->base;
}
