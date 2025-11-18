#ifndef EXPORT_H
#define EXPORT_H


#ifdef _WIN32
    #ifdef DLL_EXPORTS
        #define MemTrack_API __attribute__((dllexport))
    #elif defined(STATIC_LINK)
        #define MemTrack_API
    #else 
        #define MemTrack_API __declspec(dllimport)
    #endif
#else
    #define MemTrack_API
#endif


#endif