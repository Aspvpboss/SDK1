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
    entity->base_height = render_rect.h;
    entity->base_width = render_rect.w;
    entity->collision_rect = collision_rect;
    entity->position.x = collision_rect.x;
    entity->position.y = collision_rect.y;

    entity->data = data;


    return entity;
}




SDK_Sprite* SDK_Entity_AddSprite(SDK_Entity *entity, SDK_Display *display, const char *texture_path, SDL_FRect src_rect, SDL_Point entity_index, enum SDK_SpriteType sprite_type){

    SDK_Sprite *sprite = NULL;

    if(sprite_type == SDK_ANIMATED_SPRITE){

        sprite = SDK_Create_AnimatedSprite(display, texture_path, entity->position, src_rect);

    } else{

        sprite = SDK_Create_StaticSprite(display, texture_path, entity->position, src_rect);

    }


    if(!sprite){
        return NULL;
    }

    sprite->entity_index = entity_index;

    SDK_Sprite **new_sprites = t_realloc(entity->sprites, sizeof(SDK_Sprite*) * (entity->amount_sprites + 1));
    if(!new_sprites){
        SDK_DestroySprite(sprite);
        return NULL;
    }

    entity->sprites = new_sprites;
    entity->sprites[entity->amount_sprites] = sprite;
    entity->amount_sprites++;
    

    return sprite;
}




int SDK_Entity_UpdateSpriteRects(SDK_Entity *entity){

    if(!entity)
        return 1;

    SDL_FRect *render_rect = &entity->render_rect;
    double scale = entity->scale;

    
    for(int i = 0; i < entity->amount_sprites; i++){

        SDK_Sprite *sprite = entity->sprites[i];

        sprite->render_rect.w = sprite->base_width * scale;
        sprite->render_rect.h = sprite->base_height * scale;
        sprite->scale = scale;

        double base_x = render_rect->x;
        double base_y = render_rect->y;

        double offset_x = sprite->render_rect.w * sprite->entity_index.x;
        double offset_y = sprite->render_rect.h * sprite->entity_index.y;

        sprite->render_rect.x = base_x + offset_x;
        sprite->render_rect.y = base_y + offset_y;
        

        
    }

    return 0;
}




int SDK_Entity_CheckCollision(SDK_Entity *entity_a, SDK_Entity *entity_b){

    if(!entity_a || !entity_b)
        return 0;

    SDL_FRect *a = &entity_a->collision_rect;
    SDL_FRect *b = &entity_b->collision_rect;

    if(a->x + a->w < b->x) return 0;
    if(a->x > b->x + b->w) return 0;
    if(a->y + a->h < b->y) return 0;
    if(a->y > b->y + b->h) return 0;

    return 1;
}




void SDK_Destroy_Entity(SDK_Entity *entity){

    for(int i = 0; i < entity->amount_sprites; i++){
        SDK_DestroySprite(entity->sprites[i]);
        entity->sprites[i] = NULL;
    }

    if(entity->data)
        t_free(entity->data);

    t_free(entity->sprites);
    t_free(entity);

}

