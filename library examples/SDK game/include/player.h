#pragma once
#include "entity.h"


typedef struct{

    Entity_Method player_func;
    Entity_Sprite player_sprite;
    int amount_players;
    PhysicsBody physics;
    enum Facing_Direction facing;

} PlayerClass;

int player_init(void *appstate);