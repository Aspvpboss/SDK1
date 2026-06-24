/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_TIME_H
#define SDLite_TIME_H


#ifdef __cplusplus
extern "C"{
#endif

#include "SDLite/common_libs.h"


/*

    SDLite_Time holds variable that are used for time calculations
    
    There should only be one SDLite_Time per thread. 
    You should only use the SDLite_Time in the thread it was created in

*/
typedef struct SDLite_Time SDLite_Time;


/*
    Creates and returns a SDLite_Time struct

    set the fps_limit to be less than 0.0f to uncap the fps
    fps_limit can be changed during runtime
    if fps is above several 1000s, it will become unstable and break animation timing

    Will fail if fps_limit == 0.0f or if malloc fails

    returns SDLite_Time* for success, returns NULL for failure
    call SDL_GetError() for more info
*/
SDLite_DLL SDLite_Time* SDLite_CreateTime(double fps_limit);

/*
    Frees a SDLite_Time

    Will return early if SDLite_Time is NULL
*/
SDLite_DLL void SDLite_DestroyTime(SDLite_Time *time);

/*
    Gets the fps of the SDLite_Time*

    Will fail if SDLite_Time* is NULL

    returns the fps for success, returns -1.0f for failure
*/
SDLite_DLL double SDLite_Time_GetFPS(const SDLite_Time *time);

/*
    Gets the delta time of the SDLite_Time*

    Will fail if SDLite_Time* is NULL

    returns the delta time for success, returns -1.0f for failure
*/
SDLite_DLL double SDLite_Time_GetDT(const SDLite_Time *time);


/*
    Returns either true or false if the fps value inside SDLite_Time* updated

    Will fail if SDLite_Time* is NULL

    returns a bool of the fps updated for success, returns false for failure
*/
SDLite_DLL bool SDLite_Time_Is_FPSUpdated(const SDLite_Time *time);


/*
    Gets the fps_limit of the SDLite_Time*

    Will fail if SDLite_Time* is NULL

    returns the fps_limit for success, returns 0.0f for failure
*/
SDLite_DLL double SDLite_Time_Get_FPSLimit(const SDLite_Time *time);

/*
    Sets the fps_limit of the SDLite_Time*

    Set the fps_limit below 0.0f to uncap the fps
    if fps is above several 1000s, it will become unstable and break animation timing
    
    Will fail if SDLite_Time* is NULL or if new_fps_limit == 0.0f

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Time_Set_FPSLimit(SDLite_Time *time, double new_fps_limit);


/*
    Calls the time.h functions in order of use

    This is for ease of programmers.

    You can call the individual functions seperately
    **
    **
    Functions Called:
    
    SDLite_CalculateDT(time);
    SDLite_LimitFPS(time);
    SDLite_CalculateFPS(time);  

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_TimeFunctions(SDLite_Time *time);


/*
    Updates 'dt' within SDLite_Time with current delta time

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_CalculateDT(SDLite_Time *time);

/*
    Updates 'fps' within SDLite_Time with current fps

    This functions uses dt_buffer to average the delta time
    over a defined amount of frame for a smoother fps.
    The amounts of frames it averages is SDLite_FPS_POLL_RATE

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_CalculateFPS(SDLite_Time *time);

/*
    This function limits the fps of the application. 

    It uses 'int fps_limit' within SDLite_Time as the fps limit.

    returns 0 for success, returns 1 for failure
    call SDL_GetError() for more info
*/
SDLite_DLL int SDLite_LimitFPS(SDLite_Time *time);

#ifdef __cplusplus
}
#endif


#endif
