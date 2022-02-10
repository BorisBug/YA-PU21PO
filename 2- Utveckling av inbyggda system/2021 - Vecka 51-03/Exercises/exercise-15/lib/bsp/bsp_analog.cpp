#include <Arduino.h>
#include "bsp_analog.h"

int bsp_analog_read(uint8_t pin)
{
    return analogRead(pin);
}

void bsp_analog_write(uint8_t pin, int val)
{
    analogWrite(pin, val);
}

void bsp_analog_read_resolution(uint8_t bits)
{
    analogReadResolution(bits);
}
