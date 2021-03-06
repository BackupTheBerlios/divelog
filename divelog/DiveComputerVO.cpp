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

/*****************************************************************************
* Filename : DiveComputerVO.cpp                                              *
* CVS Id   : $Id: DiveComputerVO.cpp,v 1.5 2002/09/16 17:08:11 grunwalm Exp $*
* -------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divecomputers 	       *
*                    (Value Object)   																       *
* Owner            : Markus Grunwald (MG)                                    *
* Date of Creation : Thu Nov 22 2001                                         *
* -------------------------------------------------------------------------- *
* To Do List :                                                               *
* -------------------------------------------------------------------------- *
* Notes :                                                                    *
*****************************************************************************/
#include "DiveComputerVO.h"

/*
|| Constructors
*/
DiveComputerVO::DiveComputerVO()
{
    init();
}
                  
DiveComputerVO::DiveComputerVO( const DiveComputerVO& diveComputer )
{
    m_serial_number = diveComputer.m_serial_number;
    m_diver_number  = diveComputer.m_diver_number;
    m_name   				= diveComputer.m_name;
}

DiveComputerVO::DiveComputerVO( const QString& serial_number,
																const unsigned int& diver_number,
                    						const QString& name)
{
    init( serial_number, diver_number, name );
}

void DiveComputerVO::init( const QString& serial_number,
													 const unsigned int& diver_number,
                    			 const QString& name )
{
    m_serial_number = serial_number;
    m_diver_number  = diver_number;
    m_name   				= name;
}

DiveComputerVO& DiveComputerVO::operator=( const DiveComputerVO& diveComputer )
{
    m_serial_number = diveComputer.m_serial_number;
    m_diver_number  = diveComputer.m_diver_number;
    m_name   				= diveComputer.m_name;
    return *this;
}

void DiveComputerVO::init()
{
}

/*
|| Accessors
*/

QString DiveComputerVO::serial_number() const
{
    return m_serial_number;
}

unsigned int DiveComputerVO::diver_number() const
{
    return m_diver_number;
}

QString DiveComputerVO::name() const
{
    return m_name;
}


void DiveComputerVO::serial_number ( const QString& serial_number )
{
    m_serial_number=serial_number;
}

void DiveComputerVO::diver_number( const unsigned int& diver_number )
{
    m_diver_number=diver_number;
}

void DiveComputerVO::name( const QString& name )
{
    m_name=name;
}
