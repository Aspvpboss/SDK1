#include "quit.h"


void App_Quit(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    SDK_DestroyDisplay(display);
    SDK_DestroyInput(input);
    SDL_DestroyTexture(player->texture);

    SDK_Quit();
}