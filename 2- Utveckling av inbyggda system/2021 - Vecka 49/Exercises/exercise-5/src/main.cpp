/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 5. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

#define DELAY 50
#define MAX_VOLTAGE 3.0f
#define MIN_VOLTAGE 0.0f
#define DAC_RESOLUTION 12
#define VOLTAGE_RESOLUTION (3.3f / (1 << DAC_RESOLUTION))

static float fading_step = 0.15f;
static float voltage = MIN_VOLTAGE;

void setup()
{
    analogWriteResolution(DAC_RESOLUTION);
}

void loop()
{
    analogWriteDAC0((int)(voltage / VOLTAGE_RESOLUTION));

    voltage += fading_step;

    if (voltage <= MIN_VOLTAGE || voltage >= MAX_VOLTAGE)
    {
        voltage -= fading_step;
        fading_step = -fading_step;
    }

    delay(50);
}
