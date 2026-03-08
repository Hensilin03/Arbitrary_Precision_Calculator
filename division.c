#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/*
 * Name            : Hensilin Rithista S
 * Register Number : 25028_034 
 *
 * ----------------------------------------------------------
 * Function: division
 * -----------------------------------------------------------
 * Divides two big numbers represented as double linked lists
 * using repeated subtraction (integer division only).
 */

int division(Dlist *head1, Dlist *tail1,
             Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR)
{
    int count = 0;                        // stores how many times divisor fits into dividend

    Dlist *tempH = NULL, *tempT = NULL;   // temporary list for subtraction result

    /* if dividend < divisor → result = 0 */
    if (compare(head1, head2) < 0)
    {
        insert_at_first(0, headR, tailR);
        return SUCCESS;
    }

    //repeated subtraction loop as long as: dividend ≥ divisor
    while (compare(head1, head2) >= 0)
    {
        /* tempH will store result of subtraction */
        tempH = tempT = NULL;

        // subtract divisor from current dividend
        subtraction(head1, tail1,
                    head2, tail2,
                    &tempH, &tempT);

        /* free old dividend */
        //delete_list(&head1, &tail1);

        /* update dividend */
        head1 = tempH;
        tail1 = tempT;

        count++;
    }

    /*  convert integer quotient into linked-list digits (MSD first) and store count in result list */
    if (count == 0)
    {
        insert_at_first(0, headR, tailR);
    }
    else
    {
        while (count > 0)
        {
            insert_at_first(count % 10, headR, tailR);
            count /= 10;
        }
    }

    return SUCCESS;
}
