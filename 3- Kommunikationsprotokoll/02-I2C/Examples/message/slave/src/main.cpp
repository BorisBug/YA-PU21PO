#include <i2c_t3.h>

#define ADDRESS 0x00
#define BUFFER_SIZE 128

static volatile uint8_t tx_counter = 0;
static char tx_buffer[BUFFER_SIZE] = {};

void requestEvent(void)
{
    if (tx_buffer[tx_counter] == '\n')
    {
        int length = strlen(tx_buffer) + 1;
        if (length != Wire.write(tx_buffer, length))
        {
            Serial.println("Failed to send the data!");
        }
        memset(tx_buffer, 0, BUFFER_SIZE);
        tx_counter = 0;
    }
}

void receiveEvent(size_t length)
{
    if (length < I2C_RX_BUFFER_LENGTH)
    {
        char data[I2C_RX_BUFFER_LENGTH] = {0};
        Serial.printf("%s", (length == Wire.read(data, length)) ? data : "Failed to read data!\n");
    }
}

void setup()
{
    Serial.begin(9600);
    delay(2000);

    Wire.begin(I2C_SLAVE, ADDRESS, I2C_PINS_18_19, I2C_PULLUP_INT);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
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
}
