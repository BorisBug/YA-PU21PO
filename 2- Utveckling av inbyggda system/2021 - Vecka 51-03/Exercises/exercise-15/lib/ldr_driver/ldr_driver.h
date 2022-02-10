#ifndef LDR_DRIVER_H
#define LDR_DRIVER_H

#include <stdint.h>

#define ADC_RESOLUTION 12          // The resolution of the ADC.
#define RESISTOR_RESISTANCE (4700) // The resistance of the resistor

#define LDR_RESISTANCE_MIN 1000
#define LDR_RESISTANCE_MAX 10000

#define LDR_DRIVER_OK 0
#define LDR_DRIVER_ERROR 1

void ldr_driver_init(uint8_t pin);

uint8_t ldr_driver_get_intensity(void);

#endif /* LDR_DRIVER_H */
