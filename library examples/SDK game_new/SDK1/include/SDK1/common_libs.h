#pragma once

#ifdef _WIN32
    #ifdef DLL_EXPORTS
        #define SDK1_API __declspec(dllexport)
    #elif defined(STATIC_LINK)
        #define SDK1_API
    #else
        #define SDK1_API __declspec(dllimport)
    #endif
#else
    #define SDK1_API
#endif




#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <MemTrack.h>


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
