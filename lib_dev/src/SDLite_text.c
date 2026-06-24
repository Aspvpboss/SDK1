/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_Text.h"
#include "SDLite_display_internal.h"

struct SDLite_Text{

    TTF_Font *font;
    TTF_Text *text;
    TTF_TextEngine *engine;
    SDL_Color color;

};


SDLite_Text* SDLite_CreateText(
    const SDLite_Display *display, const char *display_text, const char *font_path, float font_size, int x, int y, SDL_Color color){

    if(!display) return NULL;

    SDLite_Text *text = t_malloc(sizeof(SDLite_Text));
    if(!text) return NULL;


    text->engine = display->text_engine;
    text->color = color;

    if(font_path == NULL){

        text->font = TTF_OpenFont("SDLite/assets/default.ttf", font_size);
        if(text->font == NULL){
            t_free(text);
            return NULL;
        }
            
    } else{

        text->font = TTF_OpenFont(font_path, font_size);
        if(text->font == NULL){
            t_free(text);
            return NULL;
        }
            
    }


    if(!display_text){
        display_text = "";
    }

    text->text = TTF_CreateText(text->engine, text->font, display_text, 0);
    
    if(!text->text){
        TTF_CloseFont(text->font);
        t_free(text);
        return NULL;
    }
    
    if(!TTF_SetTextColor(text->text, color.r, color.g, color.b, color.a)){
        TTF_CloseFont(text->font);
        TTF_DestroyText(text->text);
        t_free(text);
        return NULL;
    }

    if(!TTF_SetTextWrapWidth(text->text, 0)){
        TTF_CloseFont(text->font);
        TTF_DestroyText(text->text);
        t_free(text);
        return NULL;
    }

    int w, h;

    if(!TTF_GetTextSize(text->text, &w,  &h)){
        TTF_CloseFont(text->font);
        TTF_DestroyText(text->text);
        t_free(text);
        return NULL;
    }

    if(!TTF_SetTextPosition(text->text, x, y)){
        TTF_CloseFont(text->font);
        TTF_DestroyText(text->text);
        t_free(text);
        return NULL;
    }

    return text;
}


void SDLite_DestroyText(SDLite_Text *text){

    if(!text) return;

    TTF_DestroyText(text->text);
    TTF_CloseFont(text->font);
    text->engine = NULL;
    t_free(text);

}


TTF_Text* SDLite_Text_GetTTFText(const SDLite_Text *text){

    if(!text) return NULL;

    return text->text;
}

TTF_Font* SDLite_Text_GetTTFFont(const SDLite_Text *text){

    if(!text) return NULL;

    return text->font;
}


int SDLite_Text_SetFont(SDLite_Text *text, const char *font_path, float font_size){

    if(!text) return 1;
    
    if(font_path == NULL){
        return 1;
    }

    TTF_Font *new_font = TTF_OpenFont(font_path, font_size);

    if(new_font == NULL){
        return 1;
    }

    TTF_CloseFont(text->font);

    text->font = new_font;
    
    if(!TTF_SetTextFont(text->text, text->font)){
        return 1;
    }

    return 0;
}


int SDLite_Text_SetFontSize(SDLite_Text *text, float font_size){

    if(!text) return 1;

    if(!TTF_SetFontSize(text->font, font_size))
        return 1;

    return 0;
}


int SDLite_Text_SetString(SDLite_Text *text, const char *string){

    if(!text) return 1;

    if(!TTF_SetTextString(text->text, string, 0)){
        return 1;
    }

    return 0;
}


int SDLite_Text_SetPosition(SDLite_Text *text, int x, int y){

    if(!text) return 1;

    if(!TTF_SetTextPosition(text->text, x, y)){
        return 1;
    }

    return 0;
}


int SDLite_Text_Get_RenderRect(const SDLite_Text *text, SDL_FRect *render_rect){

    if(!text || !render_rect) return 1;

    int x, y, w, h;

    if(!TTF_GetTextSize(text->text, &w, &h)){
        return 1;
    }

    if(!TTF_GetTextPosition(text->text, &x, &y)){
        return 1;
    }

    render_rect->w = w;
    render_rect->h = h;
    render_rect->x = x;
    render_rect->y = y;    

    return 0;
}


int SDLite_Text_SetWrapWidth(SDLite_Text *text, int wrap_width_pixels){

    if(!text) return 1;

    if(!TTF_SetTextWrapWidth(text->text, wrap_width_pixels)){
        return 1;
    }

    return 0;
}


int SDLite_Text_SetColor(SDLite_Text *text, SDL_Color color){

    if(!text) return 1;

    if(!TTF_SetTextColor(text->text, color.r, color.g, color.b, color.a)){
        return 1;
    }

    text->color = color;

    return 0;
}



int SDLite_Render_Text(SDLite_Text *text){

    if(!text) return 1;
 
    int x, y;

    if(!TTF_GetTextPosition(text->text, &x, &y)){
        return 1;
    }

    if(!TTF_DrawRendererText(text->text, x, y))
        return 1;

    return 0;
}

