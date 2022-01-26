#include <bsp.h>
#include <stdbool.h>
#include "led_driver.h"

static uint8_t pin_num = 0xFFU;
static bool initialized = false;

void led_driver_init(uint8_t pin)
{
    pin_num = pin;
    initialized = true;
    bsp_pin_mode(pin, OUTPUT);
    bsp_digital_write(pin, LED_DRIVER_LOW);
}

led_driver_status_t led_driver_set_state(uint8_t state)
{
    led_driver_status_t status = LED_DRIVER_UNINITIALIZED;

    if (initialized)
    {
        status = LED_DRIVER_ERROR;
        if ((state == LED_DRIVER_HIGH) || (state == LED_DRIVER_LOW))
        {
            bsp_digital_write(pin_num, state);

            if (state == bsp_digital_read(pin_num))
            {
                status = LED_DRIVER_OK;
            }
        }
    }

    return status;
}
