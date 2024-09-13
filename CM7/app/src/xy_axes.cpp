#include <cstdint>
#include <new>

#include "FreeRTOS.h"
#include "bresenham.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
#include "xy_axes.h"

#include "../inc/debug.h"
#include "gpio.h"
#include "tmr.h"

/**
 * @brief   initializes the stepper motors for bresenham control
 * @returns	nothing
 */
bresenham &xy_axes_init() {
    static mot_pap x_axis(
        'X',
        25000, // motor resolution
        500,   // encoder resolution
        10     // turns_per_inch
    );
    x_axis.gpios.step = gpio_base{ GPIOB, 1 };           // 

    static mot_pap y_axis(
        'Y',
        25000, // motor resolution
        500,   // encoder resolution
        10     // turns_per_inch
    );
    y_axis.gpios.step = gpio_base{ GPIOB, 2 };           //

    static tmr xy_axes_tmr = tmr(); //(LPC_TIMER0, RGU_TIMER0_RST, CLK_MX_TIMER0, TIMER0_IRQn);
    alignas(bresenham) static char xy_axes_buf[sizeof(bresenham)];

    x_y_axes = new (xy_axes_buf) bresenham("xy_axes", &x_axis, &y_axis, xy_axes_tmr, true);
    x_y_axes->kp = {
        100,                 //!< Kp
        x_y_axes->step_time, //!< Update rate (ms)
        10000,               //!< Min output
        60000                //!< Max output
    };

    return *x_y_axes;
}

/**
 * @brief   handle interrupt from 32-bit timer to generate pulses for the
 * stepper motor drivers
 * @returns nothing
 * @note    calls the supervisor task every x number of generated steps
 */
extern "C" void TIMER0_IRQHandler(void) {
    if (x_y_axes->tmr.match_pending()) {
        x_y_axes->isr();
    }
}
