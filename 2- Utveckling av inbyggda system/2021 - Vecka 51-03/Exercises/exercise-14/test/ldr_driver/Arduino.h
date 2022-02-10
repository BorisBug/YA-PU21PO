#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>

void analogReadResolution(uint8_t bits);
int analogRead(uint8_t pin);

// Utility functions
uint8_t arduino_get_pin_num(void);
uint8_t arduino_get_resolutuin(void);
void arduino_set_pin_value(int value);

#endif /* Arduino_h */
