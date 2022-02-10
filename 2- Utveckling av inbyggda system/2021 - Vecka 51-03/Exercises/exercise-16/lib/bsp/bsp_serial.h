#ifndef BSP_SERIAL_H
#define BSP_SERIAL_H

#include <stdint.h>

#define BAUD_RATE 9600

void bsp_serial_begin(void);

void bsp_serial_print(const char *str);

uint8_t bsp_serial_available(void);

char bsp_serial_read(void);

#endif /* BSP_SERIAL_H */
