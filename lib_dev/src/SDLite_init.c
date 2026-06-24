/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_init.h"


int SDLite_Init(void (*func)(void*), void *func_data, bool memory_failure_abort, bool auto_null_pointers){

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        return 1;
    }

    if(!TTF_Init()){
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        SDL_Quit();
        return 1;
    }

    if(!MIX_Init()){
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        SDL_Quit();
        TTF_Quit();
        return 1;
    }

    if(MemTrack_Init(func, func_data, memory_failure_abort, auto_null_pointers)){
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        SDL_Quit();
        TTF_Quit();
        MIX_Quit();
        return 1;
    }

    return 0;
}


void SDLite_Quit(){

    TTF_Quit();
    MIX_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_Quit();

    if(check_memory_leak())
        print_tracking_info();

    MemTrack_Quit();

}
