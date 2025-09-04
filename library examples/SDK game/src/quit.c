#include "common.h"



void SDL_AppQuit(void *appstate, SDL_AppResult result){

    Appstate *state = (Appstate*)appstate;

    for(int i = 0; i < state->amount_text; i++){
        SDK_DestroyText(&state->text_array[i]);
    }

    SDK_DestroyDisplay(&state->display);
    SDK_DestroyInput(&state->input);

    free(state->text_array);
    free(appstate);


    SDK_Quit();

}


