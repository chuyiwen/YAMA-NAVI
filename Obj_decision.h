/*-*-c++-*-*/
//
//  Obj_decision.h
//
//  Header file for Obj_decision.cpp
//

#ifndef OBJ_DECISION_H
#define OBJ_DECISION_H

#include "Navigator.h"
#include "extvar.h"


//--------------------------------------------------------------------------//

class ObjDecision
{
public:

  ObjDecision(void); 
  ~ObjDecision(void);

  Navigator navi;

  void initializePlan(int objID);

  void chooseArc(int objID); 
  void checkCurrentPosition(int objID);

  void getGeoInfo(struct GEO_INFO *geo);	  
  void getObjInfo(struct OBJECTS  *obj);	
  void getCtlInfo(struct ITERATION_CONTROL  *ctl);  

  struct GEO_INFO *g;
  struct OBJECTS  *o;
  struct ITERATION_CONTROL *c; 

private:

};


#endif //OBJ_LOCATION_H
