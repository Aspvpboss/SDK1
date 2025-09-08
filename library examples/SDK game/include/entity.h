#pragma once
#include "SDK.h"

typedef struct{

    void (*quit)(void*, int);
    void (*handle_events)(void*, int);
    void (*update)(void*, int);
    void (*render)(void*, int);

} Entity_Method;


typedef struct{

    SDL_Texture *atlas;
    SDL_FRect position;
    SDL_FRect atlas_frame;

} Entity_Sprite;