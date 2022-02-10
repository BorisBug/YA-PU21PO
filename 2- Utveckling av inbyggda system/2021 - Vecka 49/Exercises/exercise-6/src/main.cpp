/**
 * @file main.cpp
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Exercise 6. Look at circuit.jpg
 * @version 0.1
 * @date 2022-01-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <Metro.h>
#include <Arduino.h>

#define RED_PIN (2)
#define GREEN_PIN (3)
#define BLUE_PIN (4)

static Metro metro = Metro(500);

void setup()
{
	Serial.begin(9600);
	delay(2000);
}

void loop()
{
	if (metro.check())
	{
		uint8_t red = random(255);
		uint8_t green = random(255);
		uint8_t blue = random(255);

		analogWrite(RED_PIN, red);
		analogWrite(GREEN_PIN, green);
		analogWrite(BLUE_PIN, blue);

		Serial.printf("Color: 0x%02X%02X%02X\n", red, green, blue);
	}
}