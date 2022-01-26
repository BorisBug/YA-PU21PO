#include <stdlib.h>
#include <stdbool.h>
#include "led_driver.h"

static uint8_t pin_num = 0xFFU;
static bool initialized = false;
static led_driver_mcal_t mcal = {0};

void led_driver_init(uint8_t pin, led_driver_mcal_t *inteface)
{
    if ((inteface != NULL) && (inteface->digital_read != NULL) &&
        (inteface->digital_write != NULL) && (inteface->pin_mode != NULL))
    {
        mcal.pin_mode = inteface->pin_mode;
        mcal.digital_read = inteface->digital_read;
        mcal.digital_write = inteface->digital_write;

        pin_num = pin;
        initialized = true;
        mcal.pin_mode(pin, OUTPUT);
        mcal.digital_write(pin, LED_DRIVER_LOW);
    }
}

led_driver_status_t led_driver_set_state(uint8_t state)
{
    led_driver_status_t status = LED_DRIVER_UNINITIALIZED;

    if (initialized)
    {
        status = LED_DRIVER_ERROR;
        if ((state == LED_DRIVER_HIGH) || (state == LED_DRIVER_LOW))
        {
            mcal.digital_write(pin_num, state);

            if (state == mcal.digital_read(pin_num))
            {
                status = LED_DRIVER_OK;
            }
        }
    }

    return status;
}
