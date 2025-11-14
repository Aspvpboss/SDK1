#include "init_entitys.h"

#define SCALE 8.0f
#define GROUND_TEX "./assets/Overworld_Tileset.png"
#define PLAYER_TEX "./assets/char_spritesheet.png"


SDK_Entity* create_block(SDK_Display *display, float x, float y){

    SDL_FRect rect = {x, y, (16 *SCALE), (16 * SCALE)};
    SDL_FRect src_rect = {16, 32, 16, 16};

    uint64_t z_depth = 1;
    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, z_depth, NULL, NULL);
    if(!entity) return NULL;

    SDK_Sprite *new_sprite = SDK_Entity_AddSprite(entity, display, GROUND_TEX, src_rect, (SDL_Point){0, 0}, SDK_STATIC_SPRITE);
    if(!new_sprite){
        SDK_Destroy_Entity(entity);
        return NULL;
    }
    SDL_SetTextureScaleMode(new_sprite->texture, SDL_SCALEMODE_NEAREST);

    return entity;
}


SDK_Entity* create_ground(SDK_Display *display){

    int sprite_width = (int)(display->width / (16 * SCALE)) + 1;

    SDL_FRect rect = {0, display->height - (16 * SCALE), (16 *SCALE) * sprite_width, display->height - (16 * SCALE)};
    SDL_FRect src_rect = {16, 32, 16, 16};

    uint64_t z_depth = 1;

    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, z_depth, NULL, NULL);
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


    entity->scale = SCALE;
    SDK_Entity_UpdateSpriteRects(entity);

    
    return entity;
}


SDK_Entity* create_player(SDK_Display *display){

    SDL_FRect rect = {0, 200, 13, 15};
    SDL_FRect src_rect_down = {18, 16, 14, 15};
    SDL_FRect src_rect_left = {18, 32, 13, 15};
    SDL_FRect src_rect_right = {18, 48, 13, 15};
    SDL_FRect src_rect_up = {17, 64, 14, 15};


    uint64_t z_depth = 2;
    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, z_depth, update_player, player_events);
    
    if(!entity) return NULL;

    entity->data = t_malloc(sizeof(Player_Data));
    if(!entity->data){
        SDK_Destroy_Entity(entity);
        return NULL;
    }


    Player_Data *data = (Player_Data*)entity->data;
    data->x_friction = 0.5f;
    data->y_friction = 0.2f;
    data->gravity = 3.0f;
    data->x_speed = 19.0f;
    data->y_speed = 6.7f;
    data->x_velocity = 0;
    data->y_velocity = 0;
    data->x_acceleration = 1.0f;
    data->y_acceleration = 1.0f;
    data->is_ground = false;


    SDK_Sprite *sprite = SDK_Entity_AddSprite(entity, display, PLAYER_TEX, src_rect_down, (SDL_Point){0, 0}, SDK_ANIMATED_SPRITE);
    if(!sprite){
        t_free(entity->data);
        SDK_Destroy_Entity(entity);
        return NULL;
    }   

    entity->scale = SCALE;
    SDK_Entity_UpdateSpriteRects(entity);
    SDL_SetTextureScaleMode(sprite->texture, SDL_SCALEMODE_NEAREST);


    uint8_t amount_frames = 6;
    double fps = 9.0f;
    double offset = 3.0f;
    bool loop_animation = true;

    SDK_Sprite_AddAnimation(sprite, src_rect_down, 0, 0, 0, false, false);
    SDK_Sprite_AddAnimation(sprite, src_rect_left, amount_frames, fps, offset - 1, loop_animation, false);
    SDK_Sprite_AddAnimation(sprite, src_rect_right, amount_frames, fps, offset - 1, loop_animation, false);
    SDK_Sprite_AddAnimation(sprite, src_rect_up, amount_frames, fps, offset, loop_animation, false);

    SDK_Entity_SelectAnimation(entity, PLAYER_DOWN_ANI);

    return entity;
}