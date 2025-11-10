#pragma once

#include "common_libs.h"
#include "SDK_sprite.h"
#include "SDK_input.h"


struct SDK_Entity;

typedef void (*SDK_Func_Update)(struct SDK_Entity *self, SDK_Time *time);
typedef void (*SDK_Func_Event)(struct SDK_Entity *self, SDK_Input *input); 

typedef struct SDK_Entity{

    SDK_Sprite **sprites;
    uint8_t amount_sprites;


    bool visible;
    uint64_t z_index;
    SDL_FPoint position;
    SDL_FRect collision_rect;    
    SDL_FRect render_rect;

    SDK_Func_Update on_update;
    SDK_Func_Event on_event;

    void *data;

} SDK_Entity;



SDK1_API SDK_Entity* SDK_Create_Entity(
    SDL_FRect collision_rect, SDL_FRect render_rect, void *data, uint64_t z_index, SDK_Func_Update on_update, SDK_Func_Event on_event);


SDK1_API SDK_Sprite* SDK_Entity_AddSprite(
    SDK_Entity *entity, SDK_Display *display, 
    const char *texture_path, SDL_FRect src_rect, SDL_Point entity_index, enum SDK_SpriteType sprite_type);


SDK1_API int SDK_Entity_CheckCollision(SDK_Entity *entity_a, SDK_Entity *entity_b);


SDK1_API void SDK_Destroy_Entity(SDK_Entity *entity);