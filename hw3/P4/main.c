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
         //int winSize = j-finger+1;
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


     /* =========== print result =============== */
     printString(String);
  
    t++;
  }


  return 0;

}

