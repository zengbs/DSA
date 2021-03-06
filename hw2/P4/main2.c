#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>


int *getLeftData( int **root, int *parent)
{
  if (*(parent+1) < 0 )                         return NULL;
  else                                          return *root+4* *(parent+1);
}

int *getRightData( int **root, int *parent)
{
  if (*(parent+2) < 0)                          return NULL;
  else                                          return *root+4* *(parent+2);
}

void inorderTraversal( int **root, int **subroot )
{
  int *RightChild, *LeftChild;

  LeftChild  = getLeftData (root, *subroot);
  RightChild = getRightData(root, *subroot);

  if ( LeftChild  != NULL ){
    *(LeftChild+3) = 0;
    inorderTraversal(root, &LeftChild);
  }

  if ( RightChild != NULL ){
    *(RightChild+3) = 0;
    inorderTraversal(root, &RightChild);
  }
}

bool serarchBT( int **root, int *grand, int *parent, int *inputData, bool rightGrand )
{
  int *RightChild, *LeftChild;

  LeftChild  = getLeftData (root, parent);
  RightChild = getRightData(root, parent);


  if ( LeftChild  != NULL ){
    if ( *parent < *LeftChild )                                         *( LeftChild+3)  = 0;
    else if ( grand != NULL && !rightGrand && *grand > *LeftChild  )    *( LeftChild+3)  = 0;
    else if ( grand != NULL && !rightGrand && *grand < *LeftChild  )    *( LeftChild+3)  = 1; 
    else if ( grand != NULL &&  rightGrand && *grand > *LeftChild  )    *( LeftChild+3)  = 1; 
    else if ( grand != NULL &&  rightGrand && *grand < *LeftChild  )    *( LeftChild+3)  = 1; 
    else                                                                *( LeftChild+3)  = 1;

    //if ( *( LeftChild+3)  == 0 ) inorderTraversal(root, &LeftChild);
  }


  if ( RightChild  != NULL ){
    if ( *parent > *RightChild )                                         *( RightChild+3)  = 0;
    else if ( grand != NULL &&  rightGrand && *grand < *RightChild  )    *( RightChild+3)  = 0;
    else if ( grand != NULL &&  rightGrand && *grand > *RightChild  )    *( RightChild+3)  = 1; 
    else if ( grand != NULL && !rightGrand && *grand < *RightChild  )    *( RightChild+3)  = 1; 
    else if ( grand != NULL && !rightGrand && *grand > *RightChild  )    *( RightChild+3)  = 1; 
    else                                                                 *( RightChild+3)  = 1;

    //if ( *( RightChild+3)  == 0 ) inorderTraversal(root, &RightChild);
  }


 
  if ( *inputData == *parent )    return true;

 

  if ( *parent > *inputData && LeftChild != NULL){
    serarchBT(root, parent, LeftChild, inputData, true);
  }
  else if (*parent < *inputData && *parent > 0 && RightChild != NULL ){
    serarchBT(root, parent, RightChild, inputData, false);
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

  nodeList[3] = 1;


  int c=0;

  //for(int i=4*numNode-4; i>=0;i-=4){
  for(int i=0; i<4*numNode-3;i+=4){
    if ( nodeList[i+3] == 1 ) c++;
    if ( nodeList[i+3] == 2 && serarchBT(&nodeList, NULL, nodeList, nodeList+i, true)) c++;

  }

  //for(int i=0; i<4*numNode; i+=4){
  //  printf("nodeList[i+3]=%d\n", nodeList[i+3]);
  //}


  printf("%d\n", c);


  free(nodeList);

  return 0;
}
