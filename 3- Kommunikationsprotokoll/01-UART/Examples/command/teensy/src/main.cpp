#include <Arduino.h>

#define ON '1'
#define OFF '0'
#define UART Serial1

static char state = OFF;
static bool send = true;
static bool show_message = true;

void setup()
{
    Serial.begin(9600);
    UART.begin(9600);
    delay(2000);
}

void loop()
{
    if (show_message)
    {
        show_message = false;
        Serial.print("Enter the command [0: Off, 1: On]: ");
    }

    if (send)
    {
        if (Serial.available())
        {
            char chr = Serial.read();
            if ((chr == OFF) || (chr == ON))
            {
                if (UART.write(chr))
                {
                    state = chr;
                    send = false;
                    Serial.print(chr);
                }
            }
            else if (chr == '\n')
            {
                show_message = true;
                Serial.println();
            }
        }
    }
    else if (UART.available())
    {
        char chr = UART.read();
        if ((chr == OFF) || (chr == ON))
        {
            Serial.println((chr == state) ? " => done" : " => failed");
            show_message = true;
            send = true;
        }
    }
}