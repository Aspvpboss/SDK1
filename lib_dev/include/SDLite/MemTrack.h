/* 
    Copyright (c) 2026 Benjamin Vaughan

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

/*

### MemTrack v1.2

# Documentation

This library tracks allocations and can report memory leaks; furthermore, it can also
get heap usage and automatically null pointers after freeing them and exiting the program if malloc fails.

This library does support multi-threading, read the function docs for more info

I wrote this library in a way to configure it as you want. If you just want to track allocations when debugging, then only use the normal malloc and free during runtime you can do that. Or if you want it to null pointers when freed during runtime and check for malloc failure during runtime, in exchange for a very small performance hit.

#### when compiling use the these macros to configure the library. I use gcc so I use -Dmacro_name to define a global macro when compiling

### Compiler Macros 
- #define STDLIB_ALLOCATIONS - this uses stdlib malloc and free 

- #define TRACK_ALLOCATIONS - this uses my tracking malloc and free functions 

- #define NDEBUG - this will disable printf logging

- NO MACRO defined - this doesn't track allocations, however it still uses the safe malloc and free functions which allows for auto nulling pointers and exiting if malloc failure



####  There are macros that you can configure memtrack to use your own functions instead of the default ones it uses

### Function Macros
- #define TRACK_PRINTF(fmt, ...) printf(fmt, ##__VA_ARGS__)
- #define TRACK_MALLOC(size) malloc(size)
- #define TRACK_REALLOC(mem, newsize) realloc(mem, newsize)
- #define TRACK_FREE(ptr) free(ptr)
- #define TRACK_STRLEN(str) strlen(str)
- #define TRACK_STRCPY(dst, src) strcpy(dst, src)
- #define TRACK_STRDUP(str) strdup(str)
- #define TRACK_EXIT exit(EXIT_FAILURE)
- #define TRACK_MUTEX_TYPE pthread_mutex_t 
- #define TRACK_MUTEX_CREATE(mutex) pthread_mutex_init(&mutex, NULL)
- #define TRACK_MUTEX_DESTROY(mutex) pthread_mutex_destroy(&mutex)
- #define TRACK_MUTEX_LOCK(mutex) pthread_mutex_lock(mutex)
- #define TRACK_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex)

# Initializing

First, you must define the MEMTRACK_IMPLEMENTATION macro to paste the functions in, then include the memtrack header. You only need to define the MEMTRACK_IMPLEMENTATION once in one C file

    #define MEMTRACK_IMPLEMENTATION 
    #include "memtrack.h"

Secondly, in the main function, you need to call MemTrack_Init(); and use your desired configs

    MemTrack_Init(NULL, NULL, false, false);

If you are using the memory_failure_abort config, the malloc failure function you pass into the init function will run with the void* you pass into init if malloc fails

Importantly, if you're using the macro STDLIB_ALLOCATIONS, the auto_null_pointers and memory_failure_abort bools will do nothing

# Using MemTrack

Here are the main functions and macros this library provides, most of these functions support multi-threading 

## Functions


MemTrack_Init and MemTrack_Quit are the only functions that should only be called on the main thread

    int MemTrack_Init(void(*malloc_fail_handler)(void*), void *handler_arg, bool auto_null_pointers, bool memory_failure_abort);     
    // returns 1 if failure or if called more than once

    void MemTrack_Quit(); // call this after all other threads are cleaned up


    size_t check_memory_usage(); // returns size_t of the amount of bytes used in heap
    int check_memory_leak(); // returns 1 if there are tracked allocations, returns 0 if there aren't tracked allocations
    void print_tracking_info(); // prints all tracking information
    int MemTrack_GetVersion(int *major, int *minor); // gets the version of memtrack, returns 1 if failure


## Macros

These macro definitions change depending on what compiler macro you define, but these are the generic args you give them. All of these macros support multi-threading

    void* t_malloc(size_t size);

    void* t_realloc(void *mem, size_t size);
    
    void t_free(void *mem); 

    char* t_strdup(const char *string);


# Example Program

```c
#define MEMTRACK_IMPLEMENTATION
#include "memtrack.h"
#include <pthread.h>

void malloc_failure(void *data){
    printf("\ndub\n");
}


void* thread_func(void *arg){
    return t_malloc(100);
}



int main(void){

    MemTrack_Init(malloc_failure, NULL, true, true);

    pthread_t thread;

    if(pthread_create(&thread, NULL, thread_func, NULL)){
        return 1;
    } 

    int *array = t_malloc(999999);

    if(!array)
        printf("array is null\n");


    t_free(array);

    if(!array){

        printf("is null after free\n");

    } else{

        printf("isn't null after free\n");

    }
   
    

    void *result = NULL;
    pthread_join(thread, &result);

    if(check_memory_leak())
        print_tracking_info();
    
    MemTrack_Quit();

    return 0;
}
```

output of program

```
is null after free

Allocation Information
size 100 - Line 13 - File main.c
```



*/

#ifndef MEMTRACK_MEMTRACK_H
#define MEMTRACK_MEMTRACK_H 


#ifdef __cplusplus 
extern "C"{
#endif

#include <stdlib.h>
#include <stdbool.h>
#include "SDL3/SDL_thread.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_mutex.h"

// uncomment this for use in DLLs
#define MEMTRACK_DLL

#if defined(MEMTRACK_DLL)

    #if defined(_WIN32)
        #if defined(MEMTRACK_BUILD_DLL)
            #define MEMTRACK_API __declspec(dllexport)
        #else
            #define MEMTRACK_API __declspec(dllimport)
        #endif
    #else
        #define MEMTRACK_API __attribute__((visibility("default")))
    #endif

#else
    #define MEMTRACK_API
#endif



// changes these macros to use what functions you want, be careful

#ifndef NDEBUG
    #define TRACK_PRINTF(fmt, ...) SDL_Log(fmt, ##__VA_ARGS__)
#else 
    #define TRACK_PRINTF(fmt, ...)
#endif


#define TRACK_MALLOC(size) SDL_malloc(size)
#define TRACK_REALLOC(mem, newsize) SDL_realloc(mem, newsize)
#define TRACK_FREE(ptr) SDL_free(ptr)
#define TRACK_STRLEN(str) SDL_strlen(str)
#define TRACK_STRLCPY(dst, src, size) SDL_strlcpy(dst, src, size)
#define TRACK_STRDUP(str) SDL_strdup(str)
#define TRACK_EXIT exit(EXIT_FAILURE)

#define TRACK_MUTEX_TYPE SDL_Mutex*
#define TRACK_MUTEX_CREATE(mutex) SDL_CreateMutex() // you may have to change this if your mutex create function doesn't take the mutex as an arg
#define TRACK_MUTEX_DESTROY(mutex) SDL_DestroyMutex(mutex)
#define TRACK_MUTEX_LOCK(mutex) SDL_LockMutex(mutex)
#define TRACK_MUTEX_UNLOCK(mutex) SDL_UnlockMutex(mutex)

typedef struct Mem_Info{

    struct Mem_Info *next;
    size_t size;
    void *ptr;
    char *file_name;
    int file_line;

} Mem_Info;



MEMTRACK_API size_t check_memory_usage();
MEMTRACK_API void print_tracking_info();
MEMTRACK_API int check_memory_leak();

// init and quit should only be called on main thread
MEMTRACK_API void MemTrack_Quit();
MEMTRACK_API int MemTrack_Init(void(*malloc_fail_handler)(void*), void *handler_arg, bool auto_null_pointers, bool memory_failure_abort);
MEMTRACK_API int MemTrack_GetVersion(int *major, int *minor);

MEMTRACK_API void safe_free(void **mem);
MEMTRACK_API void* safe_malloc(size_t size);
MEMTRACK_API void* safe_realloc(void *memory, size_t size);
MEMTRACK_API char* safe_strdup(const char *src);

MEMTRACK_API void debug_free(void **mem, const char *file, int line);
MEMTRACK_API void* debug_malloc(size_t size, const char *file, int line);
MEMTRACK_API void* debug_realloc(void *mem, size_t size, const char *file, int line);
MEMTRACK_API char* debug_strdup(const char* src, const char *file, int line);



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




#ifdef MEMTRACK_IMPLEMENTATION

//linked_list.c

typedef struct{

    Mem_Info *head;
    Mem_Info *tail;
    void (*fail_handler)(void*);
    void *handler_arg;
    bool memory_failure_abort;
    bool auto_null_pointers;
    bool init;
    TRACK_MUTEX_TYPE mutex;

} Track_Info;

static Track_Info info = {0};


int MemTrack_GetVersion(int *major, int *minor){

    if(!major || !minor)
        return 1;

    *major = 1;
    *minor = 2;

    return 0;
}


int MemTrack_Init(void(*malloc_fail_handler)(void*), void *handler_arg, bool auto_null_pointers, bool memory_failure_abort){

    if(info.init){
        TRACK_PRINTF("Memtrack already initialized\n");
        return 1;
    }

    info.mutex = TRACK_MUTEX_CREATE(info.mutex);
    if(!info.mutex){
        TRACK_PRINTF("Memtrack failed to create mutex\n");
        return 1;
    }

    info.head = NULL;
    info.tail = NULL;

    info.auto_null_pointers = auto_null_pointers;
    info.memory_failure_abort = memory_failure_abort;
    info.init = true;

    info.fail_handler = malloc_fail_handler;
    info.handler_arg = handler_arg;

    return 0;
}




void MemTrack_Quit(){

    Mem_Info *current = info.head;
    Mem_Info *next = NULL;

    if(!current) return;

    while(current){
        next = current->next;
        TRACK_FREE(current->file_name);
        TRACK_FREE(current);
        current = next;
    }

    TRACK_MUTEX_DESTROY(info.mutex);

    info.head = NULL;
    info.tail = NULL;
    info.init = false;
}



size_t check_memory_usage(){

    TRACK_MUTEX_LOCK(info.mutex);

    Mem_Info *current = info.head;
    size_t total = 0;

    while(current){
        total += current->size;
        current = current->next;
    }

    TRACK_MUTEX_UNLOCK(info.mutex);
    
    return total;
}


int check_memory_leak(){

    TRACK_MUTEX_LOCK(info.mutex);
    
    if(info.head || info.tail){
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 1;
    }

    TRACK_MUTEX_UNLOCK(info.mutex);

    return 0;
}



void print_tracking_info(){

    TRACK_MUTEX_LOCK(info.mutex);
    
    Mem_Info *current = info.head;

    if(!current){
        TRACK_MUTEX_UNLOCK(info.mutex);
        return;
    }

    TRACK_PRINTF("\nAllocation Information\n");
    while(current){
        TRACK_PRINTF("size %lld - Line %d - File %s\n", current->size, current->file_line, current->file_name);
        current = current->next;
    }
    TRACK_PRINTF("\n"); 

    TRACK_MUTEX_UNLOCK(info.mutex);

}


int append_allocation(void *ptr, const char *file, int line, size_t size){

    TRACK_MUTEX_LOCK(info.mutex);

    Mem_Info *node = (Mem_Info *)TRACK_MALLOC(sizeof(Mem_Info));
    if(!node){
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 1;
    }
    node->size = size;
    node->ptr = ptr;
    node->file_name = TRACK_STRDUP(file);
    if(!node->file_name){
        TRACK_FREE(node);
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 1;
    }
    node->file_line = line;

    if(info.tail){

        info.tail->next = node;
        info.tail = node;
        info.tail->next = NULL;
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 0;
    }

    if(!info.head){

        info.head = node;
        info.head->next = NULL;
        info.tail = info.head;
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 0;
    }

    TRACK_MUTEX_UNLOCK(info.mutex);
    
    return 1;
}


int delete_allocation(void *check_ptr){
    
    TRACK_MUTEX_LOCK(info.mutex);
    
    Mem_Info *current = info.head;
    Mem_Info *prev = NULL;

    while(current && current->ptr != check_ptr){

        prev = current;
        current = current->next;

    }

    if(!current){
        TRACK_MUTEX_UNLOCK(info.mutex);
        return 1;
    }

    if(current->next && prev){ // not head, not tail

        prev->next = current->next;
    
    } else if(current->next && !prev){ // head, not tail

        info.head = current->next;

    } else if(!current->next && prev){ // not head, tail

        prev->next = NULL;
        info.tail = prev;

    } else{ // one node

        info.head = NULL;
        info.tail = NULL;

    }
    
    TRACK_FREE(current->file_name);
    TRACK_FREE(current);
    
    TRACK_MUTEX_UNLOCK(info.mutex);

    return 0;
}



//alloc.c





void check_malloc_error(void *mem){

    if(mem || !info.init)
        return;

    if(info.fail_handler)
        (*info.fail_handler)(info.handler_arg);

    TRACK_PRINTF("MemTrack ERROR: malloc failed\n");

    if(info.memory_failure_abort)
        TRACK_EXIT;
    
    return; 
}

void debug_check_malloc_error(void *mem, const char *file, int line){

    if(mem || !info.init)
        return;

    if(info.fail_handler)
        (*info.fail_handler)(info.handler_arg);

    TRACK_PRINTF("MemTrack ERROR: malloc failed for file %s, line - %d\n", file, line);
    
    if(info.memory_failure_abort)
        TRACK_EXIT;
    
    return; 
}


char* safe_strdup(const char *src){
    char *new_mem = TRACK_STRDUP(src);
    check_malloc_error(new_mem);
    return new_mem;
}

void* safe_realloc(void *memory, size_t size){
    void *new_mem = TRACK_REALLOC(memory, size);
    check_malloc_error(new_mem);
    return new_mem;
}

void* safe_malloc(size_t size){
    void *new_mem = TRACK_MALLOC(size);
    check_malloc_error(new_mem);
    return new_mem;
}


void safe_free(void **mem){

    if(!mem || !(*mem))
        return;

    TRACK_FREE(*mem);

    if(info.auto_null_pointers)
        *mem = NULL;

}

void debug_free(void **mem, const char *file, int line){

    if(!mem || !(*mem))
        return;

    if(delete_allocation(*mem)){

        TRACK_PRINTF("MemTrack ERROR: failed to free old tracking info for file %s, line - %d\n", file, line);

        return;
    }
    TRACK_FREE(*mem);

    if(info.auto_null_pointers)
        *mem = NULL;
    
}


void* debug_malloc(size_t size, const char *file, int line){

    void *mem = TRACK_MALLOC(size);

    debug_check_malloc_error(mem, file, line);
    if(!mem)
        return NULL;
    

    if(append_allocation(mem, file, line, size)){
        TRACK_FREE(mem);

        TRACK_PRINTF("MemTrack ERROR: failed to malloc tracking info for file %s, line - %d\n", file, line);

        return NULL;    
    }

    return mem;
}


void* debug_realloc(void *mem, size_t size, const char *file, int line){

    if(!mem){
        void *new_mem = debug_malloc(size, file, line);
        return new_mem;
    }
        

    if(delete_allocation(mem)){

        TRACK_PRINTF("MemTrack ERROR: failed to free old tracking info for file %s, line - %d\n", file, line);

        return NULL;
    }
    
    void *new_mem = TRACK_REALLOC(mem, size);
    debug_check_malloc_error(new_mem, file, line);

    if(!new_mem)
        return NULL;
    

    if(append_allocation(new_mem, file, line, size)){
        TRACK_FREE(new_mem);

        TRACK_PRINTF("MemTrack ERROR: failed to malloc tracking info for file %s, line - %d\n", file, line);

        return NULL;            
    }


    return new_mem;
}

char* debug_strdup(const char* src, const char *file, int line){

    if(!src)
        return NULL;

    size_t src_len = TRACK_STRLEN(src);

    char *dup = (char *)debug_malloc(sizeof(char) * (src_len + 1), file, line);
    if(!dup)
        return NULL;

    TRACK_STRLCPY(dup, src, src_len + 1);
    dup[src_len] = '\0';

    return dup;
}

#endif


#ifdef __cplusplus 
}
#endif

#endif
