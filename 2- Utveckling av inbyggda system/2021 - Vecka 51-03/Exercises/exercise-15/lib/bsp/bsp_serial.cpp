#include <Arduino.h>
#include "bsp_serial.h"

void bsp_serial_begin(uint32_t speed)
{
    Serial.begin(speed);
}

void bsp_serial_print(const char *str)
{
    Serial.print(str);
}
