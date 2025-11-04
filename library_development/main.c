#include "SDK.h"

void update_text(SDK_TextDisplay *text, double fps){

    static char fps_text[40];

    snprintf(fps_text, sizeof(fps_text), "FPS: %.2f", fps);

    SDK_Text_UpdateString(text, fps_text);

}

int main(){

    SDK_Init();

    SDK_Display *display = SDK_CreateDisplay("SDK window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDK_Time *time = SDK_CreateTime(144);
    SDK_Input *input = SDK_CreateInput();
    SDK_TextDisplay *text = SDK_CreateText(display, NULL, 20, 5, 5, (SDL_Color){255, 255, 255, 255});
    
    t_malloc(2);

    if(!text){
        printf("Kys!\n");
        return 1;
    }

    bool running = true;
    SDL_Event e;

    while(running){

        while(SDL_PollEvent(&e)){

            if(e.type == SDL_EVENT_QUIT){
                running = false;
            }
                
        }

        if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_ESCAPE)){
            running = false;
        }

        if(time->fps_updated){
            update_text(text, time->fps);
        }
            
        SDK_TimeFunctions(time);
        SDK_Update_Previous_Inputs(input);

        SDL_RenderClear(display->renderer);
        SDK_Text_Render(text);
        SDL_RenderPresent(display->renderer);
    }

    SDK_DestroyDisplay(display);
    display = NULL;
    SDK_DestroyInput(input);
    input = NULL;
    SDK_DestroyTime(time);
    time = NULL;
    SDK_DestroyText(text);
    text = NULL;

    SDK_Quit();

    return 0;
}