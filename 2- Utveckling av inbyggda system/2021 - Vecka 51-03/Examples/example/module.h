#ifndef MODULE_H
#define MODULE_H

#include <stdlib.h>

typedef struct person person_t;

person_t *module_create(int age, const char *name);

int module_get_age(person_t *ptr);

char *module_get_name(person_t *ptr);

void module_destroy(person_t *ptr);

#endif
