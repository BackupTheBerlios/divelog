/******************************************************************************
* Filename : DiveVO.cpp                                                       *
* CVS Id   : $Id: DiveVO.cpp,v 1.1 2002/02/14 11:31:04 markus Exp $           *
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
#include <qpointarray.h>

#define DIVE_PROFILE_SEPARATOR " "

/*
|| Constructors
*/
DiveVO::DiveVO()
// -------------------------------------------------
// Use : Create an empty Dive Profile Value Object
//       Mostly useless, may vanish some time.
// -------------------------------------------------
{
}

DiveVO::DiveVO( const DiveVO& d )
// -------------------------------------------------
// Use : Copy Constructor for Dive Profile Value Object
// Parameters  : d - the source object
// -------------------------------------------------
{
    (*this)= d ;
}

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
    m_profile       = d.m_profile;
    m_secsPerSample = d.m_secsPerSample;
    m_marks         = d.m_marks;
    m_samples       = d.m_samples;
    m_maxDepth      = d.m_maxDepth;

    return *this;
}

// Stream/Shift Operators
ostream& operator<<( ostream& ostr, DiveVO& profile )
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


/*
|| Accessors
*/

// All in header file