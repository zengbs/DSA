#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>


#define DEBUG
#define VERBOSE_0
//#define VERBOSE_1

typedef struct Deque_t Deque;

/* heaps */
typedef struct BHeap_t {
	struct Node_t* 	head;
}BHeap;

/* binomial tree */
typedef struct Node_t {
	struct Node_t* 	parent;
	struct Node_t* 	sibling;
	struct Node_t* 	child;

	unsigned int 	degree;
	int			    key;

    Deque*          dequeNode;
}Node;


/* deque */
typedef struct Deque_t{
  struct Node_t* heapNode;
  struct Deque_t *prevNode;
  int data;
  struct Deque_t *npx;
}Deque;

void checkPtr(void *ptr, int line);
void SwapInt(int *x, int *y);
void SwapPtr(void**Ptr1, void**Ptr2);
void makeHeap(BHeap* heap);
void heapNodeInit(Node* node, int key);
void heapPeekMax(BHeap *heap, Node** prev, Node** maxNode);
void heapLink(Node* root1, Node* root2);
Node* heapMerge(BHeap *heap1, BHeap *heap2);
BHeap* heapUnion(BHeap *heap1, BHeap *heap2);
void heapInsert( BHeap **heap, Node *x );
Node* heapReverse(Node* node);
Node* heapExtractMax(BHeap** heap);
void IncreaseKey(BHeap* heap, Node* node, int newKey);
void heapDelete(BHeap **heap, Node* x);


//void freeNode(Node* x)
//{
//# ifdef DEBUG
//  checkPtr((void*)x, __LINE__);
//# endif
// 
//  if (x->dequeNode) free(x->dequeNode);
//
//  x->dequeNode  = NULL;    
//}

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



void IncreaseKey(BHeap* heap, Node* x, int newKey)
{
# ifdef DEBUG
  checkPtr((void*)x, __LINE__);
# endif

  if (newKey < x->key){
    printf("“new key is smaller than current key");
    exit(0);
  }
 
  x->key = newKey;
  
  Node* y = x;

  Node* z = y->parent;

  while( z && y->key > z->key ){
    SwapInt(&y->key, &z->key);
    SwapPtr((void**)&y->dequeNode, (void**)&z->dequeNode);
    y = z;
    z = y->parent;
  }
}


void heapDelete(BHeap **heap, Node* x)
{
#   ifdef DEBUG
    checkPtr((void*)x, __LINE__);
#   endif

  if (x){
    IncreaseKey(*heap, x, INT_MAX);
    Node* maxNode = heapExtractMax(heap);

#   ifdef DEBUG
    checkPtr((void*)maxNode, __LINE__);
#   endif

    free(maxNode);
    maxNode = NULL;
  }
}

void SwapPtr(void**Ptr1, void**Ptr2)
{
  void* temp = *Ptr1;
  *Ptr1 = *Ptr2;
  *Ptr2 = temp;
}


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

void heapPeekMax(BHeap *heap, Node** prev, Node** maxNode)
{
  Node *root = heap->head;
  Node *prevRoot = NULL;

  int max = INT_MIN;

  while( root ){

    if ( max < root->key ){
      max     = root->key;
     *maxNode = root;
     *prev    = prevRoot;
    }

    prevRoot = root;
    root     = root->sibling;
  }

}


/* Links binomial trees whose roots have the same degree */
void heapLink(Node* root1, Node* root2)
{
  if (root1->key < root2->key){
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
# endif

  if (!heap1->head) return heap2->head;
  if (!heap2->head) return heap1->head;

  Node *head  = NULL;
  Node *root1 = heap1->head;
  Node *root2 = heap2->head;


  Node **curNode = &head;


  while( root1 && root2 ){

    if ( root1->degree > root2->degree ){
     *curNode  = root2;
      root2    = root2->sibling;
#     ifdef VERBOSE_1
      printf("root1->degree > root2->degree\n" );
      checkPtr((void*)*curNode, __LINE__);
#     endif
    }
    else{
     *curNode = root1;
      root1   = root1->sibling;
#     ifdef VERBOSE_1
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

  //printf("heap1->head=%p\n", heap1->head);
  //printf("heap2->head=%p\n", heap2->head);


  if (!heap1->head ) SwapPtr((void**)&heap1->head, (void**)&heap2->head);

  //printf("heap1->head=%p\n", heap1->head);
  //printf("heap2->head=%p\n", heap2->head);

  BHeap* unionHeap = (BHeap*)malloc(sizeof(BHeap));

  makeHeap(unionHeap);

  if (!heap1->head && !heap2->head) return heap1;

  unionHeap->head = heapMerge(heap1, heap2);

  heap2->head = NULL;
  heap1->head = NULL;

# ifdef DEBUG
  checkPtr((void*)unionHeap->head, __LINE__);
# endif

  Node *prev = NULL;
  Node *x    = unionHeap->head;
  Node *next = x->sibling;

  while( next ){
    if ( x->degree != next->degree || (next->sibling && next->sibling->degree == x->degree) ){
      prev = x;
      x    = next;
    }else if( x->key >= next->key ){
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

Node* heapExtractMax(BHeap** heap)
{
  if (!(*heap)->head) return NULL;

  Node* prev;
  Node* max;

  heapPeekMax(*heap, &prev, &max);

# ifdef DEBUG
  checkPtr((void*)max, __LINE__);
# endif

  if(prev)  prev->sibling    = max->sibling;
  else      (*heap)->head    = max->sibling;

  BHeap reverseHeap;

  reverseHeap.head = heapReverse(max->child);

  *heap = heapUnion(*heap, &reverseHeap);
  
  return max; 
}


/*============================ Deque ===================================*/

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


void pushDeque(Deque **leftPoint, Deque **prev_rightPoint, Deque **rightPoint, int data)
{
  Deque *newNode    = (Deque *) malloc (sizeof (Deque) );
  newNode->data     = data;

  if (*rightPoint != NULL)
  {
    Deque *rightSecondPoint = XOR( (*rightPoint)->npx, NULL );
    newNode->npx = XOR(*rightPoint, NULL);
    (*rightPoint)->npx = XOR(rightSecondPoint, newNode);
    *prev_rightPoint = XOR((*rightPoint)->npx, NULL);
  }
  else{
    newNode->npx = XOR(NULL, NULL);
    *leftPoint = newNode;
    *prev_rightPoint = NULL;
  }

  *rightPoint = newNode;
}


int peekRightDeque(Deque **rightPoint)
{
   return (*rightPoint)->data;
}

int peekLeftDeque(Deque **leftPoint)
{
   return (*leftPoint)->data;
}

void popRightDeque(Deque **leftPoint, Deque **rightPoint)
{
  Deque *nextNode;
  Deque *nextnextNode;

  nextNode     = (*rightPoint)->npx;

  if (nextNode != NULL){

    nextnextNode = XOR(nextNode->npx, *rightPoint);
    nextNode->npx  = nextnextNode;

    free(*rightPoint);
    *rightPoint = NULL;
    *rightPoint = nextNode;
  }
  else if ( *leftPoint != *rightPoint ){
    free(*rightPoint);
    *rightPoint = NULL;
  }
  else{
    free(*rightPoint);
    *rightPoint = NULL;
   
    if (!*leftPoint) free(*leftPoint);
    *leftPoint = NULL;
  }
}

void popLeftDeque(Deque **leftPoint, Deque **rightPoint)
{
  Deque *nextNode;
  Deque *nextnextNode;

  nextNode     = (*leftPoint)->npx;

  if (nextNode != NULL){

    nextnextNode = XOR(nextNode->npx, *leftPoint);
    nextNode->npx  = nextnextNode;

    free(*leftPoint);
    *leftPoint = NULL;
    *leftPoint = nextNode;
  }
  else if ( *leftPoint != *rightPoint ){
    free(*leftPoint);
    *leftPoint = NULL;
  }
  else{
    free(*leftPoint);
    if(!*rightPoint) free(*rightPoint);
    *leftPoint = NULL;
    *rightPoint = NULL;
  }
}

void popNodeDeque(Deque **target, Deque **prev, Deque **leftPoint, Deque **rightPoint)
{

  if (*target == *leftPoint){
    popLeftDeque(leftPoint, rightPoint);
  }
  else if (*target == *rightPoint){
    popRightDeque(leftPoint, rightPoint);
  }
  else{

#   ifdef DEBUG
    checkPtr((void*)*target, __LINE__);
#   endif

    Deque *next     = XOR((*target)->npx, *prev);

#   ifdef DEBUG
    checkPtr((void*)*target, __LINE__);
    checkPtr((void*)next, __LINE__);
    checkPtr((void*)*prev, __LINE__);
#   endif
    Deque *nextnext = XOR( *target    , next->npx);
    Deque *prevprev = XOR((*prev)->npx,   *target);
    next->npx = XOR(*prev, nextnext);
    (*prev)->npx = XOR(prevprev, next);
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
#     ifdef DEBUG
      checkPtr((void*)*rightPoint_broken, __LINE__);
#     endif

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


void Checking( Deque **right, Deque **left, BHeap **heap, int *packagesHeight, int Nsize, int *arrIdx )
{
  int  height;
  bool matchRight = false;
  bool matchLeft  = false;
  bool matchMax   = false;
  bool match      = false;

  int n = *arrIdx;

  do{

    if (!*right || !*left) break;
    
    if (match)    height = packagesHeight[++n];
    else          height = packagesHeight[n];

 
    /* E. peek max height from heaps */
    Node *maxNode, *prevNode;
    heapPeekMax(*heap, &prevNode, &maxNode);
#   ifdef DEBUG
    checkPtr((void*)maxNode, __LINE__);
#   endif
    int max = maxNode->key;

    /* F. peek left and right end in deque */
    int rightEnd, leftEnd;
#   ifdef DEBUG
    checkPtr((void*)*right, __LINE__);
    checkPtr((void*)*left,  __LINE__);
#   endif

    rightEnd = peekRightDeque( right ); 
    leftEnd  = peekLeftDeque ( left ); 

#   ifdef VERBOSE_0
    printf("    Compare the %d-th pop package(%d) with the left(%d)/max(%d)/right(%d) package...\n\n",
                             n,            height,         leftEnd,    max, rightEnd);
#   endif

    matchRight = rightEnd == height;
    matchLeft  = leftEnd  == height;
    matchMax   =     max  == height;

    match      = matchRight || matchLeft || matchMax;

    Node *deleteNode;

    if (matchRight){

       deleteNode = (*right)->heapNode;

#      ifdef VERBOSE_0
       printf("  rightEnd(%d) == height(%d) !!\n", rightEnd, height);
#      endif

       popRightDeque(left, right);

       heapDelete(heap, deleteNode);

       (*arrIdx)++;
    }
    else if(matchLeft){

       deleteNode = (*left)->heapNode;

#      ifdef VERBOSE_0
       printf("  leftEnd(%d) == height(%d) !!\n", leftEnd, height);
#      endif

       popLeftDeque(left, right);

       heapDelete(heap, deleteNode);

       (*arrIdx)++;
    }
    else if(matchMax){
#      ifdef VERBOSE_0
       printf("  Max(%d) == height(%d) !!\n", max, height);
#      endif
       maxNode              = heapExtractMax(heap);

#      ifdef DEBUG
       checkPtr((void*)maxNode, __LINE__);
#      endif

       Deque* maxDeque      = maxNode->dequeNode;

#      ifdef DEBUG
       checkPtr((void*)maxDeque, __LINE__);
#      endif

       Deque* prev_maxDeque = maxDeque->prevNode;

       popNodeDeque( &maxDeque, &prev_maxDeque, left, right );
       (*arrIdx)++;
    }


  }while(n<=Nsize && match);


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

     /*====================== Heap initialization ============================*/
     /* allocate memory for heaps */
     BHeap **heaps = (BHeap **)malloc(Lsize*sizeof(BHeap*));
     
     heaps[0] = (BHeap *)malloc(Lsize*sizeof(BHeap));
     
     for (int i=0;i<Lsize;i++){
       heaps[i]=heaps[0]+i;
       makeHeap(heaps[i]);
     }

     /*===================== Deque initialization =============================*/
     /* allocate deque memory for `L` production lines */
     Deque **leftPoint   = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));
     Deque **rightPoint  = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));

     /* initialize end pointers in deque */
     for (int i=0;i<Lsize;i++){
       leftPoint[i]   = NULL;
       rightPoint[i]  = NULL;
     }

     /*
     * perform `push` or `merge` on deque or heaps
     * and try to `pop out` from heap or deque
     *  */

     int arrIdx = 0;

     for (int o=0;o<Osize;o++){

       /*=========== push =============*/
       if (operation_0[o] == 0){
         packageHeight  = operation_1[o];
         productionLine = operation_2[o];

         /* A. insert into heap */
         Node *node = malloc(sizeof(Node));
         heapNodeInit(node, packageHeight);
         heapInsert(&heaps[productionLine], node);

         /* B. push `packageHeight` into deque from right end*/
         Deque *prevNode;
         pushDeque(&leftPoint[productionLine], &prevNode, &rightPoint[productionLine], packageHeight);
      
         // B-1. store the addresss of previous node into the current node
         rightPoint[productionLine]->prevNode = prevNode;

         /* C. store the address of heap node in deque */
         rightPoint[productionLine]->heapNode = node;

         /* D. store the address of deque node in heap */
         node->dequeNode = rightPoint[productionLine];


       }

       /*=========== merge =============*/
       else{
         brokenLine     = operation_1[o];
         runningLine    = operation_2[o];


         /* merge deques */
         mergeDeque(&leftPoint[runningLine], &rightPoint[runningLine],
                    &leftPoint[brokenLine],  &rightPoint[brokenLine]);

         heaps[runningLine] = heapUnion(heaps[runningLine], heaps[brokenLine]);

       }

#      ifdef VERBOSE_0
       if (operation_0[o] == 0 )   printf("\n\npush %d into %d-th line:\n", operation_1[o], operation_2[o]);
       if (operation_0[o] == 1 )   printf("\n\nmerge %d-th into %d-th line:\n", operation_1[o], operation_2[o]);
#      endif

       for (int Line=0; Line<Lsize; Line++){
         if (rightPoint[Line]){
#          ifdef VERBOSE_0
           printf("  Check the %d-th line...\n", Line);
#          endif

#          ifdef DEBUG
           checkPtr((void*)rightPoint[Line], __LINE__);
#          endif
           Checking(&rightPoint[Line], &leftPoint[Line], &heaps[Line], packagesHeight, Nsize, &arrIdx);
         }
       }


     } // for (int o=0;o<Osize;o++)


     if (arrIdx == Nsize ) printf("possible\n");
     else                  printf("impossible\n");

//     /* ============ print deque ================== */
//     
//     printf("\ndeque traversal:\n"); 
//     for(int i=0;i<Lsize;i++)   printDequeLeft(leftPoint[i]);
//
//     /* ============ print heap ================== */
//
//     printf("heap traversal:\n"); 
//     for(int i=0;i<Lsize;i++){
//       Node* max, *prev;
//       heapPeekMax(heaps[i], &prev, &max);
//
//
//       if (max)  heapDelete(&heaps[i], max); 
//       heapTraversal(heaps[i]);
//       printf("\n");
//     }

     t++;

     free(operation_0);
     free(operation_1);
     free(operation_2);
     free(packagesHeight);

     operation_0    = NULL; 
     operation_1    = NULL;
     operation_2    = NULL;
     packagesHeight = NULL; 
 
  }

  return 0;
}
