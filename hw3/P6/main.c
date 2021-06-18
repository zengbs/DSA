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
bool checkFriend( int **head, int *lastIdx, int p, int j, int *p2, int *j2, bool checkSelf, int lengthAdjList, int *numVertex ){

  int X;

  if (checkSelf){

    X = head[p][j];
    if (numVertex[p] != 0 && head[X][lastIdx[X]] == p){

      *p2 = X;
      *j2 = lastIdx[X];

      return true;
    }

  }
  else{

    if (numVertex[p+1] != 0 && p+1 < lengthAdjList && j < numVertex[p+1] && j == lastIdx[p+1] ){

      X = head[p+1][j];
      if (head[X][lastIdx[X]] == p+1){

#       ifdef VERBOSE
        printf("new friend(lower) at (%d,%d)!\n", p+1,j);
#       endif
        *p2 = p+1;
        *j2 = j;

        return true;
      }
    }
     
    if (numVertex[p] != 0 && j+1 < numVertex[p] && j+1 == lastIdx[p]){
      X = head[p][j+1];
      if (head[X][lastIdx[X]] == p){

#       ifdef VERBOSE
        printf("new friend(right) at (%d,%d)!\n", p,j+1);
#       endif

        *p2 = p;
        *j2 = j+1;

        return true;
      }
    }
    
    if (numVertex[p-1] != 0 && p-1 >= 0 && j < numVertex[p-1] && j == lastIdx[p-1]){ 
      X = head[p-1][j];
      if (head[X][lastIdx[X]] == p-1){
#       ifdef VERBOSE
        printf("new friend(upper) at (%d,%d)!\n", p-1,j);
#       endif

        *p2 = p-1;
        *j2 = j;

        return true;
      }
    }
    
    if (numVertex[p-1] != 0 && p-1 >= 0 && j+1 < numVertex[p-1] && j+1 == lastIdx[p-1]){ 
      X = head[p-1][j+1];
      if (head[X][lastIdx[X]] == p-1){
#       ifdef VERBOSE
        printf("new friend(upper right) at (%d,%d)!\n", p-1,j+1);
#       endif

        *p2 = p-1;
        *j2 = j+1;

        return true;
      }
    }
    
    if (numVertex[p+1] != 0 && p+1 >= 0 && j+1 < numVertex[p+1] && j+1 == lastIdx[p+1]){ 
      X = head[p+1][j+1];
      if (head[X][lastIdx[X]] == p+1){
#       ifdef VERBOSE
        printf("new friend(lower right) at (%d,%d)!\n", p+1,j+1);
#       endif

        *p2 = p+1;
        *j2 = j+1;

        return true;
      }
    }

    if (numVertex[p-1] != 0 && p-1 >= 0 && j-1 < numVertex[p-1] && j-1 == lastIdx[p-1]){ 
      X = head[p-1][j-1];
      if (head[X][lastIdx[X]] == p-1){
#       ifdef VERBOSE
        printf("new friend(upper left) at (%d,%d)!\n", p-1,j-1);
#       endif

        *p2 = p-1;
        *j2 = j-1;

        return true;
      }
    }
    
    if (numVertex[p+1] != 0 && p+1 >= 0 && j-1 < numVertex[p+1] && j-1 == lastIdx[p+1]){ 
      X = head[p+1][j-1];
      if (head[X][lastIdx[X]] == p+1){
#       ifdef VERBOSE
        printf("new friend(lower left) at (%d,%d)!\n", p+1,j-1);
#       endif

        *p2 = p+1;
        *j2 = j-1;

        return true;
      }
    }

  }

  p2 = NULL;
  j2 = NULL;

  return false;

}


void getPForNextRun(int *lastIdx, int *numVertex, int *lastP, int **head, int lengthAdjList)
{

  bool advanceP = false;

  int p;

  for (p=*lastP; p<lengthAdjList; p++){
    if (numVertex[p] != 0){
      int p2, j2;

      if ( lastIdx[p] != numVertex[p]  && checkFriend( head, lastIdx, p, lastIdx[p], &p2, &j2, true, lengthAdjList, numVertex ) ){
        *lastP = p;
        advanceP = true;
        break;
      }

    }
  }


  if (!advanceP && p == lengthAdjList){
    for (int p=0; p<lengthAdjList; p++){
      if (numVertex[p] != 0){
        int p2, j2;

        if ( lastIdx[p] != numVertex[p]  && checkFriend( head, lastIdx, p, lastIdx[p], &p2, &j2, true, lengthAdjList, numVertex ) ){
          *lastP = p;
          break;
        }

      }
    }
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
  for (int p=0;p<lengthAdjList;p++){

    scanf("%d", &numVertex[p]);
 

    head[p] = (int*)malloc((size_t)(numVertex[p])*sizeof(int));


    for (int j=0;j<numVertex[p];j++){
      scanf("%d", &head[p][j]);
      head[p][j]--;
    }

    lastIdx[p] = 0;

    DoubleTotalEdge += numVertex[p];
  }
  /*============== STEP-2:  ============== */

 

  int *ans  = malloc(DoubleTotalEdge*sizeof(int));
  int ansIdx = 0;

  int p1 = 0;
  int j1 = 0;
  int p2, j2;
  int pf, jf;
  int c = 0;

  int lastP = 0; 

  int prevCASE;
  int prev_lastP;

  while( 1 ){

#   ifdef VERBOSE
    printf("\n\n====================================================\n");
    for (int p=0;p<lengthAdjList;p++){
      printf("lastIdx[%d]=%d\n", p, lastIdx[p]);
    }
#   endif

   
    
 
    /* Put the ptr at (p1,j1) and check if (p1,j1) has a friend, say (p2,j2), or not. */
    if (checkFriend( head, lastIdx, p1, j1, &p2, &j2, true, lengthAdjList, numVertex )){
#     ifdef VERBOSE
      printf("=============== (p1,j1)=(%d,%d) ===================\n", p1,j1); 
      printf("=============== (p2,j2)=(%d,%d) ===================\n", p2,j2); 
      printf("c=(%d)\n", c); 
      printf("CASE-1\n");
#     endif

      prevCASE = 1;

      /* print (p1,j1) and (p2,j2) */
#     ifdef VERBOSE
      printf("%d %d\n", head[p1][j1]+1, head[p2][j2]+1);
#     endif
      ans[ansIdx++] = head[p1][j1]+1;
      ans[ansIdx++] = head[p2][j2]+1;


      lastIdx[p1]++;
      lastIdx[p2]++;

      //if ( lastIdx[p1] == numVertex[p1] ) c++;
      //if ( lastIdx[p2] == numVertex[p2] ) c++;
      c=c+2;

      /* check if we loop through all items in the table or not. */
      if (c == DoubleTotalEdge) break;

     
      /* check if (p1±1,j1±1) has a friend or not. */
      if (checkFriend( head, lastIdx, p1, j1, &pf, &jf, false, lengthAdjList, numVertex )){
#       ifdef VERBOSE
        printf("CASE-2\n");
#       endif
        prevCASE = 2;
     
        /* move ptr to (p1±1,j1±1), continue */
        p1 = pf;
        j1 = jf;
        continue; 
      }
      else{
#       ifdef VERBOSE
        printf("CASE-3\n");
#       endif

        prevCASE = 3;

        /* check if (p2±1,j2±1) has a friend or not. */
        if (checkFriend( head, lastIdx, p2, j2, &pf, &jf, false, lengthAdjList, numVertex )){
#         ifdef VERBOSE
          printf("CASE-4\n");
#         endif

          prevCASE = 4;

          /* move ptr to (p2±1,j2±1), continue */
          p1 = pf;
          j1 = jf;
          continue;
        }
        else{
#         ifdef VERBOSE
          printf("CASE-5\n");
#         endif

          prevCASE = 5;

          /* check if we loop through all items in the table or not. */
          if (c == DoubleTotalEdge){
#           ifdef VERBOSE
            printf("CASE-5a\n");
#           endif
            //printf("Yes\n");
            break;
          }
          else{
#           ifdef VERBOSE
            printf("CASE-5b\n");
#           endif
            getPForNextRun(lastIdx, numVertex, &lastP, head, lengthAdjList);
            prev_lastP = lastP;
#           ifdef VERBOSE
            printf("lastP: %d -> %d\n", p1, lastP);
#           endif     
            /* move ptr to (lastP,lastIdx[lastP]) and continue */
            p1 = lastP;
            j1 = lastIdx[lastP];
            continue;
          }
        }

      }
    }
    else{
#     ifdef VERBOSE
      printf("CASE-6\n");
#     endif


      getPForNextRun(lastIdx, numVertex, &lastP, head, lengthAdjList);
      
#     ifdef VERBOSE
      printf("lastP: %d -> %d\n", p1, lastP);
#     endif     

      if (prevCASE == 6 && lastP == prev_lastP) break;

      p1 = lastP;
      j1 = lastIdx[lastP];
    
      prevCASE = 6;
      prev_lastP = lastP;
      continue;

//      /* check if p1+1 is inside the table */
//      if ( checkFriend( head, lastIdx, p1, lastIdx[p1], &pf, &jf, true, lengthAdjList, numVertex ) ){
//#       ifdef VERBOSE
//        printf("CASE-7\n");
//#       endif
//        p1 = pf;
//        j1 = jf;
//        continue;
//      }
//      else{
//      }
    }
  } // while()

 
  /* output results */
 
  if (c == DoubleTotalEdge){
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

