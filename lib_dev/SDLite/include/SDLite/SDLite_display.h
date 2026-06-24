/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_DISPLAY_H
#define SDLite_DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "SDLite/common_libs.h"

/*
    These functions should only be called on the main thread
*/
typedef struct SDLite_Display SDLite_Display;

/*
    Creates a SDLite_Display 
    The SDLite_Display width and height get initialized with window_width and window_height

    SDLite_Display needs to be freed by SDLite_DestroyDisplay()

    returns SDLite_Display* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Display* SDLite_CreateDisplay(const char* window_title, int window_width, int window_height, SDL_WindowFlags window_flag);

/*
    Frees a SDLite_Display 

    Will return early if SDLite_Display is NULL
*/
SDLite_DLL void SDLite_DestroyDisplay(SDLite_Display *display);

/*
    Clears all rendered objects (SDLite_Sprite, SDLite_Text) from the SDLite_Display,
    or all that was rendered using the SDL_Renderer* stored within

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_DisplayClear(SDLite_Display *display);


/*
    Present all rendered objects (SDLite_Sprite, SDLite_Text) to the SDLite_Display,
    or all that is rendered using the SDL_Renderer* stored within

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_DisplayPresent(SDLite_Display *display);


/*
    This sets a SDLite_Display to be windowed at a specified width and height

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_DisplaySetWindowed(SDLite_Display *display, int width, int height);


/*
    This sets a SDLite_Display to be fullscreen, the width and height will be
    update to the size of the fullscreen window

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_DisplaySetFullscreen(SDLite_Display *display);


/*
    Fills int* with width and height of window

    Will fail if SDLite_Display*, or if int* is NULL

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Display_GetSize(SDLite_Display *display, int *w, int *h);


/*
    Gets the SDL_Renderer* stored within SDLite_Display. 
    Use it at your own discretion, but do not destroy the SDL_Renderer*

    Will fail if SDLite_Display* is NULL

    returns SDL_Renderer* on success, returns NULL on failure
*/
SDLite_DLL SDL_Renderer* SDLite_Display_GetSDLRenderer(const SDLite_Display *display);


/*
    Gets the SDL_Window* stored within SDLite_Display. 
    Use it at your own discretion, but do not destroy the SDL_Window*

    Will fail if SDLite_Display* is NULL

    returns SDL_Window* on success, returns NULL on failure
*/
SDLite_DLL SDL_Window* SDLite_Display_GetSDLWindow(const SDLite_Display *display);


/*
    Gets the TTF_TextEngine* stored within SDLite_Display. 
    Use it at your own discretion, but do not destroy the TTF_TextEngine*

    Will fail if SDLite_Display* is NULL

    returns TTF_TextEngine* on success, returns NULL on failure
*/
SDLite_DLL TTF_TextEngine* SDLite_Display_GetTTFTextEngine(const SDLite_Display *display);


/*
    Gets the SDL_WindowFlags stored within SDLite_Display. 
    Use it at your own discretion
    
    Will fail if SDLite_Display* is NULL

    returns SDL_WindowFlags on success, returns 0 on failure
*/
SDLite_DLL SDL_WindowFlags SDLite_Display_GetWindowFlags(const SDLite_Display *display);



#ifdef __cplusplus
}
#endif


#endif
