#ifndef MODULE_H
#define MODULE_H

#include <stdlib.h>

typedef void (*free_t)(void *);

void module_begin(free_t func);
void module_end(void);

#endif /* MODULE_H */
