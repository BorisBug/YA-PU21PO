#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef void (*free_t)(void *);    // Function pointer to free
typedef void *(*malloc_t)(size_t); // Function pointer to malloc

typedef struct stack stack_t; // stack_t is a forward declared abstracted data type

/**
 * @brief This function is used to initialize the interfaces
 *
 * @param free_ptr A function pointer for free function. If it is NULL the standard free function is is used.
 * @param malloc_ptr A function pointer for malloc function. If it is NULL the standard malloc function is is used.
 */
void stack_init(free_t free_ptr, malloc_t malloc_ptr);

/**
 * @brief This function is used to create a stack
 *
 * @param size The capacity of the stack
 * @return stack_t* - NULL if an error occurres; otherwis a pointer to the created stack.
 */
stack_t *stack_create(uint16_t size);

/**
 * @brief This function returns size of the stack
 *
 * @param stck A pointer to the stack
 * @return uint16_t - 0 if stck is invalid; otherwise size of the stack
 */
uint16_t stack_size(stack_t *stck);

/**
 * @brief This function is used to clear a stack
 *
 * @param stck A pointer to the stack
 * @return bool - false if stck is not valid; otherwise true
 */
bool stack_clear(stack_t *stck);

/**
 * @brief This function returns the number of available data elements in the stack
 *
 * @param stck A pointer to the stack
 * @return int32_t -1 if the stck is invalid; otherwise the number of data elements to pop
 */
int32_t stack_available(stack_t *stck);

/**
 * @brief This function is used to insert an element in the stack.
 *
 * @param stck A pointer to the stack
 * @param data The data to push to the stack
 * @return bool - false if the stack is full; otherwise true
 */
bool stack_push(stack_t *stck, uint8_t data);

/**
 * @brief This function is used to pop the top element in the stack
 *
 * @param stck A pointer to the stack
 * @param data A pointer to an placeholder to fill with the top element
 * @return bool - false if the stack is empty; otherwise true
 */
bool stack_pop(stack_t *stck, uint8_t *data);

/**
 * @brief This function is used to destroy a stack
 *
 * @param stck A double pointer to the stack
 */
void stack_destroy(stack_t **stck);

#endif /* STACK_H */
