#include <stddef.h>
#include <stdarg.h>
#include "nile.h"

nile_Kernel_t *
nile_pipeline (nile_Kernel_t *k0, ...)
{
    va_list args;
    nile_Kernel_t *ki, *kj;

    va_start (args, k0); 
    ki = k0;
    do {
        kj = va_arg (args, nile_Kernel_t *);
        ki->downstream = kj;
        ki = kj;
    } while (ki == NULL);

    va_end (args);
    return k0;
}

void
nile_emit (nile_Buffer_t **out, nile_Kernel_t *k)
{
    /* TODO */
}
