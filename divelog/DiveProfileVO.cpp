/******************************************************************************
* Filename : DiveProfileVO.cpp                                                *
* CVS Id   : $Id: DiveProfileVO.cpp,v 1.1 2002/02/05 20:10:15 markus Exp $    *
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
#include <qpointarray.h>

/*
|| Constructors
*/
DiveProfileVO::DiveProfileVO()
{
    init();
}

DiveProfileVO::DiveProfileVO( const DiveProfileVO& d )
{
    m_profile       = d.m_profile;
    m_secsPerSample = d.m_secsPerSample;
}

DiveProfileVO::DiveProfileVO( const UDCFSample* samples, const uint maxIndex )
{
    m_profile.resize( maxIndex ); // This is too big because maxIndex contains
    															// marks and other infos as well
																  // So resize it later to the proper size
    uint depth_count=0;           // Counts real depth Values;
    uint mark_count=0;            // Counts marks

    m_maxDepth=0;

    for ( uint i=0 ; i<maxIndex; i++ )
    {
        cerr << "Sample Type : " << samples[i].type << endl;

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
            mark_count++;
            break;
        case ST_MIX:
            break;
        case ST_SAMPLETIME:
            m_secsPerSample=(uint) samples[i].data.sampleTime; // FIXME: any doubles
                                                               //        possible ?
            cout << "\t Sampletime: "
                 << m_secsPerSample << endl;
            break;
        case ST_WORK: // Don't know
            break;
        default:
            break;
        }
    }
    cout << depth_count << " Depth Values" << endl;
    cout << mark_count << " Mark Values" << endl;
    cout << "Max Depth:" << m_maxDepth << endl;

    m_profile.resize( depth_count ); // Now we know for sure how many depth values
                                     // we have, so we trim them.
}

void DiveProfileVO::init()
{
}

DiveProfileVO& DiveProfileVO::operator=( const DiveProfileVO& d )
{
    m_profile       = d.m_profile;
    m_secsPerSample = d.m_secsPerSample;
}

/*
|| Accessors
*/

// All in header file