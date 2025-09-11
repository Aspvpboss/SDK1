#include "player.h"
#include "common.h"

const char TEXTURE_PATH[] = "./assets/Char_Sprites/char_spritesheet.png";


void normalize_velocitys(PhysicsBody *physics){
    float magnitude = SDL_sqrt(physics->x_velocity * physics->x_velocity + physics->y_velocity * physics->y_velocity);

    if (magnitude == 0.0f) {
        physics->x_velocity = 0.0f;
        physics->y_velocity = 0.0f;
    } else {
        physics->x_velocity /= magnitude;
        physics->y_velocity /= magnitude;
    }    
}


void clamp_float(float *value, float *velocity, float min, float max){

    if(*value < min){
        *value = min;
        *velocity *= -1;
    }

    if(*value > max){
        *value = max;
        *velocity *= -1;
    }

}


void apply_friction(float *velocity, float friction, double dt){
    float friction_factor = (1.0f - friction * dt);
    if(friction_factor < 0.0f)
        friction_factor = 0.0f;

    *velocity *= friction_factor;

    if (SDL_fabsf(*velocity) < 0.01f) {
        *velocity = 0.0f;
    }
}


void update_direction(PlayerClass *Player){

    if(Player->physics.x_velocity < 0){
        Player->facing = FACING_LEFT;
        Player->player_sprite.atlas_frame.x = 18;
        Player->player_sprite.atlas_frame.y = 32;
    }
    
    if(Player->physics.x_velocity > 0){
        Player->facing = FACING_LEFT;
        Player->player_sprite.atlas_frame.x = 18;
        Player->player_sprite.atlas_frame.y = 48;
    }

    if(Player->physics.y_velocity < 0){
        Player->facing = FACING_DOWN;
        Player->player_sprite.atlas_frame.x = 18;
        Player->player_sprite.atlas_frame.y = 64;
    }

    if(Player->physics.y_velocity > 0){
        Player->facing = FACING_UP;
        Player->player_sprite.atlas_frame.x = 18;
        Player->player_sprite.atlas_frame.y = 16;
    }

}


void Player_Update(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;

    SDK_Display *display = &state->display;
    PlayerClass *Player = &state->Player;
    SDK_Time *time = &state->time;
    SDL_FRect *position = &Player->player_sprite.position;
    SDL_FRect *atlas_frame = &Player->player_sprite.atlas_frame;
    PhysicsBody *physics = &Player->physics;

    
    apply_friction(&physics->x_velocity, physics->friction, time->dt);
    position->x += (physics->x_velocity * physics->speed * time->dt);
    clamp_float(&position->x, &physics->x_velocity, 0, display->width - (atlas_frame->w * physics->w_scale));


    apply_friction(&physics->y_velocity, physics->friction, time->dt);
    position->y += (physics->y_velocity * physics->speed * time->dt);
    clamp_float(&position->y, &physics->y_velocity, 0, display->height - (atlas_frame->h * physics->h_scale));


    update_direction(Player);
}


void Player_Events(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;    
    PlayerClass *Player = &state->Player;
    SDK_Input *input = &state->input;

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_W)){
        Player->physics.y_velocity = -1;
        normalize_velocitys(&Player->physics);
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_S)){
        Player->physics.y_velocity = 1;
        normalize_velocitys(&Player->physics);
    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_A)){
        Player->physics.x_velocity = -1;
        normalize_velocitys(&Player->physics);

    }

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_D)){
        Player->physics.x_velocity = 1;
        normalize_velocitys(&Player->physics);

    }

    

}


void Player_Render(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;
    PlayerClass *Player = &state->Player;

    SDL_SetTextureScaleMode(Player->player_sprite.atlas, SDL_SCALEMODE_NEAREST);

    SDL_RenderTexture(state->display.renderer, Player->player_sprite.atlas, &Player->player_sprite.atlas_frame, &Player->player_sprite.position);

}


void Player_Quit(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;
    PlayerClass *Player = &state->Player;

    SDL_DestroyTexture(Player->player_sprite.atlas);
}




int player_init(void *appstate){

    Appstate *state = (Appstate*) appstate;

    PlayerClass *Player = &state->Player;
    SDK_Display *display = &state->display;
    Player->amount_players = 1;
    Player->physics.x_velocity = 0.0f;
    Player->physics.y_velocity = 0.0f;
    Player->physics.speed = 300.0f;
    Player->physics.friction = 1.0f;
    
    Player->player_sprite.atlas = IMG_LoadTexture(display->renderer, TEXTURE_PATH);
    if(Player->player_sprite.atlas == NULL)
        return 1;
    
    Player->player_sprite.atlas_frame = (SDL_FRect){18, 16, 13, 16};
    Player->player_sprite.position = (SDL_FRect){0, 100, 52, 64};

    Player->physics.w_scale =  Player->player_sprite.position.w / 13;
    Player->physics.h_scale =  Player->player_sprite.position.h / 16;


    Player->player_func.quit = Player_Quit;
    Player->player_func.update = Player_Update;
    Player->player_func.handle_events = Player_Events;
    Player->player_func.render = Player_Render;

    return 0;
}

