#include "SDK1.h"
#include <stdio.h>

int main(){

    SDL_Init(SDL_INIT_VIDEO);

    SDK_Time time;
    SDK_CreateTime(&time, 600);


    SDK_Display display;
    SDK_CreateDisplay(&display, "SDK Window", 800, 800, SDL_WINDOW_MAXIMIZED);


    SDK_Input input;
    SDK_CreateInput(&input);


    SDL_Event event;
    bool running = 1;

    while(running){

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }

        if(time.fps_updated)
            printf("\r%f                 ", time.fps);

        if(SDK_Keyboard_JustPressed(&input, SDL_SCANCODE_F11)){
        
            Uint32 flags = SDL_GetWindowFlags(display.window);

            if(flags & SDL_WINDOW_FULLSCREEN) {
                SDK_DisplaySetWindowed(&display, 300, 300);
            } else{
                SDK_DisplaySetFullscreen(&display);
                printf("%d %d\n", display.width, display.height);
            }
        }
            
        
        SDK_Update_Previous_Inputs(&input);
        SDK_TimeFunctions(&time);

        SDL_RenderClear(display.renderer);
        SDL_RenderPresent(display.renderer);
    }

    SDK_DestroyDisplay(&display);
    SDK_DestroyInput(&input);

    return 0;
}

