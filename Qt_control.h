/*-*-c++-*-*/
//
//  Qt_control.h
//
//  Header file for Qt_control.cpp
//

#ifndef QT_CONTROL_H
#define QT_CONTROL_H

// Header file for Qt
#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>


#include "Qt_ctl_panel.h"
#include "extvar.h"


class QtControl
{
public:

  QtControl(void); 
  ~QtControl(void);

  void InitCtlSimulation(int argc, char **argv); 
  void CtlSimulation(int argc, char **argv,struct GEO_INFO *geo, struct OBJECTS *obj);


  ITERATION_CONTROL *tmp; 
  ITERATION_CONTROL iteration; 

  int qt_argc ; 
  char **qt_argv ;  

private:

};


#endif //QT_CONTROL_H
