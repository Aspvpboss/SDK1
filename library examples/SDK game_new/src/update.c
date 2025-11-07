#include "update.h"


void update_animated_sprites(Animated_Sprite_Manager *manager, SDK_Time *time){

    SDK_Sprite **sprites = manager->sprites;
    if(!sprites)
        return;

    for(int i = 0; i < manager->amount_sprites; i++)
        SDK_Sprite_UpdateAnimation(sprites[i], time);

}

int update(Appstate *state){

    update_animated_sprites(&state->a_sprite_manager, state->time);

    return 0;
}