#ifndef BSP_ANALOG_H
#define BSP_ANALOG_H

#include <stdint.h>

void bsp_analog_write(uint8_t pin, int val);

// Utility functions
uint8_t double_get_pin_pwm(void);
uint8_t double_get_pin_num(void);

#endif /* BSP_ANALOG_H */
