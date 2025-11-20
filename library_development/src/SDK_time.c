#include "SDK_time.h"


#define MAX_SAMPLES 100


typedef struct{

    uint64_t previous_counter;
    uint64_t counter_frequency;
    uint64_t update_count;
    uint16_t frame;
    uint16_t collected_frames;
    double total;
    double dt_buffer[MAX_SAMPLES];

} Time_Data;


SDK_Time* SDK_CreateTime(int fps_limit){

    if(fps_limit <= 0) return NULL;

    SDK_Time *time = t_malloc(sizeof(SDK_Time));
    time->data = t_malloc(sizeof(Time_Data));
    if(!time->data){
        t_free(time);
        return NULL;
    }
    Time_Data *data = (Time_Data*)time->data;

    data->collected_frames = 0;
    data->frame = 0;
    data->total = 0.0f;
    data->update_count = 0;
    data->previous_counter = 0;
    data->counter_frequency = 0;

    memset(data->dt_buffer, 0, sizeof(data->dt_buffer));

    time->fps_limit = fps_limit;
    time->dt = 0;
    time->fps = 0;
    time->fps_updated = false;



    return time;
}

void SDK_DestroyTime(SDK_Time *time){

    if(!time) return;

    t_free(time->data);

    t_free(time);

}


int SDK_CalculateDT(SDK_Time *time){

    if(!time) return 1;

    Time_Data *data = (Time_Data*)time->data;

    if(data->counter_frequency == 0){
        data->counter_frequency = SDL_GetPerformanceFrequency();
        data->previous_counter = SDL_GetPerformanceCounter();
        time->dt = 0.0f;
        return 0;
    }
    

    uint64_t current = SDL_GetPerformanceCounter();
    time->dt = (double)(current - data->previous_counter) / (double)data->counter_frequency;
    data->previous_counter = current;

    return 0;
}


int SDK_CalculateFPS(SDK_Time *time){

    if(!time) return 1;
    Time_Data *data = (Time_Data*)time->data;

    if(time->fps_updated == 1){
        time->fps_updated = 0;
    }

    double *dt_buffer = data->dt_buffer;

    data->total -= dt_buffer[data->frame];
    dt_buffer[data->frame] = time->dt;
    data->total += time->dt;
    
    if(data->collected_frames < MAX_SAMPLES) data->collected_frames++;

    data->frame = (data->frame + 1) % MAX_SAMPLES;
    time->fps = 1 / (data->total / data->collected_frames);
    data->update_count++;

    if(data->update_count > time->fps_limit){
        time->fps_updated = 1;
        data->update_count = 0;
    }
        
    return 0;
}


int SDK_LimitFPS(SDK_Time *time){

    if(!time) return 1;
    Time_Data *data = (Time_Data*)time->data;



    uint64_t counter_frequency = data->counter_frequency;
    uint64_t current_counter = SDL_GetPerformanceCounter();
    uint64_t previous_counter = data->previous_counter;
    double delta_time = (double)(current_counter - previous_counter) / (double)counter_frequency;
    double target_delta_time = (1.0 / time->fps_limit); 
    


    double remaining = target_delta_time - delta_time;
    if(remaining < 0){
        return 0;
    }


    if(remaining > 0.002){
        Uint32 ms = (Uint32)((remaining - 0.001) * 1000.0);
        if (ms > 0) SDL_Delay(ms);
    }

    do{
        current_counter = SDL_GetPerformanceCounter();
        delta_time = (double)(current_counter - previous_counter) / (double)counter_frequency;
    } while(delta_time < target_delta_time);

    data->previous_counter = current_counter;

    time->dt = delta_time;

    return 0;
}


int SDK_TimeFunctions(SDK_Time *time){
    if(SDK_CalculateDT(time)) return 1;
    if(SDK_LimitFPS(time)) return 1;
    if(SDK_CalculateFPS(time)) return 1;

    return 0;
}