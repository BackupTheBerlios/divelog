/******************************************************************************
* Filename : myscrollbar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.4 2001/09/11 17:34:31 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Enhance the QScrollBar                                   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : Provide some given methods as slots                            *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.4 2001/09/11 17:34:31 markus Exp $";

#include "myscrollbar.h"

MyScrollBar::MyScrollBar( QWidget *parent, const char *name=0 )
    : QScrollBar( parent, name )
{
    init();
}

MyScrollBar::MyScrollBar( Orientation o, QWidget *parent, const char *name=0 )
		: QScrollBar( o, parent, name )
{
    init();
}

MyScrollBar::MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep, int value, Orientation o, QWidget *parent, const char *name=0 )
		: QScrollBar( minValue, maxValue, LineStep, PageStep, value, o, parent, name )
{
    init();
}

MyScrollBar::MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep, int value, Orientation o, bool bFlip, QWidget *parent, const char *name=0 )
		: QScrollBar( minValue, maxValue, LineStep, PageStep, value, o, parent, name )
{
    init();
    m_flip=bFlip;
}

void MyScrollBar::init()
{
    m_flip=FALSE;

    // Just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    myscrollbar_cvs_id+=0;
}

void MyScrollBar::setFlip( bool flip )
{
    m_flip=flip;
    setValue( QScrollBar::value() );
}

bool MyScrollBar::flip() const
{
    return m_flip;
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
    int debug; // DEBUG

    if ( flip() )
    {
        debug=maxValue()-v+minValue();
        QScrollBar::setValue( maxValue()-v+minValue() );
    }
    else
    {
        QScrollBar::setValue( v );
    }
}

int MyScrollBar::value() const
{
    int debug; // DEBUG
    if ( flip() )
    {
        debug=maxValue()-QScrollBar::value()+minValue();
        return maxValue()-QScrollBar::value()+minValue();
    }

    return QScrollBar::value();
}


