#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#define MAX( a, b )     (  ( (a) > (b) ) ? (a) : (b)  )
#define MIN( a, b )     (  ( (a) < (b) ) ? (a) : (b)  )

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

bool serarchBT( int **root, int *parent, int *inputData, int lower, int upper )
{
  int *RightChild, *LeftChild;

  LeftChild  = getLeftData (root, parent);
  RightChild = getRightData(root, parent);
 
  if ( *inputData == *parent )    return true;


  if ( *parent > *inputData && LeftChild != NULL){

    upper = MIN( *parent,  upper );

    if ( lower < *LeftChild && *LeftChild < upper ) *(LeftChild+3) = 1;

    if ( *LeftChild < lower && lower < upper )      *(LeftChild+3) = 0;

    if ( lower < upper && upper < *LeftChild )      *(LeftChild+3) = 0;

    if ( (lower > upper) || (lower+1 == upper) )    inorderTraversal(root, &LeftChild);

    serarchBT(root, LeftChild, inputData, lower, upper);

  }
  else if (*parent < *inputData && *parent > 0 && RightChild != NULL ){

    lower = MAX( *parent, lower );

    if ( lower < *RightChild && *RightChild < upper ) *(RightChild+3) = 1;

    if ( *RightChild < lower && lower < upper )       *(RightChild+3) = 0;

    if ( lower < upper && upper < *RightChild )       *(RightChild+3) = 0;

    if ( (lower > upper) || (lower+1 == upper) )      inorderTraversal(root, &RightChild);

    serarchBT(root, RightChild, inputData, lower, upper);

  }
  else{
    *(inputData+3)=0;
    return false;
  }
}



int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);


  int *nodeList  = malloc((size_t)(4*numNode)*sizeof(int));


  for(int i=0; i<4*numNode; i += 4){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeList[i  ] = data;
    nodeList[i+1] = IdxLeft-1;
    nodeList[i+2] = IdxRight-1;
    nodeList[i+3] = 2;
  }

  nodeList[3] = 1;


  int c=0, cc=0;

  for(int i=4*numNode-4; i>=0;i-=4){
    if ( nodeList[i+3] == 1 ) c++;
    if ( nodeList[i+3] == 2 && serarchBT(&nodeList, nodeList, nodeList+i, 0, INT_MAX)) {c++;cc++;}

  }

  //for(int i=0; i<4*numNode; i+=4){
  //  printf("nodeList[i+3]=%d\n", nodeList[i+3]);
  //}


  printf("%d %d\n", c, cc);
  //printf("%d\n", c);


  free(nodeList);

  return 0;
}
