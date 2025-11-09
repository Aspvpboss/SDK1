#pragma once

#include "common_libs.h"
#include "SDK_display.h"
#include "SDK_time.h"


#define MAX_Z_DEPTH 16
#define MAX_SPRITES 512


enum SDK_SpriteType{

    SDK_STATIC_SPRITE,
    SDK_ANIMATED_SPRITE

};




typedef struct{

    enum SDK_SpriteType sprite_type;

    union{

        void *static_s;
        void *animate_s;

    } data;


    SDL_Texture *texture;

    SDL_FPoint position;
    SDL_FRect collision_rect;
    SDL_FRect render_rect;

    SDL_FlipMode flip_mode;
    double base_width;
    double base_height;
    double scale;
    double angle;
    

} SDK_Sprite;


struct SDK_Sprite_Layer{

    SDK_Sprite *sprite[MAX_SPRITES];
    uint16_t amount_sprites;

};




typedef struct{

    struct SDK_Sprite_Layer layers[MAX_Z_DEPTH];

} SDK_Sprite_Manager;



SDK1_API SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);

SDK1_API SDK_Sprite* SDK_Create_AnimatedSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);

SDK1_API void SDK_DestroySprite(SDK_Sprite *sprite);

SDK1_API int SDK_RenderSprite(SDK_Display *display, SDK_Sprite *sprite);

SDK1_API int SDK_Sprite_AddAnimation(
    SDK_Sprite *animated_sprite, SDL_FRect src_rect, 
    uint8_t amount_frames, double fps, double offset_width, 
    bool loop_animation, bool play_animation);

SDK1_API int SDK_Sprite_UpdateAnimation(SDK_Sprite *animated_sprite, SDK_Time *time);

SDK1_API int SDK_Sprite_SelectAnimation(SDK_Sprite *animated_sprite, uint8_t animation_select);

SDK1_API int SDK_Sprite_SetPlayAnimation(SDK_Sprite *animated_sprite, bool play_animation);

SDK1_API int SDK_Sprite_SetLoop(SDK_Sprite *animated_sprite, bool loop_animation);

SDK1_API int SDK_Sprite_UpdateScale(SDK_Sprite *sprite, double new_scale);

SDK1_API int SDK_Sprite_CheckCollision(SDK_Sprite *sprite_a, SDK_Sprite *sprite_b);

SDK1_API void SDK_Sprite_UpdatePosition(SDK_Sprite *sprite, bool update_collsion, bool update_render);



