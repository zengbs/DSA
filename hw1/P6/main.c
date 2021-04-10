#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>

struct List{
  int data;
  struct List *next;
};

insertAfter()
{

}

void removeAfter(struct List **node, int pos)
{
  struct List *cursor;
  struct List *temp;

  for(int i=0;cursor == *node;i++){
    temp         = cursor->next;
    cursor->next = cursor->next->next;
  }
  free(temp);
}

void appendNode(struct List **node, int data)
{
  struct List *newNode = (struct List*)calloc((size_t)1, sizeof(struct List));

  if (*node == NULL){
    *node = newNode;
    (*node)->data = data;
    (*node)->next = NULL;
  }
  else{
    newNode->data = data;
    newNode->next = *node;
    *node = newNode;
  }
}

void printList(struct List *node)
{
  for(int i=0;node != NULL;i++){
    printf("%d ", node->data);
    node = node->next;
  }
  printf("\n");
}

int main(){
  struct List *list = NULL;

  appendNode(&list, 1);
  appendNode(&list, 2);
  appendNode(&list, 3);
  appendNode(&list, 4);
  appendNode(&list, 4);
  appendNode(&list, 4);
  printList(list);

  return 0;
}
