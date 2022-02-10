#ifndef BSP_SERIAL_H
#define BSP_SERIAL_H

#include <stdint.h>

void bsp_serial_begin(uint32_t speed);

void bsp_serial_print(const char *str);

#endif /* BSP_SERIAL_H */
