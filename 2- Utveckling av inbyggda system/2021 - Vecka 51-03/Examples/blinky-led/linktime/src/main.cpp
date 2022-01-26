#include <Arduino.h>
#include "led_driver.h"
#include <IntervalTimer.h>

static IntervalTimer timer;

static void blink(void)
{
    static uint8_t state = LED_DRIVER_LOW;

    state = (state == LED_DRIVER_HIGH) ? LED_DRIVER_LOW : LED_DRIVER_HIGH;

    (void)led_driver_set_state(state);
}

static void print_error(const char *msg)
{
    Serial.begin(9600);
    delay(2000);

    while (1)
    {
        Serial.println(msg);
        delay(1000);
    }
}

void setup()
{
    led_driver_init(13);

    (void)led_driver_set_state(LED_DRIVER_LOW);

    if (!timer.begin(blink, 500000))
    {
        print_error("Failed to start the timer!");
    }
}

void loop()
{
}
