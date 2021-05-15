#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>



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

void SwapInt(int *x, int *y);
void heapInit(BHeap* heap);  
void heapNodeInit(Node* node, int key);  


void SwapInt(int *x, int *y)
{
    *x = (*x) ^ (*y);
    *y = (*x) ^ (*y);
    *x = (*x) ^ (*y);
}

void heapInit(BHeap *heap)
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


Node* heapMin(BHeap *heap)
{
  Node *root = heap->head;
  Node *curNode = NULL;

  int min = INT_MAX;

  while( root ){
    if ( min > root->key ){
      min     = root->key;
      curNode = root;
      root    = root->sibling;
    }
  }

  return curNode;
}


/* Links binomial trees whose roots have the same degree */
void heapLink(Node* root1, Node* root2)
{
  if (root1->key > root2->key){
     root1->parent = root2;
     root1->sibling = root2->child;
     root2->child = root1;
     root2->degree++
  }
  else{
     root2->parent = root1;
     root2->sibling = root1->child;
     root1->child = root2;
     root1->degree++
  }
}

Node* heapMerge(BHeap *heap1, BHeap *heap2)
{
  BHeap *mergeHeap = (BHeap*)malloc(sizeof(BHeap));
  heapInit(mergeHeap);

  Node *root1 = heap1->head;
  Node *root2 = heap2->head;

  Mode *curNode = mergeHeap->head;

  while( root1 && root2 ){

    if ( root1->degree >= root2->deree ){
     curNode->sibling  = root2;
     root2             = root2->sibling;
    }
    else{
     curNode->sibling  = root1;
     root1             = root1->sibling;
    }
    curNode  = curNode->sibling;
  }

  if( root1 )  curNode->sibling = root1->sibling;
  if( root2 )  curNode->sibling = root2->sibling;

  return mergeHeap;
}

BHeap* heapUnion(BHeap *heap1, BHeap *heap2)
{
  BHeap* unionHeap = (BHeap*)malloc(sizeof(BHeap));
  heapInit(unionHeap);

  unionHeap->head = heapMerge(heap1, heap2);

  free(heap1);
  free(heap2);

  if (unionHeap->head ) return unionHeap;

  Node *prev = NULL;

  Node *x = unionHeap->head;

  Node *next = x->sibling;

  while( next ){
    if ( x->degree != next->degree || (next->next && next->next->degree == x->degree) ){
      prev = x;
      x    = x->sibling;
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

  return unionHeap->head;  
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

int main(){

  //Deque *left  = NULL;
  //Deque *right = NULL;

  //pushDeque(&left, &right,-1);
  //pushDeque(&left, &right, 1);
  //pushDeque(&left, &right, 2);
  //pushDeque(&left, &right, 3);
  //popRightDeque(&right);
  //popRightDeque(&right);
  //popRightDeque(&left);
  //pushDeque(&left, &right, 8);
  //pushDeque(&left, &right, 9);
  //pushDeque(&left, &right, 4);
  //pushDeque(&left, &right, 5);
  //popLeftDeque(&right);
  //popLeftDeque(&left);
  //popLeftDeque(&left);
  //pushDeque(&left, &right, 6);

  //printDequeLeft(left);

  //popRightDeque();



  //exit(0);

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

     /*==================================================*/
     BHeap* heap = (BHeap*)malloc(sizeof(BHeap));
     heapInit(heap);

     /* allocate heap memory for heaps */
     Node **root = (Node**)malloc((size_t)Lsize*sizeof(Node*));

     heap->head = root[0];
     heap->min  = NULL;
     
     Node *curRoot = root[0];

     /* make linked list for heaps */
     for (int i=0;i<Lsize;i++){

       if (i==Lsize-1) curRoot->sibling = NULL;
       else            curRoot->sibling = root[i+1];

       curRoot = curRoot->sibling;
     }

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
         //Node *node = malloc(sizeof(Node));
         //HeapNodeInit(node, packageHeight);
         //HeapInsert(root[productionLine], node);

       }

       /*=========== merge =============*/
       else{
         brokenLine     = operation_1[o];
         runningLine    = operation_2[o];


         /* merge deques */
         mergeDeque(&leftPoint[runningLine], &rightPoint[runningLine],
                    &leftPoint[brokenLine],  &rightPoint[brokenLine]);

         /* union heap */
         //heapUnion(root[runningLine], root[brokenLine]);
       }

     } // for (int o=0;o<Osize;o++)


     /* ============ print deque ================== */
     for(int i=0;i<Lsize;i++)   printDequeLeft(leftPoint[i]);

     for(int i=0;i<Lsize;i++){
       Node *minNode;

       //minNode = heapExtractMin(heapLine[i]);
       //heapGetMinNode(heapLine[i], &minNode);

      // if (minNode && minNode->child){
      //   //heapDecrease(heapLine[i],minNode->child, -1);
      //   printf("%p\n", minNode->child);
      // }
       //minNode = heapPeekMin(heapLine[i]);

     //  if ( minNode )  printf("Line=%d, min=%d, degree=%d, child=%p\n", i, minNode->key, minNode->degree, minNode->child);
     }

     t++;

     free(operation_0);
     free(operation_1);
     free(operation_2);
     free(packagesHeight);

  }

  return 0;
}
