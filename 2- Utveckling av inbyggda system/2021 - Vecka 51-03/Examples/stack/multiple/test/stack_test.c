#include "stack.h"
#include <unity.h>

static stack_t *stack = NULL;

void setUp(void) {}

void tearDown(void)
{
    stack_destroy(&stack);
}

void test_create_stacks(void)
{
    stack = stack_create(10);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_UINT16(10, stack_size(stack));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));

    TEST_ASSERT_NULL(stack_create(0));
    TEST_ASSERT_EQUAL_UINT16(0, stack_size(NULL));
    TEST_ASSERT_EQUAL_INT32(-1, stack_available(NULL));

    stack_t *temp = stack_create(20);
    TEST_ASSERT_NOT_NULL(temp);
    TEST_ASSERT_EQUAL_UINT16(20, stack_size(temp));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(temp));

    stack_destroy(&temp);
    TEST_ASSERT_NULL(temp);

    stack_destroy(NULL);
    stack_destroy(&temp);
}

void test_stack_push_clear(void)
{
    stack = stack_create(10);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_UINT16(10, stack_size(stack));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));

    TEST_ASSERT_TRUE(stack_push(stack, 20));
    TEST_ASSERT_EQUAL_INT32(1, stack_available(stack));

    TEST_ASSERT_TRUE(stack_clear(stack));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));

    TEST_ASSERT_FALSE(stack_clear(NULL));

    TEST_ASSERT_FALSE(stack_push(NULL, 100));

    uint16_t size = stack_size(stack);
    for (int i = 1; i <= size; i++)
    {
        TEST_ASSERT_TRUE(stack_push(stack, i));
        TEST_ASSERT_EQUAL_INT32(i, stack_available(stack));
    }
    TEST_ASSERT_FALSE(stack_push(stack, 100));
}

void test_stack_push_pop(void)
{
    stack = stack_create(10);
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_UINT16(10, stack_size(stack));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));

    TEST_ASSERT_TRUE(stack_push(stack, 20));
    TEST_ASSERT_EQUAL_INT32(1, stack_available(stack));

    uint8_t data = 0;
    TEST_ASSERT_TRUE(stack_pop(stack, &data));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));
    TEST_ASSERT_EQUAL_UINT8(20, data);

    TEST_ASSERT_FALSE(stack_pop(stack, &data));

    TEST_ASSERT_FALSE(stack_pop(NULL, &data));
    TEST_ASSERT_FALSE(stack_pop(NULL, NULL));
    TEST_ASSERT_TRUE(stack_push(stack, 20));
    TEST_ASSERT_EQUAL_INT32(1, stack_available(stack));
    TEST_ASSERT_FALSE(stack_pop(stack, NULL));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_create_stacks);
    RUN_TEST(test_stack_push_clear);
    RUN_TEST(test_stack_push_pop);

    return UNITY_END();
}
