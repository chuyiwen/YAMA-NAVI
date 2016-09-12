/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Navigator.h"


 
//////////////////////////
//
// Navigator methods


//
//
//

//--------------------------------------------------------------------------//

Navigator::Navigator(void)
{ 
}

Navigator::~Navigator(void)
{ 
}

//--------------------------------------------------------------------------//

void 
Navigator::idealPathPlanning(int objID){
  

  //-- Input Start and End Node
  int     outward_start;  //-- Start Node of Outward Shortest Path for Dijkstra
  int     outward_end;    //-- End Node of Outward Shortest Path by Dijkstra   
  int     homeward_start; //-- Start Node of Homeward Shortest Path for Dijkstra
  int     homeward_end;   //-- End Node of Homeward Shortest Path by Dijkstra 

  int     o_arc   = o->move[objID].origin_arc; 
  int     o_side  = o->move[objID].origin_side;   
  int     o_block = o->move[objID].origin_block; 

  int     d_arc   = o->move[objID].destination_arc;  //-- Arc of Destination     
  int     d_side  = o->move[objID].destination_side; //-- Side of Destination  
  int     d_block = o->move[objID].destination_block;//-- Block of Destination  
  
  int     last_block;

  double  distance_from_top_node_to_origin       = 0;
  double  distance_from_last_node_to_destination = 0;
 
  double  time_from_top_node_to_origin           = 0;
  double  time_from_last_node_to_destination     = 0;

  double  time_from_last_node_to_origin          = 0;
  double  time_from_top_node_to_destination      = 0;

  double  vel;
  double  len;


  //-- Calculate Outward Shortest Path from Start to End
  outward_start = o->move[objID].end;
  outward_end   = g->arc[d_arc].block_start_node[d_side]; 


  //-- Shortest Path Distance from Start Node to End Node
  dijkstra(outward_start, outward_end, IDEAL_DISTANCE);


  //-- Calculate Ideal Distance from Origin to Top Block
  last_block  = g->arc[o_arc].num_block - 1;
     
  if(o_block == last_block){

    distance_from_top_node_to_origin  
      = g->arc[o_arc].distance - g->arc[o_arc].block[o_side][last_block].block_length;
  }
  else{

    distance_from_top_node_to_origin  
      = (double)o_block * g->arc[o_arc].block[o_side][o_block].block_length;
  }

  
  //-- Calculate Ideal Distance from Destionation to Last Block 
  last_block  = g->arc[d_arc].num_block - 1;

  if(d_block == last_block){

    distance_from_last_node_to_destination 
      = g->arc[d_arc].block[d_side][last_block].block_length;
  }
  else{

    distance_from_last_node_to_destination 
      = g->arc[d_arc].block[d_side][last_block].block_length 
      + (last_block - d_block) * g->arc[d_arc].block[d_side][d_block].block_length;
  }



  //-- Calculate Ideal Distance from Origin to Destination
  o->move[objID].ideal_required_distance[OUTWARD] = 
    (shortest_distance +  distance_from_top_node_to_origin + distance_from_last_node_to_destination); 

  //printf("shortest_distance                     :%f\n",shortest_distance);  
  //printf("distance_from_top_node_to_origin      :%f\n",distance_from_top_node_to_origin  );
  //printf("distance_from_last_node_to_destination:%f\n",distance_from_last_node_to_destination);  


  //--  Shortest Path Time from Start to End
  dijkstra(outward_start, outward_end, IDEAL_TIME);


  //-- Calculate Ideal Time from Origin to Top Block
  time_from_top_node_to_origin = 0;  

  for(int blockID = 0; blockID < o_block; blockID++){
    
    vel = g->arc[o_arc].block[o_side][blockID].ideal_velocity;
    len = g->arc[o_arc].block[o_side][blockID].block_length;

    time_from_top_node_to_origin += len/(vel * TIME_UNIT);
  }



 //-- Calculate Ideal Time from Destionation to Last Block 
  time_from_last_node_to_destination = 0;
 
  for(int blockID = d_block; blockID < g->arc[d_arc].num_block; blockID++){

    vel = g->arc[d_arc].block[d_side][blockID].ideal_velocity;
    len = g->arc[d_arc].block[d_side][blockID].block_length;

    time_from_last_node_to_destination += len/(vel * TIME_UNIT);
  }

  o->move[objID].ideal_required_time[OUTWARD] = 
    (shortest_distance +  time_from_top_node_to_origin + time_from_last_node_to_destination); 


  //printf("shortest_time                     :%f\n",shortest_distance);  
  //printf("time_from_top_node_to_origin      :%f\n",time_from_top_node_to_origin  );
  //printf("time_from_last_node_to_destination:%f\n",time_from_last_node_to_destination);  


  //printf("addition:%d\n", o->move[objID].plan[OUTWARD][shortest_path_length-1]);
  // 
  /*
  printf("Ideal Outward Plan of obj %d:",objID);
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
  }
  printf("\n");//
  */




  //-- Calculate Homeward Shortest Path from End to Start 
  homeward_start = g->arc[d_arc].block_end_node[d_side];
  homeward_end   = g->arc[o_arc].block_start_node[o_side];  


  //--  Shortest Path Distance from End to Start 
  dijkstra(homeward_start, homeward_end, IDEAL_DISTANCE);


  //-- Calculate Ideal Distance from Destination to Origin
  o->move[objID].ideal_required_distance[HOMEWARD] = 
     shortest_distance 
     +( g->arc[o_arc].distance - distance_from_top_node_to_origin )
     +( g->arc[d_arc].distance - distance_from_last_node_to_destination ); 


  //printf("shortest_time                     :%f\n",shortest_distance);    
  //printf("time_from_last_node_to_origin     :%f\n", time_from_last_node_to_origin);  
  //printf("time_from_top_node_to_destination :%f\n", time_from_top_node_to_destination );


  
  //--  Shortest Path Time from End to Start 
  dijkstra(homeward_start, homeward_end, IDEAL_TIME);


  //-- Calculate Ideal Time from Origin to Last Block
  time_from_last_node_to_origin = 0;

  for(int blockID = o_block; blockID < g->arc[o_arc].num_block; blockID++){

    vel = g->arc[o_arc].block[o_side][blockID].ideal_velocity;
    len = g->arc[o_arc].block[o_side][blockID].block_length;

    time_from_last_node_to_origin += len/(vel * TIME_UNIT);
  }

  //-- Calculate Ideal Time from Destination to Top Block
  time_from_top_node_to_destination = 0;
  
  for(int blockID = 0; blockID < d_block; blockID++){

    vel = g->arc[d_arc].block[d_side][blockID].ideal_velocity;
    len = g->arc[d_arc].block[d_side][blockID].block_length;

    time_from_top_node_to_destination += len/(vel * TIME_UNIT);
  }


  //printf("addition:%d\n", o->move[objID].plan[HOMEWARD][shortest_path_length-1]);
  /*
  printf("Ideal Homeward Plan of obj %d:",objID);
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
  }
  printf("\n");  */



 //-- Calculate Ideal Distance from Origin to Destination 
  o->move[objID].ideal_required_time[HOMEWARD] = 
    (shortest_distance + time_from_last_node_to_origin + time_from_top_node_to_destination); 


  //printf("shortest_time                     :%f\n",shortest_distance);    
  //printf("time_from_last_node_to_origin     :%f\n", time_from_last_node_to_origin);  
  //printf("time_from_top_node_to_destination :%f\n", time_from_top_node_to_destination );




  //-- Set Ideal Path 

  o->move[objID].ideal_plan_length[OUTWARD]  = o->move[objID].plan_length[OUTWARD];  
  o->move[objID].ideal_plan_length[HOMEWARD] = o->move[objID].plan_length[HOMEWARD];

  for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){ 

    o->move[objID].ideal_plan[OUTWARD][nodeID] = o->move[objID].plan[OUTWARD][nodeID];
    
    //printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
  }

  for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
    
    o->move[objID].ideal_plan[HOMEWARD][nodeID] = o->move[objID].plan[HOMEWARD][nodeID];

    //printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
  }


  
  //printf("objID:%d ideal_required_time[OUTWARD]:%f\n",
  // objID,o->move[objID].ideal_required_time[OUTWARD]);
  //printf("objID:%d ideal_required_time[HOMEWARD]:%f\n",
  // objID,o->move[objID].ideal_required_time[HOMEWARD]);

  
  //printf("objID:%d ideal_required_distance[OUTWARD]:%f\n",
  // objID,o->move[objID].ideal_required_distance[OUTWARD]);
  //printf("objID:%d ideal_required_distance[HOMEWARD]:%f\n\n",
  // objID,o->move[objID].ideal_required_distance[HOMEWARD]);

}

//--------------------------------------------------------------------------//

void 
Navigator::normalPathPlanning(int objID){
  

  //-- Input Start and End Node
  int outward_start;  //-- Start Node of Outward Shortest Path for Dijkstra
  int outward_end;    //-- End Node of Outward Shortest Path by Dijkstra   
  int homeward_start; //-- Start Node of Homeward Shortest Path for Dijkstra
  int homeward_end;   //-- End Node of Homeward Shortest Path by Dijkstra 

  int o_arc  = o->move[objID].origin_arc; 
  int o_side = o->move[objID].origin_side; 
  int d_arc  = o->move[objID].destination_arc; //-- Arc of Destination     
  int d_side = o->move[objID].destination_side;//-- Side of Destination  

  int current_node = o->move[objID].end;


  //-- Calculate Outward Shortest Path from Start to End
  outward_start = current_node;
  outward_end   = g->arc[d_arc].block_start_node[d_side];
 

  dijkstra(outward_start, outward_end, o->move[objID].navi_type);


  for(int nodeID = 0; nodeID < shortest_path_length-1; nodeID++){  
    o->move[objID].plan[OUTWARD][nodeID] = Shortest_Path[nodeID+1];
  }  

  o->move[objID].plan[OUTWARD][shortest_path_length-1] = g->arc[d_arc].block_end_node[d_side]; 
  o->move[objID].plan_length[OUTWARD]                  = shortest_path_length;  


  //printf("addition:%d\n", o->move[objID].plan[OUTWARD][shortest_path_length-1]);
  /*
  printf("Outward Plan :");
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
  }
  printf("\n");  */




  //-- Calculate Homeward Shortest Path from End to Start 

  homeward_start = g->arc[d_arc].block_end_node[d_side];
  homeward_end   = g->arc[o_arc].block_start_node[o_side];  


  dijkstra(homeward_start, homeward_end, o->move[objID].navi_type);

  for(int nodeID = 0; nodeID < shortest_path_length-1; nodeID++){  
    o->move[objID].plan[HOMEWARD][nodeID] = Shortest_Path[nodeID+1];
  }  

  o->move[objID].plan[HOMEWARD][shortest_path_length-1] = g->arc[o_arc].block_end_node[o_side]; 
  o->move[objID].plan_length[HOMEWARD]                  = shortest_path_length;      


  //printf("addition:%d\n", o->move[objID].plan[HOMEWARD][shortest_path_length-1]);
  /*
  printf("Homeward Plan:");
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
  }
  printf("\n");  */


  //-- Calculate Travel Plan
  
  compositePlan(objID);

}

//--------------------------------------------------------------------------//

void 
Navigator::compositePlan(int objID){


  int outward_plan_length = o->move[objID].plan_length[OUTWARD];

  for(int nodeID = 0; nodeID < outward_plan_length; nodeID++){  
    o->move[objID].travel_plan[nodeID] = o->move[objID].plan[OUTWARD][nodeID];
  }  


  int homeward_plan_length = o->move[objID].plan_length[HOMEWARD];

  for(int nodeID = 0; nodeID < homeward_plan_length; nodeID++){
    o->move[objID].travel_plan[nodeID + outward_plan_length] = o->move[objID].plan[HOMEWARD][nodeID];
  }  


  o->move[objID].travel_plan_length = outward_plan_length + homeward_plan_length; 

  //
  /*
  printf("objID:%2d Travel Plan (%2d) :",objID,o->move[objID].travel_plan_length);
  for(int nodeID = 0; nodeID < o->move[objID].travel_plan_length; nodeID++){  
    printf("%d ",o->move[objID].travel_plan[nodeID]);
  }
  printf("\n");   
  printf("\n");  
  //
  */

}

//--------------------------------------------------------------------------//

void 
Navigator::successivePathPlanning(int objID){
  

  //-- Input Start and End Node
  int outward_start;  //-- Start Node of Outward Shortest Path for Dijkstra
  int outward_end;    //-- End Node of Outward Shortest Path by Dijkstra   
  int homeward_start; //-- Start Node of Homeward Shortest Path for Dijkstra
  int homeward_end;   //-- End Node of Homeward Shortest Path by Dijkstra 

  int o_arc  = o->move[objID].origin_arc; 
  int o_side = o->move[objID].origin_side; 
  int d_arc  = o->move[objID].destination_arc; //-- Arc of Destination     
  int d_side = o->move[objID].destination_side;//-- Side of Destination  

  int current_node = o->move[objID].end;


  //-- Calculate Outward Shortest Path from Start to End   
  if( o->move[objID].plan_direction == OUTWARD ){
   
    //outward_start = current_node;
    outward_end   = g->arc[d_arc].block_start_node[d_side];

    dijkstra(current_node, outward_end, o->move[objID].navi_type);
    
    
    for(int nodeID = 0; nodeID < shortest_path_length-1; nodeID++){  
      o->move[objID].plan[OUTWARD][nodeID] = Shortest_Path[nodeID+1];
    }  
  
    o->move[objID].plan[OUTWARD][shortest_path_length-1] = g->arc[d_arc].block_end_node[d_side];
    o->move[objID].plan_length[OUTWARD]                  = shortest_path_length;   
    
  }

  /*
  printf("Outward Plan  of 0bj %d:",objID);
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
  }
  printf("\n");*/



  //-- Calculate Homeward Shortest Path from End to Start 
  if( o->move[objID].plan_direction == HOMEWARD ){
  
    //homeward_start = current_node;
    homeward_end   = g->arc[o_arc].block_start_node[o_side];   
      
    
    dijkstra(current_node, homeward_end, o->move[objID].navi_type);
    
    
    for(int nodeID = 0; nodeID < shortest_path_length-1; nodeID++){  
      o->move[objID].plan[HOMEWARD][nodeID] = Shortest_Path[nodeID+1];
    }  
    o->move[objID].plan[HOMEWARD][shortest_path_length-1] = g->arc[o_arc].block_end_node[o_side];
    o->move[objID].plan_length[HOMEWARD]                  = shortest_path_length;   
    
  }

  /*
  printf("Homeward Plan of 0bj %d:",objID);
  for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
    printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
  }
  printf("\n");*/


}

//--------------------------------------------------------------------------//

void 
Navigator::dijkstra(int start, int end, int navi_type){

  
  //-- Begin of Main Algorithm of Dijkstra  

  //-- Initialize Map Data for Shortest Distance Path & Ideal Distance Path
  if(navi_type == SHORTEST_DISTANCE || navi_type == IDEAL_DISTANCE){

    for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
      for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
	ArcWeight[nodeID1][nodeID2] = g->Adjacency[nodeID1][nodeID2]; 
      }
    }
  }  


 //-- Initialize Map Data for Shortest Time Path
  if(navi_type == REPLANNING_ORIGIN || navi_type == SUCCESSIVE_REPLANNING){

    for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
      for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
	ArcWeight[nodeID1][nodeID2] = g->ExpectedTravelTime[nodeID1][nodeID2];
      }
    }
  }
  

  //-- Initialize Map Data for Ideal Time Path
  if(navi_type == IDEAL_TIME){

    for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
      for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
	ArcWeight[nodeID1][nodeID2] = g->IdealTravelTime[nodeID1][nodeID2]; 

	//printf("ideal time:%.2f\n",g->IdealTravelTime[nodeID1][nodeID2]);
      }
    }
  }  

  //-- Initialize Map Data for Ideal Time Path
  if(navi_type == CONGESTION_AVOIDANCE){

    for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
      for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
	ArcWeight[nodeID1][nodeID2] =  g->CongestionAvoidance[nodeID1][nodeID2]; 

	//printf("ideal time:%.2f\n",g->IdealTravelTime[nodeID1][nodeID2]);
      }
    }
  }  

  
  //-- Initialize Map Data for Declaring Path 
  if(navi_type == DECLARING_PATH){
    
    for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
      for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){

	if(g->BOOL_Adjacency[nodeID1][nodeID2] == TRUE){

	  ArcWeight[nodeID1][nodeID2] = 
	    g->ExpectedTravelTime[nodeID1][nodeID2] * g->DeclaredPlan[nodeID1][nodeID2];	

	  //printf("g->ExpectedTravelTime[%d][%d]:%f\n",nodeID1,nodeID2,g->ExpectedTravelTime[nodeID1][nodeID2]);
	  //printf("ArcWeight[%d][%d]            :%f\n",nodeID1,nodeID2,ArcWeight[nodeID1][nodeID2]);
	  //printf("g->DeclaredPlan[%d][%d]      :%f\n",nodeID1,nodeID2,g->DeclaredPlan[nodeID1][nodeID2]);
	}
	else{
	  ArcWeight[nodeID1][nodeID2] = MAX_VALUE;
	}

	/*
	if( (nodeID1==0 && nodeID2 ==5)||(nodeID1==5 && nodeID2 ==0)||
	    (nodeID1==2 && nodeID2 ==3)||(nodeID1==3 && nodeID2 ==2) ){

	  printf("g->ExpectedTravelTime[%d][%d]:%f\n",nodeID1,nodeID2,g->ExpectedTravelTime[nodeID1][nodeID2]);
	  printf("ArcWeight[%d][%d]            :%f\n",nodeID1,nodeID2,ArcWeight[nodeID1][nodeID2]);
	  printf("g->DeclaredPlan[%d][%d]      :%f\n",nodeID1,nodeID2,g->DeclaredPlan[nodeID1][nodeID2]);

	}
	*/  
	
      }
    }
  }


  /*
  for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
    for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
      //ArcWeight[nodeID1][nodeID2] = g->Adjacency[nodeID1][nodeID2]; 
      ArcWeight[nodeID1][nodeID2] = g->ExpectedTravelTime[nodeID1][nodeID2];
    }
  }*/


  //-- Initialize Parameters for Dijkstra  
  int    size;
  int    nearest;
  double min; 

  for(int nodeID = 0; nodeID < g->num_node; nodeID++){
    S[nodeID]                  = 0;
    Length[nodeID]             = MAX_VALUE; 
    Shortest_Path[nodeID]      = -999;
    temp_Shortest_Path[nodeID] = -999;
  }

  S[start] = 1;
  size     = 1;

  for(int nodeID = 0; nodeID < g->num_node; nodeID++){
        
    if(ArcWeight[start][nodeID] >= 0){
      Length[nodeID] = ArcWeight[start][nodeID];
      Path[nodeID]   = start;
    }
  }

  Length[start] = 0;
  Path[start]   = -1;//-- "-1" represents start node. 


  //--

  while(size < MAX_NODE){

    min = MAX_VALUE; 

    int initial_nodeID;
    int max_nodeID;
    int connect_nodeID; 


    initial_nodeID = rand()/g->num_node;
    max_nodeID     = g->num_node + initial_nodeID;


    for(int nodeID = initial_nodeID; nodeID < max_nodeID; nodeID++){      
    
      connect_nodeID = nodeID%g->num_node; 

      /*
      if(S[connect_nodeID]==0 && min > Length[connect_nodeID]){
	
	    min     = Length[connect_nodeID];
	    nearest = connect_nodeID;
      }
      */


      //printf("g->BOOL_Adjacency[%d][%d] = %d\n",
      //start,connect_nodeID,g->BOOL_Adjacency[start][connect_nodeID]);


      if(Length[connect_nodeID] > MAX_VALUE)
	printf("Length[connect_nodeID]:%f\n",Length[connect_nodeID]);


      //if(g->BOOL_Adjacency[start][connect_nodeID] == TRUE){

      if(S[connect_nodeID]==0 && min >= Length[connect_nodeID]){
	
	if( min == Length[connect_nodeID] ){
	  if( rand()%5 == TRUE ){
	    min     = Length[connect_nodeID];
	    nearest = connect_nodeID;
	  } 
	}
	else{
	  min     = Length[connect_nodeID];
	  nearest = connect_nodeID;
	}
      }
      
      //}
      
    }
    

    S[nearest] = 1;
    size++;


    initial_nodeID = rand()/g->num_node;
    max_nodeID     = g->num_node + initial_nodeID;


    for(int nodeID = initial_nodeID; nodeID < max_nodeID; nodeID++){      
    
      connect_nodeID = nodeID%g->num_node; 


    //initial_nodeID = rand()%g->node[nearest].num_connect_node;
    //max_nodeID     = initial_nodeID + g->node[nearest].num_connect_node;
      
      
    //for(int nodeID = initial_nodeID; nodeID < max_nodeID; nodeID++){ 
	
    // for(int nodeID = 0; nodeID < g->node[nearest].num_connect_node; nodeID++){
      
    //connect_nodeID = g->node[nearest].connect_node[ nodeID%g->node[nearest].num_connect_node ];


      //for(int connect_nodeID = 0; connect_nodeID < g->num_node; connect_nodeID++){
      /*
      if(g->Adjacency[nearest][connect_nodeID]!=999999 && S[connect_nodeID]!=1){
	if( Length[connect_nodeID]>(Length[nearest] + g->Adjacency[nearest][connect_nodeID]) ){
	  Length[connect_nodeID] = Length[nearest] + g->Adjacency[nearest][connect_nodeID];
	  Path[connect_nodeID]   = nearest;
	}
      }*/


      //
if(g->BOOL_Adjacency[nearest][connect_nodeID] == TRUE){

	if(ArcWeight[nearest][connect_nodeID]!= MAX_VALUE && S[connect_nodeID]!=1){
	  
	  if( Length[connect_nodeID]>=(Length[nearest] + ArcWeight[nearest][connect_nodeID])){
	    
	    if( Length[connect_nodeID]==(Length[nearest] + ArcWeight[nearest][connect_nodeID])){
	      if( rand()%5 == TRUE ){
		Length[connect_nodeID] = Length[nearest] + ArcWeight[nearest][connect_nodeID];
		Path[connect_nodeID]   = nearest;
	      }
	    }
	    else{
	      Length[connect_nodeID] = Length[nearest] + ArcWeight[nearest][connect_nodeID];
	      Path[connect_nodeID]   = nearest;
	    }
	  }
	}

	//
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
  //printf("shortest_path:");
  
  //
  /*
  for(int i = 0; i < shortest_path_length; i++){  
    printf("%d ",Shortest_Path[i]);
  }    
  printf("\n");  
  printf("path length   :%d\n",shortest_path_length);
  printf("%2d-%2d distance:%f\n",start, end, Length[end]);
  printf("\n");  
  //
  */

}

//--------------------------------------------------------------------------//

void
Navigator::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;  
}

void 
Navigator::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

//--------------------------------------------------------------------------//

