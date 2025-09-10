#include "common.h"

int frame_events(Appstate *state){

    PlayerClass *Player = &state->Player;

    Player->player_func.handle_events(state, 0);
    
    return 0;
}



SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    Appstate *state = (Appstate*)appstate;

    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

