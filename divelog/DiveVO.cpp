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
* Filename : DiveVO.cpp                                                       *
* CVS Id   : $Id: DiveVO.cpp,v 1.6 2002/09/16 17:08:11 grunwalm Exp $         *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about dives ( Value Object ), *
*                    i.e. maximum depth, duration, profile...                   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Feb 14 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiveVO.h"
#include "DiveProfileVO.h"
#include <qpointarray.h>

#define DIVE_PROFILE_SEPARATOR " "

/*
|| Constructors
*/
DiveVO::DiveVO()
// -------------------------------------------------
// Use : Create an empty Dive Value Object
// -------------------------------------------------
{
}

DiveVO::DiveVO( const int& number,          // NOT NULL
                const QDateTime& date_time, // NOT NULL
                const bool&   sync,         // NOT NULL
                const int&    diver_number,
                const QString& place,
                const QString& location,
                const double& altitude_mode,
                const double& water_temperature,
                const double& start_pressure,
                const double& end_pressure,
                const double& surface_intervall,
                const double& max_depth,
                const QString& duration,
                const DiveProfileVO profile,
                const QString& log,      // TEXT
                const int&    partner_diver_number,
                const QString& weather,
                const QString& sight,
                const double& lead,
                const double& air_temperature,
                const int& 	  dive_type,
                const int&    filling_station_number,
                const int&    bottle_number )
{
    init( number, date_time, sync, diver_number, place, location,  altitude_mode,
          water_temperature, start_pressure, end_pressure, surface_intervall,
          max_depth, duration, profile, log, partner_diver_number, weather,
          sight, lead, air_temperature, dive_type, filling_station_number,
          bottle_number );
}

void DiveVO::init( const int& number,          // NOT NULL
                   const QDateTime& date_time, // NOT NULL
                   const bool&   sync,         // NOT NULL
                   const int&    diver_number,
                   const QString& place,
                   const QString& location,
                   const double& altitude_mode,
                   const double& water_temperature,
                   const double& start_pressure,
                   const double& end_pressure,
                   const double& surface_intervall,
                   const double& max_depth,
                   const QString& duration,
                   const DiveProfileVO profile,
                   const QString& log,      // TEXT
                   const int&    partner_diver_number,
                   const QString& weather,
                   const QString& sight,
                   const double& lead,
                   const double& air_temperature,
                   const int& 	  dive_type,
                   const int&    filling_station_number,
                const int&    bottle_number )
{
    m_number                 = number;
    m_date_time              = date_time;
    m_sync                   = sync;
    m_diver_number           = diver_number;
    m_place                  = place;
    m_location               = location;
    m_altitude_mode          = altitude_mode;
    m_water_temperature      = water_temperature;
    m_start_pressure         = start_pressure;
    m_end_pressure           = end_pressure;
    m_surface_intervall      = surface_intervall;
    m_max_depth              = max_depth;
    m_duration                 = duration;
    m_profile                = profile;
    m_log                    = log;      // TEXT
    m_partner_diver_number   = partner_diver_number;
    m_weather                = weather;
    m_sight                  = sight;
    m_lead                   = lead;
    m_air_temperature        = air_temperature;
    m_dive_type              = dive_type;
    m_filling_station_number = filling_station_number;
    m_bottle_number          = bottle_number;
}

DiveVO::DiveVO( const DiveVO& d )
// -------------------------------------------------
// Use : Copy Constructor for Dive Profile Value Object
// Parameters  : d - the source object
// -------------------------------------------------
{
    (*this)= d ;
}

void DiveVO::init()
// -------------------------------------------------
// Use : general initialisation
// -------------------------------------------------
{
}

DiveVO& DiveVO::operator=( const DiveVO& d )
// -------------------------------------------------
// Use : Copy operator
// -------------------------------------------------
{
    m_number                 = d.m_number;
    m_date_time              = d.m_date_time; 
    m_sync                   = d.m_sync;
    m_diver_number           = d.m_diver_number;
    m_place                  = d.m_place;
    m_location               = d.m_location;
    m_altitude_mode          = d.m_altitude_mode;
    m_water_temperature      = d.m_water_temperature;
    m_start_pressure         = d.m_start_pressure;
    m_end_pressure           = d.m_end_pressure;
    m_surface_intervall      = d.m_surface_intervall;
    m_max_depth              = d.m_max_depth;
    m_duration                 = d.m_duration;
    m_profile                = d.m_profile;
    m_log                    = d.m_log;      // TEXT
    m_partner_diver_number   = d.m_partner_diver_number;
    m_weather                = d.m_weather;
    m_sight                  = d.m_sight;
    m_lead                   = d.m_lead;
    m_air_temperature        = d.m_air_temperature;
    m_dive_type              = d.m_dive_type;
    m_filling_station_number = d.m_filling_station_number;
    m_bottle_number          = d.m_bottle_number;

    return *this;
}


/*
|| Accessors
*/

void DiveVO::number( const int& number )
{
    m_number = number;
}

void DiveVO::date_time( const QDateTime& date_time )
{
    m_date_time= date_time;
}

void DiveVO::sync( const bool& sync )
{
    m_sync= sync;
}

void DiveVO::diver_number( const int& diver_number )
{
    m_diver_number= diver_number;
}

void DiveVO::place( const QString& place )
{
    m_place= place;
}

void DiveVO::location( const QString& location )
{
    m_location= location;
}

void DiveVO::altitude_mode( const double& altitude_mode )
{
    m_altitude_mode= altitude_mode;
}

void DiveVO::water_temperature( const double& water_temperature )
{
    m_water_temperature= water_temperature;
}

void DiveVO::start_pressure( const double& start_pressure )
{
    m_start_pressure= start_pressure;
}

void DiveVO::end_pressure( const double& end_pressure )
{
    m_end_pressure= end_pressure;
}

void DiveVO::surface_intervall( const double& surface_intervall )
{
    m_surface_intervall= surface_intervall;
}

void DiveVO::max_depth( const double& max_depth )
{
    m_max_depth= max_depth;
}

void DiveVO::duration( const QString& duration )
{
    m_duration= duration;
}

void DiveVO::profile( const DiveProfileVO& profile )
{
    m_profile= profile;
}

void DiveVO::log( const QString& log )
{
    m_log= log;
}

void DiveVO::partner_diver_number( const int& partner_diver_number )
{
    m_partner_diver_number= partner_diver_number;
}

void DiveVO::weather( const QString& weather )
{
    m_weather= weather;
}

void DiveVO::sight( const QString& sight )
{
    m_sight= sight;
}

void DiveVO::lead( const double& lead )
{
    m_lead= lead;
}

void DiveVO::air_temperature( const double& air_temperature )
{
    m_air_temperature= air_temperature;
}

void DiveVO::dive_type( const int& dive_type )
{
    m_dive_type= dive_type;
}

void DiveVO::filling_station_number( const int& filling_station_number )
{
    m_filling_station_number= filling_station_number;
}

void DiveVO::bottle_number( const int& bottle_number )
{
    m_bottle_number= bottle_number;
}

