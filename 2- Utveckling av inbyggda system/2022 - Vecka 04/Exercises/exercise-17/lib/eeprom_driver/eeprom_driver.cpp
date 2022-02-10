#include "bsp.h"
#include <stdlib.h>
#include "eeprom_driver.h"

static uint16_t used = 0;
static uint16_t space = 0;

static void write_nbytes(uint16_t address, uint8_t *data, uint16_t size);
static void read_nbytes(uint16_t address, uint8_t *buffer, uint16_t size);

void eeprom_driver_init(bool reset)
{
    space = eeprom_init();
    if (reset)
    {
        used = 0;
        write_nbytes(0, (uint8_t *)&used, sizeof(used)); // The word is used to store the used bytes
    }
    else
    {
        read_nbytes(0, (uint8_t *)&used, sizeof(used)); // The word is used to store the used bytes
    }
}

uint8_t eeprom_driver_read(uint16_t address, uint8_t *buffer, uint16_t length)
{
    uint8_t status = EEPROM_DRIVER_ERROR;

    if ((buffer != NULL) && (length > 0) && (address + length <= used))
    {
        read_nbytes(address + sizeof(used), buffer, length);
        status = EEPROM_DRIVER_OKEY;
    }

    return status;
}

uint8_t eeprom_driver_write(uint16_t address, uint8_t *data, uint16_t length)
{
    uint8_t status = EEPROM_DRIVER_ERROR;

    if ((data != NULL) && (length > 0) && (address + sizeof(used) + length < space))
    {
        write_nbytes(address + sizeof(used), data, length);

        if (address + length > used)
        {
            used += length;
            write_nbytes(0, (uint8_t *)&used, sizeof(used));
        }

        status = EEPROM_DRIVER_OKEY;
    }

    return status;
}

static void write_nbytes(uint16_t address, uint8_t *data, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        eeprom_write(address + i, data[i]);
    }
}

static void read_nbytes(uint16_t address, uint8_t *buffer, uint16_t size)
{
    for (uint16_t i = 0; i < size; i++)
    {
        buffer[i] = eeprom_read(address + i);
    }
}
