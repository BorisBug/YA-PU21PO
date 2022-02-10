/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 2. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

#define LED_PIN 0

static uint8_t led_state = LOW;
static uint32_t last_millis = 0;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    uint32_t now = millis();

    if (now - last_millis >= 500u)
    {
        last_millis = now;
        led_state = !led_state;
        digitalWrite(LED_PIN, led_state);
    }
}
