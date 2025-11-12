#include "update.h"


void update_animated_entitys(Entity_Manager *manager, SDK_Time *time){

    SDK_Entity **sprites = manager->entitys;
    if(!sprites)
        return;

    for(int i = 0; i < manager->amount_entitys; i++)
        SDK_Entity_UpdateAnimation(sprites[i], time);

}



void update_fps_text(TextDisplay_Manager *manager, SDK_Time *time){

    if(!time->fps_updated)
        return;

    SDK_TextDisplay *fps_text = manager->texts[0];
    char fps_string[25];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.2f", time->fps);
    SDK_Text_UpdateString(fps_text, fps_string);

}



void update_player(SDK_Entity *player, SDK_Time *time){

    Player_Data *data = (Player_Data*)player->data;

    data->y_velocity += data->gravity * time->dt;

    player->collision_rect.x += (data->x_velocity * data->speed) * time->dt;
    player->collision_rect.y += (data->y_velocity * data->speed) * time->dt;

}


void update_physics(Entity_Manager *manager, SDK_Time *time){

    SDK_Entity *player = manager->entitys[ENTITY_PLAYER];
    SDK_Entity *ground = manager->entitys[ENTITY_GROUND];


    if(SDK_Entity_CheckCollision(player, ground)){

        player->collision_rect.y = ground->collision_rect.y - player->collision_rect.h;

    }

    player->render_rect = player->collision_rect;
    player->is_updated = true;

}


void update_entity_rects(Entity_Manager *manager){

    if(!manager)
        return;

    SDK_Entity **entitys = manager->entitys;

    for(int i = 0; i < manager->amount_entitys; i++){
        SDK_Entity_UpdateSpriteRects(entitys[i]);
    }

}



void update_entitys(Entity_Manager *manager){


    
}


int update(Appstate *state){

    update_physics(&state->entity_manager, state->time);    

    update_entity_rects(&state->entity_manager);

    update_animated_entitys(&state->entity_manager, state->time);
    update_fps_text(&state->text_manager, state->time);

    return 0;
}

