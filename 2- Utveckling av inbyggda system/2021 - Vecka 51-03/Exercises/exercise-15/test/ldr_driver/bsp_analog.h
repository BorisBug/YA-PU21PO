#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#include <stdint.h>

int bsp_analog_read(uint8_t pin);
void bsp_analog_read_resolution(uint8_t bits);

// Utility functions
uint8_t double_get_pin_num(void);
uint8_t double_get_resolutuin(void);
void double_stub_digital_value(int value); // We use this function to provide test data and fake the ADC

#endif /* BSP_ANALOG_H */
