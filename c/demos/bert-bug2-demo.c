#include <stdio.h>
#include "gezira.h"

typedef nile_Real_t real;

real path[] =
{
    7.391, 4.336, 7.391, 4.336, 8.977, 4.336,
    8.977, 4.336, 8.977, 4.336, 8.977, 11.422,
    8.977, 11.422, 8.977, 13.297, 9.656, 14.125,
    9.656, 14.125, 10.336, 14.945, 11.859, 14.945,
    11.859, 14.945, 13.375, 14.945, 14.055, 14.125,
    14.055, 14.125, 14.734, 13.297, 14.734, 11.422,
    14.734, 11.422, 14.734, 11.422, 14.734, 4.336,
    14.734, 4.336, 14.734, 4.336, 16.32, 4.336,
    16.32, 4.336, 16.32, 4.336, 16.32, 11.617,
    16.32, 11.617, 16.32, 13.898, 15.188, 15.063,
    15.188, 15.063, 14.063, 16.227, 11.859, 16.227,
    11.859, 16.227, 9.648, 16.227, 8.516, 15.063,
    8.516, 15.063, 7.391, 13.898, 7.391, 11.617,
    7.391, 11.617, 7.391, 11.617, 7.391, 4.336
};
int path_n = sizeof (path) / sizeof (path[0]);

int
main (int argc, char **argv)
{
    nile_t *nl;
    char mem[500000];
    real bounds[4];
    int n = 0;

    nl = nile_new (0, mem, sizeof (mem));

    nile_Kernel_t *pipeline = nile_Pipeline (nl,
            /*
        gezira_StrokeBeziers (nl, 0, gezira_StrokeJoinMiter (nl, 0.25, 0),
                                     gezira_StrokeJoinMiter (nl, 0.25, 0)),
                                     */
        gezira_CalculateBounds (nl),
        nile_Capture (nl, bounds, 4, &n),
        NULL);

    nile_feed (nl, pipeline, path, 6, path_n, 1);
    nile_sync (nl);

    printf ("(%.2f, %.2f) (%.2f, %.2f)\n",
            bounds[0], bounds[1], bounds[2], bounds[3]);

    nile_free (nl);
    printf ("done\n");

    return 0;
}
