#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>





int *getLeftData( int **root, int *parent)
{
  if (*(parent+1) < 0) return NULL;
  else                 return *root+3* *(parent+1);
}

int *getRightData( int **root, int *parent)
{
  if (*(parent+2) < 0) return NULL;
  else                 return *root+3* *(parent+2);
}

bool serarchBT( int **root, int *parent, int *inputData )
{
  int *RightChild, *LeftChild;

  LeftChild = getLeftData (root, parent);
  RightChild  = getRightData(root, parent);

 
  if ( *inputData == *parent ) return true;
 

  if ( *parent > *inputData && LeftChild != NULL){
    serarchBT(root, LeftChild, inputData);
  }
  else if (*parent < *inputData && *parent > 0 && RightChild != NULL ){
    serarchBT(root, RightChild, inputData);
  }
  else{
    return false;
  }
}



int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);

  if ((double)INT_MAX/(double)numNode < 3.0 ){
    exit(0);
  }

  int *nodeList  = malloc((size_t)(3*numNode)*sizeof(int));

  for(int i=0; i<3*numNode; i += 3){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeList[i  ] = data;
    nodeList[i+1] = IdxLeft-1;
    nodeList[i+2] = IdxRight-1;
  }



  int c=0;

  for(int i=0; i<3*numNode; i+=3){
    if (serarchBT(&nodeList, nodeList, nodeList+i)) c++;
  }
  printf("%d\n", c);

  free(nodeList);

  return 0;
}
