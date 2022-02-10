# ESP32 and Teensy 3.5 - NTP & RTC

## Connections

Teensy(Slave) ........... ESP32(Master)

SDA(18) .................. SDA(23)

SCL(19) .................. SCL(22)

GND ...................... GND

## Requirements

Make a program for ESP32 to

    1. Get the current date and time from an NTP server

    2. Initialize the RTC of ESP32 with the received date and time from the NTP server

    3. Send the current date and time to Teensy via I2C.

Make a program for Teensy 3.5 to

    1. Receive date and time from ESP32 via I2C

    2. Initialize the RTC of Teensy

    3. Print the current time to the terminal every second;

Date and time format shall be YYYY-MM-DD hh:mm:ss
