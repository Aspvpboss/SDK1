#include "SDK_sprite.h"

SDK_Sprite* SDK_Create_StaticSprite(const char *texture_path){

    SDK_Sprite *sprite = t_malloc(sizeof(SDK_Sprite));

    if(!sprite)
        return NULL;
    
    return sprite;
}


