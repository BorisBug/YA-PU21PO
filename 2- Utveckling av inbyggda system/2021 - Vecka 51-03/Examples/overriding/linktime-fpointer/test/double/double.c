#include <stdio.h>
#include <stdlib.h>
#include "double.h"

void my_free(void *ptr)
{
    printf("\nmy_free is called!\n\n");
    free(ptr);
}
