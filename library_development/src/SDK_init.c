#include "SDK_init.h"

static MemTrack_Context ctx;

int SDK_Init(){

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        return 1;
    }

    if(!TTF_Init()){
        return 1;
    }


    ctx.config.memory_failure_abort = true;
    ctx.config.print_error_info = true;

    Set_MemTrack_Context(&ctx);

    return 0;
}


void SDK_Quit(){

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_Quit();
    TTF_Quit();

    if(check_memory_leak())
        print_tracking_info();

    free_tracking_info();

}