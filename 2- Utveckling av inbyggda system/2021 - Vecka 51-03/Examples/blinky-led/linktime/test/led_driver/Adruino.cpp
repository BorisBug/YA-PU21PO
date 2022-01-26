#include "Arduino.h"

static bool pin_status = true;
static uint8_t pin_num = 0xFFU;
static uint8_t pin_mode = 0xFFU;
static uint8_t pin_state = 0xFFU;

void pinMode(uint8_t pin, uint8_t mode)
{
    pin_num = pin;
    pin_mode = mode;
}

void digitalWrite(uint8_t pin, uint8_t val)
{
    pin_num = pin;
    pin_state = val;
}

uint8_t digitalRead(uint8_t pin)
{
    uint8_t temp = pin_state;

    pin_num = pin;

    if (!pin_status)
    {
        temp = !pin_state;
    }

    return temp;
}

void arduino_set_pin_status(bool status)
{
    pin_status = status;
}

uint8_t arduino_get_pin_num(void)
{
    return pin_num;
}

uint8_t arduino_get_pin_mode(void)
{
    return pin_mode;
}

uint8_t arduino_get_pin_state(void)
{
    return pin_state;
}
