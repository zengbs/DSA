#include<stdio.h>

#define N 1000

int main()
{
  printf("%d\n",N);

  for (int i=1;i<=N;i++){
    printf("%d %d %d\n", N-i+1, (i+1), -1);
  }

  return 0;
}
