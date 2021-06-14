/*
 * LinkedListIntersection.c
 *
 *  Created on: Jun. 12, 2021
 *      Author: Emil Fanache
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct List_t List;

struct List_t
{
    List *_next;
    int _info;
};

List* List_createNode(int value);
void List_addNode(List** head, int value);
void List_deleteAll(List** head);
void List_printAll(List* head, const char *message);


List* List_createNode(int value)
{
    List* lst = (List*) malloc(sizeof(List));
    if (!lst)
    {
        printf("Error allocating memory for a node\n");
        return NULL;
    }

    lst->_info = value;
    lst->_next = NULL;

    return lst;
}

void List_addNode(List** head, int value)
{
    if (!*head)
    {
        *head = List_createNode(value);
        return;
    }
    else
    {
        List* node = List_createNode(value);
        if (!node)
        {
            return;
        }
        List* lst = *head;
        while (lst->_next != NULL)
        {
            if (lst->_info >= node->_info)
            {
                break;
            }
            lst = lst->_next;
        }

        if (lst->_next == NULL)
        {
            /* end node */
            lst->_next = node;
        }
        else /* intermediary node */
        {
            node->_next = lst->_next;
            lst->_next = node;
        }
    }
}

void List_deleteAll(List** head)
{
    List* current = *head;
    List* node = NULL;

    while (current != NULL)
    {
        node = current;
        current = current->_next;
        if (node)
        {
            free(node);
            node = NULL;
        }
    }

    current = NULL;
}

void List_printAll(List* head, const char *message)
{
    if (message)
    {
        printf("%s\n", message);
    }

    while (head != NULL)
    {
        printf("%d ", head->_info);
        head = head->_next;
    }
    printf("\n");
}


void List_printAllAddr(List* head, const char *message)
{
    if (message)
    {
        printf("%s\n", message);
    }

    while (head != NULL)
    {
        printf("%p ", head);
        head = head->_next;
    }
    printf("\n");
}

/*
 * The inefficient method where you search each node in the second list
 */
List* LinkedListIntersection(List *first, List *second)
{
    List *node_f = first;
    List *node_s = second;

    if (!node_f || !node_s)
    {
        return NULL;
    }

    if (node_f == node_s)
    {
        return node_f;
    }

    while (node_f != node_s)
    {
        node_s = second;
        while (node_s != NULL)
        {
            if (node_f == node_s)
            {
                return node_f;
            }
            node_s = node_s->_next;
        }

        node_f = node_f->_next;
    }

    return NULL;
}

/*
 * A more efficient method where once one of the list reaches the end
 * it's pointer goes to the head of the other list.
 */
List* LinkedListIntersection_second(List *first, List *second)
{
    List *node_f = first;
    List *node_s = second;

    if (!node_f || !node_s)
    {
        return NULL;
    }

    while (node_f != node_s)
    {
        node_f = (node_f != NULL ? node_f->_next : second);
        node_s = (node_s != NULL ? node_s->_next : first);
    }

    return node_f;
}


int main(void)
{
    List* head_f = NULL;
    List* head_s = NULL;
    List* head_f_copy = NULL;
    List* head_s_copy = NULL;
    List* intersection_node = NULL;

    List_addNode(&head_f, 1);

    List_addNode(&head_f, 2);
    List_addNode(&head_f, 3);
    List_addNode(&head_f, 4);

    List_addNode(&head_s, 6);
    List_addNode(&head_s, 7);
    List_addNode(&head_s, 8);
    List_addNode(&head_s, 9);

    head_f_copy = head_f;
    head_s_copy = head_s;
    /* go to the end of the first list */
    while (head_f_copy->_next != NULL)
    {
        head_f_copy = head_f_copy->_next;
    }

    /* advance 2 nodes in the second list */
    head_s_copy = head_s_copy->_next->_next;

    /* now create a list intersection */
    head_f_copy->_next = head_s_copy;

    List_printAll(head_f, "Print first list");
    List_printAllAddr(head_f, "First list addresses");
    List_printAll(head_s, "Print second list");
    List_printAllAddr(head_s, "Second list addresses");

    intersection_node = LinkedListIntersection(head_f, head_s);
    if (!intersection_node)
    {
        printf("No intersection between the 2 lists\n");
    }
    else
    {
        printf("The two lists intersect at node %d\n", intersection_node->_info);
    }

    printf("\nSecond method of finding the intersection node\n");
    intersection_node = LinkedListIntersection_second(head_f, head_s);
    if (!intersection_node)
    {
        printf("No intersection between the 2 lists\n");
    }
    else
    {
        printf("The two lists intersect at node %d\n", intersection_node->_info);
    }

    // split the 2 lists so I can free the memory without overlpaping
    head_f_copy = head_f;
    while ((head_f_copy->_next != intersection_node) && (head_f_copy != NULL))
    {
        head_f_copy = head_f_copy->_next;
    }
    head_f_copy->_next = NULL;
    List_printAll(head_f, "Print first list after spliting");
    List_printAll(head_s, "Print the second list after spliting");

    List_deleteAll(&head_f);
    List_deleteAll(&head_s);

    printf("\nDone\n");
    return 1;
}
