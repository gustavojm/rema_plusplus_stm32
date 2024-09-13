#include "gpio.h"
#include "mot_pap.h"

/**
 * @brief	 inits one gpio passed as output
 * @returns nothing
 */

/**
 * @brief    GPIO sets pin passed to high
 * @returns nothing
 */
gpio_base &gpio_base::set() {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
    return *this;
}

/**
 * @brief    GPIO sets pin passed to low
 * @returns nothing
 */
gpio_base &gpio_base::reset() {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
    return *this;
}

/**
 * @brief	 GPIO sets pin passed to the state specified
 * @returns nothing
 */
gpio_base &gpio_base::set([[maybe_unused]]bool state) {
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return *this;
}

/**
 * @brief    GPIO sets pin passed as parameter to the state specified
 * @returns nothing
 */
bool gpio_base::read() const {
    return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
    return true;
}

/**
 * @brief	toggles GPIO corresponding pin passed as parameter
 * @returns nothing
 */
gpio_base &gpio_base::toggle() {
    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
    return *this;
}
