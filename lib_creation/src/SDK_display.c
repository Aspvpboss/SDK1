#include "SDK_display.h"


/*

This functions creates a SDK_Display struct
The SDK_Display width and height get initialized with window_width and window_height

SDK_Display needs to be freed by SDK_DestroyDisplay()

*/
int SDK_CreateDisplay(SDK_Display *display, const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag){

    display->window_flag = window_flag;
    display->width = window_width;
    display->height = window_height;

    display->window = SDL_CreateWindow(window_title, window_width, window_height, window_flag);
    if(!display->window){
        return 1;
    }

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if(!display->renderer){
        return 1;
    }

    return 0;
}



/*

This function frees SDK_Display's contents

*/
void SDK_DestroyDisplay(SDK_Display *display){

    SDL_DestroyWindow(display->window);
    display->window = NULL;

    SDL_DestroyRenderer(display->renderer);
    display->renderer = NULL;

}


/*

This sets a SDK_Display to be windowed at a specified width and height
returns 1 for failure, and returns 0 for success

*/
int SDK_DisplaySetWindowed(SDK_Display *display, int width, int height){

    if(!SDL_SetWindowFullscreen(display->window, 0)){
        return 1;
    }

    if(!SDL_SetWindowSize(display->window, width, height)){
        return 1;
    }

    return 0;
}


/*

This sets a SDK_Display to be fullscreen, the width and height will be
update to the size of the fullscreen window

returns 1 for failure, and returns 0 for success

*/
int SDK_DisplaySetFullscreen(SDK_Display *display){

    if(!SDL_SetWindowFullscreen(display->window, 1)){
        return 1;
    }

    if(!SDL_GetWindowSize(display->window, &display->width, &display->height)){
        return 1;
    }

    return 0;
}