#include <Arduino.h>
#include <IntervalTimer.h>

/* Comment and uncomment the following line and compare the outputs */
#define VOLATILE

#ifdef VOLATILE
static volatile bool status = true;
#else
static bool status = true;
#endif

static IntervalTimer timer;

static void func(void)
{
    status = false;
    Serial.print("\nStatus = false; ");
}

void setup()
{
    Serial.begin(9600);
    delay(2000);

    timer.begin(func, 1000000);
}

void loop()
{
    while (status)
    {
        ;
    }

    Serial.println("Outside of the while loop!");
    status = true;
}
