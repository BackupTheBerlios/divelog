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
* Filename : DiverVO.cpp                                                      *
* CVS Id   : $Id: DiverVO.cpp,v 1.6 2002/09/16 17:08:11 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divers (Value Object)   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiverVO.h"


/*
|| Constructors
*/
DiverVO::DiverVO()
{
    init();
}

DiverVO::DiverVO( const DiverVO& d )
{
    m_number       = d.m_number;
    m_first_name   = d.m_first_name;
    m_last_name    = d.m_last_name;
    m_brevet       = d.m_brevet;
    m_street       = d.m_street;
    m_house_number = d.m_house_number;
    m_zip          = d.m_zip;
    m_place        = d.m_place;
    m_phone        = d.m_phone;
    m_email        = d.m_email;
}

DiverVO::DiverVO( const unsigned int& number, const QString& first_name, const QString& last_name, const QString& brevet,
                  const QString& street, const QString& house_number, const int& zip, const QString& place,
                  const QString& phone, const QString& email )
{
    init( number, first_name, last_name, brevet, street,
          house_number, zip, place, phone, email);
}

void DiverVO::init( const unsigned int& number, const QString& first_name, const QString& last_name, const QString& brevet,
    			 const QString& street, const QString& house_number, const int& zip, const QString& place,
    			 const QString& phone, const QString& email )
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
}

DiverVO& DiverVO::operator=( const DiverVO& d )
{
    m_number       = d.m_number;
    m_first_name   = d.m_first_name;
    m_last_name    = d.m_last_name;
    m_brevet       = d.m_brevet;
    m_street       = d.m_street;
    m_house_number = d.m_house_number;
    m_zip          = d.m_zip;
    m_place        = d.m_place;
    m_phone        = d.m_phone;
    m_email        = d.m_email;

    return *this;
}

void DiverVO::init()
{
}

/*
|| Accessors
*/

unsigned int DiverVO::number() const
{
    return m_number;
}

QString DiverVO::first_name() const
{
    return m_first_name;
}

QString DiverVO::last_name() const
{
    return m_last_name;
}

QString DiverVO::brevet() const
{
    return m_brevet;
}

QString DiverVO::street() const
{
    return m_street;
}

QString DiverVO::house_number() const
{
    return m_house_number;
}

int 	 DiverVO::zip() const
{
    return m_zip;
}

QString DiverVO::place() const
{
    return m_place;
}

QString DiverVO::phone() const
{
    return m_phone;
}

QString DiverVO::email() const
{
    return m_email;
}



void DiverVO::number ( const unsigned int& number )
{
    m_number=number;
}

void DiverVO::first_name ( const QString& first_name )
{
    m_first_name=first_name;
}

void DiverVO::last_name ( const QString& last_name )
{
    m_last_name=last_name;
}

void DiverVO::brevet ( const QString& brevet )
{
    m_brevet=brevet;
}

void DiverVO::street ( const QString& street )
{
    m_street=street;
}

void DiverVO::house_number( const QString& house_number )
{
    m_house_number=house_number;
}

void DiverVO::zip	( const int& zip )
{
    m_zip=zip;
}

void DiverVO::place	( const QString& place )
{
    m_place=place;
}

void DiverVO::phone ( const QString& phone )
{
    m_phone=phone;
}

void DiverVO::email	( const QString& email )
{
    m_email=email;
}

