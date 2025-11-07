
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include <SDL3/SDL_main.h>

#define GROUND_TEX "./assets/Overworld_Tileset.png"

int init_static_sprites(Static_Sprite_Manager *manager, SDK_Display *display){

    if(!manager)
        return 1;

    manager->amount_sprites = 1;
    manager->sprites = t_malloc(sizeof(SDK_Sprite**) * manager->amount_sprites);
    if(!manager->sprites)
        return 1;
    SDK_Sprite **sprites = manager->sprites;

    sprites[0] = SDK_Create_StaticSprite(display, GROUND_TEX, (SDL_FPoint){0, display->height - 64}, (SDL_FRect){16, 32, 16, 16});
    if(!sprites[0]) return 1;
    SDL_SetTextureScaleMode(sprites[0]->texture, SDL_SCALEMODE_NEAREST);
    sprites[0]->render_rect.w = display->width;
    sprites[0]->render_rect.h = 64;
    
    return 0;
}



SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]){

    SDK_Init();

    (*appstate) = t_malloc(sizeof(Appstate));
    Appstate *state = (Appstate*)(*appstate);

    state->display = SDK_CreateDisplay("SDK game", 1000, 800, SDL_WINDOW_MAXIMIZED);
    if(!state->display){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->time = SDK_CreateTime(144);
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->input = SDK_CreateInput();
    if(!state->time){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->text_manager.amount_text = 0;
    state->text_manager.texts = NULL;
    
    if(init_static_sprites(&state->s_sprite_manager, state->display)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;       
    }

    state->a_sprite_manager.amount_sprites = 0;
    state->a_sprite_manager.sprites = NULL;
    
    return SDL_APP_CONTINUE;
}