#ifndef GEZIRA_IMAGE_H
#define GEZIRA_IMAGE_H

#include "nile.h"

typedef struct {
    void           *pixels;
    int             width;
    int             height;
    int             stride;
    nile_Process_t *gate;
} gezira_Image_t;

void
gezira_Image_init (gezira_Image_t *image, void *pixels, int width, int height, int stride);

void
gezira_Image_done (gezira_Image_t *image);

void
gezira_Image_reset_gate (gezira_Image_t *image);

nile_Process_t *
gezira_ReadFromImage_ARGB32 (nile_Process_t *p, gezira_Image_t *image, int skipNextGate);

nile_Process_t *
gezira_WriteToImage_ARGB32 (nile_Process_t *p, gezira_Image_t *image);

nile_Process_t *
gezira_CompositeUniformColorOverImage_ARGB32 (nile_Process_t *p, gezira_Image_t *image,
                                              float a, float r, float g, float b);

#endif
