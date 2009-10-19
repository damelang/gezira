/* gezira_WriteImage and gezira_ReadImage must be supplied by the
   host system!
*/

MEMSIZE = 1000000;

/* Call this as infrequently as you can, ideally once per application */
nile_t *nl = nile_begin (1, malloc (MEMSIZE), MEMSIZE);

...

/* This is fast, so you can do this frequently in your application */
nile_Kernel_t *pipeline = nile_Pipeline (nl,
    gezira_TransformBezier (nl, a, b, c, d, e, f),
    gezira_DecomposeBezier (nl),
    gezira_Render (nl, gezira_UniformColor (nl, 1, 0.5, 0.5, 0),
                       gezira_WriteImage (nl, image)),
    NULL);

/* Pass in bezier points */
nile_feed (nl, pipeline, beziers, nfloats, 1);

...

/* At the very end */
free (nile_end (nl));
