#include "render.h"
#include "init_entitys.h"


int render_entitys(SDK_Display *display, Entity_Manager *e_manager, SDK_Sprite_Manager *s_manager){

    if(!e_manager || !s_manager)
        return 1;

    SDK_Entity **entitys = e_manager->entitys;

    for(int i = 0; i < MAX_ENTITYS; i++){
        if(!entitys[i]) continue;
        SDK_SpriteManager_AddEntitySprites(s_manager, entitys[i]);
    }

    SDK_Render_SpriteManager(display, s_manager);

    return 0;
}


int render_text(TextDisplay_Manager *manager){

    for(int i = 0; i < manager->amount_text; i++){
        SDK_Text_Render(manager->texts[i]);
    }

    return 0;
}


int render(Appstate *state){

    SDK_Display *display = state->display;

    SDL_RenderClear(display->renderer);

    render_entitys(display, &state->entity_manager, state->sprite_manager);

    render_text(&state->text_manager);

    SDL_RenderPresent(display->renderer);

    return 0;
}