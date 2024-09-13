#pragma once

#include "board.h"

template< uint32_t gpio_base, uint16_t pin>
class gpio_templ {
  public:
    static void set() {
        HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(gpio_base), pin, GPIO_PIN_SET);
    }

    static void reset() {
        HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(gpio_base), pin, GPIO_PIN_RESET);
    }

    static void set(bool state) {
        HAL_GPIO_WritePin(reinterpret_cast<GPIO_TypeDef*>(gpio_base), pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    static void toggle() {
        HAL_GPIO_TogglePin(reinterpret_cast<GPIO_TypeDef*>(gpio_base), pin);        
    }

    static bool read() {
        return HAL_GPIO_ReadPin(reinterpret_cast<GPIO_TypeDef*>(gpio_base), pin);
    }
};

template<uint32_t gpio_base, uint16_t pin, IRQn_Type IRQn>
class gpio_pinint_templ : public gpio_templ<gpio_base, pin> {
  public:
    gpio_pinint_templ() {
        // int irq = static_cast<int>(IRQn) - PIN_INT0_IRQn;
// 
        // /* Configure interrupt channel for the GPIO pin in SysCon block */
        // Chip_SCU_GPIOIntPinSel(irq, gpio_port, gpio_bit);
        // Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH(irq));
        
        /* Clear the pending interrupt flag */
        __HAL_GPIO_EXTI_CLEAR_IT(pin);
    };

    gpio_pinint_templ &int_low() {
        // int irq = static_cast<int>(IRQn) - PIN_INT0_IRQn;
        // Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH(irq));
        return *this;
    }

    gpio_pinint_templ &mode_edge() {
        // int irq = static_cast<int>(IRQn) - PIN_INT0_IRQn;
        // Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH(irq));
        return *this;
    }

    gpio_pinint_templ &clear_pending() {
        HAL_NVIC_ClearPendingIRQ(IRQn);
        return *this;
    }

    gpio_pinint_templ &enable() {
        HAL_NVIC_EnableIRQ(IRQn);
        return *this;
    }

    gpio_pinint_templ &disable() {
        HAL_NVIC_DisableIRQ(IRQn);
        return *this;
    }
};
