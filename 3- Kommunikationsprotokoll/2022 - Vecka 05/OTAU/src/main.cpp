/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Over The Air Update. Look at https://randomnerdtutorials.com/esp32-ota-over-the-air-vs-code/
 * @version 0.1
 * @date 2021-09-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <WiFi.h>
#include <Arduino.h>
#include <AsyncTCP.h>
#include <AsyncElegantOTA.h>
#include <ESPAsyncWebServer.h>

// To upload OTA set this to 1 and build the project and browse http://<IP Address>/update and upload firmware.bin
#define NEW_SKETCH 0

#define SSID "MaxPlus"
#define PASSWORD "SV21TRC3556"

static AsyncWebServer server(80);

void setup(void)
{
    Serial.begin(9600);

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", "Hi! I am ESP32!"); });

    AsyncElegantOTA.begin(&server); // Start ElegantOTA
    server.begin();
    Serial.println("HTTP server started");

#if NEW_SKETCH
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
#endif
}

void loop(void)
{
#if NEW_SKETCH
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(1000);
#endif
}
