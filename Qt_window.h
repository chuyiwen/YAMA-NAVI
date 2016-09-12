/*-*-c++-*-*/
//
//  Qt_window.h
//
//  Header file for Qt_window.cpp
//

#ifndef Qt_WINDOW_H
#define Qt_WINDOW_H

#include <qapplication.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qmultilineedit.h>
#include <qscrollview.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qwmatrix.h>
#include <qcolor.h>

#include <math.h>

#include "extvar.h"



class QtWindow : public QWidget
{
  Q_OBJECT
    
 public:
        QtWindow();
        ~QtWindow();
    
        void initializeButton(void);     
        void initializeChart(void);

        void initializeTitleChart(void);
        void initializeChartPosition(void);
        void initializeIndexPosition(void);    

	void getFrameInfo(struct FRAME_SIZE *frame);	
	void getGeoInfo(struct GEO_INFO *geo);	
	void getObjInfo(struct OBJECTS  *obj);
        void getCtlInfo(struct ITERATION_CONTROL *ext_ctl);     
        void getMacroInfo(struct  MACRO_PARAMETER *macro);    
        void getChartInfo(struct CHART *ext_chart);        
        void getWindowInfo(struct WINDOW_SIZE *ext_window);
	
	void refillPixmap(void);

	int  Check_start(void);
	int  Check_pause(void);
	int  Check_restart(void);
	int  Check_exit(void);

        void updateChartData(void);
        void storeData(int chartID);

	QPixmap  bufferpixmap_g;		
        QPixmap  bufferpixmap_c;	
        QPixmap  bufferpixmap_text;		
        QPixmap  bufferpixmap_button;
	
        QWMatrix matrix_graphics;   
        QWMatrix matrix_chart;  

	FRAME_SIZE        *f;
        GEO_INFO          *g; 
	OBJECTS           *o;	
        ITERATION_CONTROL *c;  
        MACRO_PARAMETER   *m;
        CHART             *ch;
        WINDOW_SIZE       *w;


        char   *factor_name[NUM_CHART][MAX_CHART_FACTOR][100];
  
        double max_y_raw[NUM_CHART];        
        double max_y_processed[NUM_CHART]; 
        int    max_x[NUM_CHART];        
      
        int    chart_width;   //-- Width of Chart ...x
        int    chart_height;  //-- Height of Chart ...y
        int    space_y;       //-- Space between Charts...y
        int    title_margin;  //-- Margin for Chart Title...y
  
        int    original_margin_x; //-- Distance from Left Edge of Chart to Oringial Point X  
        int    original_margin_y; //-- Distance from Lower Edge of Chart to Oringial Point Y  
  
        int    c_x1; //-- Position x of Left Bottom in Chart 1
        int    c_y1; //-- Position y of Left Bottom in Chart 1 
        int    c_x2;
        int    c_y2;
        int    c_x3;
        int    c_y3;
 
  //int    o_x[NUM_CHART]; //-- Position x of Original Point in Chart 1
  //int    o_y[NUM_CHART]; //-- Position y of Original Point in Chart 1 

        int    o_x1; //-- Position x of Original Point in Chart 1
        int    o_y1; //-- Position y of Original Point in Chart 1   
        int    o_x2; //-- Position x of Original Point in Chart 1
        int    o_y2; //-- Position y of Original Point in Chart 1         
        int    o_x3; //-- Position x of Original Point in Chart 1
        int    o_y3; //-- Position y of Original Point in Chart 1 
    
        int    o_index_x[NUM_CHART];  //-- Position x of Index of Original Point  
        int    o_index_y[NUM_CHART];  //-- Position y of Index of Original Point  

        int    X_index_max_x[NUM_CHART];  //-- Position x of First Index of X axis  
        int    X_index_max_y[NUM_CHART];  //-- Position y of First Index of X axis  

        int    X_index_half_x[NUM_CHART]; //-- Position x of Second Index of X axis  
        int    X_index_half_y[NUM_CHART]; //-- Position y of Second Index of X axis  

        int    Y_index_max_x[NUM_CHART];  //-- Position x of First Index of Y axis 
        int    Y_index_max_y[NUM_CHART];  //-- Position y of First Index of Y axis   

        int    Y_index_half_x[NUM_CHART]; //-- Position x of Second Index of Y axis  
        int    Y_index_half_y[NUM_CHART]; //-- Position y of Second Index of Y axis  

        char   o_index[NUM_CHART][100]; 
        char   X_index_max[NUM_CHART][100]; 
        char   X_index_half[NUM_CHART][100];
        char   Y_index_max[NUM_CHART][100]; 
        char   Y_index_half[NUM_CHART][100];


private:
        void resizeEvent( QResizeEvent* );  
	void paintEvent( QPaintEvent* e);

        void drawGraphics_without_Chart(void);
        void drawGraphics_with_Chart(void);
  
	int  transform_x(int);	
        int  transform_y(int);
  
	void changeCoordinate_Graphics(QPainter *bufferpainter);	
	void changeCoordinate_Chart(QPainter *bufferpainter);	
        void resetCoordinate(QPainter *bufferpainter);
	
        void drawToPixmap_Graphics(QPainter *bufferpainter);        
        void drawToPixmap_Chart(QPainter *bufferpainter);

	void drawLine(QPainter *bufferpainter);
	void drawCross(QPainter *bufferpainter);
	void drawObj(QPainter *bufferpainter);	

        void drawChart(QPainter *bufferpainter); 
        void drawLineInChart(QPainter *bufferpainter, int chartID, int c_x, int c_y, int o_x, int o_y);
  
        void drawTxt(QPainter *bufferpainter);
        
        void drawTxtToChart(QPainter *bufferpainter);  
        void drawTitle(QPainter *bufferpainter);	     
        void drawIndex(QPainter *bufferpainter);

        void get_O_Index(void);
        void get_X_Index(void);
        void get_Y_Index(void);
       
        void processMaxY(int chartID,double y);
  
	QPushButton *b1;
	QPushButton *b2;
	QPushButton *b3;
        QPushButton *b4;
	
public slots:
	void start_button();  
	void pause_button();	
        void exit_button();
        void restart_button(); 
};


#endif //Qt_WINDOW_H
