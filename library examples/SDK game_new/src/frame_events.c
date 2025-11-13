#include "frame_events.h"


void player_events(SDK_Entity *player, SDK_Input *input){

    Player_Data *data = (Player_Data*)player->data;

    SDK_Entity_SelectAnimation(player, PLAYER_DOWN_ANI);

    data->x_acceleration = 0.0f;

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_LEFT)){
        
        SDK_Entity_SelectAnimation(player, PLAYER_LEFT_ANI);
        data->x_acceleration = -data->x_speed;

    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_RIGHT)){
        
        SDK_Entity_SelectAnimation(player, PLAYER_RIGHT_ANI);
        data->x_acceleration = data->x_speed;

    }



    if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_UP)){
        
        data->y_velocity = -100.0f;

    }


}



void frame_event_entitys(Entity_Manager *manager, SDK_Input *input){

    if(!manager)
        return; 

    SDK_Entity **entitys = manager->entitys;

    for(int i = 0; i < manager->amount_entitys; i++){

        SDK_Entity *current_entity = entitys[i];
    
        if(!current_entity->on_event) continue;

        current_entity->on_event(current_entity, input);

    }
    
}



int frame_events(Appstate *state){

    frame_event_entitys(&state->entity_manager, state->input);

    return 0;
}