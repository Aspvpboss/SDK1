#ifndef MEMTRACK_H
#define MEMTRACK_H

#include "MemTrack_export.h"
#include "MemTrack_linked_list.h"
#include <string.h>
#include <stdlib.h>


//if you don't call this, then no functions will be called if malloc returns NULL
MemTrack_API void Set_Malloc_Error_Function(void(*function)(void*), void *function_arg);

//you must call this *before* you set the values within MemTrack_Context
MemTrack_API void Set_MemTrack_Context(MemTrack_Context *e_ctx);

MemTrack_API void safe_free(void **mem);
MemTrack_API void* safe_malloc(size_t size);
MemTrack_API void* safe_realloc(void *memory, size_t size);
MemTrack_API char* safe_strdup(const char *src);

MemTrack_API void debug_free(void **mem, char *file, int line);
MemTrack_API void* debug_malloc(size_t size, char *file, int line);
MemTrack_API void* debug_realloc(void *mem, size_t size, char *file, int line);
MemTrack_API char* debug_strdup(const char* src, char *file, int line);



#ifdef TRACK_ALLOCATIONS

    //void *t_malloc(size_t size);
    #define t_malloc(size) debug_malloc(size, __FILE__, __LINE__)

    //void *t_realloc(void *ptr, size_t size);
    #define t_realloc(ptr, size) debug_realloc(ptr, size, __FILE__, __LINE__)

    /*
    void t_free(void **mem);
    */
    #define t_free(ptr) debug_free((void**)&ptr, __FILE__, __LINE__)

    //char *t_strdup(char *str);
    #define t_strdup(str) debug_strdup(str, __FILE__, __LINE__)
 
#elif defined(STDLIB_ALLOCATIONS)
 
    //void *t_malloc(size_t size);
    #define t_malloc(size) malloc(size)

    //void *t_realloc(void *ptr, size_t size);
    #define t_realloc(ptr, size) realloc(ptr, size)

    /*
    void free(void *mem);
    */
    #define t_free(ptr) free(ptr)

    //char *t_strdup(char *str);
    #define t_strdup(str) strdup(str)

#else

    //void *t_malloc(size_t size);
    #define t_malloc(size) safe_malloc(size)

    //void *t_realloc(void *mem, size_t size);
    #define t_realloc(ptr, size) safe_realloc(ptr, size)

    /*
    void t_free(void **mem);
    auto NULL's pointer
    */
    #define t_free(ptr) safe_free((void**)&ptr)

    //char *t_strdup(char *str);
    #define t_strdup(str)  safe_strdup(str)


#endif



#endif