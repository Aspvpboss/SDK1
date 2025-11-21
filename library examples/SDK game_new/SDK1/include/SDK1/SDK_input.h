#pragma once
#include "common_libs.h"

/*
    SDK_Input contains variables need for SDK input functions

    You can access the mouse_x and mouse_y values in your program,
    just don't modify them.
*/
typedef struct{

    bool *previous_keyboard;
    const bool *current_keyboard;
    int num_keys;

    SDL_MouseButtonFlags previous_mouse, current_mouse;
    float mouse_x, mouse_y;

} SDK_Input;



/*
    Creates a SDK_Input
    Access mouse_x && mouse_y for mouse coordiates

    SDK_Input must be freed with SDK_DestroyInput

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info    
*/
SDK1_API SDK_Input* SDK_CreateInput();

/*
    Frees a SDK_Input

    Will return early if SDK_Input is NULL
*/
SDK1_API void SDK_DestroyInput(SDK_Input *input);


/*
    returns 1 if the SDL_Scancode is pressed
*/
SDK1_API int SDK_Keyboard_Pressed(SDK_Input *input, SDL_Scancode scancode);

/*
    returns 1 if the SDL_Scancode was just pressed
*/
SDK1_API int SDK_Keyboard_JustPressed(SDK_Input *input, SDL_Scancode scancode);

/*
    returns 1 if the SDL_Scancode was just released
*/
SDK1_API int SDK_Keyboard_JustReleased(SDK_Input *input, SDL_Scancode scancode);

/*
    Updates previous keyboard state
    This function must be called for just_pressed logic to work
    You can call this after every keyboard input call or at the end of them all
*/
SDK1_API void SDK_Update_Previous_KeyboardState(SDK_Input *input);


/*
    returns 1 if the SDL_BUTTON macro mouse button is pressed
*/
SDK1_API int SDK_Mouse_Pressed(SDK_Input *input, uint32_t SDL_MouseButtonMask);

/*
    returns 1 if the SDL_BUTTON macro mouse button was just pressed
*/
SDK1_API int SDK_Mouse_JustPressed(SDK_Input *input, uint32_t SDL_MouseButtonMask);

/*
    returns 1 if the SDL_BUTTON macro mouse button was just released
*/
SDK1_API int SDK_Mouse_JustReleased(SDK_Input *input, uint32_t SDL_MouseButtonMask);

/*
    updates mouse x and y position to the current mouse position within SDK_Input
*/
SDK1_API void SDK_Mouse_UpdatePosition(SDK_Input *input);

/*
    Updates previous mouse state
    This function must be called for just_pressed logic to work
    You can call this after every keyboard input call or at the end of them all
*/
SDK1_API void SDK_Update_Previous_MouseState(SDK_Input *input);

/*
    calls both SDK_Update_Previous_MouseState
    and SDK_Update_Previous_KeyboardState

    This is for QOL
*/
SDK1_API void SDK_Update_Previous_Inputs(SDK_Input *input);

