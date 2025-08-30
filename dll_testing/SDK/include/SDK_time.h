#pragma once

#include "SDK1.h"
#define SDK_FPS_POLL_RATE 200

/*

SDK_Time holds variable that are used for time calculations
You use dt and fps for functions

fps_updated becomes true whenever the fps gets updated
becomes false after the update

*/
typedef struct{

    double dt, fps;
    int fps_limit;
    double dt_buffer[SDK_FPS_POLL_RATE];
    bool fps_updated;

} SDK_Time;


SDK1_API int SDK_CreateTime(SDK_Time *time, int fps_limit);
SDK1_API void SDK_TimeFunctions(SDK_Time *time);

SDK1_API void SDK_CalculateDT(SDK_Time *time);
SDK1_API void SDK_CalculateFPS(SDK_Time *time);
SDK1_API void SDK_LimitFPS(SDK_Time *time);

