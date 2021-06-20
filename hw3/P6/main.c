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

      if (numVertex[p] == 0) continue;

      if ( lastIdx[p] == numVertex[p] ) continue;

      int p2, j2;

      if ( checkFriend( head, lastIdx, p, lastIdx[p], &p2, &j2, true, lengthAdjList, numVertex ) ){
        *lastP = p;
        advanceP = true;
        break;
      }

  }


  if (!advanceP && p == lengthAdjList){
# ifdef VERBOSE
  printf("OMG! Loop through vertical array to find p1!\n");
# endif


    for (int p=0; p<*lastP; p++){

      if (numVertex[p] == 0) continue;

      if ( lastIdx[p] == numVertex[p] ) continue;

      int p2, j2;

      if ( checkFriend( head, lastIdx, p, lastIdx[p], &p2, &j2, true, lengthAdjList, numVertex ) ){
        *lastP = p;
        break;
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
  int  *lastIdx    = (int* )calloc((size_t)(lengthAdjList), sizeof(int ));

  int DoubleTotalEdge = 0;

  /*============== STEP-1: input ============== */
  for (int p=0;p<lengthAdjList;p++){

    scanf("%d", &numVertex[p]);
 

    head[p] = (int*)malloc((size_t)(numVertex[p])*sizeof(int));


    for (int j=0;j<numVertex[p];j++){
      scanf("%d", &head[p][j]);
      head[p][j]--;
    }


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
  int prevCASE = -1;
  int prev_lastP;


  int *verticalArray = (int*)malloc(lengthAdjList*sizeof(int));
  int verticalArray_c = 0;

  for (int p1=0;p1<lengthAdjList;p1++){
    verticalArray[p1] = -1;
  }

  for (int p1=0;p1<lengthAdjList;p1++){
    if (!checkFriend( head, lastIdx, p1, 0, &p2, &j2, true, lengthAdjList, numVertex )&&numVertex[p1]>0){
      verticalArray[verticalArray_c] = p1;
      verticalArray_c++;
    }
  }

  verticalArray_c = 0;

  int while_counter = -1;

  while( while_counter < DoubleTotalEdge ){
    while_counter++;

#   ifdef VERBOSE
    printf("\n\n====================================================\n");
    for (int p=0;p<lengthAdjList;p++){
      printf("lastIdx[%d]=%d\n", p, lastIdx[p]);
    }
    printf("p1=%d, j1=%d\n", p1,j1);
#   endif

    /* Put the ptr at (p1,j1) and check if (p1,j1) has a friend, say (p2,j2), or not. */
    if (checkFriend( head, lastIdx, p1, j1, &p2, &j2, true, lengthAdjList, numVertex )){
#     ifdef VERBOSE
      printf("=============== (p1,j1)=(%d,%d) ===================\n", p1,j1); 
      printf("=============== (p2,j2)=(%d,%d) ===================\n", p2,j2); 
      printf("CASE-1=%d\n", __LINE__);
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

      c=c+2;

      /* check if we loop through all items in the table or not. */
      if (c == DoubleTotalEdge) break;

     
      /* check if (p1±1,j1±1) has a friend or not. */
      if (checkFriend( head, lastIdx, p1, j1, &pf, &jf, false, lengthAdjList, numVertex )){
#       ifdef VERBOSE
        printf("CASE-2=%d\n", __LINE__);
#       endif
        prevCASE = 2;
     
        /* move ptr to (p1±1,j1±1), continue */
        p1 = pf;
        j1 = jf;
        continue; 
      }
      else{

        /* check if (p2±1,j2±1) has a friend or not. */
        if (checkFriend( head, lastIdx, p2, j2, &pf, &jf, false, lengthAdjList, numVertex )){
#         ifdef VERBOSE
          printf("CASE-3=%d\n", __LINE__);
#         endif

          prevCASE = 4;

          /* move ptr to (p2±1,j2±1), continue */
          p1 = pf;
          j1 = jf;
          continue;
        }
        else{

          /* check if we loop through all items in the table or not. */
          if (c == DoubleTotalEdge){
#           ifdef VERBOSE
            printf("CASE-4=%d\n\n", __LINE__);
            printf("break!\n");
#           endif
            break;
          }
          else{
#           ifdef VERBOSE
            printf("CASE-5: %d\n", __LINE__);
#           endif     

            if (verticalArray_c+1<lengthAdjList && verticalArray[verticalArray_c+1] != -1&&j1!=0){

              if (lastIdx[verticalArray[verticalArray_c]] < numVertex[verticalArray[verticalArray_c]]){
#               ifdef VERBOSE
                printf("CASE-5a: %d\n", __LINE__);
                printf("Jump (p1,j1):(%d,%d)->(%d,%d)\n", p1, j1, verticalArray[verticalArray_c], lastIdx[verticalArray[verticalArray_c]]);
#               endif
                p1 = verticalArray[verticalArray_c];
                j1 = lastIdx[p1];
                verticalArray_c++;
                continue; 
              }
              else{
                verticalArray_c++;
#               ifdef VERBOSE
                printf("CASE-5b: %d\n", __LINE__);
#               endif
                if (lastIdx[verticalArray[verticalArray_c]] < numVertex[verticalArray[verticalArray_c]]){
                  p1 = verticalArray[verticalArray_c];
                  j1 = lastIdx[p1];
                  verticalArray_c++;
                  continue; 
                }
                else{
                   getPForNextRun(lastIdx, numVertex, &lastP, head, lengthAdjList);
                   p1 = lastP;
                   j1 = lastIdx[lastP];
                   continue; 
                }
              }
            }
            else{
#             ifdef VERBOSE
              printf("CASE-6: %d\n", __LINE__);
              printf("Loop through vertical array to find p1! (p1,j1):(%d,%d)->(%d,%d)\n", p1,j1,lastP, lastIdx[lastP]);
#             endif
              getPForNextRun(lastIdx, numVertex, &lastP, head, lengthAdjList);

              p1 = lastP;
              j1 = lastIdx[p1];
              continue; 
            }

            prev_lastP = p1;
            prevCASE = -1;
            continue;
          }
        }

      }
    }
    else{

      getPForNextRun(lastIdx, numVertex, &lastP, head, lengthAdjList);
      
      if (prevCASE == 7 && lastP == prev_lastP){
#       ifdef VERBOSE
        printf("CASE-7=%d\n", __LINE__);
        printf("Loop through vertical array to find p1 and break!\n");
#       endif     
        break;
      }

#     ifdef VERBOSE
      printf("CASE-8=%d\n", __LINE__);
      printf("Loop through vertical array to find p1! (p1,j1):(%d,%d)->(%d,%d)\n", p1,j1,lastP, lastIdx[lastP]);
#     endif     

 
      p1 = lastP;
      j1 = lastIdx[lastP];
      prev_lastP = lastP;
    
      prevCASE = 7;
      continue;

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

