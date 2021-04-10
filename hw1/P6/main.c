#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>

struct List{
  int *array;
  int arraySize;
  struct List *next;
};

//insertAfter()
//{
//
//}

//void removeAfter(struct List **node, int pos)
//{
//  struct List *cursor;
//  struct List *temp;
//
//  for(int i=0;cursor == *node;i++){
//    temp         = cursor->next;
//    cursor->next = cursor->next->next;
//  }
//  free(temp);
//}

void removeRoot(struct List **root)
{
  struct List *temp;
  temp = *root;
  *root = (*root)->next;

  free(temp->array);
  free(temp);
}

void appendNode(struct List **node, int* array, size_t arraySize)
{
  struct List *newNode = (struct List*)calloc((size_t)1, sizeof(struct List));

  if (*node == NULL){
    *node = newNode;
    (*node)->array = array;
    (*node)->arraySize = arraySize;
    (*node)->next = NULL;
  }
  else{
    newNode->array = array;
    newNode->next = *node;
    newNode->arraySize = arraySize;
    *node = newNode;
  }
}

void printList(struct List *node)
{
  for(int i=0;node != NULL;i++){
    for(int j=0;j<node->arraySize;j++){
      printf("%d ", node->array[j]);
    }
    node = node->next;
    printf("\n");
  }
}

int main(){
  int n; // length of sequence
  int q; // number of operations
  int number; // appended number

  scanf("%d %d", &n, &q);

  struct List *list = NULL;
  int * array = (int*)calloc(n, sizeof(int));
  int * brray = (int*)calloc(n, sizeof(int));

  for(int i=0;i<=n-1;i++){
    scanf("%d", &number);
    array[i] = number;
  }

  appendNode(&list, array, n);


  for(int i=0;i<=n-1;i++){
    brray[i] = -i;
  }
  appendNode(&list, brray, n);

  removeRoot(&list);

  for(int i=0;i<=n-1;i++){
    brray[i] = i*i;
  }

  appendNode(&list, brray, n);
  ///* read operations */
  //char operation[10];
  //int l_pos, r_pos, value;

  //for(int i=0;i<q;i++){
  // scanf("%7s", operation);
  //   if(strcmp(operation, "Delete"  )== 0){
  //     scanf("%d", &l_pos);
  //     delete(&end, &root, l_pos);
  //   }
  //   if(strcmp(operation, "Insert"  )== 0){
  //     scanf("%d %d", &l_pos, &value);
  //     insert(&end, &root, l_pos, value);
  //   }
  //   if(strcmp(operation, "Reverse"  )== 0){
  //     scanf("%d %d", &l_pos, &r_pos);
  //     reverse(&end, &root, l_pos, r_pos);
  //   }
  //}

  printList(list);

  return 0;
}
