/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.9 2001/10/04 21:03:17 markus Exp $      *
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
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.9 2001/10/04 21:03:17 markus Exp $";

#undef DEBUG
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
|| mostly only calls to father-class
*/

void MyScrollBar::setMinValue( int min )
{
    QScrollBar::setMinValue( min );
    qDebug( "SLOT %s->setMinValue( %i )", this->name(), min );
}

void MyScrollBar::setMaxValue( int max )
// only adding bounds
{
    if ( value()>max )
    {
        setValue( max );
    }
    QScrollBar::setMaxValue( max );
    qDebug( "SLOT %s->setMaxValue( %i )", this->name(), max );
}

void MyScrollBar::setValue( int v )
// only adding bounds
{
    if ( v>maxValue() )
    {
        v=maxValue();
    }
    QScrollBar::setValue( v );
    qDebug( "SLOT %s->setValue( %i )", this->name(), v );
}
