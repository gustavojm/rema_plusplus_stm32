#pragma once

#include "board.h"

class gpio_base {
  public:
    gpio_base() = default;


/**
 * Parameters:
 * GPIOx – where x can be (A..K) to select the GPIO peripheral.
 * GPIO_Pin – specifies the port bit to be written. This parameter can be one of GPIO_PIN_x where x can be (0..15).
 * PinState – specifies the value to be written to the selected bit. 
 * This parameter can be one of the GPIO_PinState enum values: GPIO_PIN_RESET: to clear the port pin GPIO_PIN_SET: to set the port pin
 */

    gpio_base(GPIO_TypeDef* gpio, uint16_t pin) :
        GPIOx(gpio), GPIO_Pin(pin) {
    }

    gpio_base &toggle();

    gpio_base &set();

    gpio_base &reset();

    gpio_base &set(bool state);

    bool read() const;

    GPIO_TypeDef* GPIOx;
    uint16_t GPIO_Pin;
};

class gpio_pinint : public gpio_base {
  public:
    //LPC43XX_IRQn_Type IRQn;

    gpio_pinint(GPIO_TypeDef* gpio, uint16_t pin, IRQn_Type IRQn)
        : gpio_base(gpio, pin) {//, IRQn(IRQn) {
        //int irq = static_cast<int>(IRQn) - PIN_INT0_IRQn;

        /* Configure interrupt channel for the GPIO pin in SysCon block */
        // Chip_SCU_GPIOIntPinSel(irq, gpio_port, gpio_bit);
        
        // Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(irq));
    };

    gpio_pinint &clear_pending() {
        // NVIC_ClearPendingIRQ(IRQn);
        return *this;
    }

    gpio_pinint &enable() {
        // NVIC_EnableIRQ(IRQn);
        return *this;
    }

    gpio_pinint &disable() {
        // NVIC_DisableIRQ(IRQn);
        return *this;
    }

};
