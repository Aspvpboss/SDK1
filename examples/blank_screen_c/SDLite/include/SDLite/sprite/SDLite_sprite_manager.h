/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_SPRITE_MANAGER_H
#define SDLite_SPRITE_MANAGER_H


#ifdef __cplusplus
extern "C" {
#endif



#include "SDLite/sprite/SDLite_sprite.h"
#include "SDLite/common_libs.h"



/*
    These functions should only be called on the main thread
*/
typedef struct SDLite_Sprite_Manager SDLite_Sprite_Manager;

/*
    Creates a SDLite_Sprite_Manager with the specified attributes

    SDLite_Sprite_Manager needs to be freed by SDLite_Destroy_SpriteManager()

    SDLite_Sprite_Manager allows for rendering sprites is certain orders,
    it does this by using z_depth

    returns SDLite_Sprite_Manager* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Sprite_Manager* SDLite_Create_SpriteManager(uint64_t max_z_depth, uint64_t max_sprites);

/*
    Frees a SDLite_Sprite_Manager

    Will return early if SDLite_Sprite_Manager is NULL
*/
SDLite_DLL void SDLite_Destroy_SpriteManager(SDLite_Sprite_Manager *manager);

/*
    Queues a sprite for rendering at the specified Z depth.

    The sprite is added to the sprite manager’s per-frame render queue and
    will be rendered when SDLite_Render_SpriteManager() is called. Sprites with
    higher Z depth values are rendered after lower ones.

    This function does not take ownership of the sprite and performs no
    rendering itself. The queue is cleared after rendering.

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_SpriteManager_QueueSprite(SDLite_Sprite_Manager *manager, SDLite_Sprite *sprite, uint64_t z_depth);

/*
    Renders all the sprites within each z_layer contained in SDLite_Sprite_Manager

    Will fail if SDLite_Display* or SDLite_Sprite_Manager* is NULL, 
    or it will fail if any of the sprites' textures are NULL, 
    but the function will continue to render all of the sprites before returns a failure

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_Render_SpriteManager(SDLite_Display *display, SDLite_Sprite_Manager *manager);


#ifdef __cplusplus
}
#endif

#endif


