#include "mmetro.h"
#include <unity.h>
#include <stdlib.h>
#include <string.h>

#ifndef DEVENV
#include <Arduino.h>
#endif

#define MAX_MALLOC_CALLS (8U) // Max. number of calls to malloc by the tests

static uint16_t counter = 0;                   // A counter used for storing non-NULL pointers returned by malloc
static uint32_t current_ms = 0;                // A variable to provide our own milliseconds for millis
static uint32_t current_us = 0;                // A variable to provide our own microseconds for micros
static mmetro_t *metro = NULL;                 // A mmetro pointer used in the tests
static void *malloc_ptr = NULL;                // The pointer returned by malloc.
static bool malloc_success = true;             // A variable to control the behaviour of malloc. If we want to force malloc to fail, this variable shall be false
static void *pointers[MAX_MALLOC_CALLS] = {0}; // An array to store all the poinetrs which point to successfully allocated memories by malloc.
                                               // We use this array to check if all the allocated memories are freed by the destroy function or not.

/**
 * @brief This function is used to free resources allocated for a metro.
 *        In a real application, normally we allocate memory statically and we avoid dynamic memory allocation.
 *        In a real application also a timer is used for the lifetime of the application and it will not be destroyed at all.
 *        This is the reason, the destroy function has not been declared and implemented in the module. But here it has been
 *        implemented for testing sake.
 *
 * @param metro A double pointer to the metro. If it is NULL, nothing happens; otherwise metro will be set to NULL
 */
static void mmetro_destroy(mmetro_t **metro)
{
    free(*metro);

    // Find and set the pointer to the freed memory to NULL
    for (size_t i = 0; i < MAX_MALLOC_CALLS; i++)
    {
        if (pointers[i] == *metro)
        {
            pointers[i] = NULL;
        }
    }

    *metro = NULL;
}

void setUp(void)
{
    counter = 0;
    current_ms = 0;
    current_us = 0;
    malloc_ptr = NULL;
    malloc_success = true;
    memset(pointers, 0, sizeof(pointers)); // Set all the pointers to NULL
}

void tearDown(void)
{
    mmetro_destroy(&metro);

    // Ensure that all the allocated memories were freed.
    for (size_t i = 0; i < MAX_MALLOC_CALLS; i++)
    {
        TEST_ASSERT_NULL(pointers[i]);
    }
}

// The test double for the standard malloc function.
// We need to spy on the malloc function
static void *dmalloc(size_t size)
{
    malloc_ptr = NULL;

    if (malloc_success) // If malloc_success is false, the function returns NULL and we can test dynamic memory allocation failures.
    {
        malloc_ptr = malloc(size); // The real malloc function in stdlib. Now malloc_ptr is the real returned pointer by the real malloc function.

        if (malloc_ptr != NULL) // The real returned pointer by the malloc function can be NULL or a valid address. If it is not NULL, we store it in the array
        {
            counter++;
            TEST_ASSERT_TRUE(counter < MAX_MALLOC_CALLS); // Ensure that we have a valid value for MAX_MALLOC_CALLS
            pointers[counter] = malloc_ptr;               // Store the pointer in the array of pointers
        }
    }

    return malloc_ptr;
}

static uint32_t dmicros(void)
{
    return current_us;
}

static uint32_t dmillis(void)
{
    return current_ms;
}

void test_create_metros(void)
{
    // Test if a dynamic memory allocation fails
    malloc_success = false; // To enforce a dynamic memory allocation fails, malloc_success shall be false
    metro = mmetro_create(true, 100);
    TEST_ASSERT_NULL(metro);
    malloc_success = true; // To use the real dynamic memory allocation by malloc, malloc_success shall be true

    metro = mmetro_create(true, 500);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, metro); // Test if metro is equal to malloc_ptr returned by the real malloc function. malloc_ptr can or can not be NULL.

    TEST_ASSERT_NULL(mmetro_create(false, 0));

    mmetro_t *temp = mmetro_create(true, 250);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, temp);

    mmetro_destroy(&temp);
    TEST_ASSERT_NULL(temp);
}

void test_check_reset_metro(void)
{
    metro = mmetro_create(true, 500);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, metro);

    current_ms = 500;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_ms = 900;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));

    current_ms = 1000;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_ms = 0xFFFFFFF0;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_ms = 10; // The ms register has been overflowed
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));

    current_ms = 484;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro)); // If the metro is check faster than 1ms

    current_ms = 1500;
    mmetro_reset(metro); // Reset the metro
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));

    mmetro_destroy(&metro);
    TEST_ASSERT_NULL(metro);
    TEST_ASSERT_EQUAL_UINT8(MMETRO_ERROR, mmetro_check(metro)); // Test for an invalid metro. metro is NULL

    metro = mmetro_create(false, 500);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, metro);

    current_us = 500;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_us = 900;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));

    current_us = 1000;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_us = 0xFFFFFFF0;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));

    current_us = 10; // The us register has been overflowed
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));

    current_us = 484;
    TEST_ASSERT_EQUAL_UINT8(MMETRO_YES, mmetro_check(metro));
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro)); // If the metro is check faster than 1us

    current_us = 1500;
    mmetro_reset(metro); // Reset the metro
    TEST_ASSERT_EQUAL_UINT8(MMETRO_NO, mmetro_check(metro));
}

#ifdef DEVENV
int main(void)
{
#else
void loop()
{
}

void setup()
{
    delay(3000);
#endif

    bsp_interface_t bsp = {.malloc = dmalloc, .micros = dmicros, .millis = dmillis};

    mmetro_init(&bsp); // Initialize the module with the test doubles

    UNITY_BEGIN();

    RUN_TEST(test_create_metros);
    RUN_TEST(test_check_reset_metro);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}
