#include "render.h"

int render(SDK_Display *display, SDK_Time *time, SDK_Input *input, Player *player){

    char fps_string[32];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.1f", time->fps);
    SDK_TextDisplay text;
    SDK_CreateText(&text, display, NULL, 20, 0, 0, (SDL_Color){255, 255, 255, 255});
    SDK_Text_UpdateString(&text, fps_string);


    SDL_RenderClear(display->renderer);

    SDL_RenderTexture(display->renderer, player->texture, NULL, &player->rect);
    SDK_Text_Render(&text);
    SDL_RenderPresent(display->renderer);

    SDK_DestroyText(&text);

    return 0;
}