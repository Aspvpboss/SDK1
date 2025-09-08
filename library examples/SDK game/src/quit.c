#include "common.h"



void SDL_AppQuit(void *appstate, SDL_AppResult result){

    Appstate *state = (Appstate*)appstate;
    PlayerClass *Player = &state->Player;
    TextClass *Text = &state->Text;


    for(int i = 0; i < Player->amount_players; i++){
        Player->player_func[i].quit(state, i);
    }
    free(Player->player_func);
    free(Player->player_sprite);


    for(int i = 0; i < Text->amount_text; i++){
        SDK_DestroyText(&Text->text_array[i]);
    }
    free(state->Text.text_array);


    SDK_DestroyDisplay(&state->display);
    SDK_DestroyInput(&state->input);

    free(appstate);
    SDK_Quit();

}


