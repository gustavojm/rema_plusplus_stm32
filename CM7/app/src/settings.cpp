#include "settings.h"
#include "board.h"
#include "../inc/debug.h"

/* Page used for storage */
#define PAGE_ADDR 0x01 /* Page number */

/**
 * @brief 	default hardcoded settings
 * @returns	copy of settings structure
 */
void settings::defaults() {
    IP4_ADDR(&network.gw, 192, 168, 2, 1);
    IP4_ADDR(&network.ipaddr, 192, 168, 2, 20);
    IP4_ADDR(&network.netmask, 255, 255, 255, 0);
    network.port = 5020;
}

void settings::init() {
    EEPROM_init();

    gpio_templ<GPIOB_BASE, GPIO_PIN_0> settings_erase_btn; // 
    if (!settings_erase_btn.read()) {
        settings::erase();
    }
}

/**
 * @brief 	erases EEPROM page containing settings
 * @returns	nothing
 */
void settings::erase() {
    lDebug(Info, "EEPROM Erase...");
    EEPROM_Erase(PAGE_ADDR);
}

/**
 * @brief 	saves settings to EEPROM
 * @returns	nothing
 */
void settings::save() {
    settings::erase();

    lDebug(Info, "EEPROM write...");
    EEPROM_Write(0, PAGE_ADDR, &(network), sizeof network);
}

/**
 * @brief 	reads settings from EEPROM. If no valid settings are found
 * 			loads default hardcoded values
 * @returns	copy of settings structure
 */
void settings::read() {
    lDebug(Info, "EEPROM Read...");
    EEPROM_Read(0, PAGE_ADDR, &network, sizeof network);

    if ((network.gw.addr == 0) || (network.ipaddr.addr == 0) || (network.netmask.addr == 0) || (network.port == 0)) {
        lDebug(Info, "No network config loaded from EEPROM. Loading default settings");
        settings::defaults();
    } else {
        lDebug(Info, "Using settings loaded from EEPROM");
    }
}
