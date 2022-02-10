#include <Metro.h>
#include <Arduino.h>

uint8_t led_state = LOW;
Metro metro = Metro(500);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (metro.check())
  {
    digitalWrite(LED_BUILTIN, led_state);
    led_state = !led_state;
  }
}
