#include "common.h"

void render_text(SDK_TextDisplay *text, int amount_text){
    for(int i = 0; i < amount_text; i++){
        SDK_Text_Render(&text[i]);
    }
}

int App_Render(Appstate *state){

    SDK_Display *display = &state->display;
    SDK_TextDisplay *text = state->Text.text_array;
    PlayerClass *Player = &state->Player;
    SDL_RenderClear(display->renderer);



    render_text(text, state->Text.amount_text);


    for(int i = 0; i < Player->amount_players; i++){
        Player->player_func[i].render(state, i);
    }


    
    SDL_RenderPresent(display->renderer);
    return 0;
    
}