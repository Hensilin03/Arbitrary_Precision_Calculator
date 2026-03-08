#include <stdio.h>
#include <stdlib.h>
#include "apc.h"

/* 
 * Name            : Hensilin Rithista S
 * Register Number : 25028_034 
 * 
 * -------------------------------------------------
 * compare()
 * -------------------------------------------------
 * Compares two numbers represented as linked lists
 * Return:
 *   1  -> num1 > num2  (ex: 250, 100)
 *  -1  -> num1 < num2  (ex: 100, 250)
 *   0  -> num1 == num2 (ex: 100, 100)
 * -------------------------------------------------
 */

int compare(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    /* count digits */
    while (temp1) {
       
        count1++;
        temp1 = temp1->next;
    }

    while (temp2) {
      
        count2++;
        temp2 = temp2->next;
    }

    if (count1 > count2)
        return 1;

    else if (count1 < count2)
        return -1;

    
    /* same digit count */
    temp1 = head1;
    temp2 = head2;

    /*compares digits from the most significant (head) to least, 
    and the first unequal digit determines which number is larger*/
    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;

        else if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next; //move pointers
        temp2 = temp2->next;
    }

    return 0; /*if both are equal return zero*/
}

/* -------------------------------------------------
 * subtraction()
 * -------------------------------------------------
 * Performs: larger_number - smaller_number
 * Borrow logic used
 * -------------------------------------------------
 */

int subtraction(Dlist *head1, Dlist *tail1,
                Dlist *head2, Dlist *tail2,
                Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = tail1;
    Dlist *temp2 = tail2;

    int borrow = 0;
    int res;

    while (temp1 != NULL)
    {
        int d1 = temp1->data - borrow;               //If borrowed from the previous digit, it reduces d1
        int d2 = (temp2 != NULL) ? temp2->data : 0;  //If second number runs out of digits, pretend its digit is 0.

        // if d1 is smaller than d2, borrow from the next higher digit
        // add 10 to d1 and carry the borrow forward
        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // subtract current digits and insert the result at the front
        res = d1 - d2;
        insert_at_first(res, headR, tailR);

        // move to the next more significant digit in both numbers
        // check temp2 to avoid accessing NULL for shorter numbers
        temp1 = temp1->prev;
        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    /* remove leading zeros */
    while ((*headR)->data == 0 && (*headR)->next != NULL)
    {
        Dlist *temp = *headR;
        *headR = temp->next;
        (*headR)->prev = NULL;
        free(temp);
    }

    return SUCCESS;
}

/* -------------------------------------------------
 * subtraction_operation()
 * -------------------------------------------------
 * Wrapper called from main()
 * Handles compare + sign + subtraction
 * -------------------------------------------------
 */
int subtraction_operation(Dlist *head1, Dlist *tail1,
                          Dlist *head2, Dlist *tail2,
                          Dlist **headR, Dlist **tailR)
{
    int ret = compare(head1, head2);

    if (ret == 0) //equal numbers
    {
        insert_at_first(0, headR, tailR);
    }
    else if (ret > 0) //first number is larger
    {
        subtraction(head1, tail1, head2, tail2, headR, tailR);
    }
    else //seconf number is larger, result should be negative
    {
        subtraction(head2, tail2, head1, tail1, headR, tailR);
        (*headR)->data *= -1;   /* mark negative result */
    }

    return SUCCESS;
}
