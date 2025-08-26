#include "input.h"

/*

Creates SDK_Input
Access mouse_x && mouse_y for mouse coordiates

SDK_Input must be freed with SDK_DestroyInput
*/
int SDK_CreateInput(SDK_Input *input){
    
    SDL_GetKeyboardState(&input->num_keys);
    input->previous_keyboard = malloc(sizeof(bool) * input->num_keys);
    input->current_keyboard = NULL;
    input->mouse_x = 0;
    input->mouse_y = 0;
    input->current_mouse = 0;
    input->previous_mouse = 0;

    return 0;
}

//frees SDK_Input
void SDK_DestroyInput(SDK_Input *input){

    free(input->previous_keyboard);
    input->previous_keyboard = NULL;

}





/*

Updates previous keyboard state
This function must be called for just_pressed logic to work
You can call this after every keyboard input call or at the end of them all

*/
void SDK_Update_Previous_KeyboardState(SDK_Input *input){
    if(input->current_keyboard == NULL)
        return;

    memcpy(input->previous_keyboard, input->current_keyboard, sizeof(bool) * input->num_keys);
}

/*

returns 1 if the SDL_Scancode is pressed

*/
int SDK_Keyboard_Pressed(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return input->current_keyboard[scancode];
}

/*

returns 1 if the SDL_Scancode was just pressed

*/
int SDK_Keyboard_JustPressed(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return input->current_keyboard[scancode] && !input->previous_keyboard[scancode];
}

/*

returns 1 if the SDL_Scancode was just released

*/
int SDK_Keyboard_JustReleased(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return !input->current_keyboard[scancode] && input->previous_keyboard[scancode];
}





/*

Updates previous mouse state
This function must be called for just_pressed logic to work
You can call this after every keyboard input call or at the end of them all

*/
void SDK_Update_Previous_MouseState(SDK_Input *input){
    input->previous_mouse = input->current_mouse;
}

/*

returns 1 if the SDL_Button_Mask mouse button is pressed

*/
int SDK_Mouse_Pressed(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (input->current_mouse & SDL_MouseButtonMask) != 0;
}

/*

returns 1 if the SDL_Button_Mask mouse button was just pressed

*/
int SDK_Mouse_JustPressed(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return ((input->current_mouse & SDL_MouseButtonMask) && !(input->previous_mouse & SDL_MouseButtonMask)) != 0;
}
/*

returns 1 if the SDL_Button_Mask mouse button was just released

*/
int SDK_Mouse_JustReleased(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (!(input->current_mouse & SDL_MouseButtonMask) && (input->previous_mouse & SDL_MouseButtonMask)) != 0;
}
/*

updates mouse x && y position within SDK_Input

*/
void SDK_Mouse_UpdatePosition(SDK_Input *input){
    SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
}



/*

calls both SDK_Update_Previous_MouseState
and SDK_Update_Previous_KeyboardState

This function is for ease of use

*/
void SDK_Update_Previous_Inputs(SDK_Input *input){
    SDK_Update_Previous_MouseState(input);
    SDK_Update_Previous_KeyboardState(input);
}