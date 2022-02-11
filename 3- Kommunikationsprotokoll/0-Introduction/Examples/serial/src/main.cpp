#include <Arduino.h>

void setup() // This function is used to initialize the modules
{
    Serial.begin(9600); // This function is used to initialized the usb serial. Bit rate is 9600.
    delay(2000);        // The usb serial initialization takes time. 2 sec is enough.
}

void loop()
{
    if (Serial.available()) // Check if something is avaiable in the input buffer.
    {
        char ch = Serial.read(); // Read a character
        Serial.print(ch);        // Print the read character to the termoinal
    }
}
