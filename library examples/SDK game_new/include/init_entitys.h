#pragma once
#include "appstate.h"
#include "update.h"
#include "frame_events.h"


SDK_Entity* create_player(SDK_Display *display);
SDK_Entity* create_block(SDK_Display *display, float x, float y, uint8_t block_width);

#define MAX_ENTITYS 32
#define MAX_COLLIDERS 16

#define ENTITY_SCALE 5.0f
#define GROUND_TEX "./assets/Overworld_Tileset.png"
#define PLAYER_TEX "./assets/char_spritesheet.png"


typedef struct{

    double x_velocity;
    double y_velocity;
    double x_friction;
    double y_friction;
    double gravity;
    double x_speed;
    double y_speed;
    double x_acceleration; 
    double jump_stength; 
    bool is_ground;

} Player_Data;




enum Entity_Index{

    ENTITY_GROUND,
    ENTITY_PLAYER = MAX_COLLIDERS

};


enum Player_Animations{

    PLAYER_DOWN_ANI,
    PLAYER_LEFT_ANI,
    PLAYER_RIGHT_ANI,
    PLAYER_UP_ANI

};