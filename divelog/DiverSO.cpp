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
* Filename : DiverSO.cpp                                                      *
* CVS Id   : $Id: DiverSO.cpp,v 1.1 2002/09/16 17:08:11 grunwalm Exp $        *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about search keys for divers  *
*                    (Search Object)                                          *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Aug 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiverSO.h"

DiverSO::DiverSO()
{
    m_searchField=SF_empty;
}

void DiverSO::number ( const unsigned int& number )
{
    m_diver.number(number);
    addSearchField( SF_number );
}

void DiverSO::first_name ( const QString& first_name )
{
    m_diver.first_name(first_name);
    addSearchField( SF_first_name );
}

void DiverSO::last_name ( const QString& last_name )
{
    m_diver.last_name(last_name);
    addSearchField( SF_last_name );
}

void DiverSO::brevet ( const QString& brevet )
{
    m_diver.brevet(brevet);
    addSearchField( SF_brevet );
}

void DiverSO::street ( const QString& street )
{
    m_diver.street(street);
    addSearchField( SF_street );
}

void DiverSO::house_number( const QString& house_number )
{
    m_diver.house_number(house_number);
    addSearchField( SF_street );
}

void DiverSO::zip	( const int& zip )
{
    m_diver.zip(zip);
    addSearchField( SF_zip );
}

void DiverSO::place	( const QString& place )
{
    m_diver.place(place);
    addSearchField( SF_place );
}

void DiverSO::phone ( const QString& phone )
{
    m_diver.phone(phone);
    addSearchField( SF_phone );
}

void DiverSO::email	( const QString& email )
{
    m_diver.email(email);
    addSearchField( SF_email );
}


void DiverSO::clearSearchField( const SearchFieldEnum& sfe= SF_empty )
{
    if ( sfe==SF_empty )
    {
        m_searchField=SF_empty;
    }
    else
    {
        m_searchField  = static_cast< SearchFieldEnum > ( ~m_searchField );
        m_searchField  = static_cast< SearchFieldEnum > (  m_searchField | sfe );
        m_searchField  = static_cast< SearchFieldEnum > ( ~m_searchField );
    }
}

bool DiverSO::checkMoreFields( const SearchFieldEnum& sfe ) const
{
    SearchFieldEnum mask = static_cast< SearchFieldEnum > ( ~( sfe | ( sfe -1 ) ) );
    return ( m_searchField & mask ) !=0;
}

bool DiverSO::checkSearchField( const SearchFieldEnum& sfe ) const
{
    return ( static_cast< SearchFieldEnum > (m_searchField & sfe ) == sfe  );
}
