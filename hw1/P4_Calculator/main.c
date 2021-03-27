#include<stdlib.h>
#include<stdbool.h>
#include<float.h>
#include<math.h>
#include<ctype.h>
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
void Infix2Postfix(char inFix[], char numberStack[], char expressionStack[]);
void strsplit(char inFix[]);

int main(){

  char *inFix, *numberStack, *expressionStack;
  
  if ((inFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }

  if ((expressionStack = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("NULL at %d!\n", __LINE__); exit(0); }

  if ((numberStack = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("NULL at %d!\n", __LINE__); exit(0); }

 
 
  scanf("%s", inFix);
  
  strsplit(inFix);
  //Infix2Postfix(inFix, numberStack, expressionStack);

 
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
  free(expressionStack);
  free(numberStack);

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

void Infix2Postfix(char inFix[], char numberStack[], char expressionStack[])
{


}

void strsplit(char inFix[])
{
  char *token = strtok(inFix, "+-*/()");

  while(token != NULL){
    printf("%f\n", strtod(token, NULL));
    token = strtok(NULL, "+-*/()");
  }

}
