#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>


#define DEBUG
//#define VERBOSE

typedef struct Node_t {
	struct Node_t* 	parent;
	struct Node_t* 	sibling;
	struct Node_t* 	child;

	unsigned int 	degree;
	int			    key;
}Node;

typedef struct BHeap_t {
	struct Node_t* 	head;
}BHeap;


void binomialTreeTraversal( Node* root, int depth)
{
  if (!root) return;


  Node* child      = root->child;
  Node* sibling    = root->sibling;

  printf("%d ", root->key);


  if (depth!=0){
    binomialTreeTraversal(sibling, depth);
  }

  binomialTreeTraversal(child, ++depth);
}

void heapTraversal(BHeap *heap)
{
  if (!heap->head) return;

  Node *root = heap->head;
  int c = 0;
  static int depth;
  while(root){
    depth = 0;
    printf("\n%d: ",c);
    binomialTreeTraversal(root, depth);
    root = root->sibling;
    c++;
  }
}


void checkPtr(void *ptr, int line)
{
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }
}



void SwapInt(int *x, int *y);
void makeHeap(BHeap* heap);
void heapNodeInit(Node* node, int key);
void heapMin(BHeap *heap, Node** prev, Node** minNode);
void heapLink(Node* root1, Node* root2);
Node* heapMerge(BHeap *heap1, BHeap *heap2);
BHeap* heapUnion(BHeap *heap1, BHeap *heap2);
void heapInsert( BHeap **heap, Node *x );
Node* heapReverse(Node* node);
Node* heapExtractMin(BHeap** heap);


void SwapInt(int *x, int *y)
{
    *x = (*x) ^ (*y);
    *y = (*x) ^ (*y);
    *x = (*x) ^ (*y);
}

void makeHeap(BHeap *heap)
{
	heap->head = NULL;
}

void heapNodeInit(Node* node, int key)
{
	node->parent   = NULL;
	node->sibling  = NULL;
	node->child    = NULL;
	node->degree   = INT_MAX;
	node->key      = key;
}


void printHeapRoot(BHeap* heap)
{
  if(!heap)       return;
  if(!heap->head) return;

  Node *curNode = heap->head;

  printf("========== print roots: ");

  while(curNode){
    printf("%d ", curNode->key);
    curNode = curNode->sibling;
  }

  printf("==============\n");

}

void heapMin(BHeap *heap, Node** prev, Node** minNode)
{
  Node *root = heap->head;
  Node *prevRoot = NULL;

  int min = INT_MAX;

  while( root ){

    if ( min > root->key ){
      min     = root->key;
     *minNode = root;
     *prev    = prevRoot;
    }

    prevRoot = root;
    root     = root->sibling;
  }

}


/* Links binomial trees whose roots have the same degree */
void heapLink(Node* root1, Node* root2)
{
  if (root1->key > root2->key){
     root1->parent = root2;
     root1->sibling = root2->child;
     root2->child = root1;
     root2->degree++;
  }
  else{
     root2->parent = root1;
     root2->sibling = root1->child;
     root1->child = root2;
     root1->degree++;
  }
}

Node* heapMerge(BHeap *heap1, BHeap *heap2)
{
# ifdef DEBUG
  checkPtr((void*)heap1, __LINE__);
  checkPtr((void*)heap2, __LINE__);
  checkPtr((void*)heap1->head, __LINE__);
  checkPtr((void*)heap2->head, __LINE__);
# endif

  Node *head  = NULL;
  Node *root1 = heap1->head;
  Node *root2 = heap2->head;


  Node **curNode = &head;


  while( root1 && root2 ){

    if ( root1->degree > root2->degree ){
     *curNode  = root2;
      root2    = root2->sibling;
#     ifdef VERBOSE
      printf("root1->degree > root2->degree\n" );
      checkPtr((void*)*curNode, __LINE__);
#     endif
    }
    else{
     *curNode = root1;
      root1   = root1->sibling;
#     ifdef VERBOSE
      printf("root1->degree <= root2->degree\n" );
      checkPtr((void*)*curNode, __LINE__);
#     endif
    }

#   ifdef DEBUG
    checkPtr((void*)*curNode, __LINE__);
#   endif

    if ( (*curNode)->sibling != NULL )   curNode  = &(*curNode)->sibling;

#   ifdef DEBUG
    checkPtr((void*)*curNode, __LINE__);
#   endif
  }

# ifdef DEBUG
  checkPtr((void*)*curNode, __LINE__);
# endif

  if( root1 )(*curNode)->sibling = root1;
  if( root2 )(*curNode)->sibling = root2;

  return head;
}



BHeap* heapUnion(BHeap *heap1, BHeap *heap2)
{
# ifdef DEBUG
  checkPtr((void*)heap1, __LINE__);
  checkPtr((void*)heap2, __LINE__);
# endif

  if (!heap1->head ) return heap2;
  if (!heap2->head ) return heap2;

  BHeap* unionHeap = (BHeap*)malloc(sizeof(BHeap));

  makeHeap(unionHeap);
  unionHeap->head = heapMerge(heap1, heap2);

  heap2->head = NULL;
  heap1->head = NULL;

  Node *prev = NULL;
  Node *x    = unionHeap->head;
  Node *next = x->sibling;

  while( next ){
    if ( x->degree != next->degree || (next->sibling && next->sibling->degree == x->degree) ){
      prev = x;
      x    = next;
    }else if( x->key <= next->key ){
      x->sibling = next->sibling;
      heapLink( next, x );
    }
    else{

      if( prev ){
        prev->sibling = next;
      }
      else{
        unionHeap->head = next;
      }

      heapLink( x, next );
      x = next;
    }

    next = x->sibling;
  }


  return unionHeap;
}

void heapInsert( BHeap **heap, Node *x )
{

# ifdef DEBUG
  checkPtr((void*)*heap, __LINE__);
# endif

  BHeap* h = (BHeap*)malloc(sizeof(BHeap));

  makeHeap(h);

  x->parent = NULL;
  x->child  = NULL;
  x->sibling = NULL;
  x->degree = 0;
  h->head  = x;

  *heap = heapUnion(*heap, h);
}


Node* heapReverse(Node* node)
{
    Node* tail = NULL;
    Node* next;

    if (!node)  return node;

    node->parent = NULL;

    while (node->sibling) {
      next          = node->sibling;
      node->sibling = tail;
      tail          = node;
      node          = next;
      node->parent  = NULL;
    }

    node->sibling = tail;

    return node;
}

Node* heapExtractMin(BHeap** heap)
{
  Node* prev;
  Node* min;

  heapMin(*heap, &prev, &min);

  if(prev)  prev->sibling = min->sibling;
  else      (*heap)->head    = min->sibling;

  BHeap reverseHeap;

  reverseHeap.head = heapReverse(min->child);

  *heap = heapUnion(*heap, &reverseHeap);
  
  return min; 
}


/*============================ Deque ===================================*/
typedef struct Deque_t{
  int data;
  struct Deque_t *npx;
}Deque;


Deque* XOR(Deque *a, Deque *b)
{
  return (Deque*)((uintptr_t) (a) ^ (uintptr_t) (b));
}


void printDequeRight (Deque *rightPoint)
{
    Deque *curr = rightPoint;

    Deque *prev = NULL;
    Deque *next;


    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
    }
  printf("\n");
}

void printDequeLeft (Deque *leftPoint)
{
   Deque *curr = leftPoint;

   Deque *prev = NULL;
   Deque *next;

   while (curr != NULL)
   {
       printf ("%d ", curr->data);
       next = XOR (prev, curr->npx);
       prev = curr;
       curr = next;
   }

   printf("\n");
}


void pushDeque(Deque **leftPoint, Deque **rightPoint, int data)
{
  Deque *newNode = (Deque *) malloc (sizeof (Deque) );
  newNode->data = data;


  if (*rightPoint != NULL)
  {
    Deque *rightSecondPoint = XOR( (*rightPoint)->npx, NULL );
    newNode->npx = XOR(*rightPoint, NULL);
    (*rightPoint)->npx = XOR(rightSecondPoint, newNode);
  }
  else{
    newNode->npx = XOR(NULL, NULL);
    *leftPoint = newNode;
  }

  *rightPoint = newNode;
}


void popRightDeque(Deque **rightPoint)
{
  Deque *nextNode;
  Deque *nextnextNode;

  nextNode     = (*rightPoint)->npx;

  if (nextNode != NULL){

    nextnextNode = XOR(nextNode->npx, *rightPoint);
    nextNode->npx  = nextnextNode;

    free(*rightPoint);
    *rightPoint = nextNode;
  }
  else{
    free(*rightPoint);
    *rightPoint = NULL;
  }
}

void popLeftDeque(Deque **leftPoint)
{
  Deque *nextNode;
  Deque *nextnextNode;

  nextNode     = (*leftPoint)->npx;

  if (nextNode != NULL){

    nextnextNode = XOR(nextNode->npx, *leftPoint);
    nextNode->npx  = nextnextNode;

    free(*leftPoint);
    *leftPoint = nextNode;
  }
  else{
    free(*leftPoint);
    *leftPoint = NULL;
  }
}

void mergeDeque(Deque **leftPoint_running, Deque **rightPoint_running,
                Deque **leftPoint_broken,  Deque **rightPoint_broken )
{
    if (*rightPoint_running != NULL && *leftPoint_broken != NULL){
      Deque *secondRightPoint_running = XOR( (*rightPoint_running)->npx, NULL );
      (*rightPoint_running)->npx      = XOR( secondRightPoint_running, *leftPoint_broken );

      Deque *secondLeftPoint_broken = XOR( NULL, (*leftPoint_broken)->npx );
      (*leftPoint_broken)->npx      = XOR( *rightPoint_running, secondLeftPoint_broken );

      *rightPoint_running = *rightPoint_broken;
      *leftPoint_broken  = NULL;
      *rightPoint_broken = NULL;
    }
    else if ( *rightPoint_running == NULL && *leftPoint_broken != NULL ) {
      Deque *secondRightPoint_broken = XOR( (*rightPoint_broken)->npx, NULL );
      Deque *secondLeftPoint_broken = XOR( NULL, (*leftPoint_broken)->npx );

      *leftPoint_running  = *leftPoint_broken;
      *rightPoint_running = *rightPoint_broken;

      (*leftPoint_running)->npx  = XOR( secondLeftPoint_broken,  NULL );
      (*rightPoint_running)->npx = XOR( secondRightPoint_broken, NULL );

      *rightPoint_running = *rightPoint_broken;
      *leftPoint_running  = *leftPoint_broken;
      *leftPoint_broken = NULL;
      *rightPoint_broken = NULL;
    }
}

BHeap* makeHeap0degree(int rootKey)
{
  BHeap *heap = (BHeap*)malloc(sizeof(BHeap));
  makeHeap(heap);

  Node* rootNode    = (Node*)malloc(sizeof(Node));

  heapNodeInit( rootNode, rootKey );

  rootNode->parent        = NULL;
  rootNode->sibling       = NULL;
  rootNode->degree        = 0;
  rootNode->child         = NULL;

  heap->head = rootNode;
  return heap;
}


BHeap* makeHeap1degree(int rootKey, int childKey)
{
  BHeap *heap = (BHeap*)malloc(sizeof(BHeap));
  makeHeap(heap);

  Node* rootNode    = (Node*)malloc(sizeof(Node));
  Node* childNode   = (Node*)malloc(sizeof(Node));

  heapNodeInit( rootNode, rootKey );
  heapNodeInit( childNode, childKey );

  rootNode->parent        = NULL;
  rootNode->sibling       = NULL;
  rootNode->degree        = 1;
  rootNode->child         = childNode;

  childNode->parent        = rootNode;
  childNode->sibling       = NULL;
  childNode->degree        = 0;
  childNode->child         = NULL;

  heap->head = rootNode;
  return heap;
}

BHeap* makeHeap2degree(int rootKey, int childKey, int siblingKey, int gchildKey)
{
  BHeap *heap = (BHeap*)malloc(sizeof(BHeap));
  makeHeap(heap);

  Node* rootNode    = (Node*)malloc(sizeof(Node));
  Node* childNode   = (Node*)malloc(sizeof(Node));
  Node* siblingNode = (Node*)malloc(sizeof(Node));
  Node* gchildNode  = (Node*)malloc(sizeof(Node));

  heapNodeInit( rootNode, rootKey );
  heapNodeInit( childNode, childKey );
  heapNodeInit( siblingNode, siblingKey );
  heapNodeInit( gchildNode, gchildKey );

  rootNode->parent        = NULL;
  rootNode->sibling       = NULL;
  rootNode->degree        = 2;
  rootNode->child         = childNode;

  childNode->parent        = rootNode;
  childNode->sibling       = siblingNode;
  childNode->degree        = 1;
  childNode->child         = gchildNode;

  siblingNode->parent        = rootNode;
  siblingNode->sibling       = NULL;
  siblingNode->degree        = 0;
  siblingNode->child         = NULL;

  gchildNode->parent        = childNode;
  gchildNode->sibling       = NULL;
  gchildNode->degree        = 0;
  gchildNode->child         = NULL;

  heap->head = rootNode;

  return heap;
}

int main(){

//  BHeap *heap1 = makeHeap2degree(1, 2, 3, 4);
//  BHeap *heap2 = makeHeap2degree(5, 6, 7, 8);
//
//  BHeap *heap3 = makeHeap2degree(9, 10, 11, 12);
//  BHeap *heap4 = makeHeap2degree(13, 14, 15, 16);
//
//  heapLink(heap1->head, heap2->head);
//  heapLink(heap3->head, heap4->head);
//  heapLink(heap1->head, heap3->head);
//
//
//  binomialTreeTraversal(heap1->head);
//  printf("\n");
//  exit(0);

//  BHeap *heap = (BHeap*)malloc(sizeof(BHeap));
//  makeHeap(heap);
//
//  BHeap *heap1 = makeHeap1degree(1, 2);
//  BHeap *heap2 = makeHeap0degree(3);
//
//  heap->head = heapMerge(heap1, heap2);
//  //heap = heapUnion(heap1, heap2);
//
//  heapTraversal(heap);
//
//  exit(0);
  
  /* number of test cases */
  int Tsize;

  /* number of  packages*/
  int Nsize;

  /* number of operations (merge and push)*/
  int Osize;

  /* number of production line*/
  int Lsize;

  scanf("%d", &Tsize);

  /*operations*/
  char operation[8];

  int t=0;

  while( t < Tsize ){

     scanf("%d %d %d", &Nsize, &Osize, &Lsize);

     /*store input parameters*/
     int *operation_0    = (int*)malloc((size_t)Osize*sizeof(int));
     int *operation_1    = (int*)malloc((size_t)Osize*sizeof(int));
     int *operation_2    = (int*)malloc((size_t)Osize*sizeof(int));
     int *packagesHeight = (int*)malloc((size_t)Nsize*sizeof(int));

     int packageHeight, productionLine, brokenLine, runningLine;

     for (int o=0;o<Osize;o++){

       scanf("%7s", operation);

       if      (strcmp(operation, "push")== 0){
         /* read push parameters */
         scanf("%d %d", &packageHeight, &productionLine);
         operation_0[o] = 0;
         operation_1[o] = packageHeight;
         operation_2[o] = productionLine;
       }

       else if (strcmp(operation, "merge")== 0){
         /* read merge parameters */
         scanf("%d %d", &brokenLine, &runningLine);
         operation_0[o] = 1;
         operation_1[o] = brokenLine;
         operation_2[o] = runningLine;
       }
     }

     /* read packages height */
     for (int n=0;n<Nsize;n++){
       scanf("%d", &packagesHeight[n]);
     }

     /*====================== Heap ============================*/
     /* allocate memory for heaps */
     BHeap **heaps = (BHeap **)malloc(Lsize*sizeof(BHeap*));
     
     heaps[0] = (BHeap *)malloc(Lsize*sizeof(BHeap));
     
     for (int i=0;i<Lsize;i++){
       heaps[i]=heaps[0]+i;
       makeHeap(heaps[i]);
     }

     /*===================== Deque =============================*/
     /* allocate deque memory for `L` production lines */
     Deque **leftPoint   = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));
     Deque **rightPoint  = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));

     /* initialize deque pointer */
     for (int i=0;i<Lsize;i++){
       leftPoint[i]   = NULL;
       rightPoint[i]  = NULL;
     }

     /*
     * perform `push` or `merge` on deque or heaps
     * and try to `pop out` from heap or deque
     *  */
     for (int o=0;o<Osize;o++){

       /*=========== push =============*/
       if (operation_0[o] == 0){
         packageHeight  = operation_1[o];
         productionLine = operation_2[o];

         /* A. push `packageHeight` into deque */

         pushDeque(&leftPoint[productionLine], &rightPoint[productionLine], packageHeight);


         /* B. insert into heap */
         Node *node = malloc(sizeof(Node));
         heapNodeInit(node, packageHeight);
         heapInsert(&heaps[productionLine], node);

       }

       /*=========== merge =============*/
       else{
         brokenLine     = operation_1[o];
         runningLine    = operation_2[o];


         /* merge deques */
         mergeDeque(&leftPoint[runningLine], &rightPoint[runningLine],
                    &leftPoint[brokenLine],  &rightPoint[brokenLine]);

         /* union heap */
         heaps[runningLine] = heapUnion(heaps[runningLine], heaps[brokenLine]);
         heaps[brokenLine]->head  = NULL;
       }

     } // for (int o=0;o<Osize;o++)


     /* ============ print deque ================== */
     
     printf("deque traversal: "); 
     for(int i=0;i<Lsize;i++)   printDequeLeft(leftPoint[i]);

     printf("heap traversal:"); 
     for(int i=0;i<Lsize;i++){
       Node *minNode = NULL;
       Node *prev;
 
      heapTraversal(heaps[i]);
      printf("\n\n");
 
      //printf("ooooo=%d\n", 
      //heaps[i]->head->child->child->key);
      
      heapMin(heaps[i], &prev, &minNode);

      if (minNode)    printf("min: %d\n", minNode->key);
     }

     t++;

     free(operation_0);
     free(operation_1);
     free(operation_2);
     free(packagesHeight);

  }

  return 0;
}
