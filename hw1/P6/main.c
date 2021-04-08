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

void reverse(struct List **end, int l, int r)
{
  struct List *r_nextnext = NULL;
  struct List *r_next     = NULL;
  struct List *r_cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *r_prev     = NULL;
  struct List *r_prevprev = NULL;

  struct List *l_nextnext = NULL;
  struct List *l_next     = NULL;
  struct List *l_cursor   = *end;  /* this pointer will point to the target to be deleted */
  struct List *l_prev     = NULL;
  struct List *l_prevprev = NULL;

/*-----------------------------------------------*/

  for (int i=1; i<=r;i++){
    r_next   = XOR(r_cursor->npx, r_prev);
    r_prev   = r_cursor;
    r_cursor = r_next;
  }

  r_cursor    = r_prev;
  r_prev      = XOR(r_cursor->npx, r_next);

  r_nextnext  = XOR(r_next->npx, r_cursor);
  r_prevprev  = XOR(r_prev->npx, r_cursor);

/*-----------------------------------------------*/

  for (int i=1; i<=l;i++){
    l_next   = XOR(l_cursor->npx, l_prev);
    l_prev   = l_cursor;
    l_cursor = l_next;
  }

  l_cursor    = l_prev;
  l_prev      = XOR(l_cursor->npx, l_next);

  l_nextnext  = XOR(l_next->npx, l_cursor);
  l_prevprev  = XOR(l_prev->npx, l_cursor);

/*-----------------------------------------------*/

  r_next->npx = XOR(l_cursor, r_nextnext);
  l_prev->npx = XOR(r_cursor, l_prevprev);

  r_cursor->npx = XOR(r_prev, l_prev);
  l_cursor->npx = XOR(l_next, r_next);
  
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
void delete(struct List **root, int pos)
{
  struct List *nextnext = NULL;
  struct List *next     = NULL;
  struct List *cursor   = *root;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;


  for (int i=1; i<=pos;i++){
    next   = XOR(cursor->npx, prev);
    prev   = cursor;
    cursor = next;
  }

  cursor    = prev;
  prev      = XOR(cursor->npx, next);
  

  if (prev == NULL){
    nextnext  = XOR(next->npx, cursor);
    next->npx = XOR(NULL, nextnext);
 
    *root = next;
  }
  else if (next == NULL){
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(next,prevprev);
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

/* insert `data` before the position `pos` counted from the root. The root is designated by zero */

void insert(struct List **root, int pos, int data)
{
  struct List *new = (struct List *)malloc(sizeof (struct List) );
  new->data = data;

  struct List *next     = NULL;
  struct List *cursor   = *root;  /* this pointer will point to the target to be deleted */
  struct List *prev     = NULL;
  struct List *prevprev = NULL;


  for (int i=1; i<=pos;i++){
    next   = XOR(cursor->npx, prev);
    prev   = cursor;
    cursor = next;
  }

  cursor = prev;
  prev   = XOR(cursor->npx, next);

  if (prev == NULL){
    new->npx = XOR(cursor, NULL);
    cursor->npx = XOR(next,new);
    *root = new;
  }
  else if(next == NULL){
    new->npx = XOR(NULL, cursor);
    cursor->npx = XOR(new, prev);
    
  }
  else{
    new->npx = XOR(cursor, prev);
    cursor->npx = XOR(next,new);
    prevprev  = XOR(prev->npx, cursor);
    prev->npx = XOR(new, prevprev);
  }
}

int main()
{

struct List *root = NULL;
push(&root, 1);
struct List *end = root;
push(&root, 2);
push(&root, 3);
push(&root, 4);
push(&root, 5);
push(&root, 6);
push(&root, 7);
push(&root, 8);
push(&root, 9);
push(&root, 10);
push(&root, 11);
reverse(&end, 3, 8);

//printList(root);
printList(end);
}
