#include "led_driver.h"
#ifndef DEVENV
#include <bsp_dio.h>
#endif

static uint8_t led_status = LED_DRIVER_ERROR;
static uint8_t led_state = LED_DRIVER_ERROR;
static bool led_init = false;

void led_driver_init(void)
{
#ifndef DEVENV
    bsp_pin_mode(LED_PIN, OUTPUT);
#endif
    led_init = true;
}

uint8_t led_driver_set_state(uint8_t state)
{
    led_state = state;
#ifndef DEVENV
    if (led_status == LED_DRIVER_OK)
    {
        bsp_dio_write(LED_PIN, (state == LED_DRIVER_HIGH) ? HIGH : LOW);
    }
#endif
    return led_status;
}

void double_set_led_driver_status(uint8_t status)
{
    led_status = status;
}

uint8_t double_get_led_init(void)
{
    return led_init ? LED_DRIVER_OK : LED_DRIVER_ERROR;
}

uint8_t double_get_led_state(void)
{
    return led_state;
}
