/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */
/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB */

/*************************************************************************
This file is part of divelog.

divelog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

divelog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with divelog; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

/******************************************************************************
* Filename : MyScrollBar.cpp                                                  *
* CVS Id 	 : $Id: MyScrollBar.cpp,v 1.15 2002/06/02 09:55:13 grunwalm Exp $     *
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
static const char *myscrollbar_cvs_id="$Id: MyScrollBar.cpp,v 1.15 2002/06/02 09:55:13 grunwalm Exp $";

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
