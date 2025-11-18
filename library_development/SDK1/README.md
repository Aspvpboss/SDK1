MemTrack is a library that tracks all heap memory allocations.

It helps track and fix memory leaks involved with your program.
For each allocation it tracks: size, file, and file line


-DTRACK_ALLOCATIONS


use -DTRACK_ALLOCATIONS when compiling to enable tracking, otherwise it use the normal malloc, realloc, strdup. However it will use a custom free function. All it does is automatically NULL your free pointer


notable functions

    void *t_malloc(size_t size);
        returns void pointer to allocated memory, returns NULL for error

    void *t_realloc(void *ptr, size_t size);
        returns void pointer to allocated memory, returns NULL for error
        
    char *t_strdup(char *str);
        returns char pointer to string, returns NULL for error

    void t_free(void **mem);
        frees memory, automatically NULL's the pointer

    size_t check_memory_usage();
        returns size_t for amount of heap memory usage

    void print_tracking_info();
        prints info about all allocations

    void free_tracking_info();
        frees all tracking information. If there is no memory leak this function call is unnessary, 
        but it should be called incase there is a memory leak
    
    int check_memory_leak();
        returns 1 for memory leak, returns 0 for no memory leak

example program
```

#define TRACK_ALLOCATIONS

#include "MemTrack.h"
#include <stdio.h>


int main(void){

    int *array = t_malloc(sizeof(int) * 10);

    array[2] = 1;


    if(check_memory_leak())
        print_tracking_info();

    t_free(&array);

    free_tracking_info();

    return 0;
}

```

example console output
```


Allocation Information
Address 000002c2145a13c0 - size 40 - Line 9 - File lib/src/main.c


```