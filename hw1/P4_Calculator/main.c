#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<float.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX


#define MAX_STRING_SIZE 1e6
#define MAX_STACKS_SIZE 1e6



struct Stack{
  int capacity;
  int top;
  char *stackPtr; 
};

struct StackDouble{
  int capacity;
  int top;
  double *stackPtr; 
};

void displayString(char str[]);
int ismydigit(int c );
void displayStack(struct Stack *stack);
char peek(struct Stack *stack, int line);
double peekDouble(struct StackDouble *stack, int line);
char pop(struct Stack *stack);
double popDouble(struct StackDouble *stack);
void push(struct Stack *stack, char item);
void pushDouble(struct StackDouble *stack, double item);
void Infix2Postfix(char inFix[], char postFix[]);
void strsplit(char inFix[]);
int getPriority(char operatorStack, char operator);
void freeStack(struct Stack *stack);
void freeStackDouble(struct StackDouble *stack);
double postfixEvaluation(char postFix[]);

int main(){

  char *inFix, *postFix;
  double answer;
  
  if ((inFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }
  if ((postFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
      { printf("is NULL at %d!\n", __LINE__); exit(0); }
 
  scanf("%s", inFix);
  
  Infix2Postfix(inFix, postFix);

  displayString(postFix);

  answer = postfixEvaluation(postFix);

  printf("%20.16e\n", answer);

  if (inFix == NULL) { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }
  free(inFix);
  if (postFix == NULL) { printf("postFix is NULL at %d!\n", __LINE__); exit(0); }
  free(postFix);

  return 0;
}

struct Stack* createStack(unsigned long int capacity, size_t sizePerItem)
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->stackPtr = malloc((size_t)(stack->capacity) * sizePerItem);
    return stack;
}

struct StackDouble* createStackDouble(unsigned long int capacity, size_t sizePerItem)
{
    struct StackDouble* stack = (struct StackDouble*)malloc(sizeof(struct StackDouble));
    stack->capacity = capacity;
    stack->top = -1;
    stack->stackPtr = malloc((size_t)(stack->capacity) * sizePerItem);
    return stack;
}

void freeStack(struct Stack *stack)
{
  free(stack->stackPtr);
  free(stack);
}

void freeStackDouble(struct StackDouble *stack)
{
  free(stack->stackPtr);
  free(stack);
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

void pushDouble(struct StackDouble *stack, double item)
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

double popDouble(struct StackDouble *stack)
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

double peekDouble(struct StackDouble *stack, int line)
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
  struct Stack *stack = createStack((unsigned long int)MAX_STACKS_SIZE, sizeof(char));

  for(int i=0;inFix[i] != '\0';i++){

    if (inFix[i] == '('){
      push(stack, '(');
    }
    else if (ismydigit(inFix[i]) ){
      postFix[j++] = inFix[i];
    }
    else if (inFix[i] == '+' || inFix[i] == '*' ||inFix[i] == '-' || inFix[i] == '/' ){

      /* append a space to number*/
      if (ismydigit(inFix[i-1])) postFix[j++] = ' ';

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
      /* append a space to number*/
      if (ismydigit(inFix[i-1])) postFix[j++] = ' ';

      while(peek(stack, __LINE__) != '('){
        postFix[j++] = pop(stack);
      }
      if (peek(stack, __LINE__) == '('){
        pop(stack);
      }
      else{
        printf("Parentheses is not balance!\n");
        exit(0);
      }
    }

    /* append a space to number*/
    if (inFix[i+1] == '\0' && ismydigit(inFix[i])) postFix[j++] = ' ';

  }
  while(stack->top > -1 ){
     if (peek(stack, __LINE__) != '(') postFix[j++] = pop(stack);
     else                              pop(stack);
  }

  freeStack(stack);
}

double postfixEvaluation(char postFix[])
{
  struct StackDouble *stackResult = createStackDouble((unsigned long int)MAX_STACKS_SIZE, sizeof(double));


  bool inNum = true;;

  for(int i=0;postFix[i] != '\0';i++){

    /* the first digit of number */
    if ( ismydigit(postFix[i]) && inNum){
      int numDigit=0;
      for(int ii=i;postFix[ii] != ' ';ii++) numDigit++;
      double value  = 0.0;
      double base10 = 1.0;
      for(int d=0; d<numDigit;d++){
        char digitPtr[2] = {postFix[numDigit+i-1-d], '\0'};
        value += strtod(digitPtr, NULL)*base10;
        base10 *= 10.0;
      }
      /* push the value to the stack */
      pushDouble(stackResult, value);
      inNum = false;
    }

    /* encounter operators */
    else if( postFix[i] == '+' || postFix[i] == '-' || postFix[i] == '*' || postFix[i] == '/' ) {
      inNum = true;
      double result, next, prev;
      next = popDouble(stackResult);
      prev = popDouble(stackResult);
      if (postFix[i] == '+'){
        result = prev + next;
      }
      else if (postFix[i] == '-'){
        result = prev - next;
      }
      else if (postFix[i] == '*'){
        result = prev * next;
      }
      else if (postFix[i] == '/'){
        result = prev / next;
      }

      pushDouble(stackResult, result);
    }

    /*encounter space*/
    else if (postFix[i] == ' ') inNum = true;
  }

  double answer = peekDouble(stackResult, __LINE__);

  freeStackDouble(stackResult);

  return answer;
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
      return 0; /*push*/
    }
    else if (operator == '+' || operator == '-'){
      return 1; /*append to postFix*/
    }
    else{
      return 0; /*push*/
    }
  }

  if (operatorStack == '*' ||  operatorStack == '/'){
    if (operator == '+' || operator == '-' || operator == '*' || operator == '/'){
      return 1; /*append to postFix*/
    }
    else{
      return 0; /*push*/
    }
  }

  if ( operatorStack == '\0' || operatorStack == '(' ){
    return 0; /*push*/ 
  } 

  return -1;
}

int ismydigit(int c ){
    if (c >= '0' && c <= '9')  return c;
    else                       return 0;
}
