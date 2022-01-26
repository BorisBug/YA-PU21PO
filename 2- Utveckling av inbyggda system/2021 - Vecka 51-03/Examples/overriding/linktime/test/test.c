#include <unity.h>
#include "module.h"

void setUp()
{
}

void tearDown()
{
}

void test_module_func(void)
{
    module_func();
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_module_func);

    return UNITY_END();
}
