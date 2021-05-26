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

void getAccumulation(char string[], int Accumulation[]);

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

     int Accumulation[ALPHEBET_SIZE] = {0};

     getAccumulation(Pattern, Accumulation);

     int nonZero = 0;

     for(int i=0;i<ALPHEBET_SIZE;i++){
       if (Accumulation[i] > 0) nonZero++;
     }

     bool keepSearching = false;

     for(int s=0; String[s] != '\0';s++){

       if ( Accumulation[String[s]-'A'] > 0 || keepSearching ){

         Accumulation[String[s]-'A']--;

         if (Accumulation[String[s]-'A'] == 0) nonZero--;

         String[s] = '=';

         keepSearching = true;
       }

       if (nonZero == 0) keepSearching = false;

     }

     for(int s=0; String[s] != '\0';s++){
       if (String[s] != '=') printf("%c", String[s]);
     }
     printf("\n");
  
    t++;
  }


  return 0;

}



void getAccumulation(char string[], int Accumulation[])
{
  for(int j=0; string[j] !='\0';j++){
    Accumulation[string[j]-'A']++;
  }
}
