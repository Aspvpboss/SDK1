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



    Player->player_func.render(state, 0);
    render_text(text, state->Text.amount_text);
    

    SDL_RenderPresent(display->renderer);
    return 0;
    
}