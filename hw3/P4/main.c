// https://www.geeksforgeeks.org/find-the-smallest-window-in-a-string-containing-all-characters-of-another-string/?fbclid=IwAR0WlnOCByoHjm79ikuJOqhwCwj7mfXc6hWqTNU1WjAh4ZVeWI_II_IAxHU

#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<float.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX

//#define VERBOSE
#define MAX_STRING_SIZE 100000
#define ALPHEBET_SIZE       58


void checkPtr(void *ptr, int line)
{    
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }  
}

void printString(char String[])
{
  for(int s=0; String[s] != '\0';s++){
    if (String[s] != '=') printf("%c", String[s]);
  }
  printf("\n");
}


int main(){

  int T;
  scanf("%d", &T);

  char  *String  = (char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  char  *String2 = (char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  int   *Split   = (int*  )calloc((size_t)(MAX_STRING_SIZE),sizeof(int));
  char  *Pattern = (char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
 

  checkPtr(String , __LINE__);
  checkPtr(Pattern, __LINE__);

  int t = 0;

  while(t<T){
  
     scanf("%s", String);
     scanf("%s", Pattern);

     checkPtr(String , __LINE__);
     checkPtr(Pattern, __LINE__);

     int lengthPattern = 0;
     int lengthString = 0;
     int histogramPattern[ALPHEBET_SIZE] = {0};

     /* ======================================================== */
     /* =========== get the histogram of pattern =============== */
     /* ======================================================== */
     for(int p=0; Pattern[p] != '\0';p++){
       histogramPattern[Pattern[p]-'A']++;
       lengthPattern++;
     }
 
     for(int s=0; String[s] != '\0';s++){
       lengthString++;
     }
     
     /* ============== find the shortest sub-string ===================== */
     
     int histogramString[ALPHEBET_SIZE] = {0};

     int distinctMachedChar = 0;

     char *head = &String[0];
     char *tail = head;

     char *targetWinhead = NULL;
     char *targetWintail = NULL;

     int minWin = INT_MAX;
 
     while(*head != '\0'){

       histogramString[(*head)-'A']++;

       if (histogramString[(*head)-'A'] <= histogramPattern[(*head)-'A']) distinctMachedChar++;

       if ( distinctMachedChar == lengthPattern ){

         // try to minimize the length of window
         while( histogramString [(*tail)-'A'] > histogramPattern[(*tail)-'A'] ||
                histogramPattern[(*tail)-'A'] == 0 ){
           
           if( histogramString[(*tail)-'A'] > histogramPattern[(*tail)-'A'] ) 
               histogramString[(*tail)-'A']--;

           tail++;
         }

         // get the length of current window
         int winSize = head-tail+1;
 
         if (minWin > winSize){
           minWin        = winSize;
           targetWinhead = head;
           targetWintail = tail;
         }
       }

       head++;
     }

     if (minWin == INT_MAX) minWin = 0;


     /* ======== remove the leftmost and the shortest window =========== */

     if ( targetWinhead && targetWintail ){

       char *ptr = targetWintail;

       do{
         *ptr = '=';
         ptr++;
       }while(ptr != targetWinhead);

       *ptr = '=';
     }

     /*======= copy String to String2 =========*/

     char *ptr = &String[0];
     int lastIdx = 0;


     while ( *ptr != '\0' ){

       if (*ptr != '='){
         String2[lastIdx] = *ptr;
         lastIdx++;
       }

       ptr++;
     }

     String2[lastIdx] = '\0';

     free(String);
     free(Pattern);

     /*==================== split string by dividers ===============*/

     int hashUpperBound = INT_MAX - (int)'z' - 100;

     int leftSum  = -(int)'A';
     int rightSum = -(int)'A';

     if (lastIdx%2==0) middleIdxInString = lastIdx/2;
     else              middleIdxInString = (lastIdx+1)/2;


     int idxForSplitArray = 0;

     for( int i=0; i<middleIdxInString; i++ ){
 
       leftSum  += (int)String2[i];
       rightSum += (int)String2[lastIdx-i];

       if (leftSum  > hashUpperBound) leftSum  = leftSum  % hashUpperBound;
       if (rightSum > hashUpperBound) rightSum = rightSum % hashUpperBound;

       if (leftSum == rightSum){

         bool GotIt = true;

         /* check the left and right sub-string one-by-one */
         for ( int j=Split[idxForSplitArray];j<=i;j++ ){

           GatIt &= String2[j] == String2[lastIdx-j-1];

         }

         if (GotIt){
           Split[idxForSplitArray]=i+1;
           idxForSplitArray++;
         }
       }
     }


     /* =========== print result =============== */
     //printString(String);
     printString(String2);
  
    t++;
  }


  return 0;

}

