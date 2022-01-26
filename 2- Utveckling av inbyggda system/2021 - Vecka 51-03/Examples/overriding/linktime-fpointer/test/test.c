#include <unity.h>
#include "module.h"
#include "double.h"

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

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_free_memory);

    return UNITY_END();
}
