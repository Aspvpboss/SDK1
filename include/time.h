#pragma once

#include "SDK1.h"
#define SDK_FPS_POLL_RATE 100
#define SDK_BUSY_WAIT_MARGIN 0.002


typedef struct{

    double dt, fps;
    int fps_limit;
    double dt_buffer[SDK_FPS_POLL_RATE];
    bool failure;

} SDK_Time;


SDK_Time SDK_CreateTime(int fps_limit);
void SDK_CalculateDT(SDK_Time *time);
void SDK_CalculateFPS(SDK_Time *time);
void SDK_LimitFPS(SDK_Time *time);

