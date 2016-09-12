/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Qt_graphics.h"
//#include "sleep.h"
 

//////////////////////////
//
// QtGraphics methods


//
//
//

//--------------------------------------------------------------------------//

QtGraphics::QtGraphics(void)
{ 
}

QtGraphics::~QtGraphics(void)
{ 
}

//--------------------------------------------------------------------------//

void 
QtGraphics::InitDrawPicture(int argc, char** argv)
{
  qt_argc = argc;
  qt_argv = argv;
}

//--------------------------------------------------------------------------//

void 
QtGraphics::DrawPicture(int argc,char **argv, struct FRAME_SIZE *frame, struct GEO_INFO *geo, struct OBJECTS *obj, struct ITERATION_CONTROL *ctl, struct MACRO_PARAMETER *macro, struct CHART *chart, struct WINDOW_SIZE *window)
{


  //-- 
  QApplication a(qt_argc,qt_argv);
  QtWindow w2;


  //-- Decide Window Size based on Whether Chart is or not

  window->display_text_margin_y = 30;
  window->button_margin_y       = 50;

  window->graphics_height       = 600;  
  window->graphics_width        = 600;
  window->chart_width           = 350;
  

  if(ctl->chart_switch == OFF){
    //setInitialWindowSize(frame->width, frame->height + display_text_margin_y +button_margin_y);
    //w2.setGeometry(20,30,(int)(frame->width*change_rate),(int)(frame->height*change_rate)); 

    w2.setGeometry(20,10, 
		   window->graphics_width,  
		   window->graphics_height +  window->display_text_margin_y + window->button_margin_y);
  }
  else{
    w2.setGeometry(20,30, window->graphics_width +  window->chart_width, window->graphics_height);
  }
  
  //setInitialWindowSize(frame->width, frame->height);
  //w2.setGeometry(100,30,(int)(frame->width*change_rate),(int)(frame->height*change_rate));
  

  //-- 
  a.setMainWidget( &w2 ); 
  w2.show();  
  
  w2.getFrameInfo(frame);
  w2.getGeoInfo(geo); 
  w2.getObjInfo(obj);        
  w2.getCtlInfo(ctl);      
  w2.getMacroInfo(macro);  
  w2.getChartInfo(chart);    
  w2.getWindowInfo(window); 

  w2.initializeButton();  
  w2.initializeChart();


  getFrameInfo(frame);
  getGeoInfo(geo); 
  getObjInfo(obj);        
  getCtlInfo(ctl);  

 

  while(1){

    //-- Begin Draw Loop 
    beginDraw();

    
    //-- Update Data for Chart
    w2.updateChartData();

    
    //-- Loop of "Re"painting Graphics by Qt
    do{

      a.processEvents();    

      //-- Leave this while loop if "Exit Button" is pushed. 
      if(c->exit == TRUE)
	break;

      //-- Leave this while loop if present step is over "Max_Step". 
      if(c->step == c->Max_Step - 1)
	break;


    }while(c->start == FALSE || c->pause == TRUE);
    

    //-- End Draw Loop
    endDraw();


    //-- Leave this while loop if present step is over "Max_Step".
    if(c->step == c->Max_Step - 1)
      break;
 
  }
 
  
}


//--------------------------------------------------------------------------//

void 
QtGraphics::setInitialWindowSize(int width, int height)
{
  
  change_rate = 1.0;

 //-- Reduction of Size
  if(width > MAX_FRAME_SIZE || height > MAX_FRAME_SIZE){
    
    if(width > height)
      change_rate = MAX_FRAME_SIZE/(double)width;
    else
      change_rate = MAX_FRAME_SIZE/(double)height;
  }

  //-- Extension of Size
  if(width < MIN_FRAME_SIZE || height < MIN_FRAME_SIZE){
    
    if(width < height)
      change_rate = MIN_FRAME_SIZE/(double)width;
    else
      change_rate = MIN_FRAME_SIZE/(double)height;
  }

}


//--------------------------------------------------------------------------//

void 
QtGraphics::beginDraw(void)
{   
  //-- Loop during Waiting for Calculation for Simulation
  while( checkSimStep() ){} 
  
  c->simulation = FALSE; 

  //printf("in beginDraw %d\n",c->drawing);
}

void
QtGraphics::endDraw(void)
{
  c->drawing    = FALSE;
  c->simulation = TRUE; 

  //printf("in endDraw %d\n",c->drawing);
}

int 
QtGraphics::checkSimStep(void)
{

  if( c->drawing == TRUE && c->simulation == FALSE){
    return FALSE; //-- exit waiting loop
  }
  else{
    return TRUE;
  }

}

//--------------------------------------------------------------------------//
//Get Geographicaly Information from Class QtGraphics to This Class(QtWindow)

void 
QtGraphics::getFrameInfo(struct FRAME_SIZE *ext_frame)
{ 
  //printf("in :getFrameInfo.\n");
  f = ext_frame;   
}

void 
QtGraphics::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;   
}

void 
QtGraphics::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

void 
QtGraphics::getCtlInfo(struct ITERATION_CONTROL *ext_ctl)
{ 
  //printf("in :getCtlInfo.\n");
  c = ext_ctl;  
}

void 
QtGraphics::getMacroInfo(struct MACRO_PARAMETER *ext_macro)	
{ 
  //printf("in :getMacroInfo.\n");
  m = ext_macro;  
}

void 
QtGraphics::getChartInfo(struct CHART *ext_chart)
{ 
  //printf("in :getCtlInfo.\n");
  ch = ext_chart;  
}

//--------------------------------------------------------------------------//
