#include<stdio.h>

int Sum(int biTree[], int idx)
{
	int sum = 0;

	while (idx > 0)
	{
	  sum += biTree[idx];

	  idx -= idx & (-idx);
	}
	return sum;
}

void Update(int biTree[], int n, int idx, int data)
{
	while (idx <= n)
	{
  	  biTree[idx] += data;
  
  	  idx += idx & (-idx);
	}
}

int InversionCount(int arr[], int n)
{
	int c = 0;

	int size = 0;
	for (int i=0; i<n; i++)
		if (size < arr[i])
			size = arr[i];

	int bit[size+1];
	for (int i=1; i<=size; i++)
		bit[i] = 0;

	for (int i=n-1; i>=0; i--)
	{
		c += Sum(bit, arr[i]-1);

		updatebit(bit, size, arr[i], 1);
	}

	return c;
}

int main()
{
    int numTriangle = 8;

    int *P = (int *)malloc((size_t)numTriangle*sizeof(int));
    int *Q = (int *)malloc((size_t)numTriangle*sizeof(int));

    Q[0] = 2; 
    Q[1] = 2;
    Q[2] = 2;
    Q[3] = 5;
    Q[4] = 3;
    Q[5] = 3;
    Q[6] = 5;
    Q[7] = 5;

    R[0] = 1;
    R[1] = 2;
    R[2] = 2;
    R[3] = 1;
    R[4] = 2;
    R[5] = 2;
    R[6] = 5;
    R[7] = 5;


    

	printf("%d\n",  InversionCount(arr,n));
	return 0;
}

