
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include <SDL3/SDL_main.h>

#define MAX_Z_LAYERS 16
#define MAX_SPRITES_LAYER 64

#define GROUND_TEX "./assets/Overworld_Tileset.png"
#define PLAYER_TEX "./assets/char_spritesheet.png"

int init_entitys(Entity_Manager *manager, SDK_Display *display){

    if(!manager || !display)
        return 1;


    
    return 0;
}

int init_textdisplays(TextDisplay_Manager *manager, SDK_Display *display){

    if(!manager || !display)
        return 1;

    manager->amount_text = 1;
    manager->texts = t_malloc(sizeof(SDK_TextDisplay**) * manager->amount_text);
    SDK_TextDisplay **texts = manager->texts;
    
    texts[0] = SDK_CreateText(display, NULL, 20, 0, 0, (SDL_Color){255, 255, 255, 255});
    if(!texts[0]) return 1;

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
    if(!state->input){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->sprite_manager = SDK_Create_SpriteManager(MAX_Z_LAYERS, MAX_SPRITES_LAYER);
    if(!state->sprite_manager){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;        
    }

    if(init_textdisplays(&state->text_manager, state->display)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    if(init_entitys(&state->entity_manager, state->display)){
        SDL_Log("Error: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;       
    }

    
    return SDL_APP_CONTINUE;
}