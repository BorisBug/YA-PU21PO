#include <Wire.h>
#include <Arduino.h>

#define SLAVE 0x00
#define BUFFER_SIZE 128
#define CLOCK_RATE 400000

static uint8_t tx_counter = 0;
static uint8_t rx_buffer[BUFFER_SIZE] = {0};
static uint8_t tx_buffer[BUFFER_SIZE] = {0};

void setup()
{
    Serial.begin(9600);
    delay(2000);

    while (!Wire.begin(SDA, SCL, CLOCK_RATE))
    {
        Serial.println("Failed to start I2C!");
        delay(1000);
    }
    Wire.setTimeOut(500);
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

        if ((chr != '\0') && (tx_buffer[tx_counter] != '\n'))
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

    Wire.beginTransmission(SLAVE);

    if (tx_buffer[tx_counter] == '\n')
    {
        Wire.write(tx_buffer, strlen((char *)tx_buffer) + 1);
        if (Wire.lastError())
        {
            Serial.printf("Failed to send. Error = %s\n", Wire.getErrorText(Wire.lastError()));
        }
        tx_counter = 0;
        memset(tx_buffer, 0, BUFFER_SIZE);
    }

    Wire.endTransmission(true);

    delay(10);

    Wire.readTransmission(SLAVE, rx_buffer, BUFFER_SIZE, true);

    if (strlen((char *)rx_buffer))
    {
        Serial.printf("\n%s", rx_buffer);
        memset(rx_buffer, 0, BUFFER_SIZE);
    }
}
