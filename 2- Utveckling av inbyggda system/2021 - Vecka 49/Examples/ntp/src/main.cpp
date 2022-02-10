/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of using WiFi, the standard time library and an NTP server to get the current date and time from a server
 *        and use it to set the time of the microcontroller RTC.
 * @version 0.1
 * @date 2021-03-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <time.h>
#include <WiFi.h>
#include <Arduino.h>

#define DT_LENGTH 19

#define SSID "MaxPlus"
#define PASSWORD "SV21TRC3556"

#define TIME_OFFSET (1 * 60 * 60)      // Offset from GMT in seconds. For Sweden it is 1 hour
#define TIME_DAYLIGHT (1 * 60 * 60)    // Daylight saving time in Sweden (1hour). It starts from march 28 and ends in october 31
#define NTP_SERVER "0.se.pool.ntp.org" // Address of the NTP server

static void sync_time(void)
{
    configTime(TIME_OFFSET, TIME_DAYLIGHT, NTP_SERVER);

    struct tm timeinfo = {0};

    while (!getLocalTime(&timeinfo))
    {
        delay(1000);
    }

    timeval now = {.tv_sec = mktime(&timeinfo)};

    settimeofday(&now, NULL);
}

void setup()
{
    Serial.begin(9600);
    delay(2000);

    WiFi.begin(SSID, PASSWORD);

    while (WL_CONNECTED != WiFi.status())
    {
        Serial.print(".");
        delay(500);
    }

    sync_time();

    WiFi.disconnect();
}

void loop()
{
    time_t now = 0;
    char datetime[DT_LENGTH + 1] = {0};

    time(&now);
    struct tm *timeinfo = localtime(&now);
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", timeinfo);

    Serial.println(datetime);

    delay(1000);
}
