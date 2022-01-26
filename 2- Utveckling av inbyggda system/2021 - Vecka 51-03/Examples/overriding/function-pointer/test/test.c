#include <unity.h>
#include "module.h"

static void my_free(void *ptr)
{
    printf("\nTest Code: my_free is called\n\n");
    free(ptr);
}

void setUp()
{
    module_begin(my_free);
}

void tearDown()
{
    module_end();
}

void test_free_memory()
{
    TEST_IGNORE();
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_free_memory);

    return UNITY_END();
}
