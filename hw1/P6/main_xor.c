#include<stdio.h>
#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>
#include <string.h>

struct List{
  int data;
  struct List *npx;
};


struct List* XOR(struct List *a, struct List *b)
{
  return (struct List*)((uintptr_t) (a) ^ (uintptr_t) (b));
}


void GetNeighbour(int pos, struct List **prevprev, struct List **prev, struct List **end, struct List **next, struct List **nextnext, struct List **root)
{
  struct List **cursor = end;

  int i;


  for (i=1; i<=pos; i++){
    if (*cursor != NULL) *next   = XOR((*cursor)->npx, *prev);
    *prev   = *cursor;
    *cursor = *next;
  }
 
  *cursor    = *prev;

  if (*cursor==NULL){
    *prev = *root;
    *prevprev = XOR((*prev)->npx, NULL);
    *next = NULL;
    *nextnext = NULL;
    return;
  }


  if (*cursor != NULL) *prev      = XOR((*cursor)->npx, *next);
  if (*prev   != NULL) *prevprev  = XOR((*prev)->npx, *cursor);
  if (*next   != NULL) *nextnext  = XOR((*next)->npx, *cursor);
}

void reverse(struct List **end, struct List **root, int l, int r)
{
  if ( l == r ) return;

  struct List *r_nextnext = NULL;
  struct List *r_next     = NULL;
  struct List *r_cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *r_prev     = NULL;

  struct List *l_next     = NULL;
  struct List *l_cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *l_prev     = NULL;
  struct List *l_prevprev = NULL;

/*-----------------------------------------------*/
  bool doLeftPart = true;

  for (int i=1; i<=r;i++){
    r_next   = XOR(r_cursor->npx, r_prev);
    r_prev   = r_cursor;
    r_cursor = r_next;

    if (i<=l  && doLeftPart){
      l_next   = XOR(l_cursor->npx, l_prev);
      l_prev   = l_cursor;
      l_cursor = l_next;
    }
    else{
      doLeftPart = false;
    }
  }

  r_cursor    = r_prev;
  r_prev      = XOR(r_cursor->npx, r_next);

  if (r_next != NULL) r_nextnext  = XOR(r_next->npx, r_cursor);

/*-----------------------------------------------*/


  l_cursor    = l_prev;
  l_prev      = XOR(l_cursor->npx, l_next);

  if (l_prev != NULL) l_prevprev  = XOR(l_prev->npx, l_cursor);

/*-----------------------------------------------*/

  if (r_next != NULL) r_next->npx = XOR(l_cursor, r_nextnext);
  if (l_prev != NULL) l_prev->npx = XOR(r_cursor, l_prevprev);

  r_cursor->npx = XOR(r_prev, l_prev);
  l_cursor->npx = XOR(l_next, r_next);
 
  if (l_prev == NULL) *end = r_cursor;
  if (r_next == NULL) *root = l_cursor;
}

void printList (struct List *root)
{
    struct List *curr = root;

    struct List *prev = NULL;
    struct List *next;
 
    while (curr != NULL)
    {
        if (curr == NULL){
          printf("root is NULL! %d\n", __LINE__);
          exit(0);
        }
        printf ("%d ", curr->data);
        next = XOR (prev, curr->npx);
        prev = curr;
        curr = next;
    }
  printf("\n");
}

void push(struct List **root, int data)
{
  struct List *newNode = (struct List *)malloc(sizeof (struct List) );
  newNode->data = data;
 
  newNode->npx = *root;
 
  if (*root != NULL)
  {
    (*root)->npx = XOR(newNode, (*root)->npx);
  }
 
  *root = newNode;
}

/* delete the item at the position `pos` counted from the root. The root is designated by zero */
void delete(struct List **end, struct List **root, int pos)
{
  struct List *nextnext = NULL;
  struct List *next     = NULL;
  struct List *cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;

  GetNeighbour(pos, &prevprev, &prev, &cursor, &next, &nextnext, root);

  if (prev == NULL){
    nextnext  = XOR(next->npx, cursor);
    next->npx = XOR(NULL, nextnext);
 
    *end = next;
  }
  else if (next == NULL){
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(next,prevprev);
    
    *root = prev;
  }
  else{
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(next,prevprev);
    nextnext  = XOR(next->npx, cursor);
    next->npx = XOR(prev, nextnext);
  }

  free(cursor);
  cursor = NULL;

}

/* insert `data` before the position `pos` counted from the end. The end is designated by 1 */

void insert(struct List **end, struct List **root, int pos, int data)
{
  struct List *new = (struct List *)malloc(sizeof (struct List) );
  new->data = data;

  struct List *nextnext = NULL;
  struct List *next     = NULL;
  struct List *cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;

  GetNeighbour(pos, &prevprev, &prev, &cursor, &next, &nextnext, root);

  if (prev == NULL){
    new->npx = XOR(cursor, NULL);
    cursor->npx = XOR(next,new);
    *end = new;
  }
  else if(next == NULL && cursor != NULL){
    new->npx = XOR(prev, cursor);
    cursor->npx = XOR(new, NULL);
    prev->npx  = XOR(new, prevprev);
  }
  else if (cursor == NULL){
    new->npx = XOR(prev, NULL);
    prev->npx = XOR(prevprev, new);
    *root = new;
  }
  else{
    new->npx = XOR(cursor, prev);
    cursor->npx = XOR(next,new);
    prev->npx = XOR(new, prevprev);
  }
}

int main()
{
  int n; // length of sequence
  int q; // number of operations

  scanf("%d %d", &n, &q);

  int number;

  scanf("%d", &number);

  struct List *root = NULL;
  push(&root, number);
  struct List *end = root;

  for(int i=1;i<=n-1;i++){
    scanf("%d", &number);
    insert(&end, &root, 1, number);
  }

  /* reverse list by swapping **root and **end */
  struct List *tmp;
  tmp = root;
  root = end;
  end = tmp;

  /* read operations */
  char operation[10];
  int l_pos, r_pos, value;

  for(int i=0;i<q;i++){
   scanf("%7s", operation);
     if(strcmp(operation, "Delete"  )== 0){
       scanf("%d", &l_pos);
       delete(&end, &root, l_pos);
     }
     if(strcmp(operation, "Insert"  )== 0){
       scanf("%d %d", &l_pos, &value);
       insert(&end, &root, l_pos, value);
     }
     if(strcmp(operation, "Reverse"  )== 0){
       scanf("%d %d", &l_pos, &r_pos);
       reverse(&end, &root, l_pos, r_pos);
     }
  }
  
  //printList(root);
  printList(end);
}
