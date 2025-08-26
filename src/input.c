#include "input.h"


int SDK_CreateInput(SDK_Input *input){
    
    SDL_GetKeyboardState(&input->num_keys);
    input->previous_keyboard = malloc(sizeof(bool) * input->num_keys);
    input->current_keyboard = NULL;
    input->mouse_x = 0;
    input->mouse_y = 0;

    return 0;
}



void SDK_DestroyInput(SDK_Input *input){

    free(input->previous_keyboard);
    input->previous_keyboard = NULL;

}



void SDK_Update_Previous_KeyboardState(SDK_Input *input){
    if(input->current_keyboard == NULL)
        return;

    memcpy(input->previous_keyboard, input->current_keyboard, sizeof(bool) * input->num_keys);
}


int SDK_Keyboard_Pressed(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return input->current_keyboard[scancode];
}


int SDK_Keyboard_JustPressed(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return input->current_keyboard[scancode] && !input->previous_keyboard[scancode];
}


int SDK_Keyboard_JustReleased(SDK_Input *input, SDL_Scancode scancode){

    input->current_keyboard = SDL_GetKeyboardState(NULL);

    return !input->current_keyboard[scancode] && input->previous_keyboard[scancode];
}


void SDK_Update_Previous_MouseState(SDK_Input *input){
    input->previous_mouse = input->current_mouse;
}

int SDK_Mouse_Pressed(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(&input->mouse_x, &input->mouse_y);

    return (input->current_mouse & SDL_MouseButtonMask) != 0;
}