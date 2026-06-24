/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/sprite/SDLite_sprite.h"
#include "SDLite_sprite_internal.h"
#include "SDLite_display_internal.h"



SDLite_Sprite* SDLite_Create_StaticSprite(const SDLite_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect){

    if(!display) return NULL;


    SDLite_Sprite *sprite = t_malloc(sizeof(SDLite_Sprite));

    if(!sprite)
        return NULL;

    sprite->sprite_type = SDLite_STATIC_SPRITE;

    sprite->data = t_malloc(sizeof(SDLite_StaticSprite_Data));

    if(!sprite->data){
        t_free(sprite);
        return NULL;
    }

    SDLite_StaticSprite_Data *data = (SDLite_StaticSprite_Data*)sprite->data;

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

     
    data->base_width = src_rect.w;
    data->base_height = src_rect.h;
    data->src_rect = src_rect;

    sprite->pivot_point = sprite_pos;
    sprite->angle = 0.0f;
    sprite->scale = 1.0f;
    sprite->flip_mode = SDL_FLIP_NONE;

    sprite->render_rect = (SDL_FRect){sprite_pos.x, sprite_pos.y, src_rect.w, src_rect.h};
    
    return sprite;
}




int SDLite_Sprite_SetTexture(SDLite_Sprite *sprite, SDLite_Texture *texture){

    if(!sprite || !texture) return 1;

    if(sprite->sprite_type == SDLite_STATIC_SPRITE){
        SDLite_StaticSprite_Data *data = (SDLite_StaticSprite_Data*)sprite->data;
        if(data->texture) SDLite_DestroyTexture(&data->texture);
        data->texture = texture;
        texture->refs++;
        return 0; 
    }

    if(sprite->sprite_type == SDLite_ANIMATED_SPRITE){
        SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)sprite->data;
        if(data->texture) SDLite_DestroyTexture(&data->texture);
        data->texture = texture;
        texture->refs++; 
        return 0;
    }

    return 1;
}




SDL_Texture* SDLite_Sprite_GetSDLTexture(const SDLite_Sprite *sprite){

    if(!sprite) return NULL;

    if(sprite->sprite_type == SDLite_STATIC_SPRITE){
        SDLite_StaticSprite_Data *data = (SDLite_StaticSprite_Data*)sprite->data;
        if(!data->texture) return NULL;
        return data->texture->texture;
    }

    if(sprite->sprite_type == SDLite_ANIMATED_SPRITE){
        SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)sprite->data;
        if(!data->texture) return NULL;
        return data->texture->texture;
    }

    return NULL;
}




int SDLite_Render_Sprite(const SDLite_Display *display, const SDLite_Sprite *sprite){

    if(!display || !sprite) return 1;

    const SDL_FRect *src_rect = NULL;
    SDLite_Texture *texture = NULL;
    
    switch(sprite->sprite_type){

        case(SDLite_ANIMATED_SPRITE):

            SDLite_AnimatedSprite_Data *a_data = (SDLite_AnimatedSprite_Data*)sprite->data;

            if(a_data->current_animation >= a_data->amount_animation){
                return 1;
            }

            SDLite_Animation *animation = &a_data->animation[a_data->current_animation];

            src_rect = &animation->frames[animation->current_frame];
            texture = a_data->texture;
            if(!texture) return 1;
            
            break;

        case(SDLite_STATIC_SPRITE):

            SDLite_StaticSprite_Data *s_data = (SDLite_StaticSprite_Data*)sprite->data;

            src_rect = &s_data->src_rect;
            texture = s_data->texture;
            if(!texture) return 1;
            
            break;

        case(SDLite_RECT_SPRITE):

            SDLite_RectSprite_Data *r_data = (SDLite_RectSprite_Data *)sprite->data;

            src_rect = &sprite->render_rect;

            if(!SDL_SetRenderDrawColor(display->renderer, r_data->color.r, r_data->color.g, r_data->color.b, r_data->color.a))
                return 1;
            

            if(r_data->is_filled){
                if(!SDL_RenderFillRect(display->renderer, src_rect)) return 1;
            } else{
                if(!SDL_RenderRect(display->renderer, src_rect)) return 1;
            }

            if(!SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 0)) return 1;

            return 0;

        default: return 1;
    }

    SDL_Texture *sdl_texture = texture->texture;
    if(!sdl_texture) return 1;

    if(sprite->angle == 0.0f && sprite->flip_mode == SDL_FLIP_NONE){

        if(!SDL_RenderTexture(display->renderer, sdl_texture, src_rect, &sprite->render_rect))
            return 1;

    } else{

        if(!SDL_RenderTextureRotated(display->renderer, sdl_texture, src_rect, &sprite->render_rect, sprite->angle, &sprite->pivot_point, sprite->flip_mode))
            return 1;

    }

    return 0;
}

int SDLite_Sprite_GetScale(const SDLite_Sprite *sprite, double *scale){
    
    if(!sprite || !scale) return 1;

    *scale = sprite->scale;

    return 0;
}


int SDLite_Sprite_SetScale(SDLite_Sprite *sprite, double new_scale){

    if(!sprite || new_scale <= 0.0f)
        return 1;


    if(sprite->sprite_type == SDLite_STATIC_SPRITE){

        SDLite_StaticSprite_Data *data = (SDLite_StaticSprite_Data*)sprite->data;

        SDL_FRect *render_rect = &sprite->render_rect;
        sprite->scale = new_scale;

        render_rect->w = data->base_width * new_scale;
        render_rect->h = data->base_height * new_scale;
    
    } else if(sprite->sprite_type == SDLite_ANIMATED_SPRITE){

        SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)sprite->data;

        SDL_FRect *render_rect = &sprite->render_rect;
        sprite->scale = new_scale;

        render_rect->w = data->base_width * new_scale;
        render_rect->h = data->base_height * new_scale;

    } else if(sprite->sprite_type == SDLite_RECT_SPRITE){

        SDLite_RectSprite_Data *data = (SDLite_RectSprite_Data*)sprite->data;

        SDL_FRect *render_rect = &sprite->render_rect;
        sprite->scale = new_scale;

        render_rect->w = data->base_width * new_scale;
        render_rect->h = data->base_height * new_scale;

    }  

    return 0;
}




int SDLite_Sprite_GetAngle(const SDLite_Sprite *sprite, double *angle){

    if(!sprite || !angle) return 1;

    *angle = sprite->angle;

    return 0;
}




int SDLite_Sprite_SetAngle(SDLite_Sprite *sprite, double angle){

    if(!sprite) return 1;

    sprite->angle = angle;

    return 0;
}




int SDLite_Sprite_SetPivotPoint(SDLite_Sprite *sprite, SDL_FPoint pivot_point){

    if(!sprite) return 1;

    sprite->pivot_point = pivot_point;

    return 0;
}




int SDLite_Sprite_GetPivotPoint(const SDLite_Sprite *sprite, SDL_FPoint *pivot_point){

    if(!sprite || !pivot_point) return 1;

    *pivot_point = sprite->pivot_point;

    return 0;
}




int SDLite_Sprite_SetFlipMode(SDLite_Sprite *sprite, SDL_FlipMode flip_mode){

    if(!sprite) return 1;

    sprite->flip_mode = flip_mode;

    return 0;
}




int SDLite_Sprite_GetFlipMode(const SDLite_Sprite *sprite, SDL_FlipMode *flip_mode){

    if(!sprite || !flip_mode) return 1;

    *flip_mode = sprite->flip_mode;

    return 0;
}




int SDLite_Sprite_Set_Position(SDLite_Sprite *sprite, SDL_FPoint position){

    if(!sprite) return 1;

    sprite->render_rect.x = position.x;
    sprite->render_rect.y = position.y;

    return 0;
}




int SDLite_Sprite_Get_RenderRect(const SDLite_Sprite *sprite, SDL_FRect *render_rect){

    if(!sprite || !render_rect) return 1;

    *render_rect = sprite->render_rect;

    return 0;
}




void SDLite_DestroySprite(SDLite_Sprite *sprite){

    if(!sprite) return;

    if(sprite->sprite_type == SDLite_ANIMATED_SPRITE){

        SDLite_AnimatedSprite_Data *data = (SDLite_AnimatedSprite_Data*)sprite->data;
        for(uint16_t i = 0; i < data->amount_animation; i++){
            t_free(data->animation[i].frames);
        }
        t_free(data->animation);
        SDLite_DestroyTexture(&data->texture);
        t_free(sprite->data);

    } else if(sprite->sprite_type == SDLite_STATIC_SPRITE){

        SDLite_StaticSprite_Data *data = (SDLite_StaticSprite_Data*)sprite->data;
        SDLite_DestroyTexture(&data->texture);
        t_free(sprite->data);

    } else if(sprite->sprite_type == SDLite_RECT_SPRITE){

       t_free(sprite->data); 

    }

    t_free(sprite);

}

