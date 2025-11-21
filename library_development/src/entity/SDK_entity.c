#include "entity/SDK_entity.h"



SDK_Entity* SDK_Create_Entity(SDL_FRect collision_rect, SDL_FRect render_rect, void *data, uint64_t z_index, SDK_Func_Update on_update, SDK_Func_Event on_event){

    SDK_Entity *entity = t_malloc(sizeof(SDK_Entity));

    if(!entity)
        return NULL;

    entity->sprites = NULL;
    entity->amount_sprites = 0;

    entity->is_updated = true;
    entity->visible = true;
    entity->z_index = z_index;

    entity->on_update = on_update;
    entity->on_event = on_event;

    entity->render_rect = render_rect;
    entity->base_height = render_rect.h;
    entity->base_width = render_rect.w;
    entity->collision_rect = collision_rect;

    entity->data = data;


    return entity;
}




SDK_Sprite* SDK_Entity_AddSprite(SDK_Entity *entity, SDK_Display *display, const char *texture_path, SDL_FRect src_rect, SDL_Point entity_index, enum SDK_SpriteType sprite_type){

    SDK_Sprite *sprite = NULL;

    if(sprite_type == SDK_ANIMATED_SPRITE){

        sprite = SDK_Create_AnimatedSprite(display, texture_path, (SDL_FPoint){0, 0}, src_rect);

    } else{

        sprite = SDK_Create_StaticSprite(display, texture_path, (SDL_FPoint){0, 0}, src_rect);

    }
    // (SDL_FPoint){entity->collision_rect.x, entity->collision_rect.y}

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

    if(!entity->is_updated)
        return 0;

    SDL_FRect *render_rect = &entity->render_rect;
    double scale = entity->scale;

    
    for(int i = 0; i < entity->amount_sprites; i++){

        SDK_Sprite *sprite = entity->sprites[i];

        sprite->pivot_point = (SDL_FPoint){entity->collision_rect.x, entity->collision_rect.y};

        sprite->render_rect.w = sprite->base_width * scale;
        sprite->render_rect.h = sprite->base_height * scale;
        sprite->scale = scale;


        entity->collision_rect.w = entity->base_width * scale;
        entity->collision_rect.h = entity->base_height * scale;

        double base_x = render_rect->x;
        double base_y = render_rect->y;

        double offset_x = sprite->render_rect.w * sprite->entity_index.x;
        double offset_y = sprite->render_rect.h * sprite->entity_index.y;

        sprite->render_rect.x = base_x + offset_x;
        sprite->render_rect.y = base_y + offset_y;

        sprite->angle = entity->angle;
        
        
    }

    entity->is_updated = false;

    return 0;
}




int SDK_Entity_UpdateAnimation(SDK_Entity *entity, SDK_Time *time){

    if(!entity)
        return 1;

    SDK_Sprite **sprites = entity->sprites;

    for(int i = 0; i < entity->amount_sprites; i++){
        if(SDK_Sprite_UpdateAnimation(sprites[i], time)) return 1;
    }

    return 0; 
}




int SDK_Entity_SelectAnimation(SDK_Entity *entity, uint8_t animation_select){

    if(!entity)
        return 1;

    SDK_Sprite **sprites = entity->sprites;

    for(int i = 0; i < entity->amount_sprites; i++){
        if(SDK_Sprite_SelectAnimation(sprites[i], animation_select)) return 1;
    }

    return 0; 
}



int SDK_Entity_SetPlayAnimation(SDK_Entity *entity, bool play_animation){

    if(!entity)
        return 1;    

    SDK_Sprite **sprites = entity->sprites;

    for(int i = 0; i < entity->amount_sprites; i++){
        if(SDK_Sprite_SetPlayAnimation(sprites[i], play_animation)) return 1;
    }


    return 0;
}


int SDK_Entity_SetLoopAnimation(SDK_Entity *entity, bool loop_animation){

    if(!entity)
        return 1;    

    SDK_Sprite **sprites = entity->sprites;

    for(int i = 0; i < entity->amount_sprites; i++){
        if(SDK_Sprite_SetLoopAnimation(sprites[i], loop_animation)) return 1;
    }


    return 0;
}




enum SDK_CollisionType SDK_Entity_CheckCollision(SDK_Entity *entity_a, SDK_Entity *entity_b){


    if(!entity_a || !entity_b)
        return SDK_COLLISION_NONE;

    SDL_FRect a = entity_a->collision_rect;
    SDL_FRect b = entity_b->collision_rect;

    if(a.x + a.w < b.x) return SDK_COLLISION_NONE;
    if(a.x > b.x + b.w) return SDK_COLLISION_NONE;
    if(a.y + a.h < b.y) return SDK_COLLISION_NONE;
    if(a.y > b.y + b.h) return SDK_COLLISION_NONE;


    float left_overlap = (a.x + a.w) - b.x;
    float right_overlap = (b.x + b.w) - a.x;
    float up_overlap = (a.y + a.h) - b.y;
    float down_overlap = (b.y + b.h) - a.y;

    float min_overlap = left_overlap;
    enum SDK_CollisionType side = SDK_COLLISION_LEFT;

    if(right_overlap < min_overlap){
        min_overlap = right_overlap;
        side = SDK_COLLISION_RIGHT;
    }
    if(up_overlap < min_overlap){
        min_overlap = up_overlap;
        side = SDK_COLLISION_UP;
    }
    if(down_overlap < min_overlap){
        min_overlap = down_overlap;
        side = SDK_COLLISION_DOWN;
    }


    return side;
}




void SDK_Destroy_Entity(SDK_Entity *entity){

    if(!entity) return;

    for(int i = 0; i < entity->amount_sprites; i++){
        SDK_DestroySprite(entity->sprites[i]);
        entity->sprites[i] = NULL;
    }

    if(entity->data)
        t_free(entity->data);

    t_free(entity->sprites);
    t_free(entity);

}

