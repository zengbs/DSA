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

void displayString(char str[]);
void displayStack(struct Stack *stack);
char peek(struct Stack *stack, int line);
char pop(struct Stack *stack);
void push(struct Stack *stack, char item);
void Infix2Postfix(char inFix[], char postFix[]);
void strsplit(char inFix[]);
int getPriority(char operatorStack, char operator);

int main(){

  char *inFix, *postFix;
  
  if ((inFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }
  if ((postFix = (char*)malloc((size_t)(MAX_STACKS_SIZE)*sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }


  
 
  scanf("%s", inFix);
  
  Infix2Postfix(inFix, postFix);

  displayString(postFix);

  //push(stack, '1');
  //push(stack, '2');
  //push(stack, '3');
  //push(stack, '4');
 




  
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

char peek(struct Stack *stack, int line)
{
  if (stack->top == - 1){
    return '\0';
  }
  else{
    return stack->stackPtr[stack->top];
  }

}

void displayStack(struct Stack *stack)
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

void displayString(char str[])
{
  for (int i=0;str[i] != '\0';i++){
     printf("%c", str[i]); 
  }
  printf("\n");
}

void Infix2Postfix(char inFix[], char postFix[])
{
  int j = 0;
  struct Stack *stack = createStack((unsigned long int)MAX_STACKS_SIZE);

  for(int i=0;inFix[i] != '\0';i++){

    if (inFix[i] == '('){
      push(stack, '(');
    }
    else if (isdigit(inFix[i]) || isalpha(inFix[i]) ){
      postFix[j++] = inFix[i];
    }
    else if (inFix[i] == '+' || inFix[i] == '*' ||inFix[i] == '-' || inFix[i] == '/' ){

      int getOut = getPriority(peek(stack, __LINE__), inFix[i]);

      if (getOut == 1){

        while(getOut){
          postFix[j++] = pop(stack);
          getOut = getPriority(peek(stack, __LINE__), inFix[i]);
        }

        push(stack, inFix[i]); 
      }
      else if (getOut == 0){
        push(stack, inFix[i]); 
      }
      else{
        printf("error!\n");
        exit(0);
      }
    }
    else if (inFix[i] == ')'){
      while(peek(stack, __LINE__) != '('){
        postFix[j++] = pop(stack);
      }
    }
  }
  while(stack->top > -1 ){
     if (peek(stack, __LINE__) != '(') postFix[j++] = pop(stack);
     else                              pop(stack);
  }
}

void strsplit(char inFix[])
{
  char *token = strtok(inFix, "+-*/()");

  while(token != NULL){
    printf("%s\n", token);
    token = strtok(NULL, "+-*/()");
  }

}


int getPriority(char operatorStack, char operator)
{
  if (operatorStack == '+' ||  operatorStack == '-'){
    if (operator == '*' || operator == '/'){
      return 0;
    }
    else if (operator == '+' || operator == '-'){
      return 1; /*push*/
    }
    else{
      return 0;
    }
  }

  if (operatorStack == '*' ||  operatorStack == '/'){
    if (operator == '+' || operator == '-' || operator == '*' || operator == '/'){
      return 1; /*push*/
    }
    else{
      return 0;
    }
  }

  if ( operatorStack == '\0' || operatorStack == '(' ){
    return 0;
  } 

  return -1;
}
