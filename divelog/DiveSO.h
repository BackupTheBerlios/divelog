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

#ifndef DIVESO_H
#define DIVESO_H
/******************************************************************************
* Filename : DiveSO.h                                                         *
* CVS Id   : $Id: DiveSO.h,v 1.1 2002/09/16 17:08:11 grunwalm Exp $          *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveSO.cpp                               *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Aug 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include "DiveVO.h"

class DiveSO
{
public:
    enum SearchFieldEnum
    {
        SF_invalidLow                 = -1,
        SF_empty                      =  0,
        SF_number                     =  1 <<  0,
        SF_date_time                  =  1 <<  1,
        SF_sync                       =  1 <<  2,
        SF_diver_number               =  1 <<  3,
        SF_place                      =  1 <<  4,
        SF_location                   =  1 <<  5,
        SF_altitude_mode              =  1 <<  6,
        SF_water_temperature          =  1 <<  7,
        SF_start_pressure             =  1 <<  8,
        SF_end_pressure               =  1 <<  9,
        SF_surface_intervall          =  1 << 10,
        SF_max_depth                  =  1 << 11,
        SF_duration                     =  1 << 12,
        SF_profile                    =  1 << 13,
        SF_log                        =  1 << 14,
        SF_partner_diver_number       =  1 << 15,
        SF_weather                    =  1 << 16,
        SF_sight                      =  1 << 17,
        SF_lead                       =  1 << 18,
        SF_air_temperature            =  1 << 19,
        SF_dive_type                  =  1 << 20,
        SF_filling_station_number     =  1 << 21,
        SF_bottle_number              =  1 << 22,
        SF_all                        = (1 << 23)-1,
        SF_invalidHigh                =  1 << 23
    };
    
    /*
    || Constructors
    */

    DiveSO();

    DiveSO( const DiveSO& d )
    {
        m_dive        = d.m_dive;
        m_searchField = d.m_searchField;
    };

    DiveSO( const int& number,
            const QDateTime& date_time,
            const bool&    sync,
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
            const int&    bottle_number,
            const SearchFieldEnum& sfe
          )
        : m_dive( number, date_time, sync, diver_number, place, location, altitude_mode,
                  water_temperature, start_pressure, end_pressure, surface_intervall,
                  max_depth, duration, profile, log, partner_diver_number, weather, sight,
                  lead, air_temperature, dive_type, filling_station_number, bottle_number )
    {
        m_searchField = sfe;
    };

/*
|| Accessors
*/

    void number( const int& number );
    void date_time( const QDateTime& date_time );
    void sync( const bool& sync );
    void diver_number( const int& diver_number );
    void place( const QString& place );
    void location( const QString& location );
    void altitude_mode( const double& altitude_mode );
    void water_temperature( const double& water_temperature );
    void start_pressure( const double& start_pressure );
    void end_pressure( const double& end_pressure );
    void surface_intervall( const double& surface_intervall );
    void max_depth( const double& max_depth );
    void duration( const QString& duration );
    void profile( const DiveProfileVO& profile );
    void log( const QString& log );
    void partner_diver_number( const int& partner_diver_number );
    void weather( const QString& weather );
    void sight( const QString& sight );
    void lead( const double& lead );
    void air_temperature( const double& air_temperature );
    void dive_type( const int& dive_type );
    void filling_station_number( const int& filling_station_number );
    void bottle_number( const int& bottle_number );

    int       number() const 							{ return m_dive.number(); }
    QDateTime date_time() const   				{ return m_dive.date_time(); }
    bool   sync() const   								{ return m_dive.sync(); }
    int    diver_number() const 					{ return m_dive.diver_number(); }
    QString place() const  								{ return m_dive.place(); }
    QString location() const 							{ return m_dive.location(); }
    double altitude_mode() const 					{ return m_dive.altitude_mode(); }
    double water_temperature() const 			{ return m_dive.water_temperature(); }
    double start_pressure() const    			{ return m_dive.start_pressure(); }
    double end_pressure() const      			{ return m_dive.end_pressure(); }
    double surface_intervall() const 			{ return m_dive.surface_intervall(); }
    double max_depth() const         			{ return m_dive.max_depth(); }
    QString duration() const            	{ return m_dive.duration(); }
    DiveProfileVO profile() const    			{ return m_dive.profile(); }
    QString log() const               		{ return m_dive.log(); }
    int    partner_diver_number() const 	{ return m_dive.partner_diver_number(); }
    QString weather() const 							{ return m_dive.weather(); }
    QString sight() const   							{ return m_dive.sight(); }
    double lead() const    								{ return m_dive.lead(); }
    double air_temperature() const        { return m_dive.air_temperature(); }
    int 	 dive_type() const              { return m_dive.dive_type(); }
    int    filling_station_number() const { return m_dive.filling_station_number(); }
    int    bottle_number() const          { return m_dive.bottle_number(); }

    SearchFieldEnum searchField() const
    {
        return m_searchField;
    }

    void addSearchField( const SearchFieldEnum& sfe )
    {
        m_searchField = static_cast< SearchFieldEnum > ( m_searchField | sfe );
    }

    void clearSearchField( const SearchFieldEnum& sfe= SF_empty );
    bool checkSearchField( const SearchFieldEnum& sfe ) const;

    bool checkMoreFields( const SearchFieldEnum& sfe ) const;

/*
|| Operators
*/

    DiveSO& operator=( const DiveSO& d )
    {
        m_dive        = d.m_dive;
        m_searchField = d.m_searchField;

        return *this;
    }

private:
    SearchFieldEnum m_searchField;
    DiveVO          m_dive;
};

#endif // DIVERSO_H
