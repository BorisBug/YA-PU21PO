/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Provisioning means transfering the SSID and password form a WiFi module to another WiFi module in order to
 *        connect the target module to Internet.
 *        SmartConfig is a provisioning technique which uses broadcast UDP packets to transfer the SSID and password.
 *        To use this provisioning method on ESP32 you need to install EspTouch on your phone in order to transfer
 *        the SSID and password of the network your phone is connected to, to ESP32.
 *        Note: Before uploading the code, erase the flash
 *        Look at https://www.techtonions.com/esp32-using-smartconfig/
 *
 * @version 0.1
 * @date 2021-09-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <WiFi.h>
#include <Arduino.h>

#define DT_LENGTH 19

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

    /* Set ESP32 to WiFi Station mode */
    WiFi.mode(WIFI_AP_STA);

    /* start SmartConfig */
    WiFi.beginSmartConfig();

    /* Wait for SmartConfig packet from mobile */
    Serial.println("Waiting for SmartConfig.");
    while (!WiFi.smartConfigDone())
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("SmartConfig done.");

    /* Wait for WiFi to connect to AP */
    Serial.println("Waiting for WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi Connected.");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    WiFi.printDiag(Serial);

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
