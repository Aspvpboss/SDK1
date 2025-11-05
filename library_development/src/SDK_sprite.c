#include "SDK_sprite.h"


SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect){

    SDK_Sprite *sprite = t_malloc(sizeof(SDK_Sprite));

    if(!sprite)
        return NULL;
    
    sprite->texture = IMG_LoadTexture(display->renderer, texture_path);
    if(!sprite->texture){
        t_free(sprite);
        return NULL;
    }

    sprite->data.static_s = t_malloc(sizeof(struct SDK_StaticSprite_Data));

    if(!sprite->data.static_s){
        SDL_DestroyTexture(sprite->texture);
        t_free(sprite);
        return NULL;
    }

    sprite->data.static_s->src_rect = src_rect;
    sprite->position = sprite_pos;
    sprite->sprite_type = SDK_STATIC_SPRITE;
    sprite->angle = 0.0f;
    sprite->scale = 1.0f;
    sprite->flip_mode = SDL_FLIP_NONE;

    sprite->render_rect.x = sprite_pos.x;
    sprite->render_rect.y = sprite_pos.y;
    sprite->render_rect.w = src_rect.w;
    sprite->render_rect.h = src_rect.h;

    sprite->base_width = src_rect.w;
    sprite->base_height = src_rect.h;

    sprite->collision_rect = (SDL_FRect){sprite_pos.x, sprite_pos.y, src_rect.w, src_rect.h};

    
    return sprite;
}

SDK_Sprite* SDK_Create_AnimatedSprite(
    SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect, uint16_t amount_frames, double fps, float width_offset){

    SDK_Sprite *sprite = t_malloc(sizeof(SDK_Sprite));

    if(!sprite)
        return NULL;
    
    sprite->texture = IMG_LoadTexture(display->renderer, texture_path);
    if(!sprite->texture){
        t_free(sprite);
        return NULL;
    }

    sprite->data.animate_s = t_malloc(sizeof(struct SDK_AnimatedSprite_Data));

    if(!sprite->data.animate_s){
        SDL_DestroyTexture(sprite->texture);
        t_free(sprite);
        return NULL;
    }
    
    struct SDK_AnimatedSprite_Data *data = sprite->data.animate_s;
    data->base_src_rect = src_rect;
    data->src_rect = src_rect;
    data->amount_frames = amount_frames;
    data->frame_duration = 1.0f / fps;
    data->current_frame = 0;
    data->time_elapsed = 0.0f;
    data->width_offset = width_offset;
    data->enable_loop = false;
    data->enable_animation = true;


    sprite->position = sprite_pos;
    sprite->sprite_type = SDK_ANIMATED_SPRITE;
    sprite->angle = 0.0f;
    sprite->scale = 1.0f;
    sprite->flip_mode = SDL_FLIP_NONE;

    sprite->render_rect.x = sprite_pos.x;
    sprite->render_rect.y = sprite_pos.y;
    sprite->render_rect.w = src_rect.w;
    sprite->render_rect.h = src_rect.h;

    sprite->base_width = src_rect.w;
    sprite->base_height = src_rect.h;

    sprite->collision_rect = (SDL_FRect){sprite_pos.x, sprite_pos.y, src_rect.w, src_rect.h};

    
    return sprite;
}




int SDK_Sprite_UpdateAnimation(SDK_Sprite *animated_sprite, SDK_Time *time){

    if(!animated_sprite || !time)
        return 1;

    if(animated_sprite->sprite_type != SDK_ANIMATED_SPRITE)
        return 1;

    
    struct SDK_AnimatedSprite_Data *data = animated_sprite->data.animate_s;

    if(data->enable_loop){
        data->enable_animation = true;
    }

    if(!data->enable_animation)
        return 0;

    SDL_FRect *base_src_rect = &data->base_src_rect;

    data->time_elapsed += time->dt;

    if(data->time_elapsed < data->frame_duration)
        return 0;

    int frames_advanced = (int)(data->time_elapsed / data->frame_duration);
    data->time_elapsed -= frames_advanced * data->frame_duration;
    data->current_frame = (data->current_frame + frames_advanced) % data->amount_frames;

    data->src_rect.x = base_src_rect->x + (data->current_frame * (base_src_rect->w + data->width_offset));

    if(data->current_frame == 0 && !data->enable_loop)
        data->enable_animation = false;    

    return 0;
}



int SDK_RenderSprite(SDK_Display *display, SDK_Sprite *sprite){

    SDL_FRect *src_rect;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){

        src_rect = &sprite->data.animate_s->src_rect;

    } else{

        src_rect = &sprite->data.static_s->src_rect;
        
    }

    if(sprite->angle == 0.0f && sprite->flip_mode == SDL_FLIP_NONE){

        if(!SDL_RenderTexture(display->renderer, sprite->texture, src_rect, &sprite->render_rect))
            return 1;

    } else{

        if(!SDL_RenderTextureRotated(display->renderer, sprite->texture, src_rect, &sprite->render_rect, sprite->angle, NULL, sprite->flip_mode))
            return 1;

    }


    return 0;
}

int SDK_Sprite_UpdateScale(SDK_Sprite *sprite, double new_scale){

    if(!sprite)
        return 1;

    SDL_FRect *render_rect = &sprite->render_rect;
    SDL_FRect *collision_rect = &sprite->collision_rect;
    sprite->scale = new_scale;

    render_rect->w = sprite->base_width * new_scale;
    render_rect->h = sprite->base_height * new_scale;
    collision_rect->w = sprite->base_width * new_scale;
    collision_rect->h = sprite->base_height * new_scale;
    

    return 0;
}





int SDK_Sprite_CheckCollision(SDK_Sprite *sprite_dest, SDK_Sprite *sprite_src){

    if(!sprite_dest || !sprite_src)
        return 0;

    SDL_FRect *a = &sprite_dest->collision_rect;
    SDL_FRect *b = &sprite_src->collision_rect;

    if(a->x + a->w < b->x) return 0;
    if(a->x > b->x + b->w) return 0;
    if(a->y + a->h < b->y) return 0;
    if(a->y > b->y + b->h) return 0;

    return 1;
}


void SDK_Sprite_UpdatePosition(SDK_Sprite *sprite, bool update_collsion, bool update_render){

    if(update_collsion){
        sprite->collision_rect.x = sprite->position.x;
        sprite->collision_rect.y = sprite->position.y;
    }

    if(update_render){
        sprite->render_rect.x = sprite->position.x;
        sprite->render_rect.y = sprite->position.y;        
    }

}



void SDK_DestroySprite(SDK_Sprite *sprite){

    if(!sprite)
        return;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){

        t_free(sprite->data.animate_s);

    } else{

        t_free(sprite->data.static_s);

    }


    SDL_DestroyTexture(sprite->texture);
    t_free(sprite);

}