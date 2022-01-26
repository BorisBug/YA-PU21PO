#include "bsp.h"
#include <Arduino.h>

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

void bsp_digital_write(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}

uint8_t bsp_digital_read(uint8_t pin)
{
    return digitalRead(pin);
}
