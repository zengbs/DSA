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

  popItem = tailNode->data;

  tailNode = tailNode->next;

  return popItem;
}

int peek()
{


}


int main(){







return 0;
}
