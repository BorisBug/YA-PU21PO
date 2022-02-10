#include <SPI.h>
#include <Arduino.h>

#define PIN_SPI_SS 33
#define BUFFER_SIZE 128
#define CLOCK_RATE 1000000

static uint8_t rx_counter = 0;
static uint8_t tx_counter = 0;
static char rx_buffer[BUFFER_SIZE] = {0};
static char tx_buffer[BUFFER_SIZE] = {0};
static SPISettings setting = SPISettings(CLOCK_RATE, MSBFIRST, SPI_MODE0);

void setup()
{
    pinMode(PIN_SPI_SS, OUTPUT);
    digitalWrite(PIN_SPI_SS, HIGH);

    Serial.begin(9600);
    SPI.begin();
    delay(2000);
}

void loop()
{
    if (Serial.available())
    {
        char chr = Serial.read();
        if (chr == '\r')
        {
            chr = '\n';
            while (Serial.available())
            {
                Serial.read();
            }
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

    SPI.beginTransaction(setting);
    digitalWrite(PIN_SPI_SS, LOW);

    if (tx_buffer[tx_counter] == '\n')
    {
        for (char *ptr = tx_buffer; *ptr != 0; ptr++)
        {
            SPI.transfer(*ptr);
        }

        tx_counter = 0;
        memset(tx_buffer, 0, BUFFER_SIZE);
    }

    uint8_t data = SPI.transfer(0);
    if (data != 0)
    {
        rx_buffer[rx_counter] = data;
        if ((data == '\n') || (rx_counter > BUFFER_SIZE - 2))
        {
            rx_buffer[rx_counter] = '\n';
            Serial.printf("\n%s", rx_buffer);
            rx_counter = 0;
            memset(rx_buffer, 0, BUFFER_SIZE);
        }
        else
        {
            rx_counter++;
        }
    }

    digitalWrite(PIN_SPI_SS, HIGH);
    SPI.endTransaction();
}
