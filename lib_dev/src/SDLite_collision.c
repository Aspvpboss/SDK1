/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_collision.h"



int SDLite_Collision_RectPoint(const SDL_FRect *rect, const SDL_FPoint *point){
    
    if(!rect || !point) return -1;

    if(rect->x + rect->w <= point->x) return 0;
    if(rect->y + rect->h <= point->y) return 0;
    if(point->x <= rect->x) return 0;
    if(point->y <= rect->y) return 0;

    return 1;
}



int SDLite_Collision_Rect(const SDL_FRect *a, const SDL_FRect *b){

    if(!a || !b) return -1;

    if(a->x + a->w <= b->x) return 0; 
    if(a->x >= b->x + b->w) return 0; 
    if(a->y + a->h <= b->y) return 0; 
    if(a->y >= b->y + b->h) return 0; 

    return 1;
}




enum SDLite_CollisionType SDLite_Collision_RectDir(const SDL_FRect *target, const SDL_FRect *source){

    if(!source || !target)
        return SDLITE_COLLISION_ERROR;

    if(source->x + source->w < target->x) return SDLITE_COLLISION_NONE;
    if(source->x > target->x + target->w) return SDLITE_COLLISION_NONE;
    if(source->y + source->h < target->y) return SDLITE_COLLISION_NONE;
    if(source->y > target->y + target->h) return SDLITE_COLLISION_NONE;

    float left_overlap  = (source->x + source->w) - target->x;
    float right_overlap = (target->x + target->w) - source->x;
    float up_overlap    = (source->y + source->h) - target->y;
    float down_overlap  = (target->y + target->h) - source->y;

    float min_overlap = left_overlap;
    enum SDLite_CollisionType side = SDLITE_COLLISION_LEFT;

    if(right_overlap < min_overlap){
        min_overlap = right_overlap;
        side = SDLITE_COLLISION_RIGHT;
    }
    if(up_overlap < min_overlap){
        min_overlap = up_overlap;
        side = SDLITE_COLLISION_UP;
    }
    if(down_overlap < min_overlap){
        min_overlap = down_overlap;
        side = SDLITE_COLLISION_DOWN;
    }

    return side;
}




