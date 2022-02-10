#include "list.h"
#include <unity.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

void setUp(void) {}

void tearDown(void)
{
    list_reset();
}

static void insert_into_list(int *array, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        TEST_ASSERT_TRUE(list_insert(array[i]));
        TEST_ASSERT_EQUAL_size_t(i + 1, list_available());
    }
}

void test_list_insert(void)
{
    TEST_ASSERT_EQUAL_size_t(0, list_available());

    int data[] = {10, 2, 8, 20};
    insert_into_list(data, ARRAY_SIZE(data));

    TEST_ASSERT_FALSE(list_insert(20)); // Test for a duplicate value

    // Check if the list is sorted
    int value = 0;
    TEST_ASSERT_TRUE(list_get_data(1, &value));
    TEST_ASSERT_EQUAL_INT(2, value);

    TEST_ASSERT_TRUE(list_get_data(2, &value));
    TEST_ASSERT_EQUAL_INT(8, value);

    TEST_ASSERT_TRUE(list_get_data(3, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_TRUE(list_get_data(4, &value));
    TEST_ASSERT_EQUAL_INT(20, value);

    // Test for invalid positions
    TEST_ASSERT_FALSE(list_get_data(0, &value));
    TEST_ASSERT_FALSE(list_get_data(10, &value));

    list_reset();
    TEST_ASSERT_EQUAL_size_t(0, list_available());
}

void test_list_find(void)
{
    TEST_ASSERT_FALSE(list_find(40)); // Test for a non-existing value (when the list is empty)

    int data[] = {30, 5, 10};
    insert_into_list(data, ARRAY_SIZE(data));

    TEST_ASSERT_EQUAL_size_t(1, list_find(5));
    TEST_ASSERT_EQUAL_size_t(3, list_find(30));

    TEST_ASSERT_EQUAL_size_t(0, list_find(40)); // Test for a non-existing value
}

void test_list_delete(void)
{
    TEST_ASSERT_FALSE(list_delete(33)); // Test for a non-existing value (when the list is empty)

    int data[] = {10, 2, -8, 20};
    insert_into_list(data, ARRAY_SIZE(data));

    TEST_ASSERT_FALSE(list_delete(33)); // Test for a non-existing value

    TEST_ASSERT_TRUE(list_delete(-8));
    TEST_ASSERT_EQUAL_size_t(3, list_available());

    TEST_ASSERT_TRUE(list_insert(-8));
    TEST_ASSERT_EQUAL_size_t(4, list_available());

    TEST_ASSERT_TRUE(list_delete(2));
    TEST_ASSERT_EQUAL_size_t(3, list_available());

    TEST_ASSERT_TRUE(list_insert(1));
    TEST_ASSERT_EQUAL_size_t(4, list_available());

    TEST_ASSERT_TRUE(list_insert(8));

    size_t available = list_available();
    TEST_ASSERT_EQUAL_size_t(5, available);

    // Check if the list is still sorted
    int value = 0;
    TEST_ASSERT_TRUE(list_get_data(1, &value));
    TEST_ASSERT_EQUAL_INT(-8, value);

    TEST_ASSERT_TRUE(list_get_data(2, &value));
    TEST_ASSERT_EQUAL_INT(1, value);

    TEST_ASSERT_TRUE(list_get_data(3, &value));
    TEST_ASSERT_EQUAL_INT(8, value);

    TEST_ASSERT_TRUE(list_get_data(4, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_TRUE(list_get_data(5, &value));
    TEST_ASSERT_EQUAL_INT(20, value);

    for (ssize_t i = available; i > 0; i--)
    {
        TEST_ASSERT_TRUE(list_get_data(i, &value));
        TEST_ASSERT_TRUE(list_delete(value));
        TEST_ASSERT_EQUAL_size_t(i - 1, list_available());
    }
}

void test_list_edit(void)
{
    TEST_ASSERT_FALSE(list_edit(33, 1)); // Test for a non-existing value (when the list is empty)

    int data[] = {10, 2, -8, 20};
    insert_into_list(data, ARRAY_SIZE(data));

    TEST_ASSERT_TRUE(list_edit(-8, 8));

    TEST_ASSERT_FALSE(list_edit(5, 50)); // Test for non-existing value. 5 does not exist in the list
    TEST_ASSERT_FALSE(list_edit(8, 20)); // Test for an already existing new value. 8 and 20 DOES exist in the list

    // Check if the list is still sorted
    int value = 0;
    TEST_ASSERT_TRUE(list_get_data(1, &value));
    TEST_ASSERT_EQUAL_INT(2, value);

    TEST_ASSERT_TRUE(list_get_data(2, &value));
    TEST_ASSERT_EQUAL_INT(8, value);

    TEST_ASSERT_TRUE(list_get_data(3, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_TRUE(list_get_data(4, &value));
    TEST_ASSERT_EQUAL_INT(20, value);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_find);
    RUN_TEST(test_list_delete);
    RUN_TEST(test_list_edit);

    return UNITY_END();
}
