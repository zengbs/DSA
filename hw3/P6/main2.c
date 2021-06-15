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
 

    head[i] = (int*)malloc((size_t)(numVertex[i])*sizeof(int));


    for (int j=0;j<numVertex[i];j++){
      scanf("%d", &head[i][j]);
      head[i][j]--;
    }

    lastIdx[i] = 0;
  }
  /*============== STEP-2:  ============== */

  int  brown_p, brown_j, brown_p_advance_probing, brown_p_jump_probing, brown_j_advance_probing, brown_j_jump_probing, brown_p_down_probing;
  int  green_p, green_j, green_p_advance_probing, green_p_jump_probing, green_j_advance_probing, green_j_jump_probing, green_p_down_probing;
  
  bool advance_brown = false;
  bool advance_green = false;
  bool jump_brown = false;
  bool jump_green = false;
  bool down_brown, down_green;
 
  bool horizontalExtend_brown = true;
  bool horizontalExtend_green = true;
  bool verticalExtend         = true;

  brown_j = 0;
  green_j = 0;

  brown_p_down_probing = 0;
  green_p_down_probing = 0;


  brown_p = 0;
  green_p = head[brown_p][brown_j];

  int c = 0;
  
  while(c < lengthAdjList ){

    while( horizontalExtend_green || horizontalExtend_brown ){

#     ifdef VERBOSE2
      printf("======================= Start to horizontally sweep with brown (%d,%d) and green (%d,%d): ========================\n\n",
               brown_p, brown_j, green_p, green_j);
 
      for (int i=0;i<lengthAdjList;i++){
        printf("lastIdx[%d]=%d\n", i, lastIdx[i]);
      }

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
      if (advance_brown){
        printf("new brown (%d,%d) if advance\n\n", brown_p_advance_probing, brown_j_advance_probing);
      }
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
      if (advance_green){
        printf("new green (%d,%d) if advance\n\n", green_p_advance_probing, green_j_advance_probing);
      }
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
        printf("############# CASE-1: advance brown and jump green ###############\n");
        printf("advance brown (%d,%d)->(%d,%d)\n", brown_p, brown_j, brown_p_advance_probing, brown_j_advance_probing);
        printf("jump green    (%d,%d)->(%d,%d)\n", green_p, green_j, green_p_jump_probing,    green_j_jump_probing);

        printf("\nlastIdx[%d] (%d)->(%d)\n", brown_p, lastIdx[brown_p], lastIdx[brown_p]+1);
        printf("\nlastIdx[%d] (%d)->(%d)\n", green_p, lastIdx[green_p], lastIdx[green_p]+1);
#       endif


        lastIdx[brown_p]++;
        lastIdx[green_p]++;

        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);

        brown_p = brown_p_advance_probing;
        brown_j = brown_j_advance_probing;

        green_p = green_p_jump_probing;
        green_j = green_j_jump_probing;


        if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
        if (lastIdx[green_p] == numVertex[green_p]-1)  c++;

        horizontalExtend_brown = true;
        horizontalExtend_green = false;
        verticalExtend         = false;        
      }

      /* jump brown and advance green */
      else if ( jump_brown && advance_green){

#       ifdef VERBOSE1
        printf("############# CASE-2: advance green and jump brown ###############\n");
        printf("jump brown    (%d,%d)->(%d,%d)\n" , brown_p, brown_j, brown_p_jump_probing,    brown_j_jump_probing);
        printf("advance green (%d,%d)->(%d,%d)\n" , green_p, green_j, green_p_advance_probing, green_j_advance_probing);

        printf("\nlastIdx[%d] (%d)->(%d)\n", brown_p, lastIdx[brown_p], lastIdx[brown_p]+1);
        printf("\nlastIdx[%d] (%d)->(%d)\n", green_p, lastIdx[green_p], lastIdx[green_p]+1);
#       endif


        lastIdx[brown_p]++;
        lastIdx[green_p]++;

        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);

        brown_p = brown_p_jump_probing;
        brown_j = brown_j_jump_probing;

        green_p = green_p_advance_probing;
        green_j = green_j_advance_probing;


        if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
        if (lastIdx[green_p] == numVertex[green_p]-1)  c++;

        horizontalExtend_brown = false;
        horizontalExtend_green = true;
        verticalExtend         = false;        
      }
      else if ((!jump_brown && advance_green) && !(!jump_green && advance_brown)){
        printf("############# CASE-3:  ###############\n");
        horizontalExtend_brown = false;
        horizontalExtend_green = false;
        verticalExtend         = true;

        brown_p++;
      }
      else if ((!jump_green && advance_brown) && !(!jump_brown && advance_green)){
        printf("############# CASE-4: ###############\n");
        horizontalExtend_brown = false;
        horizontalExtend_green = false;
        verticalExtend         = true;

        brown_p++;
      }

      else if ((!jump_green && advance_brown) && (!jump_brown && advance_green)){
        printf("############# CASE-5: both brown and green cannot jump ###############\n");
        horizontalExtend_brown = false;
        horizontalExtend_green = false;
        verticalExtend         = true;

        //brown_p++;
      }

      /* Both brown and green are at the end  */
      else{
        printf("############# CASE-6: ###############\n");
        horizontalExtend_brown = false;
        horizontalExtend_green = false;
        verticalExtend         = true;

       // brown_p++;
      }

 
    } // while

    printf("======================= Stop horizontally sweep with brown (%d,%d) and green (%d,%d): ========================\n\n", brown_p, brown_j, green_p, green_j);

    for (int i=0;i<lengthAdjList;i++){
      printf("lastIdx[%d]=%d\n", i, lastIdx[i]);
    }

    

    if (  horizontalExtend_brown && !horizontalExtend_green){
        printf("CASE-1: advance brown and jump green ###############\n");
        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
    }

    if ( !horizontalExtend_brown &&  horizontalExtend_green){
        printf("CASE-2: advance green and jump brown ###############\n");
        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
    }

    if (!horizontalExtend_brown && !horizontalExtend_green){
      printf("CASE-5: both brown and green cannot jump ###############\n");
      printf("CASE-6: ###############\n");

      printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
      lastIdx[brown_p]++;
      lastIdx[green_p]++;

      if (lastIdx[brown_p] == numVertex[brown_p]-1)  c++;
      if (lastIdx[green_p] == numVertex[green_p]-1)  c++;
 
    }

 } // while

  return 0;
}

