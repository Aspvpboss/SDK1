#include "appstate.h"

#define GROUND_TEX "./assets/Overworld_Tileset.png"
#define PLAYER_TEX "./assets/char_spritesheet.png"


SDK_Entity* create_ground(SDK_Display *display){

    double scale = 8.0f;

    int sprite_width = (int)(display->width / (16 * scale)) + 1;

    SDL_FRect rect = {0, display->height - (16 * scale), 16, 16};
    SDL_FRect src_rect = {16, 32, 16, 16};

    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, 0, NULL, NULL);
    if(!entity) return NULL;


    SDK_Sprite *new_sprite = NULL;


    for(int i = 0; i < sprite_width; i++){

        new_sprite = SDK_Entity_AddSprite(entity, display, GROUND_TEX, src_rect, (SDL_Point){i, 0}, SDK_STATIC_SPRITE);
        if(!new_sprite){
            SDK_Destroy_Entity(entity);
            return NULL;
        }
        SDL_SetTextureScaleMode(new_sprite->texture, SDL_SCALEMODE_NEAREST);

    }


    entity->scale = scale;
    SDK_Entity_UpdateSpriteRects(entity);

    
    return entity;
}


SDK_Entity* create_player(SDK_Display *display){

    SDL_FRect rect = {0, 0, 13, 16};
    SDL_FRect src_rect_1 = {18, 16, 13, 16};
    SDL_FRect src_rect_2 = {18, 32, 12, 16};

    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, 1, NULL, NULL);

}