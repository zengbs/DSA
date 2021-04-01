#include<stdio.h>

struct Stack *head;
struct Stack *tail;


struct Stack{
  int data;
  struct Stack *next;
};

void displayList(struct Stack *node)
{
  while( node != NULL ){
    printf(" %d ", node->data);
    node = node->next;
  }
}


struct Stack *push(struct Stack *tailNode, int value)
{
  struct Stack *NextTailNode = (struct Stack*)malloc(sizeof(struct Stack));

  if ( tailNode == NULL ){
    printf("the last node is NULL!\n");
    exit(0);
  }
  else{
    tailNode->next = NextTailNode;
    NextTailNode->data = value;
    NextTailNode->next = NULL;
  }

  return NextTailNode;
}

int pop(struct Stack *tailNode)
{
  if (tailNode == NULL) printf("stack underflow!");

  int popItem = tailNode->data;

  struct Stack *node = tailNode->next;

  free(tailNode->next);

  tailNode = node;

  return popItem;
}

int peek(struct Stack *tailNode)
{
  int item;

  if ( tailNode == NULL ){
    printf("tailNode == NULL!\n");
    exit(0);
  }
  else{
   item = tailNode->data; 
  }

  return item;
}


int main(){







return 0;
}
