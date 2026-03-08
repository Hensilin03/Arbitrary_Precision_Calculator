#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apc.h"

/* create list from string (digits only) */
void create_list(char *str, Dlist **head, Dlist **tail)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
            insert_at_last(str[i] - '0', head, tail);
    }
}

/* check if linked list value is zero */
int is_zero(Dlist *head)
{
    while (head)
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;

    char *expr, *op_ptr = NULL;
    char operator = 0;
    int sign1 = 1, sign2 = 1, result_sign = 1;

    if (argc != 2)
    {
        printf("Usage: ./a.out <num1><op><num2>\n");
        return FAILURE;
    }

    expr = argv[1];

    /* detect operator (scans the input string starting from index 1. because index 0 may contain a - sign for the first number.) */
    for (int i = 1; expr[i] != '\0'; i++)
    {
        if (expr[i] == '+' || expr[i] == '-' ||
            expr[i] == 'x' || expr[i] == '/')
        {
            operator = expr[i];
            op_ptr = &expr[i];
            break;
        }
    }

    if (!op_ptr)
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    /* split operands (splits the original string into: num1 → left side, num2 → right side) */
    *op_ptr = '\0';
    char *num1 = expr;
    char *num2 = op_ptr + 1;

    /* detect sign of operands */
    if (num1[0] == '-')
    {
        sign1 = -1;
        num1++;
    }

    if (num2[0] == '-')
    {
        sign2 = -1;
        num2++;
    }

    /* create linked lists */
    create_list(num1, &head1, &tail1);
    create_list(num2, &head2, &tail2);

    /* multiplication & division sign */
    if (operator == 'x' || operator == '/')
        result_sign = sign1 * sign2;

    /* perform operation */
    switch (operator)
    {
        case '+':
            if (sign1 == sign2)
            {
                addition(head1, tail1, head2, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                int cmp = compare(head1, head2);
                if (cmp > 0)
                {
                    subtraction_operation(head1, tail1, head2, tail2, &headR, &tailR);
                    result_sign = sign1;
                }
                else if (cmp < 0)
                {
                    subtraction_operation(head2, tail2, head1, tail1, &headR, &tailR);
                    result_sign = sign2;
                }
                else
                {
                    insert_at_last(0, &headR, &tailR);
                    result_sign = 1;
                }
            }
            break;

        case '-':
            sign2 = -sign2;  // Treat subtraction as addition with flipped sign2
            if (sign1 == sign2)
            {
                addition(head1, tail1, head2, tail2, &headR, &tailR);
                result_sign = sign1;
            }
            else
            {
                int cmp = compare(head1, head2);
                if (cmp > 0)
                {
                    subtraction_operation(head1, tail1, head2, tail2, &headR, &tailR);
                    result_sign = sign1;
                }
                else if (cmp < 0)
                {
                    subtraction_operation(head2, tail2, head1, tail1, &headR, &tailR);
                    result_sign = sign2;
                }
                else
                {
                    insert_at_last(0, &headR, &tailR);
                    result_sign = 1;
                }
            }
            break;

        case 'x':
            if (is_zero(head1) || is_zero(head2))
            {
                insert_at_last(0, &headR, &tailR);
                break;
            }
            multiplication(head1, tail1, head2, tail2, &headR, &tailR);
            break;

        case '/':
            if (is_zero(head2))
            {
                printf("Division by zero\n");
                return FAILURE;
            }
            division(head1, tail1, head2, tail2, &headR, &tailR);
            break;
    }

    /* print result (avoid -0) */
    if (headR && !is_zero(headR) && result_sign < 0)
        printf("-");
    print_list(headR);

    /* cleanup */
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return SUCCESS;
}