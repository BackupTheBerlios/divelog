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

/**********************************************************************
* Filename : DiveTypeVO.cpp                                           *
* CVS Id   : $Id: DiveTypeVO.cpp,v 1.2 2002/05/15 09:27:51 grunwalm Exp $                                                     *
* ------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divetypes	      *
*                    (Value Object)   																*
* Owner            : Markus Grunwald (MG)                             *
* Date of Creation : Thu Nov 22 2001                                  *
* ------------------------------------------------------------------- *
* To Do List :                                                        *
* ------------------------------------------------------------------- *
* Notes :                                                             *
**********************************************************************/
#include "DiveTypeVO.h"

/*
|| Constructors
*/
DiveTypeVO::DiveTypeVO()
{
    init();
}

DiveTypeVO::DiveTypeVO( const DiveTypeVO& diveType )
{
    m_number       = diveType.m_number;
    m_description  = diveType.m_description;
}

DiveTypeVO::DiveTypeVO( const unsigned int& number,
                        const string& description
											)
{
    init( number, description );
}

void DiveTypeVO::init( const unsigned int& number,
                       const string& description
                     )
{
    m_number       = number;
    m_description  = description;
}

DiveTypeVO& DiveTypeVO::operator=( const DiveTypeVO& diveType )
{
    m_number       = diveType.m_number;
    m_description  = diveType.m_description;
}

void DiveTypeVO::init()
{
}

/*
|| Accessors
*/

unsigned int DiveTypeVO::number() const
{
    return m_number;
}

string DiveTypeVO::description() const
{
    return m_description;
}



void DiveTypeVO::setNumber ( const unsigned int& number )
{
    m_number=number;
}

void DiveTypeVO::setDescription( const string& description )
{
    m_description=description;
}

