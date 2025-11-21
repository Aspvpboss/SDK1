#pragma once

#include "SDK1/SDK.h"
#include <math.h>

typedef struct{

    SDK_Text **texts;
    uint8_t amount_text;

} TextDisplay_Manager;


typedef struct{

    SDK_Entity **entitys;
    uint8_t amount_entitys;

} Entity_Manager;



typedef struct{

    SDK_Display *display;
    SDK_Time *time;
    SDK_Input *input;
    SDK_Sprite_Manager *sprite_manager;
    TextDisplay_Manager text_manager;
    Entity_Manager entity_manager;


} Appstate;