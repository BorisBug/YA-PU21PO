/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief A blinky led example for Teensy 3.5
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <Arduino.h>

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT); // Set the pin connected to the built in LED as output
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH); // Set the pin state to HIGH
    delay(500);                      // Wait 500 ms
    digitalWrite(LED_BUILTIN, LOW);  // Set the pin state to LOW
    delay(500);
}
