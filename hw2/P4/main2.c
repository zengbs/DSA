#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>





int *getLeftData( int **root, int **parent)
{
  int dataIdxLeft;

  dataIdxLeft  = *(*parent+1);
 

  if (dataIdxLeft < 0) return NULL;
  else                 return *root+3*dataIdxLeft;
}

int *getRightData( int **root, int **parent)
{
  int dataIdxRight;

  dataIdxRight = *(*parent+2);


  if (dataIdxRight < 0) return NULL;
  else                  return *root+3*dataIdxRight;
}

bool serarchBT( int **root, int **parent, int *inputData )
{
  int *RightChild, *LeftChild;

  LeftChild = getLeftData (root, parent);
  RightChild  = getRightData(root, parent);

 
  //printf("inputData=%d\n", *inputData);
  //printf("**parent=%d\n", **parent);
  //printf("RightChild=%d\n", *RightChild);
  //printf("LeftChild=%d\n", *LeftChild );

  if ( *inputData == **parent ) return true;

  

  if ( (*parent)[0] > *inputData && LeftChild != NULL){
    //printf("*LeftChild=%d\n", *LeftChild);
    serarchBT(root, &LeftChild, inputData);
  }
  else if ((*parent)[0] < *inputData && (*parent)[0] > 0 && RightChild != NULL ){
    serarchBT(root, &RightChild, inputData);
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




  //for(int i=0; i<3*numNode; i+=3){
  //  printf("%d %d %d\n", nodeList[i], nodeList[i+1]+1, nodeList[i+2]+1);
  //}


  int c=0;

  for(int i=0; i<3*numNode; i+=3){
    if (serarchBT(&nodeList, &nodeList, nodeList+i)) c++;
  }
  printf("%d\n", c);

  //if (serarchBT(&nodeList, &nodeList, nodeList+18)) printf("found!!\n");
  //else                                              printf("no!!\n");

  free(nodeList);

  return 0;
}
