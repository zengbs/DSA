#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

//#define VERBOSE

void checkPtr(void *ptr, int line)
{    
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }  
}


/* check if (p,j) has a friend or not */
bool checkFriend( int **head, int *lastIdx, int p, int j, int *pf, int *jf, bool checkSelf, int lengthAdjList, int *numVertex ){

  int X;

  if (checkSelf){

    X = head[p][j];
    if (head[X][lastIdx[X]] == p){

      *pf = X;
      *jf = lastIdx[X];

      return true;
    }

  }
  else{

    if (p+1 < lengthAdjList){

      X = head[p+1][j];
      if (head[X][lastIdx[X]] == p+1){

        *pf = X;
        *jf = lastIdx[X];

        return true;
      }
    }
     
    if (j+1 < numVertex[p]){
      X = head[p][j+1];
      if (head[X][lastIdx[X]] == p){

        *pf = X;
        *jf = lastIdx[X];

        return true;
      }
    }
    
    if (p-1 >= 0){ 
      X = head[p-1][j];
      if (head[X][lastIdx[X]] == p-1){

        *pf = X;
        *jf = lastIdx[X];

        return true;
      }
    }

  }

  *pf = NULL;
  *jf = NULL;

  return false;

}

int main(){


  /* the length of adjecent list */
  int lengthAdjList;

  
  scanf("%d", &lengthAdjList);

  int **head       = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));
  int  *numVertex  = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));
  int  *lastIdx    = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));

  int DoubleTotalEdge = 0;

  /*============== STEP-1: input ============== */
  for (int i=0;i<lengthAdjList;i++){

    scanf("%d", &numVertex[i]);
 

    head[i] = (int*)malloc((size_t)(numVertex[i])*sizeof(int));


    for (int j=0;j<numVertex[i];j++){
      scanf("%d", &head[i][j]);
      head[i][j]--;
    }

    lastIdx[i] = 0;

    DoubleTotalEdge += numVertex[i];
  }
  /*============== STEP-2:  ============== */

 

  int *ans  = malloc(DoubleTotalEdge*sizeof(int));
  int ansIdx = 0;

  int p1 = 0;
  int j1 = 0;
  int p2, j2;
  int X1, X1Right, X2Right;
  int c = 0;

  bool insideBox = true;


  while( 1 ){   

#   ifdef VERBOSE
    printf("\n\n=============== (%d,%d) ===================\n", p1,j1); 
    printf("=============== c=(%d) ===================\n", c); 
    
    for (int i=0;i<lengthAdjList;i++){
      printf("lastIdx[%d]=%d\n", i, lastIdx[i]);
    }
#   endif

    X1 = head[p1][j1];
    
    /* Put ptr at (p1,j1) and check if ptr has friend (p2,j2) or not */
    if ( head[X1][lastIdx[X1]] == p1 ){
       
    }
    else{

    }
  }

 
  /* output results */
 
  if (c == lengthAdjList){
    printf("Yes\n");
    for (int Idx=0;Idx<DoubleTotalEdge;Idx++){
      printf("%d ", ans[Idx]);
      Idx++;
      printf("%d\n",ans[Idx]);
    }
  }
  else{
    printf("No\n");
  }


  return 0;
}

