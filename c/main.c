#include <stdio.h>
#include "gezira.h"

int
main ()
{
    char memory[100000];
    nile_t *n = nile_begin (memory, sizeof (memory), 4);
    nile_end (n);
    printf ("done\n");
    return 0;
}
