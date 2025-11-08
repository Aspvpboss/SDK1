#include "quit.h"

void free_sprites(Appstate *state){

    for(int i = 0; i < state->a_sprite_manager.amount_sprites; i++){
        SDK_DestroySprite(state->a_sprite_manager.sprites[i]);
        state->a_sprite_manager.sprites[i] = NULL;
    }
    if(state->a_sprite_manager.sprites)
        t_free(state->a_sprite_manager.sprites);
    state->a_sprite_manager.sprites = NULL;

    for(int i = 0; i < state->s_sprite_manager.amount_sprites; i++){
        SDK_DestroySprite(state->s_sprite_manager.sprites[i]);
        state->s_sprite_manager.sprites[i] = NULL;
    }
    if(state->s_sprite_manager.sprites)
        t_free(state->s_sprite_manager.sprites);
    state->s_sprite_manager.sprites = NULL;

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
    

    free_sprites(state);
    free_text_manager(state);
    SDK_DestroyDisplay(state->display);
    SDK_DestroyInput(state->input);
    SDK_DestroyTime(state->time);

    t_free(state);

    SDK_Quit();



}