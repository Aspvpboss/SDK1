#define SDL_MAIN_USE_CALLBACKS 1

#include "common.h"
#include "SDL3/SDL_main.h"



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    Appstate *state = malloc(sizeof(Appstate));
    state->Text.amount_text = 1;

    if(SDK_Init()){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    if(SDK_CreateDisplay(&state->display, "SDK game", 800, 800, SDL_WINDOW_MAXIMIZED)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(SDK_CreateTime(&state->time, 11000)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    if(SDK_CreateInput(&state->input)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    state->Text.text_array = malloc(sizeof(SDK_TextDisplay));

    if(SDK_CreateText(&state->Text.text_array[FPS_TEXT], &state->display, NULL, 20, 0, 0, (SDL_Color){255, 255, 255, 255})){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    if(player_init(state)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;          
    }

    


    
    *appstate = state;

    return SDL_APP_CONTINUE;
}

