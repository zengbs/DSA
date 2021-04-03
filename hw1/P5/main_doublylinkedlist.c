#include<stdio.h>
#include<stdlib.h>
#include <string.h>


struct Stack{
  struct Stack *prev;
  int data;
  struct Stack *next;
};

void displayStack(struct Stack *root, struct Stack *end)
{
  if (end == NULL){
    while( root != NULL ){
      printf("%d ", root->data);
      root = root->next;
    }
  }
  else if(root == NULL){
    while( end != NULL ){
      printf("%d ", end->data);
      end = end->prev;
    }
  }
  printf("\n");
}


struct Stack *push(struct Stack *root, int value)
{
  struct Stack *newNode = (struct Stack*)malloc(sizeof(struct Stack));

  if ( root == NULL ){
    root = newNode;
    root-> next = NULL;
    root-> prev = NULL;
  }
  else{
    root->prev = newNode;
    newNode -> next = root;
    newNode -> prev = NULL;
    root = newNode;
  }

  root-> data = value;

  return root;
}

struct Stack *pop(struct Stack *root)
{
  if (root == NULL){
    printf("stack underflow!\n");
    exit(0);
  }

  struct Stack *thisNode = root;

  root = root->next;

  root-> prev = NULL;

  free(thisNode);

  thisNode = NULL;

  return root;
}

int peek(struct Stack *root)
{
  int item;

  if ( root == NULL ){
    printf("root == NULL!\n");
    exit(0);
  }
  else{
   item = root->data; 
  }

  return item;
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
     if (roots[r_leave] != NULL && r_leave < k && roots[r_leave]->next == NULL) ends[r_leave] = NULL;
     if (roots[r_leave] != NULL && r_leave < k)                                 roots[r_leave] = pop(roots[r_leave]);
   }
   else if (strcmp(operation, "enter" )== 0){
     scanf("%d %d", &r_enter, &l_enter);
     if ( r_enter < k){
       roots[r_enter] = push(roots[r_enter], l_enter);
       if ( roots[r_enter]->next == NULL ) ends[r_enter] = roots[r_enter];
     }
   }
   else if (strcmp(operation, "migrate")== 0){
     scanf("%d %d", &ra, &rb);
     roots[ra]->next = roots[rb];
     roots[rb] = ends[ra];
   }
   
   
   
   op++;
}

/* reverse all linked lists */
//for (int ridx=0; ridx<k; ridx++)
//  if ( roots[ridx] != NULL ) roots[ridx] = reverseLinkedList(roots[ridx], NULL);

/* display all rails */
for (int ridx=0; ridx<k; ridx++){
  ends[ridx] != NULL ?  displayStack(NULL, ends[ridx]) :  printf("\n");
  //roots[ridx] != NULL ?  displayStack(roots[ridx], NULL) :  printf("\n");
}

return 0;
}
