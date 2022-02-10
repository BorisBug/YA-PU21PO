# Beskrivning
Make a program

ESP32 generates a random string (32 lowercase characters) every second.
Print the string to the terminal.
Send the string to Teensy via SPI
On Teensy the received string shall be converted to uppercase and send it back to ESP32 via SPI
ESP32 shall display the received string from Teensy to the terminal
To generate random numbers, you can use the random function of Arduino.

# SPI

## Connections

Teensy(Slave) ........... ESP32(Master)

SS(10) .................. SS(33)

MISO(12) ................ MOSI(18)

MOSI(11) ................ MISO(19)

SCK(14) ................. SCK(5)

GND ..................... GND
