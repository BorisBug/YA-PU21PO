#include "RNGA.h"
#include <Metro.h>
#include <Arduino.h>

void setup()
{
    rnga_init();

    Serial.begin(9600);
    while (!Serial)
    {
        delay(100);
    }

    rnga_start();
}

void loop()
{
    rnga_seed(micros());
    Serial.println(rnga_generate(10, 100));
    delay(100 + rnga_generate(0, 400));
}
