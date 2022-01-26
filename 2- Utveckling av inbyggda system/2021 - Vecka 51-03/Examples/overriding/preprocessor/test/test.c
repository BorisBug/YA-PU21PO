#include <unity.h>
#include "module.h"
#include "double.h"

void test_get_string(void)
{
    const char *user_input = "User Input";

    set_iobuf(user_input);

    TEST_ASSERT_EQUAL_STRING(user_input, get_string());
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_get_string);

    return UNITY_END();
}
