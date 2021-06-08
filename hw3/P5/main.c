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


void increasePriority(int l, int r, int p, int *priorityArray)
{
  for (int i=l-1;i<r;i++){
    priorityArray[i] += p;
  }
}


int QueryPriority(int l, int r, int *priorityArray)
{
  int largest = INT_MIN;

  for (int i=l-1;i<r;i++){
    if (largest < priorityArray[i]) largest = priorityArray[i];
  }

  return largest;
}

void Remove(int *sizePriorityArray, int *priorityArray)
{

  int largest = INT_MIN;
  int largestIdx;

  for (int i=l-1;i<r;i++){
    if (largest < priorityArray[i]){
      largest    = priorityArray[i];
      largestIdx = i;
    }
  }

  Delete(largestIdx+1, sizePriorityArray, priorityArray);
}

void Swap(int *a, int *b)
{
  int temp = *a;
  *a   = *b;
  *b   = temp;
}


void Reverse(int l, int r, int *priorityArray)
{

  int rr = r-1;
  int ll = l-1;

  if ((rr-ll)%2==0){ // odd

        for (int i=ll;i<(rr-ll)/2+ll;i++){
          Swap(&priorityArray[i], &priorityArray[rr-i+ll]);
        }
  }
  else{ //even

      for (int i=ll;i<(rr-ll+1)/2+ll;i++){
        Swap(&priorityArray[i], &priorityArray[rr-i+ll]);
      }
  }
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


  /*priority of book*/
  int p;

  /*left, right position*/
  int l, r;

  /*position*/
  int k;

  for (int q = 0;q<Q;q++){ 

    scanf("%d", &operation);

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
        increasePriority(l, r, p, priorityArray);
        break;
      case 4:
      /* query the largest priority */
        scanf("%d", &l);
        scanf("%d", &r);
        QueryPriority(l, r, priorityArray);

        break;
      case 5:
      /* reverse books */
        scanf("%d", &l);
        scanf("%d", &r);
        Reverse(l, r, priorityArray);
        break;
      case 6:
      /* remove the book with the largest prioriy */
        Remove(&sizePriorityArray, priorityArray);

        break;
    }


    printPriority(&sizePriorityArray, priorityArray);
  }

  return 0;
}
