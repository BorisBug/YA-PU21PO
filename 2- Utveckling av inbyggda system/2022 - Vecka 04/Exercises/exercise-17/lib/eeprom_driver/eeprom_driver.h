#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

#define EEPROM_DRIVER_OKEY 0
#define EEPROM_DRIVER_ERROR 1

/**
 * @brief This function is used to initialize the EEPROM.
 *
 * @param reset True to clear the EEPROM; otherwise false
 */
void eeprom_driver_init(bool reset);

/**
 * @brief This function is used to read data from the EEPROM.
 *
 * @param address The client shall be able to pass the adress to this function.
 * @param buffer The client shall be able to pass
 * @param length is the length size of the array.
 * @return uint8_t The stored value.
 */
uint8_t eeprom_driver_read(uint16_t address, uint8_t *buffer, uint16_t length);

/**
 * @brief This function is used to write a buffer of data to the EEPROM.
 *
 * @param address This is the starting address where you want to store the data.
 * @param data A pointer to the data buffer to store to the EEPROM.
 * @param length Size of the array.
 * @return uint8_t The status.
 */
uint8_t eeprom_driver_write(uint16_t address, uint8_t *data, uint16_t length);

#endif
