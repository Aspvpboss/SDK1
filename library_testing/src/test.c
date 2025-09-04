#include "SDK.h"
#include <stdio.h>

void render_text(SDK_TextDisplay *text, const char *string, int x, int y){

    SDK_Text_UpdatePosition(text, x, y);
    SDK_Text_UpdateString(text, string);
    SDK_Text_Render(text);

}


int main(){

    if(SDK_Init()){
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }



    SDK_Time time;
    SDK_CreateTime(&time, 24000);


    SDK_Display display;
    SDK_CreateDisplay(&display, "SDK Window", 800, 800, SDL_WINDOW_MAXIMIZED);


    SDK_Input input;
    SDK_CreateInput(&input);

    SDK_TextDisplay text;
    if(SDK_CreateText(&text, &display, NULL, 50, 5, 5, (SDL_Color){255, 0, 0, 255})){
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }


    SDL_Event event;
    bool running = 1;

    while(running){

        SDL_RenderClear(display.renderer);

        while(SDL_PollEvent(&event)){

            if(event.type == SDL_EVENT_QUIT){
                running = 0;
            }
        }


        if(SDK_Keyboard_Pressed(&input, SDL_SCANCODE_LEFT)){
            time.fps_limit += (int)(-1000 * time.dt);
            if(time.fps_limit < 10){
                time.fps_limit = 10;
            }
        }

        if(SDK_Keyboard_Pressed(&input, SDL_SCANCODE_RIGHT)){
            time.fps_limit += (int)(1000 * time.dt);
            if(time.fps_limit > 100000){
                time.fps_limit = 1000;
            }
        }



        char fps_string[32];
        snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", time.fps);
        render_text(&text, fps_string, 0, 0);


        char fps_limit_text[32];
        snprintf(fps_limit_text, sizeof(fps_limit_text), "FPS Limit: %d", time.fps_limit);

        render_text(&text, fps_limit_text, 0, 50);


        

        SDL_RenderPresent(display.renderer);
        SDK_Update_Previous_Inputs(&input);
        SDK_TimeFunctions(&time);
    }


    SDK_DestroyDisplay(&display);
    SDK_DestroyInput(&input);
    SDK_DestroyText(&text);
    SDK_Quit();

    return 0;
}

