#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<float.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdint.h> // The maximum size of size_t is provided via SIZE_MAX

#define DEBUG

#define MAX_STRING_SIZE 100000
#define ALPHEBET_SIZE       58


void checkPtr(void *ptr, int line)
{    
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }  
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


     /* ======================================================== */
     /* =========== get the histogram of pattern =============== */
     /* ======================================================== */
     int lengthPattern = 0;
     int histogramPattern[ALPHEBET_SIZE] = {0};

     for(int p=0; Pattern[p] != '\0';p++){
       histogramPattern[Pattern[p]-'A']++;
       lengthPattern++;
     }
 
     //if (lengthPattern == 0) ...;

     /* ========================================= */
     /* =========== remove garble =============== */
     /* ========================================= */

     char *Ptr = NULL;
     char *tail = NULL;
     char *head = NULL;

     int counter = 0;

     int histogramString[ALPHEBET_SIZE]  = {0};

     Ptr = &String[0];

     /* ============== main loop started ===================== */
     for(int s=0; String[s] != '\0';s++){

       if (Ptr == NULL || Ptr == head){
         counter = 0;
         Ptr++;
       }

       histogramString[String[s]-'A']++;


       /* ============== advance counter when matching charactor  ================== */
       if ( histogramString[String[s]-'A'] <= histogramPattern[String[s]-'A'] ){

         if (counter == 0) tail = Ptr;
 
         counter++;
       }

       /* =========== Go back to tail =============== */
       if( counter == lengthPattern ){

         head = Ptr;
         Ptr  = tail;

         while( Ptr != head ){
           *Ptr = '=';
           Ptr++;
           *Ptr = '=';
         }

         for (int i=0;i<ALPHEBET_SIZE;i++) histogramString[i] = 0;

         Ptr = head-1;
       }

       Ptr++;
     }


     /* =========== print result =============== */
     for(int s=0; String[s] != '\0';s++){
       if (String[s] != '=') printf("%c", String[s]);
     }
     printf("\n");
  
    t++;
  }


  return 0;

}



//void getAccumulation(char string[], int Accumulation[])
//{
//  for(int j=0; string[j] !='\0';j++){
//    Accumulation[string[j]-'A']++;
//  }
//}
