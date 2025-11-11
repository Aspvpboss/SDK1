#include "quit.h"

void free_entity_manager(Appstate *state){

    Entity_Manager *manager = &state->entity_manager;

    for(int i = 0; i < manager->amount_entitys; i++){
        SDK_Destroy_Entity(manager->entitys[i]);
    }

    if(manager->entitys)
        t_free(manager->entitys);

}


void free_text_manager(Appstate *state){

    if(!state->text_manager.texts || !state->text_manager.amount_text)
        return;

    for(int i = 0; i < state->text_manager.amount_text; i++){
        SDK_DestroyText(state->text_manager.texts[i]);
        state->text_manager.texts[i] = NULL;
    }
    if(state->text_manager.texts)
        t_free(state->text_manager.texts);
    state->text_manager.texts = NULL;

}




void SDL_AppQuit(void *appstate, SDL_AppResult result){

    Appstate *state = (Appstate*)(appstate);

    if(!state)
        return;
    

    free_entity_manager(state);
    free_text_manager(state);
    SDK_DestroyDisplay(state->display);
    SDK_DestroyInput(state->input);
    SDK_DestroyTime(state->time);
    SDK_Destroy_SpriteManager(state->sprite_manager);

    t_free(state);

    SDK_Quit();

}