#ifndef SDLITE_TEXTURE_H
#define SDLITE_TEXTURE_H

#ifdef __cplusplus
extern "C"{
#endif

#include "SDLite/common_libs.h"
#include "SDLite/SDLite_display.h"

typedef struct SDLite_Texture SDLite_Texture;

/*
    Creates SDLite_Texture using the file given
    View SDL_Image documentation on IMG_LoadTexture() to see supported image formats

    Will fail if either SDLite_Display* or const char* is NULL,
    or if the file fails to load

    returns SDLite_Texture* on success, returns NULL on failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Texture* SDLite_CreateTexture(const SDLite_Display *display, const char *file);

/*
    Reference counting is handled internally by SDLite

    The pointer of the texture will be set to NULL if the texture is actually freed
*/
SDLite_DLL void SDLite_DestroyTexture(SDLite_Texture **texture);


/*
    Returns number of references to the SDLite_Texture

    This function only really exists for debugging purposes. 
    You could use this to check if a texture hasn't been freed by the end of the program

    Will fail if const SDLite_Texture* is NULL

    returns numbers of references on success, returns 0 on failure
*/
SDLite_DLL uint64_t SDLite_Texture_GetRefs(const SDLite_Texture *texture);

/*
    Returns the internal SDL_Texture* used by SDLite_Texture

    This is useful if you want to use the texture with SDL functions

    Will fail if const SDLite_Texture* is NULL

    returns SDL_Texture* on success, returns NULL on failure
*/
SDLite_DLL SDL_Texture* SDLite_Texture_GetSDLTexture(const SDLite_Texture *texture);    



#ifdef __cplusplus
}
#endif

#endif