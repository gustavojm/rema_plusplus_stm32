#pragma once

#include "FreeRTOS.h"
#include "bresenham.h"
//#include "encoders_pico.h"
#include "gpio_templ.h"
#include "task.h"
#include "xy_axes.h"
#include "z_axis.h"

#define WATCHDOG_TIME_MS 1000

#define TOUCH_PROBE_INTERRUPT_PRIORITY                                                                                    \
    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1) // Has to have higher priority than timers ( now +2 )

inline gpio_pinint touch_probe_irq_pin = {GPIOA, GPIO_PIN_0, EXTI1_IRQn};   //

constexpr int ENABLED_INPUTS_MASK = 0b0011'1111;

class rema {
  public:
    static const int BRAKES_RELEASE_DELAY_MS = 200;
    enum class brakes_mode_t { OFF, AUTO, ON };

    static void init_input_outputs();

    static void control_enabled_set(bool status);

    static bool control_enabled_get();

    static void brakes_release();

    static void brakes_apply();

    static void touch_probe_extend();

    static void touch_probe_retract();

    static bool is_touch_probe_touching();

    static void update_watchdog_timer();

    static bool is_watchdog_expired();

    static void hard_limits_reached();

    static bool control_enabled;
    static bool stall_control;
    static bool touch_probe_protection;
    static brakes_mode_t brakes_mode;
    static TickType_t lastKeepAliveTicks;
    static TickType_t touch_probe_debounce_time_ms;
};
