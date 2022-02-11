#include <TSPISlave.h>

#define SPI_SCK 14

static TSPISlave slave = TSPISlave(SPI, PIN_SPI_MISO, PIN_SPI_MOSI, SPI_SCK, PIN_SPI_SS);

void receive(void)
{
    while (slave.active())
    {
        if (slave.available())
        {
            uint8_t data = slave.popr();
            slave.pushr(toupper(data));
        }
    }
}

void setup()
{
    Serial.begin(9600);
    delay(2000);

    slave.onReceive(receive);
}

void loop()
{
}
