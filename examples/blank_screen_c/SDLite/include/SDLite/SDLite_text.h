/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_TEXT_H
#define SDLite_TEXT_H

#ifdef __cplusplus
extern "C" {
#endif


#include "SDLite/common_libs.h"
#include "SDLite/SDLite_display.h"

/*
    These functions should only be called on the thread that created the SDLite_Text
*/
typedef struct SDLite_Text SDLite_Text;


/*
    Creates a SDLite_Text*, this must be freed using SDLite_DestroyText()

    You can pass NULL into 'const char *font_path' and 'const char *display_text'.
    If the font_path is NULL, it will try to open "SDLite/assets/default.ttf".
    If the display_text is NULL, it will just set the string to be "" 

    returns SDLite_Text* for success, NULL for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL SDLite_Text* SDLite_CreateText(
    const SDLite_Display *display, const char *display_text, const char *font_path, float font_size, int x, int y, SDL_Color color);


/*
    Frees a SDLite_Text*

    Will return early if SDLite_Text is NULL
*/
SDLite_DLL void SDLite_DestroyText(SDLite_Text *text);


/*
    Sets the font and font_size of the SDLite_Text*

    Will fail if SDLite_Text* is NULL or if the font fails to open

    If the SDLite_Text* already has a font it will properly free it before opening the current font

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetFont(SDLite_Text *text, const char *font_path, float font_size);


/*
    Sets font_size of the SDLite_Text*

    Will fail if SDLite_Text* is NULL

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetFontSize(SDLite_Text *text, float font_size);


/*
    Sets text of SDLite_Text*

    Will fail if SDLite_Text* is NULL or if char* is NULL

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetString(SDLite_Text *text, const char *string);


/*
    Sets position of the SDLite_Text*

    Will fail if SDLite_Text* is NULL

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetPosition(SDLite_Text *text, int x, int y);


/*
    Sets wrap width of a SDLite_Text in pixels
    Set wrap_width to 0 for no wrap around
    
    Will fail if SDLite_Text* is NULL

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetWrapWidth(SDLite_Text *text, int wrap_width_pixels);


/*
    Sets color of a SDLite_Text

    Will fail if SDLite_Text* is NULL

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_SetColor(SDLite_Text *text, SDL_Color color);


/*
    Fills values of SDL_FRect of the current x, y, w, and h of the SDLite_Text*

    Will fail if SDLite_Text* is NULL or if SDL_FRect* is NULL

    returns 0 for success, returns 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Text_Get_RenderRect(const SDLite_Text *text, SDL_FRect *render_rect);


/*
    Gets the TTF_Text* stored within SDLite_Text. 
    Use it at your own discretion, but do not destroy the TTF_Text*

    Will fail if SDLite_Text* is NULL

    returns TTF_Text* on success, returns NULL on failure
*/
SDLite_DLL TTF_Text* SDLite_Text_GetTTFText(const SDLite_Text *text);


/*
    Gets the TTF_Font* stored within SDLite_Text. 
    Use it at your own discretion, but do not close the TTF_Font*

    Will fail if SDLite_Text* is NULL

    returns TTF_Font* on success, returns NULL on failure
*/
SDLite_DLL TTF_Font* SDLite_Text_GetTTFFont(const SDLite_Text *text);


/*
    Renders the SDLite_Text to the display it was created with

    Will fail if SDLite_Text* is NULL
    
    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDLite_DLL int SDLite_Render_Text(SDLite_Text *text);

#ifdef __cplusplus
}
#endif


#endif
