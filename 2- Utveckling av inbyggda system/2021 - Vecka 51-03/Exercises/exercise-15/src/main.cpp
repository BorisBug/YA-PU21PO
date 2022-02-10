#include "bsp_time.h"
#include "bsp_serial.h"
#include "ldr_driver.h"
#include "led_driver.h"

static void ldrled(void)
{
    led_driver_set_intensity(ldr_driver_get_intensity());
}

int main(void)
{
    ldr_driver_init(33);
    led_driver_init(30);
    led_driver_set_intensity(0);

    if (!bsp_time_it_begin(ldrled, 10000))
    {
        bsp_serial_begin(9600);
        bsp_time_delay(2000);

        while (1)
        {
            bsp_serial_print("Failed to start the timer!\n");
            bsp_time_delay(1000);
        }
    }

    while (1)
    {
        ;
    }

    return 0;
}
