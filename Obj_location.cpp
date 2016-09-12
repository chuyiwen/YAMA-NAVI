/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Obj_location.h"


 
//////////////////////////
//
// ObjLocaiton methods


//
//
//

//--------------------------------------------------------------------------//

ObjLocation::ObjLocation(void)
{ 
}

ObjLocation::~ObjLocation(void)
{ 
}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeObjOD(){

  //-- Initialize Origin and Destination

  for(int objID = 0; objID < o->Max_Obj; objID++){

    o->move[objID].driving_status = STANDBY;

    //-- Random Origin and Destination for Any Map 
    OD_random(objID);
    

    //-- Simple Structure 
    //OD_simple(objID);
    
    //-- Lattice Structure 
    //OD_lattice(objID);
    
    //-- Radial and Ring Structure 
    //  OD_radialring(objID);
    
  }


}

//--------------------------------------------------------------------------//

void 
ObjLocation::OD_random(int objID){

  //-- Decide Origin and Destination in Any Map
  //-- First, arc, side, block of "DESTINATION" are determined rondomly.

  //-- Destination 
  int d_arcID;
  int d_sideID;
  int d_blockID;

  //-- Origin
  int arcID;
  int sideID;
  int blockID;
  
  double k;   
  double k_s; 
  double dL;  
  
  int num_generated;
  
  //-- Second, arc, side, block of "ORIGIN" are determined   
  //-- to avoid the same arc as destination.


  //printf("g->num_arc = %d\n",g->num_arc);

  do{

    //-- Decision of Arc, Side, Block of Destination
    d_arcID   = rand()%g->num_arc; 
    d_sideID  = rand()%NUM_SIDE;

    //
    if(g->arc[d_arcID].num_block <= 2){
      d_blockID = 0; 
      arcID     = d_arcID; 
    }
    else{
      d_blockID =  1+rand()%(g->arc[d_arcID].num_block-2);//3;//1+rand()%(g->arc[d_arcID].num_block-2);
    }
   
    //printf("d_arcID=%d\n",d_arcID);   
    //printf("d_sideID=%d\n",d_sideID);
    //printf("d_blockD=%d\n",d_blockID);

    
    //-- Decision of Arc, Side, Block of Origin
    arcID   = rand()%g->num_arc; //1;//rand()%g->num_arc;    
    sideID  = rand()%NUM_SIDE;   //1;//rand()%NUM_SIDE;    


    //printf("g->arc[arcID].num_block =%d\n",g->arc[arcID].num_block);
    

    //Origin and destination avoid the top and last blocks.
    if(g->arc[arcID].num_block <= 2){
      blockID = 0;
      arcID   = d_arcID; 
    }
    else{ 
      //
      blockID = 1+rand()%(g->arc[arcID].num_block-2);
      //blockID = 2;
    }    

    //printf("arcID=%d\n",arcID);   
    //printf("sideID=%d\n",sideID);
    //printf("blockID=%d\n",blockID);

    if(d_blockID == 0 || d_blockID == g->arc[d_arcID].num_block-1){
      d_arcID = arcID;
    }
    if(blockID == 0 || blockID == g->arc[arcID].num_block-1){
      d_arcID = arcID;
    }


    num_generated = g->arc[arcID].block[sideID][blockID].block_num_generated;

    //-- Prohibitation that origin and destionation in the same arc.    
    //-- Block_num_generated has upper bound. 

  }while( d_arcID == arcID || num_generated >= MAX_NUM_WAITING);
 


  //-- Initialize Parameter of Block 

  g->arc[arcID].block[sideID][blockID].block_num_generated++;  

  
  /*
  dL      = g->arc[arcID].block[sideID][blockID].block_length;
  k       = (double)(g->arc[arcID].block[sideID][blockID].block_num_move +1)/dL ;
  k_s     = g->arc[arcID].block[sideID][blockID].K_saturation;
   

  if( k < k_s){
    //-- NOT JAM

    int block_num_moving = g->arc[arcID].block[sideID][blockID].block_num_move;
    
    g->arc[arcID].block[sideID][blockID].block_move[block_num_moving] = objID;
    g->arc[arcID].block[sideID][blockID].block_num_move++;  
    g->arc[arcID].block[sideID][blockID].K = (double)(block_num_moving+1)/dL;

    //o->move[objID].driving_status = DRIVING;
  } 
  else{
    //-- JAM
    
    int block_num_waiting = g->arc[arcID].block[sideID][blockID].block_num_wait;
    
    g->arc[arcID].block[sideID][blockID].block_wait[block_num_waiting] = objID;
    g->arc[arcID].block[sideID][blockID].block_num_wait++;  

    //o->move[objID].driving_status = WAITING;
  }
  */

  //-- Initialize Parameter of Object  

  initializeObjODParameter(objID, arcID, sideID, blockID, d_arcID, d_sideID, d_blockID);

}

//--------------------------------------------------------------------------//

void 
ObjLocation::OD_simple(int objID){

  //-- Decide Origin and Destination in Simple Structure 
  //-- First, arc, side, block of "DESTINATION" are determined rondomly.

  int d_arcID   = 8;  
  int d_sideID  = rand()%NUM_SIDE;
  int d_blockID = 1+rand()%(g->arc[d_arcID].num_block-2);

  int arcID;
  int sideID;
  int blockID;
  
  double k;   
  double k_s; 
  double dL;  
  
  
  //-- Second, arc, side, block of "ORIGIN" are determined   
  //-- to avoid the same arc as destination.

  do{
      
    arcID = 13;
    sideID  = rand()%NUM_SIDE;
    blockID = 1+rand()%(g->arc[arcID].num_block-2);
    

    int temp = rand()%5;

    if(temp== 0){
      arcID = 11;
      sideID= 1;	
      blockID = 1+rand()%(g->arc[arcID].num_block-1);
    }
    if(temp== 1){
      arcID = 12;
      sideID= 1;	
      blockID = 1+rand()%(g->arc[arcID].num_block-1);
    }
    if(temp== 2){  
      arcID = 13;	
      blockID = 1+rand()%(g->arc[arcID].num_block-1);
    }
    if(temp== 3){
      arcID = 14;
      sideID= 0;	
      blockID = 1+rand()%(g->arc[arcID].num_block-1);
    }
    if(temp== 5){
      arcID = 15;
      sideID= 0;	
      blockID = 1+rand()%(g->arc[arcID].num_block-1);
    }
    
    k       = g->arc[arcID].block[sideID][blockID].K;
    k_s     = g->arc[arcID].block[sideID][blockID].K_saturation;
    dL      = g->arc[arcID].block[sideID][blockID].block_length;
    
  }while( d_arcID == arcID || (k*dL + 1.0)/dL >  k_s );
 

  //-- Initialize Number of Object in Block 
    
  int block_num_move= g->arc[arcID].block[sideID][blockID].block_num_move;
  
  g->arc[arcID].block[sideID][blockID].block_move[block_num_move] = objID;
  g->arc[arcID].block[sideID][blockID].block_num_move++;


  //-- Initialize Parameter of Object  
  initializeObjODParameter(objID, arcID, sideID, blockID, d_arcID, d_sideID, d_blockID);

}

void 
ObjLocation::OD_lattice(int objID){


  //-- Decide Origin and Destination in Lattice Structure 
  
  //-- Setting of lattice 2-2
  //int num_d         = 8;
  //int num_arc       = 11;
  //int d_candidate[] = {0,1, 2,4, 7,9, 10,11}; 
  
  //-- Setting of lattice 3-3
  //int num_d         = 12;
  //int num_arc        = 23;
  //int d_candidate[] = {0,1,2, 4,6, 8,13, 12,20, 21,22,23}; 
  
  //-- Setting of lattice 4-4
  //
  int num_d;//         = 16;
  //
  //int num_arc       = 39;
  //
 int d_candidate[] = {0,1,2,3,4,8,13,17,22,26,31,35,36,37,38,39}; 
  

  int d_arcID;
  int d_sideID;
  int d_blockID;
  int d_ID;

  int arcID;
  int sideID;
  int blockID;
  
  double k;   
  double k_s; 
  double dL;  


  do{

    //-- First, arc, side, block of "DESTINATION" are determined rondomly.

    //d_ID            = rand()%num_d;
    d_arcID         = rand()%g->num_arc;//d_candidate[d_ID];
    d_sideID        = rand()%NUM_SIDE;
    d_blockID       = 1+rand()%(g->arc[d_arcID].num_block-2);

 
 
    //-- Second, arc, side, block of "ORIGIN" are determined   
    //-- to avoid the same arc as destination.
    arcID   = rand()%g->num_arc;//num_arc - d_arcID;
    sideID  = rand()%NUM_SIDE;    
    blockID = 1+rand()%(g->arc[arcID].num_block-2);    
    
    k       = g->arc[arcID].block[sideID][blockID].K;
    k_s     = g->arc[arcID].block[sideID][blockID].K_saturation;
    dL      = g->arc[arcID].block[sideID][blockID].block_length;
    
    //printf("loop d: %d o:%d\n",d_arcID,arcID);
    //printf("dL:%f, k*dL + 1.0)/dL :%f, k_s:%f\n",dL, (k*dL + 1.0)/dL, k_s);
    
  }while( d_arcID == arcID || (k*dL + 1.0)/dL >  k_s );
  


  //-- Initialize Number of Object in Block 
    
  int block_num_move= g->arc[arcID].block[sideID][blockID].block_num_move;
  
  g->arc[arcID].block[sideID][blockID].block_move[block_num_move] = objID;
  g->arc[arcID].block[sideID][blockID].block_num_move++;


  //-- Initialize Parameter of Object   

  initializeObjODParameter(objID, arcID, sideID, blockID, d_arcID, d_sideID, d_blockID);
  
}

void 
ObjLocation::OD_radialring(int objID){



  //-- Decide Origin and Destination in Radial and Ring Structure
  //-- First, arc, side, block of "DESTINATION" are determined rondomly.

  int d_arcID;
  int d_sideID;
  int d_blockID;

  int arcID;
  int sideID;
  int blockID;
  
  double k;   
  double k_s; 
  double dL;  
  
  
  //-- Second, arc, side, block of "ORIGIN" are determined   
  //-- to avoid the same arc as destination.


  //printf("g->num_arc = %d\n",g->num_arc);

  do{

    d_arcID   = rand()%g->num_arc;  //= 48 + rand()%8;
    d_sideID  = rand()%NUM_SIDE;

    //
    if(g->arc[d_arcID].num_block <= 2){
      d_blockID = 0; 
      arcID   = d_arcID; 
    }
    else{
      d_blockID = 1+rand()%(g->arc[d_arcID].num_block-2);
    }
   
    //d_blockID = 1+rand()%(g->arc[d_arcID].num_block);
    
    //printf("d_arcID=%d\n",d_arcID);   
    //printf("d_sideID=%d\n",d_sideID);
    //printf("d_blockD=%d\n",d_blockID);


    arcID   = rand()%g->num_arc;    //=((d_arcID - 48) + 4)%8  + 48; 
    sideID  = rand()%NUM_SIDE;    

    //printf("g->arc[arcID].num_block =%d\n",g->arc[arcID].num_block);
       
    if(g->arc[arcID].num_block <= 2){      
      blockID = 0;
      arcID   = d_arcID; 
    }
    else{ 
      blockID = 1+rand()%(g->arc[arcID].num_block-2);
    }    

    //blockID = 1+rand()%(g->arc[arcID].num_block-2); 
    //blockID =   rand()%(g->arc[arcID].num_block);

    //printf("arcID=%d\n",arcID);   
    //printf("sideID=%d\n",sideID);
    //printf("blockID=%d\n",blockID);

    
    k       = g->arc[arcID].block[sideID][blockID].K;
    k_s     = g->arc[arcID].block[sideID][blockID].K_saturation;
    dL      = g->arc[arcID].block[sideID][blockID].block_length;
   

    if(d_blockID == 0 || d_blockID == g->arc[d_arcID].num_block-1){
      d_arcID = arcID;
    }

    if(blockID == 0 || blockID == g->arc[arcID].num_block-1){
      d_arcID = arcID;
    }
 
  }while( d_arcID == arcID || (k*dL + 1.0)/dL >  k_s );
 

  //-- Initialize Number of Object in Block 
    
  int block_num_move= g->arc[arcID].block[sideID][blockID].block_num_move;
  
  g->arc[arcID].block[sideID][blockID].block_move[block_num_move] = objID;
  g->arc[arcID].block[sideID][blockID].block_num_move++;
  
  
  //-- Initialize Parameter of Object  

  initializeObjODParameter(objID, arcID, sideID, blockID, d_arcID, d_sideID, d_blockID);

}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeObjODParameter(
int objID, 
int s_arcID, int s_sideID, int s_blockID,
int d_arcID, int d_sideID, int d_blockID)
{

  o->move[objID].arc              = s_arcID;
  o->move[objID].side             = s_sideID;   
  o->move[objID].block            = s_blockID;
  o->move[objID].end              = g->arc[s_arcID].block_end_node[s_sideID];
  o->move[objID].start            = g->arc[s_arcID].block_start_node[s_sideID];
  
  o->move[objID].origin_arc       = s_arcID;
  o->move[objID].origin_side      = s_sideID;
  o->move[objID].origin_block     = s_blockID;
  
  o->move[objID].destination_arc  = d_arcID;
  o->move[objID].destination_side = d_sideID; 
  o->move[objID].destination_block= d_blockID;


  //printf("o->move[objID].arc  %d\n",o->move[objID].arc);   
  //printf("o->move[objID].side %d\n",o->move[objID].side);    
  //printf("o->move[objID].block %d\n",o->move[objID].block);  
  //printf("o->move[objID].arc  %d\n",o->move[objID].destination_arc);   
  //printf("o->move[objID].side %d\n",o->move[objID].destination_side);    
  //printf("o->move[objID].block %d\n\n",o->move[objID].destination_block);  

}

//--------------------------------------------------------------------------//

void 
ObjLocation::generateObj(){

  od.getGeoInfo(g);
  od.getObjInfo(o); 
  od.getCtlInfo(c);  


  //-- Generate New Object
  
  //-- Number of Objects Generated at Every Step
  //int    num_generate = 20; //number of objects generated at every step
  //printf("\nNow there are %5d moving objects.\n\n",o->num_move );
  


  //-- Initialize Number of Navi Type 

  if( o->num_move +  o->num_generation > o->Max_Obj){
    o->num_generation = o->Max_Obj - o->num_move;
  }

  initializeNumNaviType(o->num_generation);
  


  //-- Initialize Generated Object  
  if( o->num_move +  o->num_generation <= o->Max_Obj){

    //-- Initialize Parameters of Object  
    for(int generate_objID = 0; generate_objID < o->num_generation; generate_objID++){

      //o->move[objID].driving_status = DRIVING;
     
      int objID         = o->num_move;
      
      o->move[objID].no = objID;


      //-- Initialize Origin and Destination
      //initializeObjOD(objID);


      //-- Initialize Navigation Type 
      initializeObjNaviType(objID, o->num_generation);


      //-- Initialize Parameters 
      int arcID   = o->move[objID].arc;
      int sideID  = o->move[objID].side;
      int blockID = o->move[objID].block ;

      initializeObjParameter(objID, arcID, sideID, blockID);


      //-- Make Travel Plan 
      od.initializePlan(objID);


      //-- Increment of Number of Objects
      o->num_move++;
    }
    
  }
  
  

  //-- Re-initialize Arraiving Object  
  /*
  for(int arriving_objID = 0; arriving_objID < 0;arriving_objID++){
    //for(int arriving_objID = 0; arriving_objID < 0; o->num_move; arriving_objID++){
    
    if(o->move[arriving_objID].driving_status == ARRIVAL){

      //-- Initialize Origin and Destination
      initializeObjOD(arriving_objID);

      //-- Initialize Parameters 
      int arcID   = o->move[arriving_objID].arc;
      int sideID  = o->move[arriving_objID].side;
      int blockID = o->move[arriving_objID].block ;

      initializeObjParameter(arriving_objID, arcID, sideID, blockID);

      //-- Make Travel Plan 
      od.initializePlan(arriving_objID);
    }
    }*/


  //-- Check Nuber of Objects with Counting Objects on Map      
  /*
  int count_obj = 0;

  for(int arcID = 0; arcID < g->num_arc; arcID++){    
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      for(int blockID = 0; blockID < g->arc[arcID].num_block; blockID++){
	count_obj += g->arc[arcID].block[sideID][blockID].block_num_move;
      }
    }
  }

  if(count_obj != o->num_move){

    printf("Error! at generateObj() in Obj_location.cpp. \n");  
    printf("Number of Object is reduced. \n");

    exit(0);
  }
  */

}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeNumNaviType(int num_generate){


  double sum_ratio    = o->ratio_ShortestDistance 
                      + o->ratio_ReplanningInOrigin
                      + o->ratio_SuccessiveReplanning 
                      + o->ratio_CongestionAvoidance 
                      + o->ratio_DeclaringPath;

  int num_obj_generate[NAVI_TYPE];
  
  num_obj_generate[0] = (int)(num_generate * o->ratio_ShortestDistance/sum_ratio); 
  num_obj_generate[1] = (int)(num_generate * o->ratio_ReplanningInOrigin/sum_ratio);      
  num_obj_generate[2] = (int)(num_generate * o->ratio_SuccessiveReplanning/sum_ratio);  
  num_obj_generate[3] = (int)(num_generate * o->ratio_CongestionAvoidance/sum_ratio);    
  num_obj_generate[4] = (int)(num_generate * o->ratio_DeclaringPath/sum_ratio);   

  
  double num_obj_decimal[NAVI_TYPE];

  num_obj_decimal[0]  = ((double)num_generate * o->ratio_ShortestDistance/sum_ratio) 
                        - (double)num_obj_generate[0];
  num_obj_decimal[1]  = ((double)num_generate * o->ratio_ReplanningInOrigin/sum_ratio) 
                        - (double)num_obj_generate[1];
  num_obj_decimal[2]  = ((double)num_generate * o->ratio_SuccessiveReplanning/sum_ratio) 
                        - (double)num_obj_generate[2];
  num_obj_decimal[3]  = ((double)num_generate * o->ratio_CongestionAvoidance/sum_ratio) 
                        - (double)num_obj_generate[3];
  num_obj_decimal[4]  = ((double)num_generate * o->ratio_DeclaringPath/sum_ratio) 
                        - (double)num_obj_generate[4];
 

  int sum_num         = num_obj_generate[0] 
                      + num_obj_generate[1]
                      + num_obj_generate[2]
                      + num_obj_generate[3]
                      + num_obj_generate[4];
  

  
  //-- Arrengement of Number of Objects by Wheel Selection 
  //-- Addition of ONE Object to Navi Type with Decimal

  double sum_decimal     = 0;

  for(int navi_typeID = 0; navi_typeID < NAVI_TYPE; navi_typeID++){
    sum_decimal += num_obj_decimal[navi_typeID];
    //printf("decimal %d %f\n",navi_typeID,num_obj_decimal[navi_typeID]);
  }

  double wheel_threshold = sum_decimal*(double)((1+rand())%100001)/(100000.0);
  double sum_wheel_ratio = 0;
  int    counter         = 0; 

  //printf("wheel_threshold %f\n",wheel_threshold);
  

  while(sum_num != num_generate){
    
    counter = 0;
     
    for(int navi_typeID = 0; navi_typeID < NAVI_TYPE; navi_typeID++){
      
      sum_wheel_ratio += num_obj_decimal[counter];
      
      if(sum_wheel_ratio > wheel_threshold ){
	break;
      }
      counter++;	
    }

    if(sum_num < num_generate){
      //printf("plus\n");
      num_obj_generate[counter]++;
    }
    
    if(sum_num > num_generate){
      //printf("----\n");
      num_obj_generate[counter]--;
    }
    
    sum_num     = num_obj_generate[0] 
	        + num_obj_generate[1]
                + num_obj_generate[2]
                + num_obj_generate[3]
                + num_obj_generate[4];    
  }
  


  //printf("num_obj_generate[0] %d\n",num_obj_generate[0]);    
  //printf("num_obj_generate[1] %d\n",num_obj_generate[1]);  
  //printf("num_obj_generate[2] %d\n",num_obj_generate[2]);    
  //printf("num_obj_generate[3] %d\n",num_obj_generate[3]);  
  //printf("num_obj_generate[4] %d\n",num_obj_generate[4]);
  //printf("counter %d\n",counter); 
  

  o->generate_num_SD  = num_obj_generate[0];
  o->generate_num_RO  = num_obj_generate[1];
  o->generate_num_SR  = num_obj_generate[2];
  o->generate_num_CA  = num_obj_generate[3];
  o->generate_num_DP  = num_obj_generate[4];
  

  //-- Check Sum of Object generated in this step 

  sum_num         = num_obj_generate[0]
                  + num_obj_generate[1]
                  + num_obj_generate[2]
                  + num_obj_generate[3]
                  + num_obj_generate[4];

  if( num_generate != sum_num){
    printf("Error of Number of Navi Type at initializeObjNaviType() in Obj_location.cpp\n");
    printf("Number of Shortest Distance\t %d\n",o->generate_num_SD);
    printf("Number of Replanning In Origin\t %d\n",o->generate_num_RO);
    printf("Number of Successive Replanning\t %d\n",o->generate_num_SR);
    printf("Number of Congestion Avoidance\t %d\n",o->generate_num_CA);   
    printf("Number of Declaring Path\t %d\n",o->generate_num_DP);
    printf("Number of Moving Objects\t %d\n\n",num_generate);
    exit(1);
  }
  
}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeObjNaviType(int objID, int num_generate){

  

  if( o->generate_num_SD > 0 ){
    
    o->move[objID].navi_type = SHORTEST_DISTANCE;
    
    o->present_num_ShortestDistance++;
    o->generate_num_SD--;
  } 
  else if( o->generate_num_RO > 0 ){
    
    o->move[objID].navi_type = REPLANNING_ORIGIN;
    
    o->present_num_ReplanningInOrigin++; 
    o->generate_num_RO--;
  }
  else if( o->generate_num_SR > 0 ){
    
    o->move[objID].navi_type = SUCCESSIVE_REPLANNING;
    
    o->present_num_SuccessiveReplanning++;
    o->generate_num_SR--;
  }
  else if( o->generate_num_CA > 0 ){
    
    o->move[objID].navi_type = CONGESTION_AVOIDANCE;
    
    o->present_num_CongestionAvoidance++;
    o->generate_num_CA--;
  }      
  else if(  o->generate_num_DP > 0 ){
    
    o->move[objID].navi_type = DECLARING_PATH;
    
    o->present_num_DeclaringPath++;
    o->generate_num_DP--;
  }
  
  //printf("num_obj_generate[0] %d\n",o->present_num_ShortestDistance);    
  //printf("num_obj_generate[1] %d\n",o->present_num_ReplanningInOrigin);  
  //printf("num_obj_generate[2] %d\n",o->present_num_SuccessiveReplanning);    
  //printf("num_obj_generate[3] %d\n",o->present_num_CongestionAvoidance);  
  //printf("num_obj_generate[4] %d\n",o->present_num_DeclaringPath);


  
}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeObjParameter(int objID, int arcID, int sideID, int blockID){

  int    block_num_move = g->arc[arcID].block[sideID][blockID].block_num_move; 
  double dL   = g->arc[arcID].block[sideID][blockID].block_length;
  double k    = (double)(block_num_move)/dL ;
  double k_s  = g->arc[arcID].block[sideID][blockID].K_saturation;
  
  //if(k>0){
  //  printf("block_num_move %d\n",block_num_move);
  //}


  if( k < k_s){
    setObjParameter(NOT_JAM, objID, arcID, sideID, blockID);
  }
  else{
    setObjParameter(JAM, objID, arcID, sideID, blockID);
  }

}

//--------------------------------------------------------------------------//
void 
ObjLocation::setObjParameter(int traffic_status, int objID, int arcID, int sideID, int blockID){
 

  double k    = g->arc[arcID].block[sideID][blockID].K;
  double k_s  = g->arc[arcID].block[sideID][blockID].K_saturation;
  double dL   = g->arc[arcID].block[sideID][blockID].block_length;

  o->move[objID].plan_progress      = 0;    
  o->move[objID].plan_direction     = OUTWARD;
  
  o->move[objID].gain               = 0;
  o->move[objID].velocity           = 0;
  
  o->move[objID].generation_step    = c->step;
  o->move[objID].actual_plan_length = 0; 
  
  
  for(int direction = 0; direction < ROUND_TRIP; direction++){  
    o->move[objID].num_arrival[direction]       = 0;
    o->move[objID].required_time[direction]     = 0;   
    o->move[objID].required_distance[direction] = 0;
  }
  

  //-- In the case the block is NOT filled with objects
  if(traffic_status == NOT_JAM){

    o->move[objID].driving_status = DRIVING;
    o->move[objID].start_step     = c->step;
    
    //-- Initialize Number of Object in Block 
    
    int block_num_move= g->arc[arcID].block[sideID][blockID].block_num_move;
    g->arc[arcID].block[sideID][blockID].block_move[block_num_move] = objID;
    g->arc[arcID].block[sideID][blockID].block_num_move++;
        

    
    //-- Initialize "distance" of Object 
    int    last_block  = g->arc[arcID].num_block - 1;
    double block_distance_from_start;
    
    if(blockID == last_block){
      o->move[objID].distance = g->arc[arcID].block[sideID][last_block].block_length 
	- g->arc[arcID].block[sideID][blockID].block_num_move;
    }
    else{
      o->move[objID].distance = 
	g->arc[arcID].block[sideID][last_block].block_length 
	+ (last_block - blockID)*g->arc[arcID].block[sideID][blockID].block_length
	- g->arc[arcID].block[sideID][blockID].block_num_move/g->arc[arcID].block[sideID][blockID].K_saturation;
    }
    
    //printf("obj %d is generated in arc:%2d side:%d block:%2d distance:%f\n", 
    //   objID, arcID, sideID, blockID, o->move[objID].distance);
    //printf("origin      obj %d arc:%2d side:%d block:%2d\n",
    //     objID,o->move[objID].origin_arc,o->move[objID].origin_side, o->move[objID].origin_block);
    //printf("destination obj %d arc:%2d side:%d block:%2d\n",
    //  objID,o->move[objID].destination_arc,o->move[objID].destination_side, o->move[objID].destination_block);
    
        
    //-- Update Density of Block 
    block_num_move = g->arc[arcID].block[sideID][blockID].block_num_move;
    g->arc[arcID].block[sideID][blockID].K = (double)block_num_move/dL;
    
    
    //printf("arc:%2d side:%d block%2d obj:%d k:%f\n",
    //       arcID,sideID,blockID,num_move,g->arc[arcID].block[sideID][blockID].K); 
  }
  

  //-- In the case the block is FILLED with objects
  if(traffic_status == JAM){
        
    o->move[objID].driving_status = WAITING;

        
    //-- Initialize Number of Object in Block 
    
    int block_num_wait= g->arc[arcID].block[sideID][blockID].block_num_wait;
    g->arc[arcID].block[sideID][blockID].block_wait[block_num_wait] = objID;
    g->arc[arcID].block[sideID][blockID].block_num_wait++;
    
    

    //-- Initialize "distance" of Object 
    o->move[objID].distance = 0;
  
    
    //printf("obj %d is generated in arc:%2d side:%d block:%2d distance:%f\n", 
    //   objID, arcID, sideID, blockID, o->move[objID].distance);
    //printf("origin      obj %d arc:%2d side:%d block:%2d\n",
    //     objID,o->move[objID].origin_arc,o->move[objID].origin_side, o->move[objID].origin_block);
    //printf("destination obj %d arc:%2d side:%d block:%2d\n",
    //  objID,o->move[objID].destination_arc,o->move[objID].destination_side, o->move[objID].destination_block);    
  }


  //printf("ID %d distance %f\n",objID,o->move[objID].distance);
 
}

//--------------------------------------------------------------------------//

void 
ObjLocation::initializeObjDecision(){

  od.getGeoInfo(g);
  od.getObjInfo(o);

  for(int objID = 0; objID < o->num_move; objID++){
    od.initializePlan(objID);
  }

}

//--------------------------------------------------------------------------//

void 
ObjLocation::Update(void)
{

  //-- Get Information of Geometory and Moving Object
  od.getGeoInfo(g);
  od.getObjInfo(o);


  
  /*
  for(int objID = 0; objID < o->num_move; objID++){
    printf("obj:%2d arc:%2d side:%d block:%2d - distance:%f v:%f\n",
	   objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block,
	   o->move[objID].distance,o->move[objID].velocity);
  }
  */



  //-- Update Location of Object
  for(int objID = 0; objID < o->num_move; objID++){
    o->move[objID].flag_move_turn      = FALSE;
    o->move[objID].flag_move_new_block = FALSE;
  }


  //-- Arc updated is selected based on Random Order.
  
  int order1, order2;
  int temp;
  
  for(int arcID = 0; arcID < g->num_arc; arcID++){
    order_arcID[arcID] = arcID;
  }
  
  for(int arcID = 0; arcID < g->num_arc; arcID++){
    
    order1 = arcID;  
    order2 = rand()%g->num_arc;

    temp                = order_arcID[order1];
    order_arcID[order1] = order_arcID[order2];    
    order_arcID[order2] = temp;
  }


  //-- Update Location of Object
  for(int arcID = 0; arcID < g->num_arc; arcID++){
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){

      for(int blockID = 0; blockID < g->arc[ order_arcID[arcID] ].num_block; blockID++ ){

	
	updateObjLocation(order_arcID[arcID], sideID, blockID);


      }
    }
  }

  
  for(int objID = 0; objID < o->num_move; objID++){

    if(o->move[objID].driving_status == DRIVING){
    
      decideVelocity(objID, o->move[objID].arc, o->move[objID].side, o->move[objID].block);

      //int direction = o->move[objID].plan_direction;
      //o->move[objID].required_time[direction]++;   
      //od.checkCurrentPosition(objID);
    }
  }



}

//--------------------------------------------------------------------------//

void 
ObjLocation::updateObjLocation(int arcID, int sideID, int blockID){


  if(blockID == 0){

    updateFirstBlock(arcID, sideID, 0);

  }
  else{

    updateRearBlock(arcID, sideID, blockID);
    addWaitingObject(arcID, sideID, blockID);
      
  }

}

//--------------------------------------------------------------------------//

void 
ObjLocation::updateFirstBlock(int arcID, int sideID, int blockID)
{

  int num_obj = g->arc[arcID].block[sideID][blockID].block_num_move;
  int num_out = 0; //-- Number of Object leaving This Block
  
  double k_s  = g->arc[arcID].block[sideID][blockID].K_saturation;
  double distance_2obj;
   


  for(int block_objID = 0; block_objID < num_obj; block_objID++){

    int    objID             = g->arc[arcID].block[sideID][0].block_move[ block_objID ];
    int    u_turn            = FALSE;
    int    previous_arc      = arcID;
    double previous_distance = o->move[objID].distance;

    o->move[objID].velocity = decideVelocity(objID, arcID, sideID, blockID);
    

    //printf("obj:%2d arc:%2d side:%d block:%2d - distance:%f\n\n",
    //	   objID,o->move[objID].arc,o->move[objID].side,
    //     o->move[objID].block,o->move[objID].distance);

    
    //-- Decide One in front of Object
    int front_objID;  
    int front_obj_arc;
    
    if(block_objID == 0){
      front_obj_arc = -999; 
    }
    else{
      front_objID   = g->arc[arcID].block[sideID][0].block_move[ block_objID -1 ];
      front_obj_arc = o->move[front_objID].arc; 
    }

    
    //-- check whether this car has moved in this step
    if( o->move[objID].flag_move_turn == FALSE){  

      o->move[objID].flag_move_turn = TRUE;
      
      //-- check whether front car is in the same block 
      if( front_obj_arc != o->move[objID].arc ){
	
	//-- check whether objcect has enough velocity to move to next arc.
	if(o->move[objID].distance + o->move[objID].velocity * TIME_UNIT > g->arc[arcID].distance){

	  //-- Decision Making of Object on Cross
	  od.chooseArc(objID); 

	  
	  //-- Get Information of Object based on Decision Making of Object on Cross

	  int    next_arc       = o->move[objID].choice_arc;           //-- 移動体が選択したアーク
	  int    next_num_block = g->arc[next_arc].num_block;
	  int    last_block     = next_num_block-1;
	  int    current_node   = g->arc[arcID].block_end_node[sideID];//-- 移動体がいるノード
	  int    next_side      = getNextSide(arcID, sideID, next_arc);//-- 移動体が選択したアークのサイド

	  int    next_arc_start_node; //-- 移動体が選択したアークのノード = current_node
	  int    next_arc_end_node;   //-- 移動体が選択したアークのノード

	  
	  //-- Decide Start and End Node based on Next Arc that Object Chose
	  if(g->arc[next_arc].start == current_node){
	    next_arc_start_node = g->arc[next_arc].start;
	    next_arc_end_node   = g->arc[next_arc].end; 
	  }
	  else{
	    next_arc_start_node = g->arc[next_arc].end;
	    next_arc_end_node   = g->arc[next_arc].start; 
	  }
	  
	  //printf("now obj:%2d arc:%2d side:%d -> next arc:%2d side:%d\n",
	  //objID,arcID,sideID,next_arc,next_side);

	  
	  //-- Get Information of Block[last_block] in Next Arc that Object Chose
	  double next_k         = g->arc[next_arc].block[next_side][last_block].K;
	  double next_k_c       = g->arc[next_arc].block[next_side][last_block].K_critical; 
	  double next_k_s       = g->arc[next_arc].block[next_side][last_block].K_saturation; 
	  double next_dL        = g->arc[next_arc].block[next_side][last_block].block_length;
	  int    next_num_move  = g->arc[next_arc].block[next_side][last_block].block_num_move;
	  
	  
	  //-- Get Possible Gain "distance" of Object in Block[last_block] of Next Arc 
	  double rest_distance = g->arc[arcID].distance - o->move[objID].distance;
	  double v_this_block  = o->move[objID].velocity;    //-- velocity in this block 
	  double t_this_block  = rest_distance/v_this_block; //-- time spent in this block 
	  
	  double t_next_block  = TIME_UNIT - t_this_block;   //-- time spent in next block
	  double v_next_block  = decideVelocity(objID, next_arc, next_side, last_block);//-- velocity in next block 
	  
	  double d_next_block  = t_next_block * v_next_block;//-- gain in next block 
	  
	  int    last_obj;         
	  double last_obj_distance;


	  
	  //-- Get Position of Last Object in Block[last_block] of Next Arc
	  if(next_num_move == 0){
	    last_obj_distance = g->arc[next_arc].block[next_side][last_block].block_length; 
	  }
	  else{	  
	    last_obj          = g->arc[next_arc].block[next_side][last_block].block_move[next_num_move-1];  
	    last_obj_distance = o->move[last_obj].distance; 
	    
	    //printf("2-2 last_obj:%2d last_obj_distance:%f \n",last_obj,last_obj_distance);
	  }
	  

 
	  //-- Get Position of Object in Block[last_block] of Next Arc
	  if(last_obj_distance > d_next_block ){
	    o->move[objID].distance = d_next_block;
	  }
	  else{
	    distance_2obj           = 1.0/next_k_s;
	    o->move[objID].distance = last_obj_distance - distance_2obj;
	  }

	  
	  //-- from point of density & space, check whether next arc cant accept objcet or not.
	  if( (next_k*next_dL + 1.0)/next_dL <  next_k_s  && 
	      o->move[objID].distance >= 0	        ){
	    //-- Next arc accepts objcet.
	 

   
	    //-- Update Block[last_block]
	    next_k = (next_k*next_dL + 1.0)/next_dL;
	    
	    g->arc[next_arc].block[next_side][last_block].K                         = next_k;
	    g->arc[next_arc].block[next_side][last_block].block_move[next_num_move] = objID;
	    
	    next_num_move++;
	    g->arc[next_arc].block[next_side][last_block].block_num_move = next_num_move;
	    
	    
	    //-- Update Block[blockID]
	    num_out++;

	    
	    //-- Update Object Status
	    o->move[objID].arc   = next_arc;
	    o->move[objID].side  = next_side;   
	    o->move[objID].block = last_block;
	    o->move[objID].end   = next_arc_end_node;
	    o->move[objID].start = next_arc_start_node; 
	    
	    o->move[objID].plan_progress++;
	    o->move[objID].flag_move_new_block = TRUE;   /* 次のアークの最後尾のブロックに移動  */

	    o->move[objID].actual_plan[o->move[objID].actual_plan_length] = o->move[objID].choice_node ;
	    o->move[objID].actual_plan_length++; 


	    if(next_arc == previous_arc)
	      u_turn = TRUE;


	    //printf("objID:%d plan_progress:%d \n",objID, o->move[objID].plan_progress);
	  }
	  else{
	    //-- Next arc cannot accept objcet.
	    //-- Object stops in front of cross.


	    k_s                     = g->arc[arcID].block[sideID][blockID].K_saturation;
	    distance_2obj           = 1.0/k_s;
	    o->move[objID].distance = g->arc[arcID].distance - (block_objID - num_out)*distance_2obj;


	  }

	  
	}
	else{
	  //-- Object cant move to next arc 
	  //-- because object dosent have enough gain distance.
	 
	  o->move[objID].distance = o->move[objID].distance + o->move[objID].velocity * TIME_UNIT;
	}

      }
      else{
	//-- Object cant move to next arc 
	//-- because another car is in fornt of it.

	double d_this_block       = o->move[objID].velocity * TIME_UNIT;
	double front_obj_distance = o->move[ front_objID ].distance;
	
	if(front_obj_distance > o->move[objID].distance + d_this_block ){
	  o->move[objID].distance = o->move[objID].distance + d_this_block;

	}
	else{     
	  distance_2obj           = 1.0/k_s;
	  
	  //o->move[objID].distance = front_obj_distance - distance_2obj;  

	  if( o->move[objID].distance < front_obj_distance - distance_2obj){
	    
	    o->move[objID].distance = front_obj_distance - distance_2obj;
	    
	  }
	  else{ 
	    
	    o->move[objID].distance = o->move[objID].distance;
	    
	    //printf("objID:%d\n",objID);
	  }

	  
	  //printf("arc:%2d side:%d block:%2d o->move[%d].distance:%f\n",
	  //arcID,sideID,blockID,objID,o->move[objID].distance);
	  //printf(" front_obj_arc:%d front_obj_distance:%f\n", front_obj_arc, front_obj_distance);	
	}
      }
    
    //printf("obj:%2d arc:%2d side:%d block:%2d - distance:%f\n\n",
    //	   objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block,o->move[objID].distance);
    
    
    
    //-- Calculate Gain in This Step
      
      if( o->move[objID].arc == previous_arc && u_turn == FALSE ){
	//-- the case that objects stay the same block
      
	o->move[objID].gain = o->move[objID].distance - previous_distance;
	
	//printf("obj:%2d arc:%2d side:%d block:%2d previous_arc:%d - distance:%f\n",
	//    objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block,
	//    previous_arc,o->move[objID].distance);
	//printf("o->move[objID].gain           :%f \n",o->move[objID].gain);  
	//printf("o->move[objID].distance       :%f \n",o->move[objID].distance);   
	//printf("g->arc[previous_arc].distance :%f \n",g->arc[previous_arc].distance);    
	//printf("previous_distance             :%f \n\n",previous_distance);
	
      }
      else{
	//-- the case that objects move to the next block
	
	o->move[objID].gain = o->move[objID].distance + (g->arc[previous_arc].distance - previous_distance);
      }
      

      
      //-- Check "o->move[%d].distance"
      if(o->move[objID].distance < 0){
	printf("arc:%2d side:%d block:%2d o->move[%d].distance:%f\n",
	       arcID,sideID,blockID,objID,o->move[objID].distance);
	exit(1);
      }

    
  
      //-- Update and Check Status of Object in Block[0]
      //decideVelocity(objID, o->move[objID].arc, o->move[objID].side, o->move[objID].block);
      od.checkCurrentPosition(objID);
    }
  }
 

  //-- Update Status & List of Object in Block[blockID]
  updateBlockStatus(arcID, sideID, blockID, num_obj, num_out);


}

//--------------------------------------------------------------------------//

void 
ObjLocation::updateRearBlock(int arcID, int sideID, int blockID){


  int    num_obj = g->arc[arcID].block[sideID][blockID].block_num_move;
  int    num_out = 0;//-- Number of Object leaving This Block

  double k_s     = g->arc[arcID].block[sideID][blockID].K_saturation;
  double distance_2obj;


  for(int block_objID = 0; block_objID < num_obj; block_objID++){

    int    objID             = g->arc[arcID].block[sideID][blockID].block_move[ block_objID ];

    int    previous_arc      = arcID;
    double previous_distance = o->move[objID].distance;

    o->move[objID].velocity  = decideVelocity(objID, arcID, sideID, blockID);


    //-- "before_distance" works for checking decrease of "o->move[objID].distance".
    double before_distance = o->move[objID].distance;


    //printf("obj:%2d arc:%2d side:%d block:%2d - distance:%f\n",
    // objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block,o->move[objID].distance);


    //-- Decide One in front of Object
    int front_objID;    
    int front_obj_block;

    if(block_objID == 0){
      front_obj_block = -999; 
    }
    else{
      front_objID     = g->arc[arcID].block[sideID][blockID].block_move[ block_objID -1 ];
      front_obj_block = o->move[front_objID].block; 
    }

    
    //-- check whether this car has moved in this step
    if( o->move[objID].flag_move_turn == FALSE){  
      
      o->move[objID].flag_move_turn = TRUE;
      
      //-- check whether front car is in the same block 
      if( front_obj_block != o->move[objID].block ){
	
	int    last_block = g->arc[arcID].num_block - 1;
	double block_distance_from_start;
	double rest_distance;

	block_distance_from_start = g->arc[arcID].block[sideID][last_block].block_length 
	  + g->arc[arcID].block[sideID][blockID].block_length * (last_block - blockID);
	rest_distance             = block_distance_from_start - o->move[objID].distance;
	

	//-- check whether objcect has enough velocity to move to next block.
	if(o->move[objID].velocity * TIME_UNIT > rest_distance){
	  
	  //-- Get Information of Block[blockID - 1]
	  double next_k         = g->arc[arcID].block[sideID][blockID-1].K;
	  double next_k_c       = g->arc[arcID].block[sideID][blockID-1].K_critical; 
	  double next_k_s       = g->arc[arcID].block[sideID][blockID-1].K_saturation; 
	  double next_dL        = g->arc[arcID].block[sideID][blockID-1].block_length;
	  int    next_num_move  = g->arc[arcID].block[sideID][blockID-1].block_num_move;
	  
	  
	  //-- Get Possible Gain "distance" of Object in Block[blockID - 1] 
	  double v_this_block   = o->move[objID].velocity;
	  double t_this_block   = rest_distance/v_this_block;
	  
	  double t_next_block   = TIME_UNIT - t_this_block;
	  double v_next_block   = decideVelocity(objID, arcID, sideID, blockID-1);
	  double d_next_block   = t_next_block * v_next_block;
	  
	  int    last_obj;       
	  double last_obj_distance;
	  
	  
	  //-- Get Position of Last Object in Block[blockID - 1]
	  if(next_num_move == 0){
	    last_obj_distance = block_distance_from_start + g->arc[arcID].block[sideID][blockID-1].block_length; 
	  }
	  else{
	    last_obj          = g->arc[arcID].block[sideID][blockID-1].block_move[ next_num_move - 1 ];
	    last_obj_distance = o->move[last_obj].distance; 
	    //printf("2 last_obj:%2d last_obj_distance:%f \n",last_obj,last_obj_distance);
	  }
	  
	  
	  //-- Calculate "distance" in Next Block
	  if(last_obj_distance > d_next_block + rest_distance + o->move[objID].distance){
	    
	    o->move[objID].distance  += (d_next_block + rest_distance);
	    
	  }
	  else{	
	    distance_2obj = 1.0/next_k_s;
	    
	    if(   o->move[objID].distance < last_obj_distance - distance_2obj  ){
	      
	      o->move[objID].distance = (last_obj_distance - distance_2obj);
	    }
	    
	  }
	  
	  
	  //-- from point of density & space, check whether next arc cant accept objcet or not.
	  if(  (next_k*next_dL + 1.0)/next_dL < next_k_s   ){
	    //-- Next Block accepts objcet 
	    

	    
	    //-- If next block is destination, this object is eliminated.  
	    if(arcID     == o->move[objID].destination_arc  &&
	       sideID    == o->move[objID].destination_side &&  
	       blockID-1 == o->move[objID].destination_block ) {
      
	      o->move[objID].driving_status      = ARRIVAL;
	      
	      num_out++;	    

	      o->move[objID].block--;
	      o->move[objID].flag_move_new_block = TRUE;

	      //continue;
	    }
	    else{

	      //-- Update Block[last_block]	  
	      next_k = (next_k*next_dL + 1.0)/next_dL;
	      g->arc[arcID].block[sideID][blockID-1].K                         = next_k;     
	      g->arc[arcID].block[sideID][blockID-1].block_move[next_num_move] = objID;
	      
	      next_num_move++;
	      g->arc[arcID].block[sideID][blockID-1].block_num_move = next_num_move;
	      
	      
	      //-- Update This Block
	      num_out++;
	      
	      
	      //-- Update Object
	      o->move[objID].block--;
	      o->move[objID].flag_move_new_block = TRUE;
	      
	    }
	  
	  }
	  else{
	    //-- Next block cannot accept objcet.
	    //-- Object stops in front of next block.
	    
	    o->move[objID].distance = block_distance_from_start;
	  }
	  
	}
	else{
	  //-- Object cant move to next block 
	  //-- because object dosent have enough gain distance.
	  
	  o->move[objID].distance = o->move[objID].distance + o->move[objID].velocity * TIME_UNIT;
	}
	
      }
      else{      
	//-- Object cant move to next block 
	//-- because another car is in fornt of it.
	
	double d_this_block       = o->move[objID].velocity * TIME_UNIT;
	double front_obj_distance = o->move[ front_objID ].distance;
	
	
	if(front_obj_distance > o->move[objID].distance + d_this_block ){
	  
	  o->move[objID].distance = o->move[objID].distance + d_this_block;
	  
	}
	else{	    
	  //-- Object cant move to next block 
	  //-- because another car is in fornt of it.
	  
	  distance_2obj           = 1.0/k_s;
	  
	  if( o->move[objID].distance < front_obj_distance - distance_2obj){
	    
	    o->move[objID].distance = front_obj_distance - distance_2obj;
	    
	  }
	  
	}
      }      
      
      
      //-- Calculate Gain in This Step
      
      
      if( o->move[objID].arc == previous_arc ){  
	//-- the case that objects stay the same arc
	
	o->move[objID].gain = o->move[objID].distance - previous_distance;
	
      }
      else{
	//-- the case that objects move from next arc
	
	o->move[objID].gain = o->move[objID].distance + (g->arc[previous_arc].distance - previous_distance);
	
	//printf("o->move[objID].gain           :%f \n",o->move[objID].gain);  
	//printf("o->move[objID].distance       :%f \n",o->move[objID].distance);   
	//printf("g->arc[previous_arc].distance :%f \n",g->arc[previous_arc].distance);    
	//printf("previous_distance             :%f \n\n",previous_distance);
      }
      
      
      //-- "before_distance" works for checking decrease of "o->move[objID].distance".
      if(o->move[objID].distance < 0){
	exit(1);
      }
      
    
      //-- Update and Check Status of Object in Block[0]
      //decideVelocity(objID, o->move[objID].arc, o->move[objID].side, o->move[objID].block);
      od.checkCurrentPosition(objID);
    }
    
  }
  
  //-- Update Status & List of Object in Block[blockID]
  updateBlockStatus(arcID, sideID, blockID, num_obj, num_out);



}

//--------------------------------------------------------------------------//

void 
ObjLocation::updateBlockStatus(int arcID, int sideID, int blockID, int num_obj, int num_out)
{  

  double dL = g->arc[arcID].block[sideID][blockID].block_length;

  g->arc[arcID].block[sideID][blockID].K               = (num_obj - num_out)/dL;
  g->arc[arcID].block[sideID][blockID].block_num_move -= num_out;
  
  for(int block_objID = 0; block_objID < num_obj - num_out; block_objID++){

    g->arc[arcID].block[sideID][blockID].block_move[block_objID] = 
      g->arc[arcID].block[sideID][blockID].block_move[block_objID + num_out];

  }

}

//--------------------------------------------------------------------------//

void 
ObjLocation::addWaitingObject(int arcID, int sideID, int blockID){

  int    num_move  = g->arc[arcID].block[sideID][blockID].block_num_move;
  int    num_wait  = g->arc[arcID].block[sideID][blockID].block_num_wait;
  int    num_start = 0;//-- Number of Objects entering This Block from Waiting
  
  double dL  = g->arc[arcID].block[sideID][blockID].block_length;
  double k   = g->arc[arcID].block[sideID][blockID].K;
  double k_s = g->arc[arcID].block[sideID][blockID].K_saturation;

  double distance_2obj;
  double front_obj_distance;

  int    objID;   


  for(int block_wait_objID = 0; block_wait_objID < num_wait; block_wait_objID++){

    //-- If the block is filled, an waiting object cannot be added to the block.
    k   = (double)(g->arc[arcID].block[sideID][blockID].block_num_move +1)/dL;
    k_s = g->arc[arcID].block[sideID][blockID].K_saturation;
    
    if(k > k_s){
      break;
    }    

    //printf("obj:%2d arc:%2d side:%d block:%2d - distance:%f\n",
    // objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block,o->move[objID].distance);


    objID   = g->arc[arcID].block[sideID][blockID].block_wait[ block_wait_objID ];


    //-- The object before generated cannot added to the block. 
    if(o->move[objID].driving_status == STANDBY){
      break;
    }


    //-- Decide One in front of Object 
  
    int    front_objID;    
    int    front_obj_block;   
    int    last_block = g->arc[arcID].num_block - 1;
    
    double front_obj_distance;
    double block_distance_from_start;
    
 
    block_distance_from_start = 
      g->arc[arcID].block[sideID][last_block].block_length + 
      g->arc[arcID].block[sideID][blockID].block_length * (last_block - blockID);

    num_move = g->arc[arcID].block[sideID][blockID].block_num_move;


    if(num_move == 0){
      front_obj_block         = -999;    
      o->move[objID].distance = block_distance_from_start;
    }
    else{
      front_objID             = g->arc[arcID].block[sideID][blockID].block_move[ num_move -1 ];
      front_obj_distance      = o->move[ front_objID ].distance;
      distance_2obj           = 1.0/k_s;

      //printf("front_objID        %d\n", front_objID); 
      //printf("front_obj_distance %f\n", front_obj_distance);  
      //printf("distance_2obj      %f\n", distance_2obj);

      o->move[objID].distance = front_obj_distance - distance_2obj;
    }

    o->move[objID].driving_status = DRIVING;   
    o->move[objID].start_step     = c->step;
    o->move[objID].flag_move_turn = TRUE;   

    num_start++;
    num_wait--;

    g->arc[arcID].block[sideID][blockID].block_move[ num_move ] = objID;
    g->arc[arcID].block[sideID][blockID].block_num_move++;
    g->arc[arcID].block[sideID][blockID].block_num_wait--;
     


    //-- Calculate Gain in This Step
    o->move[objID].gain = 0;
    
    
    //-- "before_distance" works for checking decrease of "o->move[objID].distance".
    if(o->move[objID].distance < 0){
      printf("\n o->move[%d].distance %f\n\n",objID,o->move[objID].distance);
      exit(1);
    }
    
    
    //-- Update and Check Status of Object in Block[0]
    //decideVelocity(objID, o->move[objID].arc, o->move[objID].side, o->move[objID].block);

    od.checkCurrentPosition(objID);
  }
  
  
  //-- Update Status & List of Object in Block[blockID]

  //if(num_wait != 0 || num_start != 0){ 
  //  printf("num_move %d\n",g->arc[arcID].block[sideID][blockID].block_num_move);
  //  printf("num_wait %d\n",num_wait); 
  //  printf("num_start %d\n",num_start);
  //}

  updateWaitStatus(arcID, sideID, blockID, num_wait, num_start);


  //-- Print Number of Moving and Waiting Objects in Block i
  /*
  for(int move_objID=0;move_objID < g->arc[arcID].block[sideID][blockID].block_num_move; move_objID++){
    printf("move ID %d distance %f\n",g->arc[arcID].block[sideID][blockID].block_move[ move_objID ],
	                  o->move[g->arc[arcID].block[sideID][blockID].block_move[ move_objID ]].distance);
  }

  for(int wait_objID=0;wait_objID < g->arc[arcID].block[sideID][blockID].block_num_wait; wait_objID++){

    if(o->move[wait_objID].driving_status == WAITING) 
      printf("wait ID %d\n",g->arc[arcID].block[sideID][blockID].block_wait[ wait_objID ]);

    }
  */

}

//--------------------------------------------------------------------------//

void 
ObjLocation::updateWaitStatus(int arcID, int sideID, int blockID, int num_wait, int num_start)
{  
   
  double dL = g->arc[arcID].block[sideID][blockID].block_length;

  g->arc[arcID].block[sideID][blockID].K = 
    ((double)g->arc[arcID].block[sideID][blockID].block_num_move)/dL;
  
  
  //if(num_wait != 0 || num_start != 0){
  //  printf("in updateWaitStatus\n");
  //  printf("num_wait %d\n",num_wait); 
  //  printf("num_start %d\n",num_start);
  //}


  for(int wait_objID = 0; wait_objID < num_wait; wait_objID++){

    g->arc[arcID].block[sideID][blockID].block_wait[wait_objID] = 
      g->arc[arcID].block[sideID][blockID].block_wait[wait_objID + num_start];

  }

}

//--------------------------------------------------------------------------//

int 
ObjLocation::getNextSide(int arcID, int sideID, int next_arc)
{

  int    next_side    = -1;   //-- 移動体が選択したアークのサイド
  int    current_node = g->arc[arcID].block_end_node[sideID];//-- 移動体がいるノード
  int    next_arc_start_node; //-- 移動体が選択したアークのノード = current_node
  int    next_arc_end_node;   //-- 移動体が選択したアークのノード
  

  //-- Decide Start and End Node based on Next Arc that Object Chose
  if(g->arc[next_arc].start == current_node){
    next_arc_start_node = g->arc[next_arc].start;
    next_arc_end_node   = g->arc[next_arc].end; 
  }
  else{
    next_arc_start_node = g->arc[next_arc].end;
    next_arc_end_node   = g->arc[next_arc].start; 
  }
  
  
  //-- Decide Side on Next Arc that Object Chose
  for(int candidate_sideID = 0; candidate_sideID < NUM_SIDE; candidate_sideID++){
    
    int start_node_candidate = g->arc[next_arc].block_start_node[candidate_sideID];
    int end_node_candidate   = g->arc[next_arc].block_end_node[candidate_sideID];
    
    if(next_arc_start_node == start_node_candidate && 
       next_arc_end_node   == end_node_candidate){
      
      next_side = candidate_sideID;	      
    }
    
    if(next_side < -1){
      printf("errer next_side was not decided in arc %d\n",arcID);
      exit(1);
    }
  }
  
  return next_side;

}

//--------------------------------------------------------------------------//

double 
ObjLocation::decideVelocity(int objID, int arcID, int sideID, int blockID)
{

  double k              = g->arc[arcID].block[sideID][blockID].K;
  double vel            = 0;

  int    top_obj        = g->arc[arcID].block[sideID][blockID].block_move[0];
  int    next_arc       = o->move[objID].choice_arc; //-- 移動体が選択したアーク

  int    next_num_block = g->arc[next_arc].num_block;
  int    last_block     = next_num_block-1;

  int    current_node   = g->arc[arcID].block_end_node[sideID];//-- 移動体がいるノード
  int    next_side      = getNextSide(arcID, sideID, next_arc);//-- 移動体が選択したアークのサイド


  //-- Decide Dencity
  //-- Density "k" for deciding velocity is selected 
  //-- based on location of object. 
  if(objID == top_obj){

    if(blockID != 0){
      //-- When object is top one in Block[blockID],
      //-- density in next block is refered.

      if(k > g->arc[arcID].block[sideID][blockID-1].K)
	k = g->arc[arcID].block[sideID][blockID-1].K;
    }
    else{
      //-- When object is top one in Top Block[0],
      //-- density in next block that it chose is refered.
       
      if(k > g->arc[next_arc].block[next_side][last_block].K)
	k = g->arc[next_arc].block[next_side][last_block].K;
    }
  }


  //-- Decide Velocity
  //-- Velocity "vel" is decided based on 
  //-- density "K" and location of block.

  vel = K_V_function(k, arcID, blockID);

  //printf("in update velocity arc:%d side:%d block:%d\n", arcID, sideID, blockID);
  //printf("objID:%2d K:%.2f v:%.2f\n",objID,k,vel);

  return vel;

}

//--------------------------------------------------------------------------//

double 
ObjLocation::K_V_function(double k, int arcID, int blockID)
{

  double vel;


  int num_route = 0;
  
  
  if(num_route == 2){
    if(arcID == 2 || arcID == 5 ){
      k *= 2.0;
    }
  }
  
  if(num_route == 3){
    if(arcID == 2 || arcID == 5 || arcID == 16){
      k *= 3.0;
    }
  }

  if(num_route == 4){
    if(arcID == 2 || arcID == 5 || arcID == 16 || arcID == 19){
      k *= 4.0;
    }
  }

  if(num_route == 5){	  
    if(arcID == 2 || arcID == 5 || arcID == 16 || arcID == 19 || arcID == 22){
      k *= 5.0;
    }
  }

  if(num_route == 6){	  
    if(arcID == 2 || arcID == 5 || arcID == 16 || arcID == 19 || arcID == 22 || arcID == 25){
      k *= 6.0;
    }
  }




  if(blockID == 0){
    //--  K_V_function for Top Block

    vel = K_V_function_top(k);
  }
  else if(blockID == g->arc[arcID].num_block-1){
    //--  K_V_function for Last Block

    vel = K_V_function_last(k);
  }
  else{
    //--  K_V_function for Other Block

    vel = K_V_function_middle(k);
  }
  
  //printf("in update velocity arc:%d block:%d\n", arcID, blockID);
  //printf("in update velocity arc:%d side:%d block:%d\n", arcID, sideID, blockID);
  //printf("objID:%2d K:%.2f v:%.2f\n",objID,k,vel);


  return vel;

}

//--------------------------------------------------------------------------//

double 
ObjLocation::K_V_function_middle(double k){

  double V;

  V = 500.0/36.0*(1.0 - (100.0/14.0)*k);
  
  if( V <= 0 )
    V = 0.1;

  return V;
  
}


double 
ObjLocation::K_V_function_top(double k){

  double V;

  V = 500.0/36.0*(1.0 - (100.0/14.0)*k);
  
  if( V <= 0 )
    V = 0.1;
  
  return V;
  
}


double 
ObjLocation::K_V_function_last(double k){

  double V;

  V = 500.0/36.0*(1.0 - (100.0/14.0)*k);

  if( V <= 0 )
    V = 0.1;
  
  return V;
  
}
//--------------------------------------------------------------------------//

int 
ObjLocation::checkNumDrivingObj(void)
{ 
  
  int total_num_arrival_obj = 0;

  for(int naviID = 0; naviID < NAVI_TYPE; naviID++){

    total_num_arrival_obj += o->num_arrival[naviID];
  }

  //printf("total_num_driving_obj %d\n",total_num_arrival_obj); 
  //printf("total_num_driving_obj %d\n",o->Max_Obj);

  if( total_num_arrival_obj == o->Max_Obj ){

    //printf("total_num_arrival_obj %d\n",total_num_arrival_obj);

    return TRUE;
  }
  else{

    return FALSE;
  }


}

//--------------------------------------------------------------------------//

void 
ObjLocation::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;  
}

void 
ObjLocation::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

void 
ObjLocation::getCtlInfo(struct ITERATION_CONTROL *ext_ctl)
{ 
  //printf("in :getCtlInfo.\n");
  c = ext_ctl;  
}




//--------------------------------------------------------------------------//




