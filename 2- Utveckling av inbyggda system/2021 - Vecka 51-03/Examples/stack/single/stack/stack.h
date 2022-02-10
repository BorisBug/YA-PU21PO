#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_SIZE 10 // Size of the stack

/**
 * @brief This function is used to clear the stack
 *
 */
void stack_clear(void);

/**
 * @brief This function returns the number of available data elements in the stack
 *
 * @return int The number of data elements to pop
 */
int stack_available(void);

/**
 * @brief This function is used to insert an element in the stack.
 *
 * @param value The data to push to the stack
 * @return bool - false if the stack is full; otherwise true
 */
bool stack_push(int value);

/**
 * @brief This function is used to pop the top element in the stack
 *
 * @param elem A pointer to an int to fill with the top element
 * @return bool - false if the stack is empty; otherwise true
 */
bool stack_pop(int *elem);

#endif /* STACK_H */
