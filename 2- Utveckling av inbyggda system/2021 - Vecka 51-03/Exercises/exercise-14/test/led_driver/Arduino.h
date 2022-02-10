#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>

void analogWrite(uint8_t pin, int val);

// Utility functions
uint8_t arduino_pin_num(void);
uint8_t arduino_pin_pwm(void);

#endif /* Arduino_h */
