/**
 * @file string-bdd.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief An example of black-box testing.
 *
 * @version 0.1
 * @date 2021-05-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <unity.h>
#include <string.h>

#define MAX_LENGTH 64

static char actual[MAX_LENGTH] = {0};

void setUp(void)
{
    memset(actual, 0, sizeof(actual));
}

void tearDown(void)
{
}

void test_strlen(void)
{
    TEST_ASSERT_EQUAL_size_t(0, strlen(""));
    TEST_ASSERT_EQUAL_size_t(11, strlen("Test String"));
}

void test_sprintf_empty_string(void)
{
    sprintf(actual, "%s", "");
    TEST_ASSERT_EQUAL_STRING("", actual);
}

void test_sprintf_insert_string(void)
{
    sprintf(actual, "Insert %s", "String");
    TEST_ASSERT_EQUAL_STRING("Insert String", actual);
}

void test_sprintf_insert_mixed(void)
{
    sprintf(actual, "%d + %d %c %d", 20, 30, '=', 50);
    TEST_ASSERT_EQUAL_STRING("20 + 30 = 50", actual);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_strlen);
    RUN_TEST(test_sprintf_empty_string);
    RUN_TEST(test_sprintf_insert_string);
    RUN_TEST(test_sprintf_insert_mixed);

    return UNITY_END();
}
