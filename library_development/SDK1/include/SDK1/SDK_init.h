#pragma once

#include "common_libs.h"

/*
    initializes all SDL systems for SDK

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
SDK1_API int SDK_Init(bool memory_failure_abort, bool print_memtrack_info, bool auto_null_pointers);

/*
    deinitializes all SDL systems for SDK
*/
SDK1_API void SDK_Quit();