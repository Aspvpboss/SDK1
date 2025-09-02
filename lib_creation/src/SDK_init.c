#include "SDK_init.h"


int SDK_Init(){

    if(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)){
        return 1;
    }

    if(!TTF_Init()){
        return 1;
    }

    return 0;
}


void SDK_Quit(){

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
    SDL_Quit();
    TTF_Quit();

}