/*-*-c++-*-*/
//
//  InfoCenter.h
//
//  Header file for InfoCenter.cpp
//

#ifndef INFOCENTER_H
#define INFOCENTER_H

#include "extvar.h"
#include "Obj_location.h"


//--------------------------------------------------------------------------//

class InfoCenter
{
public:

  InfoCenter(void); 
  ~InfoCenter(void);

  void idealTrafficInfo(void);
  void updateTrafficInfo(void);
  
  void collectPlan(void);
  int  getNextArc(int current_node, int next_node);


  void getGeoInfo(struct GEO_INFO *geo);	  
  void getObjInfo(struct OBJECTS  *obj);	  

  struct GEO_INFO *g;
  struct OBJECTS  *o;

  ObjLocation ol_in_ic;  

  double Length[MAX_NODE];

  int    S[MAX_NODE];
  int    Path[MAX_NODE];               //-- Minimum Three made by Dijkstra 
  int    Shortest_Path[MAX_NODE];      //-- Shortest Path made by Dijkstra 
  int    temp_Shortest_Path[MAX_NODE]; //-- Minimum Three made by Dijkstra  
  int    shortest_path_length;
  double shortest_distance;


private:

};


#endif //INFOCENTER_H
