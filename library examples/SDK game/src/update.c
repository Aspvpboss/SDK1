#include "common.h"


int update(Appstate *state){

    SDK_Time *time = &state->time;
    SDK_TextDisplay *text = state->text_array;

    
    if(time->fps_updated){
        char fps_string[32];
        snprintf(fps_string, sizeof(fps_string), "FPS: %.0f", time->fps);
        SDK_Text_UpdateString(&text[FPS_TEXT], fps_string);
    }


    SDK_TimeFunctions(time);
    SDK_Update_Previous_Inputs(&state->input);

    return 0;
}