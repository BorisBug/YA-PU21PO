#include <SPI.h>
#include <Arduino.h>

#define ON '1'
#define OFF '0'
#define PIN_SPI_SS 33
#define CLOCK_RATE 1000000

static bool show_message = true;
static SPISettings setting = SPISettings(CLOCK_RATE, MSBFIRST, SPI_MODE0);

void setup()
{
    pinMode(PIN_SPI_SS, OUTPUT);
    digitalWrite(PIN_SPI_SS, HIGH);

    Serial.begin(9600);
    SPI.begin();
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

            SPI.beginTransaction(setting);
            digitalWrite(PIN_SPI_SS, LOW);

            SPI.transfer(chr);

            SPI.transfer(0); // Dummy byte
            uint8_t state = SPI.transfer(0);

            digitalWrite(PIN_SPI_SS, HIGH);
            SPI.endTransaction();

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
