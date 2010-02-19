#ifndef GEZIRA_IMAGE_H
#define GEZIRA_IMAGE_H

#include "nile.h"

nile_Kernel_t *
gezira_ReadImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                         int width, int height, int stride);

nile_Kernel_t *
gezira_WriteImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                          int width, int height, int stride);

#endif
