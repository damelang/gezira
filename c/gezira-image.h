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
gezira_WriteToImage_ARG32_UniformColor (nile_Process_t *p, uint32_t *pixels,
                                        int width, int height, int stride,
                                        float a, float r, float g, float b);

#endif
