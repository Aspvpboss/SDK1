#pragma once

#include "SDK.h"



typedef struct{

    SDL_Texture *texture;
    SDL_FRect rect;
    int x_velocity, y_velocity;

} Player;



#include "init.h"
#include "events.h"
#include "iterate.h"
#include "quit.h"
#include "render.h"