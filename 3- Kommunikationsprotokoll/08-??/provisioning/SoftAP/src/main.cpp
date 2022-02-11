/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Provisioning means transfering the SSID and password form a WiFi module to another WiFi module in order to
 *        connect the target module to Internet.
 *        SoftAP is a provisioning technique in which ESP32 acts as an access point device and we can connect another device
 *        to it and transfer the SSID and the password.
 *        To use this provisioning method on ESP32 you need to install "ESP SoftAP Prov" on your phone and connect your phone
 *        to ESP32. In the following example you need to connect your phone to PROV_ESP32.
 *        Note: Before uploading the code, erase the flash
 *
 * @version 0.1
 * @date 2021-09-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <Arduino.h>
#include "WiFiProv.h"

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

void SysProvEvent(system_event_t *sys_event, wifi_prov_event_t *prov_event)
{
    if (sys_event)
    {
        switch (sys_event->event_id)
        {
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("\nConnected IP address : ");
            Serial.println(ip4addr_ntoa(&sys_event->event_info.got_ip.ip_info.ip));
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("\nDisconnected. Connecting to the AP again... ");
            break;
        default:
            break;
        }
    }

    if (prov_event)
    {
        switch (prov_event->event)
        {
        case WIFI_PROV_START:
            Serial.println("\nProvisioning started\nGive Credentials of your access point using ESP SoftAP Prov");
            break;
        case WIFI_PROV_CRED_RECV:
        {
            Serial.println("\nReceived Wi-Fi credentials");
            wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)prov_event->event_data;
            Serial.print("\tSSID : ");
            Serial.println((const char *)wifi_sta_cfg->ssid);
            Serial.print("\tPassword : ");
            Serial.println((char const *)wifi_sta_cfg->password);
            break;
        }
        case WIFI_PROV_CRED_FAIL:
        {
            wifi_prov_sta_fail_reason_t *reason = (wifi_prov_sta_fail_reason_t *)prov_event->event_data;
            Serial.println("\nProvisioning failed!\nPlease reset to factory and retry provisioning\n");
            if (*reason == WIFI_PROV_STA_AUTH_ERROR)
                Serial.println("\nWi-Fi AP password incorrect");
            else
                Serial.println("\nWi-Fi AP not found....Add API \" nvs_flash_erase() \" before beginProvision()");
            break;
        }
        case WIFI_PROV_CRED_SUCCESS:
            Serial.println("\nProvisioning Successful");
            break;
        case WIFI_PROV_END:
            Serial.println("\nProvisioning Ends");
            break;
        default:
            break;
        }
    }
}

void setup()
{
    Serial.begin(9600);
    WiFi.onEvent(SysProvEvent);
    WiFiProv.beginProvision(provSchemeSoftAP, WIFI_PROV_EVENT_HANDLER_NONE, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_ESP32", NULL, NULL);

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
