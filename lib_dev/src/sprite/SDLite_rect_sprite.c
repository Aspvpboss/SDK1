#include "SDLite/sprite/SDLite_sprite.h"
#include "SDLite_sprite_internal.h"




SDLite_Sprite* SDLite_Create_RectSprite(SDL_FRect rect, SDL_Color color, bool is_filled){

    SDLite_Sprite *sprite = t_malloc(sizeof(SDLite_Sprite));

    if(!sprite){
        return NULL;
    }

    sprite->sprite_type = SDLite_RECT_SPRITE;

    void **data_t = (void **)&sprite->data;
    
    *data_t = t_malloc(sizeof(SDLite_RectSprite_Data));

    if(!sprite->data){
        t_free(sprite);
        return NULL;
    }

    SDLite_RectSprite_Data *data = (SDLite_RectSprite_Data*)sprite->data;
  
    sprite->render_rect = rect;
    sprite->scale = 1.0f;
    sprite->angle = 0.0f;
    sprite->flip_mode = SDL_FLIP_NONE;
    sprite->pivot_point = (SDL_FPoint){0.0f, 0.0f};

    data->is_filled = is_filled;
    data->color = color;
    data->base_height = rect.h;
    data->base_width = rect.w;

    return sprite;
}




int SDLite_Sprite_SetRectColor(SDLite_Sprite *rect_sprite, SDL_Color color){

    if(!rect_sprite || rect_sprite->sprite_type != SDLite_RECT_SPRITE) return 1;

    SDLite_RectSprite_Data *data = (SDLite_RectSprite_Data *)rect_sprite->data;

    data->color = color;

    return 0;
}