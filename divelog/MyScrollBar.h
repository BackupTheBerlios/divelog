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

#ifndef MYSCROLLBAR_H
#define MYSCROLLBAR_H
/******************************************************************************
* Filename : myscrollbar.h                                                    *
* CVS Id 	 : $Id: MyScrollBar.h,v 1.9 2002/06/02 09:55:13 grunwalm Exp $        *
* --------------------------------------------------------------------------- *
* Files subject    : Header for myscrollbar.cpp                               *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sat Sep 08 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Use #includes sparingly (see qt-tutorial) !                         *
******************************************************************************/

#include <qscrollbar.h>

class MyScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    /*
    || Constructors
    */
    MyScrollBar( QWidget *parent, const char *name=0 );
    MyScrollBar( Orientation, QWidget *parent, const char *name=0 );
    MyScrollBar( int minValue, int maxValue, int LineStep, int PageStep,
                 int value, Orientation,
                 QWidget *parent, const char *name=0 );

public slots:

    void setValue( int );
    void setMinValue( int );
    void setMaxValue( int );

private:
    void init();
};

#endif // MYSCROLLBAR_H
