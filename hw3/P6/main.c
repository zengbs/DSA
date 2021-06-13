#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define VERBOSE

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


        while(j1 < numVex[p1] || j2 < numVex[p2]){


          if ( *Ptr[*Ptr[p1]] == p1 ){

#           ifdef VERBOSE
            printf("line:%d, p1=%d, p2=%d\n", __LINE__, p1, p2);
            printf("line:%d, j1=%d, j2=%d\n", __LINE__, j1, j2);
#           endif

            p2 = *Ptr[p1];
            j2 = (int)(Ptr[p2] - head[p2]);

            j1++;
            j2++;

            Ptr[p1] = &head[p1][j1];
            Ptr[p2] = &head[p2][j2];

          }else if ( *Ptr[*Ptr[p2]] == p2 ){

#           ifdef VERBOSE
            printf("line:%d, p1=%d, p2=%d\n", __LINE__, p1, p2);
            printf("line:%d, j1=%d, j2=%d\n", __LINE__, j1, j2);
#           endif

            p1 = *Ptr[p2];
            j1 = (int)(Ptr[p1] - head[p1]);

            j1++; 
            j2++; 


            Ptr[p1] = &head[p1][j1];
            Ptr[p2] = &head[p2][j2];

          }else{
            printf("error!");
            exit(0);
          }


          if (p1<p2) printf("%d %d\n",p1, p2);
          else       printf("%d %d\n",p2, p1);



        }
      }

 }



  /*============== STEP-999:  ============== */
  /* output */
  for (int i=0;i<lengthAdjList;i++){
    for (int j=0;j<numVex[i];j++){
      printf("%d ", head[i][j]+1);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
