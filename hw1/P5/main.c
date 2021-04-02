#include<stdio.h>
#include<stdlib.h>
#include <string.h>


struct Stack{
  int data;
  struct Stack *next;
};

void displayStack(struct Stack *root)
{
  while( root ){
    printf("%d ", root->data);
    root = root->next;
  }
  printf("\n");
}


struct Stack *push(struct Stack *root, int value)
{
  struct Stack *newNode = (struct Stack*)malloc(sizeof(struct Stack));

  if ( root ){
    newNode -> next = root;
    root = newNode;
  }
  else {
    root = newNode;
    root-> next = NULL;
  }

  root-> data = value;

  return root;
}

struct Stack *pop(struct Stack *root)
{
  if (!root){
    printf("stack underflow!\n");
    exit(0);
  }

  struct Stack *thisNode = root;

  root = root->next;

  free(thisNode);
  thisNode = NULL;

  return root;
}

int peek(struct Stack *root)
{
  return root->data;
}

struct Stack* reverseLinkedList(struct Stack *root)
{
  struct Stack *temp;
  struct Stack *prev = NULL;
  
  for (int i=0; root ;i++){
    temp       = root;
    root       = root->next;
    temp->next = prev;
    prev       = temp;
  }

  return prev;
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

/* initialization */
for (int ridx=0;ridx<k;ridx++)  roots[ridx] = NULL;

int op = 0;

while( op < n ){

   scanf("%7s", operation);
   if      (operation[0] == 108){
     scanf("%d"   , &r_leave);
     if (roots[r_leave] != NULL && r_leave < k) roots[r_leave] = pop(roots[r_leave]);
   }
   else if (operation[0] == 101 ){
     scanf("%d %d", &r_enter, &l_enter);
     if ( r_enter < k)  roots[r_enter] = push(roots[r_enter], l_enter);
   }
   else if (operation[0] == 109){
     scanf("%d %d", &ra, &rb);
     for(int idx = 0;roots[ra] != NULL; idx++){
       int numCabin = peek(roots[ra]);
       roots[ra]  = pop(roots[ra]);
       roots[rb] = push(roots[rb], numCabin);
     } 
   }
   
   
   
   op++;
}

/* reverse all linked lists */
for (int ridx=0; ridx<k; ridx++)
  if ( roots[ridx] != NULL ) roots[ridx] = reverseLinkedList(roots[ridx]);

/* display all rails */
for (int ridx=0; ridx<k; ridx++){
  roots[ridx] != NULL ?  displayStack(roots[ridx]) :  printf("\n");
}

return 0;
}
