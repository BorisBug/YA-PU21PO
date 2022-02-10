#include <Wire.h>
#include <Arduino.h>

#define CLOCK_RATE 400000

void setup()
{
    Serial.begin(9600);

    Serial.print("\nPress any key to start scanning: ");
    while (!Serial.available())
    {
        delay(100);
    }

    while (!Wire.begin(SDA, SCL, CLOCK_RATE))
    {
        Serial.print("Failed to start I2C!");
        delay(1000);
    }
    Wire.setTimeOut(500);

    Serial.println("\nScanning...\n");

    for (uint8_t address = 0; address < 0x7F; address++)
    {
        Wire.beginTransmission(address);
        if (0 == Wire.endTransmission(true))
        {
            Serial.printf("I2C device found at address 0x%02X\n", address);
        }
    }

    Serial.println("\nDone!");
}

void loop()
{
}
