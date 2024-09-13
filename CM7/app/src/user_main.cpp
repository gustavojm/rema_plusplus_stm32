#include <chrono>
#include <cstdint>
#include <signal.h>
#include <stdio.h>

#include "board.h"
#include "FreeRTOS.h"
#include "task.h"

/* LWIP and ENET phy */
// #include "arch/lpc18xx_43xx_emac.h"
// #include "arch/lpc_arch.h"
// #include "arch/sys_arch.h"
// #include "lpc_phy.h" /* For the PHY monitor support */

#include "../inc/debug.h"
#include "encoders_pico.h"
#include "lwip/ip_addr.h"
//#include "lwip_init.h"
#include "mem_check.h"
#include "mot_pap.h"
#include "rema.h"
#include "settings.h"
//#include "temperature_ds18b20.h"
#include "xy_axes.h"
#include "z_axis.h"

/* GPa 201117 1850 Iss2: agregado de Heap_4.c*/
uint8_t __attribute__((section("."
                               "data"
                               ".$"
                               "RamAHB32_48_64"))) ucHeap[configTOTAL_HEAP_SIZE];

/* Sets up system hardware */
static void prvSetupHardware(void) {
    SystemCoreClockUpdate();

    // Without the following command the use of DWT makes debugging impossible
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // Enable Cycle Counter, used to create precision delays in wait.c
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief    MilliSecond delay function based on FreeRTOS
 * @param    ms    : Number of milliSeconds to delay
 * @returns    nothing
 * Needed for some functions, do not use prior to FreeRTOS running
 */
void msDelay(uint32_t ms) {
    vTaskDelay((configTICK_RATE_HZ * ms) / 1000);
}

/**
 * @brief    main routine for example_lwip_tcpecho_freertos_18xx43xx
 * @returns    function should not exit
 */
extern "C" int user_main(void) {
    debugInit();
    debugLocalSetLevel(true, Info);
    debugNetSetLevel(true, Info);

    //prvSetupHardware();

    printf("    --- NASA GSPC ---\n");
    printf("REMA Remote Terminal Unit.\n");

    settings::init();

    rema::init_input_outputs();
    xy_axes_init();
    //z_axis_init();
    encoders_pico_init();

    //temperature_ds18b20_init();
    // mem_check_init();

    //network_init();
    return 1;
}

#if (configCHECK_FOR_STACK_OVERFLOW > 0)
extern "C" void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName) {
    volatile signed char *name;
    volatile xTaskHandle *pxT;

    name = pcTaskName;
    pxT = pxTask;

    (void)name;
    (void)pxT;

    while (1) {
    }
}
#endif

/*-----------------------------------------------------------*/
/**
 * @brief     configASSERT callback function
 * @param     ulLine        : line where configASSERT was called
 * @param     pcFileName    : file where configASSERT was called
 */
void vAssertCalled(uint32_t ulLine, const char *const pcFileName) {
    volatile uint32_t ulSetToNonZeroInDebuggerToContinue = 0;

    taskENTER_CRITICAL();
    {
        printf("[ASSERT] %s:%lu\n", pcFileName, ulLine);
        /* You can step out of this function to debug the assertion by using
         the debugger to set ulSetToNonZeroInDebuggerToContinue to a non-zero
         value. */
        while (ulSetToNonZeroInDebuggerToContinue == 0) {
        }
    }
    taskEXIT_CRITICAL();
}
