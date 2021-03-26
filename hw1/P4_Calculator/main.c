#include<stdlib.h>
#include<stdio.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX

#define MAX_STRING (1e2)


int top = -1; /*the index of the last element in stack*/

void push(char str[], char data, int line);
char pop(char str[], int line);
void display(char str[], int line);

int main(){

  char *input;
  
  input = (char*)malloc((size_t)(MAX_STRING)*sizeof(char));
  if (input == NULL) printf("input is NULL at %d!\n", __LINE__); exit(0);
  
  scanf( "%s", input);






  
  if (input == NULL) printf("input is NULL at %d!\n", __LINE__); exit(0);
  free(input);

  return 0;
}

void push(char str[], char data, int line)
{
   if (top == MAX_STRING-1 ){
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
      while (top != 0){
        printf("%s", str[top]);
        top--;
      }
      printf("\n");
   }

}

int peek(char str[])
{
   if (top == -1 ){
       printf("stack is empty at %d!\n", line);
   }
   else{
i      return  str(top);
   }









}
