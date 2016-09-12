/*-*-c++-*-*/
//
//  graphics.h
//
//

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Qt_graphics.h"
#include "extvar.h"
#include "define.h"


//--------------------------------------------------------------------------//
//-- External Variables for Graphics 

QtGraphics  g;

pthread_t graphics_t; 

int g_ext_argc;
char **g_ext_argv;

struct g_two_args{
  int g_argc1;
  char **g_argv1;
};

struct g_two_args *g_ap;

//--------------------------------------------------------------------------//

void  init_graphics(int argc, char **argv );
void  start_graphics(void);
void  *graphics(void *);

void  beginSimStep(void);
void  endSimStep(void);
int   checkDrawing(void);


//--------------------------------------------------------------------------//

void init_graphics(int argc, char **argv )
{
  g_ext_argc = argc;
  g_ext_argv = argv;
  
  Ctl.drawing         = TRUE;
  Ctl.delete_graphics = FALSE;
}

//--------------------------------------------------------------------------//

//-- Create Thread with Graphics()
void start_graphics(void)
{

  pthread_create(&graphics_t, NULL, graphics, (void *)g_ap);   

}

//--------------------------------------------------------------------------//

void *
graphics(void *erg)
{

  g.InitDrawPicture(g_ext_argc, g_ext_argv);
  g.DrawPicture(g_ext_argc, g_ext_argv, &Frame, &Geo, &Obj, &Ctl, &Macro, &Chart, &Window);

  Ctl.delete_graphics = TRUE;

  pthread_exit((void *)0);

  //Ctl.delete_graphics = TRUE;

  printf("\n\n Exit from Graphics Thread.\n\n");


  return 0;  //NULL;
}

//--------------------------------------------------------------------------//

void beginSimStep(void)
{      
  if(Ctl.graphics_switch == ON){
    while( checkDrawing() ){}
    
    Ctl.drawing    = FALSE;
  }
}

void endSimStep(void)
{

  if(Ctl.graphics_switch == ON){
    Ctl.simulation = FALSE; 
    Ctl.drawing    = TRUE;
  }

}

int checkDrawing(void)
{
  //-- if grophics routine working, return 1.
  
  //printf("g.iteration.drawing = %d\n",g.iteration.drawing);

  if( Ctl.drawing == FALSE && Ctl.simulation == TRUE ){
    return FALSE;
  }
  else{
    return TRUE;
  }

}
//--------------------------------------------------------------------------//


#endif //GRAPHICS_H
