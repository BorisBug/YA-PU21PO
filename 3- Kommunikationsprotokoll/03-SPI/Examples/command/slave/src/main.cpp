#include <TSPISlave.h>

#define ON '1'
#define OFF '0'
#define SPI_SCK 14

TSPISlave slave = TSPISlave(SPI, PIN_SPI_MISO, PIN_SPI_MOSI, SPI_SCK, PIN_SPI_SS);

void receive(void)
{
    while (slave.active())
    {
        if (slave.available())
        {
            uint16_t value = 0;
            uint8_t data = slave.popr();
            if ((data == OFF) || (data == ON))
            {
                digitalWrite(LED_BUILTIN, (data == ON) ? HIGH : LOW);
                value = digitalRead(LED_BUILTIN) ? ON : OFF;
            }
            slave.pushr(value);
        }
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    slave.onReceive(receive);
}

void loop()
{
}
