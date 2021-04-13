#include<stdio.h>

int main(){

  int A[8] = {1,0,4,2,3,1,4,6};   // The array given by statement
  int B[8] = {0};                 // helper array to keep track of where the frog passes
  int i = 2;                      // Initial position of the frog
  int j = 0;                      // loop counter



  while(1){

    if (B[i] != 1){
      B[i] = 1;
      j++;
    }else{
      printf("The length of the loop is %d\n", j);
      break;
    }

    i = A[i];  
  }

  return 0;
}
