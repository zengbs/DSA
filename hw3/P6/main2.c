#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

#define VERBOSE1
#define VERBOSE2

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
      head[i][j]--;
    }

    lastIdx[i] = 0;
  }

  /*============== STEP-2:  ============== */

  int  brown_p, brown_j, brown_p_advance_probing, brown_p_jump_probing, brown_j_advance_probing, brown_j_jump_probing;
  int  green_p, green_j, green_p_advance_probing, green_p_jump_probing, green_j_advance_probing, green_j_jump_probing;
  
  bool advance_brown = false;
  bool advance_green = false;
  bool jump_brown = false;
  bool jump_green = false;
  bool down_brown, down_green;
  
  bool horizontalExtend = true;
  bool verticalExtend   = true;

  brown_j = 0;
  green_j = 0;

  brown_p = 0;
  green_p = head[brown_p][brown_j];

  int c = 0;
  
  while(c < lengthAdjList ){
#   ifdef VERBOSE2
    printf("======================= Start to vertically sweep: ========================\n");
#   endif

    if ( head[head[brown_p][brown_j]][brown_j] == brown_p ){
      horizontalExtend = true;
      verticalExtend   = false;
      printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
    }
    else{
      horizontalExtend = false;
      verticalExtend   = true;
    }


    if (brown_p + 1 < lengthAdjList){
      down_brown = true;
    }
    else{
      down_brown = false;
    }
     
    if (green_p + 1 < lengthAdjList){
      down_green = true;
    }
    else{
      down_green = false;
    }

#   ifdef VERBOSE2     
    printf("brown:(%d,%d)\n", brown_p, brown_j);
    printf("green:(%d,%d)\n", green_p, green_j);
#   endif

    if ( down_brown && verticalExtend ){
      brown_p++;
    }
 
    if ( down_green && verticalExtend ){
      green_p++; 
    }


    if ( !down_green && !down_brown){
      verticalExtend   = false;
    }

    //lastIdx[brown_p]++;
    //lastIdx[green_p]++;

    //if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
    //if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
 

    while( horizontalExtend ){

#     ifdef VERBOSE2
      printf("======================= Start to horizontally sweep: ========================\n");
#     endif

      if (brown_j+1 < numVertex[brown_p]){
        brown_p_advance_probing = brown_p;
        brown_j_advance_probing = brown_j+1;
        advance_brown = true;
      }
      else{
        advance_brown = false;
      }

#     ifdef VERBOSE2
      printf("advance_brown=%d\n", advance_brown);
      printf("new brown (%d,%d) if advance\n\n", brown_p_advance_probing, brown_j_advance_probing);
#     endif

      /* STEP-B: ============probe green for advancing ============*/
      if (green_j+1 < numVertex[green_p]){
        green_p_advance_probing = green_p;
        green_j_advance_probing = green_j+1;
        advance_green = true;
      }
      else{
        advance_green = false;
      }

#     ifdef VERBOSE2
      printf("advance_green=%d\n", advance_green);
      printf("new green (%d,%d) if advance\n\n", green_p_advance_probing, green_j_advance_probing);
#     endif

      /* ============ probe green for jumping ============*/
      if (advance_brown){

        green_p_jump_probing    = head[brown_p_advance_probing][brown_j_advance_probing];
        green_j_jump_probing    = lastIdx[green_p_jump_probing];


        if ( head[green_p_jump_probing][green_j_jump_probing] == brown_p_advance_probing )  jump_green = true;
        else                                                                                jump_green = false;

        //if (jump_green) advance_brown = true;
        //else            advance_brown = false;

#       ifdef VERBOSE2
        printf("new green (%d,%d) if jump\n", green_p_jump_probing, green_j_jump_probing);
        printf("jump_green=%d, advance_brown=%d\n\n", jump_green, advance_brown);
#       endif

      }

      /* ============probe brown for jumping ============*/
      if (advance_green){

        brown_p_jump_probing    = head[green_p_advance_probing][green_j_advance_probing]; 
        brown_j_jump_probing    = lastIdx[brown_p_jump_probing];

        if ( head[brown_p_jump_probing][brown_j_jump_probing] == green_p_advance_probing )  jump_brown = true;
        else                                                                                jump_brown = false;

        //if (jump_brown) advance_green = true;
        //else            advance_green = false;

#       ifdef VERBOSE2
        printf("new brown (%d,%d) if jump\n", brown_p_jump_probing, brown_j_jump_probing);
        printf("jump_brown=%d, advance_green=%d\n\n", jump_brown, advance_green);
#       endif

      }




      /* jump green and advance brown */
      if ( jump_green && advance_brown){

#       ifdef VERBOSE1
        printf("advance brown (%d,%d)->(%d,%d)\n", brown_p, brown_j, brown_p_advance_probing, brown_j_advance_probing);
        printf("jump green    (%d,%d)->(%d,%d)\n", green_p, green_j, green_p_jump_probing,    green_j_jump_probing);

        printf("\nlastIdx[%d] (%d)->(%d)\n", brown_p, lastIdx[brown_p], lastIdx[brown_p]+1);
        printf("\nlastIdx[%d] (%d)->(%d)\n", green_p, lastIdx[green_p], lastIdx[green_p]+1);
#       endif


        lastIdx[brown_p]++;
        lastIdx[green_p]++;

        brown_p = brown_p_advance_probing;
        brown_j = brown_j_advance_probing;

        green_p = green_p_jump_probing;
        green_j = green_j_jump_probing;

        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);

        if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
        if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
      }

      /* jump brown and advance green */
      else if ( jump_brown && advance_green){

#       ifdef VERBOSE1
        printf("jump brown    (%d,%d)->(%d,%d)\n" , brown_p, brown_j, brown_p_jump_probing,    brown_j_jump_probing);
        printf("advance green (%d,%d)->(%d,%d)\n" , green_p, green_j, green_p_advance_probing, green_j_advance_probing);

        printf("\nlastIdx[%d] (%d)->(%d)\n", brown_p, lastIdx[brown_p], lastIdx[brown_p]+1);
        printf("\nlastIdx[%d] (%d)->(%d)\n", green_p, lastIdx[green_p], lastIdx[green_p]+1);
#       endif


        lastIdx[brown_p]++;
        lastIdx[green_p]++;

        brown_p = brown_p_jump_probing;
        brown_j = brown_j_jump_probing;

        green_p = green_p_advance_probing;
        green_j = green_j_advance_probing;

        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);

        if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
        if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
      }
      else if (!jump_brown && advance_green){
        horizontalExtend = false;
        verticalExtend   = true;

        brown_p++;
        green_p++;
      }
      else if (!jump_green && advance_brown){
        horizontalExtend = false;
        verticalExtend   = true;

        brown_p++;
        green_p++;
      }

      /* Both brown and green are at the end  */
      else{
        horizontalExtend = false;
        verticalExtend   = true;

        brown_p++;
        green_p++;
      }

//      lastIdx[brown_p]++;
//      lastIdx[green_p]++;
//
//      if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
//      if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
 
    } // while

 //   lastIdx[brown_p]++;
 //   lastIdx[green_p]++;

 //   if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
 //   if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
 

 } // while

  return 0;
}

