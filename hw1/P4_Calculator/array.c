#include<stdlib.h>
#include<stdio.h>

void fun(int *array);
size_t nrows = 10;

int main(){


int *array = (int *)malloc(nrows * sizeof(int));

fun(array);

free(array); 

return 0;
}

void fun(int *array)
{
  for (int i=0;i<nrows;i++)
  {
    //array[i] = i;
    *(array+i) = i;
  }
  
  for (int i=0;i<nrows;i++)
  {
    printf("array[%d]=%d\n", i, array[i]);
  }
}
