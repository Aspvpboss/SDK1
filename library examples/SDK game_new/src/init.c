
#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>

#include "init.h"



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    
    return SDL_APP_CONTINUE;
}