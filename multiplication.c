#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/*
 * Name            : Hensilin Rithista S
 * Register Number : 25028_034 
 *
 * -------------------------------------------------------------
 * Function: multiplication
 * --------------------------------------------------------------
 * Multiplies two big numbers represented as double linked lists.
 */

int multiplication(Dlist *head1, Dlist *tail1,
                   Dlist *head2, Dlist *tail2,
                   Dlist **headR, Dlist **tailR)
{
    Dlist *temp1;
    Dlist *temp2 = tail2;

    Dlist *headR1 = NULL, *tailR1 = NULL;  // stores accumulated result
    Dlist *headR2 = NULL, *tailR2 = NULL;  // stores current partial product

    int carry, ret;
    int count = 0;

    // outer loop: process each digit of second number
    while (temp2 != NULL)
    {
        temp1 = tail1;  // start from least significant digit of first number
        carry = 0;

        /* insert zeros for shifting */
        for (int i = 0; i < count; i++)
            insert_at_first(0, &headR2, &tailR2);

        // inner loop: multiply one digit of second number with all digits of first
        while (temp1 != NULL)
        {
            ret = (temp2->data * temp1->data) + carry;  // multiply digits and add carry

            // first partial product goes directly into result list
            if (count == 0)
                insert_at_first(ret % 10, &headR1, &tailR1);
            else
                insert_at_first(ret % 10, &headR2, &tailR2);

            carry = ret / 10;    //update carry
            temp1 = temp1->prev; //move to next higher digit of 1st number
        }

        //insert remaining as the most significant digit of the partial product
        if (carry > 0)
        {
            if (count == 0)
                insert_at_first(carry, &headR1, &tailR1);
            else
                insert_at_first(carry, &headR2, &tailR2);
        }

        /* add current partial product to accumulated result */
        if (headR1 != NULL && headR2 != NULL)
        {
            addition(headR1, tailR1,
                     headR2, tailR2,
                     headR, tailR);

            /* update accumulated result */
            headR1 = *headR;
            tailR1 = *tailR;

            /* free partial result list */
            while (headR2)
            {
                Dlist *temp = headR2;
                headR2 = headR2->next;
                free(temp);
            }
            headR2 = tailR2 = NULL;

            *headR = *tailR = NULL;  //reset temp result pointers
        }

        count++;                //increase shift for next digit
        temp2 = temp2->prev;    //move to next digit of 2nd number
    }

    //final result head and tail
    *headR = headR1;
    *tailR = tailR1;

    return SUCCESS;
}
