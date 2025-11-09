#pragma once

#include "common_libs.h"
#include "SDK_sprite.h"
#include "SDK_input.h"


typedef struct SDK_Entity{

    SDK_Sprite **sprites;
    uint8_t amount_sprites;


    bool visible;
    uint8_t z_index;
    SDL_FPoint position;
    

    void (*on_update)(struct SDK_Entity *self, SDK_Time *time);
    void (*on_event)(struct SDK_Entity *self, SDK_Input *input);

    void *data;

} SDK_Entity;



