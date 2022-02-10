#include <Arduino.h>
#include "led_driver.h"

#define SCALE (2.55f)

static uint8_t pin_num = LED_DRIVER_ERROR;

void led_driver_init(uint8_t pin)
{
    pin_num = pin;
}

uint8_t led_driver_set_intensity(uint8_t brightness)
{
    uint8_t status = LED_DRIVER_ERROR;

    if ((pin_num != LED_DRIVER_ERROR) && (brightness <= 100))
    {
        analogWrite(pin_num, (int)(SCALE * brightness));
        status = LED_DRIVER_OK;
    }

    return status;
}
