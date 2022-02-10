#include <i2c_t3.h>
#include <TimeLib.h>

#define DT_LENGTH 19U
#define ADDRESS 0x00U
#define INITIALIZED 1U
#define UNINITIALIZED 0U

static volatile uint8_t status = UNINITIALIZED;

void requestEvent(void)
{
    // Send the status to ESP32
    if (sizeof(status) != Wire.write(status))
    {
        Serial.println("Failed to send the status!");
    }
}

void receiveEvent(size_t length)
{
    char data[DT_LENGTH + 1] = {0};

    // Receive and check the data from ESP32
    if (length == Wire.read(data, DT_LENGTH))
    {
        int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;

        // Extract date and time from the received data
        if (6 == sscanf(data, "%04d-%02d-%02d %02d:%02d:%02d", &year, &month, &day, &hour, &minute, &second))
        {
            status = INITIALIZED;
            setTime(hour, minute, second, day, month, year); // Set time of the RTC of Teensy
        }
    }
    else
    {
        Serial.println("Failed to receive date and time!");
    }
}

void setup()
{
    Serial.begin(9600);
    while (!Serial)
    {
        delay(500);
    }

    Wire.begin(I2C_SLAVE, ADDRESS, I2C_PINS_18_19, I2C_PULLUP_INT);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
    delay(1000);
    Serial.print("Current datetime: ");
    Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n\n", year(), month(), day(), hour(), minute(), second());
}
