#include<stdio.h>

int main(){

  int A[6] = {2,0,1,3,4,3}; // The array given by statement
  int i=3;                  // initial position of the frog
  int j=0;                  // counter of loop
  
  while(1){
  
    int next = A[i];
  
    if ( A[i] == i ){
      printf("Frog will stop!\n");
      break;
    }
    else if( j == 6 ){
      printf("Frog will keep jumping forever!\n");
      break;
    }
  
    i = next;
    j++;
  }
  
  return 0;

}
