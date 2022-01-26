#include <string.h>
#include "module.h"
#include "m1.h"

struct person
{
    int age;
    char name[32];
};

static char _name[32] = {0};

person_t *module_create(int age, const char *name)
{
    person_t *ptr = (person_t *)malloc(sizeof(person_t));

    if (ptr != NULL)
    {
        ptr->age = age;
        strncpy(ptr->name, name, 31);
    }

    return ptr;
}

int module_get_age(person_t *ptr)
{
    int age = -1;
    if (ptr != NULL)
    {
        age = ptr->age;
    }
    return age;
}

char *module_get_name(person_t *ptr)
{
    if (ptr != NULL)
    {
        memset(_name, 0, sizeof(_name));
        strcpy(_name, ptr->name);
    }

    return _name;
}

// A square IS A/AN shape
// A car HAS A/AN number of wheels

void module_destroy(person_t *ptr)
{
    if (ptr != NULL)
    {
        free(ptr);
    }
}
