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


int lastIdxInPwer;

unsigned long long ipow(int power, unsigned long long PowerArray[], unsigned long long hashUpperBound )
{
  if (PowerArray[power] == 0){

    PowerArray[0] = 1;

    for (int i=lastIdxInPwer+1;i<power+1;i++){
      PowerArray[i] = (unsigned long long)ALPHEBET_SIZE*PowerArray[i-1];
      PowerArray[i] = PowerArray[i] % hashUpperBound;
      lastIdxInPwer++;
    }
    return PowerArray[lastIdxInPwer];
  }
  else{
    return PowerArray[power];
  }
}

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

void printString2(char String[])
{
  for(int s=0; String[s] != '\0';s++){

     if (String[s]>=65 && String[s]<=122){
       printf("%c", String[s]);
     }
     else{
       printf("|");
       printf("%c", String[s]-100);
     }


  }
  printf("\n");
}


int main(){


  if (UCHAR_MAX < 255){
    printf("CHAR_MAX=%d!\n", CHAR_MAX);
    exit(0);
  }

  int T;
  scanf("%d", &T);

  char  *String  = (char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  int   *Split   = (int*  )calloc((size_t)(MAX_STRING_SIZE),sizeof(int));
  char  *Pattern = (char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(char));



  unsigned long long hashUpperBound = ((unsigned long long)LLONG_MAX+1)/128;

  unsigned long long *PowerArray = (unsigned long long *)calloc((size_t)(MAX_STRING_SIZE/2+1),sizeof(unsigned long long));

 
  unsigned char  *String2 = (unsigned char* )calloc((size_t)(MAX_STRING_SIZE),sizeof(unsigned char));

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

     /*======= copy removed String to String2 =========*/

     char *ptr = &String[0];
     int lengthString2 = 0;


     while ( *ptr != '\0' ){

       if (*ptr != '='){
         String2[lengthString2] = *ptr;
         String2[lengthString2]-= ((int)'A'-1);
         String [lengthString2] = *ptr;
         lengthString2++;
       }

       ptr++;
     }

     String [lengthString2] = '\0';
     String2[lengthString2] = '\0';


     /*==================== split string by dividers ===============*/



     unsigned long long leftSum ;
     unsigned long long rightSum;

     int middleIdxInString;

     if ((lengthString2-1)%2==0) middleIdxInString = (lengthString2-1)/2;
     else                        middleIdxInString =  lengthString2/2;


     int idxForSplitArray = 0;

     int lengthSplit = 0;

     bool GotIt = true;

     int leftIdx = 0;

     for( int i=0; i<middleIdxInString; i++ ){

       if (GotIt){

#        ifdef VERBOSE
         printf("Start to compute checksum!\n");
#        endif

         leftSum  = (unsigned long long)String2[leftIdx];
         rightSum = (unsigned long long)String2[lengthString2-i-1];
         GotIt = false; 
#        ifdef VERBOSE
         printf("%d, %d\n", leftIdx, lengthString2-i-1);
         printf("leftSum=%lld, rightSum=%lld\n", leftSum, rightSum);
#        endif
       }
       else{
#        ifdef VERBOSE
         printf("Computing checksum...\n");
#        endif
         leftIdx++;
         
         
         leftSum  = leftSum  + String2[leftIdx]*ipow(leftIdx, PowerArray, hashUpperBound);
         rightSum = rightSum * (unsigned long long)ALPHEBET_SIZE + (unsigned long long)String2[lengthString2-i-1];

         leftSum  = leftSum  % hashUpperBound;
         rightSum = rightSum % hashUpperBound;

#        ifdef VERBOSE
         printf("%d, %d\n", leftIdx, rightIdx);
         printf("leftSum=%lld, rightSum=%lld\n", leftSum, rightSum);
#        endif
       }


       if (leftSum == rightSum){

#        ifdef VERBOSE
         printf("Checking match...\n");
#        endif

         GotIt = true;

         /* check the char in the left and right sub-string one-by-one */
         for ( int j=Split[idxForSplitArray];j<=i;j++ ){

           int shift;
           
           if (lengthString2%2==0)    shift = middleIdxInString-i+middleIdxInString-1+j-Split[idxForSplitArray];
           else                       shift = middleIdxInString-i+middleIdxInString+j-Split[idxForSplitArray];

           GotIt &= String2[j] == String2[shift];
         }

         if (GotIt){
#          ifdef VERBOSE
           printf("Got it!\n");
#          endif

           leftIdx=i+1;
           idxForSplitArray++;
           Split[idxForSplitArray]=i+1;
           lengthSplit++;
           String[i+1] += 100;
           if (i+1 != lengthString2-i-1) String[lengthString2-i-1] += 100;
           leftSum  = (unsigned long long)String2[i+1];
           rightSum = (unsigned long long)String2[i+1];
         }
       }

     }

     printString2(String);
  
    t++;
  }


  return 0;

}

