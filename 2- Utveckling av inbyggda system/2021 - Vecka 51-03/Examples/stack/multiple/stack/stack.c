#include "stack.h"
#include <stdlib.h>

struct stack
{
    int32_t top;
    uint16_t size;
    uint8_t *array;
};

stack_t *stack_create(uint16_t size)
{
    stack_t *stck = NULL;

    if (size > 0)
    {
        uint8_t *array = (uint8_t *)malloc(size * sizeof(uint8_t));

        if (array != NULL)
        {
            stck = (stack_t *)malloc(sizeof(stack_t));

            if (stck == NULL)
            {
                free(array);
            }
            else
            {
                stck->array = array;
                stck->size = size;
                stck->top = -1;
            }
        }
    }

    return stck;
}

uint16_t stack_size(stack_t *stck)
{
    uint16_t size = 0;

    if (stck != NULL)
    {
        size = stck->size;
    }

    return size;
}

bool stack_clear(stack_t *stck)
{
    bool status = false;

    if (stck != NULL)
    {
        stck->top = -1;
        status = true;
    }

    return status;
}

int32_t stack_available(stack_t *stck)
{
    int32_t available = -1;

    if (stck != NULL)
    {
        available = stck->top + 1;
    }

    return available;
}

bool stack_push(stack_t *stck, uint8_t data)
{
    bool status = false;

    if (stck != NULL)
    {
        if (stck->top < stck->size - 1)
        {
            stck->top++;
            status = true;
            stck->array[stck->top] = data;
        }
    }

    return status;
}

bool stack_pop(stack_t *stck, uint8_t *data)
{
    bool status = false;

    if ((stck != NULL) && (data != NULL))
    {
        if (stck->top > -1)
        {
            *data = stck->array[stck->top];
            stck->top--;
            status = true;
        }
    }

    return status;
}

void stack_destroy(stack_t **stck)
{
    if ((stck != NULL) && (*stck != NULL))
    {
        free((*stck)->array);
        free(*stck);
        *stck = NULL;
    }
}
