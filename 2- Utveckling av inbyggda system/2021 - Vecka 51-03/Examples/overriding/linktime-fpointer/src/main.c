#include <stdio.h>
#include "module.h"

int main(void)
{
    module_begin(NULL);
    module_end();

    printf("\nThe module was used in main.c\n");

    return 0;
}
