/* Copyright 2002 Markus Grunwald */
/* All other Copyrights (especially Qt and mysql) belong to their owners */

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
* Filename : DiveListVO.cpp                                                   *
* CVS Id   : $Id: DiveListVO.cpp,v 1.2 2002/05/15 09:27:51 grunwalm Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : This is a "little" DiveVO value object. Is holds only    *
*                    Data, that is required for building up the selection     *
*                    list.                                                    *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Feb 14 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes : Don't like the idea of two structures for the same data... but I    *
*         had no better idea until now.                                       *
******************************************************************************/
#include "DiveListVO.h"

/*
|| Constructors
*/
DiveListVO::DiveListVO()
// -------------------------------------------------
// Use : Create an empty Dive Profile Value Object
//       Mostly useless, may vanish some time.
// -------------------------------------------------
{
}

DiveListVO::DiveListVO( const DiveListVO& d )
// -------------------------------------------------
// Use : Copy Constructor for Dive Profile Value Object
// Parameters  : d - the source object
// -------------------------------------------------
{
    (*this)= d ;
}

DiveListVO::DiveListVO( const int&    number,
                        const string& date,  // DATETIME split up
                        const string& time,
                        const int&    diver_number,
                        const string& place,
                        const string& location )
{
    init( number,  date, time, diver_number, place, location );
}

void DiveListVO::init( const int&    number,
                  const string& date,  // DATETIME split up
                  const string& time,
                  const int&    diver_number,
                  const string& place,
                  const string& location )
{
    m_number=number;
    m_date=date;  // DATETIME split up
    m_time=time;
    m_diver_number=diver_number;
    m_place=place;
    m_location=location;
}

void DiveListVO::init()
// -------------------------------------------------
// Use : general initialisation
// -------------------------------------------------
{
}

DiveListVO& DiveListVO::operator=( const DiveListVO& d )
// -------------------------------------------------
// Use : Copy operator
// -------------------------------------------------
{
    m_number=d.m_number;
    m_date=d.m_date;  // DATETIME split up
    m_time=d.m_time;
    m_diver_number=d.m_diver_number;
    m_place=d.m_place;
    m_location=d.m_location;

    return *this;
}


/*
|| Accessors
*/

// All in header file