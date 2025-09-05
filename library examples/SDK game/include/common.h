#pragma once

#include "SDK.h"
#include "textdisplay.h"
#include "player.h"



typedef struct{

    SDK_Display display;
    SDK_Time time;
    SDK_Input input;
    TextClass Text;
    PlayerClass Player;

} Appstate;



