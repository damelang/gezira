#ifndef NILE_H
#define NILE_H

/* EXTERNAL API */

typedef float nile_Real_t;
typedef struct nile_Kernel_ nile_Kernel_t;
typedef struct nile_ nile_t;

nile_t *
nile_begin (int nthreads, char *mem, int memsize);

nile_Kernel_t *
nile_Pipeline (nile_t *nl, ...) __attribute__ ((sentinel));

void
nile_feed (nile_t *nl, nile_Kernel_t *p, nile_Real_t *data, int n, int eos);

char *
nile_end (nile_t *nl);

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
    int n;
    int eos;
    nile_Buffer_t *next;
    real data[NILE_BUFFER_SIZE];
};

/* FIXME arbitrary garbage below */
#define NILE_KERNEL_MAX_SIZE (20 * sizeof (void *))

typedef int (*nile_Kernel_process_t)
    (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t *in, int i, nile_Buffer_t **out);

typedef nile_Kernel_t * (*nile_Kernel_clone_t) (nile_t *nl, nile_Kernel_t *k);

struct nile_Kernel_ {
    nile_Kernel_process_t process;
    nile_Kernel_clone_t clone;
    int initialized;
    nile_Kernel_t *next;
};

nile_Kernel_t *
nile_Kernel_new (nile_t *nl, nile_Kernel_process_t process,
                             nile_Kernel_clone_t clone);

#define NILE_KERNEL_NEW (n, name) \
    (name##_t *) nile_Kernel_new (n, name##_process, name##_clone)

void
nile_forward (nile_t *nl, nile_Kernel_t *k,
              nile_Buffer_t *in, int i, nile_Buffer_t **out);

void
nile_flush (nile_t *nl, nile_Kernel_t *k, nile_Buffer_t **out);

static inline void
nile_flush_if_full (nile_t *nl, nile_Kernel_t *k,
                    nile_Buffer_t **out, int quantum)
{
    if ((*out)->n > NILE_BUFFER_SIZE - quantum)
        nile_flush (nl, k, out);
}

static inline void
nile_recurse_if_full (nile_t *nl, nile_Kernel_t *k,
                      nile_Buffer_t *r, int quantum, nile_Buffer_t **out)
{
    if (r->n > NILE_BUFFER_SIZE - quantum) {
        k->process (nl, k, r, 0, out);
        r->n = 0;
    }
}

#define NILE_CONSUME_1(in, i, v) \
    real (v) = (in)->data[(i)++]

#define NILE_CONSUME_2(in, i, v1, v2) \
    NILE_CONSUME_1 (in, i, v1); NILE_CONSUME_1 (in, i, v2)

#define NILE_CONSUME_4(in, i, v1, v2, v3, v4) \
    NILE_CONSUME_2 (in, i, v1, v2); NILE_CONSUME_2 (in, i, v3, v4)

#define NILE_CONSUME_6(in, i, v1, v2, v3, v4, v5, v6) \
    NILE_CONSUME_2 (in, i, v1, v2); NILE_CONSUME_2 (in, i, v3, v4); \
    NILE_CONSUME_2 (in, i, v5, v6)

#define NILE_CONSUME_8(in, i, v1, v2, v3, v4, v5, v6, v7, v8) \
    NILE_CONSUME_4 (in, i, v1, v2, v3, v4); \
    NILE_CONSUME_4 (in, i, v5, v6, v7, v8)

#define NILE_PEEK_4(in, v1, v2, v3, v4) \
    real (v1) = (in)->data[0]; \
    real (v2) = (in)->data[1]; \
    real (v3) = (in)->data[2]; \
    real (v4) = (in)->data[3]

static inline void
nile_produce_1 (nile_Buffer_t **out, real v)
    { (*out)->data[(*out)->n++] = v; }

static inline void
nile_produce_2 (nile_Buffer_t **out, real v1, real v2)
    { nile_produce_1 (out, v1); nile_produce_1 (out, v2); }

static inline void
nile_produce_4 (nile_Buffer_t **out, real v1, real v2, real v3, real v4)
    { nile_produce_2 (out, v1, v2); nile_produce_2 (out, v3, v4); }

static inline void
nile_produce_6 (nile_Buffer_t **out, real v1, real v2, real v3, real v4,
                real v5, real v6)
{
    nile_produce_2 (out, v1, v2);
    nile_produce_2 (out, v3, v4);
    nile_produce_2 (out, v5, v6);
}

static inline void
nile_produce_1_repeat (nile_t *nl, nile_Kernel_t *k,
                       nile_Buffer_t **out, int quantum, int times, real v)
{
    while (times) {
        int room = (NILE_BUFFER_SIZE - (*out)->n) / quantum;
        int n = times < room ? times : room;
        times -= n;
        while (n--)
            nile_produce_1 (out, v);
        nile_flush_if_full (nl, k, out, quantum);
    }
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
