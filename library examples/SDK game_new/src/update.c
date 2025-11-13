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

    #define MAX_X_VELOCITY 100
    #define MAX_Y_VELOCITY 100


    Player_Data *data = (Player_Data*)player->data;
    double dt = time->dt;
    
    data->y_acceleration = data->gravity;

    data->x_velocity += data->x_acceleration;
    data->y_velocity += data->y_acceleration;

    if(fabs(data->x_velocity) > MAX_X_VELOCITY)
        data->x_velocity = MAX_X_VELOCITY * (data->x_velocity > 0 ? 1 : -1);

    if(data->y_velocity > MAX_Y_VELOCITY)
        data->y_velocity = MAX_Y_VELOCITY;


    player->collision_rect.x += ((data->x_velocity * data->x_speed) * dt);
    player->collision_rect.y += ((data->y_velocity * data->y_speed) * dt);
    

    data->x_velocity *= data->x_friction;
    if(fabs(data->x_velocity) < 0.002){
        data->x_velocity = 0.0f;
    }

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



void update_entitys(Entity_Manager *manager, SDK_Time *time){

    if(!manager)
        return; 

    SDK_Entity **entitys = manager->entitys;

    for(int i = 0; i < manager->amount_entitys; i++){

        SDK_Entity *current_entity = entitys[i];
    
        if(!current_entity->on_update) continue;

        current_entity->on_update(current_entity, time);

    }
    
}


int update(Appstate *state){

    update_entitys(&state->entity_manager, state->time);    

    update_physics(&state->entity_manager, state->time);    

    update_entity_rects(&state->entity_manager);

    update_animated_entitys(&state->entity_manager, state->time);
    update_fps_text(&state->text_manager, state->time);

    return 0;
}

