
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


#define MAX_NODE 8 // = g->nom_node


int Adjacency[MAX_NODE][MAX_NODE];//

int S[MAX_NODE];
int Length[MAX_NODE];
int Path[MAX_NODE];
int Shortest_Path[MAX_NODE];
int temp_Shortest_Path[MAX_NODE];
int shortest_path_length;
int shortest_distance;

void dijkstra(int start, int end);


int main(void){


  int start,end,weight;
 

  //-- Initialize Matricies
  for(int i = 0; i < MAX_NODE; i++){
    S[i]      = 0;
    Length[i] = 999999;
    
    for(int j = 0; j < MAX_NODE; j++){
      Adjacency[i][j] = 999999;
    }
  }


  //-- Input Weight 
  scanf("%d%d%d",&start,&end,&weight);

  while(weight!=999999){

    Adjacency[start][end] = weight;      
    Adjacency[end][start] = weight;  
    scanf("%d%d%d",&start,&end,&weight);

  }


  //-- Printout Adjacency
  printf("\n");

  for(int i = 0; i < MAX_NODE; i++){
    for(int j = 0; j < MAX_NODE; j++){
      printf("%7d",Adjacency[i][j]);
    } 
    printf("\n");
  }
  printf("\n");


    
  //-- Input Start and END Node
  int start_node; //
  int end_node;   // = 

  //printf("start?\n");
  scanf("%d",&start_node); 
  printf("start:%d\n",start_node);

  //printf("end?\n");
  scanf("%d",&end_node);  
  printf("end  :%d\n",end_node);

  printf("\n");


  //-- Calculate Shortest Path
  dijkstra(start_node, end_node);







}



void dijkstra(int start, int end){

  
  //-- Begin of Main Algorithm of Dijkstra  

  int size;
  int min;  
  int nearest;
  
  S[start] = 1;
  size     = 1;

  for(int nodeID = 0; nodeID < MAX_NODE; nodeID++){

    if(Adjacency[start][nodeID] >= 0){
      Length[nodeID] = Adjacency[start][nodeID];
      Path[nodeID]   = start;
    }
  }

  Length[start] = 0;
  Path[start]   = -1;//-- "-1" represents start node. 

  while(size < MAX_NODE){
    min = 999999;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(S[connect_nodeID]==0 && min >= Length[connect_nodeID]){
	min     = Length[connect_nodeID];
	nearest = connect_nodeID;
      }
    }

    S[nearest] = 1;
    size++;

    for(int connect_nodeID = 0; connect_nodeID < MAX_NODE; connect_nodeID++){

      if(Adjacency[nearest][connect_nodeID]!=999999 && S[connect_nodeID]!=1){
	
	if( Length[connect_nodeID]>(Length[nearest] + Adjacency[nearest][connect_nodeID]) ){

	  Length[connect_nodeID] = Length[nearest] + Adjacency[nearest][connect_nodeID];
	  Path[connect_nodeID]   = nearest;
	}
      }
    }

  }
  //-- End of Main Algorithm of Dijkstra



  //-- Set "temp_Shortest_Path" from End to Start based on Path

  int next_node;

  shortest_path_length = 0;
  next_node            = end;
    
  while(Path[next_node]!=-1){
    //-- "-1" represents start node. 

    temp_Shortest_Path[shortest_path_length] = Path[next_node]; 
    shortest_path_length++;
    
    next_node = Path[next_node];
  }


  //-- Set "Shortest_Path" from Start to End by reversing "temp_Shortest_Path"
  for(int i = 0; i < shortest_path_length; i++){
    Shortest_Path[i] = temp_Shortest_Path[shortest_path_length - (i+1)];
  }
  Shortest_Path[shortest_path_length] = end;
  shortest_path_length++;


  //-- Set "shortest_distance" based on Length[end]
  shortest_distance = Length[end];



  //-- Printout 
  printf("shortest_path:");

  for(int i = 0; i < shortest_path_length; i++){  
    printf("%d ",Shortest_Path[i]);
  }  
  
  printf("\n");  
  printf("path length   :%d\n",shortest_path_length);
  printf("%2d-%2d distance:%d\n",start, end, Length[end]);


}
