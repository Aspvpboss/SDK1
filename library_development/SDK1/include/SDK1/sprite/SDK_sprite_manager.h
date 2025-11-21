#pragma once

#include "SDK_sprite.h"
#include "../entity/SDK_entity.h"
#include "../common_libs.h"



typedef struct{

    void *data;
    uint64_t max_z_depth;
    uint64_t max_sprites;

} SDK_Sprite_Manager;


/*
    Creates a SDK_Sprite_Manager with the specified attributes

    SDK_Sprite_Manager needs to be freed by SDK_Destroy_SpriteManager()

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Sprite_Manager* SDK_Create_SpriteManager(uint64_t max_z_depth, uint64_t max_sprites);

/*
    Frees a SDK_Sprite_Manager

    Will return early if SDK_Sprite_Manager is NULL
*/
SDK1_API void SDK_Destroy_SpriteManager(SDK_Sprite_Manager *manager);


/*
    Adds all the sprites within a SDK_Entity onto the z_layer in the SDK_Sprite_Manager

    if 'bool is_visible' is false, it will not add the SDK_Sprites to the SDK_Sprite_Manager

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_SpriteManager_AddEntitySprites(SDK_Sprite_Manager *manager, SDK_Entity *entity);

/*
    Renders all the sprites within each z_layer contained in SDK_Sprite_Manager

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_Render_SpriteManager(SDK_Display *display, SDK_Sprite_Manager *manager);
