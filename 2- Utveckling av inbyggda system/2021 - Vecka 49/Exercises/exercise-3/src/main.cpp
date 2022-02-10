/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 3. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Metro.h>
#include <Arduino.h>

#define STEP 5
#define DELAY 50

static Metro metro = Metro(DELAY);
static int8_t fading_step = STEP;
static int16_t brightness = 0;

void setup()
{
}

void loop()
{
    if (metro.check())
    {
        analogWrite(A9, brightness);

        brightness += fading_step;

        if (brightness <= 0 || brightness >= 255)
        {
            brightness -= fading_step;
            fading_step = -fading_step;
        }
    }
}
