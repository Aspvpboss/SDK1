
#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL_main.h"
#include "init.h"

// bruh why do these need to be extern "C", I strongly dislike C++
extern "C" SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    SDLite_Init(NULL, NULL, true, false);

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    state->display = SDLite_CreateDisplay("SDLite game", 1000, 800, SDL_WINDOW_MAXIMIZED);
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->time = SDLite_CreateTime(144);
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->input = SDLite_CreateInput();
    if(!state->input){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    static const SDL_Color white = {255, 255, 255, 255};

    state->fps_text = SDLite_CreateText(
        state->display, NULL, "assets/default.ttf", 30, 0, 0, white);
    
        
    if(!state->fps_text){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    
    return SDL_APP_CONTINUE;
}
