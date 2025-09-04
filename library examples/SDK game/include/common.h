#pragma once

#include "SDK.h"

enum Text_List{

    FPS_TEXT

};

typedef struct{

    SDK_Display display;
    SDK_Time time;
    SDK_Input input;
    SDK_TextDisplay *text_array;
    int amount_text;

} Appstate;