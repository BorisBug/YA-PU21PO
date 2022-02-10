#include "list.h"
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

struct llist
{
    node_t *head;
    size_t available;
};

list_t *list_create(void)
{
    list_t *list = (list_t *)malloc(sizeof(list_t));

    if (list != NULL)
    {
        list->available = 0;
        list->head = NULL;
    }

    return list;
}

list_status_t list_available(list_t *list, size_t *available)
{
    list_status_t status = LIST_INVALID_POINTER;

    if ((list != NULL) && (available != NULL))
    {
        *available = list->available;
        status = LIST_OKAY;
    }

    return status;
}

list_status_t list_insert(list_t *list, int data)
{
    list_status_t status = LIST_INVALID_POINTER;

    if (list != NULL)
    {
        // Find position of the new node
        node_t *current = list->head;
        node_t *previous = NULL;

        while (current != NULL)
        {
            if (current->data >= data)
            {
                break;
            }
            previous = current;
            current = current->next;
        }

        status = LIST_DATA_DUPLICATE;

        if ((current == NULL) || (current->data != data))
        {
            status = LIST_MEMORY_ERROR;

            // Create a node
            node_t *new_node = (node_t *)malloc(sizeof(node_t));

            if (new_node != NULL)
            {
                list->available++;
                status = LIST_OKAY;

                new_node->data = data;
                new_node->next = NULL;

                // Add the node to
                if (current == NULL && previous == NULL)
                {
                    // the empty list
                    list->head = new_node;
                }
                else if (current != NULL && previous == NULL)
                {
                    // the begining of the list
                    list->head = new_node;
                    new_node->next = current;
                }
                else if (current == NULL && previous != NULL)
                {
                    // the end of the list
                    previous->next = new_node;
                }
                else
                {
                    // before current node
                    new_node->next = current;
                    previous->next = new_node;
                }
            }
        }
    }

    return status;
}

list_status_t list_find(list_t *list, int data, size_t *position)
{
    list_status_t status = LIST_INVALID_POINTER;

    if ((list != NULL) && (position != NULL))
    {
        size_t counter = 0;
        node_t *cursor = list->head;
        status = LIST_DATA_NOT_FOUND;

        while (cursor != NULL)
        {
            counter++;

            if (cursor->data == data)
            {
                *position = counter;
                status = LIST_OKAY;
                break;
            }

            cursor = cursor->next;
        }
    }

    return status;
}

list_status_t list_nth_data(list_t *list, size_t position, int *data)
{
    list_status_t status = LIST_INVALID_POINTER;

    if ((list != NULL) && (data != NULL))
    {
        size_t pos = 1;
        node_t *cursor = (position > 0) ? list->head : NULL;

        while ((pos < position) && (cursor != NULL))
        {
            cursor = cursor->next;
            pos++;
        }

        if (cursor == NULL)
        {
            status = LIST_INVALID_POSITION;
        }
        else
        {
            status = LIST_OKAY;
            *data = cursor->data;
        }
    }

    return status;
}

list_status_t list_delete(list_t *list, int data)
{
    list_status_t status = LIST_INVALID_POINTER;

    if (list != NULL)
    {
        node_t *previous = NULL;
        node_t *current = list->head;
        status = LIST_DATA_NOT_FOUND;

        while (current != NULL)
        {
            if (current->data == data)
            {
                if (previous == NULL)
                {
                    list->head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                list->available--;
                status = LIST_OKAY;
                free(current);
                break;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }

    return status;
}

list_status_t list_edit(list_t *list, int old_data, int new_data)
{
    list_status_t status = LIST_INVALID_POINTER;

    if (list != NULL)
    {
        size_t pos = 0;
        status = LIST_DATA_DUPLICATE;

        if (LIST_DATA_NOT_FOUND == list_find(list, new_data, &pos))
        {
            status = LIST_DATA_NOT_FOUND;

            if (LIST_OKAY == list_delete(list, old_data))
            {
                status = list_insert(list, new_data);
            }
        }
    }

    return status;
}

void list_destroy(list_t **list)
{
    if ((list != NULL) && (*list != NULL))
    {
        node_t *current = (*list)->head;

        while (current != NULL)
        {
            (*list)->head = current->next;
            free(current);
            current = (*list)->head;
        }

        free(*list);
        *list = NULL;
    }
}
