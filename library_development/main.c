#include "SDK.h"

#define TEXTURE_PATH "./SDK1/assets/blue.png"


void update_text(SDK_TextDisplay *text, double fps){

    static char fps_text[40];

    snprintf(fps_text, sizeof(fps_text), "FPS: %.2f", fps);

    SDK_Text_UpdateString(text, fps_text);

}


void update_sprite_info(SDK_Sprite *sprite, SDK_Input *input, SDK_Time *time){

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_RIGHT)){
        sprite->angle += (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_LEFT)){
        sprite->angle -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_W)){
        sprite->position.y -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_S)){
        sprite->position.y += (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_A)){
        sprite->position.x -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_D)){
        sprite->position.x += (128 * time->dt);
    }



}


void render(SDK_Display *display, SDK_TextDisplay *text, SDK_Sprite *sprite, SDK_Sprite *sprite_two){

    SDL_RenderClear(display->renderer);

    SDK_RenderSprite(display, sprite);
    SDK_RenderSprite(display, sprite_two);
    SDK_Text_Render(text);

    SDL_RenderPresent(display->renderer);

}


int main(){

    SDK_Init();



    SDK_Display *display = SDK_CreateDisplay("SDK window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDK_Time *time = SDK_CreateTime(1000);
    SDK_Input *input = SDK_CreateInput();
    SDK_TextDisplay *text = SDK_CreateText(display, NULL, 20, 5, 5, (SDL_Color){255, 255, 255, 255});
    
    SDK_Sprite *sprite = SDK_Create_StaticSprite(display, TEXTURE_PATH, (SDL_FPoint){0, 0}, (SDL_FRect){0, 0, 998, 917});
    SDK_Sprite *sprite_two = SDK_Create_StaticSprite(display, TEXTURE_PATH, (SDL_FPoint){50, 50}, (SDL_FRect){0, 0, 998, 917});
    SDK_Sprite_UpdateScale(sprite, 0.2f);
    SDK_Sprite_UpdateScale(sprite_two, 0.2f);

    

    if(!sprite){
        printf("Kys!\n");
        return 1;
    }

    if(!text){
        printf("Kys!\n");
        return 1;
    }

    bool running = true;
    SDL_Event e;

    while(running){

        while(SDL_PollEvent(&e)){

            if(e.type == SDL_EVENT_QUIT){
                running = false;
            }
                
        }

        if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_ESCAPE)){
            running = false;
        }

        if(time->fps_updated){
            update_text(text, time->fps);
        }

        if(SDK_Sprite_CheckCollision(sprite, sprite_two) && time->fps_updated)
            printf("colliding!\n");



        update_sprite_info(sprite, input, time);
        SDK_Sprite_UpdatePosition(sprite, true, true);
        
            
        SDK_TimeFunctions(time);
        SDK_Update_Previous_Inputs(input);

        render(display, text, sprite, sprite_two);

    }

    SDK_DestroyDisplay(display);
    display = NULL;
    SDK_DestroyInput(input);
    input = NULL;
    SDK_DestroyTime(time);
    time = NULL;
    SDK_DestroyText(text);
    text = NULL;
    SDK_DestroySprite(sprite);
    sprite = NULL;
    SDK_DestroySprite(sprite_two);
    sprite_two = NULL;

    
    SDK_Quit();


    return 0;
}