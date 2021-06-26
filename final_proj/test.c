#include <stdio.h>
#include <stdlib.h>


# define arraySIZE 9

typedef struct
{
  int *p[3][3];
} Array_st;

void stringCompare( int *p, int I, int J )
{
  for (int i=0;i<I;i++){
    for (int j=0;j<J;j++){
      p[3*i+j] *= -100;
    }
  }
}

void parse_and_hash( int *array1, Array_st *obj )
{
  for (int i=0;i<3;i++){
    for (int j=0;j<3;j++){
      obj->p[i][j] = &array1[3*i+j];
    }
  }

  stringCompare( obj->p[0][0], 3, 3 );
}

int main(){

  int array1[arraySIZE];

  for (int i=0;i<arraySIZE;i++){
    array1[i] = -2*i;
  }

  Array_st *obj = (Array_st *)calloc(1,sizeof(Array_st));

  parse_and_hash( array1, obj );
  
  for (int i=0;i<arraySIZE;i++){
    printf("%2d ", array1[i]);
  }
    printf("\n");


  return 0;
}
