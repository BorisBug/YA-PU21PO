/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief UART Over BLE.
 *        Install nRF Toolbox on your mobile.
 *            - Click on UART
 *            - Click on Connect and find UART_OVER_BLE
 *            - Click on Logs to see what you receive from ESP32
 *            - In the Custom Text Command box, by entering a number between 0 and 255 you can change the light intensity of the LED.
 * @version 0.1
 * @date 2020-04-02
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <Arduino.h>
#include <BLEDevice.h>

#define STRLEN (8U)

static bool deviceConnected = false;
static BLECharacteristic *txCharacteristic;

// UUIDs from https://infocenter.nordicsemi.com/index.jsp?topic=%2Fcom.nordic.infocenter.sdk5.v14.0.0%2Fble_sdk_app_nus_eval.html
#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"           // UART Over BLE Service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E" // Charactristic UUID for WRITE
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E" // Charactristic UUID for READ

class ServerCallbacks : public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
    }

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
    }
};

class CharactristicCallbacks : public BLECharacteristicCallbacks
{
    void onWrite(BLECharacteristic *pCharacteristic)
    {
        uint8_t value = 0;
        const char *ptr = pCharacteristic->getValue().c_str();
        while (*ptr != '\0')
        {
            if (isdigit(*ptr))
            {
                value *= 10;
                value += *ptr - '0';
            }
            ptr++;
        }
        Serial.println(value);
        ledcWrite(LED_BUILTIN, value);
    }
};

void setup()
{
    Serial.begin(9600);
    delay(2000);

    // Configure LED PWM functionalitites
    ledcSetup(LED_BUILTIN, 1000000, 8);

    // Attach the channel to LED_BUILTIN
    ledcAttachPin(LED_BUILTIN, LED_BUILTIN);

    // Create the BLE Device
    BLEDevice::init("UART_OVER_BLE");

    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ServerCallbacks());

    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create a BLE Characteristic for TX
    txCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, BLECharacteristic::PROPERTY_READ);

    // Create a BLE Characteristic for RX
    BLECharacteristic *rxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, BLECharacteristic::PROPERTY_WRITE);

    rxCharacteristic->setCallbacks(new CharactristicCallbacks());

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();

    Serial.println("Waiting a client connection to notify...");
}

void loop()
{
    if (deviceConnected)
    {
        char string[STRLEN + 1] = {0};
        for (uint8_t i = 0; i < STRLEN; i++)
        {
            string[i] = ((i == 0) ? 'A' : 'a') + random(26);
        }

        txCharacteristic->setValue(string);
        txCharacteristic->notify(); // Send the string to the client!
    }

    delay(1000);
}