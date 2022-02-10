#include <TSPISlave.h>

#define SPI_SCK 14
#define BUFFER_SIZE 128

static uint8_t rx_counter = 0;
static volatile uint8_t tx_counter = 0;
static char rx_buffer[BUFFER_SIZE] = {0};
static char tx_buffer[BUFFER_SIZE] = {0};
TSPISlave slave = TSPISlave(SPI, PIN_SPI_MISO, PIN_SPI_MOSI, SPI_SCK, PIN_SPI_SS);

void receive(void)
{
    while (slave.active())
    {
        if (slave.available())
        {
            uint8_t data = (uint8_t)slave.popr();
            if (data != 0)
            {
                slave.pushr(0);
                rx_buffer[rx_counter] = data;
                if ((data == '\n') || (rx_counter > BUFFER_SIZE - 2))
                {
                    rx_buffer[rx_counter] = '\n';
                    Serial.printf("\n%s", rx_buffer);
                    memset(rx_buffer, 0, BUFFER_SIZE);
                    rx_counter = 0;
                }
                else
                {
                    rx_counter++;
                }
            }
            else if ((data == 0) && (tx_buffer[tx_counter] == '\n'))
            {
                static char *ptr = tx_buffer;
                if (*ptr)
                {
                    slave.pushr(*ptr);
                    if (*ptr == '\n')
                    {
                        memset(tx_buffer, 0, BUFFER_SIZE);
                        ptr = tx_buffer;
                        tx_counter = 0;
                    }
                    else
                    {
                        ptr++;
                    }
                }
                else
                {
                    slave.pushr(0);
                }
            }
            else
            {
                slave.pushr(0);
            }
        }
    }
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    slave.onReceive(receive);

    Serial.begin(9600);
    delay(2000);
}

void loop()
{
    if (Serial.available())
    {
        char chr = Serial.read();
        if (chr == '\r')
        {
            chr = Serial.read();
        }

        if (chr && (tx_buffer[tx_counter] != '\n'))
        {
            if ((chr != '\n') || (*tx_buffer != 0))
            {
                if (tx_counter == BUFFER_SIZE - 2)
                {
                    chr = '\n';
                    tx_buffer[tx_counter] = chr;
                }
                else
                {
                    tx_buffer[tx_counter] = chr;
                    if (chr != '\n')
                    {
                        tx_counter++;
                    }
                }

                Serial.print(chr);
            }
        }
    }
}
