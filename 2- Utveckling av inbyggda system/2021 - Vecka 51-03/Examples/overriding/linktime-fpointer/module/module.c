#include "module.h"

static int *data_ptr = NULL;
static free_t free_memory = free;

void module_begin(free_t func)
{
    free_memory = (func == NULL) ? free : func;
    data_ptr = (int *)malloc(sizeof(int));
}

void module_end(void)
{
    if (data_ptr != NULL)
    {
        free_memory(data_ptr);
        data_ptr = NULL;
    }
}
