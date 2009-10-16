#ifndef NILE_H
#define NILE_H

/* EXTERNAL API */

typedef float nile_Real_t;
typedef struct nile_Kernel_ nile_Kernel_t;
typedef struct nile_ nile_t;

nile_t *
nile_begin (char *memory, int msize, int nthreads);

char *
nile_end (nile_t *n);

void
nile_feed (nile_t *n, nile_Kernel_t *p, nile_Real_t *data, int ndata, int eos);

nile_Kernel_t *
nile_Pipeline (nile_t *n, ...) __attribute__ ((sentinel));

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
typedef struct {
    int n;
    int eos;
    real data[NILE_BUFFER_SIZE];
} nile_Buffer_t;

struct nile_Kernel_ {
    void (*process) (nile_t *n, nile_Kernel_t *k,
                     nile_Buffer_t *in, nile_Buffer_t **out);
    int size;
    nile_Kernel_t *downstream;
    int initialized;
};

#define NILE_KERNEL_INIT(n, k, name) do { \
    nile_Kernel_t *b = (nile_Kernel_t *) nile_alloc (n, sizeof (name##_t)); \
    b->process = name##_process; \
    b->size = sizeof (name##_t); \
    b->initialized = 0; \
    k = (name##_t *) b; \
} while (0)

nile_Kernel_t *
nile_Kernel_clone (nile_t *n, nile_Kernel_t *k);

char *
nile_alloc (nile_t *n, int size);

void
nile_forward (nile_t *n, nile_Kernel_t *k,
              nile_Buffer_t *in, nile_Buffer_t **out);

void
nile_flush (nile_t *n, nile_Kernel_t *k, nile_Buffer_t **out);

void
nile_reschedule (nile_t *n, nile_Kernel_t *k, nile_Buffer_t *in, int i);

static inline void
nile_flush_if_full (nile_t *n, nile_Kernel_t *downstream,
                    nile_Buffer_t *b, nile_Buffer_t **out, int quantum)
{
    if (b->n > NILE_BUFFER_SIZE - quantum) {
        nile_flush (n, downstream, out);
        b = *out;
    }
}

static inline void
nile_recurse_if_full (nile_t *n, nile_Kernel_t *k,
                      nile_Buffer_t *b, int quantum, nile_Buffer_t **out)
{
    if (b->n > NILE_BUFFER_SIZE - quantum) {
        k->process (n, k, b, out);
        b->n = 0;
    }
}

#define NILE_CONSUME_1(b, i, v) \
    real (v) = (b)->data[(i)++]

#define NILE_CONSUME_2(b, i, v1, v2) \
    NILE_CONSUME_1 (b, i, v1); NILE_CONSUME_1 (b, i, v2)

#define NILE_CONSUME_4(b, i, v1, v2, v3, v4) \
    NILE_CONSUME_2 (b, i, v1, v2); NILE_CONSUME_2 (b, i, v3, v4)

#define NILE_CONSUME_6(b, i, v1, v2, v3, v4, v5, v6) \
    NILE_CONSUME_2 (b, i, v1, v2); NILE_CONSUME_2 (b, i, v3, v4); \
    NILE_CONSUME_2 (b, i, v5, v6)

#define NILE_CONSUME_8(b, i, v1, v2, v3, v4, v5, v6, v7, v8) \
    NILE_CONSUME_4 (b, i, v1, v2, v3, v4); \
    NILE_CONSUME_4 (b, i, v5, v6, v7, v8)

#define NILE_PEEK_4(b, v1, v2, v3, v4) \
    real (v1) = (b)->data[0]; \
    real (v2) = (b)->data[1]; \
    real (v3) = (b)->data[2]; \
    real (v4) = (b)->data[3]

static inline void
nile_produce_1 (nile_Buffer_t *b, real v)
    { b->data[b->n++] = v; }

static inline void
nile_produce_2 (nile_Buffer_t *b, real v1, real v2)
    { nile_produce_1 (b, v1); nile_produce_1 (b, v2); }

static inline void
nile_produce_4 (nile_Buffer_t *b, real v1, real v2, real v3, real v4)
    { nile_produce_2 (b, v1, v2); nile_produce_2 (b, v3, v4); }

static inline void
nile_produce_6 (nile_Buffer_t *b, real v1, real v2, real v3, real v4, real v5, real v6)
    { nile_produce_2 (b, v1, v2); nile_produce_2 (b, v3, v4); nile_produce_2 (b, v5, v6); }

static inline void
nile_produce_1_repeat (nile_t *n, nile_Kernel_t *downstream,
                       nile_Buffer_t *o, nile_Buffer_t **out, int quantum,
                       int times, real v)
{
    for (;;) {
        int room = (NILE_BUFFER_SIZE - o->n) / quantum;
        int n_ = times < room ? times : room;
        times -= n_;
        while (n_--)
            nile_produce_1 (o, v);
        if (times == 0) {
            nile_flush_if_full (n, downstream, o, out, quantum);
            break;
        }
        nile_flush (n, downstream, out);
        o = *out;
    }
}

nile_Kernel_t *
nile_Interleave (nile_t *n, nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2);

nile_Kernel_t *
nile_GroupBy (nile_t *n, int index, int quantum, nile_Kernel_t *k);

nile_Kernel_t *
nile_SortBy (nile_t *n, int index, int quantum);

#undef real

#endif
