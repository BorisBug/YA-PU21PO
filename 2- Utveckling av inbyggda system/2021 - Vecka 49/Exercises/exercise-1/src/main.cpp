/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 1. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

#define DURATION 1000
#define ADC_RESOLUTION 10                                        // The resolution of the ADC. It can be 8 to 13. By default it is 10 bits
#define VOLTAGE_OFFSET 500                                       // According to the TMP36 sensor we have 0.5 volt (500 millivolts) offset
#define MILLIVOLTS_PER_CELSIUS 10                                // According to the TMP36 sensor every 10 millivolts is 1 grad celsius
#define VOLTAGE_RESOLUTION (1000 * 3.3f / (1 << ADC_RESOLUTION)) // The voltage resolution of the ADC in millivolts

void setup()
{
    // Initial and begin the USB serial communication
    Serial.begin(9600);

    // Wait until the serial communication gets initialized and started
    while (!Serial)
    {
    }

    // Set the ADC resolution
    analogReadResolution(ADC_RESOLUTION);
}

void loop()
{
    /**
     * Wait 1 second (1000 millisecond).
     * The sensor is read every second
     **/
    delay(DURATION);

    // Read the analog pin and convert it to millivolts
    float milliVolts = analogRead(A14) * VOLTAGE_RESOLUTION;

    // Convert the voltage to temperature according to the datasheet of TMP36
    float temperature = (milliVolts - VOLTAGE_OFFSET) / MILLIVOLTS_PER_CELSIUS;

    // Print the temperature to the terminal
    Serial.printf("Temperature: %.2f\n", temperature);
}
