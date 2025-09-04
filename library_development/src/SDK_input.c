#include "SDK_input.h"


int SDK_CreateInput(SDK_Input *input){
    
    SDL_GetKeyboardState(&input->num_keys);
    input->previous_keyboard = malloc(sizeof(bool) * input->num_keys);
    if(input->previous_keyboard == NULL){
        return 1;
    }
    input->current_keyboard = NULL;
    input->mouse_x = 0;
    input->mouse_y = 0;
    input->current_mouse = 0;
    input->previous_mouse = 0;

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
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (input->current_mouse & SDL_MouseButtonMask) != 0;
}


int SDK_Mouse_JustPressed(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return ((input->current_mouse & SDL_MouseButtonMask) && !(input->previous_mouse & SDL_MouseButtonMask)) != 0;
}


int SDK_Mouse_JustReleased(SDK_Input *input, uint32_t SDL_MouseButtonMask){
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (!(input->current_mouse & SDL_MouseButtonMask) && (input->previous_mouse & SDL_MouseButtonMask)) != 0;
}

void SDK_Mouse_UpdatePosition(SDK_Input *input){
    SDL_GetMouseState(&input->mouse_x, &input->mouse_y);
}




void SDK_Update_Previous_Inputs(SDK_Input *input){
    SDK_Update_Previous_MouseState(input);
    SDK_Update_Previous_KeyboardState(input);
}