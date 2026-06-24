// this is the test file for the framework
// the entire file is just bad practice, but idc

#include "SDLite/SDLite.h"

#define TEXTURE_PATH_BLUE "./assets/blue.bmp"
#define TEXTURE_PATH_COOL "./assets/char_spritesheet.png"


typedef enum{

    IDLE_ANIMATION,
    MAX_ANIMATIONS

} Player_Animations;




void update_text(SDLite_Text *text, double fps){

    char fps_text[40];

    snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", fps);

    SDLite_Text_SetString(text, fps_text);

}


int thread_func(void *ptr){
    int *ptrptr = (int *)t_malloc(sizeof(int));
    ptrptr[0] = 0;
    return 0;
}

int test_sprite_getters_setters(SDLite_Sprite *sprite){

    /* ---------- SCALE ---------- */
    if (SDLite_Sprite_SetScale(sprite, 2.0) == 0) {
        double scale = 0.0;
        if (SDLite_Sprite_GetScale(sprite, &scale) == 0) {
            printf("Scale: %f\n", scale);
        } else {
            printf("Failed to get scale\n");
        }
    } else {
        printf("Failed to set scale\n");
    }

    /* ---------- ANGLE ---------- */
    if (SDLite_Sprite_SetAngle(sprite, 45.0) == 0) {
        double angle = 0.0;
        if (SDLite_Sprite_GetAngle(sprite, &angle) == 0) {
            printf("Angle: %f\n", angle);
        } else {
            printf("Failed to get angle\n");
        }
    } else {
        printf("Failed to set angle\n");
    }

    /* ---------- PIVOT POINT ---------- */
    SDL_FPoint pivot_set = { 10.0f, 20.0f };
    if (SDLite_Sprite_SetPivotPoint(sprite, pivot_set) == 0) {
        SDL_FPoint pivot_get;
        if (SDLite_Sprite_GetPivotPoint(sprite, &pivot_get) == 0) {
            printf("Pivot: (%f, %f)\n", pivot_get.x, pivot_get.y);
        } else {
            printf("Failed to get pivot\n");
        }
    } else {
        printf("Failed to set pivot\n");
    }

    /* ---------- FLIP MODE ---------- */
    if (SDLite_Sprite_SetFlipMode(sprite, SDL_FLIP_HORIZONTAL) == 0) {
        SDL_FlipMode flip;
        if (SDLite_Sprite_GetFlipMode(sprite, &flip) == 0) {
            printf("Flip mode: %d\n", flip);
        } else {
            printf("Failed to get flip mode\n");
        }
    } else {
        printf("Failed to set flip mode\n");
    }

    /* ---------- RENDER RECT ---------- */
    SDL_FRect rect;
    if (SDLite_Sprite_Get_RenderRect(sprite, &rect) == 0) {
        printf("RenderRect: x=%f y=%f w=%f h=%f\n",
               rect.x, rect.y, rect.w, rect.h);
    } else {
        printf("Failed to get render rect\n");
    }

    /* ---------- POSITION ---------- */
    SDL_FPoint pos = { 100.0f, 200.0f };
    if (SDLite_Sprite_Set_Position(sprite, pos) == 0) {
        SDL_FRect rect2;
        if (SDLite_Sprite_Get_RenderRect(sprite, &rect2) == 0) {
            printf("Position after set: (%f, %f)\n", rect2.x, rect2.y);
        }
    } else {
        printf("Failed to set position\n");
    }

    return 0;
}




int main(){

    if(SDLite_Init(NULL, NULL, true, true)){
        return 1;
    }



    void *data = NULL;
    SDL_Thread *thread = SDL_CreateThread(thread_func, "function", data);
    int result = 0;
    SDL_WaitThread(thread, &result);

    int macro, minor, micro;
    SDLite_Version_GetNumbers(&macro, &minor, &micro);
    printf("SDK version: %d.%d.%d\n", macro, minor, micro);


    SDLite_Audio_Handler *audio_handler = SDLite_Create_AudioHandler(4, 1.0f);
    SDLite_Display *display = SDLite_CreateDisplay("SDLite window", 800, 800, SDL_WINDOW_MAXIMIZED);
    SDLite_Time *time = SDLite_CreateTime(144);
    SDLite_Input *input = SDLite_CreateInput();
    if(!input){
        SDL_Log("%s\n", SDL_GetError());
        return 1;
    }

    const SDL_Color WHITE = {255, 255, 255, 255};
    SDLite_Text *text = SDLite_CreateText(display, NULL, NULL, 20, 5, 5, WHITE);
    SDLite_Sprite_Manager *manager = SDLite_Create_SpriteManager(16, 16);

    

    MIX_Audio *audio = MIX_LoadAudio(SDLite_Audio_GetMixer(audio_handler), "SDLite/assets/sample_mp3.mp3", true);
    if(!audio){
        printf("audio failed to laod\n");
        return 1;
    }
    SDLite_Audio_SetTrackAudio(audio_handler, 0, audio); 
    SDLite_Audio_SetTrackProp(audio_handler, 0, MIX_PROP_PLAY_MAX_MILLISECONDS_NUMBER, 10000);

    // goat player
    const SDL_FPoint player_coord = {100, 0};
    const SDL_FRect player_rect = {18, 16, 13, 16};
    SDLite_Sprite *player = SDLite_Create_AnimatedSprite(display, TEXTURE_PATH_COOL, player_coord, player_rect);
    if(!player){
        SDL_Log("Error loading player: %s\n", SDL_GetError());
        return 1;
    }

    test_sprite_getters_setters(player);

    // boilerplate stuff for animations
    SDLite_Sprite_AllocAnimation(player, MAX_ANIMATIONS);
    SDL_FRect frames[] = {
        {18, 16, 13, 16},
        {33, 16, 14, 16},
        {49, 16, 13, 16},
        {65, 16, 13, 16},
        {81, 16, 14, 16}
    };
    uint16_t num_frames = SDLite_GET_ANIMATION_FRAMES(frames);
    SDLite_Sprite_AddAnimation(player, frames, num_frames, num_frames, IDLE_ANIMATION);
    SDLite_Sprite_SetLoopAnimation(player, IDLE_ANIMATION, true);
    SDLite_Sprite_EnableAnimation(player, IDLE_ANIMATION, true);
    // player->flip_mode = SDL_FLIP_HORIZONTAL;

    
    const SDL_FRect static_rect = {0, 0, 400, 400};
    const SDL_FPoint static_pos = {10, 0};
    SDLite_Sprite *square = SDLite_Create_StaticSprite(display, TEXTURE_PATH_BLUE, static_pos, static_rect);
    if(!square){
        SDL_Log("Error loading square: %s\n", SDL_GetError());
        return 1;
    } 

    SDLite_Sprite_SetScale(player, 8.0f);
    SDL_SetTextureScaleMode(SDLite_Sprite_GetSDLTexture(player), SDL_SCALEMODE_NEAREST);
    

    const SDL_Color red = {255, 0, 0, 0};
    const SDL_FRect rect_rect = {350, 0, 150, 150};
    SDLite_Sprite *rectangle = SDLite_Create_RectSprite(rect_rect, red, true);

    if(!rectangle)
        return 1;

    if(!text){
        return 1;
    }


    // testing with these rects
    SDL_FRect a = {0.0f, 0.0f, 10.0f, 10.0f};
    SDL_FRect b = {0.0f, 9.0f, 10.0f, 10.0f};
    SDL_FPoint point = {1.0f, 10.0f};

    if(SDLite_Collision_RectPoint(&b, &point)){
        printf("rectangle and point are colliding\n");
    }

    if(SDLite_Collision_Rect(&a, &b)){
        printf("The rectangles are colliding\n");
    } else{
        printf("The rectangles aren't colliding\n");
    }

    // didn't feel like making all the switch statements
    switch(SDLite_Collision_RectDir(&a, &b)){

        case(SDLITE_COLLISION_UP):
            printf("colliding on top\n");
            break;
        
        case(SDLITE_COLLISION_DOWN):
            printf("colliding on bottom\n");
            break;

        case(SDLITE_COLLISION_NONE):
            printf("not colliding\n");
            break;

        default:
            printf("some collision direction\n");
            break;
    }


    bool running = true;
    SDL_Event e;


    if(SDLite_Display_GetWindowFlags(display) & SDL_WINDOW_FULLSCREEN){
        printf("is fullscreen\n");
    } else{
        printf("not fullscreen\n");
    }


    while(running){

        while(SDL_PollEvent(&e)){

            if(e.type == SDL_EVENT_QUIT){
                running = false;
            }        
        
        }

        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_ESCAPE)){
            running = false;
        }

        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_UP)){
            SDLite_Audio_PlayTrack(audio_handler, 0);
        }
        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_DOWN)){
            SDLite_Audio_StopTrack(audio_handler, 0, 24000);
        }


        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_1)){
            SDLite_Time_Set_FPSLimit(time, 10);
        }
        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_2)){
            SDLite_Time_Set_FPSLimit(time, 144.0f);
        }
        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_3)){
            SDLite_Time_Set_FPSLimit(time, 1500.0f);
        }
        if(SDLite_Input_KeyJustPressed(input, SDL_SCANCODE_4)){
            SDLite_Time_Set_FPSLimit(time, -1.0f);
        }


        if(SDLite_Time_Is_FPSUpdated(time))
            update_text(text, SDLite_Time_GetFPS(time));
         

        SDLite_DisplayClear(display);

        SDLite_SpriteManager_QueueSprite(manager, player, 1); 
        SDLite_SpriteManager_QueueSprite(manager, square, 0); 
        SDLite_SpriteManager_QueueSprite(manager, rectangle, 0);
       
        SDLite_Render_SpriteManager(display, manager);
        SDLite_Render_Text(text);

        SDLite_DisplayPresent(display);

        SDLite_Sprite_UpdateAnimation(player, time);
        SDLite_TimeFunctions(time);
        SDLite_Input_UpdateAllPrev(input);
    }

    SDLite_DestroyDisplay(display);
    display = NULL;
    SDLite_DestroyInput(input);
    input = NULL;
    SDLite_DestroyTime(time);
    time = NULL;
    SDLite_DestroyText(text);
    text = NULL;
    SDLite_Destroy_SpriteManager(manager);
    manager = NULL;
    SDLite_Destroy_AudioHandler(audio_handler);
    audio_handler = NULL;
    SDLite_DestroySprite(player);
    player = NULL;
    SDLite_DestroySprite(square);
    square = NULL;
    SDLite_DestroySprite(rectangle);
    rectangle = NULL;

    SDLite_Quit();
    
    return 0;
}
