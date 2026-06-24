#ifndef SDLite_DISPLAY_INTERNAL_H
#define SDLite_DISPLAY_INTERNAL_H

#include "SDLite/common_libs.h"

struct SDLite_Display{

    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_TextEngine *text_engine;

};

#endif