/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 4. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>
#include <IntervalTimer.h>

#define STEP 5
#define INTERVAL 50000

static IntervalTimer timer;

static void fading(void)
{
    static int16_t brightness = 0;
    static int8_t fading_step = STEP;

    analogWrite(A9, brightness);

    brightness += fading_step;

    if (brightness <= 0 || brightness >= 255)
    {
        brightness -= fading_step;
        fading_step = -fading_step;
    }
}

void setup()
{
    timer.begin(fading, INTERVAL);
}

void loop()
{
}
