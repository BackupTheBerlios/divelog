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

#ifndef DIVEVO_H
#define DIVEVO_H
/******************************************************************************
* Filename : DiveVO.h                                                         *
* CVS Id   : $Id: DiveVO.h,v 1.5 2002/09/16 17:08:11 grunwalm Exp $             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveVO.cpp                               *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Feb 14 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <qstring.h>
#include <qdatetime.h>
#include "DiveProfileVO.h"

class DiveVO
{
public:
    /*
    || Constructors
    */
    DiveVO();
    DiveVO( const DiveVO& d );
    DiveVO( const int&    number,       // NOT NULL
            const QDateTime& date_time, // NOT NULL
            const bool&    sync,        // NOT NULL
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
            const int&    bottle_number );

    void init( const int&    number,
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
               const int& 	 dive_type,
               const int&    filling_station_number,
               const int&    bottle_number );

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

    int       number() const 							{ return m_number; }
    QDateTime date_time() const   				{ return m_date_time; }
    bool   sync() const   								{ return m_sync; }
    int    diver_number() const 					{ return m_diver_number; }
    QString place() const  								{ return m_place; }
    QString location() const 							{ return m_location; }
    double altitude_mode() const 					{ return m_altitude_mode; }
    double water_temperature() const 			{ return m_water_temperature; }
    double start_pressure() const    			{ return m_start_pressure; }
    double end_pressure() const      			{ return m_end_pressure; }
    double surface_intervall() const 			{ return m_surface_intervall; }
    double max_depth() const         			{ return m_max_depth; }
    QString duration() const            		{ return m_duration; }
    DiveProfileVO profile() const    			{ return m_profile; }
    QString log() const               		{ return m_log; }
    int    partner_diver_number() const 	{ return m_partner_diver_number; }
    QString weather() const 							{ return m_weather; }
    QString sight() const   							{ return m_sight; }
    double lead() const    								{ return m_lead; }
    double air_temperature() const        { return m_air_temperature; }
    int 	 dive_type() const              { return m_dive_type; }
    int    filling_station_number() const { return m_filling_station_number; }
    int    bottle_number() const          { return m_bottle_number; }
    /*
    || Operators
    */

    DiveVO& operator=( const DiveVO& d );

protected:
    void init();
private:

    int       m_number;      // NOT NULL
    QDateTime m_date_time;   // NOT NULL
    bool      m_sync;        // NOT NULL
    int       m_diver_number;
    QString   m_place;
    QString   m_location;
    double    m_altitude_mode;
    double    m_water_temperature;
    double    m_start_pressure;
    double    m_end_pressure;
    double    m_surface_intervall;
    double    m_max_depth;
    QString   m_duration;
    DiveProfileVO m_profile;
    QString   m_log;      // TEXT
    int       m_partner_diver_number;
    QString   m_weather;
    QString   m_sight;
    double    m_lead;
    double    m_air_temperature;
    int 	    m_dive_type;
    int       m_filling_station_number;
    int       m_bottle_number;
};


#endif
