/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/


// some complex stuff here
#include "SDLite/SDLite_version.h"
void SDLite_Version_GetNumbers(int *major, int *minor, int *micro){
    if(!major || !minor || !micro) return; 

    *major = SDLITE_MAJOR_VERSION;
    *minor = SDLITE_MINOR_VERSION;
    *micro = SDLITE_MICRO_VERSION;
}
