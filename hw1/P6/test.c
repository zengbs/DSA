#include<stdlib.h>
#include<stdio.h>

int main(){

int *arr = (int*)malloc(10*sizeof(int));

for(int i=0;i<10;i++){
  arr[i] = i;
}

int *ptr = &arr[5];

for(int i=0;i<5;i++){
  printf("%d", ptr[i]);
}


return 0;
}
