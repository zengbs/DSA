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

void printString(char String[], int Remove[])
{
  for(int s=0; String[s] != '\0';s++){
    if (Remove[s]==0) printf("%c", String[s]);
  }
  printf("\n");
}


int main()
{
  
  char *String   = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  char *Pattern1 = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));
  char *Pattern2 = (char*)calloc((size_t)(MAX_STRING_SIZE),sizeof(char));

  int T;
  scanf("%d", &T);
  scanf("%s", String);
  scanf("%s", Pattern1);

  int lengthString  = 0;
  int lengthPattern = 0;

  for (int s=0; String[s] != '\0'; s++){
    lengthString++;
  }

  for (int p=0; Pattern1[p] != '\0'; p++){
    Pattern2[p] = Pattern1[p];
    lengthPattern++;
  }

  bool *Match     = (bool*)calloc((size_t)(lengthString),sizeof(bool));
  int  *Garbles   = (int*)calloc((size_t)(lengthString),sizeof(int));
  int  *Remove    = (int*)calloc((size_t)(lengthString),sizeof(int));


  int c = 0;

  for (int s=0; String[s] != '\0'; s++){
    for (int p=0; Pattern1[p] != '\0'; p++){

      if (c==lengthPattern){
        for (int p=0; Pattern1[p] != '\0'; p++)  Pattern1[p] = Pattern2[p];
        c = 0;
      }

      if (String[s] == Pattern1[p]){
        Match[s] = true;
        Pattern1[p] = '=';
        c++;
        break;
      }
      else{
        Match[s] = false;
      }


    } 
  }

  
  int counter = 0;
  int tail = 0;
  int number = 0;

  for (int g=0;g<lengthString;g++){


    if (Match[g]==1&&counter==0){
      tail = g;
    }

    if ( Match[g]==1) counter += Match[g];

    if (counter == lengthPattern){
      number++;
      counter = 0;

      for (int g1=0;g1<g-tail+1;g1++){
        if (number%2==0)  Garbles[tail+g1] = +(g-tail+1);
        else              Garbles[tail+g1] = -(g-tail+1);
      }
    }
  }


  for (int i=0;i<lengthString;i++){

    int tail;
    int head;
#     ifdef VERBOSE
    printf("%c\n", String[i]);
#     endif

    if (Garbles[i] != 0){

      tail = i;
      head = tail;

      if (tail+1<=lengthString-1 && Garbles[tail] == Garbles[tail+1]){
        do{

          head++;
        }while( Garbles[tail] == Garbles[head] );

        head--;
      }
#     ifdef VERBOSE
      printf("tail=%d, head=%d\n", tail, head);
#     endif

      bool reserve = false;

      for (int ii=0;ii<tail;ii++){
        if (abs(Garbles[ii]) == abs(Garbles[tail])){
          reserve |= true;
        }
      }

#     ifdef VERBOSE
      printf("reserve=%d\n", reserve);
#     endif

        for ( int j=tail;j<head+1;j++ ){
          if (reserve) Remove[j] = 0;
          else         Remove[j] = 1;
        }
      i += head-tail;
    }
    else Remove[i] = 0;

  }

#     ifdef VERBOSE
  for (int m=0;m<lengthString;m++){
    printf("%3d", Remove[m]);
  }
  printf("\n");


  for (int m=0;m<lengthString;m++){
    printf("%3d", Garbles[m]);
  }
  printf("\n");


  for (int m=0;m<lengthString;m++){
    printf("%3d", Match[m]);
  }
  printf("\n");


  for (int m=0;m<lengthString;m++){
    printf("%3c", String[m]);
  }
  printf("\n");
#     endif


  printString(String, Remove);

}
