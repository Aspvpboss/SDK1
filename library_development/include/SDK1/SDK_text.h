#pragma once
#include "common_libs.h"
#include "SDK_display.h"

/*
    contains variables needed to display a string onto the screen
    you can read the x_pos and y_pos values for use within your program
    
    Do not modify the values directly, use the SDK_Text functions
*/
typedef struct{

    TTF_Font *font;
    SDL_Color color;
    TTF_Text *text;
    TTF_TextEngine *engine;
    SDL_FRect rect;
    int wrap_width;
    float font_size;

} SDK_TextDisplay;

/*
    Initializes a SDK_TextDisplay object, this must be freed using SDK_DestroyText()

    You can pass NULL into 'const char *font_path' and 'const char *display_text'.
    If you do you must update the font using SDK_TextUpdateFont() 
    and update the text using

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API SDK_TextDisplay* SDK_CreateText(SDK_Display *display, const char *font_path, float font_size, int x, int y, SDL_Color color);


/*
    destroys a SDK_TextDisplay object
*/
SDK1_API void SDK_DestroyText(SDK_TextDisplay *text);


/*
    updates the font, and font size of a SDK_TextDisplay object

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdateFont(SDK_TextDisplay *text, const char *font_path, float font_size);


/*
    updates font size of a SDK_TextDisplay object

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdateFontSize(SDK_TextDisplay *text, float font_size);


/*
    updates display text of a SDK_TextDisplay object

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdateString(SDK_TextDisplay *text, const char *string);


/*
    updates display text of a SDK_TextDisplay object

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdatePosition(SDK_TextDisplay *text, int x, int y);


/*
    updates wrap width of a SDK_TextDisplay object
    set wrap_width to 0 for no wrap around

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdateWrapWidth(SDK_TextDisplay *text, int wrap_width);


/*
    updates color of a SDK_TextDisplay object

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_UpdateColor(SDK_TextDisplay *text, SDL_Color color);


/*
    renders the SDK_TextDisplay object to the renderer

    returns 0 for success, 1 for failure
    Use SDL_GetError() for more error details
*/
SDK1_API int SDK_Text_Render(SDK_TextDisplay *text);