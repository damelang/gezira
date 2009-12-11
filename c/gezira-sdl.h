#ifndef GEZIRA_SDL_H
#define GEZIRA_SDL_H

#include "gezira.h"
#include "SDL.h"

nile_Kernel_t *
gezira_SDL_ReadImage (nile_t *nl, SDL_Surface *image);

nile_Kernel_t *
gezira_SDL_WriteImage (nile_t *nl, SDL_Surface *image);

#endif
