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

void appendNode(struct List **root, int* array, size_t arraySize)
{
  struct List *newNode = (struct List*)calloc((size_t)1, sizeof(struct List));

  if (*root == NULL){
    *root = newNode;
    (*root)->array = array;
    (*root)->arraySize = arraySize;
    (*root)->next = NULL;
  }
  else{
    newNode->array = array;
    newNode->next = *root;
    newNode->arraySize = arraySize;
    *root = newNode;
  }
}

/* cut array before `pos` and append a new node to strore the second half array */
/* note that `pos` is counted from zero */
void delete(struct List **root, int pos)
{
  int cursor = 0;

  do{
    cursor += (*root)->arraySize - 1;
    *root = (*root)->next;
  }while(pos>cursor)

  int originalArraySize = (*root)->arraySize;
  int firstArraySize = pos;
  int secondArraySize = originalArraySize - pos;

  int *secondArray = (int*)calloc(secondArraySize, sizeof(int));

  for(int i=0;i<secondArraySize;i++){
    secondArray[i] = originalArray[i+pos];
  }

  appendNode(root, secondArray, secondArraySize);
}



void printList(struct List *root)
{
  for(int i=0;root != NULL;i++){
    for(int j=0;j<root->arraySize;j++){
      printf("%d ", root->array[j]);
    }
    root = root->next;
    printf("\n");
  }
}

int main(){
  int n; // length of sequence
  int q; // number of operations
  int number; // appended number

  scanf("%d %d", &n, &q);

  struct List *root = NULL;
  int * array = (int*)calloc(n, sizeof(int));

  for(int i=0;i<=n-1;i++){
    scanf("%d", &number);
    array[i] = number;
  }

  appendNode(&root, array, n);


  /* read operations */
  char operation[10];
  int l_pos, r_pos, value;

  for(int i=0;i<q;i++){
   scanf("%7s", operation);
     if(strcmp(operation, "Delete"  )== 0){
       scanf("%d", &l_pos);
       delete(&root, l_pos);
     }
     //if(strcmp(operation, "Insert"  )== 0){
     //  scanf("%d %d", &l_pos, &value);
     //  insert(&end, &root, l_pos, value);
     //}
     //if(strcmp(operation, "Reverse"  )== 0){
     //  scanf("%d %d", &l_pos, &r_pos);
     //  reverse(&end, &root, l_pos, r_pos);
     //}
  }

  printList(root);

  return 0;
}
