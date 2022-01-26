#ifndef DEVENV
#include <Arduino.h>
#endif
#include "bsp.h"

static bool pin_status = true;
static uint8_t pin_num = 0xFFU;
static uint8_t pin_mode = 0xFFU;
static uint8_t pin_state = 0xFFU;

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pin_num = pin;
    pin_mode = mode;
#ifndef DEVENV
    pinMode(pin, mode);
#endif
}

void bsp_digital_write(uint8_t pin, uint8_t val)
{
    pin_num = pin;
    pin_state = val;
#ifndef DEVENV
    digitalWrite(pin, val);
#endif
}

uint8_t bsp_digital_read(uint8_t pin)
{
#ifdef DEVENV
    uint8_t temp = pin_state;
#else
    uint8_t temp = digitalRead(pin);
#endif

    pin_num = pin;

    if (!pin_status)
    {
        temp = !pin_state;
    }

    return temp;
}

void bsp_set_pin_status(bool status)
{
    pin_status = status;
}

uint8_t bsp_get_pin_num(void)
{
    return pin_num;
}

uint8_t bsp_get_pin_mode(void)
{
    return pin_mode;
}

uint8_t bsp_get_pin_state(void)
{
    return pin_state;
}
