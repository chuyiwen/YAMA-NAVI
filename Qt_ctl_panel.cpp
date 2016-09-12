/*-*-c++-*-*/
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>

//#include "Qt_ctl_panel.h"
#include "Qt_ctl_panel.moc"


QtCtlPanel::QtCtlPanel()
{
  
  i.start   = 0;
  i.pause   = 0;
  i.restart = 1;
  i.exit    = 0;
	
  setGeometry( 100, 100, 400, 400 );
  
  b1 = new QPushButton( "Start", this );
  b1->setGeometry( 20, 320, 140, 30 );
  b1->setFont( QFont( "Times", 18, QFont::Normal) );
  
  b2 = new QPushButton( "Pause", this );
  b2->setGeometry( 20, 360, 140, 30 );
  b2->setFont( QFont( "Times", 18, QFont::Normal) );
  
  b3 = new QPushButton( "Restart", this );
  b3->setGeometry( 190, 320, 140, 30 );
  b3->setFont( QFont( "Times", 18, QFont::Normal) );
  
  b4 = new QPushButton( "Exit", this );
  b4->setGeometry( 190, 360, 140, 30 );
  b4->setFont( QFont( "Times", 18, QFont::Normal ) );
  
  
  QObject::connect( b1, SIGNAL( clicked() ), this, SLOT( start_button()  ) );
  QObject::connect( b2, SIGNAL( clicked() ), this, SLOT( pause_button()  ) );
  QObject::connect( b3, SIGNAL( clicked() ), this, SLOT( restart_button()) );
  QObject::connect( b4, SIGNAL( clicked() ), this, SLOT( exit_button()   ) );
}

QtCtlPanel::~QtCtlPanel()
{
  
}

//--------------------------------------------------------------------

void 
QtCtlPanel::start_button()
{
  i.start = 1;
  //printf("in start:\t start  =%d\n",i.start);
}

void 
QtCtlPanel::pause_button()
{
  i.pause   = 1;
  i.restart = 0;  

  //printf("in pause:\t pause  =%d\n",i.pause); 
  //printf("in pause:\t restart=%d\n",i.restart);
}

void 
QtCtlPanel::restart_button()
{
  i.pause   = 0;
  i.restart = 1;  
  
  //printf("in restart:\t pause  =%d\n",i.pause); 
  //printf("in restart:\t restart=%d\n",i.restart);
}

void 
QtCtlPanel::exit_button()
{
  i.exit    = 1;
  //printf("in exit:\t exit   =%d\n",i.exit);
}

//--------------------------------------------------------------------
//get geographicaly information from class QtGraphics to this class(QtCtlPanel)

/*
void 
QtCtlPanel::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;   
}

void 
QtCtlPanel::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}
*/

//--------------------------------------------------------------------
//return button action to main function

int 
QtCtlPanel::Check_start(void)
{ 
  //printf("in Check_start.\n");
  return i.start;
}

int 
QtCtlPanel::Check_pause(void)
{ 
  //printf("in Check_pause.\n");
  return i.pause;
}

int 
QtCtlPanel::Check_restart(void)
{ 
  //printf("in Check_restart.\n");
  return i.restart;
}

int 
QtCtlPanel::Check_exit(void)
{ 
  //printf("in Check_exit.\n");
  return i.exit;
}


//--------------------------------------------------------------------
