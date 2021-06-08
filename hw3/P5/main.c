#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

int main(){

  /* number of books in initial bookshelf */
  int N;

  /* number of operations*/
  int Q;

  scanf("%d %d", &N, &Q);

  /* priority array*/
  int *priorityArray = (int*)calloc((size_t)N*sizeof(int));

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

      break;
    case 2:
    /* delete */
      scanf("%d", &k);


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
