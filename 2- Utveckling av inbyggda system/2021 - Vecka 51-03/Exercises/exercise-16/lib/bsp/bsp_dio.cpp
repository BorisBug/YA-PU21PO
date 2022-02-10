#include <Arduino.h>
#include "bsp_dio.h"

uint8_t bsp_dio_read(uint8_t pin)
{
    return digitalRead(pin);
}

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    pinMode(pin, mode);
}

void bsp_dio_write(uint8_t pin, uint8_t val)
{
    digitalWrite(pin, val);
}
