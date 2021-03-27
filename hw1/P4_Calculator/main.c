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

struct Stack{
  int capacity;
  int top;
  char *stackPtr; 
};

struct Stack* createStack(unsigned long int capacity)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->stackPtr = (char*)malloc((size_t)(stack->capacity) * sizeof(char));
    return stack;
}

void display(struct Stack *stack);
char peek(struct Stack *stack);
char pop(struct Stack *stack);
void push(struct Stack *stack, char item);
void Infix2Postfix(char inFix[], char postFix[]);
void strsplit(char inFix[]);

int main(){

  char *inFix;
  
  if ((inFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }

  struct Stack *stack = createStack((unsigned long int)MAX_STACKS_SIZE);

  
 
  //scanf("%s", inFix);
  
  //strsplit(inFix);
  //Infix2Postfix(inFix, numberStack, expressionStack);

  push(stack, '1');
  push(stack, '2');
  push(stack, '3');
  push(stack, '4');
 
  display(stack); 




  
  if (inFix == NULL) { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }
  free(inFix);

  return 0;
}

void push(struct Stack *stack, char item)
{
  if (stack->top == stack->capacity - 1){
    printf("stack overflow!\n");
    exit(0);
  }
  else{
    stack->stackPtr[++stack->top] = item;
  }
}

char pop(struct Stack *stack)
{
  if (stack->top == - 1){
    printf("stack underflow!\n");
    exit(0);
  }
  else{
    return stack->stackPtr[stack->top--];
  }
}

char peek(struct Stack *stack)
{
  if (stack->top == - 1){
    printf("stack is empty!\n");
    exit(0);
  }
  else{
    return stack->stackPtr[stack->top];
  }

}

void display(struct Stack *stack)
{
  if (stack->top == - 1){
    printf("stack is empty!\n");
    exit(0);
  }
  else{
      for(int i=stack->top; i > -1; i--){
        printf("%c", stack->stackPtr[i]);
      }
      printf("\n");
  }
}

void Infix2Postfix(char inFix[], char postFix[])
{


}

void strsplit(char inFix[])
{
  char *token = strtok(inFix, "+-*/()");

  while(token != NULL){
    printf("%s\n", token);
    token = strtok(NULL, "+-*/()");
  }

}


int getPriority(char operator)
{
  if      (operator == '+' || operator == '-') return 0;
  else if (operator == '*' || operator == '/') return 1;
  else     return -1;
}
