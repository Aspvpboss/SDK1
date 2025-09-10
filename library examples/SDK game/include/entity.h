#pragma once
#include "SDK.h"

enum Facing_Direction{

    FACING_UP,
    FACING_DOWN,
    FACING_LEFT,
    FACING_RIGHT

};

typedef struct{

    float x_velocity, y_velocity;
    float speed, friction;
    float w_scale, h_scale;

} PhysicsBody;


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