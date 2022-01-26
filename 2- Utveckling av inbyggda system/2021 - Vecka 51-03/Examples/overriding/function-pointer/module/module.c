#include "module.h"

static int *ptr = NULL;
static free_t free_memory = free;

void module_begin(free_t func)
{
    free_memory = (func == NULL) ? free : func;

    ptr = (int *)malloc(sizeof(int));
}

void module_end(void)
{
    if (ptr != NULL)
    {
        free_memory(ptr);
        ptr = NULL;
    }
}
