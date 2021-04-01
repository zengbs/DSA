#include<stdio.h>

struct Stack *head;
struct Stack *tail;


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

int pop(struct Stack *root)
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







return 0;
}
