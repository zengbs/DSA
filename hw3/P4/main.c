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

     /* ======================================================== */
     /* =========== get the histogram of pattern =============== */
     /* ======================================================== */
     int lengthPattern = 0;
     int lengthString = 0;
     int histogramPattern[ALPHEBET_SIZE] = {0};

     for(int p=0; Pattern[p] != '\0';p++){
       histogramPattern[Pattern[p]-'A']++;
       lengthPattern++;
     }
 
     for(int s=0; String[s] != '\0';s++){
       lengthString++;
     }
     
     /* ============================== */
     if (lengthPattern == 0 || lengthString < lengthPattern  ){
       printString(String);
       return 0;
     }

     /* ============================== */
     int *histogramGarblelength = NULL;

     if ( lengthPattern < lengthString )  histogramGarblelength = (int*)calloc(lengthString, sizeof(int));

     checkPtr(histogramGarblelength, __LINE__);

     /* ========================================= */
     /* =========== remove garble =============== */
     /* ========================================= */

     char *Ptr = NULL;
     char *tail = NULL;
     char *head = &String[0];

     int counter = 0;

     int garbleLength = 0;

     int histogramString[ALPHEBET_SIZE]  = {0};

     Ptr = &String[0];

     bool resetCounter = true;

     /* ============== main loop started ===================== */
     for(int s=0; String[s] != '\0';s++){

#      ifdef VERBOSE
       printf("============================= next char! =====================================\n");
#      endif

       if ( resetCounter ){

#        ifdef VERBOSE
         printf("Reset counter and garbleLength...\n");
#        endif

         counter = 0;
         garbleLength = 0;
       }

#      ifdef VERBOSE
       printf("%c\n", String[s]);
       printf("Add 1 to histogram of string (%c)\n", String[s]);
#      endif

       histogramString[String[s]-'A']++;

       
       /* ============== advance counter when matching charactor  ================== */
       if ( histogramString[String[s]-'A'] <= histogramPattern[String[s]-'A'] ){

         if (counter == 0){
           tail = Ptr;
#          ifdef VERBOSE
           printf("Move tail to (%c)...\n", *tail);
#          endif
         }

         counter++;
#        ifdef VERBOSE
         printf("advance counter to (%d)...\n", counter); 
#        endif
       }


       if (counter == lengthPattern ){

         head = Ptr;
         Ptr  = tail;

         garbleLength = ( (head) - (tail) )/sizeof(char) +1;

#        ifdef VERBOSE
         printf("garble length is %d\n", garbleLength);
#        endif

         Ptr = head;
       }

       /* =========== Go back to tail =============== */
       if( counter == lengthPattern && histogramGarblelength[garbleLength] == 0){

#        ifdef VERBOSE
         printf("From head(%c) going back to tail(%c)...\n", *head, *tail);
#        endif

         head = Ptr;
         Ptr  = tail;

#        ifdef VERBOSE
         printf("Replace (%c) with '='\n", *Ptr);
#        endif

         *Ptr = '=';

         while( Ptr != head ){
           Ptr++;

#          ifdef VERBOSE
           printf("Replace (%c) with '='\n", *Ptr);
#          endif

           *Ptr = '=';
         }

       }

       if( counter == lengthPattern ){

#        ifdef VERBOSE
         printf("Reset histogram of string...\n");
#        endif

         for (int i=0;i<ALPHEBET_SIZE;i++) histogramString[i] = 0;

#        ifdef VERBOSE
         printf("Add 1 to histogram of garble lengh (%d)...\n", garbleLength);
#        endif

         histogramGarblelength[garbleLength]++;

#        ifdef VERBOSE
         printf("Reset counter...\n");
#        endif

         resetCounter = true;

#        ifdef VERBOSE
         printf("Advance Ptr from (%c)", *Ptr);
#        endif

         Ptr++;

#        ifdef VERBOSE
         printf(" to (%c)\n", *Ptr);
#        endif

         continue;
       }

       resetCounter = false;

#      ifdef VERBOSE
       printf("Advance Ptr from (%c)", *Ptr);
#      endif

       Ptr++;

#      ifdef VERBOSE
       printf(" to (%c)\n", *Ptr);
#      endif
     }


     /* =========== print result =============== */
     printString(String);
  
    t++;
  }


  return 0;

}
