/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_COMMON_LIBS_H
#define SDLite_COMMON_LIBS_H

#ifdef __cplusplus
extern "C"{
#endif

#ifdef _WIN32
    #ifdef DLL_EXPORTS
        #define SDLite_DLL __declspec(dllexport)
    #elif defined(STATIC_LINK)
        #define SDLite_DLL
    #else
        #define SDLite_DLL __declspec(dllimport)
    #endif
#else
    #define SDLite_DLL
#endif



#include "SDLite/SDL3_mixer/SDL_mixer.h" 
#include "SDLite/SDL3/SDL.h"
#include "SDLite/SDL3_image/SDL_image.h"
#include "SDLite/SDL3_ttf/SDL_ttf.h"
#include "SDLite/Memtrack.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#ifdef __cplusplus
}
#endif


#endif
