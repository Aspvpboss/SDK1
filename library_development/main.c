#include "SDK1/SDK.h"

#define TEXTURE_PATH_BLUE "./assets/blue.bmp"
#define TEXTURE_PATH_COOL "./assets/char_spritesheet.png"



void update_text(SDK_Text *text, double fps){

    static char fps_text[40];

    snprintf(fps_text, sizeof(fps_text), "FPS: %.2f", fps);

    SDK_Text_UpdateString(text, fps_text);

}


void update_sprite_info(SDK_Sprite *sprite, SDK_Sprite *sprite_two, SDK_Input *input, SDK_Time *time){


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




SDK_Entity* init_entity_one(SDK_Display *display){

    SDK_Entity *entity = SDK_Create_Entity((SDL_FRect){0, 0, 13, 16}, (SDL_FRect){0, 0, 13, 16}, NULL, 1, NULL, NULL);


    SDK_Sprite *sprite = SDK_Entity_AddSprite(
        entity, display, TEXTURE_PATH_COOL, (SDL_FRect){18, 16, 13, 16}, (SDL_Point){0, 0}, SDK_ANIMATED_SPRITE);

    if(!sprite)
        return NULL;

    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 16, 13, 16}, 5, 6.7f, 3.0f, true, false);
    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 32, 13, 16}, 5, 6.7f, 3.0f, true, false);
    SDL_SetTextureScaleMode(sprite->texture, SDL_SCALEMODE_NEAREST);

    sprite = SDK_Entity_AddSprite(
        entity, display, TEXTURE_PATH_COOL, (SDL_FRect){18, 16, 13, 16}, (SDL_Point){1, 0}, SDK_ANIMATED_SPRITE);

    if(!sprite)
        return NULL;

    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 16, 13, 16}, 5, 6.7f, 3.0f, true, false);
    SDK_Sprite_AddAnimation(sprite, (SDL_FRect){18, 32, 13, 16}, 5, 6.7f, 3.0f, true, false);
    SDL_SetTextureScaleMode(sprite->texture, SDL_SCALEMODE_NEAREST);

    return entity;
}


int main(){

    if(SDK_Init(NULL, NULL, true, true, true)){
        return 1;
    }


    SDK_Display *display = SDK_CreateDisplay("SDK window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDK_Time *time = SDK_CreateTime(144);
    SDK_Input *input = SDK_CreateInput();
    SDK_Text *text = SDK_CreateText(display, NULL, 20, 5, 5, (SDL_Color){255, 255, 255, 255});
    SDK_Sprite_Manager *manager = SDK_Create_SpriteManager(16, 16);


    SDK_Entity *entity_one = init_entity_one(display);
    entity_one->scale = 8.0f;
    SDK_Entity_UpdateSpriteRects(entity_one);


    SDK_Entity_SetLoopAnimation(entity_one, false);




    if(!entity_one){
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

        if(time->fps_updated)
            update_text(text, time->fps);

        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_A)){
            double movement = 128 * time->dt;
            entity_one->render_rect.x -= movement;
            entity_one->collision_rect.x -= movement;
            entity_one->is_updated = true;
        }
        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_D)){
            double movement = 128 * time->dt;
            entity_one->render_rect.x += movement;
            entity_one->collision_rect.x += movement;
            entity_one->is_updated = true;
        }
        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_W)){
            double movement = 128 * time->dt;
            entity_one->render_rect.y -= movement;
            entity_one->collision_rect.y -= movement;
            entity_one->is_updated = true;
        }
        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_S)){
            double movement = 128 * time->dt;
            entity_one->render_rect.y += movement;
            entity_one->collision_rect.y += movement;
            entity_one->is_updated = true;
        }
        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_RIGHT)){
            double movement = 128 * time->dt;
            entity_one->angle += movement;
            entity_one->is_updated = true;
        }
        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_LEFT)){
            double movement = 128 * time->dt;
            entity_one->angle -= movement;
            entity_one->is_updated = true;
        }

        // SDK_Entity_SetPlayAnimation(entity_one, false);

        if(SDK_Keyboard_Pressed(input, SDL_SCANCODE_UP)){
            SDK_Entity_SetPlayAnimation(entity_one, true);
            entity_one->is_updated = true;
        }


        SDK_Entity_UpdateAnimation(entity_one, time);
        SDK_Entity_UpdateSpriteRects(entity_one);
        SDK_SpriteManager_AddEntitySprites(manager, entity_one);



        SDL_RenderClear(display->renderer);



        SDK_Render_SpriteManager(display, manager);
        SDK_Render_Text(text);



        SDL_RenderPresent(display->renderer);
 

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
    SDK_Destroy_SpriteManager(manager);
    manager = NULL;
    SDK_Destroy_Entity(entity_one);
    entity_one = NULL;

    
    SDK_Quit();


    return 0;
}