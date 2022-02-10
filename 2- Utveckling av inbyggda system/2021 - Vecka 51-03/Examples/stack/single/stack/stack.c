#include "stack.h"

#if ((STACK_SIZE < 1) || (STACK_SIZE > 1024))
#error STACK_SIZE shall be an integer in the range of 1 and 1024
#endif

static int top = -1;
static int stack[STACK_SIZE] = {0};

void stack_clear(void)
{
    top = -1;
}

bool stack_push(int value)
{
    bool status = false;

    if (top < (STACK_SIZE - 1))
    {
        top++;
        status = true;
        stack[top] = value;
    }

    return status;
}

bool stack_pop(int *elem)
{
    bool status = false;

    if (top > -1)
    {
        *elem = stack[top];
        status = true;
        top--;
    }

    return status;
}

int stack_available(void)
{
    return (top + 1);
}
