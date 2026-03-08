#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/* -------------------------------------------------
 * insert_at_first
 * -------------------------------------------------
 */

int insert_at_first(int data, Dlist **head, Dlist **tail)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head)
        (*head)->prev = new;
    else
        *tail = new;

    *head = new;
    return SUCCESS;
}

/* -------------------------------------------------
 * insert_at_last
 * -------------------------------------------------
 */

int insert_at_last(int data, Dlist **head, Dlist **tail)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new)
        return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*tail)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;
    return SUCCESS;
}

/* -------------------------------------------------
 * delete_list
 * -------------------------------------------------
 */

void delete_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    while (*head)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}

/* -------------------------------------------------
 * print_list
 * -------------------------------------------------
 */

void print_list(Dlist *head)
{
    if (!head)
        return;

    /* handle negative result */
    if (head->data < 0)
    {
        printf("-");
        head->data *= -1;
    }

    while (head)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}
