#include<stdio.h>
#include<stdlib.h>

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

int InversionCount(int Q[], int R[], int left, int right, int Bit[], int bitSize)
{
	int c = 0;


	for (int i=right; i>=left; i--){
		c += Sum(Bit, Q[i]);
		Update(Bit, bitSize, R[i], 1);
	}

	return c;
}

int main()
{
    int numTriangle = 8;

    int *P = (int *)malloc((size_t)numTriangle*sizeof(int));
    int *Q = (int *)malloc((size_t)numTriangle*sizeof(int));
    int *R = (int *)malloc((size_t)numTriangle*sizeof(int));

    P[0] = 1;
    P[1] = 2;
    P[2] = 2;
    P[3] = 3;
    P[4] = 3;
    P[5] = 5;
    P[6] = 5;
    P[7] = 5;

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

    /* get the maximum item in Q[] */
    int bitSize = 1;

	for (int i=0; i<numTriangle; i++){
      if (bitSize < Q[i]) bitSize = Q[i];
    }
    bitSize++;
   
    int *Bit = (int *)calloc((size_t)bitSize, sizeof(int));

    int ans = InversionCount(Q, R, 0, numTriangle-1, Bit, bitSize);

    free(Bit);

    int numDuplicate = 1;
    int Temp = 0;
    int partialCountTotal=0;

    for (int i=0;i<numTriangle;i=i+numDuplicate){

      numDuplicate = 1;

      int ii = i+1;

      while( P[i] == P[ii] ){

        numDuplicate++; 
 
        ii++;
      }

      if (numDuplicate > 1){
        //printf("i=%d, i+numDuplicate-1=%d, numDuplicate=%d\n", i, i+numDuplicate-1, numDuplicate);
        bitSize = 1;
	    for (int ii=i; ii<=i+numDuplicate-1; ii++){
          if (bitSize < Q[ii]) bitSize = Q[ii];
        }
        bitSize++;
        //printf("bitSize=%d\n", bitSize);
        Bit = (int *)calloc((size_t)bitSize, sizeof(int));

        partialCountTotal += InversionCount(Q, R, i, i+numDuplicate-1, Bit, bitSize);

        Temp += numDuplicate*(numDuplicate-1)/2;
      }

    }


    


	printf("%d\n",  ans-partialCountTotal+Temp);
	return 0;
}

