#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define VERBOSE1
//#define VERBOSE2

void checkPtr(void *ptr, int line)
{    
  if (!ptr){
    printf("NULL at %d!!\n", line);
    exit(0);
  }  
}


int main(){


  /* the length of adjecent list */
  int lengthAdjList;

  
  scanf("%d", &lengthAdjList);

  int **head       = (int**)malloc((size_t)(lengthAdjList)*sizeof(int*));
  int  *numVertex  = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));
  int  *lastIdx    = (int* )malloc((size_t)(lengthAdjList)*sizeof(int ));

  /*============== STEP-1: input ============== */
  for (int i=0;i<lengthAdjList;i++){

    scanf("%d", &numVertex[i]);
 
    head[i] = (int*)malloc((size_t)(&numVertex[i])*sizeof(int));


    for (int j=0;j<numVertex[i];j++){
      scanf("%d", &head[i][j]);
//      head[i][j]--;
    }

    lastIdx[i] = 0;
  }

  /*============== STEP-2:  ============== */

int  brown_p, brown_j, brown_p_advance_probing, brown_p_jump_probing, brown_j_advance_probing, brown_j_jump_probing;
int  green_p, green_j, green_p_advance_probing, green_p_jump_probing, green_j_advance_probing, green_j_jump_probing;
  
bool advance_brown, advance_green;
bool jump_brown,    jump_green;

 for(int i=0;i<lengthAdjList;i++){


   if ( head[head[i][0]][0] == i ){

     brown_p = i;
     green_p = head[i][0];

     brown_j = 0;
     green_j = 0;


     /* ============probe brown for advancing ============*/
     

     if (brown_j+1 < numVertex[brown_p]){
       brown_p_advance_probing = brown_p;
       brown_j_advance_probing = brown_j+1;
       advance_brown = true;
     }
     else{
       advance_brown = false;
     }

#    ifdef VERBOSE2
     printf("brown_p_advance_probing=%d, brown_j_advance_probing=%d\n", brown_p_advance_probing, brown_j_advance_probing);
     printf("advance_brown=%d\n", advance_brown);
#    endif

     /* ============probe green for advancing ============*/
     if (green_j+1 < numVertex[green_p]){
       green_p_advance_probing = green_p;
       green_j_advance_probing = green_j+1;
       advance_green = true;
     }
     else{
       advance_green = false;
     }

#    ifdef VERBOSE2
     printf("green_p_advance_probing=%d, green_j_advance_probing=%d\n", green_p_advance_probing, green_j_advance_probing);
     printf("advance_green=%d\n", advance_green);
#    endif

     /* ============ probe green for jumping ============*/
     if (advance_brown){

       green_p_jump_probing    = head[brown_p_advance_probing][brown_j_advance_probing];
       green_j_jump_probing    = lastIdx[green_p_jump_probing];

       if ( head[green_p_jump_probing][green_j_jump_probing] == brown_p_advance_probing )  jump_green = true;
       else                                                                                jump_green = false;

       if (jump_green) advance_brown = true;
       else            advance_brown = false;

#      ifdef VERBOSE2
       printf("green_p_jump_probing=%d, green_j_jump_probing=%d\n", green_p_jump_probing, green_j_jump_probing);
       printf("jump_green=%d, advance_brown=%d\n", jump_green, advance_brown);
#      endif

     }

     /* ============probe brown for jumping ============*/
     if (advance_green){

       brown_p_jump_probing    = head[green_p_advance_probing][green_j_advance_probing]; 
       brown_j_jump_probing    = lastIdx[brown_p_jump_probing];

       if ( head[brown_p_jump_probing][brown_j_jump_probing] == green_p_advance_probing )  jump_brown = true;
       else                                                                                jump_brown = false;

       if (jump_brown) advance_green = true;
       else            advance_green = false;

#      ifdef VERBOSE2
       printf("brown_p_jump_probing=%d, brown_j_jump_probing=%d\n", brown_p_jump_probing, brown_j_jump_probing);
       printf("jump_brown=%d, advance_green=%d\n", jump_brown, advance_green);
#      endif

     }




     /* jump green and advance brown */
     if ( jump_green == advance_brown){

#      ifdef VERBOSE1
       printf("advance brown (%d,%d)->(%d,%d)\n", brown_p, brown_j, brown_p_advance_probing, brown_j_advance_probing);
       printf("jump green    (%d,%d)->(%d,%d)\n", green_p, green_j, green_p_jump_probing,    green_j_jump_probing);
#      endif

       brown_p = brown_p_advance_probing;
       brown_j = brown_j_advance_probing;

       green_p = green_p_jump_probing;
       green_j = green_j_jump_probing;

     }

     /* jump brown and advance green */
     else if ( jump_brown == advance_green){

#      ifdef VERBOSE1
       printf("jump brown    (%d,%d)->(%d,%d)\n" , brown_p, brown_j, brown_p_jump_probing,    brown_j_jump_probing);
       printf("advance green (%d,%d)->(%d,%d)\n" , green_p, green_j, green_p_advance_probing, green_j_advance_probing);
#      endif

       brown_p = brown_p_jump_probing;
       brown_j = brown_j_jump_probing;

       green_p = green_p_advance_probing;
       green_j = green_j_advance_probing;

     }
     else{
#      ifdef VERBOSE1
       printf("We cannot advance/jump brown/green!\n");
#      endif
       exit(0);
     }
   exit(0);
   }
 }

  return 0;
}

