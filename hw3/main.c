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

       int Accumulation[52] = {0};

       for(int j=0; String[j] !='\0';j++){
         printf("%d\n", (int)String[j]);
       }


      t++;
    }


  return 0;

}


getAccumulation(char string[], int Accumulation[])
{
  
  for(int j=0; Pattern[j] !='\0';j++){
    switch (Pattern[j]){
      case 'a':
        Accumulate[0]++;
      case 'b':
        Accumulate[1]++;
      case 'c':
        Accumulate[2]++;
      case 'd':
        Accumulate[3]++;
      case 'e':
        Accumulate[4]++;
      case 'f':
        Accumulate[5]++;
      case 'g':
        Accumulate[6]++;
      case 'h':
        Accumulate[7]++;
      case 'i':
        Accumulate[8]++;
      case 'j':
        Accumulate[9]++;
      case 'k':
        Accumulate[10]++;
      case 'l':
        Accumulate[11]++;
      case 'm':
        Accumulate[12]++;
      case 'n':
        Accumulate[13]++;
      case 'o':
        Accumulate[14]++;
      case 'p':
        Accumulate[15]++;
      case 'q':
        Accumulate[16]++;
      case 'r':
        Accumulate[17]++;
      case 's':
        Accumulate[18]++;
      case 't':
        Accumulate[19]++;
      case 'u':     
        Accumulate[20]++;
      case 'v':     
        Accumulate[21]++;
      case 'w':     
        Accumulate[22]++;
      case 'x':     
        Accumulate[23]++;
      case 'y':     
        Accumulate[24]++;
      case 'z':     
        Accumulate[25]++;
      case 'A':     
        Accumulate[26]++;
      case 'B':     
        Accumulate[27]++;
      case 'C':     
        Accumulate[28]++;
      case 'D':     
        Accumulate[29]++;
      case 'E':
        Accumulate[30]++;
      case 'F': 
        Accumulate[31]++;
      case 'G': 
        Accumulate[32]++;
      case 'H': 
        Accumulate[33]++;
      case 'I': 
        Accumulate[34]++;
      case 'J': 
        Accumulate[35]++;
      case 'K': 
        Accumulate[36]++;
      case 'L': 
        Accumulate[37]++;
      case 'M': 
        Accumulate[38]++;
      case 'N': 
        Accumulate[39]++;
      case 'O':
        Accumulate[40]++;
      case 'P': 
        Accumulate[41]++;
      case 'Q': 
        Accumulate[42]++;
      case 'R': 
        Accumulate[43]++;
      case 'S': 
        Accumulate[44]++;
      case 'T': 
        Accumulate[45]++;
      case 'U': 
        Accumulate[46]++;
      case 'V': 
        Accumulate[47]++;
      case 'W': 
        Accumulate[48]++;
      case 'X':
        Accumulate[49]++;
      case 'Y':
        Accumulate[50]++;
      case 'Z':
        Accumulate[51]++;
    }
  }
  

}
