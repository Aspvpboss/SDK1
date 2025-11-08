#include "update.h"


void update_animated_sprites(Animated_Sprite_Manager *manager, SDK_Time *time){

    SDK_Sprite **sprites = manager->sprites;
    if(!sprites)
        return;

    for(int i = 0; i < manager->amount_sprites; i++)
        SDK_Sprite_UpdateAnimation(sprites[i], time);

}



void update_fps_text(TextDisplay_Manager *manager, SDK_Time *time){

    if(!time->fps_updated)
        return;

    SDK_TextDisplay *fps_text = manager->texts[0];
    char fps_string[25];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.2f", time->fps);
    SDK_Text_UpdateString(fps_text, fps_string);

}


int update(Appstate *state){

    update_animated_sprites(&state->a_sprite_manager, state->time);
    update_fps_text(&state->text_manager, state->time);

    return 0;
}

