/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "InfoCenter.h"


 
//////////////////////////
//
// InformationCenter methods


//
//
//

//--------------------------------------------------------------------------//

InfoCenter::InfoCenter(void)
{ 

}

InfoCenter::~InfoCenter(void)
{ 

}

//--------------------------------------------------------------------------//

void 
InfoCenter::idealTrafficInfo(void)
{

  //-- In order to connect "g" in THIS CLASS(InfoCenter) and "g" in "Obj_location",
  //--  ( ol_in_ic.K_V_function(k, arcID, blockID) )
  //-- these members are called.
  ol_in_ic.getGeoInfo(g);
  ol_in_ic.getObjInfo(o);


  for(int arcID = 0; arcID < g->num_arc; arcID++){
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){

      double ideal_time;
      double sum_ideal_time = 0;

      double k;
      double velocity;
      double dL;

      int    start = g->arc[arcID].block_start_node[sideID];  
      int    end   = g->arc[arcID].block_end_node[sideID];  


      for(int blockID = 0; blockID < g->arc[arcID].num_block; blockID++){	
	//-- Velocity of second object is used for estimation.  
	//-- "Second object" means "object who is not Top of block". 

	k               = 0;
	velocity        = ol_in_ic.K_V_function(k, arcID, blockID);
	dL              = g->arc[arcID].block[sideID][blockID].block_length;
	ideal_time      = dL/(velocity *  TIME_UNIT);
	sum_ideal_time += ideal_time;

	g->arc[arcID].block[sideID][blockID].ideal_velocity = velocity;

      }

      g->IdealTravelTime[start][end] = sum_ideal_time;
      
      //printf("arcID:%d sideID:%d time:%.2f\n",arcID,sideID,sum_ideal_time);
      
    }

  }

  //printf("in traffic information center.\n");
  

}

//--------------------------------------------------------------------------//

void 
InfoCenter::updateTrafficInfo(void)
{

  //-- In order to connect "g" in THIS CLASS(InfoCenter) and "g" in "Obj_location",
  //-- these members are called.
  ol_in_ic.getGeoInfo(g);
  ol_in_ic.getObjInfo(o);


  for(int arcID = 0; arcID < g->num_arc; arcID++){
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){

      double expected_time;

      double sum_expected_time         = 0;
      double sum_congestion_avoid_time = 0;

      double k;
      double velocity;
      double dL;

      int    start = g->arc[arcID].block_start_node[sideID];  
      int    end   = g->arc[arcID].block_end_node[sideID];  

      double threshold_congestion      = 0.3;
      double preference_for_congestion = 100.0;
      //-- "preference_for_congestion" represents the preference for congestion.
      //-- The larger this parameter becomes, more object hates congestion.


      for(int blockID = 0; blockID < g->arc[arcID].num_block; blockID++){	
	//-- Velocity of second object is used for estimation.  
	//-- "Second object" means "object who is not Top of block". 

	k                  = g->arc[arcID].block[sideID][blockID].K;
	velocity           = ol_in_ic.K_V_function(k, arcID, blockID);
	dL                 = g->arc[arcID].block[sideID][blockID].block_length;


	//-- Update for "g->ExpectedTravelTime[][]"
	expected_time      = dL/velocity;
	sum_expected_time += expected_time;


	//-- Update for "g->CongestionAvoidance[][]"

	if(velocity < threshold_congestion){
	  expected_time    = dL/velocity * preference_for_congestion;
	}
	else{
	  expected_time    = dL/velocity;
	}

	sum_congestion_avoid_time += expected_time;
      }

      g->ExpectedTravelTime[start][end]  = sum_expected_time;   
      g->CongestionAvoidance[start][end] = sum_congestion_avoid_time;
      
      //printf("arcID:%d sideID:%d time:%.2f\n",arcID,sideID,sum_expected_time);
      
    }

  }

  //printf("in traffic information center.\n");
  

}

//--------------------------------------------------------------------------//

void 
InfoCenter::collectPlan(void)
{ 

  //-- In order to connect "g" in THIS CLASS(InfoCenter) and "g" in "Obj_location",
  //-- these members are called.
  ol_in_ic.getGeoInfo(g);
  ol_in_ic.getObjInfo(o);



  //-- Initialize "DeclaredPlan[][]"

  for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
    for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){

      g->DeclaredPlan[nodeID1][nodeID2]        = 1.0; 

    }
  }



  //-- Update "DeclaredPlan[][]" based on 
  //-- the plan of object using "Declaring Path" 
  
  int    current_node;
  int    next_node;
  int    next_arc;
  int    plan_length_outward;  
  int    plan_length_homeward; 
  int    plan_length_total;

  int    order_from_goal;
  double weight;

  for(int objID = 0; objID < o->num_move;objID++){
    
    if(o->move[objID].driving_status == ARRIVAL || o->move[objID].driving_status == STANDBY){
      continue;
    }

    if(o->move[objID].navi_type == DECLARING_PATH){

      plan_length_outward  = o->move[objID].plan_length[OUTWARD];
      plan_length_homeward = o->move[objID].plan_length[HOMEWARD];
      plan_length_total    = plan_length_outward + plan_length_homeward;
      

      //printf("now   :%d\n",o->move[objID].end);    
      
      if(o->move[objID].plan_direction == OUTWARD){
	
	for(int nodeID = 0; nodeID < plan_length_outward; nodeID++){
	  
	  current_node    = o->move[objID].plan[OUTWARD][nodeID];
	  next_node       = o->move[objID].plan[OUTWARD][nodeID+1];
	  
	  /*
	  order_from_goal = plan_length_outward - nodeID;
	  weight          = (double)order_from_goal/(double)plan_length_outward;
	  */
	  
	  double DP_ratio = (double)o->num_navi_type[DECLARING_PATH]/(double)o->num_move; 
	  double a        = 0.1;
	  
	  order_from_goal = plan_length_outward - nodeID;

	  //weight          = a*DP_ratio * (double)order_from_goal/(double)plan_length_outward;	  
	  weight          = a* (double)order_from_goal/(double)plan_length_outward;	 
	  

	  g->DeclaredPlan[current_node][next_node] += weight;
	  
	  //printf("DP_ratio = %f\n",DP_ratio);
	  //printf("plan  :%d\t",o->move[objID].plan_length[OUTWARD]); 
	  //printf("node  :%d\t",current_node);    
	  //printf("weight:%f\n",weight);	  
	}
      }


      if(o->move[objID].plan_direction == HOMEWARD){

	for(int nodeID = 0; nodeID < plan_length_homeward; nodeID++){
	  
	  current_node    = o->move[objID].plan[HOMEWARD][nodeID];
	  next_node       = o->move[objID].plan[HOMEWARD][nodeID+1];
	  
	  
	  /*
	  order_from_goal = plan_length_homeward - nodeID;
	  weight          = (double)order_from_goal/(double)plan_length_homeward;
	  */
	  
	 


	  double DP_ratio = (double)o->num_navi_type[DECLARING_PATH]/(double)o->num_move; 
	  double a        = 0.1;


	  order_from_goal = plan_length_homeward - nodeID;
	  
	  //weight          = a*DP_ratio * (double)order_from_goal/(double)plan_length_homeward;	 
	  weight          = a*(double)order_from_goal/(double)plan_length_homeward;	   
	  

	  g->DeclaredPlan[current_node][next_node] += weight;
	  

	  //printf("DP_ratio = %f\n",DP_ratio);
	  //printf("plan  :%d\t",o->move[objID].plan_length[HOMEWARD]);     
	  //printf("node  :%d\t",current_node);
	  //printf("weight:%f\n",weight);
	}
      }

      //printf("\n\n");

    }
    
  }

  /*
  for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
    for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
      
      printf("%f\n",g->DeclaredPlan[nodeID1][nodeID2]); 
      
    }
  }
  */


}

int 
InfoCenter::getNextArc(int current_node, int next_node)
{
  
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
    }   
    
    if(g->arc[candidate_arc].start == next_node && 
       g->arc[candidate_arc].end   == current_node){
      
      next_arc = candidate_arc;
    }
  }    


  return next_arc;
  
  
}



//--------------------------------------------------------------------------//

void 
InfoCenter::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;  
}

void 
InfoCenter::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

//--------------------------------------------------------------------------//

