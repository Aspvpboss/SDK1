#pragma once

#include "SDK1.h"
#define SDK_FPS_POLL_RATE 100
#define SDK_BUSY_WAIT_MARGIN 0.002

/*

SDK_Time holds variable that are used for time calculations

*/
typedef struct{

    double dt, fps;
    int fps_limit;
    double dt_buffer[SDK_FPS_POLL_RATE];

} SDK_Time;


int SDK_CreateTime(SDK_Time *time, int fps_limit);
void SDK_TimeFunctions(SDK_Time *time);

void SDK_CalculateDT(SDK_Time *time);
void SDK_CalculateFPS(SDK_Time *time);
void SDK_LimitFPS(SDK_Time *time);

