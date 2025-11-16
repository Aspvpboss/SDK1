#pragma once

#include "SDK_sprite.h"
#include "../entity/SDK_entity.h"
#include "../common_libs.h"

struct SDK_Render_Layer{

    SDK_Sprite **sprites;
    uint16_t amount_sprites;

};

typedef struct{

    struct SDK_Render_Layer *layers;
    uint64_t max_z_depth;
    uint64_t max_sprites;

} SDK_Sprite_Manager;



SDK1_API SDK_Sprite_Manager* SDK_Create_SpriteManager(uint64_t max_z_depth, uint64_t max_sprites);
SDK1_API int SDK_SpriteManager_AddEntitySprites(SDK_Sprite_Manager *manager, SDK_Entity *entity);
SDK1_API int SDK_Render_SpriteManager(SDK_Display *display, SDK_Sprite_Manager *manager);
SDK1_API void SDK_Destroy_SpriteManager(SDK_Sprite_Manager *manager);