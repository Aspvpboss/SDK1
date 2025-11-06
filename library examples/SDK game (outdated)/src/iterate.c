#include "common.h"
#include "render.h"
#include "update.h"
#include "events.h"



SDL_AppResult SDL_AppIterate(void *appstate){

    Appstate *state = (Appstate*)appstate;

    if(frame_events(state)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;          
    }

    if(App_Update(state)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;    
    }

    if(App_Render(state)){
        SDL_Log("%s\n", SDL_GetError());
        return SDL_APP_FAILURE;            
    }
    

    return SDL_APP_CONTINUE;
}