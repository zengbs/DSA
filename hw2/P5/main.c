/* Reference:
 * https://www.programiz.com/c-programming/examples/swapping
 * https://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/
 * https://hackmd.io/@zengbs/Bk6pVcdHO
 * */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "generator.h"


#define JUDGE

struct PQArray{
    int p;
    int q;
    int r;
};

int compare(const void *struct1, const void *struct2) {
      if ( ((struct PQArray *)struct1)->p <  ((struct PQArray *)struct2)->p ) return -1;
      if ( ((struct PQArray *)struct1)->p == ((struct PQArray *)struct2)->p ) return 0;
      if ( ((struct PQArray *)struct1)->p >  ((struct PQArray *)struct2)->p ) return 1;
}


void swap(int *a, int *b)
{
  *a = *a + *b;
  *b = *a - *b;
  *a = *a - *b;
}

long Sum(long biTree[], long idx)
{
	long sum = 0;

	while (idx > 0)
	{
	  sum += biTree[idx];

	  idx -= idx & (-idx);
	}
	return sum;
}

void Update(long biTree[], long n, long idx, long data)
{
	while (idx <= n)
	{
  	  biTree[idx] += data;
  
  	  idx += idx & (-idx);
	}
}

long InversionCount(int Q[], int R[], long left, long right, long Bit[], long bitSize)
{
	long c = 0;

	for (long i=right; i>=left; i--){
		c += Sum(Bit, Q[i]);
		Update(Bit, bitSize, R[i], 1);
	}

	return c;
}

int main()
{
#   ifndef JUDGE
    int numTriangle = 8;
    int *P = (int *)malloc((size_t)numTriangle*sizeof(long));
    int *Q = (int *)malloc((size_t)numTriangle*sizeof(long));
    int *R = (int *)malloc((size_t)numTriangle*sizeof(long));
#   endif

#   ifdef JUDGE
    generator.init();

    int t = generator.getT();

    while (t--) {

      int numTriangle, *P, *Q, *R;

      generator.getData(&numTriangle, &P, &Q, &R);
#   endif

      struct PQArray *pqrArray = (struct PQArray *)malloc((size_t)numTriangle*sizeof(struct PQArray));

#     ifndef JUDGE
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
#     endif
      
      for (long i=0;i<numTriangle;i++){
        pqrArray[i].p = P[i];
        pqrArray[i].q = Q[i];
        pqrArray[i].r = R[i];
      }


      qsort(pqrArray, numTriangle, sizeof(*pqrArray), compare);


      for (long i=0;i<numTriangle;i++){
        P[i] = pqrArray[i].p;
        Q[i] = pqrArray[i].q;
        R[i] = pqrArray[i].r;
      }

      free(pqrArray);

//      for (long i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].p);
//      }
//      printf("\n"); 
//
//      for (long i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].q);
//      }
//      printf("\n"); 
//
//      for (long i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].r);
//      }
//
//      printf("\n"); 
//      exit(0);

      /* get the minimum item in P[] */
      long minP = LONG_MAX;
      long minQ = LONG_MAX;
      long minR = LONG_MAX;
      for ( long i=0;i<numTriangle;i++ ){
        if ( minP > P[i] ) minP = P[i];
        if ( minQ > Q[i] ) minQ = Q[i];
        if ( minR > R[i] ) minR = R[i];

        if (Q[i] < R[i]) swap( &Q[i], &R[i] );
      } 


      /* get the minimum item in RPQ */
      long minPQR[3] = {minP, minQ, minR};
      long min = LONG_MAX;
      for (long i=0;i<3;i++){
        if (min > minPQR[i] ) min = minPQR[i];
      }

      min--;

      /* coordinate shift */
      for (long i=0;i<numTriangle;i++){
        P[i] -= min;
        Q[i] -= min;
        R[i] -= min;
      }


      /* get the maximum item in Q[] */
      long bitSize = 1;

	  for (long i=0; i<numTriangle; i++){
        if (bitSize < Q[i]) bitSize = Q[i];
      }

      bitSize++;
   
      long *Bit = (long *)calloc((size_t)bitSize, sizeof(long));

      long ans = InversionCount(Q, R, 0, numTriangle-1, Bit, bitSize);

      free(Bit);

      long numDuplicate = 1;
      long Temp = 0;
      long partialCountTotal=0;

      for (long i=0;i<numTriangle;i=i+numDuplicate){

        numDuplicate = 1;

        long ii = i+1;

        while( P[i] == P[ii] ){

          numDuplicate++; 
 
          ii++;
        }

        if (numDuplicate > 1){
          //printf("i=%d, i+numDuplicate-1=%d, numDuplicate=%d\n", i, i+numDuplicate-1, numDuplicate);
          bitSize = 1;
	      for (long ii=i; ii<=i+numDuplicate-1; ii++){
            if (bitSize < Q[ii]) bitSize = Q[ii];
          }
          bitSize++;
          //printf("bitSize=%d\n", bitSize);
          Bit = (long *)calloc((size_t)bitSize, sizeof(long));

          partialCountTotal += InversionCount(Q, R, i, i+numDuplicate-1, Bit, bitSize);

          free(Bit);

          Temp += numDuplicate*(numDuplicate-1)/2;
        }

      }
   
	  printf("%ld\n",  ans-partialCountTotal+Temp);
#   ifdef JUDGE
    }
#   endif
	return 0;
}

