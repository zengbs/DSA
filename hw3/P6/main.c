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

  int whileCounter = 0;

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
#     ifdef VERBOSE
      printf("CASE-1:\n");
#     endif
      /* if true, print X1(p1,j1) and X2(p2,j2) */
      p2 = head[p1][j1];
      j2 = lastIdx[X1];

      //printf("%d %d\n", X1+1, p1+1);
      ans[ansIdx++] = X1+1;
      ans[ansIdx++] = p1+1;

      lastIdx[X1]++;
      lastIdx[p1]++;

      if ( lastIdx[X1] == numVertex[X1] ) c++;
      if ( lastIdx[p1] == numVertex[p1] ) c++;

      if (c == lengthAdjList) break;

      /* check if (p1,j1+1) has friend or not */
      
      if (j1+1 >= numVertex[p1]) insideBox = false;
      else                       {X1Right = head[p1][j1+1];insideBox=true;}
  

      if ( insideBox && head[X1Right][lastIdx[X1Right]] == p1 ){
#       ifdef VERBOSE
        printf("CASE-2: move ptr to (p1,j1+1)\n");
#       endif
        /* move ptr to (p1,j1+1) */
        p1 = p1;
        j1 = j1+1; 
      }
      else{
#       ifdef VERBOSE
        printf("CASE-3:\n");
#       endif


        if (j2+1 >= numVertex[p2]) insideBox = false;
        else                       {X2Right = head[p2][j2+1];insideBox = true;}

        /* if false, check (p2,j2+1) has friend */
        X2Right = head[p2][j2+1];

        if ( insideBox && head[X2Right][lastIdx[X2Right]] == p2 ){
#         ifdef VERBOSE
          printf("CASE-4:\n");
#         endif
          /*  move ptr to (p2,j2+1) */
          p1 = p2;
          j1 = j2+1;

        }
        else{
#         ifdef VERBOSE
          printf("CASE-5: check if p1+1=(%d) is inside the box\n", p1+1);
#         endif

          if ( p1+1 < lengthAdjList ){
#           ifdef VERBOSE
            printf("CASE-6: move ptr to (p1+1,j1)=(%d,%d)\n",p1+1,j1);
#           endif
            p1 = p1+1;
            j1 = j1;
          }
          else{
#           ifdef VERBOSE
            printf("CASE-7: move ptr to (p2,j2)=(%d,%d)\n",p2,j2);
#           endif
            p1 = p2+1;
            j1 = j2;
          }

          if (p1 == lengthAdjList) continue;
        }
      }
    }
    else{
#     ifdef VERBOSE
      printf("CASE-8: move ptr to (p1+1,j1)\n");
#     endif
      /* if false, move ptr to (p1+1,j1) */
      p1 = p1+1;
      j1 = j1;

      if (p1 == lengthAdjList) continue;
    }

  }

  
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

