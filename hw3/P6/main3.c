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


  while(  ){   

    value_X1 = head[p1][j1];


    /* Put ptr at (p1,j1) and check ptr have pair (p2,j2) or not */
    if ( head[value_X1][lastIdx[value_X1]] == value_X1 ){

      /* if true, print (p1,j1) and (p2,j2) */
      print("%d %d\n", head[p1][j1], value_X1);

      value_X1Right = head[p1][j1+1];

      /* and check (p1,j1+1) have pair */
      if ( head[value_X1Right][lastIdx[value_X1Right]] == value_X1Right ){
        /* if true, move ptr to (p1,j1+1) */
        

      }
      else{
        /* if false, check (p2,j2+1) have pair */
        if (  ){
          /* if true, move ptr to (p2,j2+1) */
        }
        else{
          /* if false, move ptr to (p1+1,j1) */

        }

      }
    }
    else{
       /* if false, move ptr to (p1+1,j1) */

    }
    

  }


  return 0;
}

