#include "SDK_display.h"



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

    display->text_engine = TTF_CreateRendererTextEngine(display->renderer);
    if(!display->text_engine){
        return 1;
    }

    return 0;
}


void SDK_DestroyDisplay(SDK_Display *display){

    SDL_DestroyWindow(display->window);
    display->window = NULL;

    SDL_DestroyRenderer(display->renderer);
    display->renderer = NULL;

    TTF_DestroyRendererTextEngine(display->text_engine);
    display->text_engine = NULL;

}


int SDK_DisplaySetWindowed(SDK_Display *display, int width, int height){

    if(!SDL_SetWindowFullscreen(display->window, 0)){
        return 1;
    }

    if(!SDL_SetWindowSize(display->window, width, height)){
        return 1;
    }

    display->width = width;
    display->height = height;

    return 0;
}


int SDK_DisplaySetFullscreen(SDK_Display *display){

    if(!SDL_SetWindowFullscreen(display->window, 1)){
        return 1;
    }

    if(!SDL_GetWindowSize(display->window, &display->width, &display->height)){
        return 1;
    }

    return 0;
}