/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#include "SDLite/SDLite_time.h"


#define MAX_SAMPLES 200


struct SDLite_Time{

    double dt;
    bool fps_updated;
    double fps;
    double fps_limit;

    uint64_t previous_counter;
    uint64_t counter_frequency;
    uint16_t frame;
    uint16_t collected_frames;
    double total;
    double dt_buffer[MAX_SAMPLES];
    double fps_update_count;

};



SDLite_Time* SDLite_CreateTime(double fps_limit){

    if(fps_limit == 0) return NULL;

    SDLite_Time *time = t_malloc(sizeof(SDLite_Time));
    if(!time) return NULL;

    time->collected_frames = 0;
    time->frame = 0;
    time->total = 0.0f;
    time->previous_counter = 0;
    time->counter_frequency = 0;

    memset(time->dt_buffer, 0, sizeof(time->dt_buffer));

    time->fps_limit = fps_limit;
    time->dt = 0.0f;
    time->fps = 0.0f;
    time->fps_updated = false;
    time->fps_update_count = 0.0f;

    return time;
}

void SDLite_DestroyTime(SDLite_Time *time){

    if(!time) return;
    t_free(time);

}


double SDLite_Time_GetFPS(const SDLite_Time *time){
    
    if(!time) return -1.0f;

    return time->fps;
}

double SDLite_Time_GetDT(const SDLite_Time *time){
    
    if(!time) return -1.0f;

    return time->dt;
}


bool SDLite_Time_Is_FPSUpdated(const SDLite_Time *time){

    if(!time) return false;

    return time->fps_updated;
}


double SDLite_Time_Get_FPSLimit(const SDLite_Time *time){

    if(!time) return 0.0f;

    return time->fps_limit;
}

int SDLite_Time_Set_FPSLimit(SDLite_Time *time, double new_fps_limit){

    if(!time || new_fps_limit == 0.0f) return 1;

    time->fps_limit = new_fps_limit;

    return 0;
}



int SDLite_CalculateDT(SDLite_Time *time){

    if(!time) return 1;

    if(time->counter_frequency == 0){
        time->counter_frequency = SDL_GetPerformanceFrequency();
        time->previous_counter = SDL_GetPerformanceCounter();
        time->dt = 0.0f;
        return 0;
    }
    

    uint64_t current = SDL_GetPerformanceCounter();
    time->dt = (double)(current - time->previous_counter) / (double)time->counter_frequency;
    time->previous_counter = current;

    return 0;
}



int SDLite_CalculateFPS(SDLite_Time *time){

    if(!time) return 1;
    bool *fps_updated = (bool *)&time->fps_updated;
    double *fps = (double *)&time->fps;

    if(time->fps_updated == true){
        *fps_updated = false;
    }

    double *dt_buffer = time->dt_buffer;

    time->total -= dt_buffer[time->frame];
    dt_buffer[time->frame] = time->dt;
    time->total += time->dt;
    time->fps_update_count += time->dt;
    
    if(time->collected_frames < MAX_SAMPLES) time->collected_frames++;

    time->frame = (time->frame + 1) % MAX_SAMPLES;
    *fps = 1 / (time->total / time->collected_frames);

    
    if(time->fps_update_count > 1.0f){
        *fps_updated = true;
        time->fps_update_count = 0.0f;
    }
       

    return 0;
}


int SDLite_LimitFPS(SDLite_Time *time){

    if(!time || time->fps_limit == 0.0f) return 1;
    if(time->fps_limit < 0.0f) return 0;


    double target_delta_time = (1.0 / time->fps_limit); 

    double remaining = target_delta_time - time->dt;
    if(remaining < 0){
        return 0;
    }


    if(remaining > 0.002){
        Uint32 ms = (Uint32)((remaining - 0.001) * 1000.0);
        if (ms > 0) SDL_Delay(ms);
    }

    uint64_t current_counter = SDL_GetPerformanceCounter();
    
    do{
        current_counter = SDL_GetPerformanceCounter();
        time->dt = (double)(current_counter - time->previous_counter) / (double)time->counter_frequency;
    } while(time->dt < target_delta_time);

    time->previous_counter = current_counter;

    time->dt = time->dt;

    return 0;
}


int SDLite_TimeFunctions(SDLite_Time *time){
    if(SDLite_CalculateDT(time)) return 1;
    if(SDLite_LimitFPS(time)) return 1;
    if(SDLite_CalculateFPS(time)) return 1;

    return 0;
}
