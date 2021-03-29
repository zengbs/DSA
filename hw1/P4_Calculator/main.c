#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<float.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX


#define MAX_STRING_SIZE 1000000 
#define MAX_STACKS_SIZE 1000000 



struct Stack{
  long int capacity;
  long int top;
  char *stackPtr; 
};

struct StackDouble{
  long int capacity;
  long int top;
  double *stackPtr; 
};

void displayString(char str[]);
long int ismydigit(long int c );
void displayStack(struct Stack *stack);
void displayStackDouble(struct StackDouble *stack);
char peek(struct Stack *stack, long int line);
double peekDouble(struct StackDouble *stack, long int line);
char pop(struct Stack *stack, int line);
double popDouble(struct StackDouble *stack, int line);
void push(struct Stack *stack, char item);
void pushDouble(struct StackDouble *stack, double item);
void Infix2Postfix(char inFix[], char postFix[]);
void strsplit(char inFix[]);
long int getPriority(char operatorStack, char operator);
void freeStack(struct Stack *stack);
void freeStackDouble(struct StackDouble *stack);
double postfixEvaluation(char postFix[]);

long int main(){

  char *inFix, *postFix;
  double answer;

    if ((inFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
        { printf("is NULL at %d!\n", __LINE__); exit(0); }
    if ((postFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
        { printf("is NULL at %d!\n", __LINE__); exit(0); }
 
  
    while(scanf("%s", inFix) != EOF){

      //displayString(inFix);

      Infix2Postfix(inFix, postFix);
    
      //displayString(postFix);
    
      answer = postfixEvaluation(postFix);
    
      printf("%.16f\n", answer);

      if (inFix == NULL) { printf("inFix is NULL at %d!\n", __LINE__); exit(0); }
      free(inFix);
      if (postFix == NULL) { printf("postFix is NULL at %d!\n", __LINE__); exit(0); }
      free(postFix);

      if ((inFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
          { printf("is NULL at %d!\n", __LINE__); exit(0); }
      if ((postFix = (char*)calloc((size_t)(MAX_STACKS_SIZE),sizeof(char))) == NULL)
          { printf("is NULL at %d!\n", __LINE__); exit(0); }
    }



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

char pop(struct Stack *stack, int line)
{
  if (stack->top == - 1){
    printf("stack underflow at %d!\n", line);
    exit(0);
  }
  else{
    return stack->stackPtr[stack->top--];
  }
}

double popDouble(struct StackDouble *stack, int line)
{
  if (stack->top == - 1){
    printf("stack underflow at %d!\n", line);
    exit(0);
  }
  else{
    return stack->stackPtr[stack->top--];
  }
}

char peek(struct Stack *stack, long int line)
{
  if (stack->top == - 1){
    return '\0';
  }
  else{
    return stack->stackPtr[stack->top];
  }
}

double peekDouble(struct StackDouble *stack, long int line)
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
      for(long int i=stack->top; i > -1; i--){
        printf("%c", stack->stackPtr[i]);
      }
      printf("\n");
  }
}

void displayStackDouble(struct StackDouble *stack)
{
  if (stack->top == - 1){
    printf("stack is empty!\n");
    exit(0);
  }
  else{
      for(long int i=stack->top; i > -1; i--){
        printf("%f\n", stack->stackPtr[i]);
      }
      printf("\n");
  }
}

void displayString(char str[])
{
  for (long int i=0;str[i] != '\0';i++){
     printf("%c", str[i]); 
  }
  printf("\n");
}

void Infix2Postfix(char inFix[], char postFix[])
{
  long int j = 0;
  struct Stack *stack = createStack((unsigned long int)MAX_STACKS_SIZE, sizeof(char));

  for(long int i=0;inFix[i] != '\0';i++){

    if (inFix[i] == '('){
      push(stack, '(');
    }
    else if (ismydigit(inFix[i]) ){
      postFix[j++] = inFix[i];
    }
    else if (inFix[i] == '+' || inFix[i] == '*' ||inFix[i] == '-' || inFix[i] == '/' ){

      /* append a space to number*/
      if (ismydigit(inFix[i-1])) postFix[j++] = ' ';

      long int getOut = getPriority(peek(stack, __LINE__), inFix[i]);

      if (getOut == 1){

        while(getOut){
          postFix[j++] = pop(stack, __LINE__);
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
        postFix[j++] = pop(stack, __LINE__);
      }
      if (peek(stack, __LINE__) == '('){
        pop(stack, __LINE__);
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
     if (peek(stack, __LINE__) != '(') postFix[j++] = pop(stack, __LINE__);
     else                              pop(stack, __LINE__);
  }

  freeStack(stack);
}

double postfixEvaluation(char postFix[])
{
  struct StackDouble *stackResult = createStackDouble((unsigned long int)MAX_STACKS_SIZE, sizeof(double));


  bool inNum = true;;

  for(long int i=0;postFix[i] != '\0';i++){

    /* the first digit of number */
    if ( ismydigit(postFix[i]) && inNum){
      long int numDigit=0;
      for(long int ii=i;postFix[ii] != ' ';ii++) numDigit++;
      double value  = 0.0;
      double base10 = 1.0;
      for(long int d=0; d<numDigit;d++){
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
      next = popDouble(stackResult, __LINE__);
      prev = popDouble(stackResult, __LINE__);
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
    else if (postFix[i] == ' '){
      inNum = true;
    }
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


long int getPriority(char operatorStack, char operator)
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

long int ismydigit(long int c ){
    if (c >= '0' && c <= '9')  return c;
    else                       return 0;
}
