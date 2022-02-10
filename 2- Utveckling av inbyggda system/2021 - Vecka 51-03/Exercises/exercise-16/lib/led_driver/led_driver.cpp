#include <stdbool.h>
#include "bsp_dio.h"
#include "led_driver.h"

#define DIO_PIN_MAX 57

#if ((LED_PIN < 0) || (LED_PIN > DIO_PIN_MAX))
#error The pin number shall be an integer in the range of 0 and DIO_PIN_MAX
#endif

static bool initialized = false;

void led_driver_init(void)
{
    bsp_pin_mode(LED_PIN, OUTPUT);
    initialized = true;
}

uint8_t led_driver_set_state(uint8_t state)
{
    uint8_t status = LED_DRIVER_ERROR;

    if (initialized)
    {
        if ((state == LED_DRIVER_LOW) || (state == LED_DRIVER_HIGH))
        {
            uint8_t led_state = (state == LED_DRIVER_LOW) ? LOW : HIGH;

            bsp_dio_write(LED_PIN, led_state);

            if (led_state == bsp_dio_read(LED_PIN))
            {
                status = LED_DRIVER_OK;
            }
        }
    }

    return status;
}
