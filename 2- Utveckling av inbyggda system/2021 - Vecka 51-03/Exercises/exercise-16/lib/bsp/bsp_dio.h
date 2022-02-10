#ifndef BSP_DIO_H
#define BSP_DIO_H

#include <stdint.h>

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef OUTPUT
#define OUTPUT 2
#endif

uint8_t bsp_dio_read(uint8_t pin);

void bsp_pin_mode(uint8_t pin, uint8_t mode);

void bsp_dio_write(uint8_t pin, uint8_t val);

#endif /* BSP_DIO_H */
