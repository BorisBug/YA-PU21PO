#include "bsp.h"
#include <EEPROM.h>

uint16_t eeprom_init(void)
{
    eeprom_initialize();
    return EEPROM.length();
}

uint8_t eeprom_read(uint16_t address)
{
    return EEPROM.read(address);
}

void eeprom_write(uint16_t address, uint8_t value)
{
    EEPROM.write(address, value);
}
