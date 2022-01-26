#include <EEPROM.h>
#include <Arduino.h>

void setup()
{
  float f = 0.0f;    // Variable to store data read from EEPROM.
  int eeAddress = 0; // EEPROM address to start reading from

// If you wan to store change 0 to 1, and if you want to read the stored value it should be 0
#if 0 // Store f in the EEPROM
  f = 2.50f;
  EEPROM.put(eeAddress, f);

#else // Read f from the EEPROM
  Serial.begin(9600);
  while (!Serial.dtr())
  {
    ;
  }
  // Get the float data from the EEPROM at position 'eeAddress'
  EEPROM.get(eeAddress, f);
  Serial.printf("Read float from EEPROM: %f\n", f);
#endif
}

void loop()
{
}
