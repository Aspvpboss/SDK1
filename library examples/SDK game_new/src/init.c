
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include <SDL3/SDL_main.h>



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    state->display = SDK_CreateDisplay("SDK game", 1000, 800, SDL_WINDOW_MAXIMIZED);
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->time = SDK_CreateTime(144);
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->input = SDK_CreateInput();
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->text_manager.amount_text = 0;
    state->text_manager.texts = NULL;
    
    state->s_sprite_manager.amount_sprites = 0;
    state->s_sprite_manager.sprites = NULL;

    state->a_sprite_manager.amount_sprites = 0;
    state->a_sprite_manager.sprites = NULL;
    
    return SDL_APP_CONTINUE;
}