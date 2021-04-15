#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


struct node{
  int *data;
  struct node *left, *right;
};

struct node *newNode(int *data, struct node **new)

  *new = (struct node *)malloc(sizeof( struct node));

  (*new)->data  = data;
  (*new)->left  = NULL;
  (*new)->right = NULL;

  return new;
}


struct node *buildBinaryTree(const int *nodeListData, const int *nodeListLeft, const int *nodeListRight, const int numNode)
{
  int *dataRoot;
  int *dataIdxLeft, *dataIdxRight;
  int  IdxLeft, IdxRight;
  struct node *root, *leftChild, *rightChild;


  for(int i=0; i<numNode; i++){
    dataRoot = &nodeListData[i];

    IdxLeft  =  nodeListLeft[i];
    IdxRight =  nodeListRight[i];

    dataIdxLeft  = &nodeListData[IdxLeft];
    dataIdxRight = &nodeListData[IdxRight];

    root  = newNode( dataRoot, &root );
    root  = newNode( dataRoot, &root );

    root->left  = ;
    root->right = ;

  }


  return newNode();
}

int main(){

int numNode, data, IdxLeft, IdxRight;

  scanf("%d", &numNode);

  int *nodeListData  = malloc((size_t)(numNode)*sizeof(int));
  int *nodeListLeft  = malloc((size_t)(numNode)*sizeof(int));
  int *nodeListRight = malloc((size_t)(numNode)*sizeof(int));

  int i = 0;

  for(int i=0; i<numNode; i++){
    scanf("%d %d %d", &data, &IdxLeft, &IdxRight);
    nodeListData [i] = data;
    nodeListLeft [i] = IdxLeft-1;
    nodeListRight[i] = IdxRight-1;
  }





  i = 0;
  for(int node=0; node<numNode; node++){
    printf("%d %d %d\n", nodeList[i], nodeList[i+1]+1, nodeList[i+2]+1);
    i += 3;
  }

  free(nodeList);

  return 0;
}
