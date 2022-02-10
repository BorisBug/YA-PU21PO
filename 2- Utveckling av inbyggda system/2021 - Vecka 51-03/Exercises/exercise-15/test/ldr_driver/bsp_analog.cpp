#include "bsp_analog.h"

// NOTICE!!!!!!!!
// For the LDR we don't need to include Arduino and read the actual value from the pin.
// Because the LDR can not provide test data for us. Instead double_stub_digital_value() is the function
// we use to provide test data.

static int pin_value = 0;
static uint8_t pin_num = 0xFF;
static uint8_t resolution = 0xFF;

void bsp_analog_read_resolution(uint8_t bits)
{
    resolution = bits;
}

int bsp_analog_read(uint8_t pin)
{
    pin_num = pin;
    return pin_value;
}

void double_stub_digital_value(int value)
{
    pin_value = value;
}

uint8_t double_get_pin_num(void)
{
    return pin_num;
}

uint8_t double_get_resolutuin(void)
{
    return resolution;
}
