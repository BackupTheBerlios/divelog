/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.2 2001/09/10 16:21:29 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Enhance the QScrollBar                                   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : Provide some given methods as slots                            *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.2 2001/09/10 16:21:29 markus Exp $";

#include "myscrollbar.h"

MyScrollBar::MyScrollBar( QWidget *parent, const char *name=0 )
    : QScrollBar( parent, name )
{
}

MyScrollBar::MyScrollBar( Orientation o, QWidget *parent, const char *name=0 )
		: QScrollBar( o, parent, name )
{
}

MyScrollBar::MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep, int value, Orientation o, QWidget *parent, const char *name=0 )
		: QScrollBar( minValue, maxValue, LineStep, PageStep, value, o, parent, name )
{
}

void MyScrollBar::init()
{
    // Just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    myscrollbar_cvs_id+=0;
}