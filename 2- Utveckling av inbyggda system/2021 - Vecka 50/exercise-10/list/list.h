/**
 * @file list.h
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief A linked list of unique and sorted elements.
 * @version 0.1
 * @date 2021-05-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief This function is used to insert an element in the list.
 *
 * @param data The integer to insert.
 * @return bool - true if value is unique and inserted successfully; otherwise false
 */
bool list_insert(int data);

/**
 * @brief This function returns number of the elements in the list.
 *
 * @return size_t - Number of the available elements
 */
size_t list_available(void);

/**
 * @brief This function is used to search for a data in the list.
 *
 * @param data The integer to search for.
 * @return size_t - 0 if data is not in the list; otherwise the position of the data in the list.
 */
size_t list_find(int data);

/**
 * @brief This function is used to get the data stored of the nth element of the list.
 *
 * @param n The nth element. n shall be a valid position and greater than 0
 * @param ptr An int pointer which holds address of a variable to store the data in.
 * @return bool true if n is not valid; otherwise false
 */
bool list_get_data(size_t n, int *ptr);

/**
 * @brief This function is used to delete an element in the list
 *
 * @param data The data value of a node
 * @return bool - false if data does not exist; otherwise true
 */
bool list_delete(int data);

/**
 * @brief This function is used to change data in the list.
 *
 * @param old_data The old data value
 * @param new_data The new data value
 * @return bool - false if old_data does not exist or new_data already exists; otherwise true
 */
bool list_edit(int old_data, int new_data);

/**
 * @brief This function is used to free the allocated memory for all the nodes.
 *
 */
void list_reset(void);

#endif /* LIST_H */
