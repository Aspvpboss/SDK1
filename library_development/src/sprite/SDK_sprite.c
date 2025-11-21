#include "sprite/SDK_sprite.h"




typedef struct{

    SDL_FRect src_rect;

} SDK_StaticSprite_Data;


typedef struct{

    SDL_FRect src_rect;
    SDL_FRect base_src_rect;
    uint8_t amount_frames;
    uint8_t current_frame;
    double frame_duration;
    double time_elapsed;
    float width_offset;
    bool play_animation;
    bool loop_animation;

} SDK_Animation;

typedef struct{

    SDK_Animation *animation;
    uint8_t amount_animation;
    uint8_t current_animation;

} SDK_AnimatedSprite_Data;






SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect){

    SDK_Sprite *sprite = t_malloc(sizeof(SDK_Sprite));

    if(!sprite)
        return NULL;
    
    sprite->texture = IMG_LoadTexture(display->renderer, texture_path);
    if(!sprite->texture){
        t_free(sprite);
        return NULL;
    }

    sprite->data.static_s = t_malloc(sizeof(SDK_StaticSprite_Data));

    if(!sprite->data.static_s){
        SDL_DestroyTexture(sprite->texture);
        t_free(sprite);
        return NULL;
    }

    
    SDK_StaticSprite_Data *data = (SDK_StaticSprite_Data*)sprite->data.static_s;
    data->src_rect = src_rect;

    sprite->entity_index = (SDL_Point){0, 0};
    sprite->pivot_point = sprite_pos;
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

    
    return sprite;
}




SDK_Sprite* SDK_Create_AnimatedSprite(SDK_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect){

    SDK_Sprite *sprite = t_malloc(sizeof(SDK_Sprite));

    if(!sprite)
        return NULL;
    
    sprite->texture = IMG_LoadTexture(display->renderer, texture_path);
    if(!sprite->texture){
        t_free(sprite);
        return NULL;
    }

    sprite->data.animate_s = t_malloc(sizeof(SDK_AnimatedSprite_Data));

    if(!sprite->data.animate_s){
        SDL_DestroyTexture(sprite->texture);
        t_free(sprite);
        return NULL;
    }
    
    SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)sprite->data.animate_s;
    data->amount_animation = 0;
    data->current_animation = 0;
    data->animation = NULL;


    sprite->entity_index = (SDL_Point){0, 0};
    sprite->pivot_point = sprite_pos;
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

    
    return sprite;
}




int SDK_Sprite_AddAnimation(
    SDK_Sprite *animated_sprite, SDL_FRect src_rect, 
    uint8_t amount_frames, double fps, double offset_width, 
    bool loop_animation, bool play_animation){

    if(!animated_sprite || animated_sprite->sprite_type != SDK_ANIMATED_SPRITE)
        return 1;

    SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)animated_sprite->data.animate_s;
    data->amount_animation++;
    data->animation = t_realloc(data->animation, sizeof(SDK_Animation) * data->amount_animation);

    SDK_Animation *animation = &data->animation[data->amount_animation - 1];

    animation->width_offset = offset_width;
    animation->base_src_rect = src_rect;
    animation->src_rect = src_rect;

    animation->amount_frames = amount_frames;
    animation->current_frame = 0;

    animation->frame_duration = 1.0f / fps;
    animation->time_elapsed = 0.0f;
    

    animation->loop_animation = loop_animation;
    animation->play_animation = play_animation;

    return 0;
}




int SDK_Sprite_UpdateAnimation(SDK_Sprite *animated_sprite, SDK_Time *time){

    if(!animated_sprite || !time)
        return 1;

    if(animated_sprite->sprite_type != SDK_ANIMATED_SPRITE)
        return 0;

    SDK_AnimatedSprite_Data *m_data = (SDK_AnimatedSprite_Data*)animated_sprite->data.animate_s;

    if(m_data->current_animation >= m_data->amount_animation){
        return 1;
    }
    
    SDK_Animation *data = &m_data->animation[m_data->current_animation];

    if(data->loop_animation){
        data->play_animation = true;
    }

    if(!data->play_animation){

        data->current_frame = 0;
        data->time_elapsed = 0.0f;
        data->src_rect.x = data->base_src_rect.x + (0 * (data->base_src_rect.w + data->width_offset));

        return 0;
    }
        

    SDL_FRect *base_src_rect = &data->base_src_rect;

    data->time_elapsed += time->dt;

    if(data->time_elapsed < data->frame_duration)
        return 0;

    int frames_advanced = (int)(data->time_elapsed / data->frame_duration);
    data->time_elapsed -= frames_advanced * data->frame_duration;
    data->current_frame = (data->current_frame + frames_advanced) % data->amount_frames;

    data->src_rect.x = base_src_rect->x + (data->current_frame * (base_src_rect->w + data->width_offset));

    if(data->current_frame == 0)
        data->play_animation = false;    

    return 0;
}




int SDK_Render_Sprite(SDK_Display *display, SDK_Sprite *sprite){

    SDL_FRect *src_rect;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){

        SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)sprite->data.animate_s;

        if(data->current_animation >= data->amount_animation){
            return 1;
        }
        
        src_rect = &data->animation[data->current_animation].src_rect;

    } else{

        SDK_StaticSprite_Data *data = (SDK_StaticSprite_Data*)sprite->data.animate_s;
        
        src_rect = &data->src_rect;
        
    }

    if(sprite->angle == 0.0f && sprite->flip_mode == SDL_FLIP_NONE){

        if(!SDL_RenderTexture(display->renderer, sprite->texture, src_rect, &sprite->render_rect))
            return 1;

    } else{

        if(!SDL_RenderTextureRotated(display->renderer, sprite->texture, src_rect, &sprite->render_rect, sprite->angle, &sprite->pivot_point, sprite->flip_mode))
            return 1;

    }


    return 0;
}




int SDK_Sprite_UpdateScale(SDK_Sprite *sprite, double new_scale){

    if(!sprite)
        return 1;

    SDL_FRect *render_rect = &sprite->render_rect;
    sprite->scale = new_scale;

    render_rect->w = sprite->base_width * new_scale;
    render_rect->h = sprite->base_height * new_scale;


    return 0;
}




enum SDK_CollisionType SDK_Sprite_CheckCollision(SDK_Sprite *sprite_src, SDK_Sprite *sprite_dest){

    if(!sprite_src || !sprite_dest)
        return SDK_COLLISION_NONE;

    SDL_FRect a = sprite_src->render_rect;
    SDL_FRect b = sprite_dest->render_rect;

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




int SDK_Sprite_SelectAnimation(SDK_Sprite *animated_sprite, uint8_t animation_select){

    if(!animated_sprite || animated_sprite->sprite_type != SDK_ANIMATED_SPRITE || animation_select < 0)
        return 1;

    SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)animated_sprite->data.animate_s;

    if(animation_select >= data->amount_animation)
        return 1;

    data->current_animation = animation_select;

    return 0;
}




int SDK_Sprite_SetPlayAnimation(SDK_Sprite *animated_sprite, bool play_animation){

    if(!animated_sprite || animated_sprite->sprite_type != SDK_ANIMATED_SPRITE)
        return 1;

    SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)animated_sprite->data.animate_s;

    data->animation[data->current_animation].play_animation = play_animation;

    return 0;
}




int SDK_Sprite_SetLoopAnimation(SDK_Sprite *animated_sprite, bool loop_animation){

    if(!animated_sprite || animated_sprite->sprite_type != SDK_ANIMATED_SPRITE)
        return 1;

    SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)animated_sprite->data.animate_s;

    data->animation[data->current_animation].loop_animation = loop_animation;

    return 0;
}




void SDK_DestroySprite(SDK_Sprite *sprite){

    if(!sprite) return;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){

        SDK_AnimatedSprite_Data *data = (SDK_AnimatedSprite_Data*)sprite->data.animate_s;
        t_free(data->animation);
        t_free(sprite->data.animate_s);

    } else{

        t_free(sprite->data.static_s);

    }


    SDL_DestroyTexture(sprite->texture);
    t_free(sprite);

}

