#ifndef NILE_H
#define NILE_H

#include <math.h>

typedef float nile_Real;

inline nile_Real nile_Real_flr (nile_Real a)
    { nile_Real b = (int) a; return b > a ? b - 1 : b; }
inline nile_Real nile_Real_clg (nile_Real a)
    { nile_Real b = (int) a; return b < a ? b + 1 : b; }
inline nile_Real nile_Real_abs (nile_Real a) { return fabsf(a); }
inline nile_Real nile_Real_sqr (nile_Real a) { return sqrtf(a); }
inline nile_Real nile_Real_add (nile_Real a, nile_Real b) { return a + b; }
inline nile_Real nile_Real_sub (nile_Real a, nile_Real b) { return a - b; }
inline nile_Real nile_Real_mul (nile_Real a, nile_Real b) { return a * b; }
inline nile_Real nile_Real_div (nile_Real a, nile_Real b) { return a / b; }
inline nile_Real nile_Real_eq  (nile_Real a, nile_Real b) { return a == b; }
inline nile_Real nile_Real_neq (nile_Real a, nile_Real b) { return a != b; }
inline nile_Real nile_Real_lt  (nile_Real a, nile_Real b) { return a < b; }
inline nile_Real nile_Real_gt  (nile_Real a, nile_Real b) { return a > b; }
inline nile_Real nile_Real_leq (nile_Real a, nile_Real b) { return a <= b; }
inline nile_Real nile_Real_geq (nile_Real a, nile_Real b) { return a >= b; }
inline nile_Real nile_Real_or  (nile_Real a, nile_Real b) { return a || b; }
inline nile_Real nile_Real_and (nile_Real a, nile_Real b) { return a && b; }
inline nile_Real nile_Real_min (nile_Real a, nile_Real b) { return a < b ? a : b; }
inline nile_Real nile_Real_max (nile_Real a, nile_Real b) { return a > b ? a : b; }
inline nile_Real nile_Real_ave (nile_Real a, nile_Real b) { return (a + b) / 2; }

#endif
