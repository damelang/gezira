#ifndef GEZIRA_IMAGE_H
#define GEZIRA_IMAGE_H

#include <stdint.h>
#include "nile.h"

nile_Process_t *
gezira_ReadFromImage_ARGB32 (nile_Process_t *p, uint32_t *pixels,
                             int width, int height, int stride);

nile_Process_t *
gezira_WriteToImage_ARGB32 (nile_Process_t *p, uint32_t *pixels,
                            int width, int height, int stride);

nile_Process_t *
gezira_CompositeUniformColorOverImage_ARGB32 (nile_Process_t *p,
                                              float a, float r, float g, float b,
                                              uint32_t *pixels,
                                              int width, int height, int stride);

#endif
