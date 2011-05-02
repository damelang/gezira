#ifndef GEZIRA_MATRIX_H
#define GEZIRA_MATRIX_H

#include <math.h>

typedef struct {
    float a, b, c, d, e, f;
} Matrix_t;

static Matrix_t
Matrix ()
{
    Matrix_t M = { 1, 0, 0, 1, 0, 0 };
    return M;
}

static Matrix_t
Matrix_translate (Matrix_t M, float x, float y)
{
    Matrix_t M_ = { M.a, M.b, M.c, M.d,
                    M.a * x + M.c * y + M.e,
                    M.b * x + M.d * y + M.f };
    return M_;
}

static Matrix_t
Matrix_rotate (Matrix_t M, float t)
{
    Matrix_t M_ = { M.a *  cos (t) + M.c * sin (t),
                    M.b *  cos (t) + M.d * sin (t),
                    M.a * -sin (t) + M.c * cos (t),
                    M.b * -sin (t) + M.d * cos (t),
                    M.e, M.f };
    return M_;
}

static Matrix_t
Matrix_scale (Matrix_t M, float sx, float sy)
{
    Matrix_t M_ = { M.a * sx, M.b * sx, M.c * sy, M.d * sy, M.e, M.f };
    return M_;
}

#endif
