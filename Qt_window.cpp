/*-*-c++-*-*/
//#include "Qt_window.h"
#include "Qt_window.moc"



//////////////////////////
//
// QtWindow methods


//
//
//

//--------------------------------------------------------------------------//

QtWindow::QtWindow()
{
      
  
  //setGeometry( 100,100,400,400);

	  
  b1 = new QPushButton( "Start", this );
  b2 = new QPushButton( "Pause", this );     
  b3 = new QPushButton( "Exit", this );   

  b1->setFont( QFont( "NewRoman", 16, QFont::Normal) );
  b2->setFont( QFont( "NewRoman", 16, QFont::Normal) );
  b3->setFont( QFont( "NewRoman", 16, QFont::Normal ) );
  
  //b4 = new QPushButton( "Restart", this );   
  //b4->setGeometry(transform_x(650+60+60),transform_y(60),50,40);//(x,y,width,height)
  //b4->setGeometry(transform_x(20),transform_y(320),transform_x(20),transform_y(20) );
  //b4->setGeometry( 190, 320, 140, 30 );
  //b4->setFont( QFont( "Times", 16, QFont::Normal) );
  
  QObject::connect( b1, SIGNAL( clicked() ), this, SLOT( start_button()  ) );
  QObject::connect( b2, SIGNAL( clicked() ), this, SLOT( pause_button()  ) );
  QObject::connect( b3, SIGNAL( clicked() ), this, SLOT( exit_button()   ) );
  //QObject::connect( b4, SIGNAL( clicked() ), this, SLOT( restart_button()) );

}

QtWindow::~QtWindow()
{
  
}

//--------------------------------------------------------------------------//

void 
QtWindow::initializeButton()
{
  //-- Button Settings
  if(c->auto_start == ON){
    c->start   = 1;
    c->pause   = 0;
    c->restart = 1;
    c->exit    = 0;
  }
  if(c->auto_start == OFF){
    c->start   = 0;
    c->pause   = 0;
    c->restart = 1;
    c->exit    = 0;
  }


  //-- Deside Position of Buttons
  if(c->chart_switch == ON){
    b1->setGeometry(transform_x(650),      transform_y(45),70,40);//(x,y,width,height)
    b2->setGeometry(transform_x(650+80),   transform_y(45),70,40);//(x,y,width,height)
    b3->setGeometry(transform_x(650+80+80),transform_y(45),70,40);//(x,y,width,height)
  }
  if(c->chart_switch == OFF){
    b1->setGeometry(transform_x(60),       transform_y(45),70,40);//(x,y,width,height)
    b2->setGeometry(transform_x(60+80),    transform_y(45),70,40);//(x,y,width,height)
    b3->setGeometry(transform_x(60+80+80), transform_y(45),70,40);//(x,y,width,height)
  }


}

//--------------------------------------------------------------------------//

void 
QtWindow::initializeChart()
{
  //-- Chart Settings

  //-- Decide Title of Chart
  initializeTitleChart(); 


  //-- Decide Position of Chart
  initializeChartPosition(); 


  //-- Decide Position of Index
  initializeIndexPosition(); 
  
}

void 
QtWindow::initializeTitleChart(void)
{
  ch->num_factor[0] = 1; 
  ch->num_factor[1] = 1; 
  ch->num_factor[2] = 1;

  for(int chartID = 0; chartID < NUM_CHART; chartID++){
    
    for(int factorID = 0; factorID <  ch->num_factor[0]; factorID++){
      
      if(chartID == 0){
	*factor_name[chartID][factorID] = "Average Gain";
      }
      
      if(chartID == 1){
	*factor_name[chartID][factorID] = "Ratio of Stopping Vehicles";//"Average of Present Required Distance";
      }
      
      if(chartID == 2){
	*factor_name[chartID][factorID] = "Average Travel Time";//"Average of Present Required Time";//Velocity";
      }
      
    }
  }

}

void 
QtWindow::initializeChartPosition(void)
{

  chart_width       = 330; //-- Width of Chart ...x
  chart_height      = 140; //-- Height of Chart ...y
  space_y           = 20;  //-- Space between Charts...y
  title_margin      = 30;  //-- Margin for Chart Title...y

  original_margin_x = 50;  //-- Distance from Left Edge of Chart to Oringial Point X  
  original_margin_y = 20;  //-- Distance from Lower Edge of Chart to Oringial Point Y  

  //-- Set Position of Three Charts  
  c_x1 = 10; 
  c_y1 = 400;

  c_x2 = c_x1;  
  c_y2 = c_y1 - chart_height - space_y;//100+160+30  = 290; 

  c_x3 = c_x1;
  c_y3 = c_y2 - chart_height - space_y;//290+160+30 = 480;
  

  //-- Set Oringinal Point of Three Charts  
  o_x1 = c_x1 + original_margin_x;  
  o_y1 = c_y1 + original_margin_y; 
  
  o_x2 = c_x2 + original_margin_x;  
  o_y2 = c_y2 + original_margin_y; 

  o_x3 = c_x3 + original_margin_x;  
  o_y3 = c_y3 + original_margin_y; 

}

void 
QtWindow::initializeIndexPosition(void)
{

  int o_x;
  int o_y;

  for(int chartID = 0; chartID < NUM_CHART; chartID++){

    if(chartID == 0){
      o_x = o_x1;  
      o_y = o_y1;
    }
        
    if(chartID == 1){   
      o_x = o_x2;  
      o_y = o_y2;
    }
    
    if(chartID == 2){  
      o_x = o_x3;  
      o_y = o_y3;
    }
   
    o_index_x[chartID]      = o_x + 10;
    o_index_y[chartID]      = o_y - 20;
  
    X_index_max_x[chartID]  = o_index_x[chartID] + chart_width - original_margin_x - 40;
    X_index_max_y[chartID]  = o_index_y[chartID];
    
    X_index_half_x[chartID] = o_index_x[chartID] + (chart_width - original_margin_x)/2 -15;
    X_index_half_y[chartID] = o_index_y[chartID];
    
    Y_index_max_x[chartID]  = o_x - 45;
    Y_index_max_y[chartID]  = o_y + chart_height - original_margin_y - 40;
    
    Y_index_half_x[chartID] = o_x - 45;
    Y_index_half_y[chartID] = o_y + (chart_height - original_margin_y)/2 - 20;
  
  }
}



//--------------------------------------------------------------------------//

void 
QtWindow::updateChartData(void)
{

  for(int chartID = 0; chartID < NUM_CHART; chartID++){
    storeData(chartID);
  }

}

void 
QtWindow::storeData(int chartID)
{

  if(chartID == 0){

    ch->chart_factor[chartID][0][c->step] = m->ave_gain[ALL_AVERAGE];//m->ave_num_arrival; 

  }  
  if(chartID == 1){

    ch->chart_factor[chartID][0][c->step] = m->ave_num_stop[ALL_AVERAGE];     
    //m->ave_present_required_distance[ALL_AVERAGE]; 

  }
  if(chartID == 2){

    ch->chart_factor[chartID][0][c->step] = m->ave_efficiency_time[ALL_AVERAGE];
    //m->ave_present_required_time[ALL_AVERAGE]; 
    //m->ave_required_time;//m->ave_velocity; 

  }

}

//--------------------------------------------------------------------------//

void 
QtWindow::resizeEvent( QResizeEvent* )
{
  bufferpixmap_g.resize( size() );
  bufferpixmap_g.fill(backgroundColor());  

  bufferpixmap_c.resize( size() );
  bufferpixmap_c.fill(backgroundColor());  

  bufferpixmap_text.resize( size() );
  bufferpixmap_text.fill(backgroundColor());  

  bufferpixmap_button.resize( size() );
  bufferpixmap_button.fill(backgroundColor());
}


void 
QtWindow::paintEvent( QPaintEvent* e)
{

  if(c->chart_switch == OFF){

    drawGraphics_without_Chart();
  }

  if(c->chart_switch == ON){
    
    drawGraphics_with_Chart();
  }
   
}

//--------------------------------------------------------------------------//

void
QtWindow::drawGraphics_without_Chart(void)
{

    //-- Set Pixmap
    QPainter bufferpainter_g(&bufferpixmap_g); 
    QPainter bufferpainter_text(&bufferpixmap_text);  
    QPainter bufferpainter_button(&bufferpixmap_button);


    //-- Set Frame Backgroud Color 
    setBackgroundColor(gray);
    setBackgroundMode(NoBackground);

    bufferpixmap_g.fill(backgroundColor());
    
    setBackgroundColor(white);
    setBackgroundMode(NoBackground);

    bufferpixmap_text.fill(backgroundColor());
    bufferpixmap_button.fill(backgroundColor());


    //-- Draw Text to Pixmap 
    drawTxt(&bufferpainter_text);  


    //-- Arrengment of Frame Size and Transformation of Axes 
    changeCoordinate_Graphics(&bufferpainter_g);    

    
    //-- Paint: 
    //-- Draw to Pixmap    
    drawToPixmap_Graphics(&bufferpainter_g);  


    //-- Double Buffering
    //-- Text 
    bitBlt(this, 0,  0,
	   &bufferpixmap_text,  
	   0,  0, w->graphics_width, w->display_text_margin_y); 

    //-- Graphics 
    bitBlt(this, 0, w->display_text_margin_y, 
    	   &bufferpixmap_g, 
	   0,  0, w->graphics_width, w->graphics_height);  

    //-- Button
    bitBlt(this, 0,  w->display_text_margin_y + w->graphics_height,
	   &bufferpixmap_button,
	   0,  0, w->graphics_width, w->button_margin_y );

}

void
QtWindow::drawGraphics_with_Chart(void)
{
   
  //-- Set Pixmap
    QPainter bufferpainter_g(&bufferpixmap_g);  
    QPainter bufferpainter_c(&bufferpixmap_c);
    

    //-- Set Frame Backgroud Color 
    setBackgroundColor(gray);
    setBackgroundMode(NoBackground);
    
    bufferpixmap_g.fill(backgroundColor());

    setBackgroundColor(darkGray);
    setBackgroundMode(NoBackground);

    bufferpixmap_c.fill(backgroundColor());


    //-- Draw Text to Pixmap  
    drawTxt(&bufferpainter_c);  


    //-- Arrengment of Frame Size and Transformation of Axes 
    changeCoordinate_Graphics(&bufferpainter_g);    
    changeCoordinate_Chart(&bufferpainter_c);  

    
    //-- Paint: 
    //-- Draw to Pixmap
    drawToPixmap_Graphics(&bufferpainter_g);  
    drawToPixmap_Chart(&bufferpainter_c);
    

    //-- Reset Coodinate to Oringinal
    resetCoordinate(&bufferpainter_c);   


    //-- Draw Text to Chart
    drawTxtToChart(&bufferpainter_c);  


    //-- Double Buffering
    //-- Graphics 
    bitBlt(this, 0, 0,
	   &bufferpixmap_g, 
	   0,  0, w->graphics_width, w->graphics_height);  

    //-- Chart
    bitBlt(this, w->graphics_height, 0,
	   &bufferpixmap_c,
	   0,  0, w->chart_width, w->graphics_height);  

}

//--------------------------------------------------------------------------//

int 
QtWindow::transform_x(int x)
{

  int new_x = x;

  return new_x;

}

int 
QtWindow::transform_y(int y)
{

  int new_y;

  if(c->chart_switch == ON){
    new_y =  w->graphics_height - y;
  } 
  
  if(c->chart_switch == OFF){
    new_y =  w->graphics_height + w->display_text_margin_y + w->button_margin_y - y;
  }
 
  return new_y;

}

//--------------------------------------------------------------------------//

void 
QtWindow::drawTxt(QPainter *bp)
{

  //-- Draw Number of Moving Objects and Simulation Step
  //-- Original coordinate is used (before using changeCoordinate() ). 

  //-- Set Position of Text Box
  int  t_obj_x; 
  int  t_obj_y;
  int  t_step_x; 
  int  t_step_y;

  if(c->chart_switch == ON){
    t_obj_x  = 30; 
    t_obj_y  = 570; //= 20
    t_step_x = 130;
    t_step_y = 570; //= 20
  }

  if(c->chart_switch == OFF){
    t_obj_x  = 30; 
    t_obj_y  = 655; //= 20
    t_step_x = 130;
    t_step_y = 655; //= 20
  }
  

  char num_obj[100];  
  char step[100];  

  sprintf(num_obj,"object:%d",o->num_move); 
  sprintf(step,"step:%d",c->step);


  //-- Draw Number of Step
  bp->setPen(QPen(black, 1, QPen::SolidLine));    
  bp->setFont(QFont("times",20));//("NewRoman",20,QFont::Bold));
  
  bp->drawText(transform_x(t_obj_x),transform_y(t_obj_y),num_obj);  


 //-- Draw Number of Object
  bp->setPen(QPen(black, 1, QPen::SolidLine));  
  bp->setFont(QFont("times",20));//, QFont::Bold));

  bp->drawText(transform_x(t_step_x),transform_y(t_step_y),step);


}

void 
QtWindow::drawTxtToChart(QPainter *bp)
{
  
  //-- Draw Title to Chart 
  drawTitle(bp);

  
  //-- Draw Index to Chart 

  //-- Get Index of Chart
  get_O_Index();
  get_X_Index();
  get_Y_Index();

    
  //-- Draw Index 
  drawIndex(bp);

}

//--------------------------------------------------------------------------//

void 
QtWindow::drawTitle(QPainter *bp)
{

  int  c1_title_x = 30;
  int  c1_title_y = 520;

  int  c2_title_x = c1_title_x;
  int  c2_title_y = c1_title_y - chart_height - space_y;

  int  c3_title_x = c1_title_x;
  int  c3_title_y = c2_title_y - chart_height - space_y;

  bp->setPen(QPen(black, 1, QPen::SolidLine));  
  bp->setFont(QFont("times",14));//, QFont::Bold));

  bp->drawText(transform_x(c1_title_x),transform_y(c1_title_y),*factor_name[0][0]);  
  bp->drawText(transform_x(c2_title_x),transform_y(c2_title_y),*factor_name[1][0]);  
  bp->drawText(transform_x(c3_title_x),transform_y(c3_title_y),*factor_name[2][0]);  

}


void 
QtWindow::drawIndex(QPainter *bp)
{

  bp->setPen(QPen(black, 1, QPen::SolidLine));  
  bp->setFont(QFont("times",14));//, QFont::Bold));
  
  for(int chartID = 0; chartID < NUM_CHART; chartID++){
      
    bp->drawText(transform_x( o_index_x[chartID] ),    
		 transform_y( o_index_y[chartID] ),
		 o_index[chartID]);
  
    bp->drawText(transform_x( X_index_max_x[chartID]),
		 transform_y( X_index_max_y[chartID]),
		 X_index_max[chartID] );
  
    bp->drawText(transform_x( X_index_half_x[chartID]),
		 transform_y( X_index_half_y[chartID]),
		 X_index_half[chartID]);  
    
    bp->drawText(transform_x( Y_index_max_x[chartID] ),
		 transform_y( Y_index_max_y[chartID] ),
		 Y_index_max[chartID] );  

    bp->drawText(transform_x( Y_index_half_x[chartID]),
		 transform_y( Y_index_half_y[chartID]),
		 Y_index_half[chartID]);  
  }

}


//--------------------------------------------------------------------------//

void 
QtWindow::get_O_Index(void)
{

  for(int chartID = 0; chartID < NUM_CHART; chartID++){
    sprintf(o_index[chartID],"0"); 
  }

}

void 
QtWindow::get_X_Index(void)
{

  for(int chartID = 0; chartID < NUM_CHART; chartID++){    
    sprintf(X_index_max[chartID],"%d",max_x[chartID]);
    sprintf(X_index_half[chartID],"%d",(int)((double)max_x[chartID]/2));
  }

}

void 
QtWindow::get_Y_Index(void)
{
  
  for(int chartID = 0; chartID < NUM_CHART; chartID++){

    //--   
    if( max_y_processed[chartID] == 0.0){
      sprintf(Y_index_max[chartID],"%.1f",0);  
      sprintf(Y_index_half[chartID],"%.1f",0);
    }
    if( max_y_processed[chartID] <= 0.01){
      sprintf(Y_index_max[chartID],"%.4f",max_y_processed[chartID]);  
      sprintf(Y_index_half[chartID],"%.4f",max_y_processed[chartID]/2);
    }
    else if( 0.01   < max_y_processed[chartID] && max_y_processed[chartID] <= 0.1){ 
      sprintf(Y_index_max[chartID],"%.3f",max_y_processed[chartID]);
      sprintf(Y_index_half[chartID],"%.3f",max_y_processed[chartID]/2);
    }
    else if( 0.1    < max_y_processed[chartID] && max_y_processed[chartID] <= 2.0){
      sprintf(Y_index_max[chartID],"%.2f",max_y_processed[chartID]);
      sprintf(Y_index_half[chartID],"%.3f",max_y_processed[chartID]/2);
    }
    else{ 
      sprintf(Y_index_max[chartID], "%d",(int)max_y_processed[chartID]); 
      sprintf(Y_index_half[chartID],"%d",(int)(max_y_processed[chartID]/2));
    }

    /*
    if( 1.0    < max_y[chartID] && max_y[chartID] <= 10.0){
      sprintf(Y_index_max[chartID], "%5.1f",(double)( (int)max_y[chartID] + 1 ) ); 
      sprintf(Y_index_half[chartID],"%5.1f",(double)( ((int)max_y[chartID] + 1)/2 ) );
    }

    if( 10.0   < max_y[chartID] && max_y[chartID] <= 100.0){
      sprintf(Y_index_max[chartID], "%5d", (int)max_y[chartID]-(int)max_y[chartID]%10 + 10); 
      sprintf(Y_index_half[chartID],"%5d",((int)max_y[chartID]-(int)max_y[chartID]%10 + 10)/2 );
    }

    if( 100.0  < max_y[chartID] && max_y[chartID] <= 1000.0){
           
      sprintf(Y_index_max[chartID], "%5d", (int)max_y[chartID]-(int)max_y[chartID]%100 + 100); 
      sprintf(Y_index_half[chartID],"%5d",((int)max_y[chartID]-(int)max_y[chartID]%100 + 100)/2 );
    }

    if( 1000.0 < max_y[chartID] && max_y[chartID] <= 10000.0){   
      sprintf(Y_index_max[chartID], "%5d", (int)max_y[chartID]-(int)max_y[chartID]%1000 + 1000); 
      sprintf(Y_index_half[chartID],"%5d",((int)max_y[chartID]-(int)max_y[chartID]%1000 + 1000)/2 );
    }

    if( 10000.0   < max_y[chartID]){
      sprintf(Y_index_max[chartID], "%d", (int)max_y[chartID]-(int)max_y[chartID]%10000 + 10000); 
      sprintf(Y_index_half[chartID],"%d",((int)max_y[chartID]-(int)max_y[chartID]%10000 + 10000)/2 );
    }
    */



  }
  

}

//--------------------------------------------------------------------------//

void 
QtWindow::changeCoordinate_Graphics(QPainter *bp)
{
  
  //--  (Before) Draw Original x and y axes
  //bp->setPen(QPen(blue, 5, QPen::SolidLine));
  //bp->drawLine(0,0,100,0); 
  //bp->setPen(QPen(black, 5, QPen::SolidLine));
  //bp->drawLine(0,0,0,100);


  //-- Arrengment of Frame Size and Transformation of Axes 

  matrix_graphics = bp->worldMatrix();

  double ratio   = 1.0;

  double ratio_x = 1.0;  
  double ratio_y = 1.0;

  double dx = 15.0;    //-- Shift New Original Point X 
  double dy = -15.0;   //-- Shift New Original Point Y 


  //-- Extension of Size
  if(f->width < w->graphics_width - dx || f->height < w->graphics_height + dy){
    
    ratio_x = (w->graphics_width  - dx)/f->width;   
    ratio_y = (w->graphics_height + dy)/f->height;  

    if( ratio_x < ratio_y){
      ratio = ratio_x;
    }    
    else{
      ratio = ratio_y;
    }
  }
 

  //-- Reduction of Size  
  if(f->width > w->graphics_width || f->height > w->graphics_height){
    
    ratio_x = (w->graphics_width  - dx)/f->width;   
    ratio_y = (w->graphics_height + dy)/f->height;  

    if( ratio_x > ratio_y){
      ratio = ratio_x;
    }
    else{
      ratio = ratio_y;
    } 
  }
  //printf("ratio_x:%f ratio_y:%f\n", ratio_x,ratio_y );


  //-- Liner Transformation (x,y) -> (x, height - y)...Standard Axes

  matrix_graphics.setMatrix(1.0*ratio, 0.0, 0.0, -1.0*ratio, dx, dy+(double)w->graphics_height);
  bp->setWorldMatrix(matrix_graphics);

 

  //-- (After) Draw New x and y axes 
  //bp->setPen(QPen(blue, 8, QPen::SolidLine));
  //bp->drawLine(0,0,100,0); 
  //bp->setPen(QPen(black, 8, QPen::SolidLine));
  //bp->drawLine(0,0,0,100);

}

//--------------------------------------------------------------------------//

void 
QtWindow::changeCoordinate_Chart(QPainter *bp)
{
  
  //-- Liner Transformation (x,y) -> (x, height - y)...Standard Axes
  matrix_chart = bp->worldMatrix();
  matrix_chart .setMatrix(1.0, 0.0, 0.0, -1.0, 0, (double)w->graphics_height);
  bp->setWorldMatrix(matrix_chart );
 
}

//--------------------------------------------------------------------------//

void 
QtWindow::resetCoordinate(QPainter *bp)
{
    
  matrix_graphics.reset();  
  bp->setWorldMatrix(matrix_graphics); 

  matrix_chart.reset();  
  bp->setWorldMatrix(matrix_chart); 

}

//--------------------------------------------------------------------------//

void 
QtWindow::drawToPixmap_Graphics(QPainter *bp)
{

   //-- Draw Cross 
  drawCross(bp);


  //-- Draw Lines
  drawLine(bp);


  //-- Draw Objects
  drawObj(bp);  

}

void 
QtWindow::drawToPixmap_Chart(QPainter *bp)
{

  //-- Draw Chart
  drawChart(bp);

}

//--------------------------------------------------------------------------//

void QtWindow::drawLine(QPainter *bp)
{

  int s_x[g->num_arc];// start x -raw data
  int s_y[g->num_arc];// start y
  int e_x[g->num_arc];// end x
  int e_y[g->num_arc];// end y


  int x_s1[g->num_arc];// start x - for drawing two lanes 
  int y_s1[g->num_arc];// start y - for drawing two lanes 
  int x_e1[g->num_arc];// end x   - for drawing two lanes 
  int y_e1[g->num_arc];// end y   - for drawing two lanes 
  
  int x_s2[g->num_arc];// start x - for drawing two lanes 
  int y_s2[g->num_arc];// start y - for drawing two lanes 
  int x_e2[g->num_arc];// end x   - for drawing two lanes 
  int y_e2[g->num_arc];// end y   - for drawing two lanes 
  

  int    x_reduction[g->num_arc];
  int    y_reduction[g->num_arc];

  double reduction_ratio = 7.0;
  
  for(int arcID = 0; arcID < g->num_arc; arcID++){
  
    //-- Edge of Start
    s_x[arcID] = g->node[g->arc[arcID].start].x;
    s_y[arcID] = g->node[g->arc[arcID].start].y;
        

    //-- Edge of End   
    e_x[arcID] = g->node[g->arc[arcID].end].x;
    e_y[arcID] = g->node[g->arc[arcID].end].y;
    

    //-- Draw Two Lanes
    int   dx = e_x[arcID] - s_x[arcID];
    int   dy = e_y[arcID] - s_y[arcID];  

    double r = 3.0; //-- Shift Line to Draw Two Lanes     
    double hypotenuse = sqrt((double)dx*dx + (double)dy*dy);
    
    double double_x = r*(double)dy/hypotenuse;
    double double_y = r*(double)dx/hypotenuse; 
    int    int_x    = (int)(r*(double)dy/hypotenuse); 
    int    int_y    = (int)(r*(double)dx/hypotenuse); 

    int shift_x, shift_y;
 
    if (double_x - int_x > 0)
      shift_x = (int)(1.0 + r*(double)dy/hypotenuse); 
    else
      shift_x = (int)(r*(double)dy/hypotenuse); 

    if (double_y - int_y > 0)
      shift_y = (int)(1.0 + r*(double)dx/hypotenuse); 
    else
      shift_y = (int)(r*(double)dx/hypotenuse); 


    x_s1[arcID] = s_x[arcID] + shift_x;
    y_s1[arcID] = s_y[arcID] - shift_y;
    x_e1[arcID] = e_x[arcID] + shift_x;
    y_e1[arcID] = e_y[arcID] - shift_y;
   
    x_s2[arcID] = s_x[arcID] - shift_x;
    y_s2[arcID] = s_y[arcID] + shift_y;
    x_e2[arcID] = e_x[arcID] - shift_x;
    y_e2[arcID] = e_y[arcID] + shift_y;

    
    x_reduction[arcID] = (int)(reduction_ratio*(double)(x_e1[arcID] - x_s1[arcID])/hypotenuse);
    y_reduction[arcID] = (int)(reduction_ratio*(double)(y_e1[arcID] - y_s1[arcID])/hypotenuse);
  
  }
    
    //printf("shift_x = %d\n",shift_x);    
    //printf("shift_y = %d\n",shift_y);
    //printf("x:%4d -> x:%4d\t y:%4d -> y:%4d\n",s_x,x_s1,s_y,y_s1);
    //printf("x:%4d -> x:%4d\t y:%4d -> y:%4d\n\n",e_x,x_e1,e_y,y_e1);
  

  for(int arcID = 0; arcID < g->num_arc; arcID++){

    //-- Draw Two Lanes (LOWER) 
    bp->setPen(QPen(black, 7, QPen::SolidLine));
    bp->drawLine(x_s1[arcID], y_s1[arcID], x_e1[arcID], y_e1[arcID]);

    bp->setPen(QPen(black, 7, QPen::SolidLine));
    bp->drawLine(x_s2[arcID], y_s2[arcID], x_e2[arcID], y_e2[arcID]);
  
  }


  for(int arcID = 0; arcID < g->num_arc; arcID++){

    //-- Draw Two Lanes (UPPER) 
    bp->setPen(QPen(white, 5, QPen::SolidLine));
    bp->drawLine(x_s1[arcID], y_s1[arcID], x_e1[arcID], y_e1[arcID]);

    bp->setPen(QPen(white, 5, QPen::SolidLine));
    bp->drawLine(x_s2[arcID], y_s2[arcID], x_e2[arcID], y_e2[arcID]);


    //-- Draw Center Line  
    bp->setPen(QPen(white, 3, QPen::SolidLine));
    bp->drawLine(s_x[arcID], s_y[arcID], e_x[arcID], e_y[arcID]);
    
    bp->setPen(QPen(black, 1, QPen::DotLine));   
    bp->drawLine(s_x[arcID]+x_reduction[arcID], s_y[arcID]+y_reduction[arcID], 
		 e_x[arcID]-x_reduction[arcID], e_y[arcID]-y_reduction[arcID]);

  }
  
}

//--------------------------------------------------------------------------//

void QtWindow::drawCross(QPainter *bp)
{
  //-- Draw Cross
  bp->setBrush(QBrush(white,SolidPattern));
  bp->setPen(QPen(black, 1, QPen::SolidLine));   

  int shift_x = -5;  
  int shift_y = -5;

  for(int nodeID = 0; nodeID < g->num_node; nodeID++){
    bp->drawEllipse(g->node[nodeID].x+shift_x,g->node[nodeID].y+shift_y, 12,12);
  }
}

//--------------------------------------------------------------------------//

void QtWindow::drawObj(QPainter *bp)
{

  //-- Draw Objects
  
  for(int objID = 0; objID < o->num_move;objID++ ){
	
    /*
    if(o->move[objID].driving_status == STANDBY || 
       o->move[objID].driving_status == WAITING || 
       o->move[objID].driving_status == ARRIVAL){
      continue;
      }*/

    if(o->move[objID].driving_status != DRIVING){
      continue;
    }


    //int objID    = g->arc[arcID].block[sideID][blockID].block_move[block_objID];
    
    int arcID    = o->move[objID].arc;	  
    int sideID   = o->move[objID].side;
    int blockID  = o->move[objID].block;

    int num_block= g->arc[arcID].num_block;
    

    //-- Start Node and End Node of Object
    int start_node = g->arc[arcID].block_start_node[sideID];
    int end_node   = g->arc[arcID].block_end_node[sideID];
    
    
    //-- Position of Start Node and End Node 
    int s_x = g->node[start_node].x; 
    int s_y = g->node[start_node].y;   
    int e_x = g->node[end_node].x; 
    int e_y = g->node[end_node].y;
    
    //printf("arcID:%d s_x:%d s_x:%d e_x:%d e_y:%d\n",arcID,s_x,s_y,e_x,e_y);
    
    
    //-- Difference between Start Node and Current Position
    double x_from_start = ((double)e_x - (double)s_x)*o->move[objID].distance/g->arc[arcID].distance; 
    double y_from_start = ((double)e_y - (double)s_y)*o->move[objID].distance/g->arc[arcID].distance;     
    
    //-- Current Position
    int o_x = s_x + (int)x_from_start;
    int o_y = s_y + (int)y_from_start;
    
    
    //printf("o->move[objID].distance:%f g->arc[arcID].distance:%f x_from_start = %f\n",
    //	   o->move[objID].distance,g->arc[arcID].distance,x_from_start);  
    //printf("o->move[objID].distance:%f g->arc[arcID].distance:%f y_from_start = %f\n",
    //	   o->move[objID].distance,g->arc[arcID].distance,y_from_start);  

    
    //-- Decide Color of Object based on Velocity 
    /*
    int R, G, B;
    int max_c      = 255; 
    double vel     = o->move[objID].velocity;
    double max_vel = 14.0;
    
    if( vel < 3.0){
      bp->setBrush( QBrush(QColor(206,42,42),SolidPattern) );    
      bp->setPen(QPen(QColor(206,42,42), 1, QPen::SolidLine));
    }
    if( 3.0 <= vel && vel < 6.0){
      bp->setBrush( QBrush(QColor(216,46,119),SolidPattern) );    
      bp->setPen(QPen(QColor(216,46,119), 1, QPen::SolidLine));
    }
    if( 6.0 <= vel && vel < 9.0){
      bp->setBrush( QBrush(QColor(166,52,230),SolidPattern) );    
      bp->setPen(QPen(QColor(166,52,230), 1, QPen::SolidLine));
    }
    if( 9.0 <= vel && vel < 12.0){
      bp->setBrush( QBrush(QColor(49,80,233),SolidPattern) );    
      bp->setPen(QPen(QColor(49,80,233), 1, QPen::SolidLine));
    }
    if( 12.0 <= vel && vel < 14.0){
      bp->setBrush( QBrush(QColor(49,189,235),SolidPattern) );    
      bp->setPen(QPen(QColor(49,189,235), 1, QPen::SolidLine));
    }
    */


  //-- Decide Color of Object based on Gain
    //int R, G, B;
    //int max_c      = 255; 
    double gain    = o->move[objID].gain;
    //double max_vel = 140.0;
    
    if( gain < 30.0){
      bp->setBrush( QBrush(QColor(206,42,42),SolidPattern) );    
      bp->setPen(QPen(QColor(206,42,42), 1, QPen::SolidLine));
    }
    if( 30.0 <= gain && gain < 60.0){
      bp->setBrush( QBrush(QColor(216,46,119),SolidPattern) );    
      bp->setPen(QPen(QColor(216,46,119), 1, QPen::SolidLine));
    }
    if( 60.0 <= gain && gain < 90.0){
      bp->setBrush( QBrush(QColor(166,52,230),SolidPattern) );    
      bp->setPen(QPen(QColor(166,52,230), 1, QPen::SolidLine));
    }
    if( 90.0 <= gain && gain < 120.0){
      bp->setBrush( QBrush(QColor(49,80,233),SolidPattern) );    
      bp->setPen(QPen(QColor(49,80,233), 1, QPen::SolidLine));
    }
    if( 120.0 <= gain && gain < 140.0){
      bp->setBrush( QBrush(QColor(49,189,235),SolidPattern) );    
      bp->setPen(QPen(QColor(49,189,235), 1, QPen::SolidLine));
    }







    //G = (int)(vel/(double)max_vel * max_c); 
    //bp->setBrush( QBrush(QColor(255,G, 255),SolidPattern) );    
    //bp->setPen(QPen(QColor(255,G, 255), 2, QPen::SolidLine));

    //printf("Obj %2d in arc%2d side%d block%2d.\t",
    //	 objID,o->move[objID].arc,o->move[objID].side,o->move[objID].block);
    //printf("vel:%3f G:%d\n",vel,G);
    
    
    //-- Shift Position for Left-hand Traffic 
    
    int dx   = e_x - s_x;
    int dy   = e_y - s_y;
    
    double r = 3.0; //-- Shift Line to Draw Left-hand Traffic 
    double hypotenuse = sqrt((double)dx*dx + (double)dy*dy);
    
    int x_leftlane = (int)((double)o_x - r*(double)dy/hypotenuse);
    int y_leftlane = (int)((double)o_y + r*(double)dx/hypotenuse);  
    
    int shift_x    = -1;
    int shift_y    = -2;
   
      
    bp->drawEllipse(x_leftlane + shift_x, y_leftlane + shift_y, 5,5);
    //bp->drawEllipse(x_leftlane + shift_x-5, y_leftlane + shift_y-5, 15,15);
    

    if(objID%100 == 0){
      bp->setBrush(QBrush(green,SolidPattern));
      bp->setPen(QPen(darkGreen, 1, QPen::SolidLine));   
      bp->drawEllipse(x_leftlane + shift_x-5, y_leftlane + shift_y-5, 15,15);
    }
  
 
  }

}

//--------------------------------------------------------------------------//

void QtWindow::drawChart(QPainter *bp)
{
  
  //-- Draw Frame of Chart
  bp->setBrush(QBrush(white,SolidPattern));
  bp->setPen(QPen(white, 1, QPen::SolidLine));   

  bp->drawRect(c_x1, c_y1, chart_width, chart_height);
  bp->drawRect(c_x2, c_y2, chart_width, chart_height);
  bp->drawRect(c_x3, c_y3, chart_width, chart_height);


  int med_x;
  int med_y;
  int top_x; 
  int top_y;

  //-- Draw X & Y Axes of Chart 
  bp->setPen(QPen(darkGray, 1, QPen::SolidLine)); 


  //-- Chart 1
  //-- Draw X & Y Axes of Chart 1
  bp->drawLine(c_x1,o_y1,c_x1+chart_width,o_y1);              //-- X axis
  bp->drawLine(o_x1,c_y1,o_x1,c_y1+chart_height-title_margin);//-- Y axis
 
  //-- Draw Half Division  
  med_x = o_x1+(int)((double)(chart_width-original_margin_x)/2);  
  med_y = o_y1+(int)((double)(chart_height-original_margin_y-title_margin)/2);

  bp->drawLine(med_x,o_y1 -5, med_x, o_y1 +5);
  bp->drawLine(o_x1 -5, med_y, o_x1 +5, med_y);

  //-- Draw Max Division 
  top_x = o_x1 + chart_width - original_margin_x - 2; 
  top_y = o_y1 + chart_height - original_margin_y - title_margin;

  bp->drawLine(top_x,o_y1-5,top_x,o_y1+5);//-- on X axis
  bp->drawLine(o_x1-5,top_y,o_x1+5,top_y);//-- on Y axis

  

  //-- Chart 2  
  //-- Draw X & Y Axes of Chart 2
  bp->drawLine(c_x2,o_y2,c_x2+chart_width,o_y2);  
  bp->drawLine(o_x2,c_y2,o_x2,c_y2+chart_height-title_margin);

  //-- Draw Half Division  
  med_x = o_x2+(int)((double)(chart_width-original_margin_x)/2);  
  med_y = o_y2+(int)((double)(chart_height-original_margin_y-title_margin)/2);

  bp->drawLine(med_x,o_y2 -5, med_x, o_y2 +5);
  bp->drawLine(o_x2 -5, med_y, o_x2 +5, med_y);

  //-- Draw Max Division 
  top_x = o_x2 + chart_width - original_margin_x - 2; 
  top_y = o_y2 + chart_height - original_margin_y - title_margin;

  bp->drawLine(top_x,o_y2-5,top_x,o_y2+5);//-- on X axis
  bp->drawLine(o_x2-5,top_y,o_x2+5,top_y);//-- on Y axis



  //-- Chart 3  
  //-- Draw X & Y Axes of Chart 3
  bp->drawLine(c_x3,o_y3,c_x3+chart_width,o_y3);  
  bp->drawLine(o_x3,c_y3,o_x3,c_y3+chart_height-title_margin);

  //-- Draw Half Division  
  med_x = o_x3+(int)((double)(chart_width-original_margin_x)/2);  
  med_y = o_y3+(int)((double)(chart_height-original_margin_y-title_margin)/2);

  bp->drawLine(med_x,o_y3 -5, med_x, o_y3 +5);
  bp->drawLine(o_x3 -5, med_y, o_x3 +5, med_y);

  //-- Draw Max Division 
  top_x = o_x3 + chart_width - original_margin_x - 2; 
  top_y = o_y3 + chart_height - original_margin_y - title_margin;

  bp->drawLine(top_x,o_y3-5,top_x,o_y3+5);//-- on X axis
  bp->drawLine(o_x3-5,top_y,o_x3+5,top_y);//-- on Y axis


 
  //-- Draw Line in Chart 
  drawLineInChart(bp, 0, c_x1, c_y1, o_x1, o_y1);  
  drawLineInChart(bp, 1, c_x2, c_y2, o_x2, o_y2); 
  drawLineInChart(bp, 2, c_x3, c_y3, o_x3, o_y3);

}

void 
QtWindow::drawLineInChart(QPainter *bp,int chartID, int c_x, int c_y, int o_x, int o_y)
{

  int x[MAX_STEP];
  int y[MAX_STEP];
  

  //-- Update Max of Y Series
  if(c->step == 0){
    max_y_raw[chartID] = -9999999;
  }

  if( ch->chart_factor[chartID][0][c->step] > max_y_raw[chartID]){
    max_y_raw[chartID] = ch->chart_factor[chartID][0][c->step];
  }

  processMaxY(chartID, max_y_raw[chartID]);



  //-- Update Max of X Series
  double dx;    //-- Space for One Factor on X axis 
  int    first_phase  = 100;  
  int    second_phase = 100;
  
  if(c->step < first_phase){
    max_x[chartID] =  first_phase;
    dx             = (double)(chart_width-original_margin_x)/first_phase;
  }
  else{
    max_x[chartID] = c->step - (c->step%second_phase) + second_phase;
    dx             = (double)(chart_width-original_margin_x)/max_x[chartID];
  }

  
  //-- Updated Value for Drawing to Chart
  for(int stepID = 0; stepID < c->step; stepID++){
    x[stepID] = (int)(o_x + dx * stepID);

    if( c->step == 0 || max_y_raw[chartID]==0 ){  
      y[stepID] = o_y;  
    }
    else{
      y[stepID] = (int)(o_y +(chart_height - (o_y-c_y)-title_margin)
			*ch->chart_factor[chartID][0][stepID]/max_y_processed[chartID]);
    }

  }


  //-- Decide Color of Line 
  if(chartID == 0){
    bp->setPen(QPen(red,   1, QPen::SolidLine));   
  }  
  if(chartID == 1){
    bp->setPen(QPen(green, 1, QPen::SolidLine));   
  }
  if(chartID == 2){
    bp->setPen(QPen(blue,  1, QPen::SolidLine));   
  }
  

  //-- Draw Line with "bp->drawLine()"
  for(int stepID = 1; stepID < c->step; stepID++){
    bp->drawLine(x[stepID-1], y[stepID-1], x[stepID], y[stepID]);  
  }



  
}


void 
QtWindow::processMaxY(int chartID, double y)
{
  
  //--  
  if( y == 0){  
    max_y_processed[chartID] = y;
  }


  //--  
  if( y <= 10.0){  

    double temp       = y;
    double temp_half  = y/2; 
    int    count      = 0;

    if(temp!=0){
      while(temp_half < 10.0){
	temp_half *= 10.0;
	count++;
      }
    }

    temp_half = (double)((int)temp_half + 1);

    for(int i = 0;i<count;i++){
      temp_half *= 0.1;
    }

    temp = temp_half * 2.0;

    max_y_processed[chartID] = temp;

  }


  //--
  
  if( 10.0   < y && y <= 100.0){
  
    max_y_processed[chartID] = (double)( (int)y-(int)y%10 + 10 );
  }
  
  if( 100.0  < y && y <= 1000.0){
    
    max_y_processed[chartID] = (double)( (int)y- (int)y%100 + 100 );
  }
  
  if( 1000.0 < y && y <= 10000.0){   

    max_y_processed[chartID] = (double)( (int)y- (int)y%1000 + 1000 );
  }
  
  if( 10000.0   < y){

    max_y_processed[chartID] = (double)( (int)y- (int)y%10000 + 10000 );
  }
  

}




//--------------------------------------------------------------------------//
//Get Geographicaly Information from Class QtGraphics to This Class(QtWindow)

void 
QtWindow::getFrameInfo(struct FRAME_SIZE *ext_frame)
{ 
  //printf("in :getFrameInfo.\n");
  f = ext_frame;   
}

void 
QtWindow::getGeoInfo(struct GEO_INFO *ext_geo)
{ 
  //printf("in :getGeoInfo.\n");
  g = ext_geo;   
}

void 
QtWindow::getObjInfo(struct OBJECTS *ext_obj)
{ 
  //printf("in :getObjInfo.\n");
  o = ext_obj;  
}

void 
QtWindow::getCtlInfo(struct ITERATION_CONTROL *ext_ctl)
{ 
  //printf("in :getCtlInfo.\n");
  c = ext_ctl;  
}

void 
QtWindow::getMacroInfo(struct MACRO_PARAMETER *ext_macro)	
{ 
  //printf("in :getMacroInfo.\n");
  m = ext_macro;  
}

void 
QtWindow::getChartInfo(struct CHART *ext_chart)
{ 
  //printf("in :getCtlInfo.\n");
  ch = ext_chart;  
}

void 
QtWindow::getWindowInfo(struct WINDOW_SIZE *ext_window)
{ 
  //printf("in :getCtlInfo.\n");
  w = ext_window;  
}

//--------------------------------------------------------------------------//

void 
QtWindow::refillPixmap(void)
{
  update();
  
  //printf("refill\n");
}

//--------------------------------------------------------------------------//

void 
QtWindow::start_button()
{
 
  c->start =  TRUE; //1;
  
  //printf("in start:\t start  =%d\n",c->start);
}

void 
QtWindow::pause_button()
{
  
  if(c->pause == TRUE){
    c->pause = FALSE;//0;
  }else{
    c->pause = TRUE; //1;
  }

  //printf("in pause:\t pause  =%d\n",i.pause); 
  //printf("in pause:\t restart=%d\n",i.restart);
}

void 
QtWindow::restart_button()
{

  c->pause   = FALSE;//0;
  c->restart = TRUE; //1;  
  
  //printf("in restart:\t pause  =%d\n",i.pause); 
  //printf("in restart:\t restart=%d\n",i.restart);
}

void 
QtWindow::exit_button()
{

  c->exit = TRUE;//1;

  //printf("in exit:\t exit   =%d\n",c->exit);
}

//--------------------------------------------------------------------------//
//return button action to main function

int 
QtWindow::Check_start(void)
{ 
  //printf("in Check_start.\n");

  return c->start;
}

int 
QtWindow::Check_pause(void)
{ 
  //printf("in Check_pause.\n");

  return c->pause;
}

int 
QtWindow::Check_restart(void)
{ 
  //printf("in Check_restart.\n");

  return c->restart;
}

int 
QtWindow::Check_exit(void)
{ 
  //printf("in Check_exit.\n");

  return c->exit;
}

//--------------------------------------------------------------------------//

