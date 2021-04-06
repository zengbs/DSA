#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include <string.h>




struct Stack* XOR(struct Stack *a, struct Stack *b)
{
  return (struct Stack*)((uintptr_t) (a) ^ (uintptr_t) (b));
}

// prints contents of doubly linked
// list in forward direction
void printList (struct Stack *root)
{
    struct Stack *curr = root;

    struct Stack *prev = NULL;
    struct Stack *next;
 
    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
    }
  printf("\n");
}
