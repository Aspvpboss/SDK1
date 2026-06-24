#pragma once

#include "SDLite/SDLite.h"
#include <math.h>





typedef struct{

    SDLite_Display *display;
    SDLite_Time *time;
    SDLite_Input *input;
    SDLite_Text *fps_text;

} Appstate;
