#ifndef GEZIRA_IMAGE_H
#define GEZIRA_IMAGE_H

#include "nile.h"

#if defined( _MSC_VER)
typedef unsigned __int32 uint32_t;
#else
#include <stdint.h>
#endif

nile_Kernel_t *
gezira_ReadImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                         int width, int height, int stride);

nile_Kernel_t *
gezira_WriteImage_ARGB32 (nile_t *nl, uint32_t *pixels,
                          int width, int height, int stride);

#endif
