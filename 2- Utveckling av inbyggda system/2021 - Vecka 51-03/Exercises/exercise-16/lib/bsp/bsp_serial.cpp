#include <Arduino.h>
#include "bsp_serial.h"

void bsp_serial_begin(void)
{
    Serial.begin(BAUD_RATE);

    while (!Serial)
    {
        ;
    }
}

uint8_t bsp_serial_available(void)
{
    return Serial.available();
}

char bsp_serial_read(void)
{
    return Serial.read();
}

void bsp_serial_print(const char *str)
{
    Serial.print(str);
}