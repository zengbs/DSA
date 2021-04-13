#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>


int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int main(){
  int n; // length of sequence
  int q; // number of operations
  int number; // appended number

  scanf("%d %d", &n, &q);

  struct List *root = NULL;
  int * array     = (int*)calloc(n, sizeof(int));

  for(int i=0;i<n;i++){
    scanf("%d", &number);
    array[i]     = number;
  }




  /* read operations */
  char operation[10];
  int l_pos, r_pos, value, k;

  for(int i=0;i<q;i++){
   scanf("%7s", operation);
     //if(strcmp(operation, "Delete"  )== 0){
     //  scanf("%d", &l_pos);
     //  delete(&root, l_pos);
     //}
     //if(strcmp(operation, "Insert"  )== 0){
     //  scanf("%d %d", &l_pos, &value);
     //  insert(&end, &root, l_pos, value);
     //}
     //if(strcmp(operation, "Reverse"  )== 0){
     //  scanf("%d %d", &l_pos, &r_pos);
     //  reverse(&end, &root, l_pos, r_pos);
     //}
     if(strcmp(operation, "Query"  )== 0){

       scanf("%d %d %d", &l_pos, &r_pos, &k);
       int * arraySort = (int*)calloc(r_pos-l_pos+1, sizeof(int));

       for(int i=l_pos-1;i<r_pos;i++){
         arraySort[i-l_pos+1]     = array[i];
       }


       qsort (arraySort, r_pos-l_pos+1, sizeof(int), compare);
       printf("%d\n", arraySort[k-1]);
     }
  }


  return 0;
}
