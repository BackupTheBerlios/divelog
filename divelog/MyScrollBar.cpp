/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.3 2001/09/10 18:44:54 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Enhance the QScrollBar                                   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : Provide some given methods as slots                            *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.3 2001/09/10 18:44:54 markus Exp $";

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

/*
|| Slots
*/

void MyScrollBar::setMinValue( int v )
{
    QScrollBar::setMinValue( v );
}

void MyScrollBar::setMaxValue( int v )
{
    QScrollBar::setMaxValue( v );
}

void MyScrollBar::setValue( int v )
{
    QScrollBar::setValue( v );
}
