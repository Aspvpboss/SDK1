/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_input.h"


struct SDLite_Input{

    bool *previous_keyboard;
    const bool *current_keyboard;
    int num_keys;
    SDL_MouseButtonFlags previous_mouse, current_mouse;
    SDL_FPoint mouse_pos;
    
};




SDLite_Input* SDLite_CreateInput(){
    
    SDLite_Input *input = t_malloc(sizeof(SDLite_Input));
    if(!input){
        return NULL;
    }

    input->current_keyboard = SDL_GetKeyboardState(&input->num_keys);
    input->previous_keyboard = t_malloc(sizeof(bool) * input->num_keys);
    if(input->previous_keyboard == NULL){
        t_free(input);
        return NULL;
    }
    input->current_mouse = 0;
    input->previous_mouse = 0;

    input->mouse_pos.x = 0.0f;
    input->mouse_pos.y = 0.0f;

    return input;
}




void SDLite_DestroyInput(SDLite_Input *input){

    if(!input) return;

    t_free(input->previous_keyboard);
    t_free(input);

}




int SDLite_Input_Update_PrevKeyState(SDLite_Input *input){
    
    if(!input) return 1;

    if(input->current_keyboard == NULL)
        return 1;

    SDL_memcpy(input->previous_keyboard, input->current_keyboard, sizeof(bool) * input->num_keys);

    return 0;
}




int SDLite_Input_KeyPressed(SDLite_Input *input, SDL_Scancode scancode){

    if(!input) return -1;

    return input->current_keyboard[scancode];
}




int SDLite_Input_KeyJustPressed(SDLite_Input *input, SDL_Scancode scancode){

    if(!input) return -1;

    return input->current_keyboard[scancode] && !input->previous_keyboard[scancode];
}




int SDLite_Input_KeyJustReleased(SDLite_Input *input, SDL_Scancode scancode){

    if(!input) return -1;

    return !input->current_keyboard[scancode] && input->previous_keyboard[scancode];
}




int SDLite_Input_Update_PrevMouseState(SDLite_Input *input){

    if(!input) return 1;
    
    input->previous_mouse = input->current_mouse;

    return 0;
}




int SDLite_Input_MousePressed(SDLite_Input *input, uint32_t SDL_MouseButtonMask){

    if(!input) return -1;
    
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (input->current_mouse & SDL_MouseButtonMask) != 0;
}




int SDLite_Input_MouseJustPressed(SDLite_Input *input, uint32_t SDL_MouseButtonMask){
    
    if(!input) return -1;

    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return ((input->current_mouse & SDL_MouseButtonMask) && !(input->previous_mouse & SDL_MouseButtonMask)) != 0;
}




int SDLite_Input_MouseJustReleased(SDLite_Input *input, uint32_t SDL_MouseButtonMask){

    if(!input) return -1;
   
    input->current_mouse = SDL_GetMouseState(NULL, NULL);

    return (!(input->current_mouse & SDL_MouseButtonMask) && (input->previous_mouse & SDL_MouseButtonMask)) != 0;
}




int SDLite_Input_Mouse_UpdatePosition(SDLite_Input *input){

    if(!input) return 1;

    SDL_FPoint *mouse_pos = (SDL_FPoint *)&input->mouse_pos;

    SDL_GetMouseState((float *)&mouse_pos->x, (float *)&mouse_pos->y);

    return 0;
}




int SDLite_Input_Mouse_GetPosition(SDLite_Input *input, int *x, int *y){

    if(!input || !x || !y) return 1;

    *x = input->mouse_pos.x;
    *y = input->mouse_pos.y;

    return 0;
}




int SDLite_Input_UpdateAllPrev(SDLite_Input *input){
    
    if(SDLite_Input_Update_PrevMouseState(input)) return 1;
    if(SDLite_Input_Update_PrevKeyState(input)) return 1;
    if(SDLite_Input_Mouse_UpdatePosition(input)) return 1;
 
    return 0;   
}


