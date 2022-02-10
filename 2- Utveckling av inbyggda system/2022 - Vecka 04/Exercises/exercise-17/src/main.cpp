#include <Arduino.h>
#include <eeprom_driver.h>

void setup()
{
    Serial.begin(9600);
    while (!Serial.dtr())
    {
        ;
    }

    float f = 0.0f;
    uint32_t data = 0;
    uint8_t address = 0;

#if 0 // If you want to clear and write some data, change 0 to 1

    eeprom_driver_init(true); // Clear the data in the eeprom

    data = 0x12345678U;
    eeprom_driver_write(address, (uint8_t *)&data, sizeof(data));
    address += sizeof(data);

    data = 0x87654321U;
    eeprom_driver_write(address, (uint8_t *)&data, sizeof(data));
    address += sizeof(data);

    f = 23.56f;
    eeprom_driver_write(address, (uint8_t *)&f, sizeof(f));

#else
    eeprom_driver_init(false);

    data = 0;
    eeprom_driver_read(address, (uint8_t *)&data, sizeof(data));
    address += sizeof(data);
    Serial.println(data, HEX);

    data = 0;
    eeprom_driver_read(address, (uint8_t *)&data, sizeof(data));
    address += sizeof(data);
    Serial.println(data, HEX);

    f = 0.0f;
    eeprom_driver_read(address, (uint8_t *)&f, sizeof(f));
    Serial.println(f);
#endif
}

void loop()
{
}
