#include "SDLite/sprite/SDLite_sprite.h"
#include "SDLite_sprite_internal.h"
#include "SDLite_display_internal.h"


SDLite_Sprite* SDLite_Create_AnimatedSprite(const SDLite_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect){

    if(!display) return NULL;

    SDLite_Sprite *sprite = t_malloc(sizeof(SDLite_Sprite));

    if(!sprite)
        return NULL;

    sprite->sprite_type = SDLite_ANIMATED_SPRITE;

    sprite->data = t_malloc(sizeof(SDLite_AnimatedSprite_Data));

    if(!sprite->data){
        t_free(sprite);
        return NULL;
    }

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)sprite->data;

    if(texture_path){
        data->texture = SDLite_CreateTexture(display, texture_path);
        if(!data->texture){
            t_free(data);
            t_free(sprite);
            return NULL;
        }
    } else{
        data->texture = NULL;
    }

    data->amount_animation = 0;
    data->current_animation = 0;
    data->animation = NULL;
    data->base_width = src_rect.w;
    data->base_height = src_rect.h;

    sprite->pivot_point = sprite_pos;
    sprite->angle = 0.0f;
    sprite->scale = 1.0f;
    sprite->flip_mode = SDL_FLIP_NONE;
    sprite->render_rect = (SDL_FRect){sprite_pos.x, sprite_pos.y, src_rect.w, src_rect.h};

    
    return sprite;
}




int SDLite_Sprite_AllocAnimation(SDLite_Sprite *animated_sprite, uint16_t animation_capacity){

    if(!animated_sprite|| animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE || animation_capacity > UINT16_MAX) return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;


    if(data->amount_animation == 0){

        data->animation = t_malloc(sizeof(SDLite_Animation) * animation_capacity);
        if(!data->animation) return 1;

    } else{

        SDLite_Animation *new_animation = t_realloc(data->animation, sizeof(SDLite_Animation) * animation_capacity);
        if(!new_animation) return 1;
        data->animation = new_animation;

    }

    data->amount_animation = animation_capacity;

    return 0;
}




int SDLite_Sprite_AddAnimation(SDLite_Sprite *animated_sprite, SDL_FRect *frames, uint8_t amount_frames, double fps, uint16_t animation_index){

    if(!animated_sprite || animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE)
        return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;

    if(animation_index >= data->amount_animation) return 1;

    SDLite_Animation *animation = &data->animation[animation_index];

    animation->frames = t_malloc(sizeof(SDL_FRect) * amount_frames);
    if(!animation->frames) return 1;
    SDL_memcpy(animation->frames, frames, sizeof(SDL_FRect) * amount_frames); 

    animation->amount_frames = amount_frames;
    animation->current_frame = 0;

    animation->frame_duration = 1.0f / fps;
    animation->time_elapsed = 0.0f;


    animation->loop_animation = false;
    animation->play_animation = false;
    animation->enable_animation = false;

    return 0;
}




int SDLite_Sprite_UpdateAnimation(const SDLite_Sprite *animated_sprite, SDLite_Time *time){

    if(!animated_sprite || !time)
        return 1;

    if(animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE)
        return 0;

    SDLite_AnimatedSprite_Data *m_data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;

    if(m_data->current_animation >= m_data->amount_animation){
        return 1;
    }

    SDLite_Animation *animation = &m_data->animation[m_data->current_animation];


    if((!animation->loop_animation && !animation->play_animation) || !animation->enable_animation){

        animation->current_frame = 0;
        animation->time_elapsed = 0.0f;

        return 0;
    }



    animation->time_elapsed += SDLite_Time_GetDT(time);

    if(animation->time_elapsed < animation->frame_duration)
        return 0;

    int frames_advanced = (int)(animation->time_elapsed / animation->frame_duration);
    animation->time_elapsed -= frames_advanced * animation->frame_duration;
    animation->current_frame = (animation->current_frame + frames_advanced) % animation->amount_frames;


    if(animation->current_frame == 0)
        animation->play_animation = false;    

    return 0;
}




int SDLite_Sprite_SelectAnimation(SDLite_Sprite *animated_sprite, uint16_t animation_index){

    if(!animated_sprite || animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE)
        return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;

    if(animation_index >= data->amount_animation)
        return 1;

    data->current_animation = animation_index;

    return 0;
}




int SDLite_Sprite_SetPlayAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool play){

    if(!animated_sprite || animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE) return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;
    if(animation_index >= data->amount_animation) return 1;

    data->animation[animation_index].play_animation = play;

    return 0;
}




int SDLite_Sprite_SetLoopAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool loop){

    if(!animated_sprite || animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE) return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;
    if(animation_index >= data->amount_animation) return 1;

    data->animation[animation_index].loop_animation = loop;
    
    return 0;
}




int SDLite_Sprite_EnableAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool enabled){
    
    if(!animated_sprite || animated_sprite->sprite_type != SDLite_ANIMATED_SPRITE) return 1;

    SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)animated_sprite->data;
    if(animation_index >= data->amount_animation) return 1;
    
    data->animation[animation_index].enable_animation = enabled;

    return 0;
}