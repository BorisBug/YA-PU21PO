#ifndef RNGA_H
#define RNGA_H

#include <stdint.h>

/**
 * @brief This function is used to initialize the RNGA.
 */
void rnga_init(void);

/**
 * @brief This function is used to start the RNGA.
 * 
 */
void rnga_start(void);

/**
 * @brief This function is used to seed the RNGA
 * 
 * @param seed The entropy value
 */
void rnga_seed(uint32_t seed);

/**
 * @brief This function is used to generate a random number within a range
 * 
 * @param min The min of the range
 * @param max The max of the range
 * @return uint32_t The random generated number
 */
uint32_t rnga_generate(uint32_t min, uint32_t max);

/**
 * @brief This function is used to stop the RNGA.
 * 
 */
void rnga_stop(void);

#endif