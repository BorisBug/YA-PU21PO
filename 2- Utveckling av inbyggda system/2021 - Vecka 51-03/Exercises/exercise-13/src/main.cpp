/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example code of using the mmetro module
 * @version 0.1
 * @date 2021-05-29
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "mmetro.h"
#include <Arduino.h>

static mmetro_t *metro = NULL;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    mmetro_init(NULL);                    // Initialize the metro module
    metro = mmetro_create(false, 500000); // A metro with 500000us (500ms) interval

    if (metro == NULL)
    {
        Serial.begin(9600);
        delay(2000);

        while (1)
        {
            Serial.println("Failed to create the metro");
            delay(1000);
        }
    }
}

void loop()
{
    if (MMETRO_YES == mmetro_check(metro))
    {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    }
}
