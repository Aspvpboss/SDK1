#pragma once

#include "SDK1.h"

typedef struct{

    SDL_Window *window;
    SDL_WindowFlags window_flag;
    SDL_Renderer *renderer;
    int width, height;

} SDK_Display;


SDK1_API int SDK_CreateDisplay(SDK_Display *display, const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag);
SDK1_API void SDK_DestroyDisplay(SDK_Display *display);
SDK1_API int SDK_DisplaySetWindowed(SDK_Display *display, int width, int height);
SDK1_API int SDK_DisplaySetFullscreen(SDK_Display *display);