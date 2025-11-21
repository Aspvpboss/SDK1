#pragma once

#include "common_libs.h"

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
SDK1_API int SDK_Init(
    void (*func)(void*), void *func_data, bool memory_failure_abort, bool print_memtrack_info, bool auto_null_pointers);

/*
    deinitializes all SDL systems, and MemTrack for SDK
    
    If you are using SDK1_debug, it will print tracking info for any memory you haven't freed
*/
SDK1_API void SDK_Quit();