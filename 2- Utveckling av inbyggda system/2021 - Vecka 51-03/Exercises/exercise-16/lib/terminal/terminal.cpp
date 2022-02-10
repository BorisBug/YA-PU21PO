#include <string.h>
#include <stdbool.h>
#include "terminal.h"
#include "led_driver.h"
#include "bsp_serial.h"

#define ON '1'
#define OFF '0'

#define DONE_MSG " => done\n"
#define FAILED_MSG " => faild\n"
#define COMMAND_MSG "Enter the command [0: Off, 1: On]: "

static bool initialized = false;
static bool show_message = true;

void terminal_init(void)
{
    led_driver_init();
    bsp_serial_begin();
    led_driver_set_state(LED_DRIVER_LOW);
    initialized = true;
}

void terminal_run(void)
{
    if (initialized)
    {
        if (show_message)
        {
            show_message = false;
            bsp_serial_print(COMMAND_MSG);
        }

        if (0 < bsp_serial_available())
        {
            char chr = bsp_serial_read();

            if ((chr == ON) || (chr == OFF) || (chr == '\n'))
            {
                char temp[2 + (sizeof(DONE_MSG) > sizeof(FAILED_MSG) ? sizeof(DONE_MSG) : sizeof(FAILED_MSG))] = "";

                if (chr == '\n')
                {
                    strcpy(temp, "\n");
                }
                else
                {
                    temp[0] = chr;

                    if (LED_DRIVER_OK == led_driver_set_state((chr == ON) ? LED_DRIVER_HIGH : LED_DRIVER_LOW))
                    {
                        strcpy(temp + 1, DONE_MSG);
                    }
                    else
                    {
                        strcpy(temp + 1, FAILED_MSG);
                    }
                }

                bsp_serial_print(temp);
                show_message = true;
            }
        }
    }
}
