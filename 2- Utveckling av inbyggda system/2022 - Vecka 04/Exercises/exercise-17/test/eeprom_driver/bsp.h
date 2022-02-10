#ifndef BSP_H
#define BSP_H

#include <stdint.h>

#define EEPROM_LENGTH (4094U)

uint16_t eeprom_init(void);

uint8_t eeprom_read(uint16_t address);

void eeprom_write(uint16_t address, uint8_t value);

#endif /* BSP_H */
