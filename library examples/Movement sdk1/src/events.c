#include "events.h"

void limit_position(float *value, int max_limit){
    if(*value < 0)
        *value = 0;
    if(*value > max_limit)
        *value = max_limit;
}

int App_Events(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    SDL_Event e;
    while(SDL_PollEvent(&e)){
        if(e.type == SDL_EVENT_QUIT){
            return 1;
        }
    }

    if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_F11)){
        
        Uint32 flags = SDL_GetWindowFlags(display->window);

        if(flags & SDL_WINDOW_FULLSCREEN) {
            SDK_DisplaySetWindowed(display, 500, 500);
        } else{
            SDK_DisplaySetFullscreen(display);
        }
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_D)){
        player->rect.x += (player->x_velocity * time->dt);
        limit_position(&player->rect.x, display->width - player->rect.w);
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_A)){
        player->rect.x -= (player->x_velocity * time->dt);
        limit_position(&player->rect.x, display->width - player->rect.w);
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_S)){
        player->rect.y += (player->y_velocity * time->dt);
        limit_position(&player->rect.y, display->height - player->rect.h);
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_W)){
        player->rect.y -= (player->y_velocity * time->dt);
        limit_position(&player->rect.y, display->height - player->rect.h);
    }

    SDK_Update_Previous_KeyboardState(input);

    return 0;
}


