/*-*-c++-*-*/
//
//  Monitor.h
//
//  Header file for Monitor.cpp
//

#ifndef MONITOR_H
#define MONITOR_H

#include "extvar.h"
#include "Obj_location.h"


//--------------------------------------------------------------------------//

class Monitor
{
public:

  Monitor(void); 
  ~Monitor(void);  

  void initializeParameter(void); 

  void updateMacroParameter_step(void);   
  void updateMacroParameter_NaviType_step(void); 
  
  void outputMacroParameter_step(void);  
  void outputMacroParameter_trial(void);  

  void outputMicroParameter_trial(void);

  void openOuputFile_step(char *filename);   
  void openOuputFile_step(char *filename, int num_obj, int order);    
  void openOuputFile_step(char *filename, int num_obj, int ratio1, int order);
  void openOuputFile_step(char *filename, int num_obj, int ratio1, int ratio2, int order);
  void openOuputFile_step(char *filename, int num_obj, int ratio1, int ratio2, int ratio3, int order);
  void closeOuputFile_step(void);

  void openOuputFile_trial(char *filename);     
  void openOuputFile_trial(char *filename, int num_obj);   
  void openOuputFile_trial(char *filename, int num_obj, int one_ratio);   
  void openOuputFile_trial(char *filename, int num_obj, int one_ratio, int order); 
  void openOuputFile_trial(char *filename, int num_obj, int ratio1, int ratio2, int ratio3);

  void closeOuputFile_trial(void);

  void getGeoInfo(struct GEO_INFO *geo);	  
  void getObjInfo(struct OBJECTS  *obj);
  void getCtlInfo(struct ITERATION_CONTROL  *ctl);  
  void getMacroInfo(struct  MACRO_PARAMETER *macro);	  


  double calcuAve(int step, double old_ave, int    new_factor);
  double calcuAve(int step, double old_ave, double new_factor);


  FILE *fp_output_step;  
  FILE *fp_output_K_step;   
  FILE *fp_output_D_step;  
  
  FILE *fp_output_trial;   
  FILE *fp_output_K_trial;  

  struct GEO_INFO          *g;
  struct OBJECTS           *o;
  struct ITERATION_CONTROL *c; 
  struct MACRO_PARAMETER   *m;

  ObjLocation ol_in_ic;  

private:

};


#endif //MONITOR_H
