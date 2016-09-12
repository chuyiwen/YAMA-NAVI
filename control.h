/*-*-c++-*-*/
//
//  control.h
//
//

#ifndef CONTROL_H
#define CONTROL_H

#include "Qt_control.h"
#include "extvar.h"
#include "define.h"



//------------------------------------------------
// external variables for control panel

QtControl  c;

//struct GEO_INFO Geo; 
//struct WindowSize Frame;

pthread_t control_t; 

int c_ext_argc;
char **c_ext_argv;

struct c_two_args{
  int c_argc1;
  char **c_argv1;
};

struct c_two_args *c_ap;


//------------------------------------------------


void init_controller(int argc, char **argv );
void start_controller(void);
void *controller(void *);


void init_controller(int argc, char **argv )
{
  c_ext_argc = argc;
  c_ext_argv = argv;
}


// create thread with controller()
void start_controller(void)
{
  pthread_create(&control_t, NULL, controller, (void *)c_ap);    
}


void *
controller(void *erg)
{

  c.InitCtlSimulation(c_ext_argc, c_ext_argv);
  c.CtlSimulation(c_ext_argc, c_ext_argv, &Geo, &Obj);


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
