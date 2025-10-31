#include "SDK_time.h"



int SDK_CreateTime(SDK_Time *time, int fps_limit){

    time->fps_limit = fps_limit;
    time->prev_fps_limit = fps_limit;
    time->dt = 0;
    time->fps = 0;

    if(fps_limit <= 0){
        return 1;
    }

    time->dt_buffer = t_malloc(sizeof(double) * fps_limit);

    return 0;
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

    static int frame = 0;

    if(time->fps_updated == 1){
        time->fps_updated = 0;
    }

    if(time->fps_limit != time->prev_fps_limit){
        time->dt_buffer = t_realloc(time->dt_buffer, sizeof(double) * time->fps_limit);
        time->prev_fps_limit = time->fps_limit;
        frame = 0;
        return;
    }

    time->prev_fps_limit = time->fps_limit;


    if(frame < time->fps_limit){

        time->dt_buffer[frame] = time->dt;
        frame++;
        return;

    }


    double total = 0.0;
    for(int i = 0; i < time->fps_limit; i++)
        total += time->dt_buffer[i];

    if(total <= 0){
        time->fps = 0.0;
    } else{
        time->fps = 1.0 / (total / time->fps_limit);
    }

    frame = 0;

    time->fps_updated = 1;

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
    if (remaining < 0){
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