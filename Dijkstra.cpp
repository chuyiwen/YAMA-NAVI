
/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "Navigator.h"



//////////////////////////
//
// Navigator methods


//
//
//

//--------------------------------------------------------------------------//


#define MAX_NODE 8


int A[MAX_NODE][MAX_NODE];
int S[MAX_NODE];
int L[MAX_NODE];
int Path[MAX_NODE];

void dijkstra(int start);


int main(void){


  int start,end,weight;
  int size,min;  
  int nearest;
  int nodeID;


  //-- Initialize 
  for(int i = 0; i < MAX_NODE; i++){
    S[i] = 0;
    L[i] = 999;
    
    for(int j = 0; j < MAX_NODE; j++){
      A[i][j] = 999;
    }
  }


  //-- Input
  scanf("%d%d%d",&start,&end,&weight);

  while(weight!=999){

    A[start][end] = weight;      
    A[end][start] = weight;  
    scanf("%d%d%d",&start,&end,&weight);

  }


  //-- 
  printf("\n");

  for(int i = 0; i < MAX_NODE; i++){
    for(int j = 0; j < MAX_NODE; j++){
      
      printf("%4d",A[i][j]);
      
    } 
    printf("\n");
  }
  
    
  //-- Input start node
  printf("start?\n");
  scanf("%d",&start);


  //--
  S[start] = 1;
  size     = 1;

  for(int nodeID = 0; nodeID < MAX_NODE; nodeID++){

    if(A[start][nodeID]>=0){
      L[nodeID]    = A[start][nodeID];
      Path[nodeID] = start;
    }
  }


  L[start]    = 0;
  Path[start] = 0;

  while(size < MAX_NODE){
    min = 999;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(S[connect_nodeID]==0 && min>=L[connect_nodeID]){
	
	min     = L[connect_nodeID];
	nearest = connect_nodeID;

      }
    }

    S[nearest] = 1;
    size++;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(A[nearest][connect_nodeID]!=999 && S[connect_nodeID]!=1){
	
	if( L[connect_nodeID]>(L[nearest]+A[nearest][connect_nodeID]) ){

	  L[connect_nodeID]    = L[nearest]+A[nearest][connect_nodeID];
	  Path[connect_nodeID] = nearest;

	}
      }

    }

  }







  //-- 
  for(int i = 0; i < MAX_NODE; i++){
    printf("%d-distance:%d\n",i,L[i]);
  }
  
  //--
  for(int i = 0; i < MAX_NODE; i++){

    printf("%d:",i);

    nodeID = i;
    
    while(Path[nodeID]!=0){

      printf("%d\t",Path[nodeID]);
      
      nodeID = Path[nodeID];

    }

    printf("\n");
  
  }

}



void dijkstra(){



  int start,end,weight;
  int size,min;  
  int nearest;
  int nodeID;


  //-- Initialize 
  for(int i = 0; i < MAX_NODE; i++){
    S[i] = 0;
    L[i] = 999;
    
    for(int j = 0; j < MAX_NODE; j++){
      A[i][j] = 999;
    }
  }


  //-- Input
  scanf("%d%d%d",&start,&end,&weight);

  while(weight!=999){

    A[start][end] = weight;      
    A[end][start] = weight;  
    scanf("%d%d%d",&start,&end,&weight);

  }


  //-- 
  printf("\n");

  for(int i = 0; i < MAX_NODE; i++){
    for(int j = 0; j < MAX_NODE; j++){
      
      printf("%4d",A[i][j]);
      
    } 
    printf("\n");
  }
  
    
  //-- Input start node
  printf("start?\n");
  scanf("%d",&start);


  //--
  S[start] = 1;
  size     = 1;

  for(int nodeID = 0; nodeID < MAX_NODE; nodeID++){

    if(A[start][nodeID]>=0){
      L[nodeID]    = A[start][nodeID];
      Path[nodeID] = start;
    }
  }


  L[start]    = 0;
  Path[start] = 0;

  while(size < MAX_NODE){
    min = 999;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(S[connect_nodeID]==0 && min>=L[connect_nodeID]){
	
	min     = L[connect_nodeID];
	nearest = connect_nodeID;

      }
    }

    S[nearest] = 1;
    size++;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(A[nearest][connect_nodeID]!=999 && S[connect_nodeID]!=1){
	
	if( L[connect_nodeID]>(L[nearest]+A[nearest][connect_nodeID]) ){

	  L[connect_nodeID]    = L[nearest]+A[nearest][connect_nodeID];
	  Path[connect_nodeID] = nearest;

	}
      }

    }

  }



}
