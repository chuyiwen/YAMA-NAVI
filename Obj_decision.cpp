/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Obj_decision.h"


 
//////////////////////////
//
// ObjDecision methods


//
//
//

//--------------------------------------------------------------------------//

ObjDecision::ObjDecision(void)
{ 
}

ObjDecision::~ObjDecision(void)
{ 
}

//--------------------------------------------------------------------------//

void 
ObjDecision::initializePlan(int objID){


  //printf("obj:%d\n",objID);      

  //-- Get Information of Geometory and Moving Object
  navi.getGeoInfo(g);
  navi.getObjInfo(o);


  //-- Navigator makes plan for object.
  navi.normalPathPlanning(objID);
  navi.idealPathPlanning(objID);
  
}

//--------------------------------------------------------------------------//

void 
ObjDecision::chooseArc(int objID)
{

  int current_node  = o->move[objID].end;
  int previous_node = o->move[objID].start; 

  int current_arc   = o->move[objID].arc; 
  int current_side  = o->move[objID].side; 
  int current_block = o->move[objID].block;

  
  //-- Choose Next Node on Cross 
  int num_candidate_node = g->node[current_node].num_connect_node;
  int next_node_no;  
  int next_node;

  
  //-- Randam Choice of Next Node
  /*
  do{
    next_node_no = rand()% num_candidate_node;
    next_node    = g->node[current_node].connect_node[next_node_no];
  }while(next_node == previous_node);
  */
  //printf("obj:%d next_node:%d\n", objID, next_node);



  //-- Choice of Next Node based on Plan
  
  int progress  = o->move[objID].plan_progress;
  int direction = o->move[objID].plan_direction;
  

  //--  Shortest Distance Path & Replanning in Only Origin
  if(o->move[objID].navi_type == SHORTEST_DISTANCE || 
     o->move[objID].navi_type == REPLANNING_ORIGIN ){

    next_node = o->move[objID].travel_plan[progress];

    //printf("ST next_node %d\n",next_node);
  }


  //-- Succesive (Stepwise) Shortest Time Path Planning 
  if(o->move[objID].navi_type == SUCCESSIVE_REPLANNING || 
     o->move[objID].navi_type == CONGESTION_AVOIDANCE  ||
     o->move[objID].navi_type == DECLARING_PATH ){

    next_node = o->move[objID].plan[direction][0]; 

    //printf("RIS next_node %d\n",next_node);

    /*
    if(current_arc == 10){
      printf("next_node:%d\n",next_node);
      printf("Outward Plan :");
      for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
	printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
      }
      printf("\n");
      
      printf("Homeward Plan:");
      for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
	printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
      }
      printf("\n");
    }
    */
  }


  //o->move[objID].plan_progress++;//to Obj_location.cpp 
  //printf("objID:%d next:%d current node:%d plan:%d progress:%d direction:%d\n",  
  //	 objID,next_node, current_node,o->move[objID].plan[direction][progress],progress, direction);
  //printf("obj:%d progress:%d direction:%d  next_node:%d\n", 
  // objID, progress,  direction, next_node);
  


  //-- Calculate Next Arc based on Next Node
  int next_arc;
  int num_candidate_arc = g->node[current_node].num_connect_arc;
  //printf("current_node %d\t num candidate arc %d\n",current_node,num_candidate_arc);


  for(int arcID = 0; arcID < num_candidate_arc;arcID++){

    int candidate_arc = g->node[current_node].connect_arc[arcID];
    
    //printf("candidate arc %d\n",candidate_arc);

    if(g->arc[candidate_arc].start == current_node && 
       g->arc[candidate_arc].end   == next_node){

      next_arc = candidate_arc;

      //printf("1 next_arc %d\n",next_arc);
      //break;
    }   

    if(g->arc[candidate_arc].start == next_node && 
       g->arc[candidate_arc].end   == current_node){

      next_arc = candidate_arc;
      
      //printf("2 next_arc %d\n",next_arc);
      //break;
    }
  }
  
  
  //printf("next_node %d\n",next_node);
  //printf("next_arc %d\n",next_arc);


  //-- Result of Decision Making fo Object
  o->move[objID].choice_node = next_node;//-- Object would like to go to "choice_node".
  o->move[objID].choice_arc  = next_arc; //-- Object would like to go to "choice_arc".


}

//--------------------------------------------------------------------------//

void 
ObjDecision::checkCurrentPosition(int objID){


  //-- Change Plan in Origin and Distination
  int current_arc   = o->move[objID].arc; 
  int current_side  = o->move[objID].side; 
  int current_block = o->move[objID].block;
  int direction     = o->move[objID].plan_direction;


  //printf("arc:%2d side:%d block:%d\n", current_arc, current_side, current_block);  
  //printf("objID:%d progress:%2d length:%d\n", 
  //	 objID,o->move[objID].plan_progress, o->move[objID].travel_plan_length);  
 


  //-- Update Recquired Time and Distance in Each Step
  o->move[objID].required_time[direction]++; 

  if( o->move[objID].flag_move_new_block == TRUE){

    o->move[objID].required_distance[direction] += 
      g->arc[current_arc].block[current_side][current_block].block_length;
  }





  //-- Update Status of Objdect in Origin and Distination

  direction = o->move[objID].plan_direction;

  //-- In Origin
  if( (current_arc   == o->move[objID].origin_arc    &&
       current_side  == o->move[objID].origin_side &&  
       current_block == o->move[objID].origin_block) &&
      (o->move[objID].plan_direction == HOMEWARD) ){
    
    o->move[objID].plan_direction             = OUTWARD;
    o->move[objID].num_arrival[direction]++;
    o->move[objID].required_time[OUTWARD]     = 0; 
    o->move[objID].required_distance[OUTWARD] = 0;    

    //if(objID%100 == 0)
    //  printf("obj:%d change plan to OUTWARD.\n",objID);
  }

  //-- In Distination
  if( (current_arc   == o->move[objID].destination_arc    &&
       current_side  == o->move[objID].destination_side &&
       current_block == o->move[objID].destination_block) &&  
      (o->move[objID].plan_direction == OUTWARD) ){

    //o->move[objID].plan_direction              = HOMEWARD;  

    o->move[objID].num_arrival[direction]++;
    o->move[objID].arrival_step           = c->step;

    //printf("c->step %d\n",c->step);
    

    //o->move[objID].last_required_time          = o->move[objID].required_time[HOMEWARD]; 
    //o->move[objID].last_required_distance      = o->move[objID].required_distance[HOMEWARD];
    //o->move[objID].required_time[HOMEWARD]     = 0; 
    //o->move[objID].required_distance[HOMEWARD] = 0;


    o->move[objID].last_required_time           = o->move[objID].required_time[OUTWARD];
    o->move[objID].last_required_distance       = o->move[objID].required_distance[OUTWARD];

    o->move[objID].last_ideal_required_time     = o->move[objID].ideal_required_time[OUTWARD];
    o->move[objID].last_ideal_required_distance = o->move[objID].ideal_required_distance[OUTWARD];


    //o->move[objID].required_time[OUTWARD]       = 0; 
    //o->move[objID].required_distance[OUTWARD]   = 0;



    //printf("last_required_time     %d\n", o->move[objID].last_required_time );   
    //printf("last_ideal_required_time     %f\n", o->move[objID].last_ideal_required_time ); 
    //printf("last_required_distance %f\n", o->move[objID].last_required_distance );


    //if(objID%500 == 0)
    // printf("obj:%d change plan to HOMEWARD.arc:%d side:%d block:%d \n",
    //objID,current_arc,current_side,current_block);
    
    /*
      printf("Outward Plan :");
      for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
      printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
      }
      printf("\n");
      
      printf("Homeward Plan:");
      for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
      printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
      }
      printf("\n");
    */

  }






  //-- Update Efficeincy Time and Distance
  double required_time;         
  double present_required_time; 
  double ideal_time;            

  double required_distance;     
  double present_required_distance;
  double ideal_distance;           

  //--
  if(o->move[objID].plan_direction == HOMEWARD)
    direction = HOMEWARD;//OUTWARD;
  else
    direction = OUTWARD;//HOMEWARD;


  /*
  required_time             = (double)o->move[objID].required_time[direction];  
  ideal_time                = o->move[objID].ideal_required_time[direction];
  required_distance         = o->move[objID].required_distance[direction];  
  ideal_distance            = o->move[objID].ideal_required_distance[direction];
  o->move[objID].efficiency_time             = required_time/ideal_time;     
  o->move[objID].efficiency_distance         = required_distance/ideal_distance;   
  */


  required_time             = (double)o->move[objID].last_required_time;  
  ideal_time                = o->move[objID].last_ideal_required_time;

  //printf("ideal_time    %f\n", ideal_time ); 
  //printf("required_time %f\n\n", required_time); 

  required_distance         = o->move[objID].last_required_distance;  
  ideal_distance            = o->move[objID].last_ideal_required_distance;

  
  if(ideal_time == 0){
    o->move[objID].efficiency_time     = 0;
   }
  else{
    o->move[objID].efficiency_time     = required_time/ideal_time; 

    //printf("efficiency_time %f\n",o->move[objID].efficiency_time);

  }


  if(ideal_distance == 0){
    o->move[objID].efficiency_distance = 0;
  }
  else{
    o->move[objID].efficiency_distance = required_distance/ideal_distance;   
  }



  //printf("required_time:%f /%f \t",
  //  required_time, o->move[objID].ideal_required_time[direction]);
  //
  //if(objID%100 == 0){
  //printf("objID:%3d required_distance:%f/%f efficiency:%f\n",
  //objID,o->move[objID].required_distance[direction], o->move[objID].ideal_required_distance[direction], 
  //o->move[objID].efficiency_distance );
  //}



  //--
  if(o->move[objID].plan_direction == HOMEWARD)
    direction = HOMEWARD;
  else
    direction = OUTWARD;


  present_required_time     = (double)o->move[objID].required_time[direction];  
  ideal_time                = o->move[objID].ideal_required_time[direction];

  present_required_distance = o->move[objID].required_distance[direction];  
  ideal_distance            = o->move[objID].ideal_required_distance[direction];
  
  o->move[objID].present_efficiency_time     = present_required_time/ideal_time; 
  o->move[objID].present_efficiency_distance = present_required_distance/ideal_distance;  


  //printf("present_required_time:%f /%f\n",
  //     present_required_time, o->move[objID].ideal_required_time[direction]);



  //-- Update Status of Objdect in Origin and Distination

  direction = o->move[objID].plan_direction;



  /*
  //-- In Origin
  if( (current_arc   == o->move[objID].origin_arc    &&
       current_side  == o->move[objID].origin_side &&  
       current_block == o->move[objID].origin_block) &&
      (o->move[objID].plan_direction == HOMEWARD) ){
    
    o->move[objID].plan_direction             = OUTWARD;
    o->move[objID].num_arrival[direction]++;
    o->move[objID].required_time[OUTWARD]     = 0; 
    o->move[objID].required_distance[OUTWARD] = 0;    

    //if(objID%500 == 0)
    //  printf("obj:%d change plan to OUTWARD.\n",objID);
  }

  //-- In Distination
  if( (current_arc   == o->move[objID].destination_arc    &&
       current_side  == o->move[objID].destination_side &&
       current_block == o->move[objID].destination_block) &&  
      (o->move[objID].plan_direction == OUTWARD) ){

    //o->move[objID].plan_direction              = HOMEWARD;  
    o->move[objID].num_arrival[direction]++;

    //o->move[objID].last_required_time          = o->move[objID].required_time[HOMEWARD]; 
    //o->move[objID].last_required_distance      = o->move[objID].required_distance[HOMEWARD];
    //o->move[objID].required_time[HOMEWARD]     = 0; 
    //o->move[objID].required_distance[HOMEWARD] = 0;


    o->move[objID].last_required_time           = o->move[objID].required_time[OUTWARD];
    o->move[objID].last_required_distance       = o->move[objID].required_distance[OUTWARD];

    o->move[objID].last_ideal_required_time     = o->move[objID].ideal_required_time[OUTWARD];
    o->move[objID].last_ideal_required_distance = o->move[objID].ideal_required_distance[OUTWARD];


    o->move[objID].required_time[OUTWARD]       = 0; 
    o->move[objID].required_distance[OUTWARD]   = 0;



    //printf("last_required_time     %d\n", o->move[objID].last_required_time );   
    //printf("last_ideal_required_time     %f\n", o->move[objID].last_ideal_required_time ); 
    //printf("last_required_distance %f\n", o->move[objID].last_required_distance );


    //if(objID%500 == 0)
    // printf("obj:%d change plan to HOMEWARD.arc:%d side:%d block:%d \n",
    //objID,current_arc,current_side,current_block);
    
    
    //  printf("Outward Plan :");
    //  for(int nodeID = 0; nodeID < o->move[objID].plan_length[OUTWARD]; nodeID++){  
    //  printf("%d ",o->move[objID].plan[OUTWARD][nodeID]);
    //  }
    //   printf("\n");
      
    //  printf("Homeward Plan:");
    //  for(int nodeID = 0; nodeID < o->move[objID].plan_length[HOMEWARD]; nodeID++){  
    //  printf("%d ",o->move[objID].plan[HOMEWARD][nodeID]);
    //  }
    //  printf("\n");
    

  }

  */





  //-- Shortest Distance 
  if( o->move[objID].navi_type == SHORTEST_DISTANCE){

    if(  o->move[objID].travel_plan_length == o->move[objID].plan_progress ){
      
      o->move[objID].plan_progress  = 0;
    }
  }


  //-- Replanning in Origin 
  //-- In origin, Navigator makes plan for object AGEIN
  //-- based on current traffic status.
  if( o->move[objID].navi_type == REPLANNING_ORIGIN ){

    if(  o->move[objID].travel_plan_length == o->move[objID].plan_progress ){
      
      o->move[objID].plan_progress  = 0;
      navi.normalPathPlanning(objID);
    }
  }


  //-- Successive Replanning & Congestion Avoidance & Declaring Path
  //-- Navigator makes plan for object on EVERY cross
  //-- based on CURRENT traffic status.
  if(o->move[objID].navi_type == SUCCESSIVE_REPLANNING || 
     o->move[objID].navi_type == CONGESTION_AVOIDANCE  || 
     o->move[objID].navi_type == DECLARING_PATH ){

    if(  current_block == 0 ){
      navi.successivePathPlanning(objID);
    }
  }


}

//--------------------------------------------------------------------------//
void 
ObjDecision::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;  
}

void 
ObjDecision::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

void 
ObjDecision::getCtlInfo(struct ITERATION_CONTROL *ext_ctl)
{ 
  //printf("in :getCtlInfo.\n");
  c = ext_ctl;  
}

//--------------------------------------------------------------------------//

