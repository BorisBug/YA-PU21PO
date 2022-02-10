#ifndef BSP_TIME_H
#define BSP_TIME_H

#include <stdint.h>
#include <stdbool.h>

typedef void (*funct_t)(void);

void bsp_time_delay(uint32_t msec);
bool bsp_time_it_begin(funct_t func, uint32_t interval);

#endif /* BSP_TIME_H */
