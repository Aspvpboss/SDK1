#include "SDK.h"



int main(){

    SDK_Init();

    SDK_Display *display = SDK_CreateDisplay("SDK window", 400, 400, SDL_WINDOW_MAXIMIZED);
    SDK_Time *time = SDK_CreateTime(500);
    SDK_Input *input = SDK_CreateInput();

    bool running = true;
    SDL_Event e;

    while(running){

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT){
                running = false;
                break;
            }
                
        }

        if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_ESCAPE)){
            running = false;
        }

        SDK_TimeFunctions(time);
        SDK_Update_Previous_Inputs(input);
    }

    SDK_DestroyDisplay(display);

    return 0;
}