#include <Arduino.h>
#include "ldr_driver.h"
#include "led_driver.h"
#include <IntervalTimer.h>

static IntervalTimer timer;

static void ldrled(void)
{
    led_driver_set_intensity(ldr_driver_get_intensity());
}

void setup()
{
    ldr_driver_init(33);
    led_driver_init(30);
    led_driver_set_intensity(0);

    if (!timer.begin(ldrled, 10000))
    {
        Serial.begin(9600);
        delay(2000);

        while (1)
        {
            Serial.println("Failed to start the timer!");
            delay(1000);
        }
    }
}

void loop()
{
}
