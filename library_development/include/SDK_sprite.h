#pragma once

#include "common_libs.h"
#include "SDK_display.h"

enum SDK_SpriteType{

    SDK_STATIC_SPRITE,
    SDK_ANIMATED_SPRITE

};


struct SDK_StaticSprite_Data{

    SDL_FRect src_rect;

};

struct SDK_AnimatedSprite_Data{

    SDL_FRect src_rect;
    SDL_FRect base_src_rect;
    uint16_t amount_frames;
    uint16_t current_frame;
    double frame_duration;
    double time_elapsed;

};


typedef struct{

    enum SDK_SpriteType sprite_type;

    union{

        struct SDK_StaticSprite_Data *static_s;
        struct SDK_AnimatedSprite_Data *animate_s;

    } data;

    SDL_Texture *texture;
    SDL_FRect dst_rect;
    SDL_FlipMode flip_mode;

    double scale;
    double angle;
    

} SDK_Sprite;


SDK1_API SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);

SDK1_API void SDK_DestroySprite(SDK_Sprite *sprite);

SDK1_API int SDK_RenderSprite(SDK_Display *display, SDK_Sprite *sprite);