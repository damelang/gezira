#ifndef NILE_H
#define NILE_H

#include <math.h>

typedef float nile_Real_t;
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

#undef real

typedef struct nile_Context_ nile_Context_t;

typedef struct {
    nile_Real_t *data;
    int n;
    int capacity;
} nile_Buffer_t;

typedef struct nile_Kernel_ nile_Kernel_t;

struct nile_Kernel_ {
    void (*process) (nile_Kernel_t *k, nile_Buffer_t *in,
                     nile_Buffer_t **out, nile_Context_t *c);
    nile_Kernel_t *downstream;
    int initialized;
};

nile_Context_t *
nile_Context ();

void
nile_free_Context (nile_Context_t *c);

nile_Kernel_t *
nile_pipeline (nile_Kernel_t *k0, ...) __attribute__ ((sentinel));

/* TODO need to rename. This is the "end user" entry point */
void
nile_feed (nile_Kernel_t *k, nile_Real_t *data, int n, nile_Context_t *c);

/* TODO need to rename/refactor. This is "internal" and puts a new buffer in 'out' */
void
nile_flush (nile_Kernel_t *k, nile_Buffer_t **out, nile_Context_t *c);

typedef struct {
    nile_Kernel_t kernel;
    nile_Kernel_t *v_k1;
    int v_quantum1;
    nile_Kernel_t *v_k2;
    int v_quantum2;
    /* TODO */
} nile_Interleave_t;

nile_Kernel_t *
nile_Interleave (nile_Interleave_t *k,
                 nile_Kernel_t *k1, int quantum1,
                 nile_Kernel_t *k2, int quantum2);

#endif
