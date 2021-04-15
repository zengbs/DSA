#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>





int getLeftData( int **root, int **parent )
{
  int dataIdxLeft;

  dataIdxLeft  = *(*parent+1);
 
  if (dataIdxLeft < 0) return -1;
  else                 return *(*root+3*dataIdxLeft);
}

int getRightData( int **root, int **parent )
{
  int dataRight, dataIdxRight;

  dataIdxRight = *(*parent+2);

  if (dataIdxRight < 0) return -1;
  else                  return  *(*root+3*dataIdxRight);
}





int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);

  int *nodeList  = malloc((size_t)(3*numNode)*sizeof(int));

  int i = 0;

  for(int i=0; i<3*numNode; i += 3){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeList[i  ] = data;
    nodeList[i+1] = IdxLeft-1;
    nodeList[i+2] = IdxRight-1;
  }




  for(int i=0; i<3*numNode; i+=3){
    printf("%d %d %d\n", nodeList[i], nodeList[i+1]+1, nodeList[i+2]+1);
  }

  int *Ptr = nodeList+18;
  printf("%d\n", getLeftData(  &nodeList, &Ptr ));
  printf("%d\n", getRightData( &nodeList, &Ptr ));

  free(nodeList);

  return 0;
}
