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

/************************************************************************************
* Filename : DiverNotFoundException.cpp																              *
* CVS Id   : $Id: DiverNotFoundException.cpp,v 1.5 2002/09/16 17:08:11 grunwalm Exp $ *
* --------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecr couldn't            *
*                    be identified.                                                 *
* Owner            : Markus Grunwald                                                *
* Date of Creation : Thu Nov 15 2001                                                *
* --------------------------------------------------------------------------------- *
* To Do List :  Just incapsulate (inherit?) a DiverVO ...                           *
* --------------------------------------------------------------------------------- *
* Notes :                                                                           *
*************************************************************************************/
static char DiverNotFoundException_cvs_id[]="$Id: DiverNotFoundException.cpp,v 1.5 2002/09/16 17:08:11 grunwalm Exp $";

#include "DiverNotFoundException.h"
#include "DivelogDAOException.h"
#include "DiverVO.h"
#include <iostream>
                                               
DiverNotFoundException::DiverNotFoundException( const unsigned int& number=0,
                                                const QString& first_name="",
                                                const QString& last_name="",
                                                const QString& brevet="",
                                                const QString& street="",
                                                const QString& house_number="",
                                                const int& zip=0,
                                                const QString& place="",
                                                const QString& phone="",
                                                const QString& email="" )
: DivelogDAOException()
{
    m_number       = number;
    m_first_name   = first_name;
    m_last_name    = last_name;
    m_brevet       = brevet;
    m_street       = street;
    m_house_number = house_number;
    m_zip          = zip;
    m_place        = place;
    m_phone        = phone;
    m_email        = email;

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DiverNotFoundException_cvs_id[0]+=0;
}

DiverNotFoundException::DiverNotFoundException( const DiverSO& diver )
: DivelogDAOException()
{
    m_number       = diver.number();
    m_first_name   = diver.first_name();
    m_last_name    = diver.last_name();
    m_brevet       = diver.brevet();
    m_street       = diver.street();
    m_house_number = diver.house_number();
    m_zip          = diver.zip();
    m_place        = diver.place();
    m_phone        = diver.phone();
    m_email        = diver.email();
}

unsigned int DiverNotFoundException::number() const
{
    return m_number;
}

QString DiverNotFoundException::first_name() const
{
    return m_first_name;
}

QString DiverNotFoundException::last_name() const
{
    return m_last_name;
}

QString DiverNotFoundException::brevet() const
{
    return m_brevet;
}

QString DiverNotFoundException::street() const
{
    return m_street;
}

QString DiverNotFoundException::house_number() const
{
    return m_house_number;
}

int 	 DiverNotFoundException::zip() const
{
    return m_zip;
}

QString DiverNotFoundException::place() const
{
    return m_place;
}

QString DiverNotFoundException::phone() const
{
    return m_phone;
}

QString DiverNotFoundException::email() const
{
    return m_email;
}


ostream& operator << (ostream& os, const DiverNotFoundException e)
{
    os << "DiverNotFoundException:" << endl;

    if ( e.m_number==0 )
    {
        os << "\tNo diver found!";
    }
    else
    {
        os << "\tnumber       : " << e.m_number << endl
           << "\tfirst_name   : " << e.m_first_name.latin1() << endl
           << "\tlast_name    : " << e.m_last_name.latin1() << endl
           << "\tbrevet       : " << e.m_brevet.latin1() << endl
           << "\tstreet       : " << e.m_street.latin1() << endl
           << "\thouse_number : " << e.m_house_number.latin1() << endl
           << "\tzip          : " << e.m_zip << endl
           << "\tplace        : " << e.m_place.latin1() << endl
           << "\tphone        : " << e.m_phone.latin1() << endl
           << "\temail        : " << e.m_email.latin1();
    }
    os << endl;
    return os;
}

