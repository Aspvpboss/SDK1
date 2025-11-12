#pragma once

#include "appstate.h"
#include "init_entitys.h"

int update(Appstate *state);

void update_player(SDK_Entity *player, SDK_Time *time);