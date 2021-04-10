#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>

struct List{
  int *data;
  struct List *next;
};

insertAfter()
{

}

removeAfter(struct List *node)
{
  struct List *cursor;
  struct List *temp;

  for(int i=0;cursor == node;i++){
    temp         = cursor->next;
    cursor->next = cursor->next->next;
  }
  free(temp);
}

appendNode(struct List *node, int data)
{
  struct List *newNode = (struct List*)calloc((size_t)1, sizeof(struct List));

  if (node == NULL){
    node = newNode;
    node->data = data;
    node->next = NULL;
  }
  else{
    newNode->data = data;
    newNode->next = node;
  }
}

int main(){


  return 0;
}
