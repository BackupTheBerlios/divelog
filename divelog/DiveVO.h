#ifndef DIVEVO_H
#define DIVEVO_H
/******************************************************************************
* Filename : DiveVO.h                                                         *
* CVS Id   : $Id: DiveVO.h,v 1.2 2002/04/03 11:43:33 markus Exp $             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveVO.cpp                               *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Feb 14 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>
#include "DiveProfileVO.h"

//class DiveProfileVO;

class DiveVO
{
public:
    /*
    || Constructors
    */
    DiveVO();
    DiveVO( const DiveVO& d );
    DiveVO( const int&    number,
            const string& date,  // DATETIME split up
            const string& time,
            const int&    sync,
            const int&    diver_number,
            const string& place,
            const string& location,
            const double& altitude_mode,
            const double& water_temperature,
            const double& start_pressure,
            const double& end_pressure,
            const double& surface_intervall,
            const double& max_depth,
            const string& length,
            const DiveProfileVO profile,
            const string& log,      // TEXT
            const int&    partner_diver_number,
            const string& weather,
            const string& sight,
            const double& lead,
            const double& air_temperature,
            const int& 	  dive_type,
            const int&    filling_station_number,
            const int&    bottle_number );

    void init( const int&    number,
               const string& date,  // DATETIME split up
               const string& time,
               const int&    sync,
               const int&    diver_number,
               const string& place,
               const string& location,
               const double& altitude_mode,
               const double& water_temperature,
               const double& start_pressure,
               const double& end_pressure,
               const double& surface_intervall,
               const double& max_depth,
               const string& length,
               const DiveProfileVO profile,
               const string& log,      // TEXT
               const int&    partner_diver_number,
               const string& weather,
               const string& sight,
               const double& lead,
               const double& air_temperature,
               const int& 	 dive_type,
               const int&    filling_station_number,
               const int&    bottle_number );

    /*
    || Accessors
    */
    void setNumber( const int& number );
    void setDate( const string& date );
    void setTime( const string& time );
    void setSync( const bool& sync );
    void setDiver_number( const int& diver_number );
    void setPlace( const string& place );
    void setLocation( const string& location );
    void setAltitude_mode( const double& altitude_mode );
    void setWater_temperature( const double& water_temperature );
    void setStart_pressure( const double& start_pressure );
    void setEnd_pressure( const double& end_pressure );
    void setSurface_intervall( const double& surface_intervall );
    void setMax_depth( const double& max_depth );
    void setLength( const string& length );
    void setProfile( const DiveProfileVO& profile );
    void setLog( const string& log );
    void setPartner_diver_number( const int& partner_diver_number );
    void setWeather( const string& weather );
    void setSight( const string& sight );
    void setLead( const double& lead );
    void setAir_temperature( const double& air_temperature );
    void setDive_type( const int& dive_type );
    void setFilling_station_number( const int& filling_station_number );
    void setBottleNumber( const int& bottle_number );

    int    number() const 								{ return m_number; }
    string date() const   								{ return m_date; }
    string time() const   								{ return m_time; }
    int    sync() const   								{ return m_sync; }
    int    diver_number() const 					{ return m_diver_number; }
    string place() const  								{ return m_place; }
    string location() const 							{ return m_location; }
    double altitude_mode() const 					{ return m_altitude_mode; }
    double water_temperature() const 			{ return m_water_temperature; }
    double start_pressure() const    			{ return m_start_pressure; }
    double end_pressure() const      			{ return m_end_pressure; }
    double surface_intervall() const 			{ return m_surface_intervall; }
    double max_depth() const         			{ return m_max_depth; }
    string length() const            			{ return m_length; }
    DiveProfileVO profile() const    			{ return m_profile; }
    string log() const               			{ return m_log; }
    int    partner_diver_number() const 	{ return m_partner_diver_number; }
    string weather() const 								{ return m_weather; }
    string sight() const   								{ return m_sight; }
    double lead() const    								{ return m_lead; }
    double air_temperature() const        { return m_air_temperature; }
    int 	 dive_type() const              { return m_dive_type; }
    int    filling_station_number() const { return m_filling_station_number; }
    int    bottle_number() const          { return m_bottle_number; }
    /*
    || Operators
    */

    DiveVO& operator=( const DiveVO& d );


private:
    void init();

    int    m_number;
    string m_date;  // DATETIME split up
    string m_time;
    int    m_sync;
    int    m_diver_number;
    string m_place;
    string m_location;
    double m_altitude_mode;
    double m_water_temperature;
    double m_start_pressure;
    double m_end_pressure;
    double m_surface_intervall;
    double m_max_depth;
    string m_length;
    DiveProfileVO m_profile;
    string m_log;      // TEXT
    int    m_partner_diver_number;
    string m_weather;
    string m_sight;
    double m_lead;
    double m_air_temperature;
    int 	 m_dive_type;
    int    m_filling_station_number;
    int    m_bottle_number;
};


#endif
