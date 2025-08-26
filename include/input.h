#pragma once
#include "SDK1.h"


typedef struct{

    bool *previous_keyboard;
    const bool *current_keyboard;
    int num_keys;

    SDL_MouseButtonFlags previous_mouse, current_mouse;
    float mouse_x, mouse_y;

} SDK_Input;


int SDK_CreateInput(SDK_Input *input);
void SDK_DestroyInput(SDK_Input *input);


int SDK_Keyboard_Pressed(SDK_Input *input, SDL_Scancode scancode);
int SDK_Keyboard_JustPressed(SDK_Input *input, SDL_Scancode scancode);
int SDK_Keyboard_JustReleased(SDK_Input *input, SDL_Scancode scancode);
void SDK_Update_Previous_KeyboardState(SDK_Input *input);

int SDK_Mouse_Pressed(SDK_Input *input, uint32_t SDL_MouseButtonMask);
