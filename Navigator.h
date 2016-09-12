/*-*-c++-*-*/
//
//  Navigator.h
//
//  Header file for Navigator.cpp
//

#ifndef NAVIGATORI_H
#define NAVIGATOR_H

#include "extvar.h"


//--------------------------------------------------------------------------//

class Navigator
{
public:

  Navigator(void); 
  ~Navigator(void);

  void idealPathPlanning(int objID); 
  void normalPathPlanning(int objID); 
  void successivePathPlanning(int objID);


  void compositePlan(int objID);
  
  void dijkstra(int start, int end, int navi_type);

  void getGeoInfo(struct GEO_INFO *geo2);	  
  void getObjInfo(struct OBJECTS  *obj2);	
  

  struct GEO_INFO *g;
  struct OBJECTS  *o;

  double ArcWeight[MAX_NODE][MAX_NODE];
  double Length[MAX_NODE];

  int    S[MAX_NODE];
  int    Path[MAX_NODE];               //-- Minimum Three made by Dijkstra 
  int    Shortest_Path[MAX_NODE];      //-- Shortest Path made by Dijkstra 
  int    temp_Shortest_Path[MAX_NODE]; //-- Minimum Three made by Dijkstra  
  int    shortest_path_length;
  double shortest_distance;


private:

};


#endif //NAVIGATOR_H
