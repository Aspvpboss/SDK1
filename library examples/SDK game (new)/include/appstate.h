#pragma once

#include "SDK1/SDK.h"


typedef struct{

    SDK_TextDisplay **texts;
    uint8_t amount_text;

} TextDisplay_Manager;


typedef struct{

    SDK_Display *display;
    SDK_Time *time;
    SDK_Input *input;

} AppState;