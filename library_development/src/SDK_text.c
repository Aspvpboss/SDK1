#include "SDK_text.h"



SDK_TextDisplay* SDK_CreateText(SDK_Display *display, const char *font_path, float font_size, int x, int y, SDL_Color color){
    
    SDK_TextDisplay *text = t_malloc(sizeof(SDK_TextDisplay));

    text->engine = display->text_engine;
    text->color = color;
    text->rect.x = x;
    text->rect.y = y;
    text->font_size = font_size;
    text->wrap_width = 0;

    if(font_path == NULL){

        text->font = TTF_OpenFont("./SDK1/assets/default.ttf", font_size);
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



    text->text = TTF_CreateText(text->engine, text->font, "", text->wrap_width);
    
    if(text->text == NULL){
        t_free(text);
        return NULL;
    }
    
    TTF_SetTextColor(text->text, color.r, color.g, color.b, color.a);

    TTF_SetTextWrapWidth(text->text, 0);

    int w, h;

    if(!TTF_GetTextSize(text->text, &w,  &h)){
        TTF_DestroyText(text->text);
        t_free(text);
        return NULL;
    }

    text->rect.w = w;
    text->rect.h = h;

    return text;
}


void SDK_DestroyText(SDK_TextDisplay *text){

    if(!text) return;

    TTF_DestroyText(text->text);
    TTF_CloseFont(text->font);
    text->engine = NULL;
    t_free(text);

}


int SDK_Text_UpdateFont(SDK_TextDisplay *text, const char *font_path, float font_size){
    
    if(font_path == NULL){
        printf("font_path can't be null\n");
        return 1;
    }

    
    TTF_Font *new_font = TTF_OpenFont(font_path, font_size);

    if(new_font == NULL){
        return 1;
    }

    TTF_CloseFont(text->font);

    text->font = new_font;
    text->font_size = font_size;
    
    if(!TTF_SetTextFont(text->text, text->font)){
        return 1;
    }

    return 0;
}


int SDK_Text_UpdateFontSize(SDK_TextDisplay *text, float font_size){
    
    if(!TTF_SetFontSize(text->font, font_size))
        return 1;

    text->font_size = font_size;

    return 0;
}


int SDK_Text_UpdateString(SDK_TextDisplay *text, const char *string){

    if(!TTF_SetTextString(text->text, string, 0)){
        return 1;
    }

    return 0;
}


int SDK_Text_UpdatePosition(SDK_TextDisplay *text, int x, int y){

    if(!TTF_SetTextPosition(text->text, x, y)){
        return 1;
    }

    text->rect.x = x;
    text->rect.y = y;

    return 0;
}


int SDK_Text_UpdateSize(SDK_TextDisplay *text){

    int w, h;

    if(!TTF_GetTextSize(text->text, &w, &h)){
        return 1;
    }

    text->rect.w = w;
    text->rect.h = h;

    return 0;
}


int SDK_Text_UpdateWrapWidth(SDK_TextDisplay *text, int wrap_width){

    if(!TTF_SetTextWrapWidth(text->text, wrap_width)){
        return 1;
    }

    text->wrap_width = wrap_width;

    return 0;
}


int SDK_Text_UpdateColor(SDK_TextDisplay *text, SDL_Color color){

    if(!TTF_SetTextColor(text->text, color.r, color.g, color.b, color.a)){
        return 1;
    }

    text->color = color;

    return 0;
}


int SDK_Text_Render(SDK_TextDisplay *text){

    if(!TTF_DrawRendererText(text->text, text->rect.x, text->rect.y))
        return 1;

    return 0;
}

