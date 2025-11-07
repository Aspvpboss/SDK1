#include "render.h"

int render(Appstate *state){

    SDK_Display *display = state->display;

    SDL_RenderClear(display->renderer);
    SDL_RenderPresent(display->renderer);

    return 0;
}