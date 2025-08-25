#include "SDK1.h"
#include <stdio.h>

int main(){

    SDL_Init(SDL_INIT_VIDEO);

    SDK_Time time = SDK_CreateTime(144);
    SDK_Display display = SDK_CreateDisplay("SDK Window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDL_Event event;
    bool running = 1;



    while(running){

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }

        SDL_RenderClear(display.renderer);
        SDL_RenderPresent(display.renderer);

        SDK_CalculateDT(&time);
        SDK_LimitFPS(&time);
        SDK_CalculateFPS(&time);

        
    }

    

    return 0;
}

