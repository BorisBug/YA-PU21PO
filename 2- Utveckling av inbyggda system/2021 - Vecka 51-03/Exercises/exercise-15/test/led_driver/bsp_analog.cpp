#include "bsp_analog.h"

#ifndef DEVENV
#include <Arduino.h>
#endif

static uint8_t pin_num = 0xFF;
static uint8_t pin_pwm = 0xFF;

void bsp_analog_write(uint8_t pin, int val)
{
    pin_num = pin;
    pin_pwm = val;
#ifndef DEVENV
    analogWrite(pin, val);
#endif
}

uint8_t double_get_pin_num(void)
{
    return pin_num;
}

uint8_t double_get_pin_pwm(void)
{
    return pin_pwm;
}
