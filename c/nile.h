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

typedef struct
{
    int n;
    int quantum;
    int capacity;
    nile_Real_t *data;
} nile_Buffer_t;

typedef struct nile_Kernel_ nile_Kernel_t;

struct nile_Kernel_
{
    void (*process) (nile_Kernel_t *k, nile_Buffer_t *in, nile_Buffer_t **out);
    nile_Kernel_t *downstream;
};

nile_Kernel_t *
nile_pipeline (nile_Kernel_t *k0, ...) __attribute__ ((sentinel));

void
nile_emit (nile_Buffer_t **out, nile_Kernel_t *k);

#endif
