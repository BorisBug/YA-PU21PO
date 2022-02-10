#include "bsp.h"

#ifndef DEVENV
#include <EEPROM.h>
#else
#include <string.h>

static uint8_t array[EEPROM_LENGTH] = {0};
#endif

uint16_t eeprom_init(void)
{
#ifdef DEVENV
    return EEPROM_LENGTH;
#else
    eeprom_initialize();
    return EEPROM.length();
#endif
}

uint8_t eeprom_read(uint16_t address)
{
#ifdef DEVENV
    return array[address];
#else
    return EEPROM.read(address);
#endif
}

void eeprom_write(uint16_t address, uint8_t value)
{
#ifdef DEVENV
    array[address] = value;
#else
    EEPROM.write(address, value);
#endif
}
