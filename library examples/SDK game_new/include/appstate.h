#pragma once

#include "SDK1/SDK.h"


typedef struct{

    SDK_TextDisplay **texts;
    uint8_t amount_text;

} TextDisplay_Manager;


typedef struct{

    SDK_Sprite **sprites;
    uint8_t amount_sprites;

} Static_Sprite_Manager;


typedef struct{

    SDK_Sprite **sprites;
    uint8_t amount_sprites;

} Animated_Sprite_Manager;


typedef struct{

    SDK_Display *display;
    SDK_Time *time;
    SDK_Input *input;
    TextDisplay_Manager text_manager;
    Static_Sprite_Manager s_sprite_manager;
    Animated_Sprite_Manager a_sprite_manager;

} Appstate;