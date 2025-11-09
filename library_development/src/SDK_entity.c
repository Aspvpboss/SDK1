#include "SDK_entity.h"


int SDK_Push_Entity_SpriteManager(SDK_Sprite_Manager *manager, SDK_Entity *entity){

    if(!manager || !entity)
        return 1;

    if(entity->z_index >= MAX_Z_DEPTH)
        return 1;
    
    struct SDK_Render_Layer *layer = &manager->layers[entity->z_index];

    if(layer->amount_sprites + entity->amount_sprites >= MAX_SPRITES)
        return 1;

    memcpy(layer->sprites + layer->amount_sprites, entity->sprites, sizeof(SDK_Sprite*) * entity->amount_sprites);
    layer->amount_sprites += entity->amount_sprites;

    return 0;
}


