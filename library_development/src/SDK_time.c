#include "SDK_time.h"


#define MAX_SAMPLES 100


SDK_Time* SDK_CreateTime(int fps_limit){

    SDK_Time *time = t_malloc(sizeof(SDK_Time));
    time->fps_limit = fps_limit;
    time->prev_fps_limit = fps_limit;
    time->dt = 0;
    time->fps = 0;

    if(fps_limit <= 0){
        t_free(time);
        return NULL;
    }


    return time;
}

void SDK_DestroyTime(SDK_Time *time){

    t_free(time);

}


void SDK_CalculateDT(SDK_Time *time){

    static uint64_t previous = 0;
    static uint64_t frequency = 0;

    if (frequency == 0) {
        frequency = SDL_GetPerformanceFrequency();
        previous = SDL_GetPerformanceCounter();
        time->dt = 0.0f;
        return;
    }

    uint64_t current = SDL_GetPerformanceCounter();
    time->dt = (double)(current - previous) / (double)frequency;
    previous = current;

}


void SDK_CalculateFPS(SDK_Time *time){

    static uint64_t update_count = 0;
    static uint16_t frame = 0;
    static uint16_t collected_frames = 0;
    static double total = 0.0;
    static double dt_buffer[MAX_SAMPLES] = {0};

    if(time->fps_updated == 1){
        time->fps_updated = 0;
    }

    total -= dt_buffer[frame];
    dt_buffer[frame] = time->dt;
    total += time->dt;
    
    if(collected_frames < MAX_SAMPLES) collected_frames++;

    frame = (frame + 1) % MAX_SAMPLES;
    time->fps = 1 / (total / collected_frames);
    update_count++;

    if(update_count > time->fps_limit){
        time->fps_updated = 1;
        update_count = 0;
    }
        
}


void SDK_LimitFPS(SDK_Time *time){

    static uint64_t last_counter = 0;
    static uint64_t freq = 0;

    if (freq == 0) {
        freq = SDL_GetPerformanceFrequency();
        last_counter = SDL_GetPerformanceCounter();
        return;
    }

    double target_frame_time = (1.0 / time->fps_limit);

    uint64_t now_counter = SDL_GetPerformanceCounter();
    double elapsed = (double)(now_counter - last_counter) / (double)freq;


    double remaining = target_frame_time - elapsed;
    if(remaining < 0){
        last_counter = SDL_GetPerformanceCounter();
        return;
    }


    if (remaining > 0.002) {
        SDL_Delay((Uint32)((remaining - 0.001) * 1000.0));
    }

    do {
        now_counter = SDL_GetPerformanceCounter();
        elapsed = (double)(now_counter - last_counter) / (double)freq;
    } while (elapsed < target_frame_time);



    last_counter = SDL_GetPerformanceCounter();
}


void SDK_TimeFunctions(SDK_Time *time){
    SDK_CalculateDT(time);
    SDK_LimitFPS(time);
    SDK_CalculateFPS(time);
}