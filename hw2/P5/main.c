/* Reference:
 * https://www.programiz.com/c-programming/examples/swapping
 * https://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/
 * https://hackmd.io/@zengbs/Bk6pVcdHO
 * https://www.geeksforgeeks.org/merge-sort/
 * */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#include "generator.h"


//#define JUDGE

struct PQRArray{
    int p;
    int q;
    int r;
};


void merge(struct PQRArray *pqrArray, int left, int m, int right)
{
    int i, j, k;
    int idxL = m - left + 1;
    int idxR = right - m;
 
    struct PQRArray *L = (struct PQRArray *)malloc((size_t)idxL*sizeof(struct PQRArray));
    struct PQRArray *R = (struct PQRArray *)malloc((size_t)idxR*sizeof(struct PQRArray));
 
    for (i = 0; i < idxL; i++){
      L[i].p = pqrArray[left + i].p;
      L[i].q = pqrArray[left + i].q;
      L[i].r = pqrArray[left + i].r;
    }

    for (j = 0; j < idxR; j++){
      R[j].p = pqrArray[m + 1 + j].p;
      R[j].q = pqrArray[m + 1 + j].q;
      R[j].r = pqrArray[m + 1 + j].r;
    }
 
    i = j = 0;
    k = left;

    while(i < idxL && j < idxR){
      if(L[i].p <= R[j].p){
        pqrArray[k].p = L[i].p;
        pqrArray[k].q = L[i].q;
        pqrArray[k].r = L[i].r;
        i++;
      }
      else{
        pqrArray[k].p = R[j].p;
        pqrArray[k].q = R[j].q;
        pqrArray[k].r = R[j].r;
        j++;
      }
      k++;
    }
 
    while(i < idxL){
      pqrArray[k].p = L[i].p;
      pqrArray[k].q = L[i].q;
      pqrArray[k].r = L[i].r;
      i++;
      k++;
    }
 
    while(j < idxR){
      pqrArray[k].p = R[j].p;
      pqrArray[k].q = R[j].q;
      pqrArray[k].r = R[j].r;
      j++;
      k++;
    }

    free(L);
    free(R);
}
 
void mergeSort(struct PQRArray *pqrArray, int left, int right)
{
    if (left < right){

      int m = left + (right - left) / 2;
      mergeSort(pqrArray, left, m);
      mergeSort(pqrArray, m + 1, right);
      merge(pqrArray, left, m, right);
    }
}

int compare(const void *struct1, const void *struct2) {
      if ( ((struct PQRArray *)struct1)->p <  ((struct PQRArray *)struct2)->p ) return -1;
      if ( ((struct PQRArray *)struct1)->p == ((struct PQRArray *)struct2)->p ) return 0;
      if ( ((struct PQRArray *)struct1)->p >  ((struct PQRArray *)struct2)->p ) return 1;
}


void swap(int *a, int *b)
{
  *a = *a + *b;
  *b = *a - *b;
  *a = *a - *b;
}

long Sum(int biTree[], int idx)
{
	long sum = 0;

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

long InversionCount(int P[], int Q[], int R[], int numTriangle)
{
    long  numDuplicate = 1;
	long c = 0;

    /* get the maximum item in Q[] */
    long bitSize = 1;

	for (int i=0; i<numTriangle; i++){
      if (bitSize < Q[i]) bitSize = Q[i];
    }

    bitSize++;
   
    int *Bit = (int *)calloc((size_t)bitSize, sizeof(int));  // for unique P[]

    for (int i=numTriangle-1;i>=0;i=i-numDuplicate){

      numDuplicate = 1;

      if( P[i] == P[i-1] ){
        int ii = i;


        while( P[i] == P[ii] ){

          c += Sum(Bit, Q[ii]);
          numDuplicate++; 
          ii--;
        }

        numDuplicate--;

        for ( int jj=i;jj>i-numDuplicate;jj-- ){
          Update(Bit, bitSize, R[jj], 1);
        }

        c += numDuplicate*(numDuplicate-1)/2;

      }
      else{
        c += Sum(Bit, Q[i]);
        Update(Bit, bitSize, R[i], 1);
      }

    }

    free(Bit);
	return c;
}

int main()
{
#   ifndef JUDGE
    int numTriangle = 8;
    int *P = (int *)malloc((size_t)numTriangle*sizeof(int));
    int *Q = (int *)malloc((size_t)numTriangle*sizeof(int));
    int *R = (int *)malloc((size_t)numTriangle*sizeof(int));
#   endif

#   ifdef JUDGE
    generator.init();

    int t = generator.getT();

    while (t--) {

      int numTriangle, *P, *Q, *R;

      generator.getData(&numTriangle, &P, &Q, &R);
#   endif

      struct PQRArray *pqrArray = (struct PQRArray *)malloc((size_t)numTriangle*sizeof(struct PQRArray));

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


//      P[0] = 2;
//      P[1] = 2;
//      P[2] = 2;
//      P[3] = 3;
//      P[4] = 3;
//      P[5] = 3;
//      P[6] = 3;
//      P[7] = 4;
//      P[8] = 5;
//      P[9] = 5;
//          
//      Q[0] = 5; 
//      Q[1] = 3;
//      Q[2] = 2;
//      Q[3] = 3;
//      Q[4] = 6;
//      Q[5] = 5;
//      Q[6] = 3;
//      Q[7] = 3;
//      Q[8] = 6;
//      Q[9] = 7;
//          
//      R[0] = 4;
//      R[1] = 1;
//      R[2] = 1;
//      R[3] = 1;
//      R[4] = 1;
//      R[5] = 3;
//      R[6] = 2;
//      R[7] = 2;
//      R[8] = 2;
//      R[9] = 4;
#     endif
      
      for (int i=0;i<numTriangle;i++){
        pqrArray[i].p = P[i];
        pqrArray[i].q = Q[i];
        pqrArray[i].r = R[i];
      }


      //qsort(pqrArray, numTriangle, sizeof(*pqrArray), compare);
      mergeSort(pqrArray, 0, numTriangle-1);


      for (int i=0;i<numTriangle;i++){
        P[i] = pqrArray[i].p;
        Q[i] = pqrArray[i].q;
        R[i] = pqrArray[i].r;
      }

      free(pqrArray);

//      for (int i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].p);
//      }
//      printf("\n"); 
//
//      for (int i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].q);
//      }
//      printf("\n"); 
//
//      for (int i=0;i<numTriangle;i++){
//        printf("%2d ", pqrArray[i].r);
//      }
//
//      printf("\n"); 
//      exit(0);

      /* get the minimum item in P[] */
//      int minP = LONG_MAX;
      int minQ = INT_MAX;
      int minR = INT_MAX;

      for ( int i=0;i<numTriangle;i++ ){
//        if ( minP > P[i] ) minP = P[i];
        if ( minQ > Q[i] ) minQ = Q[i];
        if ( minR > R[i] ) minR = R[i];

        if (Q[i] < R[i]) swap( &Q[i], &R[i] );
      }


      /* get the minimum item in RPQ */
      int minPQR[3] = {P[0], minQ, minR};
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

    

      long ans = InversionCount(P, Q, R, numTriangle);


   
	  printf("%ld\n",  ans);
#   ifdef JUDGE
    }
#   endif
	return 0;
}

