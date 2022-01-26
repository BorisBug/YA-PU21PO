#include <stdio.h>
#include "module.h"

int main(void)
{
    person_t *eva = module_create(20, "Eva");

    if (eva != NULL)
    {
        printf("%s is %d years old!\n", module_get_name(eva), module_get_age(eva));
    }

    m1_get_value();

    return 0;
}
