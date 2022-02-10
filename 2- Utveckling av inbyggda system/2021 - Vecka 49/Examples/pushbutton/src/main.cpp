#include <Metro.h>
#include <Arduino.h>

#define DURATION 100
#define BUTTON_PIN 33

uint32_t count = 0;
uint32_t previous_count = 0;
uint8_t previous_state = HIGH;
Metro timer = Metro(DURATION);

void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    delay(2000);
}

void loop()
{
    uint8_t current_state = digitalRead(BUTTON_PIN);

    if (current_state != previous_state)
    {
        if (current_state == LOW)
        {
            count++;
        }
        previous_state = current_state;
    }
    else if ((count != previous_count) && timer.check())
    {
        Serial.printf("count: %d\n", count);
        previous_count = count;
    }
}
