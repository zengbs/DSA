#include<stdlib.h>
#include<stdio.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX

#define MAX_STRING 1e2


struct st_Stack_char {
   int  maxsize; /*the maximum allowed size*/
   int  top;     /*the size of stack*/
   char *item;    
};


void initializeStack(struct st_Stack_char stack, int maxsize){
   stack.maxsize = maxsize;
   stack.top     = 0;
   stack.items   = NULL;
}


int main(){

  char *input;
  
  input = (char*)malloc((size_t)(MAX_STRING)*sizeof(char));
  if (input == NULL) printf("input is NULL at %d!\n", __LINE__); exit(0);
  
  scanf( "%s", input);



  
  if (input == NULL) printf("input is NULL at %d!\n", __LINE__); exit(0);
  free(input);

  return 0;
}
