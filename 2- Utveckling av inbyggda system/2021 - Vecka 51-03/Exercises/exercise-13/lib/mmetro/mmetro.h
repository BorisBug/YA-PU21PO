#ifndef MMETRO_H
#define MMETRO_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define MMETRO_NO (0U)
#define MMETRO_YES (1U)
#define MMETRO_ERROR (2U)

typedef struct
{
    void *(*malloc)(size_t);  // Function pointer to malloc
    uint32_t (*micros)(void); // Function pointer to micros
    uint32_t (*millis)(void); // Function pointer to millis
} bsp_interface_t;

typedef struct mmetro mmetro_t; // mmetro_t is a forward declared abstracted data type

/**
 * @brief This function is used to initialize the interfaces
 *
 * @param bsp_ptr A function pointer to the bsp fuctions interface. If it is NULL, free, malloc the Arduino millis and micros functions are used.
 */
void mmetro_init(bsp_interface_t *bsp_ptr);

/**
 * @brief This function is used to create a mmetro
 *
 * @param mu If it is true, the created metro measures milliseconds; otherwise microseconds
 * @param interval The interval to check if it is passed or not
 * @return mmetro_t* - NULL if an error occurres; otherwis a pointer to the created mmetro.
 */
mmetro_t *mmetro_create(bool mu, uint32_t interval);

/**
 * @brief This function is used to check if the interval of a metro has been passed or not
 *
 * @param metro A pointer to the metro
 * @return uint8_t - MMETRO_ERROR if metro is invalid, MMETRO_YES if the interval from the last call has been passed; otherwise MMETRO_NO
 */
uint8_t mmetro_check(mmetro_t *metro);

/**
 * @brief This function is used to reset the internal previous time of a metro
 *
 * @param metro A pointer to the metro. If it is NULL, nothing happens
 */
void mmetro_reset(mmetro_t *metro);

#endif /* MMETRO_H */