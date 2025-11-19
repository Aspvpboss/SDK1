#pragma once

#include "../common_libs.h"
#include "../SDK_display.h"
#include "../SDK_time.h"




enum SDK_SpriteType{

    SDK_STATIC_SPRITE,
    SDK_ANIMATED_SPRITE

};



enum SDK_CollisionType{

    SDK_COLLISION_NONE,
    SDK_COLLISION_LEFT,
    SDK_COLLISION_RIGHT,
    SDK_COLLISION_UP,
    SDK_COLLISION_DOWN,

};



/*
    contains data for static / animated sprites
    enum SDK_SpriteType sprite_type determines whether it is animated or static
*/
typedef struct{

    enum SDK_SpriteType sprite_type;

    union{

        void *static_s;
        void *animate_s;

    } data;


    SDL_Texture *texture;
    SDL_FRect render_rect;
    SDL_Point entity_index;

    SDL_FlipMode flip_mode;
    double base_width;
    double base_height;
    double scale;
    double angle;
    SDL_FPoint pivot_point;
    

} SDK_Sprite;




/*
    Creates static SDK_Sprite with the specified attributes

    SDK_Sprite needs to be freed by SDK_DestroySprite()

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);



/*
    Creates animated SDK_Sprite with the specified attributes
    this doesn't add animations to the sprite yet, use SDK_Sprite_AddAnimation() to do so

    SDK_Sprite needs to be freed by SDK_DestroySprite()

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Sprite* SDK_Create_AnimatedSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);


/*
    This function frees a SDK_Sprite (whether animated or static)

    Will return early if SDK_Sprite is NULL
*/
SDK1_API void SDK_DestroySprite(SDK_Sprite *sprite);

SDK1_API int SDK_RenderSprite(SDK_Display *display, SDK_Sprite *sprite);

SDK1_API int SDK_Sprite_AddAnimation(
    SDK_Sprite *animated_sprite, SDL_FRect src_rect, 
    uint8_t amount_frames, double fps, double offset_width, 
    bool loop_animation, bool play_animation);

SDK1_API int SDK_Sprite_UpdateAnimation(SDK_Sprite *animated_sprite, SDK_Time *time);

SDK1_API int SDK_Sprite_SelectAnimation(SDK_Sprite *animated_sprite, uint8_t animation_select);

SDK1_API int SDK_Sprite_SetPlayAnimation(SDK_Sprite *animated_sprite, bool play_animation);

SDK1_API int SDK_Sprite_SetLoopAnimation(SDK_Sprite *animated_sprite, bool loop_animation);

SDK1_API int SDK_Sprite_UpdateScale(SDK_Sprite *sprite, double new_scale);

SDK1_API enum SDK_CollisionType SDK_Sprite_CheckCollision(SDK_Sprite *sprite_a, SDK_Sprite *sprite_b);



