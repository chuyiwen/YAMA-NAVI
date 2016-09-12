/*-*-c++-*-*/
//
//  Obj_location.h
//
//  Header file for Obj_location.cpp
//

#ifndef OBJ_LOCATION_H
#define OBJ_LOCATION_H

#include "Obj_decision.h"
#include "extvar.h"


class ObjLocation
{
public:

  ObjLocation(void); 
  ~ObjLocation(void);

  ObjDecision od;

  void   initializeObjOD(void);   
  void   OD_random(int objID);  
  void   OD_simple(int objID);  
  void   OD_lattice(int objID);    
  void   OD_radialring(int objID);  
  void   initializeObjODParameter(int objID,int s_arcID,int s_sideID,int s_blockID,int d_arcID,int d_sideID,int d_blockID);

  void   generateObj(void);  
  void   initializeNumNaviType(int num_generate);  
  void   initializeObjNaviType(int objID, int num_generate);  

  void   initializeObjParameter(int objID, int arcID, int sideID, int blockID);  
  void   setObjParameter(int traffic_status, int objID, int arcID, int sideID, int blockID);
  
  void   initializeObjDecision(void);

  void   Update(void);

  void   updateObjLocation(int arcID, int sideID, int blockID);

  void   updateFirstBlock(int arcID, int sideID, int blockID);
  void   updateRearBlock(int arcID, int sideID, int blockID);
  void   updateBlockStatus(int arcID, int sideID, int blockID, int num_obj, int num_out);

  void   addWaitingObject(int arcID, int sideID, int blockID);
  void   updateWaitStatus(int arcID, int sideID, int blockID, int num_waiting, int num_start);

  int    getNextSide(int arcID, int sideID, int next_arc);

  double decideVelocity(int objID, int arcID, int sideID, int blockID);
  double K_V_function(double k, int arcID, int blockID);

  double K_V_function_middle(double density);  
  double K_V_function_top(double density);  
  double K_V_function_last(double density);

  int    checkNumDrivingObj(void);

  void   getGeoInfo(struct GEO_INFO *geo1);	  
  void   getObjInfo(struct OBJECTS  *obj1);	 
  void   getCtlInfo(struct ITERATION_CONTROL  *ctl);  	
  

  struct GEO_INFO *g;
  struct OBJECTS  *o;
  struct ITERATION_CONTROL *c; 
  
  int    order_arcID[MAX_ARC];

private:

};


#endif //OBJ_LOCATION_H
