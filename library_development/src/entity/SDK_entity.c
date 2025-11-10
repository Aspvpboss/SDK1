#include "SDK_entity.h"



SDK_Entity* SDK_Create_Entity(SDL_FRect collision_rect, SDL_FRect render_rect, void *data, uint64_t z_index, SDK_Func_Update on_update, SDK_Func_Event on_event){

    SDK_Entity *entity = t_malloc(sizeof(SDK_Entity));

    if(!entity)
        return NULL;

    entity->sprites = NULL;
    entity->amount_sprites = 0;

    entity->visible = true;
    entity->z_index = z_index;

    entity->on_update = on_update;
    entity->on_event = on_event;

    entity->render_rect = render_rect;
    entity->collision_rect = collision_rect;
    entity->position.x = collision_rect.x;
    entity->position.y = collision_rect.y;

    entity->data = data;


    return entity;
}



int SDK_Entity_AddSprite(){


    return 0;
}


void SDK_Destroy_Entity(SDK_Entity *entity){

    t_free(entity);

}

