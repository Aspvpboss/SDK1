#include "common.h"


int App_Update(Appstate *state){

    SDK_Time *time = &state->time;
    SDK_TextDisplay *text = state->Text.text_array;
    PlayerClass *Player = &state->Player;

    
    if(time->fps_updated){
        char fps_string[32];
        snprintf(fps_string, sizeof(fps_string), "FPS: %.0f", time->fps);
        SDK_Text_UpdateString(&text[FPS_TEXT], fps_string);
    }



    for(int i = 0; i < Player->amount_players; i++){
        Player->player_func[i].update(state, i);
    }


    SDK_TimeFunctions(time);
    SDK_Update_Previous_Inputs(&state->input);

    return 0;
}