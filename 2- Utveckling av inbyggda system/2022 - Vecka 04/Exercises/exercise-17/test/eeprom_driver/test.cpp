#ifndef DEVENV
#include <Arduino.h>
#endif
#include "bsp.h"
#include <unity.h>
#include "eeprom_driver.h"

void setUp(void)
{
    eeprom_driver_init(true);
}

void tearDown(void) {}

void test_eeprom_driver_init(void)
{
    uint16_t address = 0;
    uint32_t data = 0x12345678;

    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_write(address, (uint8_t *)&data, sizeof(data)));

    uint32_t temp = 0;
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_read(address, (uint8_t *)&temp, sizeof(temp)));
    TEST_ASSERT_EQUAL_UINT32(data, temp);

    temp = 0;
    eeprom_driver_init(false);
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_read(address, (uint8_t *)&temp, sizeof(temp)));
    TEST_ASSERT_EQUAL_UINT32(data, temp);
}

void test_eeprom_driver_invalid_read(void)
{
    uint32_t data = 0;
    uint16_t address = 0;

    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_read(address, NULL, sizeof(data)));
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_read(address, (uint8_t *)&data, 0));
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_read(address, (uint8_t *)&data, sizeof(data)));
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_read(address, (uint8_t *)&data, EEPROM_LENGTH));
}

void test_eeprom_driver_invalid_write(void)
{
    uint32_t data = 0x12345678;
    uint16_t address = EEPROM_LENGTH;

    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_write(address, NULL, sizeof(data)));
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_write(address, (uint8_t *)&data, 0));
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_ERROR, eeprom_driver_write(0, (uint8_t *)&data, EEPROM_LENGTH));

    address = 0;
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_write(address, (uint8_t *)&data, sizeof(data)));

    address += sizeof(data);
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_write(address, (uint8_t *)&data, sizeof(data)));

    address = 0;
    TEST_ASSERT_EQUAL_UINT8(EEPROM_DRIVER_OKEY, eeprom_driver_write(address, (uint8_t *)&data, sizeof(data)));
}

int main(void)
{
#ifndef DEVENV
    delay(3000);
#endif

    UNITY_BEGIN();

    RUN_TEST(test_eeprom_driver_init);
    RUN_TEST(test_eeprom_driver_invalid_read);
    RUN_TEST(test_eeprom_driver_invalid_write);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();

    while (1)
    {
        ;
    }
#endif
}
