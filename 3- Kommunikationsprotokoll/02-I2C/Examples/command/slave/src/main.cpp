#include <i2c_t3.h>

#define ON '1'
#define OFF '0'
#define ADDRESS 0x00

static volatile char state = '0';

void requestEvent(void)
{
    Wire.write(state);
}

void receiveEvent(size_t length)
{
    uint8_t data = 0;
    Wire.read(&data, sizeof(data));
    if ((data == OFF) || (data == ON))
    {
        digitalWrite(LED_BUILTIN, (data == ON) ? HIGH : LOW);
        state = digitalRead(LED_BUILTIN) ? ON : OFF;
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Wire.begin(I2C_SLAVE, ADDRESS, I2C_PINS_18_19, I2C_PULLUP_INT);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop()
{
}
