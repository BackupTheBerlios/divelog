/******************************************************************************
* Filename : DiveVO.cpp                                                       *
* CVS Id   : $Id: DiveVO.cpp,v 1.2 2002/04/03 11:43:33 markus Exp $           *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about dives ( Value Object ), *
*                    i.e. maximum depth, length, profile...                   *
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

DiveVO::DiveVO( const int& number,
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
                const int&    bottle_number )
{
    init( number, date, time, sync, diver_number, place, location,  altitude_mode,
          water_temperature, start_pressure, end_pressure, surface_intervall,
          max_depth, length, profile, log, partner_diver_number, weather,
          sight, lead, air_temperature, dive_type, filling_station_number,
          bottle_number );
}

void DiveVO::init( const int&    number,
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
                   const int&    bottle_number )
{
    m_number                 = number;
    m_date                   = date;  // DATETIME split up
    m_time                   = time;
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
    m_length                 = length;
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

#ifdef undefined
DiveVO::DiveVO( const UDCFSample* samples, const uint maxIndex )
// -------------------------------------------------
// Use : Read existing profile data from an UDCF
//       sample.
// Parameters  : samples - the UDCF sample data
//                         structure
//               maxIndex - one-past-end index
//                          of samples
// -------------------------------------------------
{
    m_profile.resize( maxIndex ); // This is too big because maxIndex contains
    															// marks and other infos as well
																  // So resize it later to the proper size
    uint depth_count=0;           // Counts real depth Values;
    uint mark_count=0;            // Counts marks

    m_maxDepth=0;

    for ( uint i=0 ; i<maxIndex; i++ )
    {
//        cerr << "Sample #" << i << "  Type : " << samples[i].type << endl; // DEBUG
/*  // DEBUG
             << "depth       : " << samples[i].data.depth << endl
             << "sampleTime  : " << samples[i].data.sampleTime << endl
             << "mark        : " << samples[i].data.mark << endl
             << "point       : " << samples[i].data.point.x << " | " << samples[i].data.point.x << endl
             << "work        : " << samples[i].data.work << endl
             << "mix         : " << samples[i].data.mix << endl;
*/
        switch ( samples[i].type )
        {
        case ST_DEPTH:
            // The depth entry in the point array is only an index, not
            // the real time                     V
            m_profile.setPoint( depth_count, depth_count, qRound( samples[i].data.depth*10 ) );
            m_maxDepth = QMAX( m_maxDepth, qRound(samples[i].data.depth*10)/10.0 );
            depth_count++;
            break;
        case ST_TD:   // Don't know
            break;
        case ST_MARK:
            m_marks[ depth_count ] = samples[i].data.mark;
            mark_count++;
            break;
        case ST_MIX:
            cerr << "Sample #" << i << "  Type : " << samples[i].type << endl // DEBUG
                 << "depth       : " << samples[i].data.depth << endl
                 << "sampleTime  : " << samples[i].data.sampleTime << endl
                 << "mark        : " << samples[i].data.mark << endl
                 << "point       : " << samples[i].data.point.x << " | " << samples[i].data.point.x << endl
                 << "work        : " << samples[i].data.work << endl
                 << "mix         : " << samples[i].data.mix << endl;
            break;
        case ST_SAMPLETIME:
            m_secsPerSample=(uint) samples[i].data.sampleTime; // FIXME: any doubles
                                                               //        possible ?
           break;
        case ST_WORK: // Don't know
            break;
        default:
            break;
        }
    }

    m_profile.resize( depth_count ); // Now we know for sure how many depth values
                                     // we have, so we trim them.
    m_samples=depth_count;
}
#endif

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
    m_date                   = d.m_date;  // DATETIME split up
    m_time                   = d.m_time;
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
    m_length                 = d.m_length;
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
// Stream/Shift Operators
ostream& operator<<( ostream& ostr, DiveVO& profile )
// -------------------------------------------------
// FIXME: This is not a DiveVO serialisation, but a
// FIXME: DiveProfileVO ser. !
// Use : Serialize a Dive Profile Value Object
// Parameters  : ostr - output stream
//               profile - profile to serialize
//
// Note: Serialisation order:
//  <Number of Depth Samples>
//    <Depth Samples>
//  <Number of marks>
//    <marks>
//  <Seconds per Sample>
//  <Number of Samples>
//  <Maximum Depth>
// -------------------------------------------------
{
    ostr << profile.m_profile.size() << DIVE_PROFILE_SEPARATOR;

    for ( uint i=0; i<profile.m_profile.size(); i++ )
    {
        ostr << profile.m_profile.point( i ).x() << DIVE_PROFILE_SEPARATOR
             << profile.m_profile.point( i ).y() << DIVE_PROFILE_SEPARATOR;
    }

    ostr << profile.m_marks.size() << DIVE_PROFILE_SEPARATOR;

    map< uint, UDCFMarkerType >::iterator i;
    for ( i=profile.m_marks.begin(); i!=profile.m_marks.end(); i++ )
    {
        ostr << (*i).first  << DIVE_PROFILE_SEPARATOR
             << (*i).second << DIVE_PROFILE_SEPARATOR;
    }

    ostr << profile.m_secsPerSample << DIVE_PROFILE_SEPARATOR
         << profile.m_samples << DIVE_PROFILE_SEPARATOR
         << profile.m_maxDepth << DIVE_PROFILE_SEPARATOR;

    return ostr;
}

istream& operator>>( istream& istr, DiveVO& profile )
{
    uint profile_size;
    uint marks_size;

    istr >> profile_size;

    profile.m_profile.resize( profile_size );
    for ( uint i=0; i<profile_size; i++ )
    {
        uint sample;
        uint depth;

        istr >> sample ;
        istr >> depth;

        profile.m_profile.setPoint( i, sample, depth );
    }

    profile.m_marks.clear();

    istr >> marks_size;

    for ( uint i=0; i<marks_size; i++ )
    {
        uint sample;
        int  imark;
        UDCFMarkerType mark;

        istr >> sample >> imark;

        mark=(UDCFMarkerType) imark;

        profile.m_marks[ sample ]=mark;
    }

    istr >> profile.m_secsPerSample
         >> profile.m_samples
         >> profile.m_maxDepth ;

    return istr;
}
*/

/*
|| Accessors
*/

// All in header file