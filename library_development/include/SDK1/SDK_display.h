#pragma once
#include "common_libs.h"

/*
    SDK_Display contains variables needed for SDK functions
    
    width and height are the dimensions of the display
*/
typedef struct{

    SDL_Window *window;
    SDL_WindowFlags window_flag;
    SDL_Renderer *renderer;
    TTF_TextEngine *text_engine;
    int width, height;

} SDK_Display;


/*
    Creates a SDK_Display 
    The SDK_Display width and height get initialized with window_width and window_height

    SDK_Display needs to be freed by SDK_DestroyDisplay()

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API SDK_Display* SDK_CreateDisplay(const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag);

/*
    Frees a SDK_Display 

    Will return early if SDK_Display is NULL
*/
SDK1_API void SDK_DestroyDisplay(SDK_Display *display);

/*
    This presents what you have rendered onto the display

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
inline int SDK_Display_Present(SDK_Display *display){
    return !SDL_RenderPresent(display->renderer);
}

/*
    This clears what you have rendered onto the display

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
inline int SDK_Display_Clear(SDK_Display *display){
    return !SDL_RenderClear(display->renderer);
}


/*
    This sets a SDK_Display to be windowed at a specified width and height

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_DisplaySetWindowed(SDK_Display *display, int width, int height);


/*
    This sets a SDK_Display to be fullscreen, the width and height will be
    update to the size of the fullscreen window

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDK1_API int SDK_DisplaySetFullscreen(SDK_Display *display);