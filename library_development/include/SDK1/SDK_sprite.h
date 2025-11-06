#pragma once

#include "common_libs.h"
#include "SDK_display.h"
#include "SDK_time.h"


#define SDK_ANIMATE_SPRITE(sprite) sprite->data.animate_s->enable_animation = true;
#define SDK_SET_LOOP_SPRITE(sprite, boolean) sprite->data.animate_s->enable_loop = boolean;

enum SDK_SpriteType{

    SDK_STATIC_SPRITE,
    SDK_ANIMATED_SPRITE

};


struct SDK_StaticSprite_Data{

    SDL_FRect src_rect;

};


struct SDK_Animation{

    SDL_FRect src_rect;
    SDL_FRect base_src_rect;
    uint8_t amount_frames;
    uint8_t current_frame;
    double frame_duration;
    double time_elapsed;
    float width_offset;
    bool play_animation;
    bool loop_animation;

};

struct SDK_AnimatedSprite_Data{

    struct SDK_Animation *animation;
    uint8_t amount_animation;
    uint8_t current_animation;

};


typedef struct{

    enum SDK_SpriteType sprite_type;

    union{

        struct SDK_StaticSprite_Data *static_s;
        struct SDK_AnimatedSprite_Data *animate_s;

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



