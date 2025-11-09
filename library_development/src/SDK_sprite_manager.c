#include "SDK_sprite_manager.h"



SDK_Sprite_Manager* SDK_Create_SpriteManager(uint64_t max_z_depth, uint64_t max_sprites){

    if(!max_z_depth || !max_sprites)
        return NULL;

    SDK_Sprite_Manager *manager = t_malloc(sizeof(SDK_Sprite_Manager));
    if(!manager)
        return NULL;
    
    manager->layers = t_malloc(sizeof(struct SDK_Render_Layer) * max_z_depth);
    if(!manager->layers){
        t_free(manager);
        return NULL;
    }

    manager->max_z_depth = max_z_depth;
    manager->max_sprites = max_sprites;

    for(int i = 0; i < max_z_depth; i++){
        manager->layers[i].sprites = NULL;
        manager->layers[i].sprites = t_malloc(sizeof(SDK_Sprite*) * max_sprites);

        if(!manager->layers[i].sprites){
            for(int a = 0; a < i; a++)
                t_free(manager->layers[a].sprites);

            t_free(manager->layers);
            t_free(manager);

            return NULL;
        }

        manager->layers[i].amount_sprites = 0;

    }

    return manager;
}




int SDK_SpriteManager_AddEntitySprites(SDK_Sprite_Manager *manager, SDK_Entity *entity){

    const uint64_t MAX_Z_DEPTH = manager->max_z_depth;
    const uint64_t MAX_SPRITES = manager->max_sprites;

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




int SDK_Render_SpriteManager(SDK_Display *display, SDK_Sprite_Manager *manager){

    if(!display || !manager)
        return 1;

    for(int i = 0; i < manager->max_z_depth; i++){

        struct SDK_Render_Layer *layer = &manager->layers[i];
        SDK_Sprite **sprites = layer->sprites;

        for(int a = 0; a < layer->amount_sprites; a++){
            SDK_RenderSprite(display, sprites[a]);
        }

    }

    return 0;
}




void SDK_Destroy_SpriteManager(SDK_Sprite_Manager *manager){

    for(int i = 0; i < manager->max_z_depth; i++){

        t_free(manager->layers[i].sprites);

    }

    t_free(manager->layers);
    t_free(manager);

}