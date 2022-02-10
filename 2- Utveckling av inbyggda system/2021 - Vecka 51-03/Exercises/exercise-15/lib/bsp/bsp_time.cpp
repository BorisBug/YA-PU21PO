#include <Arduino.h>
#include "bsp_time.h"
#include <IntervalTimer.h>

static IntervalTimer timer;

void bsp_time_delay(uint32_t msec)
{
    delay(msec);
}

bool bsp_time_it_begin(funct_t func, uint32_t interval)
{
    return timer.begin(func, interval);
}
