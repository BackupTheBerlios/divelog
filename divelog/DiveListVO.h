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

#ifndef DIVELISTVO_H
#define DIVELISTVO_H
/******************************************************************************
* Filename : DiveListVO.h                                                     *
* CVS Id   : $Id: DiveListVO.h,v 1.4 2002/09/16 17:08:11 grunwalm Exp $         *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveListVO.cpp                           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Mon Mar 18 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <qstring.h>

class DiveListVO
{
public:
    /*
    || Constructors
    */
    DiveListVO();
    DiveListVO( const DiveListVO& d );
    DiveListVO( const int&    number,
                const QString& date,  // DATETIME split up
                const QString& time,
                const int&    diver_number,
                const QString& place,
                const QString& location );

    void init( const int&    number,
               const QString& date,  // DATETIME split up
               const QString& time,
               const int&    diver_number,
               const QString& place,
               const QString& location );

    /*
    || Accessors
    */
    void number( const int& number );
    void date( const QString& date );
    void time( const QString& time );
    void diver_number( const int& diver_number );
    void place( const QString& place );
    void location( const QString& location );

    int    number() const 								{ return m_number; }
    QString date() const   								{ return m_date; }
    QString time() const   								{ return m_time; }
    int    diver_number() const 					{ return m_diver_number; }
    QString place() const  								{ return m_place; }
    QString location() const 							{ return m_location; }

    /*
    || Operators
    */

    DiveListVO& operator=( const DiveListVO& d );


private:
    void init();

    int    m_number;
    QString m_date;  // DATETIME split up
    QString m_time;
    int    m_diver_number;
    QString m_place;
    QString m_location;
};


#endif
