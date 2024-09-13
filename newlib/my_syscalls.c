/* Includes */
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

#include "FreeRTOS.h"

/* Defining malloc/free should overwrite the standard versions provided by the compiler. */

void *malloc(size_t size) {
    /* Call the FreeRTOS version of malloc. */
    return pvPortMalloc(size);
}

void free(void *ptr) {
    /* Call the FreeRTOS version of free. */
    vPortFree(ptr);
}