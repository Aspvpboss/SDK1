#include "SDK1.h"
#include <stdio.h>

int main(){

    SDK_Time time = SDK_CreateTime(144);
    SDL_Event event;
    bool running = 1;

    SDL_Window *window;
    SDL_Renderer *renderer;

    while(running){

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }
        SDK_LimitFPS(&time);
        SDK_CalculateDT(&time);
        SDK_CalculateFPS(&time);
    }






    return 0;
}

