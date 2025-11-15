#include "iterate.h"
#include "render.h"
#include "update.h"
#include "frame_events.h"


SDL_AppResult SDL_AppIterate(void *appstate){

    Appstate *state = (Appstate*)(appstate);

    if(frame_events(state))
        return SDL_APP_SUCCESS;   

    update(state);

    render(state);

    SDK_Update_Previous_Inputs(state->input);
    SDK_TimeFunctions(state->time);

    return SDL_APP_CONTINUE;
}