/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 7. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Metro.h>
#include <Bounce.h> // Look at https://www.pjrc.com/teensy/td_libs_Bounce.html
#include <Arduino.h>

#define BUTTON_PIN 33
#define DURATION 100
#define INTERVAL 10

static uint32_t count = 0;
static uint32_t previous_count = 0;
static Metro timer = Metro(DURATION);
static Bounce pushbutton = Bounce(BUTTON_PIN, INTERVAL);

void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    delay(2000);
}

void loop()
{
    if (pushbutton.update())
    {
        if (pushbutton.fallingEdge())
        {
            count++;
        }
    }
    else if ((count != previous_count) && timer.check())
    {
        Serial.printf("count: %d\n", count);
        previous_count = count;
    }
}
