#include "bsp_analog.h"
#include "ldr_driver.h"

#define VOLTAGE_REFERENCE 3.3f                                         // The voltage reference of the ADC
#define VOLTAGE_RESOLUTION (VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION)) // The voltage resolution of the ADC

// This function is used to map value in the range of [from_min, from_max] to the range of [to_min, to_max]
static inline uint8_t map_value(float value, uint32_t from_min, uint32_t from_max, uint8_t to_min, uint8_t to_max)
{
    return ((value - from_min) * (to_max - to_min) / (from_max - from_min) + to_min);
}

static uint8_t pin_num = 0xFF;

void ldr_driver_init(uint8_t pin)
{
    pin_num = pin;
    bsp_analog_read_resolution(ADC_RESOLUTION);
}

uint8_t ldr_driver_get_intensity(void)
{
    // Read the data from the analog pin and convert it to voltage
    float voltage = bsp_analog_read(pin_num) * VOLTAGE_RESOLUTION;

    // Calculate the resistance of the LDR
    float ldr_resistance = RESISTOR_RESISTANCE * (VOLTAGE_REFERENCE - voltage) / voltage;

    uint8_t intensity = 0;

    if (ldr_resistance <= LDR_RESISTANCE_MAX)
    {
        intensity = 100;

        if (ldr_resistance > LDR_RESISTANCE_MIN)
        {
            // Convert the resistance to a percentage
            intensity -= map_value(ldr_resistance, LDR_RESISTANCE_MIN, LDR_RESISTANCE_MAX, 0, 100);
        }
    }

    return intensity;
}
