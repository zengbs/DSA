#include<stdlib.h>
#include<stdio.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX

#define MAX_STRING_SIZE 1e2


int top = -1; /*the index of the last element in stack*/

void push(char str[], char data, int line);
char pop(char str[], int line);
void display(char str[], int line);
char peek(char str[], int line);

int main(){

  char *input, *stack;
  
  input = (char*)malloc((size_t)(MAX_STRING_SIZE)*sizeof(char));
  stack = (char*)malloc((size_t)(MAX_STRING_SIZE)*sizeof(char));
  if (input == NULL) { printf("input is NULL at %d!\n", __LINE__); exit(0); }
  
  scanf( "%s", input);


  push( stack, input[0], __LINE__ );
  push( stack, input[1], __LINE__ );
  push( stack, input[2], __LINE__ );
  push( stack, input[3], __LINE__ );
  push( stack, input[4], __LINE__ );

    
  //printf("stack[%d]=%c\n", top, peek(stack, __LINE__));
  
  display(stack, __LINE__); 




  
  if (input == NULL) { printf("input is NULL at %d!\n", __LINE__); exit(0); }
  free(input);

  return 0;
}

void push(char str[], char data, int line)
{
   if (top == MAX_STRING_SIZE-1 ){
       printf("stack overflow at %d!\n", line); exit(0);
   }
   else{
       top++;
       str[top] = data;
   }
}

char pop(char str[], int line)
{
   if (top == -1 ){
       printf("stack underflow at %d!\n", line); return -1; 
   }
   else{
       return str[top];
       top--;
   }
}

void display(char str[], int line)
{
   if (top == -1 ){
       printf("stack is empty at %d!\n", line);
   }
   else{
      while (top != -1){
        printf("%c", str[top]);
        top--;
      }
      printf("\n");
   }

}

char peek(char str[], int line)
{
   if (top == -1 ){
       printf("stack is empty at %d!\n", line); return "\0"; exit(0);
   }
   else{
      return  str[top];
   }
}
