#include "list.h"
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node_t;

static node_t *head = NULL;
static size_t available = 0;

bool list_insert(int data)
{
    bool status = false;

    // Find position of the new node
    node_t *current = head;
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

    if ((current == NULL) || (current->data != data))
    {
        // Create a node
        node_t *new_node = (node_t *)malloc(sizeof(node_t));

        if (new_node != NULL)
        {
            available++;
            status = true;

            new_node->data = data;
            new_node->next = NULL;

            // Add the node to
            if (current == NULL && previous == NULL)
            {
                // the empty list
                head = new_node;
            }
            else if (current != NULL && previous == NULL)
            {
                // the begining of the list
                head = new_node;
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

    return status;
}

size_t list_available(void)
{
    return available;
}

size_t list_find(int data)
{
    size_t counter = 0;
    size_t position = 0;
    node_t *cursor = head;

    while (cursor != NULL)
    {
        counter++;

        if (cursor->data == data)
        {
            position = counter;
            break;
        }

        cursor = cursor->next;
    }

    return position;
}

bool list_get_data(size_t n, int *ptr)
{
    size_t position = 1;
    node_t *cursor = (n > 0) ? head : NULL;

    while ((position < n) && (cursor != NULL))
    {
        cursor = cursor->next;
        position++;
    }

    if (cursor != NULL)
    {
        *ptr = cursor->data;
    }

    return (cursor != NULL);
}

bool list_delete(int data)
{
    bool status = false;
    node_t *current = head;
    node_t *previous = NULL;

    while (current != NULL)
    {
        if (current->data == data)
        {
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            available--;
            free(current);
            status = true;
            break;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }

    return status;
}

bool list_edit(int old_data, int new_data)
{
    bool status = false;

    if (0 == list_find(new_data))
    {
        if (list_delete(old_data))
        {
            status = list_insert(new_data);
        }
    }

    return status;
}

void list_reset(void)
{
    while (head != NULL)
    {
        node_t *next = head->next;
        free(head);
        head = next;
    }
    available = 0;
}
