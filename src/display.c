#include "display.h"


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