#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

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

  int **head = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));

  /*============== STEP-1: input ============== */
  for (int i=0;i<lengthAdjList;i++){
    int lengthAdj;
    scanf("%d", &lengthAdj);
 
    head[i] = (int*)malloc((size_t)(lengthAdj+1)*sizeof(int));

    head[i][0] = lengthAdj;

    for (int j=1;j<lengthAdj+1;j++){
      scanf("%d", &head[i][j]);
    }
  }

  /*============== STEP-2:  ============== */


  /* output */
  for (int i=0;i<lengthAdjList;i++){
    for (int j=0;j<head[i][0]+1;j++){
      printf("%d ", head[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return 0;
}
