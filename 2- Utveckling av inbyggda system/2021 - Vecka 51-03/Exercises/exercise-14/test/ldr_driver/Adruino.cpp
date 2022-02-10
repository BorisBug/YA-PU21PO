#include "Arduino.h"

static int pin_value = 0;
static uint8_t pin_num = 0xFF;
static uint8_t resolution = 0xFF;

void analogReadResolution(uint8_t bits)
{
    resolution = bits;
}

int analogRead(uint8_t pin)
{
    pin_num = pin;
    return pin_value;
}

void arduino_set_pin_value(int value)
{
    pin_value = value;
}

uint8_t arduino_get_pin_num(void)
{
    return pin_num;
}

uint8_t arduino_get_resolutuin(void)
{
    return resolution;
}
