#include<stdio.h>
#include<stdlib.h>


struct Stack{
  int data;
  struct Stack *next;
};

void displayList(struct Stack *root)
{
  while( root != NULL ){
    printf(" %d ", root->data);
    root = root->next;
  }
}


struct Stack *push(struct Stack *root, int value)
{
  struct Stack *newNode = (struct Stack*)malloc(sizeof(struct Stack));

  root-> data = value;

  if ( root == NULL ){
    root = newNode;
    root-> next = NULL;
  }
  else{
    root -> next = root;
  }

  return root;
}

struct Stack *pop(struct Stack *root)
{
  if (root == NULL){
    printf("stack underflow!\n");
    exit(0);
  }

  struct Stack *thisNode = root;

  int lastItem = root->data;

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

int n; /* number of operations */
int k; /* number of rails */


/* what is difference between sizeof(struct Stack *) and sizeof(struct Stack) ? */
struct Stack **roots = (struct Stack **)malloc((size_t)k*sizeof(struct Stack *));





return 0;
}
