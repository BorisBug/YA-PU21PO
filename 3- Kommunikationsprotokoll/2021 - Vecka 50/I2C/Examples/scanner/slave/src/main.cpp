#include <i2c_t3.h>

#define ADDRESS 0x25

void requestEvent(void)
{
}

void receiveEvent(size_t length)
{
}

void setup()
{
    Wire.begin(I2C_SLAVE, ADDRESS, I2C_PINS_18_19, I2C_PULLUP_INT);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
}
