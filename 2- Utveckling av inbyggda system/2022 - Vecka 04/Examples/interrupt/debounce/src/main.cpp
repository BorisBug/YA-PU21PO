#include <Arduino.h>

#define BUTTON_PIN 33

static uint32_t prev_count = 0;
volatile static uint32_t count = 0;

void isr_button_pressed(void)
{
    noInterrupts(); // Disbale interrupts to prevent nested interrupts

    static uint32_t prev_ms = 0;

    uint32_t now = millis();
    uint32_t passed = (now - prev_ms);

    if (prev_ms > now) // The timer has been overflowed
    {
        passed = (0xFFFFFFFFu - prev_ms) + 1u + now;
    }

    if (passed > 150)
    {
        count++;
    }

    prev_ms = now;

    interrupts(); // Enable interrupts
}

void setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.begin(9600);
    delay(2000);

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), isr_button_pressed, FALLING);
}

void loop()
{
    if (prev_count != count)
    {
        Serial.print("Count = ");
        Serial.println(count);
        prev_count = count;
    }

    if (count % 10 == 0)
    {
        noInterrupts();
        count++; // A protected shared varaible
        interrupts();
    }
}
