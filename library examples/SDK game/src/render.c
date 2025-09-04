#include "common.h"

void render_text(SDK_TextDisplay *text, int amount_text){
    for(int i = 0; i < amount_text; i++){
        SDK_Text_Render(&text[i]);
    }
}

int render(Appstate *state){

    SDK_Display *display = &state->display;
    SDK_TextDisplay *text = state->text_array;
    SDL_RenderClear(display->renderer);



    render_text(text, state->amount_text);


    
    SDL_RenderPresent(display->renderer);
    return 0;
    
}