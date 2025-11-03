#pragma once

#include "common_libs.h"

enum SDK_SpriteType{

    SDK_STATIC_SPRITE,
    SDK_ANIMATED_SPRITE

};


struct SDK_StaticSprite_Data{

    SDL_FRect dst_rect;

};

struct SDK_AnimatedSprite_Data{

    SDL_FRect dst_rect;
    uint16_t amount_frames;
    uint16_t current_frame;
    double frame_duration;
    double time_elapsed;

};


typedef struct{

    enum SDK_SpriteType sprite_type;

    union{

        SDK_StaticSprite_Data *static_s;
        SDK_AnimatedSprite_Data *animate_s;

    } data;

    SDL_Texture *texture;
    SDL_FRect src_rect;
    SDL_FlipMode flip_mode;

    double scale;
    double angle;
    

} SDK_Sprite;

