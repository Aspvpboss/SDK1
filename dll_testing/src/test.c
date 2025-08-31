#include "SDK.h"
#include <stdio.h>

int main(){

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();



    SDK_Time time;
    SDK_CreateTime(&time, 240);


    SDK_Display display;
    SDK_CreateDisplay(&display, "SDK Window", 800, 800, SDL_WINDOW_MAXIMIZED);


    SDK_Input input;
    SDK_CreateInput(&input);

    SDK_TextDisplay text;
    if(SDK_CreateText(&text, &display, NULL, 50, 5, 5, (SDL_Color){255, 255, 0, 255})){
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    SDL_Event event;
    bool running = 1;

    while(running){

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }


        if(SDK_Keyboard_JustPressed(&input, SDL_SCANCODE_F11)){
        
            Uint32 flags = SDL_GetWindowFlags(display.window);

            if(flags & SDL_WINDOW_FULLSCREEN) {
                SDK_DisplaySetWindowed(&display, 300, 300);
                SDK_Text_UpdateFontSize(&text, 50);
            } else{
                SDK_DisplaySetFullscreen(&display);
                SDK_Text_UpdateFontSize(&text, 10);
            }
        }

        if (time.fps_updated) {
            char fps_string[32];
            snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", time.fps);
            SDK_Text_UpdateString(&text, fps_string);
        }       



        SDL_RenderClear(display.renderer);

        SDK_Text_Render(&text);

        SDL_RenderPresent(display.renderer);

        SDK_Update_Previous_Inputs(&input);
        SDK_TimeFunctions(&time);
    }


    SDK_DestroyDisplay(&display);
    SDK_DestroyInput(&input);
    SDK_DestroyText(&text);
    TTF_Quit();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();

    return 0;
}

