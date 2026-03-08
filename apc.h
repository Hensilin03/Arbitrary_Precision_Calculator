#ifndef APC_H
#define APC_H

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/* list operations */
int insert_at_first(int data, Dlist **head, Dlist **tail);
int insert_at_last(int data, Dlist **head, Dlist **tail);
void delete_list(Dlist **head, Dlist **tail);
void print_list(Dlist *head);

int compare(Dlist *head1, Dlist *head2);

/* arithmetic operations */
int addition(Dlist *head1, Dlist *tail1,
             Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR);

int subtraction_operation(Dlist *head1, Dlist *tail1,
                          Dlist *head2, Dlist *tail2,
                          Dlist **headR, Dlist **tailR);

int subtraction(Dlist *head1, Dlist *tail1,
                Dlist *head2, Dlist *tail2,
                Dlist **headR, Dlist **tailR);

int multiplication(Dlist *head1, Dlist *tail1,
                   Dlist *head2, Dlist *tail2,
                   Dlist **headR, Dlist **tailR);

int division(Dlist *head1, Dlist *tail1,
             Dlist *head2, Dlist *tail2,
             Dlist **headR, Dlist **tailR);

#endif

