#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



int main(){

int numNode, level, dataL, dataR;

  scanf("%d", &numNode);

  for(int node=0; node<numNode; node++){
    scanf("%d %d %d", &level, &dataL, &dataR);
    printf("%d %d %d\n", level, dataL, dataR);
  }


  return 0;
}
