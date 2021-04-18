#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>


int *getLeftData( int **root, int *parent)
{
  //if (*(parent+1) < 0 || *(parent+1) > *parent) return NULL;
  if (*(parent+1) < 0 )                         return NULL;
  else                                          return *root+4* *(parent+1);
}

int *getRightData( int **root, int *parent)
{
  //if (*(parent+2) < 0 || *(parent+2) < *parent) return NULL;
  if (*(parent+2) < 0)                          return NULL;
  else                                          return *root+4* *(parent+2);
}

bool serarchBT( int **root, int *parent, int *inputData )
{
  int *RightChild, *LeftChild;

  LeftChild  = getLeftData (root, parent);
  RightChild = getRightData(root, parent);

  if ( LeftChild  != NULL && *parent < *LeftChild ){
    *( LeftChild +3)  = 0;
  }
  else if (LeftChild  != NULL && *parent > *LeftChild){
    *( LeftChild +3)  = 1;
  }
  if ( RightChild != NULL && *parent > *RightChild){
    *( RightChild+3)  = 0;
  }
  else if(RightChild != NULL && *parent < *RightChild){
    *( RightChild+3)  = 1;
  }

  //if ( LeftChild  == NULL ) printf("%d\n", *(*root +4* *(parent+1) +3));
  //if ( LeftChild  == NULL ) printf("%d\n", *(*root +4* *(parent+2) +3));

  //if ( LeftChild   == NULL && *(parent+1) == *inputData )  *(*root +4* *(parent+1) +3) = 1;
  //if ( RightChild  == NULL && *(parent+2) == *inputData )  *(*root +4* *(parent+2) +3) = 1;
  

  //printf("*parent=%d, *inputData=%d\n", *parent, *inputData);


 
  if ( *inputData == *parent )    return true;

 

  if ( *parent > *inputData && LeftChild != NULL){
    serarchBT(root, LeftChild, inputData);
  }
  else if (*parent < *inputData && *parent > 0 && RightChild != NULL ){
    serarchBT(root, RightChild, inputData);
  }
  else{
    *(inputData+3)=0;
    return false;
  }
}



int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);

  if ((double)INT_MAX/(double)numNode < 4.0 ){
    exit(0);
  }

  int *nodeList  = malloc((size_t)(4*numNode)*sizeof(int));

  for(int i=0; i<4*numNode; i += 4){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeList[i  ] = data;
    nodeList[i+1] = IdxLeft-1;
    nodeList[i+2] = IdxRight-1;
    nodeList[i+3] = 2;
  }



  int c=0;

  for(int i=4*numNode-4; i>=0;i-=4){

    //if ( nodeList[i+3] == 1)                                                 c++;
    //if ( nodeList[i+3] == 2 && serarchBT(&nodeList, nodeList, nodeList+i))   c++;
    
    if ( serarchBT(&nodeList, nodeList, nodeList+i)) c++;
  }

  //for(int i=0; i<4*numNode; i+=4){
  //  printf("nodeList[i+3]=%d\n", nodeList[i+3]);
  //}


  printf("%d\n", c);


  free(nodeList);

  return 0;
}
