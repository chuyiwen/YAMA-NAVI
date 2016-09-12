/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Monitor.h"


 
//////////////////////////
//
// TrafficMonitor methods


//
//
//

//--------------------------------------------------------------------------//

Monitor::Monitor(void)
{ 

}

Monitor::~Monitor(void)
{ 

}

//--------------------------------------------------------------------------//

void 
Monitor::initializeParameter(void)
{

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){

    m->ave_gain[averageID]                              = 0;
    m->ave_num_stop[averageID]                          = 0; 
    m->ave_num_arrival[averageID]                       = 0; 
    m->ave_velocity[averageID]                          = 0;     
    m->ave_required_time[averageID]                     = 0;
    m->ave_required_distance[averageID]                 = 0;
    m->ave_present_required_time[averageID]             = 0;
    m->ave_present_required_distance[averageID]         = 0;
    m->ave_ideal_required_time[averageID]               = 0;     
    m->ave_ideal_required_distance[averageID]           = 0; 
    
    m->ave_efficiency_time[averageID]                   = 0;             
    m->ave_efficiency_distance[averageID]               = 0;   
    m->ave_present_efficiency_time[averageID]           = 0; 
    m->ave_present_efficiency_distance[averageID]       = 0;     

    m->variance_efficiency_time[averageID]              = 0;
    


    m->ave_gain_trial[averageID]                        = 0;     
    m->ave_num_stop_trial[averageID]                    = 0;           
    m->ave_num_arrival_trial[averageID]                 = 0; 
    m->ave_velocity_trial[averageID]                    = 0; 
    m->ave_required_time_trial[averageID]               = 0;
    m->ave_required_distance_trial[averageID]           = 0;
    m->ave_present_required_time_trial[averageID]       = 0;
    m->ave_present_required_distance_trial[averageID]   = 0;   
    m->ave_ideal_required_time_trial[averageID]         = 0;
    m->ave_ideal_required_distance_trial[averageID]     = 0; 
    
    m->ave_efficiency_time_trial[averageID]             = 0;  
    m->ave_efficiency_distance_trial[averageID]         = 0;   
    m->ave_present_efficiency_time_trial[averageID]     = 0;  
    m->ave_present_efficiency_distance_trial[averageID] = 0;
  
    m->ave_variance_efficiency_time_trial[averageID]    = 0;
  } 
  
}

//--------------------------------------------------------------------------//

void 
Monitor::openOuputFile_step(char *filename)
{ 

  char output_file_step[100];  
  char output_file_K_step[100];  
  char output_file_D_step[100];

  sprintf(output_file_step,      "%s",filename); 
  sprintf(output_file_K_step,    "%s_K",filename);  
  sprintf(output_file_D_step,    "%s_D",filename);

  fp_output_step   = fopen(output_file_step,"w");  
  fp_output_K_step = fopen(output_file_K_step,"w");  
  fp_output_D_step = fopen(output_file_D_step,"w"); 

}

void 
Monitor::openOuputFile_step(char *filename, int num_obj, int order)
{ 

  char output_file_step[100];  
  char output_file_K_step[100]; 
  char output_file_D_step[100];
  
  sprintf(output_file_step, "%s%d_obj%d",filename, order, num_obj);  
  sprintf(output_file_K_step,"%s%d_obj%d_K",filename, order, num_obj); 
  sprintf(output_file_D_step,"%s%d_obj%d_D",filename, order, num_obj);

  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n",output_file_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_D_step);

  fp_output_step   = fopen(output_file_step,"w");  
  fp_output_K_step = fopen(output_file_K_step,"w");   
  fp_output_D_step = fopen(output_file_D_step,"w");  

}

void 
Monitor::openOuputFile_step(char *filename, int num_obj, int first_ratio, int order)
{ 

  char output_file_step[100];  
  char output_file_K_step[100];  
  char output_file_D_step[100];
  
  sprintf(output_file_step, "%s%d_obj%d_SD%d",   filename, order, num_obj, first_ratio);  
  sprintf(output_file_K_step,"%s%d_obj%d_SD%d_K",filename, order, num_obj, first_ratio);   
  sprintf(output_file_D_step,"%s%d_obj%d_SD%d_D",filename, order, num_obj, first_ratio);  

  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n"  ,output_file_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_D_step);


  fp_output_step   = fopen(output_file_step,"w");  
  fp_output_K_step = fopen(output_file_K_step,"w");   
  fp_output_D_step = fopen(output_file_D_step,"w");  

}

void 
Monitor::openOuputFile_step(char *filename, int num_obj, int first_ratio, int second_ratio, int order)
{ 

  char output_file_step[100];  
  char output_file_K_step[100];  
  char output_file_D_step[100];
  
  sprintf(output_file_step,  "%s%d_obj%d_SD%d_ST%d",  filename, order, num_obj, first_ratio, second_ratio);  
  sprintf(output_file_K_step,"%s%d_obj%d_SD%d_ST%d_K",filename, order, num_obj, first_ratio, second_ratio);   
  sprintf(output_file_D_step,"%s%d_obj%d_SD%d_ST%d_D",filename, order, num_obj, first_ratio, second_ratio);  

  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n",output_file_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_D_step);

  fp_output_step   = fopen(output_file_step,"w");  
  fp_output_K_step = fopen(output_file_K_step,"w");   
  fp_output_D_step = fopen(output_file_D_step,"w");  

}

void 
Monitor::openOuputFile_step(char *filename, int num_obj, int  ratio1, int ratio2, int ratio3, int order)
{ 

  char output_file_step[100];  
  char output_file_K_step[100];  
  char output_file_D_step[100];
  
  sprintf(output_file_step,  "%s%d_obj%d_SD%d_ST%d_RIS%d",  filename, order, num_obj, ratio1, ratio2, ratio3);  
  sprintf(output_file_K_step,"%s%d_obj%d_SD%d_ST%d_RIS%d_K",filename, order, num_obj, ratio1, ratio2, ratio3); 
  sprintf(output_file_D_step,"%s%d_obj%d_SD%d_ST%d_RIS%d_D",filename, order, num_obj, ratio1, ratio2, ratio3); 

  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n"  ,output_file_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_step); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_D_step);

  fp_output_step   = fopen(output_file_step,"w");  
  fp_output_K_step = fopen(output_file_K_step,"w");   
  fp_output_D_step = fopen(output_file_D_step,"w");  

}

void 
Monitor::closeOuputFile_step(void)
{ 

  fclose(fp_output_step); 
  fclose(fp_output_K_step);  
  fclose(fp_output_D_step);

}

//--------------------------------------------------------------------------//

void 
Monitor::openOuputFile_trial(char *filename)
{ 

  char output_file_trial[100];   
  char output_file_K_trial[100]; 

  sprintf(output_file_trial,  "%s_Ave",filename);
  sprintf(output_file_K_trial,"%s_K_Ave",filename);

  fp_output_trial   = fopen(output_file_trial,"w");  
  fp_output_K_trial = fopen(output_file_K_trial,"w");

}

/*
void 
Monitor::openOuputFile_trial(char *filename, int num_obj){ 

  char output_file_trial[100];    
  char output_file_K_trial[100]; 
    
  sprintf(output_file_trial, "%s_obj%d_Ave",filename, num_obj);  
  sprintf(output_file_K_trial, "%s_obj%d_K_Ave",filename, num_obj);
  sprintf(output_file_trial, "%s_Ave_obj%d",filename, num_obj);  

  sprintf(output_file_K_trial, "%s_Ave_obj%d_K",filename, num_obj);
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n",output_file_trial); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_trial);

  fp_output_trial   = fopen(output_file_trial,"w");  
  fp_output_K_trial = fopen(output_file_K_trial,"w");  
}
*/


void 
Monitor::openOuputFile_trial(char *filename, int ratio_SD)
{ 

  char output_file_trial[100];    
  char output_file_K_trial[100]; 
    
  sprintf(output_file_trial, "%s_Ave_SD%d",filename, ratio_SD);  
  sprintf(output_file_K_trial, "%s_Ave_SD%d_K",filename, ratio_SD);

  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n",output_file_trial); 
  printf("\n\n\n Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_trial);

  fp_output_trial   = fopen(output_file_trial,"w");  
  fp_output_K_trial = fopen(output_file_K_trial,"w");

}


void 
Monitor::openOuputFile_trial(char *filename, int num_obj, int order)
{ 

  char output_file_trial[100];    
  char output_file_K_trial[100]; 
    
  //sprintf(output_file_trial, "%s%d_obj%d_Ave",filename, order, num_obj);  
  //sprintf(output_file_K_trial, "%s%d_obj%d_K_Ave",filename, order, num_obj);

  sprintf(output_file_trial, "%s_Ave_obj%d",filename, num_obj);  
  sprintf(output_file_K_trial, "%s_Ave_obj%d_K",filename, num_obj);

  printf(" Now writing Simulation Result to File \"%s\"...\n",output_file_trial); 
  printf(" Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_trial);

  fp_output_trial   = fopen(output_file_trial,"w");  
  fp_output_K_trial = fopen(output_file_K_trial,"w");

}

void 
Monitor::openOuputFile_trial(char *filename, int num_obj, int ratio1, int ratio2, int ratio3)
{ 

  char output_file_trial[100];    
  char output_file_K_trial[100]; 
    
  //sprintf(output_file_trial, "%s%d_obj%d_Ave",filename, order, num_obj);  
  //sprintf(output_file_K_trial, "%s%d_obj%d_K_Ave",filename, order, num_obj);
  //sprintf(output_file_trial, "%s_Ave_obj%d",filename, num_obj);  
  //sprintf(output_file_K_trial, "%s_Ave_obj%d_K",filename, num_obj);  

  sprintf(output_file_trial,  "%s_obj%d_SD%d_ST%d_RIS%d",  filename, num_obj, ratio1, ratio2, ratio3);  
  sprintf(output_file_K_trial,"%s_obj%d_SD%d_ST%d_RIS%d_K",filename, num_obj, ratio1, ratio2, ratio3); 

  printf(" Now writing Simulation Result to File \"%s\"...\n",output_file_trial); 
  printf(" Now writing Simulation Result to File \"%s\"...\n\n",output_file_K_trial);

  fp_output_trial   = fopen(output_file_trial,"w");  
  fp_output_K_trial = fopen(output_file_K_trial,"w");

}


void 
Monitor::closeOuputFile_trial()
{ 

  fclose(fp_output_trial); 
  fclose(fp_output_K_trial); 
 
}

//--------------------------------------------------------------------------//

void 
Monitor::updateMacroParameter_step(void)
{

  //-- In order to connect "g" in THIS CLASS(Monitor) and "g" in "Obj_location",
  //-- these members are called.
  ol_in_ic.getGeoInfo(g);
  ol_in_ic.getObjInfo(o);



  int step = c->step;
  if(c->step == 0)
    step = 1;
 
  
  int num_move;// = o->num_move;

  /*
  if(o->num_move == 0)
    num_move = 1 ;
  */

  
  //-- Average Time and Distance of All Objects
  //--   i) from Origin to Destination 
  //--   ii)from Destination to Origin 

  //-- Initialize of Macro Parameter
  
  //int    sum_num_standby[NUM_AVERAGE]; 
  //int    sum_num_driving[NUM_AVERAGE];
  //int    sum_num_arrival[NUM_AVERAGE];  
  int    sum_driving_arrival[NUM_AVERAGE];  
  
  double sum_required_time[NUM_AVERAGE];
  double sum_required_distance[NUM_AVERAGE];
  double sum_present_required_time[NUM_AVERAGE];
  double sum_present_required_distance[NUM_AVERAGE];
  double sum_ideal_required_time[NUM_AVERAGE];
  double sum_ideal_required_distance[NUM_AVERAGE];
  
  double sum_efficiency_time[NUM_AVERAGE];       
  double sum_efficiency_distance[NUM_AVERAGE];    
  double sum_present_efficiency_time[NUM_AVERAGE];
  double sum_present_efficiency_distance[NUM_AVERAGE];
  

  o->num_navi_type[0] = o->present_num_ShortestDistance; 
  o->num_navi_type[1] = o->present_num_ReplanningInOrigin;
  o->num_navi_type[2] = o->present_num_SuccessiveReplanning;
  o->num_navi_type[3] = o->present_num_CongestionAvoidance;  
  o->num_navi_type[4] = o->present_num_DeclaringPath;
  o->num_navi_type[5] = o->num_move;//sum type 1-2-3-4


  //printf("num_obj_generate[0] %d\n",o->present_num_ShortestDistance);    
  //printf("num_obj_generate[1] %d\n",o->present_num_ReplanningInOrigin);  
  //printf("num_obj_generate[2] %d\n",o->present_num_SuccessiveReplanning);    
  //printf("num_obj_generate[3] %d\n",o->present_num_CongestionAvoidance);  
  //printf("num_obj_generate[4] %d\n",o->present_num_DeclaringPath);


  //for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
  //  printf("o->num_navi_type[%d] = %d\n",averageID,o->num_navi_type[averageID]);
  //}

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    o->num_standby[averageID] = 0;      
    o->num_waiting[averageID] = 0;    
    o->num_driving[averageID] = 0;      
    o->num_arrival[averageID] = 0;     
  }


  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){

    //sum_num_standby[averageID]                 = 0;    
    //sum_num_driving[averageID]                 = 0;      
    //sum_num_arrival[averageID]                 = 0;     

    sum_driving_arrival[averageID]             = 0;
    
    sum_required_time[averageID]               = 0;     
    sum_required_distance[averageID]           = 0;     
    sum_present_required_time[averageID]       = 0;     
    sum_present_required_distance[averageID]   = 0;    
    sum_ideal_required_time[averageID]         = 0;     
    sum_ideal_required_distance[averageID]     = 0;     
    
    sum_efficiency_time[averageID]             = 0;     
    sum_efficiency_distance[averageID]         = 0;     
    sum_present_efficiency_time[averageID]     = 0;     
    sum_present_efficiency_distance[averageID] = 0;  
  }


  //-- Calculate Sum of Objecst Parameter 
  for(int objID = 0; objID < o->num_move; objID++){


    /*
    //-- Test Output of Object Status
    if(objID%100 == 0 || objID%106 == 0){
      
      printf("objID:%d %3d required_distance:%.1f/%f efficiency:%f\n",
	     o->move[objID].navi_type,
	     objID,o->move[objID].required_distance[0], o->move[objID].ideal_required_distance[0], 
	     o->move[objID].efficiency_distance );
      
      printf("path:");
      for(int nodeID = 0; nodeID <o->move[objID].actual_plan_length; nodeID++){
	printf("%2d ",o->move[objID].actual_plan[nodeID]);
      }
      printf("\n");   
      printf("path:");
      for(int nodeID = 0; nodeID <o->move[objID].ideal_plan_length[0]; nodeID++){
	printf("%2d ",o->move[objID].ideal_plan[0][nodeID]);
      }
      printf("\n"); 
      printf("\n"); 
    }    */
    

    for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
      
      if( (averageID == o->move[objID].navi_type) || ( averageID == ALL_AVERAGE) ){

	/*
	if(o->move[objID].driving_status == STANDBY){
	  o->num_standby[averageID]++;     
	}
	*/

	if(o->move[objID].driving_status == WAITING){

	  o->num_waiting[averageID]++;	  
	}

	if(o->move[objID].driving_status == DRIVING){

	  o->num_driving[averageID]++;	  

	  sum_present_efficiency_time[averageID]     += o->move[objID].present_efficiency_time;     
	  sum_present_efficiency_distance[averageID] += o->move[objID].present_efficiency_distance; 
	}   


	if(o->move[objID].driving_status == ARRIVAL){
	  
	  o->num_arrival[averageID]++;    

	  sum_required_time[averageID]       += (double)o->move[objID].last_required_time;   
	  sum_required_distance[averageID]   += o->move[objID].last_required_distance;

	  sum_efficiency_time[averageID]     += o->move[objID].efficiency_time;   
	  sum_efficiency_distance[averageID] += o->move[objID].efficiency_distance; 	
	  
	  //printf("efficiency_time        %f\n", o->move[objID].efficiency_time); 
	  	  
	  
	  //-- 
	  int direction;
	  
	  if(o->move[objID].plan_direction == HOMEWARD)
	    direction = HOMEWARD;
	  else
	    direction = OUTWARD;

	  sum_ideal_required_time[averageID]         += o->move[objID].ideal_required_time[direction];
	  sum_ideal_required_distance[averageID]     += o->move[objID].ideal_required_distance[direction];
	}
      }     
    }
  }
   

  /*
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){

    // o->num_standby[averageID] = o->Max_Obj - ( o->num_driving[averageID] + o->num_arrival[averageID]);
  }
  */



  //-- Check Number of Objects Driving and Arriving

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    
    sum_driving_arrival[averageID] = 
      o->num_waiting[averageID] + o->num_driving[averageID] + o->num_arrival[averageID];
    
    if( o->num_navi_type[averageID] !=  
	o->num_waiting[averageID] + o->num_driving[averageID] + o->num_arrival[averageID] ){
      
      if( o->num_navi_type[averageID] >  
	  o->num_waiting[averageID] + o->num_driving[averageID] + o->num_arrival[averageID] ){
	
	printf("1 Error ! %d objects are illegally lost at updateMacroParameter_step() in Monitor.cpp\n\n", 
	       o->num_navi_type[averageID] 
	       - (o->num_waiting[averageID] + o->num_driving[averageID] + o->num_arrival[averageID]) );

	
	printf("o->num_navi_type[%d]=%d\n",averageID,o->num_navi_type[averageID]);		
	printf("o->num_waiting[%d]=  %d\n",averageID,o->num_waiting[averageID]);
	printf("o->num_driving[%d]=  %d\n",averageID,o->num_driving[averageID]);
	printf("o->num_arrival[%d]=  %d\n\n",averageID,o->num_arrival[averageID]);

      }
      else{
	printf("2 Error ! %d objects are illegally added at updateMacroParameter_step() in Monitor.cpp\n\n", 
	       (o->num_waiting[averageID] + o->num_driving[averageID] + o->num_arrival[averageID]) 
	       - o->num_navi_type[averageID] );	

	printf("o->num_navi_type[%d]=%d\n",averageID,o->num_navi_type[averageID]);	
	printf("o->num_waiting[%d]=  %d\n",averageID,o->num_waiting[averageID]);	
	printf("o->num_driving[%d]=  %d\n",averageID,o->num_driving[averageID]);
	printf("o->num_arrival[%d]=  %d\n\n",averageID,o->num_arrival[averageID]);
      }
      
      exit(0);
    }
    
  }
  




  //-- (PART 1) Calculate Average based on Sum of Objecst Parameter 
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    
        
    if(o->num_arrival[averageID] == 0){
      num_move = 1;
    }
    else{
      num_move = o->num_arrival[averageID]; //num_move = o->num_navi_type[averageID];
    }  
    
    
    if( (averageID ==  ALL_AVERAGE) || (num_move > 0) ){
      
      m->ave_num_arrival[averageID]                 
	=  (double)o->num_arrival[averageID]/(sum_driving_arrival[averageID]);

                                                      //(double)sum_num_arrival[averageID]/(step*num_move);

      m->ave_required_time[averageID]               = sum_required_time[averageID]/num_move;
      m->ave_required_distance[averageID]           = sum_required_distance[averageID]/num_move;
      
      //m->ave_present_required_time[averageID]       = sum_present_required_time[averageID]/num_move;
      //m->ave_present_required_distance[averageID]   = sum_present_required_distance[averageID]/num_move;
      
      m->ave_ideal_required_time[averageID]         = sum_ideal_required_time[averageID]/num_move;
      m->ave_ideal_required_distance[averageID]     = sum_ideal_required_distance[averageID]/num_move;
      
      m->ave_efficiency_time[averageID]             = sum_efficiency_time[averageID]/num_move;             
      m->ave_efficiency_distance[averageID]         = sum_efficiency_distance[averageID]/num_move;       
      
      //m->ave_present_efficiency_time[averageID]     = sum_present_efficiency_time[averageID]/num_move; 
      //m->ave_present_efficiency_distance[averageID] = sum_present_efficiency_distance[averageID]/num_move;
    
    }
  }
  

  
  //-- Calculate Variance Travel Time Efficiency
  
  double sum_pow[NUM_AVERAGE];
  
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    sum_pow[averageID] = 0;
  }
  
  
  for(int objID = 0; objID < o->num_move; objID++){

    if(o->move[objID].driving_status == STANDBY || 
       o->move[objID].driving_status == WAITING ||
       o->move[objID].driving_status == DRIVING){
      continue;
    }
    
    for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
      if( (averageID == o->move[objID].navi_type) || ( averageID == ALL_AVERAGE) ){
	sum_pow[averageID] += 
	  pow( o->move[objID].efficiency_time - m->ave_efficiency_time[averageID],2.0); 
      }
    }
  }
  
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    if(o->num_arrival[averageID] == 0){
      num_move = 1;
    }
    else{
      num_move = o->num_arrival[averageID];
    }
    m->variance_efficiency_time[averageID] 
      = sum_pow[averageID]/(double)num_move;
  }



  
  //-- (PART 2) Calculate Average based on Sum of Objecst Parameter 
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
    

    if(o->num_arrival[averageID] == 0){
      num_move = 1;
    }
    else{
      num_move = o->num_arrival[averageID];    //num_move = o->num_navi_type[averageID];
    }

    if( (averageID ==  ALL_AVERAGE) || (num_move > 0) ){

      //if(step > 500){
      //int ave_step = step - 501;
      
      if(step > 0){

	int ave_step = step-1;


	if(m->ave_efficiency_time[averageID] > 0){


	  m->ave_num_arrival_trial[averageID]              = m->ave_num_arrival[averageID];
	  
	  m->ave_required_time_trial[averageID]            = m->ave_required_time[averageID];	  
	  m->ave_required_distance_trial[averageID]        = m->ave_required_distance[averageID];
	  
	  m->ave_ideal_required_time_trial[averageID]      = m->ave_ideal_required_time[averageID];  
	  m->ave_ideal_required_distance_trial[averageID]  = m->ave_ideal_required_distance[averageID];  
	  
	  m->ave_efficiency_time_trial[averageID]          = m->ave_efficiency_time[averageID];	  
	  m->ave_efficiency_distance_trial[averageID]      = m->ave_efficiency_distance[averageID];    

	  m->ave_variance_efficiency_time_trial[averageID] = m->variance_efficiency_time[averageID];




	  m->ave_present_required_time_trial[averageID]     
	    = calcuAve(ave_step, 
		       m->ave_present_required_time_trial[averageID], 
		       m->ave_present_required_time[averageID]);
	  
	  m->ave_present_required_distance_trial[averageID] 
	    = calcuAve(ave_step, 
		       m->ave_present_required_distance_trial[averageID], 
		       m->ave_present_required_distance[averageID]);
	  	  
	  m->ave_present_efficiency_time_trial[averageID]      
	    = calcuAve(ave_step, 
		       m->ave_present_efficiency_time_trial[averageID], 
		       m->ave_present_efficiency_time[averageID]);
	  
	  m->ave_present_efficiency_distance_trial[averageID] 
	    = calcuAve(ave_step,
		       m->ave_present_efficiency_distance_trial[averageID],
		       m->ave_present_efficiency_distance[averageID]);
	  
	  /*
	  m->ave_num_arrival_trial[averageID]             
	    = calcuAve(ave_step, 
		       m->ave_num_arrival_trial[averageID], 
		       m->ave_num_arrival[averageID]);
	  
	  m->ave_required_time_trial[averageID]           
	    = calcuAve(ave_step, 
		       m->ave_required_time_trial[averageID], 
		       m->ave_required_time[averageID]);
	  
	  m->ave_required_distance_trial[averageID]       
	    = calcuAve(ave_step, 
		       m->ave_required_distance_trial[averageID], 
		       m->ave_required_distance[averageID]);
	  
	  m->ave_present_required_time_trial[averageID]     
	    = calcuAve(ave_step, 
		       m->ave_present_required_time_trial[averageID], 
		       m->ave_present_required_time[averageID]);
	  
	  m->ave_present_required_distance_trial[averageID] 
	    = calcuAve(ave_step, 
		       m->ave_present_required_distance_trial[averageID], 
		       m->ave_present_required_distance[averageID]);
	  
	  m->ave_ideal_required_time_trial[averageID]     
	    = m->ave_ideal_required_time[averageID];  
	  
	  m->ave_ideal_required_distance_trial[averageID] 
	    = m->ave_ideal_required_distance[averageID];  
	  
	  m->ave_efficiency_time_trial[averageID]         
	    = calcuAve(ave_step, 
		       m->ave_efficiency_time_trial[averageID],
		       m->ave_efficiency_time[averageID]);
	  
	  m->ave_efficiency_distance_trial[averageID]     
	    = calcuAve(ave_step, 
		       m->ave_efficiency_distance_trial[averageID], 
		       m->ave_efficiency_distance[averageID]);          
	  
	  m->ave_present_efficiency_time_trial[averageID]      
	    = calcuAve(ave_step, 
		       m->ave_present_efficiency_time_trial[averageID], 
		       m->ave_present_efficiency_time[averageID]);
	  
	  m->ave_present_efficiency_distance_trial[averageID] 
	    = calcuAve(ave_step,
		       m->ave_present_efficiency_distance_trial[averageID],
		       m->ave_present_efficiency_distance[averageID]);
	  
	  m->ave_variance_efficiency_time_trial[averageID] 
	    = calcuAve(ave_step,
		       m->ave_variance_efficiency_time_trial[averageID],
		       m->variance_efficiency_time[averageID]);
	  */

	}

      }
    }
  }

  
  //-- Average Gain and Velocity of All Objects
    
  //-- Initialize of Macro Parameter  
  int    sum_num_stop[NUM_AVERAGE];
  double sum_gain[NUM_AVERAGE];
  double sum_velocity[NUM_AVERAGE];
  
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){    
    sum_num_stop[averageID] = 0;   
    sum_gain[averageID]     = 0;   
    sum_velocity[averageID] = 0; 
  }


  //-- Calculate Sum of Objecst Parameter 
  for(int objID = 0; objID < o->num_move; objID++){

    if(o->move[objID].driving_status == STANDBY || 
       o->move[objID].driving_status == WAITING || 
       o->move[objID].driving_status == ARRIVAL){
      continue;
    }

    for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){


      if( (averageID == o->move[objID].navi_type) || ( averageID == ALL_AVERAGE) ){
      
	//--
	if(o->move[objID].gain == 0){
	  sum_num_stop[averageID]++;
	}

	//--
	sum_gain[averageID]     += o->move[objID].gain;
	sum_velocity[averageID] += o->move[objID].velocity;
	
	//printf("objID:%d block:%d o->move[objID].gain:%f\n",objID, 
	//o->move[objID].block, o->move[objID].gain);
      }
      
    }
  }



  //-- Calculate Average based on Sum of Objecst Parameter 
  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){

    //num_move = o->num_navi_type[averageID];

    if(o->num_driving[averageID] == 0){
      num_move = 1;
    }
    else{
      num_move = o->num_driving[averageID];
    }


    if( (averageID ==  ALL_AVERAGE) || (num_move > 0) ){  
      
      m->ave_num_stop[averageID]       = (double)sum_num_stop[averageID]/num_move;
      m->ave_gain[averageID]           = sum_gain[averageID]/num_move;   
      m->ave_velocity[averageID]       = sum_velocity[averageID]/num_move;   
      
      //if(step > 500){	
      //int ave_step = step - 501;

      int ave_step = step-1;
	
	m->ave_num_stop_trial[averageID]             
	  = calcuAve(step, m->ave_num_stop_trial[averageID], m->ave_num_stop[averageID]);
	
	m->ave_gain_trial[averageID]     
	  = calcuAve(ave_step, m->ave_gain_trial[averageID], m->ave_gain[averageID]);   
	
	m->ave_velocity_trial[averageID] 
	  = calcuAve(ave_step, m->ave_velocity_trial[averageID], m->ave_velocity[averageID]);  
	
	//}
    }
  }



}

//--------------------------------------------------------------------------//

void 
Monitor::outputMacroParameter_step(void)
{


  /*
  for(int nodeID1 = 0; nodeID1 < g->num_node; nodeID1++){
    for(int nodeID2 = 0; nodeID2 < g->num_node; nodeID2++){
      
      if( (nodeID1==0 && nodeID2 ==5)||(nodeID1==5 && nodeID2 ==0)||
	  (nodeID1==2 && nodeID2 ==3)||(nodeID1==3 && nodeID2 ==2) ){
	
	//printf("g->ExpectedTravelTime[%d][%d]:%f\n",nodeID1,nodeID2,g->ExpectedTravelTime[nodeID1][nodeID2]);
	//printf("ArcWeight[%d][%d]            :%f\n",nodeID1,nodeID2,ArcWeight[nodeID1][nodeID2]);
	//printf("g->DeclaredPlan[%d][%d]      :%f\n",nodeID1,nodeID2,g->DeclaredPlan[nodeID1][nodeID2]);
	
      }
    }
  }
  */


  //-- Output Result in One Step to Display

  printf("step:%3d   ", c->step);  
  printf("obj:%4d    ", o->num_move);     
  printf("MAX:%4d\n",o->Max_Obj);

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
   
    if( o->num_navi_type[averageID] != 0){
      
      printf("obj:%4d ", o->num_navi_type[averageID]);     
      printf("wait:%4d ",o->num_waiting[averageID]);
      printf("drive:%4d ",o->num_driving[averageID]);
      printf("arrival:%4d ",o->num_arrival[averageID]); 
      
      printf("gain:%5.1f ", m->ave_gain[averageID]);   
      printf("stop:%.2f ", m->ave_num_stop[averageID]);
      printf("vel:%2.2f ", m->ave_velocity[averageID]);  
      printf("arrival:%1.4f   ", m->ave_num_arrival[averageID]);  
      
      //printf("time:%5.1f ", m->ave_required_time[averageID]);    
      //printf("%5.1f ", m->ave_present_required_time[averageID]);    
      //printf("%5.1f ", m->ave_ideal_required_time[averageID]);  
      
      //printf("distance:%5.1f ", m->ave_required_distance[averageID]);
      //printf("%5.1f\t", m->ave_present_required_distance[averageID]);   
      //printf("%5.1f\t", m->ave_ideal_required_distance[averageID]);  
      
      //printf("efficiency:");

      printf("time:%5.2f ", m->ave_efficiency_time[averageID] );   
      printf("var:%5.3f ", m->variance_efficiency_time[averageID] );
      
      
      //printf("distance:%5.2f ", m->ave_efficiency_distance[averageID] ); 
      //printf("%5.2f ", m->ave_present_efficiency_time[averageID]); 
      //printf("%5.2f ", m->ave_present_efficiency_distance[averageID]); 
      
      printf("\n");  
      
      }    
  }
  
  printf("\n"); 


  //-- Output Result in One Step to File
  
  fprintf(fp_output_step,"%d\t", c->step);   
  fprintf(fp_output_step,"%d\t", o->num_move);

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
   
    //if( o->num_navi_type[averageID] != 0){

    fprintf(fp_output_step,"%d\t",o->num_navi_type[averageID]);      
    fprintf(fp_output_step,"%d\t",o->num_driving[averageID]);   
    fprintf(fp_output_step,"%d\t",o->num_waiting[averageID]);
    fprintf(fp_output_step,"%d\t",o->num_arrival[averageID]); 
    
    fprintf(fp_output_step,"%f\t", m->ave_gain[averageID]);      
    fprintf(fp_output_step,"%f\t", m->ave_num_stop[averageID]);
    fprintf(fp_output_step,"%f\t", m->ave_velocity[averageID]);  
    
    fprintf(fp_output_step,"%f\t", m->ave_required_time[averageID]);    
    fprintf(fp_output_step,"%f\t", m->ave_ideal_required_time[averageID]);  
    
    fprintf(fp_output_step,"%f\t", m->ave_required_distance[averageID]);  
    fprintf(fp_output_step,"%f\t", m->ave_ideal_required_distance[averageID]);  
    
    fprintf(fp_output_step,"%f\t", m->ave_efficiency_time[averageID] );       
    fprintf(fp_output_step,"%f\t", m->variance_efficiency_time[averageID] );
    
    fprintf(fp_output_step,"%f\t", m->ave_efficiency_distance[averageID] ); 
    
    
    //fprintf(fp_output_step,"%f\t", m->ave_num_arrival[averageID]);  
    //fprintf(fp_output_step,"%f\t", m->ave_present_required_time[averageID]);
    //fprintf(fp_output_step,"%f\t", m->ave_present_required_distance[averageID]);
    //fprintf(fp_output_step,"%f\t", m->ave_present_efficiency_time[averageID]);  
    //fprintf(fp_output_step,"%f\t", m->ave_present_efficiency_distance[averageID]);    
    
    //}
  }
  fprintf(fp_output_step,"\n");
  


  //-- Output Result of Density in One Step to File

  /*
  for(int arcID = 0; arcID < g->num_arc; arcID++){
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      for(int blockID = 0; blockID < g->arc[arcID].num_block; blockID++){	
      
	fprintf(fp_output_K_step,"%f\t", g->arc[arcID].block[sideID][blockID].K);

      }
    }
  }
  
  fprintf(fp_output_K_step,"\n");
  */

}

//--------------------------------------------------------------------------//

void 
Monitor::outputMacroParameter_trial(void)
{

  //-- Output Result in One Trial to Display

  printf("step:%3d ", c->step);  
  printf("obj:%4d\n", o->num_move);

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){
   
    if( o->num_navi_type[averageID] != 0){

      printf("obj:%4d\t", o->num_navi_type[averageID]);
      printf("gain:%5.2f ", m->ave_gain_trial[averageID]);      
      printf("stop:%5.3f\t", m->ave_num_stop_trial[averageID]);
      printf("vel:%5.3f ", m->ave_velocity_trial[averageID]);  
      printf("arrival:%5.4f ", m->ave_num_arrival_trial[averageID]);  
      
      printf("time:%5.1f ", m->ave_required_time_trial[averageID]);    
      printf("%5.1f ", m->ave_ideal_required_time_trial[averageID]);  

      printf("distance:%5.1f ", m->ave_required_distance_trial[averageID]);
      printf("%5.1f\t", m->ave_ideal_required_distance_trial[averageID]);  
      
      printf("efficiency:");
      printf("time:%5.3f\t", m->ave_efficiency_time_trial[averageID]);   
      printf("distance:%5.3f\t", m->ave_efficiency_distance_trial[averageID]);



      //printf("%5.1f ", m->ave_present_required_time_trial[averageID]);    
      //printf("%5.1f\t", m->ave_present_required_distance_trial[averageID]);
      //printf("%5.1f\t", m->ave_present_efficiency_time_trial[averageID]);  
      // printf("%5.1f\t", m->ave_present_efficiency_distance_trial[averageID]);
      

      printf("\n");  
    }
  }  
  printf("\n");  



  //-- Output Result in One Trial to File

  for(int averageID = 0; averageID < NUM_AVERAGE; averageID++){

    fprintf(fp_output_trial,"%d\t", c->step);   
    fprintf(fp_output_trial,"%d\t", o->num_move);

    
    fprintf(fp_output_trial,"%d\t", o->num_navi_type[averageID]);
    fprintf(fp_output_trial,"%f\t", m->ave_gain_trial[averageID]);    
    fprintf(fp_output_trial,"%f\t", m->ave_num_stop_trial[averageID]);
    fprintf(fp_output_trial,"%f\t", m->ave_velocity_trial[averageID]);  
    fprintf(fp_output_trial,"%f\t", m->ave_num_arrival_trial[averageID]);  
    
    fprintf(fp_output_trial,"%f\t", m->ave_required_time_trial[averageID]);  
    fprintf(fp_output_trial,"%f\t", m->ave_ideal_required_time[averageID]);  
    
    fprintf(fp_output_trial,"%f\t", m->ave_required_distance_trial[averageID]);  
    fprintf(fp_output_trial,"%f\t", m->ave_ideal_required_distance[averageID]);
    
    fprintf(fp_output_trial,"%f\t", m->ave_efficiency_time_trial[averageID]);   
    fprintf(fp_output_trial,"%f\t", m->ave_efficiency_distance_trial[averageID]);
    
    fprintf(fp_output_trial,"%f\t", m->ave_variance_efficiency_time_trial[averageID]);
    
   
    //fprintf(fp_output_trial,"%f\t", m->ave_present_required_time_trial[averageID]);  
    //fprintf(fp_output_trial,"%f\t", m->ave_present_required_distance_trial[averageID]);
    //fprintf(fp_output_trial,"%f\t", m->ave_present_efficiency_time_trial[averageID]);  
    //fprintf(fp_output_trial,"%f\t", m->ave_present_efficiency_distance_trial[averageID]);    
  }

  fprintf(fp_output_trial,"\n");



  //-- Output Result of Density in One Trial to File

  for(int arcID = 0; arcID < g->num_arc; arcID++){
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      for(int blockID = 0; blockID < g->arc[arcID].num_block; blockID++){	
      
	fprintf(fp_output_K_trial,"%f\t", g->arc[arcID].block[sideID][blockID].ave_K);

      }
    }
  }
      
  fprintf(fp_output_K_trial,"\n");

}

//--------------------------------------------------------------------------//

void 
Monitor::outputMicroParameter_trial(void){


  for(int objID = 0; objID < o->num_move; objID++){

    fprintf(fp_output_D_step,"%d\t",objID);
    fprintf(fp_output_D_step,"%d\t",o->move[objID].navi_type);    

    fprintf(fp_output_D_step,"%d\t",o->move[objID].origin_arc);      
    fprintf(fp_output_D_step,"%d\t",o->move[objID].origin_side);       
    fprintf(fp_output_D_step,"%d\t",o->move[objID].origin_block);     

    fprintf(fp_output_D_step,"%d\t",o->move[objID].destination_arc);   
    fprintf(fp_output_D_step,"%d\t",o->move[objID].destination_side);  
    fprintf(fp_output_D_step,"%d\t",o->move[objID].destination_block); 
    
    fprintf(fp_output_D_step,"%d\t",o->move[objID].generation_step);   
    fprintf(fp_output_D_step,"%d\t",o->move[objID].arrival_step);     
    
    fprintf(fp_output_D_step,"999\t"); 

    fprintf(fp_output_D_step,"%d\t",o->move[objID].required_time[0]);     
    fprintf(fp_output_D_step,"%f\t",o->move[objID].ideal_required_time[OUTWARD]);

    fprintf(fp_output_D_step,"%f\t",o->move[objID].required_distance[0]);      
    fprintf(fp_output_D_step,"%f\t",o->move[objID].ideal_required_distance[OUTWARD]);

    fprintf(fp_output_D_step,"%f\t",o->move[objID].efficiency_time);                   
    fprintf(fp_output_D_step,"%f\t",o->move[objID].efficiency_distance);               


    fprintf(fp_output_D_step,"9999\t");     

    fprintf(fp_output_D_step,"%d\t",o->move[objID].ideal_plan_length[0]);
  
    for(int nodeID = 0; nodeID < o->move[objID].ideal_plan_length[0]; nodeID++){
      
      fprintf(fp_output_D_step,"%d\t",o->move[objID].ideal_plan[0][nodeID]); 

    }

    fprintf(fp_output_D_step,"99999\t");  

    fprintf(fp_output_D_step,"%d\t",o->move[objID].actual_plan_length);
  
    for(int nodeID = 0; nodeID < o->move[objID].actual_plan_length; nodeID++){
      
      fprintf(fp_output_D_step,"%d\t",o->move[objID].actual_plan[nodeID]); 

    }

    fprintf(fp_output_D_step,"\n");

  }

}

//--------------------------------------------------------------------------//

double 
Monitor::calcuAve(int current_step, double old_ave, int new_factor)
{

  double new_ave;

  new_ave = ( old_ave*current_step + (double)new_factor)/(current_step + 1);

  return new_ave;
  
}

double 
Monitor::calcuAve(int current_step, double old_ave, double new_factor)
{

  double new_ave;

  new_ave = ( old_ave*current_step + new_factor)/(current_step+1);

  return new_ave;
  
}

//--------------------------------------------------------------------------//

void 
Monitor::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;  
}

void 
Monitor::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

void 
Monitor::getCtlInfo(struct ITERATION_CONTROL *ext_ctl)
{ 
  //printf("in :getCtlInfo.\n");
  c = ext_ctl;  
}

void 
Monitor::getMacroInfo(struct MACRO_PARAMETER *ext_macro)	
{ 
  //printf("in :getMacroInfo.\n");
  m = ext_macro;  
}

//--------------------------------------------------------------------------//

