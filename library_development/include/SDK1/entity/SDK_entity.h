#pragma once

#include "../common_libs.h"
#include "../sprite/SDK_sprite.h"
#include "../SDK_input.h"


struct SDK_Entity;

typedef void (*SDK_Func_Update)(struct SDK_Entity *self, SDK_Time *time);
typedef void (*SDK_Func_Event)(struct SDK_Entity *self, SDK_Input *input); 

typedef struct SDK_Entity{

    SDK_Sprite **sprites;
    uint8_t amount_sprites;


    bool visible;
    bool is_updated;
    uint64_t z_index;

    double angle;
    double scale;
    double base_width;
    double base_height;

    SDL_FRect collision_rect;    
    SDL_FRect render_rect;

    SDK_Func_Update on_update;
    SDK_Func_Event on_event;

    void *data;

} SDK_Entity;


/*
    Creates a static SDK_Entity with the specified attributes

    SDK_Entity needs to be freed by SDK_Destroy_Entity()

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Entity* SDK_Create_Entity(
    SDL_FRect collision_rect, SDL_FRect render_rect, void *data, uint64_t z_index, SDK_Func_Update on_update, SDK_Func_Event on_event);


/*
    Frees a SDK_Entity

    Will return early if SDK_Entity is NULL
*/
SDK1_API void SDK_Destroy_Entity(SDK_Entity *entity);


/*
    Adds either a static or animated sprite, with its entity_index
    the entity_index is how many sprites its x and y  gets offset by, this could be used for stiching multiple sprites together


    returns a pointer to the created SDK_Entity, this can be used to modify value within it,
    or adding animations

    returns SDK_Sprite* on success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Sprite* SDK_Entity_AddSprite(
    SDK_Entity *entity, SDK_Display *display, 
    const char *texture_path, SDL_FRect src_rect, SDL_Point entity_index, enum SDK_SpriteType sprite_type);

/*
    Selects an animation for all animated_sprites within the SDK_Entity

    will return 1 if 'uint8_t animation_select' is greater than the amount of animations in the sprite

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_Entity_SelectAnimation(SDK_Entity *entity, uint8_t animation_select);

/*
    This will set the play_animation bool all of the animated SDK_Sprites within the SDK_Entity, 
    the animation will play once set to true

    If you set it false before the animation completes, the animation will automatically reset

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_Entity_SetPlayAnimation(SDK_Entity *entity, bool play_animation);


/*
    This will set the loop_animation bool all of the animated SDK_Sprites within SDK_Entity,
    the animation will loop until you set loop_animation to false

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_Entity_SetLoopAnimation(SDK_Entity *entity, bool loop_animation);

/*
    Updates timing and data for animations in all animated sprites within the SDK_Entity

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_Entity_UpdateAnimation(SDK_Entity *entity, SDK_Time *time);


SDK1_API int SDK_Entity_UpdateSpriteRects(SDK_Entity *entity);

SDK1_API enum SDK_CollisionType SDK_Entity_CheckCollision(SDK_Entity *entity_a, SDK_Entity *entity_b);


