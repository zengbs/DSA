#include<stdio.h>
#include<stdlib.h>
#include <string.h>


struct Stack{
  int data;
  struct Stack *next;
};

void displayStack(struct Stack *root)
{
  while( root != NULL ){
    printf("%d ", root->data);
    root = root->next;
  }
  printf("\n");
}


struct Stack *push(struct Stack *root, int value)
{
  struct Stack *newNode = (struct Stack*)malloc(sizeof(struct Stack));


  if ( root == NULL ){
    root = newNode;
    root-> next = NULL;
  }
  else{
    newNode -> next = root;
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

  free(thisNode);

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
scanf("%7s", operation);

if      (strcmp(operation, "leave"  )== 0) scanf("%d"   , &r_leave);
else if (strcmp(operation, "enter"  )== 0) scanf("%d %d", &r_enter, &l_enter);
else if (strcmp(operation, "migrate")== 0) scanf("%d %d", &ra, &rb);


struct Stack **roots = (struct Stack **)malloc((size_t)k*sizeof(struct Stack *));


/* initialization */
for (int ridx=0;ridx<k;ridx++){
  roots[ridx] = NULL;
}

/* the l-th cabin enter the r-th rail */
if ( strcmp(operation, "enter")  == 0 && r_enter < k )           roots[r_enter] = push(roots[r_enter], l_enter);

/* the last cabin leave the r-th rail */
if (strcmp(operation, "leave")  == 0 && roots[r_leave] != NULL ) roots[r_leave] = pop(roots[r_leave]);

//if (strcmp(operation, "migrate")== 0){
//  for(int idx = 0;roots[idx] != NULL; idx++){
//
//  }
//}


/* display all rails */
for (int ridx=0; ridx<k; ridx++){
  roots[ridx] != NULL ?  displayStack(roots[ridx]) :  printf(" \n");
}

/* free memory */
//for (int r=0;r<k;r++){
//  pop(roots[r])
//}

//struct Stack *root = NULL;
//
//root = push(root, 1);
//root = push(root, 2);
//root = push(root, 3);
//root = pop(root);
//root = push(root, 4);
//root = push(root, 5);
//
//root = pop(root);
//
//displayStack(root);


return 0;
}
