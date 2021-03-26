#include<stdlib.h>
#include<float.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX


#define MAX_STRING_SIZE 1e2
#define MAX_STACKS_SIZE 1e2


int top = -1; /*the index of the last element in stack*/

void push(char stack[], char data, int line);
char pop(char stack[], int line);
void display(char stack[], int line);
char peek(char stack[], int line);
void Infix2Postfix(char src[], char tar[]);

int main(){

  char *inFix, *postFix, *stack;
  
  if ((inFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }

  if ((postFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("postFix is NULL at %d!\n", __LINE__); exit(0); }

  if ((stack = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }
 
 
  scanf("%s", inFix);

  Infix2Postfix(inFix, postFix);

 
  //for (int i=0;i<stacklen(inFix);i++){
  //  if ( inFix[i] == "+" || inFix[i] == "-" ||
  //       inFix[i] == "*" || inFix[i] == "/" ||
  //       inFix[i] == "(" || inFix[i] == ")"    ){ /* operators */
  //  }
  //  else{  /* number */
  //        push( stack, inFix[i], __LINE__ );
  //  }
  //}
  
  //display(stack, __LINE__); 




  
  if (inFix == NULL) { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }
  free(inFix);
  free(stack);

  return 0;
}

void push(char stack[], char data, int line)
{
   if (top == MAX_STACKS_SIZE-1 ){
       printf("stack overflow at %d!\n", line); exit(0);
   }
   else{
       top++;
       stack[top] = data;
   }
}

char pop(char stack[], int line)
{
   if (top == -1 ){
       printf("stack underflow at %d!\n", line); return -1; 
   }
   else{
       return stack[top];
       top--;
   }
}

void display(char stack[], int line)
{
   if (top == -1 ){
       printf("stack is empty at %d!\n", line);
   }
   else{
      while (top != -1){
        printf("%c", stack[top]);
        top--;
      }
      printf("\n");
   }

}

char peek(char stack[], int line)
{
   if (top == -1 ){
       printf("stack is empty at %d!\n", line); return '\0'; exit(0);
   }
   else{
      return  stack[top];
   }
}

void Infix2Postfix(char inFix[], char postFix[])
{
   long int lengthNumber = 0;

   for(long int i=0;inFix[i] != '\0';i++){
      if (isdigit(inFix[i])){
         push(inFix[i]-'0', inFix[i], __LINE__);
         lengthNumber++;
      }
      else{
         if (lengthNumber > 0) push(NAN, inFix[i], __LINE__);
         push(inFix[i], inFix[i], __LINE__);
         lengthNumber = 0;
      }
   

   }


}
