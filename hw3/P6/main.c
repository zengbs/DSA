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

  int **head    = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));
  int  *numVex  = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));
  int **Ptr     = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));

  /*============== STEP-1: input ============== */
  for (int i=0;i<lengthAdjList;i++){

    scanf("%d", &numVex[i]);
 
    head[i] = (int*)malloc((size_t)(&numVex[i])*sizeof(int));


    for (int j=0;j<numVex[i];j++){
      scanf("%d", &head[i][j]);
      head[i][j]--;
    }

    Ptr[i] = &head[i][0];
  }

  /*============== STEP-2:  ============== */
  int j1 = 0;
  int j2 = 0;

  int p1, p2;

 for(int i=0;i<lengthAdjList;i++){

 
      if ( *Ptr[*Ptr[i]] == i ){


        p1 = i;
        p2 = *Ptr[p1];

        j1++;
        j2++;

        Ptr[p1] = &head[p1][j1];
        Ptr[p2] = &head[p2][j2];

#       ifdef VERBOSE
        printf("advance p1 and p2...\n");
        printf("p1=%d, p2=%d, j1=%d, j2=%d\n", p1, p2, j1, j2);
        printf("\n");
#       endif

          int c=0;

          while(c<4){

          if ( *Ptr[*Ptr[p1]] == p1 ){


            p2 = *Ptr[p1];
            j2 = (int)(Ptr[p2] - head[p2]);


            Ptr[p2] = &head[p2][j2];

#           ifdef VERBOSE
            printf("advance p2...\n");
            printf("p1=%d, p2=%d, j1=%d, j2=%d\n", p1, p2, j1, j2);
            printf("*Ptr[p2]=%d\n", *Ptr[p2]);
            printf("\n");
#           endif

            if (j2<=numVex[p2]-1) j2++;

          }else if ( *Ptr[*Ptr[p2]] == p2 ){


            p1 = *Ptr[p2];
            j1 = (int)(Ptr[p1] - head[p1]);



            Ptr[p1] = &head[p1][j1];

#           ifdef VERBOSE
            printf("advance p1...\n");
            printf("p1=%d, p2=%d, j1=%d, j2=%d\n", p1, p2, j1, j2);
            printf("*Ptr[p1]=%d\n", *Ptr[p1]);
            printf("\n");
#           endif

            if (j1<=numVex[p1]-1) j1++;
         
          }else{
            printf("error!");
            exit(0);
          }
 c++;
       }



      }

 }



//  /*============== STEP-999:  ============== */
//  /* output */
//  for (int i=0;i<lengthAdjList;i++){
//    for (int j=0;j<numVex[i];j++){
//      printf("%d ", head[i][j]+1);
//    }
//    printf("\n");
//  }
//  printf("\n");

  return 0;
}
