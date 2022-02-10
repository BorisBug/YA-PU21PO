#include <Arduino.h>

uint16_t counter = 0;
uint8_t led_state = LOW;
uint32_t last_millis = 0;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    uint32_t now = millis();

    if (last_millis > now) // When the timer gets overflowed
    {
        counter += (0xFFFFFFFFu - last_millis) + 1u + now;
    }
    else
    {
        counter += (now - last_millis);
    }

    last_millis = now;

    if (counter >= 500u)
    {
        counter = 0;
        led_state = !led_state;
        digitalWrite(LED_BUILTIN, led_state);
    }
}
