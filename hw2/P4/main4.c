#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

#define MAX( a, b )     (  ( (a) > (b) ) ? (a) : (b)  )
#define MIN( a, b )     (  ( (a) < (b) ) ? (a) : (b)  )

int *getLeftData( int *root, int *parent)
{
  if (*(parent+1) < 0 )                         return NULL;
  else                                          return root+6* *(parent+1);
}

int *getRightData( int *root, int *parent)
{
  if (*(parent+2) < 0)                          return NULL;
  else                                          return root+6* *(parent+2);
}


void serarchBT( int *root, int *parent )
{
  int *RightChild, *LeftChild;
  int upper, lower;

  LeftChild  = getLeftData (root, parent);
  RightChild = getRightData(root, parent);

 // printf("*parent=%d\n", *parent);

  if ( LeftChild != NULL){
//    printf("*LeftChild=%d, *(LeftChild+3)=%d\n", *(LeftChild), *(LeftChild+3));


    upper = MIN( *parent,  *(parent+5) );
    lower = MIN( *parent,  *(parent+4) );
   
    *(LeftChild+4) = lower;
    *(LeftChild+5) = upper;

    if ( lower < *LeftChild && *LeftChild < upper ) *(LeftChild+3) = 1;

    if ( *LeftChild < lower && lower < upper )      *(LeftChild+3) = 0;

    if ( lower < upper && upper < *LeftChild )      *(LeftChild+3) = 0;

    if ( lower >= upper )                           *(LeftChild+3) = 0;

    serarchBT(root, LeftChild);

  }

  if ( *parent > 0 && RightChild != NULL ){
    //printf("*RightChild=%d, *(RightChild+3)=%d\n", *(RightChild), *(RightChild+3));

    lower = MAX( *parent,  *(parent+4) );
    upper = MAX( *parent,  *(parent+5) );

    *(RightChild+4) = lower;
    *(RightChild+5) = upper;

    if ( lower < *RightChild && *RightChild < upper ) *(RightChild+3) = 1;

    if ( *RightChild < lower && lower < upper )       *(RightChild+3) = 0;

    if ( lower < upper && upper < *RightChild )       *(RightChild+3) = 0;

    if ( lower >= upper )                             *(RightChild+3) = 0;

    serarchBT(root, RightChild);

  }
}



int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);


  int *nodeList  = malloc((size_t)(6*numNode)*sizeof(int));


  for(int i=0; i<6*numNode; i += 6){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeList[i  ] = data;
    nodeList[i+1] = IdxLeft-1;
    nodeList[i+2] = IdxRight-1;
    nodeList[i+3] = 2;
    nodeList[i+4] = INT_MIN;
    nodeList[i+5] = INT_MIN;
  }


  nodeList[3] = 1;
  nodeList[4] = INT_MIN;
  nodeList[5] = INT_MAX;

  serarchBT(nodeList, nodeList);



  //for(int i=0; i<6*numNode; i+=6){
  //  printf("%2d %2d %2d %2d %10d %10d\n",
  //         nodeList[i], nodeList[i+1], nodeList[i+2], nodeList[i+3], nodeList[i+4], nodeList[i+5]);
  //}

  int c = 0;

  for(int i=0; i<6*numNode; i+=6){
    if (nodeList[i+3] == 1) c++;
  }

  printf("%d\n", c);

  free(nodeList);

  return 0;
}
