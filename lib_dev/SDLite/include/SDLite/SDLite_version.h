/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_VERSION_H
#define SDLite_VERSION_H

#ifdef __cplusplus
extern "C"{
#endif

#include "SDLite/common_libs.h"

#define SDLITE_MAJOR_VERSION 1
#define SDLITE_MINOR_VERSION 2
#define SDLITE_MICRO_VERSION 3

/* 
    takes in int* and writes the version numbers to those pointers

    Can be called from any thread

    returns early if any pointer is NULL
*/
SDLite_DLL void SDLite_Version_GetNumbers(int *major, int *minor, int *micro);

#ifdef __cplusplus
}
#endif

#endif
