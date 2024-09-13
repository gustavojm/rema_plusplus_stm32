#include "rema.h"
#include "gpio.h"

gpio_templ<GPIOA_BASE, GPIO_PIN_0> brakes_out;               // 
gpio_templ<GPIOA_BASE, GPIO_PIN_1> touch_probe_actuator_out; // 
gpio_templ<GPIOA_BASE, GPIO_PIN_2> relay_DOUT2;              // 
gpio_templ<GPIOA_BASE, GPIO_PIN_3> relay_DOUT3;              // 
gpio_templ<GPIOA_BASE, GPIO_PIN_4> shut_down_out;            // 

bool rema::control_enabled = false;
bool rema::stall_control = true;
bool rema::touch_probe_protection = true;
TickType_t rema::touch_probe_debounce_time_ms = 0;

rema::brakes_mode_t rema::brakes_mode = rema::brakes_mode_t::AUTO;
TickType_t rema::lastKeepAliveTicks;

void rema::init_input_outputs() {
    brakes_apply();

    shut_down_out.set(1);

    //NVIC_SetPriority(__HAL_GPIO_EX, TOUCH_PROBE_INTERRUPT_PRIORITY);
    //touch_probe_irq_pin.mode_edge().int_high().int_low().clear_pending().enable();
    touch_probe_irq_pin.clear_pending().enable();

}

void rema::control_enabled_set(bool status) {
    control_enabled = status;
    shut_down_out.set(!status);
    if (status) {
        x_y_axes->first_axis->stall_reset();
        x_y_axes->second_axis->stall_reset();
        z_dummy_axes->first_axis->stall_reset();
    }
}

bool rema::control_enabled_get() {
    return control_enabled;
}

void rema::brakes_release() {
    if (brakes_mode == brakes_mode_t::AUTO || brakes_mode == brakes_mode_t::OFF) {
        brakes_out.set(true);
        vTaskDelay(pdMS_TO_TICKS(BRAKES_RELEASE_DELAY_MS));
    }
}

void rema::brakes_apply() {
    if (brakes_mode == brakes_mode_t::AUTO || brakes_mode == brakes_mode_t::ON) {
        brakes_out.set(false);
    }
}

void rema::touch_probe_extend() {
    touch_probe_actuator_out.set(0);
}

void rema::touch_probe_retract() {
    touch_probe_actuator_out.set(1);
}

bool rema::is_touch_probe_touching() {
    return touch_probe_irq_pin.read();
}

void rema::update_watchdog_timer() {
    lastKeepAliveTicks = xTaskGetTickCount();
}

bool rema::is_watchdog_expired() {
    return ((xTaskGetTickCount() - lastKeepAliveTicks) > pdMS_TO_TICKS(WATCHDOG_TIME_MS));
}

void rema::hard_limits_reached() {
    /* TODO Read input pins to determine which limit has been reached and stop
     * only one motor*/
    z_dummy_axes->stop();
    x_y_axes->stop();
}

// IRQ Handler for Touch Probe
extern "C" void GPIO1_IRQHandler(void) {
    //Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(1));
    __HAL_GPIO_EXTI_CLEAR_FLAG(GPIO_PIN_1);

    static TickType_t ticks_last_release_time = 0;
    TickType_t ticks_now = xTaskGetTickCountFromISR();
    bool debounce_time_exceeded = (ticks_now - ticks_last_release_time) > pdMS_TO_TICKS(rema::touch_probe_debounce_time_ms);

    // if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT)) {
    //     Chip_PININT_ClearFallStates(LPC_GPIO_PIN_INT, PININTCH(1));    

    //     if (debounce_time_exceeded) {
    //         ticks_last_release_time = ticks_now;
    //     }
    // }

    // if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT)) {
    //     Chip_PININT_ClearRiseStates(LPC_GPIO_PIN_INT, PININTCH(1));
  
    //     if (debounce_time_exceeded) {
    //         if (x_y_axes->is_moving) {
    //             x_y_axes->was_stopped_by_probe = true;
    //         }

    //         if (z_dummy_axes->is_moving) {
    //             z_dummy_axes->was_stopped_by_probe = true;
    //         }

    //         x_y_axes->stop();
    //         z_dummy_axes->stop();
    //     }
    // }
}
