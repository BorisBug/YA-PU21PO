#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#define LED_PIN 13

#define LED_DRIVER_LOW 0
#define LED_DRIVER_HIGH 1

#define LED_DRIVER_OK 254
#define LED_DRIVER_ERROR 255

void led_driver_init(void);

uint8_t led_driver_set_state(uint8_t state);

// Some helper functions to get access to the internal data of this test double
void double_set_led_driver_status(uint8_t status);
uint8_t double_get_led_state(void);
uint8_t double_get_led_init(void);

#endif /* LED_DRIVER_H */
