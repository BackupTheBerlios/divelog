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
* CVS Id   : $Id: DiverNotFoundException.h,v 1.6 2002/09/16 17:08:11 grunwalm Exp $ *
* ------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecomputer couldn't    *
*                    be identified.                                               *
* Owner            : Markus Grunwald                                              *
* Date of Creation : Thu Nov 15 2001                                              *
* ------------------------------------------------------------------------------- *
* To Do List : Just incapsulate (inherit?) a DiverSO ...                          *
* ------------------------------------------------------------------------------- *
* Notes :                                                                         *
**********************************************************************************/
#ifndef DIVER_NOT_FOUND_EXCEPTION
#define DIVER_NOT_FOUND_EXCEPTION

#include "DiverSO.h"
#include "DivelogDAOException.h"
#include <qstring.h>
#include <iostream>


class DiverNotFoundException : public DivelogDAOException
{
public:
    
    DiverNotFoundException( const unsigned int& number=0,
                            const QString& first_name="",
                            const QString& last_name="",
                            const QString& brevet="",
                            const QString& street="",
                            const QString& house_number="",
                            const int& zip=0,
                            const QString& place="",
                            const QString& phone="",
                            const QString& email="" );

    DiverNotFoundException( const DiverSO& diver );
    ~DiverNotFoundException() throw() {};

    friend ostream& operator << (ostream& os, const DiverNotFoundException e);

    unsigned int number() const;
    QString first_name() const;
    QString last_name() const;
    QString brevet() const;
    QString street() const;
    QString house_number() const;
    int 	 zip() const;
    QString place() const;
    QString phone() const;
    QString email() const;

private:

    unsigned int m_number;
    QString m_first_name;
    QString m_last_name;
    QString m_brevet;
    QString m_street;
    QString m_house_number;
    int m_zip;
    QString m_place;
    QString m_phone;
    QString m_email;
};

#endif
