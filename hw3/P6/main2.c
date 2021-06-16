#include<stdio.h>
#include <stddef.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdint.h>
#include<limits.h>

//#define VERBOSE1
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
 

    head[i] = (int*)malloc((size_t)(numVertex[i])*sizeof(int));


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
 
  bool horizontalExtend_brown = true;
  bool horizontalExtend_green = true;

  brown_j = 0;
  green_j = 0;


  brown_p = 0;
  green_p = head[brown_p][brown_j];

  int c = 0;
 
  bool Case1;  
  bool Case2;
  bool Case3;
  bool Case4;
  bool Case5;
  bool Case6;
  bool Case7;

  while(c < lengthAdjList ){
#  ifdef VERBOSE2
   printf("======================= Start vertically sweep with brown (%d,%d) and green (%d,%d): ========================\n\n",
           brown_p, brown_j, green_p, green_j);
#  endif

    while( horizontalExtend_green || horizontalExtend_brown ){

      Case1 = false;
      Case2 = false;
      Case3 = false;
      Case4 = false;
      Case5 = false;
      Case6 = false;
      Case7 = false;

#     ifdef VERBOSE2
      printf("======================= Start horizontally sweep with brown (%d,%d) and green (%d,%d): ========================\n\n",
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

        green_p = head[brown_p][brown_j];
        green_j = lastIdx[head[brown_p][brown_j]];

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
        Case1 = true;
      }

      /* jump brown and advance green */
      else if ( jump_brown && advance_green){

        brown_p = head        [green_p][green_j];
        brown_j = lastIdx[head[green_p][green_j]];

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
        Case2 = true;
      }
      else if ((!jump_brown && advance_green) && !(!jump_green && advance_brown)){
#       ifdef VERBOSE2
        printf("############# CASE-3:  ###############\n");
#       endif
        horizontalExtend_brown = false;
        horizontalExtend_green = false;

        Case3 = true;
      }
      else if ((!jump_green && advance_brown) && !(!jump_brown && advance_green)){
#       ifdef VERBOSE2
        printf("############# CASE-4: ###############\n");
#       endif
        horizontalExtend_brown = false;
        horizontalExtend_green = false;

        Case4 = true;
      }

      else if ((!jump_green && advance_brown) && (!jump_brown && advance_green)){

        if (head[head[brown_p][brown_j]][brown_j] == brown_p){
#         ifdef VERBOSE2
          printf("############# CASE-5: both brown and green cannot jump but brown and green are legal ###############\n");
#         endif
          horizontalExtend_brown = false;
          horizontalExtend_green = false;

          Case5 = true;
        }
        else{
#         ifdef VERBOSE2
          printf("############# CASE-6: both brown and green cannot jump but brown and green are illegal ###############\n");
#         endif
          horizontalExtend_brown = false;
          horizontalExtend_green = false;

          Case6 = true;

        }
      }

      /* Both brown and green are at the end  */
      else{
#       ifdef VERBOSE2
        printf("############# CASE-7: Both brown and green are at the end ###############\n");
#       endif
        horizontalExtend_brown = false;
        horizontalExtend_green = false;

        Case7 = true;
      }

 
    } // while

#   ifdef VERBOSE2
    printf("======================= Stop horizontally sweep with brown (%d,%d) and green (%d,%d): ========================\n\n", brown_p, brown_j, green_p, green_j);
#   endif


    

    if ( Case1 ){
#       ifdef VERBOSE2
        printf("CASE-1: advance brown and jump green ###############\n");
#     endif
        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
    }

    if ( Case2 ){
#       ifdef VERBOSE2
        printf("CASE-2: advance green and jump brown ###############\n");
#     endif
        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
    }

    if (Case3) {
     printf("Case3!\n");
     exit(0);
    }

    if (Case4) {
     printf("Case4!\n");
     exit(0);
    }

    if ( Case5 ){
#       ifdef VERBOSE2
      printf("CASE-5: both brown and green cannot jump but brown and green are legal ###############\n");
#     endif
      printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
      horizontalExtend_green = true;
      horizontalExtend_brown = true;

      lastIdx[brown_p]++;
      lastIdx[green_p]++;

      if (lastIdx[brown_p] == numVertex[brown_p])  c++;
      if (lastIdx[green_p] == numVertex[green_p])  c++;

      brown_p++;
      green_p++;
    }

    if ( Case6 ){
#     ifdef VERBOSE2
      printf("CASE-6: both brown and green cannot jump but brown and green are illegal ###############\n");
#     endif
      horizontalExtend_green = true;
      horizontalExtend_brown = true;
 
      brown_p++;

    }

    if ( Case7 ){
#     ifdef VERBOSE2
      printf("CASE-7: Both brown and green are at the end ###############\n");
#     endif
      printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
 
      lastIdx[brown_p]++;
      lastIdx[green_p]++;

      if (lastIdx[brown_p] == numVertex[brown_p])  c++;
      if (lastIdx[green_p] == numVertex[green_p])  c++;

      if (brown_p+1<lengthAdjList){

        brown_p++;

        if ( head[head[brown_p][brown_j]][lastIdx[head[brown_p][brown_j]]] == brown_p ){
          green_p = head[brown_p][brown_j];
          green_j = lastIdx[green_p];
        }

        printf("%d %d\n", head[brown_p][brown_j]+1, head[green_p][green_j]+1);
      }


    }

#   ifdef VERBOSE2
    for (int i=0;i<lengthAdjList;i++){
      printf("lastIdx[%d]=%d\n", i, lastIdx[i]);
    }
#   endif
   
#   ifdef VERBOSE2
    printf("c=%d\n", c);
    printf("======================= Stop vertically sweep with brown (%d,%d) and green (%d,%d): ========================\n\n", brown_p, brown_j, green_p, green_j);
#   endif
 } // while

  return 0;
}

