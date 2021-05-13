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
    const void*         value;
    struct iheap_node** ref;

}Node;

typedef struct BHeap_t {
	struct Node_t* 	head;
	struct Node_t*	min;
}BHeap;

void heapInit(BHeap* heap);  // ============================ ok
void heapNodeInit(Node* node, int key);  // ============================ ok
void heapLink(Node* root, Node* child);  // ============================ ok
Node* heapMerge(Node* a, Node* b);  // ============================ ok
Node* heapReverse(Node* h);  // ============================ ok
void heapGetMinNode(BHeap *heap, Node **prev, Node **node);  // ============================ ok
void heapUnion_internal(BHeap* heap, Node* h2);  // ============================ ok
void heapUnion(BHeap *target, BHeap *addition);  // ============================ ok
Node* heapExtractMin(BHeap* heap);  // ============================ ok
void heapRemoveMin(BHeap* heap);  // ============================ ok
Node* heapPeekMin(BHeap* heap);  // ============================ ok
void heapInsert(BHeap* heap, Node* node);  // ============================ ok
void heapDecrease(BHeap* heap, Node* node, int new_key);
void heapDelete(BHeap* heap, Node* node);


void heapInit(BHeap* heap)
{
	heap->head = NULL;
	heap->min  = NULL;
}



void heapNodeInit(Node* node, int key)
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

void heapGetMinNode(BHeap *heap, Node **prevNode2, Node **node)
{
	Node *nodeCur, *prevNode1, *curNode;
    *prevNode2 = NULL;

    if ( !heap->head ) { *node = NULL; return; }

    *node = heap->head;
    prevNode1 = heap->head;
    nodeCur = heap->head->sibling;


	while (nodeCur){

	  if (nodeCur->key < (*node)->key){
        *node = nodeCur;
        *prevNode2 = prevNode1;
	  }

      prevNode1  = nodeCur;
	  nodeCur     = nodeCur->sibling;
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
    heapRemoveMin(target);
    heapRemoveMin(addition);
    heapUnion_internal(target, addition->head);
    addition->head = NULL;
}

Node* heapExtractMin(BHeap* heap)
{
	Node *prev, *node;

	heapGetMinNode(heap, &prev, &node);

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

void heapRemoveMin(BHeap* heap)
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
	if (!heap->min)  heap->min = heapExtractMin(heap);
	return heap->min;
}


void heapDecrease(BHeap* heap, Node* node, int new_key)
{
	Node *parent;
	int   tmp_key;

	if (new_key >= node->key) return;

	node->key = new_key;

	if (heap->min != node){

		if (heap->min && node->key < heap->min->key) heapRemoveMin(heap);

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
    Node *test;
    heapDecrease(heap, node, INT_MIN);
    test = heapExtractMin(heap);
}
//    Node *parent, *prev, *pos;
//    int tmp_key;
//
//    if (heap->min != node){
//      parent = node->parent;
//
//      while (parent){
//        tmp_key       = parent->key;
//        parent->key   = node->key;
//        node->key     = tmp_key;
//
//        if (node==NULL) printf("Oooop!\n");
//        node   = parent;
//        parent = node->parent;
//      }
//
//      prev = NULL;
//      pos  = heap->head;
//
//      while (pos != node){
//        prev = pos;
//        pos  = pos->sibling;
//      }
//
//      if (prev) prev->sibling = node->sibling;
//      else      heap->head    = node->sibling;
//
//      if (node==NULL) printf("Oooopppp!\n");
//      heapUnion_internal(heap, heapReverse(node->child));
//
//    } else heap->min = NULL;
//
//    if (node==NULL) printf("Oooop!\n");
//    node->degree = INT_MAX;
//}






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

     /* allocate heap memory for `L` production lines */
     BHeap **heapLine = (BHeap **)malloc((size_t)(Lsize)*sizeof(BHeap*));

     /* initialize heap memory */
     for (int i=0;i<Lsize;i++){
       heapLine[i] = (BHeap*)malloc(sizeof(BHeap));
       heapInit(heapLine[i]);
     }

     /* allocate deque memory for `L` production lines */
     Deque **leftPoint = (Deque**)malloc((size_t)(Lsize)*sizeof(Deque*));
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
         heapInsert(heapLine[productionLine], node);

       }

       /*=========== merge =============*/
       else{
         brokenLine     = operation_1[o];
         runningLine    = operation_2[o];


         /* merge deques */
         mergeDeque(&leftPoint[runningLine], &rightPoint[runningLine],
                    &leftPoint[brokenLine],  &rightPoint[brokenLine]);

         /* union heap */
         heapUnion(heapLine[runningLine], heapLine[brokenLine]);
       }

     } // for (int o=0;o<Osize;o++)


     /* ============ print deque ================== */
     for(int i=0;i<Lsize;i++)   printDequeLeft(leftPoint[i]);

     for(int i=0;i<Lsize;i++){
       Node *minNode;

       minNode = heapPeekMin(heapLine[i]);
       heapDelete(heapLine[i], minNode);
       minNode = heapPeekMin(heapLine[i]);
       if ( minNode ) printf("Line=%d, min=%d\n", i, minNode->key);
     }

     t++;

     free(operation_0);
     free(operation_1);
     free(operation_2);
     free(packagesHeight);

  }

  return 0;
}
