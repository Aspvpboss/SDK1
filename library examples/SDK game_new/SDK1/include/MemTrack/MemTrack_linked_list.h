

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "MemTrack_export.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct Mem_Info{

    struct Mem_Info *next;
    size_t size;
    void *ptr;
    char *file_name;
    int file_line;

} Mem_Info;


typedef struct{

    void (*fail_handler)(void*);
    void *handler_arg;
    struct{
        bool memory_failure_abort;
        bool auto_null_pointers;
        bool print_error_info;
    } config;


} MemTrack_Context;


MemTrack_API size_t check_memory_usage();
MemTrack_API void print_tracking_info();
MemTrack_API void free_tracking_info();
MemTrack_API int check_memory_leak();
int append_allocation(void *ptr, char *file, int line, size_t size);
int delete_allocation(void *check_ptr);


#endif

