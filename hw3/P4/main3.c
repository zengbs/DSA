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
     



     char *head = NULL;
     char *head = &String[0];
     char *tail = head;

     int counter = 0;

     int garbleLength = 0;

     int histogramWindow[ALPHEBET_SIZE] = {0};
     

     bool resetCounter = true;

     int winSize = 0;
     int minWin = 0;

     /* ============== main loop started ===================== */

 
     // the number of matched char in the window
     int totalMatchCharInWindow = 0; 

     // the number of distinct matched char in the window
     int distinctMatchCharInWindow = 0; 

     /* Advance the head pointer */
     while( *head != '\0' ){

       histogramWindow[(*head)-'A']++;
       winSize++;

       
       if ( histogramPattern[(*head)-'A']  > 0 )
            totalMatchCharInWindow++;


       if ( histogramPattern[(*head)-'A']  > 0 && histogramWindow[(*head)-'A'] <= histogramPattern[(*head)-'A'] )
            distinctMatchCharInWindow++;


       if ( distinctMatchCharInWindow == lengthPattern ){
 
         while(tail != head+1){

             if ( totalMatchCharInWindow == lengthPattern ) *tail = '=';

             tail++;
         }
       }

       head++;
     }



     /* =========== print result =============== */
     printString(String);
  
    t++;
  }


  return 0;

}

