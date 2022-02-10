#include "Arduino.h"

static uint8_t pin_num = 0xFF;
static uint8_t pin_pwm = 0xFF;

void analogWrite(uint8_t pin, int val)
{
    pin_num = pin;
    pin_pwm = val;
}

uint8_t arduino_pin_num(void)
{
    return pin_num;
}

uint8_t arduino_pin_pwm(void)
{
    return pin_pwm;
}
