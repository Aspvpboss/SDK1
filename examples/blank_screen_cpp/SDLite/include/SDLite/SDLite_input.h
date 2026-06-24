/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_INPUT_H
#define SDLite_INPUT_H

#ifdef __cplusplus
extern "C"{
#endif


#include "SDLite/common_libs.h"

/*
    These functions should only be called on the main thread
*/
typedef struct SDLite_Input SDLite_Input;


/*
    Creates a SDLite_Input
    Access mouse_x && mouse_y for mouse coordiates

    SDLite_Input must be freed with SDLite_DestroyInput

    returns SDLite_Input* for success, returns NULL for failure
    call SDL_GetError() for more info    
*/
SDLite_DLL SDLite_Input* SDLite_CreateInput();

/*
    Frees a SDLite_Input

    Will return early if SDLite_Input is NULL
*/
SDLite_DLL void SDLite_DestroyInput(SDLite_Input *input);

/*
    returns 1 if the specified keyboard key i pressed

    Function only fails if SDLite_Input* is NULL

    returns 0 for no keyboard key pressed, returns 1 for keyboard key pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_KeyPressed(SDLite_Input *input, SDL_Scancode scancode);

/*
    returns 1 if the specified keyboard key was just pressed

    Function only fails if SDLite_Input* is NULL

    returns 0 for no keyboard key pressed, returns 1 for keyboard key pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_KeyJustPressed(SDLite_Input *input, SDL_Scancode scancode);

/*
    returns 1 if the specified keyboard key was just released

    Function only fails if SDLite_Input* is NULL

    returns 0 for no keyboard key pressed, returns 1 for keyboard key pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_KeyJustReleased(SDLite_Input *input, SDL_Scancode scancode);

/*
    Updates previous keyboard state
    This function must be called for just_pressed key logic to work
    You can call this after every keyboard input call or at the end of them all

    Function only fails if SDLite_Input* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Input_Update_PrevKeyState(SDLite_Input *input);

/*
    returns 1 if the specified mouse button is pressed

    Function only fails if SDLite_Input* is NULL

    returns 0 for no mouse button pressed, returns 1 for mouse button pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_MousePressed(SDLite_Input *input, uint32_t SDL_MouseButtonMask);

/*
    returns 1 if the specified mouse button was just pressed

    Function only fails if SDLite_Input* is NULL

    returns 0 for no mouse button pressed, returns 1 for mouse button pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_MouseJustPressed(SDLite_Input *input, uint32_t SDL_MouseButtonMask);

/*
    returns 1 if the specified mouse button was just released

    Function only fails if SDLite_Input* is NULL

    returns 0 for no mouse button pressed, returns 1 for mouse button pressed, returns -1 for failure
*/
SDLite_DLL int SDLite_Input_MouseJustPressed(SDLite_Input *input, uint32_t SDL_MouseButtonMask);

/*
    Updates mouse x and y position to the current mouse position within SDLite_Input

    Function only fails if SDLite_Input* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Input_Mouse_UpdatePosition(SDLite_Input *input);

/*
    Fills in values of the mouse x and y position into the int*

    Functions only fails if SDLite_Input* other if either of the int* are NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Input_Mouse_GetPosition(SDLite_Input *input, int *x, int *y);

/*
    Updates previous mouse state
    This function must be called for just_pressed logic to work
    You can call this after every keyboard input call or at the end of them all

    Function only fails if SDLite_Input* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Input_Update_PrevMouseState(SDLite_Input *input);

/*
    calls both SDLite_Update_Previous_MouseState
    and SDLite_Update_Previous_KeyboardState

    This is for QOL

    Function only fails if SDLite_Input* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Input_UpdateAllPrev(SDLite_Input *input);


#ifdef __cplusplus
}
#endif



#endif

