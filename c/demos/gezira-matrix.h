#ifndef GEZIRA_MATRIX_H
#define GEZIRA_MATRIX_H

typedef struct {
    float a, b, c, d, e, f;
} matrix_t;

matrix_t
matrix_new () {
    matrix_t M = { 1, 0, 0, 1, 0, 0 };
    return M;
}

matrix_t
matrix_translate (matrix_t M, float x, float y)
{
    matrix_t N = { M.a, M.b, M.c, M.d,
                   M.a * x + M.c * y + M.e,
                   M.b * x + M.d * y + M.f};
    return N;
}

matrix_t
matrix_rotate (matrix_t M, float t)
{
    matrix_t N = { M.a *  cos (t) + M.c * sin (t),
                   M.b *  cos (t) + M.d * sin (t),
                   M.a * -sin (t) + M.c * cos (t),
                   M.b * -sin (t) + M.d * cos (t),
                   M.e, M.f};
    return N;
}

matrix_t
matrix_scale (matrix_t M, float sx, float sy)
{
    matrix_t N = { M.a * sx, M.b * sx, M.c * sy, M.d * sy, M.e, M.f};
    return N;
}

#endif
