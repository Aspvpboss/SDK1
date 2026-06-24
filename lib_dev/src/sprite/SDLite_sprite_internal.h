#ifndef SDLite_SPRITE_INTERNAL_H
#define SDLite_SPRITE_INTERNAL_H

#include "SDLite/common_libs.h"
#include "SDLite/SDLite_display.h"
#include "SDLite/SDLite_time.h"
#include "SDLite/SDLite_texture.h"
#include "SDLite_texture_internal.h"


enum SDLite_SpriteType{

    SDLite_STATIC_SPRITE,
    SDLite_ANIMATED_SPRITE,
    SDLite_RECT_SPRITE

};


struct SDLite_Sprite{

    enum SDLite_SpriteType sprite_type;
    void *data;

    SDL_FRect render_rect;
    SDL_FlipMode flip_mode;
    double scale;
    double angle;
    SDL_FPoint pivot_point;

};



typedef struct{

    float base_width;
    float base_height;
    SDLite_Texture *texture;
    
    SDL_FRect src_rect;

} SDLite_StaticSprite_Data;


typedef struct{

    float base_width;
    float base_height;
    SDL_Color color;
    bool is_filled;

} SDLite_RectSprite_Data;


typedef struct{

    SDL_FRect *frames;
    uint8_t amount_frames;
    uint8_t current_frame;
    double frame_duration;
    double time_elapsed;
    bool play_animation;
    bool loop_animation;
    bool enable_animation;

} SDLite_Animation;

typedef struct{

    float base_width;
    float base_height;
    SDLite_Texture *texture;

    SDLite_Animation *animation;
    uint16_t amount_animation;
    uint16_t current_animation;

} SDLite_AnimatedSprite_Data;




#endif