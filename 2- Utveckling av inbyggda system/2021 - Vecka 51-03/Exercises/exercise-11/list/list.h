/**
 * @file list.h
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief A multiple-instance linked list module of unique and sorted elements.
 * @version 0.1
 * @date 2021-05-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct llist list_t;

typedef enum
{
    LIST_OKAY = 0,
    LIST_MEMORY_ERROR,
    LIST_INVALID_POINTER,
    LIST_INVALID_POSITION,
    LIST_DATA_NOT_FOUND,
    LIST_DATA_DUPLICATE,
} list_status_t;

/**
 * @brief This function is used to create a new linked list;
 *
 * @return NULL if an error occurrs; else a pointer to the created empty list.
 */
list_t *list_create(void);

/**
 * @brief his function is used to insert a data element into a linked list.
 * sdsdsd
 * @param list A pointer to the list
 * @param data An integer to insert.
 * @return LIST_INVALID_POINTER if list is NULL,
 *         LIST_MEMORY_ERROR if memory allocation fails,
 *         LIST_DATA_DUPLICATE if data is daplicate,
 *         LIST_OKAY if data is inserted into the list
 */
list_status_t list_insert(list_t *list, int data);

/**
 * @brief This function returns number of the elements in a list.
 *
 * @param list A pointer to the list
 * @param available A pointer to store number of the available data elements
 * @return LIST_INVALID_POINTER if list or available is NULL; else LIST_OKAY
 */
list_status_t list_available(list_t *list, size_t *available);

/**
 * @brief This function is used to search for a data in a list.
 *
 * @param list A pointer to the list
 * @param data The integer to search for
 * @param position A pointer to store the position of data in the list.
 *                 If data does not exist in the list, position will be 0
 * @return LIST_INVALID_POINTER if list or position is NULL,
 *         LIST_DATA_NOT_FOUND if data not found; else LIST_OKAY
 */
list_status_t list_find(list_t *list, int data, size_t *position);

/**
 * @brief This function is used to get the data value of the nth element in a list.
 *
 * @param list A pointer to the list
 * @param position The nth element. position shall be a valid position and greater than 0
 * @param data A pointer to store the data in the nth element of the list.
 * @return LIST_INVALID_POINTER if list or data is NULL,
 *         LIST_INVALID_POSITION if position is invalid; otherwise LIST_OKAY
 */
list_status_t list_nth_data(list_t *list, size_t position, int *data);

/**
 * @brief This function is used to delete an element in a list
 *
 * @param list A pointer to the list
 * @param data The data value of a node
 * @return LIST_INVALID_POINTER if list is NULL,
 *         LIST_DATA_NOT_FOUND if data does not exist in the list; otherwise LIST_OKAY
 */
list_status_t list_delete(list_t *list, int data);

/**
 * @brief This function is used to change data in a list.
 *
 * @param list A pointer to the list
 * @param old_data The old data value
 * @param new_data The new data value
 * @return LIST_INVALID_POINTER if list is NULL,
 *         LIST_MEMORY_ERROR if memory allocation fails
 *         LIST_DATA_NOT_FOUND if old_data does not exist in the list,
 *         LIST_DATA_DUPLICATE if new_data already exists in the list; otherwise LIST_OKAY
 */
list_status_t list_edit(list_t *list, int old_data, int new_data);

/**
 * @brief This function is used to destroy a linked list.
 *
 * @param list A double pointer to the list
 */
void list_destroy(list_t **list);

#endif /* LIST_H */
