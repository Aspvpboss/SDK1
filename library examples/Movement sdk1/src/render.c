#include "render.h"

static bool init = 0;

int render(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    static char fps_string[32];
    
    static SDK_TextDisplay text;
    if(!init){
        SDK_CreateText(&text, display, NULL, 20, 0, 0, (SDL_Color){255, 255, 255, 255});
        init = 1;
    }


    if(time->fps_updated){
        snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", time->fps);
        SDK_Text_UpdateString(&text, fps_string);
    }

    SDL_RenderClear(display->renderer);

    SDL_RenderTexture(display->renderer, player->texture, NULL, &player->rect);
    SDK_Text_Render(&text);
    SDL_RenderPresent(display->renderer);

    return 0;
}