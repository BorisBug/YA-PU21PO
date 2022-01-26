#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>

#define OUTPUT 1
#define LED_DRIVER_LOW 0U
#define LED_DRIVER_HIGH 1U

typedef enum
{
    LED_DRIVER_OK,
    LED_DRIVER_ERROR,
    LED_DRIVER_UNINITIALIZED
} led_driver_status_t;

typedef struct
{
    void (*pin_mode)(uint8_t, uint8_t);
    void (*digital_write)(uint8_t, uint8_t);
    uint8_t (*digital_read)(uint8_t);
} led_driver_mcal_t;

/**
 * @brief This function is used to initialize the driver.
 *
 * @param pin The pin number is used by the LED
 */
void led_driver_init(uint8_t pin, led_driver_mcal_t *inteface);

/**
 * @brief This function is used to change the state of the LED.
 *
 * @param state The set state. It can be LED_DRIVER_LOW or LED_DRIVER_HIGH.
 * @return led_driver_status_t The status. It can be LED_DRIVER_OK, LED_DRIVER_ERROR or LED_DRIVER_UNINITIALIZED.
 */
led_driver_status_t led_driver_set_state(uint8_t state);

#endif /* LED_DRIVER_H */
