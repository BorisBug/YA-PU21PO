#include <Wire.h>
#include <Arduino.h>

#define ON '1'
#define OFF '0'
#define SLAVE 0x00
#define CLOCK_RATE 400000

static bool show_message = true;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    while (!Wire.begin(SDA, SCL, CLOCK_RATE))
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(1000);
    }
    Wire.setTimeOut(500);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(9600);
    delay(2000);
}

void loop()
{
    if (show_message)
    {
        show_message = false;
        Serial.print("Enter the command [0: Off, 1: On]: ");
    }

    if (Serial.available())
    {
        char chr = Serial.read();
        if ((chr == OFF) || (chr == ON))
        {
            Serial.print(chr);

            Wire.beginTransmission(SLAVE);
            Wire.write(chr);
            if (Wire.lastError())
            {
                digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            }
            else
            {
                digitalWrite(LED_BUILTIN, LOW);
            }
            Wire.endTransmission(false);

            char state = 0;
            Wire.requestFrom(SLAVE, sizeof(chr));
            if (Wire.lastError())
            {
                digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
            }
            else if (Wire.available())
            {
                state = Wire.read();
                digitalWrite(LED_BUILTIN, LOW);
            }

            Wire.endTransmission(true);

            Serial.println((state == chr) ? " => done" : " => failed");
            show_message = true;
        }
        else if (chr == '\n')
        {
            show_message = true;
            Serial.println();
        }
    }
}
