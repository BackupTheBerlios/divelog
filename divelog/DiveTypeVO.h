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

#ifndef DIVETYPE_H
#define DIVETYPE_H
/******************************************************************************
* Filename : DiveTypeVO.h                                                     *
* CVS Id   : $Id: DiveTypeVO.h,v 1.3 2002/06/02 09:55:13 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveTypeVO.cpp                           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveTypeVO
{
public:
    /*
    || Constructors
    */
    DiveTypeVO();
    DiveTypeVO( const DiveTypeVO& fs );
    DiveTypeVO( const unsigned int& number,
    						const string& description
    					);

    void init( const unsigned int& number,
    					 const string& description
             );

    /*
    || Accessors
    */

    unsigned int number() const;
    string description() const;

    void setNumber ( const unsigned int& number );
    void setDescription( const string& description );

    /*
    || Operators
    */

    DiveTypeVO& operator=( const DiveTypeVO& diveType );


private:
    void init();

    unsigned int m_number;
    string 			 m_description;

};

#endif
