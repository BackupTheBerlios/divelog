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

/**********************************************************************
* Filename : FillingStationVO.cpp                                     *
* CVS Id   : $Id: FillingStationVO.cpp,v 1.3 2002/06/02 09:55:13 grunwalm Exp $                                                     *
* ------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about fillingstations	*
*                    (Value Object)   																*
* Owner            : Markus Grunwald (MG)                             *
* Date of Creation : Thu Nov 22 2001                                  *
* ------------------------------------------------------------------- *
* To Do List :                                                        *
* ------------------------------------------------------------------- *
* Notes :                                                             *
**********************************************************************/
#include "FillingStationVO.h"

/*
|| Constructors
*/
FillingStationVO::FillingStationVO()
{
    init();
}

FillingStationVO::FillingStationVO( const FillingStationVO& fs )
{
    m_number       = fs.m_number;
    m_stationname  = fs.m_stationname;
    m_first_name   = fs.m_first_name;
    m_last_name    = fs.m_last_name;;
}

FillingStationVO::FillingStationVO( const unsigned int& number,
                                    const string& stationname,
                                    const string& first_name,
                                    const string& last_name )
{
    init( number, stationname, first_name, last_name );
}

void FillingStationVO::init( const unsigned int& number,
                             const string& stationname,
                             const string& first_name,
                             const string& last_name )
{
    m_number       = number;
    m_stationname  = stationname;
    m_first_name   = first_name;
    m_last_name    = last_name;
}

FillingStationVO& FillingStationVO::operator=( const FillingStationVO& fs )
{
    m_number       = fs.m_number;
    m_stationname  = fs.m_stationname;
    m_first_name   = fs.m_first_name;
    m_last_name    = fs.m_last_name;;
}

void FillingStationVO::init()
{
}

/*
|| Accessors
*/

unsigned int FillingStationVO::number() const
{
    return m_number;
}

string FillingStationVO::stationname() const
{
    return m_stationname;
}

string FillingStationVO::first_name() const
{
    return m_first_name;
}

string FillingStationVO::last_name() const
{
    return m_last_name;
}


void FillingStationVO::setNumber ( const unsigned int& number )
{
    m_number=number;
}

void FillingStationVO::setStationname( const string& stationname )
{
    m_stationname=stationname;
}

void FillingStationVO::setFirst_name( const string& first_name )
{
    m_first_name=first_name;
}

void FillingStationVO::setLast_name( const string& last_name )
{
    m_last_name=last_name;
}

