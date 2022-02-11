#include <SPI.h>
#include <Arduino.h>

#define STRLEN 32
#define PIN_SPI_SS 33
#define CLOCK_RATE 1000000

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
    uint8_t string[STRLEN + 1] = {0};
    for (uint8_t i = 0; i < STRLEN; i++)
    {
        string[i] = 'a' + random(26); // Generate a random string (lowercase)
    }
    Serial.printf("Master: %s\n", (char *)string);

    SPI.beginTransaction(setting);
    digitalWrite(PIN_SPI_SS, LOW);

    for (uint8_t i = 0; i < STRLEN; i++)
    {
        SPI.transfer(string[i]);     // Send data to the slave
        SPI.transfer(0);             // Dummy byte
        string[i] = SPI.transfer(0); // Receive data from the slave
    }

    digitalWrite(PIN_SPI_SS, HIGH);
    SPI.endTransaction();

    Serial.printf("Slave : %s\n", (char *)string);

    Serial.println();
    delay(1000);
}