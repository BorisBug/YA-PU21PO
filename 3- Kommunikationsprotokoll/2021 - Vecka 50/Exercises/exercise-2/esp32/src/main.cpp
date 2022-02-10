#include <time.h>
#include <Wire.h>
#include <WiFi.h>
#include <Arduino.h>

#define DT_LENGTH 19U

#define SSID "MaxPlus"
#define PASS "SV21TRC3556"

#define SLAVE 0x00         // The address of the slave
#define CLOCK_RATE 400000U // The speed of the communication

#define TIME_OFFSET (1 * 60 * 60)       // Offset from GMT for Sweden. It is one hour
#define TIME_DAYLIGHT (0 * 60 * 60)     // Sweden daylight saving time. Look at https://www.timeanddate.com/time/change/sweden/stockholm
#define NTP_ADDRESS "0.se.pool.ntp.org" // The NTP server

/**
 * @brief This function is used to get the current time of ESP32
 *
 * @param str A buffer to store the current time as a string in the format of YYYY-MM-DD hh:mm:ss
 */
static void get_time(char *str)
{
    time_t now;
    time(&now);
    struct tm *timeifo = localtime(&now);
    strftime(str, DT_LENGTH, "%Y-%m-%d %H:%M:%S", timeifo);
}

/**
 * @brief This function is used to get the current time from the server and initialize the time of ESP32
 *
 */
static void sync_time(void)
{
    struct tm timeinfo;
    configTime(TIME_OFFSET, TIME_DAYLIGHT, NTP_ADDRESS);

    while (!getLocalTime(&timeinfo))
    {
        delay(1000);
    }

    timeval now = {.tv_sec = mktime(&timeinfo)};
    settimeofday(&now, NULL);
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    WiFi.begin(SSID, PASS); // Initialize and beging the WiFi module

    // Wait until the module is connected to Internet
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }

    sync_time();

    WiFi.disconnect();

    while (!Wire.begin(SDA, SCL, CLOCK_RATE)) // Initialize and begin the I2C controller
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(500);
    }

    Wire.setTimeOut(500);
    digitalWrite(LED_BUILTIN, LOW);

    uint8_t status = 0;

    do
    {
        delay(500);

        char datetime[DT_LENGTH + 1] = "";
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

        get_time(datetime); // Read the current time of ESP32

        // Wire.beginTransmission(SLAVE); No need to begin the transmission

        // Transmit the current time to Teensy
        if (I2C_ERROR_OK == Wire.writeTransmission(SLAVE, (uint8_t *)datetime, DT_LENGTH, true))
        {
            // Get confirmation from Teensy
            if (I2C_ERROR_OK != Wire.readTransmission(SLAVE, &status, sizeof(status), true))
            {
                status = 0;
            }
        }

    } while (status != 1); // Until the sent date and time has not been confirmed by Teensy

    digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
}
