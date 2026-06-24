/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_INIT_H
#define SDLite_INIT_H

#ifdef __cplusplus
extern "C" {
#endif



#include "SDLite/common_libs.h"

/*
    These functions can be called from any thread, but you should only call them once anyways
*/


/*
    initializes all SDL systems, and MemTrack for SDK

    void (*func)(void*) is a optional function you can pass to run if malloc fails
    void *func_data is the void pointer that gets passed into void(*func)(void*)

    **
    **
    
    if bool memory_failure_abort is set to true, then if malloc fails the program will abort

    if bool print_memtrack_info is set to true, then MemTrack will print debug info

    if bool auto_null_pointers is set to true, then pointers you free will automatically be set to null
    

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
SDLite_DLL int SDLite_Init(
    void (*func)(void*), void *func_data, bool memory_failure_abort, bool auto_null_pointers);

/*
    deinitializes all SDL systems, and MemTrack for SDK
    
    If you are using SDK1_debug, it will print tracking info for any memory you haven't freed
*/
SDLite_DLL void SDLite_Quit();

#ifdef __cplusplus
}
#endif



#endif
