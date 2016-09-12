#include <qapplication.h>
#include <qwidget.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qfont.h>
#include <qmultilineedit.h>
#include <qscrollview.h>
#include <qstring.h>
#include <qpixmap.h>

#include "extvar.h"



class QtCtlPanel : public QWidget
{
  Q_OBJECT
    
 public:
        QtCtlPanel();
        ~QtCtlPanel();
  
        ITERATION_CONTROL i;
       
	//ITERATION_CONTROL* Check_Iteration(void);      

	//void getGeoInfo(struct GEO_INFO *geo);	
	//void getObjInfo(struct OBJECTS  *obj);

	int  Check_start(void);
	int  Check_pause(void);
	int  Check_restart(void);
	int  Check_exit(void);

        GEO_INFO *g; 
	OBJECTS  *o;

 private:
        //void paintEvent( QPaintEvent* );
	
	//QPainter *paint;
	//QPainter bufferpainter;
	//QPixmap bufferpixmap;

	QPushButton *b1;
	QPushButton *b2;
	QPushButton *b3;
	QPushButton *b4;
	

 public slots:
        void start_button();  
        void pause_button();
        void restart_button(); 
	void exit_button();
};

