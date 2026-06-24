/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_display.h"
#include "SDLite_display_internal.h"


SDLite_Display* SDLite_CreateDisplay(const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag){

    if(!window_title) return NULL;

    SDLite_Display *display = t_malloc(sizeof(SDLite_Display));

    display->window = SDL_CreateWindow(window_title, window_width, window_height, window_flag);
    if(!display->window){
        t_free(display);
        return NULL;
    }

    display->renderer = SDL_CreateRenderer(display->window, NULL);
    if(!display->renderer){
        SDL_DestroyWindow(display->window);
        t_free(display);
        return NULL;
    }

    display->text_engine = TTF_CreateRendererTextEngine(display->renderer);
    if(!display->text_engine){
        SDL_DestroyWindow(display->window);
        SDL_DestroyRenderer(display->renderer);
        t_free(display);
        return NULL;
    }

    return display;
}


int SDLite_DisplayClear(SDLite_Display *display){

    if(!display) return 1;

    if(!SDL_RenderClear(display->renderer)){
        return 1;
    }

    return 0;
}


int SDLite_DisplayPresent(SDLite_Display *display){

    if(!display) return 1;

    if(!SDL_RenderPresent(display->renderer)){
        return 1;
    }

    return 0;
}


void SDLite_DestroyDisplay(SDLite_Display *display){

    if(!display) return;

    SDL_DestroyWindow(display->window);
    display->window = NULL;

    SDL_DestroyRenderer(display->renderer);
    display->renderer = NULL;

    TTF_DestroyRendererTextEngine(display->text_engine);
    display->text_engine = NULL;

    t_free(display);

}


int SDLite_DisplaySetWindowed(SDLite_Display *display, int width, int height){

    if(!SDL_SetWindowFullscreen(display->window, 0)){
        return 1;
    }

    if(!SDL_SetWindowSize(display->window, width, height)){
        return 1;
    }

    return 0;
}


int SDLite_DisplaySetFullscreen(SDLite_Display *display){

    if(!SDL_SetWindowFullscreen(display->window, 1)){
        return 1;
    }

    return 0;
}


int SDLite_Display_GetSize(SDLite_Display *display, int *w, int *h){

    if(!display || !w || !h) return 1;

    if(!SDL_GetWindowSize(display->window, w, h)) return 1;

    return 0;
}


SDL_Renderer* SDLite_Display_GetSDLRenderer(const SDLite_Display *display){

    if(!display) return NULL;

    return display->renderer;
}


SDL_Window* SDLite_Display_GetSDLWindow(const SDLite_Display *display){

    if(!display) return NULL;

    return display->window;
}


TTF_TextEngine* SDLite_Display_GetTTFTextEngine(const SDLite_Display *display){

    if(!display) return NULL;

    return display->text_engine;
}


SDL_WindowFlags SDLite_Display_GetWindowFlags(const SDLite_Display *display){

    if(!display) return 0;

    return SDL_GetWindowFlags(display->window);
}

