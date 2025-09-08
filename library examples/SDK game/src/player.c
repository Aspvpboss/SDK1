#include "player.h"
#include "common.h"

const char TEXTURE_PATH[] = "./assets/Char_Sprites/char_spritesheet.png";



void Player_Update(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;

}


void Player_Events(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;    

}


void Player_Render(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;
    PlayerClass *Player = &state->Player;

    SDL_SetTextureScaleMode(Player->player_sprite[index].atlas, SDL_SCALEMODE_NEAREST);

    SDL_RenderTexture(state->display.renderer, Player->player_sprite[index].atlas, &Player->player_sprite[index].atlas_frame, &Player->player_sprite[index].position);

}


void Player_Quit(void *appstate, int index){
    Appstate *state = (Appstate*) appstate;
    PlayerClass *Player = &state->Player;

    SDL_DestroyTexture(Player->player_sprite->atlas);
}




int player_init(void *appstate){

    Appstate *state = (Appstate*) appstate;

    PlayerClass *Player = &state->Player;
    SDK_Display *display = &state->display;
    Player->amount_players = 1;

    Player->player_sprite = malloc(sizeof(Entity_Sprite) * Player->amount_players);
    if(Player->player_sprite == NULL)
        return 1;
    
    Player->player_sprite[0].atlas = IMG_LoadTexture(display->renderer, TEXTURE_PATH);
    if(Player->player_sprite[0].atlas == NULL)
        return 1;
    
    Player->player_sprite[0].atlas_frame = (SDL_FRect){18, 16, 13, 16};
    Player->player_sprite[0].position = (SDL_FRect){0, 100, 52, 64};


    Player->player_func = malloc(sizeof(Entity_Method) * Player->amount_players);
    if(Player->player_func == NULL)
        return 1;
    
    Player->player_func[0].quit = Player_Quit;
    Player->player_func[0].update = Player_Update;
    Player->player_func[0].handle_events = Player_Events;
    Player->player_func[0].render = Player_Render;

    return 0;
}

