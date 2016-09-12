/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Qt_control.h"



 
//////////////////////////
//
// QtControl methods


//
//
//

//--------------------------------------------------------------------------//

QtControl::QtControl(void)
{ 
}

QtControl::~QtControl(void)
{ 
}

//--------------------------------------------------------------------------//

void 
QtControl::InitCtlSimulation(int argc, char** argv)
{
  qt_argc = argc;
  qt_argv = argv;
}

//--------------------------------------------------------------------------//

void 
QtControl::CtlSimulation(int argc,char **argv, struct GEO_INFO *geo, struct OBJECTS *obj)
{

  QApplication c(qt_argc,qt_argv);

  QtCtlPanel w1;
  c.setMainWidget( &w1 ); 
  
  w1.show();  

  //w1.getGeoInfo(geo); 
  //w1.getObjInfo(obj);

  //struct ITERATION_CONTROL iteration; 

  /*
  QWidget mainwindow;
  mainwindow.setMinimumSize( 200, 100 );
  mainwindow.setMaximumSize( 200, 100 );
  QPushButton helloworld( "Hello World!", &mainwindow );
  helloworld.setGeometry( 20, 20, 160, 60 );
  a.setMainWidget( &mainwindow );   
  mainwindow.show();  
  */

  
  
  //a.exec();
 
  int count=0;

  while(1){
    count++;

    //w1.getGeoInfo(geo); 
    //w1.getObjInfo(obj);
    

    //int s = sleep(100);

    c.processEvents();

    //if(count%10 == 0)
    //  printf("after processEvents. %d\n",count);
    
    
    if(count%1 == 0){
      
      //tmp= w1.Check_Iteration();
     
      iteration.start   = w1.Check_start();
      iteration.pause   = w1.Check_pause();  
      iteration.restart = w1.Check_restart();
      iteration.exit    = w1.Check_exit();

      //printf("in Qt:start = %d.\n",iteration.start);

      //count = 0;
      
      //printf("in if.\n");
    }
    
    //printf("after DrawPicture Roop.\n");
    //printf("start = %d\n",iteration->start);
    //printf("generation = %d\n",count);
  }
 
  
}

//--------------------------------------------------------------------------//
