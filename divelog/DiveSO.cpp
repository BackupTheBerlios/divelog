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
* Filename : DiveSO.cpp                                                       *
* CVS Id   : $Id: DiveSO.cpp,v 1.1 2002/09/16 17:08:11 grunwalm Exp $        *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about search keys for dives   *
*                    (Search Object)                                          *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Aug 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiveSO.h"

DiveSO::DiveSO()
{
    m_searchField=SF_empty;
}

void DiveSO::number( const int& number )
{
    m_dive.number( number );
    addSearchField( SF_number );
}

void DiveSO::date_time( const QDateTime& date_time )
{
    m_dive.date_time( date_time );
    addSearchField( SF_date_time );
}

void DiveSO::sync( const bool& sync )
{
    m_dive.sync( sync );
    addSearchField( SF_sync  );
}

void DiveSO::diver_number( const int& diver_number )
{
    m_dive.diver_number( diver_number );
    addSearchField( SF_diver_number  );
}

void DiveSO::place( const QString& place )
{
    m_dive.place( place );
    addSearchField( SF_place  );
}

void DiveSO::location( const QString& location )
{
    m_dive.location( location );
    addSearchField( SF_location  );
}

void DiveSO::altitude_mode( const double& altitude_mode )
{
    m_dive.altitude_mode( altitude_mode );
    addSearchField( SF_altitude_mode  );
}

void DiveSO::water_temperature( const double& water_temperature )
{
    m_dive.water_temperature( water_temperature );
    addSearchField( SF_water_temperature  );
}

void DiveSO::start_pressure( const double& start_pressure )
{
    m_dive.start_pressure( start_pressure );
    addSearchField( SF_start_pressure  );
}

void DiveSO::end_pressure( const double& end_pressure )
{
    m_dive.end_pressure( end_pressure );
    addSearchField( SF_end_pressure  );
}

void DiveSO::surface_intervall( const double& surface_intervall )
{
    m_dive.surface_intervall( surface_intervall );
    addSearchField( SF_surface_intervall  );
}

void DiveSO::max_depth( const double& max_depth )
{
    m_dive.max_depth( max_depth );
    addSearchField( SF_max_depth  );
}

void DiveSO::duration( const QString& duration )
{
    m_dive.duration( duration );
    addSearchField( SF_duration  );
}

void DiveSO::profile( const DiveProfileVO& profile )
{
    m_dive.profile( profile );
    addSearchField( SF_profile  );
}

void DiveSO::log( const QString& log )
{
    m_dive.log( log );
    addSearchField( SF_log  );
}

void DiveSO::partner_diver_number( const int& partner_diver_number )
{
    m_dive.partner_diver_number( partner_diver_number );
    addSearchField( SF_partner_diver_number  );
}

void DiveSO::weather( const QString& weather )
{
    m_dive.weather( weather );
    addSearchField( SF_weather  );
}

void DiveSO::sight( const QString& sight )
{
    m_dive.sight( sight );
    addSearchField( SF_sight  );
}

void DiveSO::lead( const double& lead )
{
    m_dive.lead( lead );
    addSearchField( SF_lead  );
}

void DiveSO::air_temperature( const double& air_temperature )
{
    m_dive.air_temperature( air_temperature );
    addSearchField( SF_air_temperature  );
}

void DiveSO::dive_type( const int& dive_type )
{
    m_dive.dive_type( dive_type );
    addSearchField( SF_dive_type  );
}

void DiveSO::filling_station_number( const int& filling_station_number )
{
    m_dive.filling_station_number( filling_station_number );
    addSearchField( SF_filling_station_number  );
}

void DiveSO::bottle_number( const int& bottle_number )
{
    m_dive.bottle_number( bottle_number );
    addSearchField( SF_bottle_number  );
}

void DiveSO::clearSearchField( const SearchFieldEnum& sfe= SF_empty )
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

bool DiveSO::checkMoreFields( const SearchFieldEnum& sfe ) const
{
    SearchFieldEnum mask = static_cast< SearchFieldEnum > ( ~( sfe | ( sfe -1 ) ) );
    return ( m_searchField & mask ) !=0;
}

bool DiveSO::checkSearchField( const SearchFieldEnum& sfe ) const
{
    return ( static_cast< SearchFieldEnum > (m_searchField & sfe ) == sfe  );
}
