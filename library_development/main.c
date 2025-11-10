#include "SDK1/SDK.h"

#define TEXTURE_PATH_BLUE "./assets/blue.bmp"
#define TEXTURE_PATH_COOL "./assets/char_spritesheet.png"


void update_text(SDK_TextDisplay *text, double fps){

    static char fps_text[40];

    snprintf(fps_text, sizeof(fps_text), "FPS: %.2f", fps);

    SDK_Text_UpdateString(text, fps_text);

}


void update_sprite_info(SDK_Sprite *sprite, SDK_Sprite *sprite_two, SDK_Input *input, SDK_Time *time){

    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_RIGHT)){
        sprite->angle += (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_LEFT)){
        sprite->angle -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_W)){
        sprite->render_rect.y -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_S)){
        sprite->render_rect.y += (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_A)){
        sprite->render_rect.x -= (128 * time->dt);
    }
    if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_D)){
        sprite->render_rect.x += (128 * time->dt);
    }

    if(SDK_Sprite_CheckCollision(sprite, sprite_two))
        SDK_Sprite_SetPlayAnimation(sprite, true);

    SDK_Sprite_UpdateAnimation(sprite, time);

}


void render(SDK_Display *display, SDK_TextDisplay *text, SDK_Sprite *sprite, SDK_Sprite *sprite_two){

    SDL_RenderClear(display->renderer);
    
    if(SDK_Sprite_CheckCollision(sprite, sprite_two)){
        SDK_RenderSprite(display, sprite_two);
    }
        
    SDK_RenderSprite(display, sprite);
    SDK_Text_Render(text);

    SDL_RenderPresent(display->renderer);

}



SDK_Entity* init_entity(SDK_Display *display){

    SDK_Entity *entity = SDK_Create_Entity((SDL_FRect){0, 0, 13, 16}, (SDL_FRect){0, 0, 13, 16}, NULL, 1, NULL, NULL);

    SDK_Sprite *sprite = SDK_Entity_AddSprite(
        entity, display, TEXTURE_PATH_COOL, (SDL_FRect){18, 16, 13, 16}, (SDL_Point){0, 0}, SDK_ANIMATED_SPRITE);

    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 16, 13, 16}, 5, 6.7f, 3.0f, false, false);
    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 32, 13, 16}, 5, 6.7f, 3.0f, false, false);
    SDL_SetTextureScaleMode(sprite->texture, SDL_SCALEMODE_NEAREST);

}


int main(){

    SDK_Init();


    SDK_Display *display = SDK_CreateDisplay("SDK window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDK_Time *time = SDK_CreateTime(144);
    SDK_Input *input = SDK_CreateInput();
    SDK_TextDisplay *text = SDK_CreateText(display, NULL, 20, 5, 5, (SDL_Color){255, 255, 255, 255});

    SDK_Entity *entity_one = init_entity(display);
    


    SDK_Sprite *sprite_two = SDK_Create_StaticSprite(display, TEXTURE_PATH_BLUE, (SDL_FPoint){50, 50}, (SDL_FRect){0, 0, 400, 400});
    SDK_Sprite_UpdateScale(sprite, 8.0f);
    SDK_Sprite_UpdateScale(sprite_two, 1.0f);



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

        SDK_Sprite_SetPlayAnimation(sprite, false);

        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_UP))
            SDK_Sprite_SetPlayAnimation(sprite, true);

        if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_1))
            SDK_Sprite_SelectAnimation(sprite, 0);
        if(SDK_Keyboard_JustPressed(input, SDL_SCANCODE_2))
            SDK_Sprite_SelectAnimation(sprite, 1);

        if(time->fps_updated){
            update_text(text, time->fps);
        }



        update_sprite_info(sprite, sprite_two, input, time);
        

        render(display, text, sprite, sprite_two);

        SDK_TimeFunctions(time);
        SDK_Update_Previous_Inputs(input);

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