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
	struct Node_t*	min;
}BHeap;

void removeMin(BHeap* heap);


void heapInit(BHeap* heap)
{
	heap->head = NULL;
	heap->min  = NULL;
}



void node_init(Node* node, int key)
{
	node->parent   = NULL;
	node->sibling  = NULL;
	node->child    = NULL;
	node->degree   = INT_MAX;
	node->key      = key;
}



void heapLink(Node* root, Node* child)
{
	child->parent = root;
	child->sibling   = root->child;
	root->child   = child;
	root->degree++;
}



Node* heapMerge(Node* a, Node* b)
{
	Node *head = NULL;
	Node **pos = &head;

	while (a && b){
	  if (a->degree < b->degree){
	  	*pos = a;
	  	a = a->sibling;
	  } else {
	  	*pos = b;
	  	b = b->sibling;
	  }
	  pos = &(*pos)->sibling;
	}

	if (a) *pos = a;
	else   *pos = b;

	return head;
}

Node* heapReverse(Node* h)
{
	Node* tail = NULL;
	Node* sibling;

	if (!h) return h;

	h->parent = NULL;

	while (h->sibling){
	  sibling    = h->sibling;
	  h->sibling = tail;
	  tail       = h;
	  h          = sibling;
	  h->parent  = NULL;
	}

	h->sibling = tail;

	return h;
}

void getMinNode(BHeap *heap, Node **prev, Node **node)
{
	Node *nodeCur = heap->head;

    int min = INT_MAX;


	while (nodeCur){

	  if (nodeCur->key < min){
        min = nodeCur->key;
        *node = nodeCur;
	  }

      *prev  = nodeCur;
	  nodeCur  = nodeCur->sibling;
	}
}

void heapUnion_internal(BHeap* heap, Node* h2)
{
	Node* h1;
	Node *prev, *x, *sibling;

	if (!h2) return;

	h1 = heap->head;

	if (!h1){
      heap->head = h2;
      return;
	}

	h1      = heapMerge(h1, h2);
	prev    = NULL;
	x       = h1;
	sibling = x->sibling;

	while (sibling){
	  if (x->degree != sibling->degree || ((sibling->sibling != NULL) && sibling->sibling->degree == x->degree)){
	  	prev = x;
	  	x    = sibling;
	  } else if (x->key <= sibling->key){
	  	x->sibling = sibling->sibling;
	  	heapLink(sibling, x);
	  } else {

	  	if (prev) prev->sibling = sibling;
	  	else      h1 = sibling;

	  	heapLink(x, sibling);
	  	x = sibling;
	  }
	  sibling = x->sibling;
	}

	heap->head = h1;
}


void heapUnion(BHeap *target, BHeap *addition)
{
    removeMin(target);
    removeMin(addition);
    heapUnion_internal(target, addition->head);
    addition->head = NULL;
}

Node* extractMin(BHeap* heap)
{
	Node *prev, *node;

	getMinNode(heap, &prev, &node);

	if (!node) return NULL;

	if (prev) prev->sibling = node->sibling;
	else      heap->head    = node->sibling;

	heapUnion_internal(heap, heapReverse(node->child));

	return node;
}

void heapInsert(BHeap* heap, Node* node)
{
	Node *min;
	node->child     = NULL;
	node->parent    = NULL;
	node->sibling   = NULL;
	node->degree    = 0;

	if (heap->min && node->key < heap->min->key){

	  min = heap->min;
	  min->child     = NULL;
	  min->parent    = NULL;
	  min->sibling   = NULL;
	  min->degree    = 0;
	  heapUnion_internal(heap, min);
	  heap->min      = node;

	} else heapUnion_internal(heap, node);
}

void removeMin(BHeap* heap)
{
	Node* min;
	if (heap->min){
		min = heap->min;
		heap->min = NULL;
		heapInsert(heap, min);
	}
}


Node* heapPeekMin(BHeap* heap)
{
	if (!heap->min)  heap->min = extractMin(heap);

	return heap->min;
}


void heapDecrease(BHeap* heap, Node* node, int new_key)
{
	Node *parent;
	int   tmp_key;

	if (new_key >= node->key) return;

	node->key = new_key;

	if (heap->min != node){

		if (heap->min && node->key < heap->min->key) removeMin(heap);

		parent = node->parent;

		while (parent && node->key < parent->key){
			tmp_key       = parent->key;
			parent->key   = node->key;
			node->key     = tmp_key;

			node           = parent;
			parent         = node->parent;
		}
	}
}

void heapDelete(BHeap* heap, Node* node)
{
	Node *parent, *prev, *pos;
	int tmp_key;


	if (heap->min != node){
	  parent = node->parent;

	  while (parent){
	  	tmp_key       = parent->key;
	  	parent->key   = node->key;
	  	node->key     = tmp_key;


	  	node   = parent;
	  	parent = node->parent;
	  }

	  prev = NULL;
	  pos  = heap->head;

	  while (pos != node){
	  	prev = pos;
	  	pos  = pos->sibling;
	  }

	  if (prev) prev->sibling = node->sibling;
	  else      heap->head    = node->sibling;

	  heapUnion_internal(heap, heapReverse(node->child));

	} else heap->min = NULL;


	node->degree = INT_MAX;
}






/* Deque */
typedef struct Deque_t{
  int data;
  struct Deque_t *npx;
}Deque;


Deque* XOR(Deque *a, Deque *b)
{
  return (Deque*)((uintptr_t) (a) ^ (uintptr_t) (b));
}


void printList (Deque *endPoint)
{
    Deque *curr = endPoint;

    Deque *prev = NULL;
    Deque *sibling;

    while (curr != NULL)
    {
        printf ("%d ", curr->data);
        sibling = XOR (prev, curr->npx);
        prev = curr;
        curr = sibling;
    }
  printf("\n");
}



void pushDeque(Deque **endPoint, int data)
{
  Deque *newNode = (Deque *) malloc (sizeof (Deque) );
  newNode->data = data;
  newNode->npx = *endPoint;

  if (*endPoint != NULL)
  {
      (*endPoint)->npx = XOR(newNode, (*endPoint)->npx);
  }

  *endPoint = newNode;
}


void popDeque(Deque **endPoint)
{
  Deque *siblingNode;
  Deque *siblingsiblingNode;

  siblingNode     = (*endPoint)->npx;

  if (siblingNode != NULL){

    siblingsiblingNode = XOR(siblingNode->npx, *endPoint);
    siblingNode->npx  = siblingsiblingNode;

    free(*endPoint);
    *endPoint = siblingNode;
  }
  else{
    free(*endPoint);
    *endPoint = NULL;
  }
}

void mergeDeque(Deque *tail, Deque *head)
{
  if (tail != NULL && head != NULL){
    Deque *tailPrev = XOR( tail->npx, NULL );
    tail->npx = XOR( tailPrev, head );

    Deque *headNext = XOR( NULL, head->npx );
    head->npx = XOR( NULL, headNext );
  }
  else if (tail == NULL && head != NULL){
    tail = head;
  }
}

int main(){


//  Deque *left  = NULL;
//  Deque *right = NULL;
//
//  pushDeque(&left, 1);
//
//  right = left;
//
//  pushDeque(&left, 2);
//  pushDeque(&left, 3);
//  pushDeque(&right, 99);
//  pushDeque(&left, 4);
//  popDeque(&left);
//  pushDeque(&right, -1);
//  pushDeque(&right, 0);
//  popDeque(&right);
//  pushDeque(&right, 55);
//
//
//  printList(left);


//  #define N 10
//
//  int A[N]   = {-1, 3, 5, 7, 2, 77, -3, 9, -25, -26};
//  int B[N] = {-5, 5, 6, 654, 852, -2, -43696, 1, 2, 3};
//
//  BHeap *heapA = (BHeap*)malloc(sizeof(BHeap));
//  BHeap *heapB = (BHeap*)malloc(sizeof(BHeap));
//  heapInit(heapA);
//  heapInit(heapB);
//
//  for (int i=0;i<N;i++){
//    Node  *nodeA = (Node*)malloc(sizeof(Node));
//    node_init(nodeA, A[i]);
//    heapInsert(heapA, nodeA);
//    Node  *nodeB = (Node*)malloc(sizeof(Node));
//    node_init(nodeB, B[i]);
//    heapInsert(heapB, nodeB);
//  }
//
//  Node *minA = NULL;
//
//  //getMinNode(heapA, &minAprev, &minA);
//  //printf("%d\n", minA->key);
//
//  //heapUnion(heapA, heapB);
//
//  minA = heapPeekMin(heapA);
//
//
//  printf("%d\n", minA->key);



/*-------------------------*/

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

     /* allocate heap memory for `L` production lines */
     BHeap **heapLine = (BHeap **)malloc((size_t)(Lsize)*sizeof(BHeap*));

     /* initialize heap memory */
     for (int i=0;i<Lsize;i++){
       heapLine[i] = (BHeap*)malloc(sizeof(BHeap));
       heapInit(heapLine[i]);
     }

     /* allocate deque memory for `L` production lines */
     Deque **dequeFirst = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));
     Deque **dequeLast  = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));

     /* initialize deque pointer */
     for (int i=0;i<Lsize;i++){
       dequeFirst[i] = NULL;
       dequeLast[i]  = NULL;
     }


     int firstPush = 0;

     /*
     * perform `push` or `merge` on deque or heaps
     * and try to `pop out` from heap or deque
     *  */
     for (int o=0;o<Osize;o++){

       if (operation_0[o] == 0){ // push
         packageHeight  = operation_1[o];
         productionLine = operation_2[o];

         /* A. push `packageHeight` into deque */
         pushDeque(&dequeFirst[productionLine], packageHeight);

         if (firstPush == 0) dequeLast[productionLine] = dequeFirst[productionLine];

         /* B. insert into heap */
         Node *node = malloc(sizeof(Node));
         node_init(node, packageHeight);
         heapInsert(heapLine[productionLine], node);

         firstPush++;
       }
       else{                     // merge
         brokenLine     = operation_1[o];
         runningLine    = operation_2[o];

         /* merge deques */
         mergeDeque(dequeLast[runningLine], dequeFirst[brokenLine]);

         /* union heap */
         heapUnion(heapLine[runningLine], heapLine[brokenLine]);
       }

     }

     t++;

     free(operation_0);
     free(operation_1);
     free(operation_2);
     free(packagesHeight);
  }

  return 0;
}
