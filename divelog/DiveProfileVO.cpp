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
* CVS Id   : $Id: DiveProfileVO.cpp,v 1.6 2002/09/16 17:08:11 grunwalm Exp $  *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about dive profiles ( Value   *
*                    Object ), i.e. Depth, sample-time, warnings...           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Tue Feb 05 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List : Need mark for invalid/empty depth/length/profile entries       *
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
            m_marks.insert( pair<uint , UDCFMarkerType>(depth_count, samples[i].data.mark ));
            break;
        case ST_MIX:
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

QString DiveProfileVO::toQString() const
// -------------------------------------------------
// Use : Convert a Dive Profile Value Object
//       to a QString
//
// Note: Serialisation order:
//  <Number of Depth Samples>
//    <Depth Samples>
//  <Number of marks>
//    <sample number>
//    <mark>
//  <Seconds per Sample>
//  <Number of Samples>
//  <Maximum Depth>
// -------------------------------------------------
{
    QString result;
    result= QString::number( m_profile.size() ) + DIVE_PROFILE_SEPARATOR;

    for ( uint i=0; i<m_profile.size(); i++ )
    {
        result += QString::number( m_profile.point( i ).x() ) + DIVE_PROFILE_SEPARATOR
               +  QString::number( m_profile.point( i ).y() ) + DIVE_PROFILE_SEPARATOR;
    }

    result += QString::number( m_marks.size() ) + DIVE_PROFILE_SEPARATOR;

    for (DiveProfileVO::t_marker_map::const_iterator it = m_marks.begin();
         it != m_marks.end();  ++it)
    {
        result += QString::number( (*it).first ) + DIVE_PROFILE_SEPARATOR;  // Sample number for marker
        result += QString::number( (*it).second ) + DIVE_PROFILE_SEPARATOR;   // The marker

    }

    result += QString::number( m_secsPerSample ) + DIVE_PROFILE_SEPARATOR
           +  QString::number( m_samples  ) + DIVE_PROFILE_SEPARATOR
           +  QString::number( m_maxDepth ) + DIVE_PROFILE_SEPARATOR;

    return result;
}

void DiveProfileVO::fromQString( const QString& profileString )
{
    if ( !profileString.isNull() && !profileString.isEmpty() )
    {
        QString profStr = profileString.simplifyWhiteSpace ();
        qDebug("profStr=%s", profStr.latin1() );
        uint strPos=0;
        uint profile_size;

        profile_size=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
        ++strPos;

        m_profile.resize( profile_size );

        for ( uint i=0; i<profile_size; i++ )
        {
            uint sample;
            uint depth;

            sample=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
            ++strPos;
            depth=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
            ++strPos;

            m_profile.setPoint( i, sample, depth );
        }

        m_marks.clear();

        uint marks_size;
        marks_size=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
        ++strPos;

        for ( uint i=0; i<marks_size; i++ )
        {
            uint sample;
            int  imark;
            UDCFMarkerType mark;

            sample=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
            ++strPos;
            imark =profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
            ++strPos;
            mark  =static_cast< UDCFMarkerType >( imark );

            m_marks.insert( pair<uint , UDCFMarkerType>(sample, mark ) );
        }

        m_secsPerSample=profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
        ++strPos;
        m_samples      =profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toUInt();
        ++strPos;
        m_maxDepth     =profStr.section(DIVE_PROFILE_SEPARATOR, strPos, strPos ).toDouble();
        ++strPos;
    }
}

/*
|| Accessors
*/

// All in header file