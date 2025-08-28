#pragma once
#include "SDK1.h"

typedef struct{

    SDL_Texture *texture;
    SDL_FRect rect;
    SDL_Color color;
    TTF_Font *font;
    char *text;

} SDK_TextDisplay;