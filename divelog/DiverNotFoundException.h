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

/**********************************************************************************
* Filename : DiverNotFoundException.h																					    *
* CVS Id   : $Id: DiverNotFoundException.h,v 1.5 2002/08/10 18:15:44 grunwalm Exp $ *
* ------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecomputer couldn't    *
*                    be identified.                                               *
* Owner            : Markus Grunwald                                              *
* Date of Creation : Thu Nov 15 2001                                              *
* ------------------------------------------------------------------------------- *
* To Do List : Just incapsulate (inherit?) a DiverVO ...                          *
* ------------------------------------------------------------------------------- *
* Notes :                                                                         *
**********************************************************************************/
#ifndef DIVER_NOT_FOUND_EXCEPTION
#define DIVER_NOT_FOUND_EXCEPTION

#include "DiverVO.h"
#include "DivelogDAOException.h"
#include <string>
#include <iostream>


class DiverNotFoundException : public DivelogDAOException
{
public:
    
    DiverNotFoundException( const unsigned int& number=0,
                            const string& first_name="",
                            const string& last_name="",
                            const string& brevet="",
                            const string& street="",
                            const string& house_number="",
                            const int& zip=0,
                            const string& place="",
                            const string& phone="",
                            const string& email="" );

    DiverNotFoundException( const DiverVO& diver );
    ~DiverNotFoundException() throw() {};

    friend ostream& operator << (ostream& os, const DiverNotFoundException e);

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

private:

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
