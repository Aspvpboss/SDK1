#include "SDK_Text.h"


typedef struct{

    TTF_Font *font;
    SDL_Color color;
    TTF_Text *text;
    TTF_TextEngine *engine;
    int wrap_width;
    float font_size;

} Text_Data;


SDK_Text* SDK_CreateText(SDK_Display *display, const char *font_path, float font_size, int x, int y, SDL_Color color){
    
    SDK_Text *text = t_malloc(sizeof(SDK_Text));

    if(!text) return NULL;

    text->data = t_malloc(sizeof(Text_Data));

    if(!text->data){
        t_free(text);
        return NULL;
    }

    Text_Data *data = (Text_Data*)text->data;

    data->engine = display->text_engine;
    data->color = color;
    text->rect.x = x;
    text->rect.y = y;
    data->font_size = font_size;
    data->wrap_width = 0;

    if(font_path == NULL){

        data->font = TTF_OpenFont("./SDK1/assets/default.ttf", font_size);
        if(data->font == NULL){
            t_free(text->data);
            t_free(text);
            return NULL;
        }
            

    } else{

        data->font = TTF_OpenFont(font_path, font_size);
        if(data->font == NULL){
            t_free(text->data);
            t_free(text);
            return NULL;
        }
            

    }



    data->text = TTF_CreateText(data->engine, data->font, "", data->wrap_width);
    
    if(data->text == NULL){
        t_free(text);
        t_free(text->data);
        return NULL;
    }
    
    TTF_SetTextColor(data->text, color.r, color.g, color.b, color.a);

    TTF_SetTextWrapWidth(data->text, 0);

    int w, h;

    if(!TTF_GetTextSize(data->text, &w,  &h)){
        TTF_DestroyText(data->text);
        t_free(text->data);
        t_free(text);
        return NULL;
    }

    text->rect.w = w;
    text->rect.h = h;

    return text;
}


void SDK_DestroyText(SDK_Text *text){

    if(!text) return;

    Text_Data *data = (Text_Data*)text->data;

    TTF_DestroyText(data->text);
    TTF_CloseFont(data->font);
    data->engine = NULL;
    t_free(text);

}


int SDK_Text_UpdateFont(SDK_Text *text, const char *font_path, float font_size){

    if(!text) return 1;
    
    if(font_path == NULL){
        printf("font_path can't be null\n");
        return 1;
    }

    Text_Data *data = (Text_Data*)text->data;
    
    TTF_Font *new_font = TTF_OpenFont(font_path, font_size);

    if(new_font == NULL){
        return 1;
    }

    TTF_CloseFont(data->font);

    data->font = new_font;
    data->font_size = font_size;
    
    if(!TTF_SetTextFont(data->text, data->font)){
        return 1;
    }

    return 0;
}


int SDK_Text_UpdateFontSize(SDK_Text *text, float font_size){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_SetFontSize(data->font, font_size))
        return 1;

    data->font_size = font_size;

    return 0;
}


int SDK_Text_UpdateString(SDK_Text *text, const char *string){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_SetTextString(data->text, string, 0)){
        return 1;
    }

    return 0;
}


int SDK_Text_UpdatePosition(SDK_Text *text, int x, int y){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_SetTextPosition(data->text, x, y)){
        return 1;
    }

    text->rect.x = x;
    text->rect.y = y;

    return 0;
}


int SDK_Text_UpdateSize(SDK_Text *text){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    int w, h;

    if(!TTF_GetTextSize(data->text, &w, &h)){
        return 1;
    }

    text->rect.w = w;
    text->rect.h = h;

    return 0;
}


int SDK_Text_UpdateWrapWidth(SDK_Text *text, int wrap_width){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_SetTextWrapWidth(data->text, wrap_width)){
        return 1;
    }

    data->wrap_width = wrap_width;

    return 0;
}


int SDK_Text_UpdateColor(SDK_Text *text, SDL_Color color){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_SetTextColor(data->text, color.r, color.g, color.b, color.a)){
        return 1;
    }

    data->color = color;

    return 0;
}


int SDK_Render_Text(SDK_Text *text){

    if(!text) return 1;

    Text_Data *data = (Text_Data*)text->data;

    if(!TTF_DrawRendererText(data->text, text->rect.x, text->rect.y))
        return 1;

    return 0;
}

