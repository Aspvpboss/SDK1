#include "SDK_sprite.h"


SDK_Sprite* SDK_Create_StaticSprite(SDK_Display *display, const char *texture_path, SDL_FRect dst_rect, SDL_FRect src_rect){

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
        t_free(sprite);
        SDL_DestroyTexture(sprite->texture);
        return NULL;
    }

    sprite->data.static_s->src_rect = src_rect;
    sprite->sprite_type = SDK_STATIC_SPRITE;
    sprite->angle = 0.0f;
    sprite->scale = 1.0f;
    sprite->flip_mode = SDL_FLIP_NONE;
    sprite->dst_rect = dst_rect;
    
    return sprite;
}


int SDK_RenderSprite(SDK_Display *display, SDK_Sprite *sprite){

    SDL_FRect src_rect;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){

        src_rect = sprite->data.animate_s->src_rect;

    } else{

        src_rect = sprite->data.static_s->src_rect;

    }

    if(!SDL_RenderTextureRotated(display->renderer, sprite->texture, &src_rect, &sprite->dst_rect, sprite->angle, NULL, sprite->flip_mode))
        return 1;

    return 0;
}



void SDK_DestroySprite(SDK_Sprite *sprite){

    if(!sprite)
        return;

    if(sprite->sprite_type == SDK_ANIMATED_SPRITE){



    } else{

        t_free(sprite->data.static_s);

    }


    SDL_DestroyTexture(sprite->texture);
    t_free(sprite);

}