/*
 * Copyright (c) 2026 Benjamin Vaughan
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
*/

#ifndef SDLite_AUDIO_H
#define SDLite_AUDIO_H

// allows header to be C++ compatiable
#ifdef __cplusplus
extern "C"{
#endif

#include "SDLite/common_libs.h"

typedef struct{

    MIX_Track *track;
    SDL_PropertiesID track_prop;

} SDLite_Track;


/*
    These functions can be called from any thread
*/
typedef struct SDLite_Audio_Handler SDLite_Audio_Handler;

/*
    Creates an SDLite_Audio_Handler*

    SDLite_Audio_Handler owns all MIX_Tracks, MIX_Mixer, and SDLite_Tracks

    Use SDLite_Destroy_AudioHandler to free SDLite_Audio_Handler

    returns SDLite_Audio_Handler* for success, returns NULL for failure
*/
SDLite_DLL SDLite_Audio_Handler* SDLite_Create_AudioHandler(uint16_t track_capacity, float master_volume);


/*
    Frees an SDLite_Audio_Handler*

    Will return early if SDLite_Audio_Handler* is NULL
*/
SDLite_DLL void SDLite_Destroy_AudioHandler(SDLite_Audio_Handler *audio_handler);


/*
    Gets the specified SDLite_Track*, the SDLite_Audio_Handler still owns the SDLite_Track*  

    Use the SDLite_Track* cautiously.
    Do not free SDLite_Track. It is owned by SDLite_Audio_Handler*   
    
    returns SDLite_Track* for success, returns NULL for failure
*/
SDLite_DLL SDLite_Track* SDLite_Audio_GetTrack(SDLite_Audio_Handler *audio_handler, uint16_t audio_track);

/*
    Gets the MIX_Mixer*, the SDLite_Audio_Handler still owns the MIX_Mixer*. 
    Do not free the MIX_Mixer*

    Will fail if SDLite_Audio_Handler* is NULL

    returns MIX_Mixer* for success, returns NULL for failure
*/
SDLite_DLL MIX_Mixer* SDLite_Audio_GetMixer(SDLite_Audio_Handler *audio_handler);

    /*
    Plays the audio that has been loaded to the specified audio_track

    Function will fail if no audio has been loaded to the track

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_PlayTrack(SDLite_Audio_Handler *audio_handler, uint16_t audio_track);

/*
    Stops the audio that's playing on the specified audio_track

    Function will fail if no audio has been loaded to the track

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_StopTrack(SDLite_Audio_Handler *audio_handler, uint16_t audio_track, int64_t fade_out_frames);

/*
    Loads a MIX_Audio* to the specified audio_track

    To load a MIX_Audio* use MIX_LoadAudio()
    MIX_Audio* must be freed using MIX_DestroyAudio()

    Look at the SDL_Mixer documentation for more information

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_SetTrackAudio(SDLite_Audio_Handler *audio_handler, uint16_t audio_track, MIX_Audio *audio);


/*
    Sets the track volume for a specified track_volume, volume range between 0.0f - 1.0f

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_SetTrackVolume(SDLite_Audio_Handler *audio_handler, uint16_t audio_track, float track_volume);


/*
    Sets a value to a specified property in the specified audio_track 

    Look at the SDL documentation about SDL_PropertiesID for more info,
    Look at the SDL_Mixer properties for more info

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_SetTrackProp(SDLite_Audio_Handler *audio_handler, uint16_t audio_track, const char *prop_name, int64_t value);

/*
    Sets the master volume of all audio, volume range between 0.0f - 1.0f

    returns 0 for success, returns 1 for failure 
*/
SDLite_DLL int SDLite_Audio_SetMasterVolume(SDLite_Audio_Handler *audio_handler, float master_volume);

/*
    Gets the master volume and fills in the float* with it

    Will fail if either SDLite_Audio_Handler* or float* is NULL

    returns 0 for success, returns 1 for failure
*/
SDLite_DLL int SDLite_Audio_GetMasterVolume(SDLite_Audio_Handler *audio_handler, float *master_volume);



#ifdef __cplusplus
}
#endif


#endif
