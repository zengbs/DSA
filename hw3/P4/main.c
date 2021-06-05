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

  char *String  = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  char *Pattern = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
 
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

     int finger = 0;

     int minWin;
 
     for ( int j=0;String[j] != '\0';j++ ){

       histogramString[String[j]-'A']++;

       if (histogramString[String[j]-'A'] <= histogramPattern[String[j]-'A']) distinctMachedChar++;

       if ( distinctMachedChar == lengthPattern ){

         while( histogramString[String[finger]-'A'] > histogramPattern[String[finger]-'A'] || histogramPattern[String[finger]-'A'] == 0 ){
           
           if( histogramString[String[finger]-'A'] > histogramPattern[String[finger]-'A'] ) histogramString[String[finger]-'A']--;

           finger++;
         }

         // get the length of shortest window
         int winSize = j-finger+1;

         if (minWin > winSize) minWin = winSize;
       }
     }

     printf("minWin=%d\n", minWin);

     /* =========== print result =============== */
     printString(String);
  
    t++;
  }


  return 0;

}

