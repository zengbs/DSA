/* Reference:
 * https://www.programiz.com/c-programming/examples/swapping
 * https://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/
 * https://hackmd.io/@zengbs/Bk6pVcdHO
 * */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct PQArray{
    int p;
    int q;
    int r;
};

int compare(const void *struct1, const void *struct2) {
    return ((struct PQArray *)struct1)->p - ((struct PQArray *)struct2)->p;
}


void swap(int *a, int *b)
{
  *a = *a + *b;
  *b = *a - *b;
  *a = *a - *b;
}

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

    struct PQArray *pqrArray = (struct PQArray *)malloc((size_t)numTriangle*sizeof(struct PQArray));


    P[0] = 2;
    P[1] = 5;
    P[2] = 3;
    P[3] = 5;
    P[4] = 3;
    P[5] = 2;
    P[6] = 5;
    P[7] = 0;
        
    Q[0] = 2; 
    Q[1] = 3;
    Q[2] = 5;
    Q[3] = 5;
    Q[4] = 3;
    Q[5] = 2;
    Q[6] = 5;
    Q[7] = 2;
        
    R[0] = 2;
    R[1] = 2;
    R[2] = 1;
    R[3] = 5;
    R[4] = 2;
    R[5] = 2;
    R[6] = 5;
    R[7] = 0;

    
    for (int i=0;i<numTriangle;i++){
      pqrArray[i].p = P[i];
      pqrArray[i].q = Q[i];
      pqrArray[i].r = R[i];
    }


    qsort(pqrArray, numTriangle, sizeof(*pqrArray), compare);


    for (int i=0;i<numTriangle;i++){
      P[i] = pqrArray[i].p;
      Q[i] = pqrArray[i].q;
      R[i] = pqrArray[i].r;
    }

    free(pqrArray);

//    for (int i=0;i<numTriangle;i++){
//      printf("%2d ", pqrArray[i].p);
//    }
//    printf("\n"); 
//
//    for (int i=0;i<numTriangle;i++){
//      printf("%2d ", pqrArray[i].q);
//    }
//    printf("\n"); 
//
//    for (int i=0;i<numTriangle;i++){
//      printf("%2d ", pqrArray[i].r);
//    }
//
//    printf("\n"); 
//    exit(0);

    /* get the minimum item in P[] */
    int minP = INT_MAX;
    int minQ = INT_MAX;
    int minR = INT_MAX;
    for ( int i=0;i<numTriangle;i++ ){
      if ( minP > P[i] ) minP = P[i];
      if ( minQ > Q[i] ) minQ = Q[i];
      if ( minR > R[i] ) minR = R[i];

      if (Q[i] < R[i]) swap( &Q[i], &R[i] );
    } 


    /* get the minimum item in RPQ */
    int minPQR[3] = {minP, minQ, minR};
    int min = INT_MAX;
    for (int i=0;i<3;i++){
      if (min > minPQR[i] ) min = minPQR[i];
    }

    min--;

    /* coordinate shift */
    for (int i=0;i<numTriangle;i++){
      P[i] -= min;
      Q[i] -= min;
      R[i] -= min;
    }


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

