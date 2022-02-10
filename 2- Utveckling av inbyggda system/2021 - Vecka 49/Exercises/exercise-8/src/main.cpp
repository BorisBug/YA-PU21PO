/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 8. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Arduino.h>

#define KILO 1000
#define ADC_RESOLUTION 12                                              // The resolution of the ADC.
#define VOLTAGE_REFERENCE 3.3f                                         // The voltage reference of the ADC
#define LDR_MIN_RESISTANCE (4 * KILO)                                  // The resistance of the LDR in 10 lux(1.0 ftc) is something between 4 kΩ and 7 kΩ
#define LDR_MAX_RESISTANCE (7 * KILO)                                  // The resistance of the LDR in 10 lux(1.0 ftc) is something between 4 kΩ and 7 kΩ
#define RESISTOR_RESISTANCE (4.7f * KILO)                              // The resistance of the resistor
#define VOLTAGE_RESOLUTION (VOLTAGE_REFERENCE / (1 << ADC_RESOLUTION)) // The voltage resolution of the ADC

// A variable to store state of the built in LED
static uint8_t led_state = LOW;

void setup()
{
    // Initialize and begin the USB serial communication
    Serial.begin(9600);

    // Wait until the serial communication gets initialized and started
    delay(2000);

    // Set the mode of the LED pin to OUTPUT
    pinMode(LED_BUILTIN, OUTPUT);

    // Set the resolution of the ADC
    analogReadResolution(ADC_RESOLUTION);
}

void loop()
{
    // Read the analog pin and convert it to voltage
    float voltage = analogRead(A14) * VOLTAGE_RESOLUTION;

    // Calculate the resistance of the LDR
    float ldr_resistance = RESISTOR_RESISTANCE * (VOLTAGE_REFERENCE - voltage) / voltage;

    // Print the resistance of the LDR to the terminal
    Serial.printf("The resistance of the LDR is %.3f kΩ\n", ldr_resistance / KILO);

    if (ldr_resistance < LDR_MIN_RESISTANCE)
    {
        /**
         * If the resistance of the LDR is lesser than 2 kΩ,
         * it means that the light intensity is greater than 10 lux(1.0 ftc)
         * and therefore the LED will blink
         */
        led_state = !led_state;
    }
    else if (ldr_resistance > LDR_MAX_RESISTANCE)
    {
        /**
         * If the resistance of the LDR is greater than 6 kΩ,
         * it means that the light intensity is lesser than 10 lux(1.0 ftc)
         * and therefore the LED will be turned on
         */
        led_state = HIGH;
    }
    else
    {
        /**
         * If the resistance of the LDR is between 2 kΩ and 6 kΩ,
         * it means that the light intensity is almost 10 lux(1.0 ftc)
         * and therefore the LED will be turned off
         */
        led_state = LOW;
    }

    // Change the state of the LED
    digitalWrite(LED_BUILTIN, led_state);

    // Wait 500 milliseconds
    delay(500);
}
