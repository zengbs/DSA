#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define MAX_BOOKS 100000

void printPriority(int *sizePriorityArray, int *priorityArray)
{
  for (int i=0;i<*sizePriorityArray; i++){
    printf("%d ", priorityArray[i]);
  }
  printf("\n");
}


void Insert(int p, int k, int *sizePriorityArray, int *priorityArray)
{
  if (k > *sizePriorityArray+1){
    printf("k(%d) > sizePriorityArray(%d)\n", k, *sizePriorityArray);
    exit(0);
  }

  for(int i=*sizePriorityArray ;i>k; i--){
    priorityArray[i] = priorityArray[i-1];
  }
  
  *sizePriorityArray = *sizePriorityArray + 1;
  priorityArray[k] = p;
}

void Delete(int k, int *sizePriorityArray, int *priorityArray)
{
  for(int i=k ;i<*sizePriorityArray; i++){
    priorityArray[i-1] = priorityArray[i];
  }

  *sizePriorityArray = *sizePriorityArray - 1;
}


int main(){


  /* number of books in initial bookshelf */
  int N;


  /* number of operations*/
  int Q;

  scanf("%d %d", &N, &Q);

  int sizePriorityArray = N;

  /* priority array*/
  int *priorityArray = (int*)calloc((size_t)MAX_BOOKS, sizeof(int));

  for(int i=0;i<N;i++){
    scanf("%d", &priorityArray[i]);
  }

  /*operations*/
  int operation;

  scanf("%d", &operation);

  /*priority of book*/
  int p;

  /*left, right position*/
  int l, r;

  /*position*/
  int k;

 

  switch(operation)
  {
    case 1:
    /* insert */
      scanf("%d", &p);
      scanf("%d", &k);
      Insert(p, k, &sizePriorityArray, priorityArray);
      break;

    case 2:
    /* delete */
      scanf("%d", &k);
      Delete(k, &sizePriorityArray, priorityArray);
      break;

    case 3:
    /* increase priority */
      scanf("%d", &l);
      scanf("%d", &r);
      scanf("%d", &p);

      break;
    case 4:
    /* query the largest priority */
      scanf("%d", &l);
      scanf("%d", &r);


      break;
    case 5:
    /* reverse books */
      scanf("%d", &l);
      scanf("%d", &r);

      break;
    case 6:
    /* remove the book with the largest prioriy */


      break;
  }


  printPriority(&sizePriorityArray, priorityArray);

  return 0;
}
