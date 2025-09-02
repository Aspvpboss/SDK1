#pragma once

#include "common_libs.h"

/*
    initializes all SDL systems for SDK

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
SDK1_API int SDK_Init();

/*
    deinitializes all SDL systems for SDK
*/
SDK1_API void SDK_Quit();