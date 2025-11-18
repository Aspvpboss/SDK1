#include "sdl_events.h"


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    // Appstate *state = (Appstate*)(appstate);

    if(event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS;

    return SDL_APP_CONTINUE;
}