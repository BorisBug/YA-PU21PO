#include <Arduino.h>

#define UART Serial1

void setup()
{
    Serial.begin(9600);
    UART.begin(9600);
    delay(2000);
}

void loop()
{
    if (Serial.available())
    {
        char chr = Serial.read();
        Serial.print(chr);
        UART.write(chr);
    }

    if (UART.available())
    {
        char chr = UART.read();
        if (chr != '\0')
        {
            Serial.print(chr);
        }
    }
}
