#include <stdio.h>
#include <stdlib.h>
#include "apc.h"
/* 
 * Name            : Hensilin Rithista S
 * Register Number : 25028_034 
 *
 * ----------------------------------------------------------
 * Function: addition
 * ----------------------------------------------------------
 * Adds two big numbers represented as doubly linked lists.
 *
 * head1, tail1 : First number
 * head2, tail2 : Second number
 * headR, tailR : Result list
 */

int addition(Dlist *head1, Dlist *tail1,
             Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;

    int carry = 0;
    int res;

    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 != NULL && temp2 != NULL)
            res = temp1->data + temp2->data + carry;

        else if (temp1 == NULL && temp2 != NULL)
            res = temp2->data + carry;

        else /* temp1 != NULL && temp2 == NULL */
            res = temp1->data + carry;

        carry = res / 10;
        res = res % 10;

        insert_at_first(res, headR, tailR);

        if (temp1 != NULL)
            temp1 = temp1->prev;

        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    if (carry != 0)
        insert_at_first(carry, headR, tailR);

    return SUCCESS;
}

