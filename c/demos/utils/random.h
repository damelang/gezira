#ifndef GEZIRA_RANDOM_H
#define GEZIRA_RANDOM_H

#include <stdlib.h>

static float
gezira_random (float min, float max)
{
    static int called_srand = 0;
    if (!called_srand)
        srand (1234567);
    called_srand = 1;
    return rand () / (float) RAND_MAX * (max - min) + min;
}

#endif
