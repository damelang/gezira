#include <stdio.h>
#include "gezira.h"

int
main ()
{
    char memory[100000];
    nile_t *nl = nile_begin (4, memory, sizeof (memory));
    nile_end (nl);
    printf ("done\n");
    return 0;
}
