
#define SDL_MAIN_USE_CALLBACKS 1

#include "init.h"
#include "init_entitys.h"
#include <SDL3/SDL_main.h>

#define MAX_Z_LAYERS 16
#define MAX_SPRITES_LAYER 64






int init_entitys(Entity_Manager *manager, SDK_Display *display){

    if(!manager || !display)
        return 1;

    uint8_t amount_entitys = 0;
    SDK_Entity **entitys = manager->entitys;
    SDK_Entity *new_entity = NULL;

    entitys = t_malloc(sizeof(SDK_Entity*) * MAX_ENTITYS);
    if(!entitys) return 1;
    for(int i = 0; i < MAX_ENTITYS; i++) entitys[i] = NULL;


    new_entity = create_block(display, 400, 380, 4);
    if(!new_entity) return 1;
    entitys[amount_entitys] = new_entity;
    amount_entitys++;

    new_entity = create_block(display, 200, 480, 2);
    if(!new_entity) return 1;
    entitys[amount_entitys] = new_entity;
    amount_entitys++;

    new_entity = create_block(display, 0, display->height - (16 * ENTITY_SCALE), (int)(display->width / (16 * ENTITY_SCALE)) + 1);
    if(!new_entity) return 1;
    entitys[amount_entitys] = new_entity;
    amount_entitys++;



    new_entity = create_player(display);
    if(!new_entity) return 1;
    entitys[ENTITY_PLAYER] = new_entity;



    amount_entitys = MAX_ENTITYS;
    manager->entitys = entitys;
    manager->amount_entitys = amount_entitys;


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

    state->time = SDK_CreateTime(13000);
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