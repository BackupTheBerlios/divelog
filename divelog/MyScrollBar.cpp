/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.12 2001/11/19 19:42:05 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : QScrollBar has (nearly?) no slots. We implement some     *
*                    more to make it more usefull.                            *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.12 2001/11/19 19:42:05 markus Exp $";

#include "MyScrollBar.h"

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
|| mostly only calls to father-class
*/

void MyScrollBar::setMinValue( int min )
{
    QScrollBar::setMinValue( min );
}

void MyScrollBar::setMaxValue( int max )
// only adding bounds
{
    if ( value()>max )
    {
        setValue( max );
    }
    QScrollBar::setMaxValue( max );
}

void MyScrollBar::setValue( int v )
// only adding bounds
{
    if ( v>maxValue() )
    {
        v=maxValue();
    }
    QScrollBar::setValue( v );
}
