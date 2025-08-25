#pragma once

#include "SDK1.h"

typedef struct{

    SDL_Window *window;
    SDL_WindowFlags window_flag;
    SDL_Renderer *renderer;
    int width, height;
    bool failure;

} SDK_Display;


SDK_Display SDK_CreateDisplay(const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag);
void SDK_DestroyDisplay(SDK_Display *display);