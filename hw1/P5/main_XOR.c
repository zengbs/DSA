#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include <string.h>


struct Stack{
  int data;
  struct Stack* npx;
};
 
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

/* Insert a node at the beginning of the
   XORed linked list and makes the newly
   inserted node as head */
void push(struct Stack **root, int data)
{
  // Allocate memory for new node
  struct Stack *newNode = (struct Stack *) malloc (sizeof (struct Stack) );
  newNode->data = data;
 
  /* Since new node is being inserted at the
     beginning, npx of new node will always be
     XOR of current head and NULL */
  newNode->npx = *root;
 
  /* If linked list is not empty, then npx of
     current head node will be XOR of new node
     and node next to current head */
  if (*root != NULL)
  {
      // *(root)->npx is XOR of NULL and next.
      // So if we do XOR of it with NULL, we get next
      (*root)->npx = XOR(newNode, (*root)->npx);
  }
 
  // Change head
  *root = newNode;
}


void pop(struct Stack **root)
{
  struct Stack *nextNode;
  struct Stack *nextnextNode;

  nextNode     = (*root)->npx;

  if (nextNode != NULL){
    nextnextNode = XOR(nextNode->npx, *root);
    nextNode->npx  = nextnextNode;

    free(*root);
    *root = nextNode;
  }
  else{
    free(*root); 
    *root = NULL;
  }
}




int main(){


char operation[8];
int k;                /* total number of rails */
int n;                /* total number of operations */

int l_enter, r_enter; /* the l-th cabin enter the r-th rail */
int r_leave;          /* the last cabin leave the r-th rail */
int ra, rb;           /* migrate all cabins from the rail ra to rb */

scanf("%d %d", &k, &n);
struct Stack **roots = (struct Stack **)malloc((size_t)k*sizeof(struct Stack *));
struct Stack **ends  = (struct Stack **)malloc((size_t)k*sizeof(struct Stack *));

/* initialization */
for (int ridx=0;ridx<k;ridx++){
  roots[ridx] = NULL;
  ends[ridx] = NULL;
}

int op = 0;

while( op < n ){

   scanf("%7s", operation);
   if      (strcmp(operation, "leave"  )== 0){
     scanf("%d"   , &r_leave);
     if (roots[r_leave] != NULL && r_leave < k){
       pop(&roots[r_leave]);
       if (roots[r_leave] == NULL) ends[r_leave] = NULL;
     }
   }
   else if (strcmp(operation, "enter" )== 0){
     scanf("%d %d", &r_enter, &l_enter);
     if ( r_enter < k){
       struct Stack *temp = roots[r_enter];
       push(&roots[r_enter], l_enter);

       if ( temp == NULL ) ends[r_enter] = roots[r_enter];
     }
   }
   else if (strcmp(operation, "migrate")== 0 ){
     scanf("%d %d", &ra, &rb);
     if (roots[ra] != NULL){
       if (roots[rb] != NULL){
         roots[rb]->npx  = XOR(roots[rb]->npx, roots[ra]);
         roots[ra]->npx  = XOR(roots[rb], roots[ra]->npx);
       }
       else{
         ends[rb] = roots[ra];
       }
       roots[rb] = ends[ra];

       roots[ra] = NULL;
        ends[ra] = NULL;
     }
   }
   
   
   op++;
}

///* display all rails */
for (int ridx=0; ridx<k; ridx++){
  ends[ridx] != NULL ?  printList(ends[ridx]) :  printf("\n");
}

return 0;
}
