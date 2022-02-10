#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#include <stdint.h>

int bsp_analog_read(uint8_t pin);
void bsp_analog_write(uint8_t pin, int val);
void bsp_analog_read_resolution(uint8_t bits);

#endif /* BSP_ANALOG_H */
