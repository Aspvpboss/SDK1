#pragma once

typedef struct{

    void (*quit)(void*);
    void (*handle_events)(void*);
    void (*update)(void*);
    void (*render)(void*);

} Entity_Method;


typedef struct{

    SDL_Texture *atlas;
    SDL_FRect position;
    SDL_FRect atlas_frame;

} Entity_Sprite;