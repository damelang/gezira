#ifndef NILE_H
#define NILE_H

/* EXTERNAL API */

typedef float nile_Real_t;
typedef struct nile_Kernel_ nile_Kernel_t;
typedef struct nile_ nile_t;

nile_t *
nile_begin (int nthreads, char *mem, int memsize);

void
nile_feed (nile_t *nl, nile_Kernel_t *k, nile_Real_t *data, int n, int eos);

void
nile_sync (nile_t *nl);

char *
nile_end (nile_t *nl);

nile_Kernel_t *
nile_Pipeline (nile_t *nl, ...) __attribute__ ((sentinel));

/* INTERNAL API */

#include <stddef.h>
#include <math.h>

#define real nile_Real_t

static inline real nile_Real_flr (real a)
    { real b = (int) a; return b > a ? b - 1 : b; }
static inline real nile_Real_clg (real a)
    { real b = (int) a; return b < a ? b + 1 : b; }
static inline real nile_Real_abs (real a) { return fabsf (a); }
static inline real nile_Real_sqr (real a) { return sqrtf (a); }
static inline real nile_Real_add (real a, real b) { return a + b; }
static inline real nile_Real_sub (real a, real b) { return a - b; }
static inline real nile_Real_mul (real a, real b) { return a * b; }
static inline real nile_Real_div (real a, real b) { return a / b; }
static inline real nile_Real_eq  (real a, real b) { return a == b; }
static inline real nile_Real_neq (real a, real b) { return a != b; }
static inline real nile_Real_lt  (real a, real b) { return a < b; }
static inline real nile_Real_gt  (real a, real b) { return a > b; }
static inline real nile_Real_leq (real a, real b) { return a <= b; }
static inline real nile_Real_geq (real a, real b) { return a >= b; }
static inline real nile_Real_or  (real a, real b) { return a || b; }
static inline real nile_Real_and (real a, real b) { return a && b; }
static inline real nile_Real_min (real a, real b) { return a < b ? a : b; }
static inline real nile_Real_max (real a, real b) { return a > b ? a : b; }
static inline real nile_Real_ave (real a, real b) { return (a + b) / 2; }
static inline real nile_Real_sel (real a, real b, real c) { return b ? a : c; }

#define NILE_BUFFER_SIZE 128

typedef struct nile_Buffer_ nile_Buffer_t;
struct nile_Buffer_ {
    nile_Buffer_t *next;
    int i;
    int n;
    int eos;
    real data[NILE_BUFFER_SIZE];
};

nile_Buffer_t *
nile_Buffer_new (nile_t *nl);

nile_Buffer_t *
nile_Buffer_clone (nile_t *nl, nile_Buffer_t *b);

void
nile_Buffer_free (nile_t *nl, nile_Buffer_t *b);

typedef nile_Buffer_t * (*nile_Kernel_process_t)
    (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *in, nile_Buffer_t *out, int *pause);

typedef void * (*nile_Kernel_clone_t) (nile_t *nl, void *k);

struct nile_Kernel_ {
    nile_Kernel_t *next;
    nile_Kernel_process_t process;
    nile_Kernel_clone_t clone;
    nile_Kernel_t *downstream;
    nile_Buffer_t *inbox;
    int initialized;
};

nile_Kernel_t *
nile_Kernel_new (nile_t *nl, nile_Kernel_process_t process,
                             nile_Kernel_clone_t clone);

#define NILE_KERNEL_NEW(nl, name) \
    ((name##_t *) nile_Kernel_new ((nl), name##_process, name##_clone))

static inline void *
nile_Kernel_clone (nile_t *nl, void *k_)
{
    nile_Kernel_t *k = (nile_Kernel_t *) k_;
    return nile_Kernel_new (nl, k->process, k->clone);
}

void
nile_Kernel_free (nile_t *nl, nile_Kernel_t *k);

void
nile_Kernel_pause (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *b, int *pause);

void
nile_Kernel_resume (nile_t *nl, nile_Kernel_t *k);

void
nile_deliver (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *b);

#define NILE_CONSUME_1(in, v) \
    real (v) = (in)->data[(in)->i++]

#define NILE_CONSUME_2(in, v1, v2) \
    NILE_CONSUME_1 (in, v1); NILE_CONSUME_1 (in, v2)

#define NILE_CONSUME_4(in, v1, v2, v3, v4) \
    NILE_CONSUME_2 (in, v1, v2); NILE_CONSUME_2 (in, v3, v4)

#define NILE_CONSUME_6(in, v1, v2, v3, v4, v5, v6) \
    NILE_CONSUME_2 (in, v1, v2); NILE_CONSUME_2 (in, v3, v4); \
    NILE_CONSUME_2 (in, v5, v6)

#define NILE_CONSUME_8(in, v1, v2, v3, v4, v5, v6, v7, v8) \
    NILE_CONSUME_4 (in, v1, v2, v3, v4); \
    NILE_CONSUME_4 (in, v5, v6, v7, v8)

#define NILE_PEEK_4(in, v1, v2, v3, v4) \
    real (v1) = (in)->data[(in)->i + 0]; \
    real (v2) = (in)->data[(in)->i + 1]; \
    real (v3) = (in)->data[(in)->i + 2]; \
    real (v4) = (in)->data[(in)->i + 3]

static inline nile_Buffer_t *
nile_flush_if_full (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *out, int quantum)
{
    if (out->n > NILE_BUFFER_SIZE - quantum) {
        nile_deliver (nl, k->downstream, out);
        out = nile_Buffer_new (nl);
    }
    return out;
}

static inline void
nile_produce_1 (nile_Buffer_t *out, real v)
    { out->data[out->n++] = v; }

static inline void
nile_produce_2 (nile_Buffer_t *out, real v1, real v2)
    { nile_produce_1 (out, v1); nile_produce_1 (out, v2); }

static inline void
nile_produce_4 (nile_Buffer_t *out, real v1, real v2, real v3, real v4)
    { nile_produce_2 (out, v1, v2); nile_produce_2 (out, v3, v4); }

static inline void
nile_produce_6 (nile_Buffer_t *out, real v1, real v2, real v3, real v4,
                real v5, real v6)
{
    nile_produce_2 (out, v1, v2);
    nile_produce_2 (out, v3, v4);
    nile_produce_2 (out, v5, v6);
}

static inline nile_Buffer_t *
nile_produce_1_repeat (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *out,
                       int quantum, int times, real v)
{
    while (times) {
        int room = (NILE_BUFFER_SIZE - out->n) / quantum;
        int n = times < room ? times : room;
        times -= n;
        while (n--)
            nile_produce_1 (out, v);
        out = nile_flush_if_full (nl, k, out, quantum);
    }
    return out;
}

static inline nile_Buffer_t *
nile_recurse (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *r, nile_Buffer_t *out)
{
    return k->process (nl, k, r, out, NULL);
}

static inline nile_Buffer_t *
nile_recurse_if_full (nile_t *nl, nile_Kernel_t *k,
                      nile_Buffer_t *r, int quantum, nile_Buffer_t *out)
{
    if (r->n > NILE_BUFFER_SIZE - quantum) {
        out = nile_recurse (nl, k, r, out);
        r->i = 0;
        r->n = 0;
    }
    return out;
}

nile_Kernel_t *
nile_Interleave (nile_t *nl, nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2);

nile_Kernel_t *
nile_GroupBy (nile_t *nl, int index, int quantum, nile_Kernel_t *k);

nile_Kernel_t *
nile_SortBy (nile_t *nl, int index, int quantum);

#undef real

#endif
