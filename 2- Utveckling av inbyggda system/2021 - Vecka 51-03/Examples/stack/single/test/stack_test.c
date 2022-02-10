#include "stack.h"
#include <unity.h>

void setUp()
{
    stack_clear();
}

void tearDown() {}

void test_stack_clear_push(void)
{
    TEST_ASSERT_EQUAL_INT(0, stack_available());

    for (int i = 0; i < STACK_SIZE; i++)
    {
        TEST_ASSERT_TRUE(stack_push(i));
        TEST_ASSERT_EQUAL_INT(i + 1, stack_available());
    }

    stack_clear();
    TEST_ASSERT_EQUAL_INT(0, stack_available());
}

void test_stack_push_pop(void)
{
    TEST_ASSERT_TRUE(stack_push(10));
    TEST_ASSERT_EQUAL_INT(1, stack_available());

    int value = 0;
    TEST_ASSERT_TRUE(stack_pop(&value));
    TEST_ASSERT_EQUAL_INT(0, stack_available());
    TEST_ASSERT_EQUAL_INT(10, value);
}

void test_stack_empty_full(void)
{
    int value = 0;
    TEST_ASSERT_FALSE(stack_pop(&value));
    TEST_ASSERT_EQUAL_INT(0, value);

    for (int i = 1; i <= STACK_SIZE; i++)
    {
        TEST_ASSERT_TRUE(stack_push(i));
        TEST_ASSERT_EQUAL_INT(i, stack_available());
    }

    TEST_ASSERT_FALSE(stack_push(100));

    for (int i = STACK_SIZE; i > 0; i--)
    {
        TEST_ASSERT_TRUE(stack_pop(&value));
        TEST_ASSERT_EQUAL_INT(i, value);
        TEST_ASSERT_EQUAL_INT(i - 1, stack_available());
    }

    TEST_ASSERT_FALSE(stack_pop(&value));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_stack_clear_push);
    RUN_TEST(test_stack_push_pop);
    RUN_TEST(test_stack_empty_full);

    return UNITY_END();
}
