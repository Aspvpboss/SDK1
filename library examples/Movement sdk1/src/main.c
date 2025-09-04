#include "common.h"


int main(){

    SDK_Input input;
    SDK_Display display;
    SDK_Time time;
    Player player;

    if(App_Init(&display, &time, &input, &player)){
        SDL_Log("Error %s", SDL_GetError());
        return 1;
    }

    if(App_Iterate(&display, &time, &input, &player)){
        SDL_Log("Error %s", SDL_GetError());
        return 1;
    }

    App_Quit(&display, &time, &input, &player);

    return 0;
}


