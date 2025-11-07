#include "render.h"


int render_sprites(SDK_Display *display, Static_Sprite_Manager *s_manager, Animated_Sprite_Manager *a_manager){

    for(int i = 0; i < s_manager->amount_sprites; i++){
        if(SDK_RenderSprite(display, s_manager->sprites[i])) return 1;
    }

    for(int i = 0; i < a_manager->amount_sprites; i++){
        if(SDK_RenderSprite(display, a_manager->sprites[i])) return 1;
    }

    return 0;
}


int render(Appstate *state){

    SDK_Display *display = state->display;

    SDL_RenderClear(display->renderer);

    render_sprites(display, &state->s_sprite_manager, &state->a_sprite_manager);

    SDL_RenderPresent(display->renderer);

    return 0;
}