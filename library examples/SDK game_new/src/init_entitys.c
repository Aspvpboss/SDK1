#include "init_entitys.h"




SDK_Entity* create_block(SDK_Display *display, float x, float y, uint8_t block_width){

    SDL_FRect rect = {x, y, 16 * block_width, 16};
    SDL_FRect src_rect = {16, 32, 16, 16};

    uint64_t z_depth = 1;
    SDK_Entity *entity = SDK_Create_Entity(rect, rect, NULL, z_depth, NULL, NULL);
    if(!entity) return NULL;

    SDK_Sprite *new_sprite = NULL;

    for(int i = 0; i < block_width; i++){

        new_sprite = SDK_Entity_AddSprite(entity, display, GROUND_TEX, src_rect, (SDL_Point){i, 0}, SDK_STATIC_SPRITE);
        if(!new_sprite){
            SDK_Destroy_Entity(entity);
            return NULL;
        }
        SDL_SetTextureScaleMode(new_sprite->texture, SDL_SCALEMODE_NEAREST);

    }

    entity->scale = ENTITY_SCALE;

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
    data->gravity = 9.8f;
    data->jump_stength = -7.7f;
    data->x_speed = 200.0f;
    data->y_speed = 100.0f;
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

    entity->scale = ENTITY_SCALE;
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

