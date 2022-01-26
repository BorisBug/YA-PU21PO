#ifndef BSP_H
#define BSP_H

#include <stdint.h>

#define OUTPUT 1

void bsp_pin_mode(uint8_t pin, uint8_t mode);
void bsp_digital_write(uint8_t pin, uint8_t val);
uint8_t bsp_digital_read(uint8_t pin);

// Helper functions
uint8_t bsp_get_pin_num(void);
uint8_t bsp_get_pin_mode(void);
uint8_t bsp_get_pin_state(void);
void bsp_set_pin_status(bool status);

#endif /* BSP_H */
