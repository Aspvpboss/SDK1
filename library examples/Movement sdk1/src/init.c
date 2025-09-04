#include "init.h"


int App_Init(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    if(SDK_Init()){
        return 1;
    }

    if(SDK_CreateDisplay(display, "SDK Window", 1000, 1000, SDL_WINDOW_MAXIMIZED)){
        return 1;
    }

    if(SDK_CreateTime(time, 400)){
        return 1;
    }

    if(SDK_CreateInput(input)){     
        return 1;
    }

    player->rect.h = 40;
    player->rect.w = 40;
    player->rect.x = 0.0f;
    player->rect.y = 0.0f;
    player->x_velocity = 400;
    player->y_velocity = 400;

    player->texture = IMG_LoadTexture(display->renderer, "./assets/blue.bmp");
    if(player->texture == NULL){
        return 1;
    }

    return 0;
}



