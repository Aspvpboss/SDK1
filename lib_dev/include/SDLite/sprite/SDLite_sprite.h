/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_SPRITE_H
#define SDLite_SPRITE_H

#ifdef __cplusplus
extern "C"{
#endif


#include "SDLite/common_libs.h"
#include "SDLite/SDLite_display.h"
#include "SDLite/SDLite_time.h"
#include "SDLite/SDLite_texture.h"


/*
    Three main sprite types

    Rect - renders a simple color rect, either filled or not filled 

    Static - renders a texture that was loaded from an image

    Animated - renders an animated texture, it uses the image as a spritesheet

*/

/*
    These functions should only be called on the main thread
*/
typedef struct SDLite_Sprite SDLite_Sprite;


/* ============== Static sprite / general sprite functions ============== */



/*
    Creates a static SDLite_Sprite with the specified attributes
    If texture_path is NULL then you must set a texture or else nothing will render
    SDLite_Sprite needs to be freed by SDLite_DestroySprite()

    returns SDLite_Sprite* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Sprite* SDLite_Create_StaticSprite(
    const SDLite_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);


/*
    Frees a SDLite_Sprite (whether animated, static, or rect)

    Will return early if SDLite_Sprite is NULL
*/
SDLite_DLL void SDLite_DestroySprite(SDLite_Sprite *sprite);

/*
    Renders a sprite onto the display

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Render_Sprite(const SDLite_Display *display, const SDLite_Sprite *sprite);


/*
    Returns the SDL_Texture* of the given SDLite_Sprite*

    will fail if SDLite_Sprite* or SDL_Texture* are NULL, or if the SDLite_Sprite* is a SDLite_RECT_SPRITE 
    
    returns SDL_Texture* for success, returns NULL for failure
*/
SDLite_DLL SDL_Texture* SDLite_Sprite_GetSDLTexture(const SDLite_Sprite *sprite);

/*
    Sets the SDLite_Texture* of the given SDLite_Sprite*. The SDLite_Texture* is used when rendering the SDLite_Sprite*
    The SDLite_Sprite* does not take ownership of the texture, 
    but it will decrement the SDLite_Texture* reference when destroyed

    If the SDLite_Sprite* already has a texture, it will free its reference and then set the new texture

    Will fail if SDLite_Sprite* or SDLite_Texture* are NULL, or if the SDLite_Sprite* is a SDLite_RECT_SPRITE 

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetTexture(SDLite_Sprite *sprite, SDLite_Texture *texture);


/*
    Fills in double* with the scale of the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if double* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_GetScale(const SDLite_Sprite *sprite, double *scale);

/*
    Scales the width and height of the render_rect relative to the original width and height when the sprite was created
    The scale is used when rendering the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if the new_scale <= 0.0f

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetScale(SDLite_Sprite *sprite, double new_scale);



/*
    Fills in double* with the angle in degrees of the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if double* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_GetAngle(const SDLite_Sprite *sprite, double *angle);


/*
    Sets the angle in degrees of the SDLite_Sprite*
    The angle is used for rendering the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetAngle(SDLite_Sprite *sprite, double angle);


/*
    Fills in SDL_FPoint* with the SDL_FPoint of the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if SDL_FPoint* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_GetPivotPoint(const SDLite_Sprite *sprite, SDL_FPoint *pivot_point);

/*
    Sets the pivot_point of the SDLite_Sprite*
    The pivot_point is where on the sprite it rotates around when rendered

    Will fail if SDLite_Sprite* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetPivotPoint(SDLite_Sprite *sprite, SDL_FPoint pivot_point);


/*
    Fills in SDL_FPoint* with the SDL_FlipMode of the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if SDL_FlipMode* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_GetFlipMode(const SDLite_Sprite *sprite, SDL_FlipMode *flip_mode);


/*
    Sets the SDL_FlipMode of the SDLite_Sprite*
    The SDL_FlipMode is used when rendering the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetFlipMode(SDLite_Sprite *sprite, SDL_FlipMode flip_mode);


/*
    Fills in SDL_FRect* with the render_rect of the SDLite_Sprite*

    Will fail if SDLite_Sprite* is NULL or if SDL_FRect* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_Get_RenderRect(const SDLite_Sprite *sprite, SDL_FRect *render_rect);



/*
    Sets the position of the SDLite_Sprite*
    This changes the x & y parameters of the render_rect used for rendering

    Will fail if SDLite_Sprite* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_Set_Position(SDLite_Sprite *sprite, SDL_FPoint position);




/* ============== Animated sprite functions ============== */



/*
    Only use this with stack arrays such as 'SDL_FRect frames[5];'
    This macro calculates the amounts of frames with the array
*/
#define SDLite_GET_ANIMATION_FRAMES(frames) sizeof(frames) / sizeof(SDL_FRect)



/*
    Creates an animated SDLite_Sprite with the specified attributes
    this doesn't add animations to the sprite yet, use SDLite_Sprite_AddAnimation() to do so
    
    If texture_path is NULL then you must set a texture using SDLite_Sprite_SetTexture() or else nothing will render
    SDLite_Sprite needs to be freed by SDLite_DestroySprite()

    returns SDLite_Sprite* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Sprite* SDLite_Create_AnimatedSprite(
    const SDLite_Display *display, const char *texture_path, SDL_FPoint sprite_pos, SDL_FRect src_rect);




/*
    Allocates storage for animations in the SDLite_Sprite*

    Function will use realloc if called a multiple times 
    Recommended to just call this function once per sprite

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_AllocAnimation(SDLite_Sprite *animated_sprite, uint16_t animation_capacity);


/*
    Adds an animation at the specified index in the animated_sprite

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Sprite_AddAnimation(SDLite_Sprite *animated_sprite, SDL_FRect *frames, uint8_t amount_frames, double fps, uint16_t animation_index);

/*
    Updates frames of an animation, must be called once per frame for animations to work

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Sprite_UpdateAnimation(const SDLite_Sprite *animated_sprite, SDLite_Time *time);

/*
    Selects an animation within the SDLite_Sprite

    function will fail if 'animation_select' is greater than the amount of animations allocated in the sprite

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Sprite_SelectAnimation(SDLite_Sprite *animated_sprite, uint16_t animation_index);


/*
    Sets the bool that plays the selected animation once
    
    If you set the bool to true it will play the animation once
    After the animation is done playing, the bool will be set to false

    If you set the bool to false while the animation is playing, the animation will simply reset and stop
    
    Animation will not play if it isn't enabled by SDLite_Sprite_EnableAnimation(); 

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetPlayAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool play);



/*
    Sets the bool that loops the selected animation
    If you set the bool to true it will loop the animation
    If you set the bool to false it will stop looping the animatio

    Animation will not play if it isn't enabled by SDLite_Sprite_EnableAnimation();

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetLoopAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool loop);



/*
    Sets the bool that enables the selected animation 
    If you set the bool to true it will enable the animation to play
    If you set the bool to false it will disable the animation from playing

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_EnableAnimation(const SDLite_Sprite *animated_sprite, uint16_t animation_index, bool enabled);



/* ============== Rect sprite functions ============== */



/*
    Creates a rectangle SDLite_Sprite with the specified attributes
    If texture_path is NULL then you must set a texture using SDLite_Sprite_SetTexture() or else nothing will render
    SDLite_Sprite needs to be freed by SDLite_DestroySprite()

    returns SDLite_Sprite* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Sprite* SDLite_Create_RectSprite(SDL_FRect rect, SDL_Color color, bool is_filled);




/*
    Sets new color to rect SDLite_Sprite*

    Functions only fails if SDLite_Sprite* is NULL or if it isn't a SDLite_RECT_SPRITE 

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Sprite_SetRectColor(SDLite_Sprite *rect_sprite, SDL_Color color);





#ifdef __cplusplus
}
#endif


#endif  
