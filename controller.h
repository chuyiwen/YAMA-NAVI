/*-*-c++-*-*/
//
//  ctl_panel.h
//
//

#ifndef CTL_PANEL_H
#define CTL_PANEL_H

#include "Qt_ctl_panel.h"
#include "extvar.h"
#include "define.h"



//------------------------------------------------
// external variables for control panel

QtCtlPanel  c;

//struct GEO_INFO Geo; 
//struct WindowSize Frame;

pthread_t ctl_panel_t; 

int c_ext_argc;
char **c_ext_argv;

struct two_args{
  int c_argc1;
  char **c_argv1;
};

struct two_args *c_ap;


//------------------------------------------------


void init_controller(int argc, char **argv );
void start_controller(void);
void *controller(void *);


void int_controller(int argc, char **argv )
{
  c_ext_argc = argc;
  c_ext_argv = argv;
}


// create thread with ctl_panel()
void start_controller(void)
{
  pthread_create(&ctl_panel_t, NULL, controller, (void *)c_ap);    
}


void *
controller(void *erg)
{

  c.InitCtlSimulation(c_ext_argc, c_ext_argv);
  c.CtlSimulaiton(c_ext_argc, c_ext_argv, &Geo, &Obj);


  /*
  printf("in graphics\n");
  
  int a;
  while(1){
    scanf("%d",&a);
    printf("in test function\n"); 
    printf("a = %d\n",a);
  }  
  */

  return NULL;
}

#endif //CTL_PANEL_H
