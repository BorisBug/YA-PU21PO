#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#define LED_DRIVER_OK 0U
#define LED_DRIVER_ERROR 0xFFU

void led_driver_init(uint8_t pin);

uint8_t led_driver_set_intensity(uint8_t brightness);

#endif /* LED_DRIVER_H */
