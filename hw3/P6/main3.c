#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define VERBOSE1
#define VERBOSE2

void checkPtr(void *ptr, int line)
{    
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }  
}


int main(){


  /* the length of adjecent list */
  int lengthAdjList;

  
  scanf("%d", &lengthAdjList);

  int **head       = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));
  int  *numVertex  = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));
  int  *lastIdx    = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));


  /*============== STEP-1: input ============== */
  for (int i=0;i<lengthAdjList;i++){

    scanf("%d", &numVertex[i]);
 

    head[i] = (int*)malloc((size_t)(numVertex[i])*sizeof(int));


    for (int j=0;j<numVertex[i];j++){
      scanf("%d", &head[i][j]);
      head[i][j]--;
    }

    lastIdx[i] = 0;
  }
  /*============== STEP-2:  ============== */


  int p1 = 0;
  int j1 = 0;
  int p2, j2;
  int X1, X1Right, X2Right;

  while(  ){   

    X1 = head[p1][j1];


    /* Put ptr at (p1,j1) and check ptr have pair (p2,j2) or not */
    if ( head[X1][lastIdx[X1]] == X1 ){

      /* if true, print X1(p1,j1) and X2(p2,j2) */
      p2 = head[p1][j1];
      j2 = lastIdx[X1];

      printf("%d %d\n", X1, p1);
      lastIdx[X1]++;
      lastIdx[p1]++;

      /* and check if (p1,j1+1) have pair or not */
      X1Right = head[p1][j1+1];

      if ( head[X1Right][lastIdx[X1Right]] == X1Right ){
        /* if true, print (p1,j1+1) and its friend,  */
        
        printf("%d %d\n", X1Right, p1);
        lastIdx[X1Right]++;
        lastIdx[p1]++;

        /* , and move ptr to (p1,j1+1) */
        p1 = p1;
        j1 = j1+1; 
      }
      else{
        /* if false, check (p2,j2+1) have pair */
        X2Right = head[p2][j2+1];

        if ( head[X2Right][lastIdx[X2Right]] == X2Right ){

          /* if true, print (p2,j2+1) and its friend */
          printf("%d %d\n", X2Right, p2);
          lastIdx[X2Right]++;
          lastIdx[p2]++;

          /*  move ptr to (p2,j2+1) */
          p1 = p2;
          j1 = j2+1;

        }
        else{
          /* if false, move ptr to (p1+1,j1) */
          p1 = p1+1;
          j1 = j1;
        }
      }
    }
    else{
      /* if false, move ptr to (p1+1,j1) */
      p1 = p1+1;
      j1 = j1;
    }

  }


  return 0;
}

