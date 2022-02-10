#include "stack.h"
#include <unity.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC_BOTH_SUCCESS 1
#define MALLOC_FIRST_FAILED 2
#define MALLOC_SECOND_FAILED 3

#define MAX_MALLOC_CALLS (32U) // Max. number of calls to malloc by the tests

static uint16_t counter = 0;                        // A counter used for storing non-NULL pointers returned by malloc
static stack_t *stack = NULL;                       // A stack pointer used in the tests
static void *malloc_ptr = NULL;                     // The pointer returned by malloc.
static void *pointers[MAX_MALLOC_CALLS] = {0};      /* An array to store all the poinetrs which point to successfully allocated memories by malloc.
                                                        We use this array to check if all the allocated memories are freed by the destroy function or not. */
static uint8_t malloc_status = MALLOC_BOTH_SUCCESS; // A variable to control the behaviour of malloc. If we want to force malloc to fail

void setUp(void)
{
    counter = 0;
    malloc_ptr = NULL;
    malloc_status = MALLOC_BOTH_SUCCESS;
    memset(pointers, 0, sizeof(pointers)); // Set all the pointers to NULL
}

void tearDown(void)
{
    stack_destroy(&stack);

    // Ensure that all the allocated memories were freed.
    for (size_t i = 0; i < MAX_MALLOC_CALLS; i++)
    {
        TEST_ASSERT_NULL(pointers[i]);
    }
}

// The test double for the standard free function.
// We need to spy on the free function
static void dfree(void *ptr)
{
    free(ptr); // The real free function in stdlib

    // Find and set the pointer to the freed memory to NULL
    for (size_t i = 0; i < MAX_MALLOC_CALLS; i++)
    {
        if (pointers[i] == ptr)
        {
            pointers[i] = NULL;
        }
    }
}

// The test double for the standard malloc function.
// We need to spy on the malloc function
static void *dmalloc(size_t size)
{
    malloc_ptr = NULL;

    // If malloc_status is not MALLOC_BOTH_SUCCESS or MALLOC_SECOND_FAILED, the function returns NULL and we can test dynamic memory allocation failures.
    if ((malloc_status == MALLOC_BOTH_SUCCESS) || (malloc_status == MALLOC_SECOND_FAILED))
    {
        if (malloc_status == MALLOC_SECOND_FAILED)
        {
            malloc_status = MALLOC_FIRST_FAILED;
        }

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

void test_create_stacks(void)
{
    // Test if a dynamic memory allocation fails
    malloc_status = MALLOC_FIRST_FAILED; // To enforce the first call to malloc in stack_create fails
    stack = stack_create(5);
    TEST_ASSERT_NULL(stack);

    malloc_status = MALLOC_SECOND_FAILED; // To enforce the second call to malloc in stack_create fails
    stack = stack_create(5);
    TEST_ASSERT_NULL(stack);

    malloc_status = MALLOC_BOTH_SUCCESS; // To use the real dynamic memory allocation by malloc, malloc_status shall be true

    stack = stack_create(10);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, stack); // Test if stack is equal to malloc_ptr returned by the real malloc function. malloc_ptr can or can not be NULL.
    TEST_ASSERT_EQUAL_UINT16(10, stack_size(stack));
    TEST_ASSERT_EQUAL_INT32(0, stack_available(stack));

    TEST_ASSERT_NULL(stack_create(0));
    TEST_ASSERT_EQUAL_UINT16(0, stack_size(NULL));
    TEST_ASSERT_EQUAL_INT32(-1, stack_available(NULL));

    stack_t *temp = stack_create(20);
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, temp);
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
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, stack);
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
    TEST_ASSERT_EQUAL_PTR(malloc_ptr, stack);
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

#ifdef DEVENV
int main(void)
{
#else
void loop()
{
}

void setup()
{
#endif
    stack_init(dfree, dmalloc); // Initialize the module with the test doubles

    UNITY_BEGIN();

    RUN_TEST(test_create_stacks);
    RUN_TEST(test_stack_push_clear);
    RUN_TEST(test_stack_push_pop);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}
