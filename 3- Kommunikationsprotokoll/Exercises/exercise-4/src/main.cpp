#include <FlexCAN.h> // To read more about FlexCAN look at chapter 49 in https://www.pjrc.com/teensy/K64P144M120SF5RM.pdf
#include <Arduino.h>
#include <IntervalTimer.h>

#define MESSAGES 3       // Number of the messages
#define BAUD_RATE 250000 // CAN speed

#define INTERVAL_TX 50
#define INTERVAL_RX 500

static IntervalTimer timer;

static CAN_message_t messages[MESSAGES] = {
    {.id = 0x100, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
    {.id = 0x101, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
    {.id = 0x111, .timestamp = 0, .flags = {.extended = 0, .remote = 0, .overrun = 0, .reserved = 0}, .len = 8, .buf = {0}},
};

static void timing(void)
{
    static uint32_t counter = 0;

    for (uint8_t i = 0; i < MESSAGES; i++)
    {
        Can0.write(messages[i]);
    }

    counter++;

    if (counter == INTERVAL_RX / INTERVAL_TX)
    {
        counter = 0;

        if (Can0.available())
        {
            CAN_message_t message;
            while (Can0.read(message))
            {
                Serial.printf("Received - ID: 0x%03X, DLC: %d bytes, Data: ", message.id, message.len);
                for (int i = 0; i < message.len; ++i)
                {
                    Serial.printf("%c", message.buf[i]);
                }
                Serial.printf("\n");
            }
        }
    }
}

void setup()
{
    Serial.begin(9600);
    delay(2000);

    // Fill the buffers
    memcpy(messages[0].buf, "ABCDEFGH", messages[0].len);
    memcpy(messages[1].buf, "IJKLMNOP", messages[1].len);
    memcpy(messages[2].buf, "QRSTUVWX", messages[2].len);

    Serial.println("\nStarting Can0 in loopback mode ...");

    Can0.loopBack = true;
    Can0.begin(BAUD_RATE);

    Serial.println("Setting the filters...");

    // Set up a blockin filter/mask for all the RX mailboxes
    CAN_filter_t filter = {.id = 0x7FF, .flags = {.extended = 1, .remote = 0, .reserved = 0}}; // The blockin filter

    for (int i = 0; i < NUM_MAILBOXES; ++i)
    {
        Can0.setFilter(filter, i);
        Can0.setMask(0x0U, i);
    }

    // Set up the filter/mask for the first mailbox in order to let the second and third messages in

    filter.id = 0x101; // 0x101  = 001 0000 0001
                       // 0x111  = 001 0001 0001
                       // ----------------------
                       // Filter = 001 0000 0001

    filter.flags.extended = 0;
    Can0.setFilter(filter, 0);

    // 0x101 = 001 0000 0001
    // 0x111 = 001 0001 0001
    // ---------------------
    // Mask  = 111 1110 1111

    Can0.setMask(0x7EF << 18, 0); // 0x101, 0x111 are passed; 3 msb bits are reserved

    timer.begin(timing, INTERVAL_RX * 1000);
}

void loop()
{
}
