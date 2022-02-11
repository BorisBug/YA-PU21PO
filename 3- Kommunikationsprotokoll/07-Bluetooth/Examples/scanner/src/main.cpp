/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of BLE Scan.
 * @version 0.1
 * @date 2020-04-08
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <Arduino.h>
#include <BLEScan.h>
#include <BLEDevice.h>
#include <BLEAdvertisedDevice.h>

static uint32_t scan_time = 1; // In seconds
static BLEScan *pBLEScan = NULL;

class advertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        Serial.printf("Address: %s", advertisedDevice.getAddress().toString().c_str());

        if (advertisedDevice.haveName())
        {
            Serial.printf(", Name: %s", advertisedDevice.getName().c_str());
        }

        if (advertisedDevice.haveServiceUUID())
        {
            Serial.printf(", ServiceUUID: %s", advertisedDevice.getServiceUUID().toString().c_str());
        }

        if (advertisedDevice.haveServiceData())
        {
            uint8_t *data = (uint8_t *)advertisedDevice.getServiceData().c_str();

            Serial.print(", ServiceData: ");
            while (*data != '\0')
            {
                Serial.printf("%02x", *data);
                data++;
            }
        }

        if (advertisedDevice.haveTXPower())
        {
            Serial.printf(", TXPower: %d", advertisedDevice.getTXPower());
        }

        Serial.println();
    }
};

void setup()
{
    Serial.begin(9600);
    delay(3000);

    Serial.println("Scanning...");

    BLEDevice::init("ESP32_SCANNER");
    pBLEScan = BLEDevice::getScan(); // Create new scan

    pBLEScan->setAdvertisedDeviceCallbacks(new advertisedDeviceCallbacks());
    pBLEScan->setActiveScan(false); // Active scan uses more power, but gets results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // Less or equal setInterval value
}

void loop()
{
    pBLEScan->start(scan_time, false);
    pBLEScan->clearResults(); // Delete results from BLEScan buffer to release memory
    pBLEScan->stop();

    Serial.println();
    delay(2500);
}