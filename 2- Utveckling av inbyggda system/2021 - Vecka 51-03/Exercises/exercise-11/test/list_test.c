#include "list.h"
#include <unity.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static list_t *list = NULL;

void setUp(void) {}

void tearDown(void)
{
    list_destroy(&list);
}

static void insert_into_list(list_t *lst, int *array, size_t len)
{
    size_t available = 0;
    for (size_t i = 0; i < len; i++)
    {
        TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_insert(lst, array[i]));
        TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(lst, &available));
        TEST_ASSERT_EQUAL_size_t(i + 1, available);
    }
}

void test_list_create(void)
{
    size_t available = ~(0U);

    list = list_create();
    TEST_ASSERT_NOT_NULL(list);

    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_available(NULL, &available));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_available(list, NULL));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_available(NULL, NULL));

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(list, &available));
    TEST_ASSERT_EQUAL_size_t(0, available);

    available = ~(0U);
    list_t *temp = list_create();
    TEST_ASSERT_NOT_NULL(temp);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(temp, &available));
    TEST_ASSERT_EQUAL_size_t(0, available);

    list_destroy(&temp);
    TEST_ASSERT_NULL(temp);

    list_destroy(NULL);
    list_destroy(&temp);
}

void test_list_insert(void)
{
    size_t available = ~(0U);

    list = list_create();
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(list, &available));
    TEST_ASSERT_EQUAL_size_t(0, available);

    int data[] = {10, 2, 8, 20};
    insert_into_list(list, data, ARRAY_SIZE(data));

    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_insert(NULL, 30));

    TEST_ASSERT_EQUAL_INT(LIST_DATA_DUPLICATE, list_insert(list, 10)); // Test for a duplicate value

    // Check if the list is sorted
    int value = 0;

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 1, &value));
    TEST_ASSERT_EQUAL_INT(2, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 2, &value));
    TEST_ASSERT_EQUAL_INT(8, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 3, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 4, &value));
    TEST_ASSERT_EQUAL_INT(20, value);

    // Test for invalid parameters
    value = 0;
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_nth_data(NULL, 1, &value));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_nth_data(NULL, 1, NULL));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_nth_data(list, 1, NULL));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POSITION, list_nth_data(list, 40, &value));
    TEST_ASSERT_EQUAL_INT(0, value);

    list_destroy(&list);
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_available(list, &available));
}

void test_list_find(void)
{
    list = list_create();
    TEST_ASSERT_NOT_NULL(list);

    size_t position = 0;
    int data[] = {10, 2, 8, 20};
    insert_into_list(list, data, ARRAY_SIZE(data));

    // Test for invalid parameters
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_find(NULL, 2, &position));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_find(list, 2, NULL));
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_find(NULL, 2, NULL));
    TEST_ASSERT_EQUAL_INT(LIST_DATA_NOT_FOUND, list_find(list, 40, &position));

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_find(list, 8, &position));
    TEST_ASSERT_EQUAL_size_t(2, position);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_find(list, 10, &position));
    TEST_ASSERT_EQUAL_size_t(3, position);
}

void test_list_delete(void)
{
    list = list_create();
    TEST_ASSERT_NOT_NULL(list);

    int data[] = {10, 2, 8, 20};
    insert_into_list(list, data, ARRAY_SIZE(data));

    // Test for invalid parameters
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_delete(NULL, 8));
    TEST_ASSERT_EQUAL_INT(LIST_DATA_NOT_FOUND, list_delete(list, 30));

    size_t available = 0;
    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_delete(list, 8));
    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(list, &available));
    TEST_ASSERT_EQUAL_size_t(3, available);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_insert(list, 5));
    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(list, &available));
    TEST_ASSERT_EQUAL_size_t(4, available);

    // Check if the list is still sorted
    int value = 0;

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 1, &value));
    TEST_ASSERT_EQUAL_INT(2, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 2, &value));
    TEST_ASSERT_EQUAL_INT(5, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 3, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 4, &value));
    TEST_ASSERT_EQUAL_INT(20, value);

    for (size_t i = available; i > 0; i--)
    {
        TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, i, &value));
        TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_delete(list, value));
        TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_available(list, &available));
        TEST_ASSERT_EQUAL_size_t(i - 1, available);
    }
}

void test_list_edit(void)
{
    list = list_create();
    TEST_ASSERT_NOT_NULL(list);

    int data[] = {10, 2, -8, 20};
    insert_into_list(list, data, ARRAY_SIZE(data));

    // Test for invalid parameters
    TEST_ASSERT_EQUAL_INT(LIST_INVALID_POINTER, list_edit(NULL, -8, 8));
    TEST_ASSERT_EQUAL_INT(LIST_DATA_NOT_FOUND, list_edit(list, 30, 60));
    TEST_ASSERT_EQUAL_INT(LIST_DATA_DUPLICATE, list_edit(list, 2, -8));

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_edit(list, -8, 8));

    // Check if the list is still sorted
    int value = 0;

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 1, &value));
    TEST_ASSERT_EQUAL_INT(2, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 2, &value));
    TEST_ASSERT_EQUAL_INT(8, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 3, &value));
    TEST_ASSERT_EQUAL_INT(10, value);

    TEST_ASSERT_EQUAL_INT(LIST_OKAY, list_nth_data(list, 4, &value));
    TEST_ASSERT_EQUAL_INT(20, value);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_list_create);
    RUN_TEST(test_list_insert);
    RUN_TEST(test_list_find);
    RUN_TEST(test_list_delete);
    RUN_TEST(test_list_edit);

    return UNITY_END();
}
