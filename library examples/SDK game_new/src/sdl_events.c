#include "sdl_events.h"


SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){

    Appstate *state = (Appstate*)(appstate);

    return SDL_APP_CONTINUE;
}