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
* Filename : DiveProfileVO.cpp                                                *
* CVS Id   : $Id: DiveProfileVO.cpp,v 1.5 2002/06/02 09:55:13 grunwalm Exp $    *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about dive profiles ( Value   *
*                    Object ), i.e. Depth, sample-time, warnings...           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Feb 05 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiveProfileVO.h"
#include <strstream.h>
#include <qpointarray.h>


#define DIVE_PROFILE_SEPARATOR " "

/*
|| Constructors
*/
DiveProfileVO::DiveProfileVO()
// -------------------------------------------------
// Use : Create an empty Dive Profile Value Object
//       Mostly useless, may vanish some time.
// -------------------------------------------------
{
}

DiveProfileVO::DiveProfileVO( const DiveProfileVO& d )
// -------------------------------------------------
// Use : Copy Constructor for Dive Profile Value Object
// Parameters  : d - the source object
// -------------------------------------------------
{
    (*this)= d ;
}

DiveProfileVO::DiveProfileVO( const UDCFSample* samples, const uint maxIndex )
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

void DiveProfileVO::init()
// -------------------------------------------------
// Use : general initialisation
// -------------------------------------------------
{
}

DiveProfileVO& DiveProfileVO::operator=( const DiveProfileVO& d )
// -------------------------------------------------
// Use : Copy operator
// -------------------------------------------------
{
    m_profile       = d.m_profile;
    m_secsPerSample = d.m_secsPerSample;
    m_marks         = d.m_marks;
    m_samples       = d.m_samples;
    m_maxDepth      = d.m_maxDepth;

    return *this;
}

// Stream/Shift Operators
ostream& operator<<( ostream& ostr, const DiveProfileVO& profile )
// -------------------------------------------------
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

    DiveProfileVO::marker_map::iterator i;
    for ( i=profile.marks().begin(); i!=profile.marks().end(); i++ )
    {
        ostr << (*i).first  << DIVE_PROFILE_SEPARATOR
             << (*i).second << DIVE_PROFILE_SEPARATOR;
    }

    ostr << profile.m_secsPerSample << DIVE_PROFILE_SEPARATOR
         << profile.m_samples << DIVE_PROFILE_SEPARATOR
         << profile.m_maxDepth << DIVE_PROFILE_SEPARATOR;

    return ostr;
}

istream& operator>>( istream& istr, DiveProfileVO& profile )
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

string& operator>>( string& str, DiveProfileVO& profile )
{
    istrstream istr( str.c_str() );
    istr >> profile;
    return str;
}

/*
|| Accessors
*/

// All in header file