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

#ifndef DIVERVO_H
#define DIVERVO_H
/******************************************************************************
* Filename : DiverVO.h                                                        *
* CVS Id   : $Id: DiverVO.h,v 1.6 2002/06/02 09:55:13 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiverVO.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiverVO
{
public:
    /*
    || Constructors
    */
    DiverVO();
    DiverVO( const DiverVO& d );
    DiverVO( const unsigned int& number,
             const string& first_name,
             const string& last_name,
             const string& brevet,
             const string& street,
             const string& house_number,
             const int& zip,
             const string& place,
             const string& phone,
             const string& email );

    void init( const unsigned int& number,
               const string& first_name,
               const string& last_name,
               const string& brevet,
               const string& street,
               const string& house_number,
               const int& zip,
               const string& place,
               const string& phone,
               const string& email );

    /*
    || Accessors
    */

    unsigned int number() const;
    string first_name() const;
    string last_name() const;
    string brevet() const;
    string street() const;
    string house_number() const;
    int 	 zip() const;
    string place() const;
    string phone() const;
    string email() const;

    void setNumber ( const unsigned int& number );
    void setFirst_name ( const string& first_name );
    void setLast_name ( const string& last_name );
    void setBrevet ( const string& brevet );
    void setStreet ( const string& street );
    void setHouse_number( const string& house_number );
    void setZip	( const int& zip );
    void setPlace	( const string& place );
    void setPhone ( const string& phone );
    void setEmail	( const string& email );

    /*
    || Operators
    */

    DiverVO& operator=( const DiverVO& d );


private:
    void init();

    unsigned int m_number;
    string m_first_name;
    string m_last_name;
    string m_brevet;
    string m_street;
    string m_house_number;
    int m_zip;
    string m_place;
    string m_phone;
    string m_email;
};


#endif
