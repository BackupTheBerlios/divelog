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
* CVS Id   : $Id: DiveListVO.h,v 1.3 2002/06/02 09:55:13 grunwalm Exp $         *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveListVO.cpp                           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Mon Mar 18 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveListVO
{
public:
    /*
    || Constructors
    */
    DiveListVO();
    DiveListVO( const DiveListVO& d );
    DiveListVO( const int&    number,
                const string& date,  // DATETIME split up
                const string& time,
                const int&    diver_number,
                const string& place,
                const string& location );

    void init( const int&    number,
               const string& date,  // DATETIME split up
               const string& time,
               const int&    diver_number,
               const string& place,
               const string& location );

    /*
    || Accessors
    */
    void setNumber( const int& number );
    void setDate( const string& date );
    void setTime( const string& time );
    void setDiver_number( const int& diver_number );
    void setPlace( const string& place );
    void setLocation( const string& location );

    int    number() const 								{ return m_number; }
    string date() const   								{ return m_date; }
    string time() const   								{ return m_time; }
    int    diver_number() const 					{ return m_diver_number; }
    string place() const  								{ return m_place; }
    string location() const 							{ return m_location; }

    /*
    || Operators
    */

    DiveListVO& operator=( const DiveListVO& d );


private:
    void init();

    int    m_number;
    string m_date;  // DATETIME split up
    string m_time;
    int    m_diver_number;
    string m_place;
    string m_location;
};


#endif
