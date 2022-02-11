#include <Arduino.h>

#define ON '1'
#define OFF '0'
#define UART Serial1

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    UART.begin(9600);
    delay(2000);
}

void loop()
{
    if (UART.available())
    {
        char state = UART.read();
        if ((state == ON) || (state == OFF))
        {
            digitalWrite(LED_BUILTIN, (state == ON) ? HIGH : LOW);
            UART.write((HIGH == digitalRead(LED_BUILTIN)) ? ON : OFF);
        }
    }
}
