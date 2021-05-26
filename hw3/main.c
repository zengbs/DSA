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

   char *String;
   String = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
 
   checkPtr(String, __LINE__);

    int t = 0;

    while(t<T){
    
       scanf("%s", String);
       printf("=================\n");

       for(int j=0; String[j] !='\0';j++){
         printf("%d\n", (int)String[j]);
       }

      t++;
    }


  return 0;

}
