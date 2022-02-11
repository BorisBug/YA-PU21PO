#include <Metro.h>
#include <FlexCAN.h>
#include <Arduino.h>

#define MESSAGES (3U)
#define BAUD_RATE (250000U)

// For more info about Metro look at: https://www.pjrc.com/teensy/td_libs_Metro.html
static Metro tx_timer = Metro(50);
static Metro rx_timer = Metro(500);

static CAN_message_t messages[MESSAGES] = {
    {.id = 0x190, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
    {.id = 0x200, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
    {.id = 0x210, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
};

void setup()
{
    Serial.begin(9600);
    delay(2000);

    // Fill the buffers
    memcpy(messages[0].buf, "ABCDEFGH", messages[0].len);
    memcpy(messages[1].buf, "IJKLMNOP", messages[1].len);
    memcpy(messages[2].buf, "QRSTUVWX", messages[2].len);

    Serial.println("\nStarting Can0 ...");
    Can0.begin(BAUD_RATE);

    Serial.println("Setting the filters...");

    // Set up a blockin filter/mask for all the RX mailboxes
    CAN_filter_t filter = {.id = 0x7FF, .flags = {.extended = 1, .remote = 0, .reserved = 0}}; // The blockin filter

    for (int i = 0; i < NUM_MAILBOXES; ++i)
    {
        Can0.setFilter(filter, i);
        Can0.setMask(0x000, i);
    }

    // Set up the filter/mask for the first mailbox in order to let the first message in
    filter.id = 0x100;
    filter.flags.extended = 0;
    Can0.setFilter(filter, 0);
    Can0.setMask(0x7EF << 18, 0); // 0x100, 0x110 are passed; 3 msb bits are reserved
}

void loop()
{
    if (tx_timer.check())
    {
        for (uint8_t i = 0; i < MESSAGES; i++)
        {
            Can0.write(messages[i]);
        }
    }

    if (rx_timer.check())
    {
        if (Can0.available())
        {
            CAN_message_t message;
            while (Can0.read(message))
            {
                Serial.printf("RX - ID: 0x%03X - [%d] - ", message.id, message.len);
                for (int i = 0; i < message.len; ++i)
                {
                    Serial.printf("%c ", message.buf[i]);
                }
                Serial.print("\n");
            }
            Serial.print("\n");
        }
    }
}
