#include<stdio.h>
#include<stdlib.h>


struct Stack{
  int data;
  struct Stack *next;
};

void displayStack(struct Stack *root)
{
  while( root != NULL ){
    printf("%d\n", root->data);
    root = root->next;
  }
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

int n; /* number of operations */
int k; /* number of rails */


/* what is difference between sizeof(struct Stack *) and sizeof(struct Stack) ? */
// struct Stack **roots = (struct Stack **)malloc((size_t)k*sizeof(struct Stack *));

struct Stack *root = NULL;

root = push(root, 1);
root = push(root, 2);
root = push(root, 3);
root = push(root, 4);
root = push(root, 5);

displayStack(root);


return 0;
}
