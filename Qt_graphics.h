/*-*-c++-*-*/
//
//  Qt_graphics.h
//
//  Header file for Qt_graphics.cpp
//

#ifndef QT_GRAPHICS_H
#define QT_GRAPHICS_H

// Header file for Qt
#include <qapplication.h>
#include <qwidget.h>
#include <qpushbutton.h>
#include <pthread.h>

#include "Qt_window.h"
#include "extvar.h"



class QtGraphics
{
public:

  QtGraphics(void); 
  ~QtGraphics(void);

  void InitDrawPicture(int argc, char **argv); 
  void DrawPicture(int argc, char **argv,
		   struct FRAME_SIZE *frame,struct GEO_INFO *geo,
		   struct OBJECTS *obj, struct ITERATION_CONTROL *ctl, 
		   struct MACRO_PARAMETER *macro, struct CHART *chart,
		   struct WINDOW_SIZE *window);

  void setInitialWindowSize(int width, int height);

  int  checkSimStep(void);
  void beginDraw(void);
  void endDraw(void);


  void getFrameInfo(struct FRAME_SIZE *frame);	
  void getGeoInfo(struct GEO_INFO *geo);	
  void getObjInfo(struct OBJECTS  *obj);
  void getCtlInfo(struct ITERATION_CONTROL *ext_ctl);         
  void getMacroInfo(struct  MACRO_PARAMETER *macro);    
  void getChartInfo(struct CHART *ext_chart);
	

  int qt_argc ; 
  char **qt_argv ;  

  double change_rate;

  FRAME_SIZE        *f;
  GEO_INFO          *g; 
  OBJECTS           *o;	
  ITERATION_CONTROL *c; 
  MACRO_PARAMETER   *m;
  CHART             *ch;

private:

};


#endif //QT_GRAPHICS_H
