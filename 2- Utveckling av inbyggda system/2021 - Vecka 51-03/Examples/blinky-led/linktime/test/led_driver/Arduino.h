#ifndef Arduino_h
#define Arduino_h

#include <stdint.h>
#include <stdbool.h>

#define OUTPUT 1

uint8_t digitalRead(uint8_t pin);
void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);

// Helper functions
uint8_t arduino_get_pin_num(void);
uint8_t arduino_get_pin_mode(void);
uint8_t arduino_get_pin_state(void);
void arduino_set_pin_status(bool status);

#endif /* Arduino_h */
