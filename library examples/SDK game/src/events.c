#include "common.h"

int frame_events(Appstate *state){

    PlayerClass *Player = &state->Player;

    for(int i = 0; i < Player->amount_players; i++){
        Player->player_func[i].handle_events(state, i);
    }


    return 0;
}



SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    Appstate *state = (Appstate*)appstate;

    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

