#include "time.h"


/*
Creates and returns a SDK_Time struct
SDK_Time doesn't need to be freed after use

**fps_limit can be changed during runtime*

You should call the time functions in this order

    SDK_LimitFPS(&time);
    SDK_CalculateDT(&time);
    SDK_CalculateFPS(&time);
*/
SDK_Time SDK_CreateTime(int fps_limit){
    SDK_Time time;

    time.fps_limit = fps_limit;
    time.dt = 0;
    time.fps = 0;
    time.failure = 0;

    if(fps_limit <= 0){
        time.failure = 1;
    }

    return time;
}



/*
Updates 'dt' within SDK_Time with current delta time


You should call the time functions in this order

    SDK_LimitFPS(&time);
    SDK_CalculateDT(&time);
    SDK_CalculateFPS(&time);

*/
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



/*
Updates 'fps' within SDK_Time with current fps

This functions uses dt_buffer to average the delta time
over a defined amount of frame for a smoother fps.
The amounts of frames to loop over is SDK_FPS_POLL_RATE


You should call the time functions in this order

    SDK_LimitFPS(&time);
    SDK_CalculateDT(&time);
    SDK_CalculateFPS(&time);
    

*/
void SDK_CalculateFPS(SDK_Time *time){
    static int frame = 0;

    if(frame < SDK_FPS_POLL_RATE){
        time->dt_buffer[frame] = time->dt;
        frame++;
        return;
    }

    double total = 0.0f;
    for(int i = 0; i < SDK_FPS_POLL_RATE; i++)
        total += time->dt_buffer[i];

    time->fps = 1 / (total / SDK_FPS_POLL_RATE);
    frame = 0;
    printf("\r%f                ", time->fps);

    return;
}



/*
This function limits the fps of the application. 

It uses 'int fps_limit' within SDK_Time as the fps limit.


You should call the time functions in this order

    SDK_LimitFPS(&time);
    SDK_CalculateDT(&time);
    SDK_CalculateFPS(&time);
*/
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

