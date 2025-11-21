#include "update.h"


void update_animated_entitys(Entity_Manager *manager, SDK_Time *time){

    SDK_Entity **sprites = manager->entitys;
    if(!sprites)
        return;

    for(int i = 0; i < MAX_ENTITYS; i++){
        if(!sprites[i]) continue;
        SDK_Entity_UpdateAnimation(sprites[i], time);
    }
        

}



void update_fps_text(TextDisplay_Manager *manager, SDK_Time *time){

    if(!time->fps_updated)
        return;

    SDK_Text *fps_text = manager->texts[0];
    char fps_string[25];
    snprintf(fps_string, sizeof(fps_string), "FPS: %.2f", time->fps);
    SDK_Text_UpdateString(fps_text, fps_string);

}



void update_player(SDK_Entity *player, SDK_Time *time){

    #define MAX_X_VELOCITY 100
    #define MAX_Y_VELOCITY 1000


    Player_Data *data = (Player_Data*)player->data;
    double dt = time->dt;
    

    data->x_velocity += data->x_acceleration;

    if(!data->is_ground)
        data->y_velocity += data->gravity * dt;

    if(fabs(data->x_velocity) > MAX_X_VELOCITY)
        data->x_velocity = MAX_X_VELOCITY * (data->x_velocity > 0 ? 1 : -1);

    if(data->y_velocity > MAX_Y_VELOCITY)
        data->y_velocity = MAX_Y_VELOCITY;



    player->collision_rect.x += (data->x_velocity * (data->x_speed * dt));
    player->collision_rect.y += (data->y_velocity * (data->y_speed * dt));

    data->x_velocity *= data->x_friction;
    


    if(fabs(data->x_velocity) < 0.002){
        data->x_velocity = 0.0f;
    }

}



int update_window_bounds(SDK_Entity *player, SDK_Display *display){

    SDL_FRect *rect = &player->collision_rect;

    if(rect->y > display->height - rect->h){
        rect->y = display->height - rect->h;
        return 1;
    }
        

    if(rect->y < 0){
        rect->y = 0;
    }
        

    if(rect->x > display->width - rect->w){
        rect->x = display->width - rect->w;
    }
        

    if(rect->x < 0){
        rect->x = 0;
    }   
        

    return 0;
}




void update_collisions(Entity_Manager *manager, SDK_Time *time, SDK_Display *display){

    SDK_Entity *player = manager->entitys[ENTITY_PLAYER];
    Player_Data *data = (Player_Data*)player->data;    

    data->is_ground = false;    

    if(update_window_bounds(player, display)){

        data->y_velocity = 0.0f;
        data->is_ground = true;

    }


    //updates all colliders with player
    for(int i = 0; i < MAX_COLLIDERS; i++){

        SDK_Entity *collider = manager->entitys[i];

        if(!collider) continue;

        SDL_FRect *collider_rect = &collider->collision_rect;
        SDL_FRect *player_rect = &player->collision_rect;

        enum SDK_CollisionType side = SDK_Entity_CheckCollision(player, collider);

        switch(side){

            case(SDK_COLLISION_LEFT): 
                player_rect->x = collider_rect->x - player_rect->w;
                data->x_velocity = 0.0f;
                break;

            case(SDK_COLLISION_RIGHT): 
                player_rect->x = collider_rect->x + collider_rect->w;
                data->x_velocity = 0.0f;
                break;

            case(SDK_COLLISION_UP):
                player_rect->y = collider_rect->y - player_rect->h;
                data->y_velocity = 0.0f;
                data->is_ground = true;
                break;

            case(SDK_COLLISION_DOWN): 
                player_rect->y = collider_rect->y + collider_rect->h;
                data->y_velocity = 0.0f;
                break;

            default:
                break;
        }

    }


    player->render_rect = player->collision_rect;
    player->is_updated = true;

}


void entity_update_rects(Entity_Manager *manager){

    if(!manager)
        return;

    SDK_Entity **entitys = manager->entitys;

    for(int i = 0; i < MAX_ENTITYS; i++){
        if(!entitys[i]) continue;
        SDK_Entity_UpdateSpriteRects(entitys[i]);
    }

}





void entity_update_funcs(Entity_Manager *manager, SDK_Time *time){

    if(!manager)
        return; 

    SDK_Entity **entitys = manager->entitys;

    for(int i = 0; i < MAX_ENTITYS; i++){

        SDK_Entity *current_entity = entitys[i];

        if(!current_entity || !current_entity->on_update) continue;

        current_entity->on_update(current_entity, time);

    }
    
}




int update(Appstate *state){

    SDK_Display *display = state->display;
    SDK_Time *time = state->time;
    Entity_Manager *entity_manager = &state->entity_manager;
    TextDisplay_Manager *text_manager = &state->text_manager;

    entity_update_funcs(entity_manager, time);    

    update_collisions(entity_manager, time, display);    

    entity_update_rects(entity_manager);

    update_animated_entitys(entity_manager, time);

    update_fps_text(text_manager, time);

    return 0;
}

