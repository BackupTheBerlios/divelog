#ifndef DIVEPROFILEVO_H
#define DIVEPROFILEVO_H
/******************************************************************************
* Filename : DiveProfileVO.h                                                  *
* CVS Id   : $Id: DiveProfileVO.h,v 1.3 2002/04/03 11:43:33 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveProfileVO.cpp                        *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>
#include <UDCF.h>
#include <qpointarray.h>
#include <map>
#include <iostream>

class DiveProfileVO
{
public:

    typedef map< uint, UDCFMarkerType> marker_map;

    /*
    || Constructors
    */
    DiveProfileVO();
    DiveProfileVO( const DiveProfileVO& d );
    DiveProfileVO( const UDCFSample* samples, const uint maxIndex );

    void init( const UDCFSample* samples );

    /*
    || Accessors
    */

    QPointArray profile() const { return m_profile; }

    marker_map  marks() const { return m_marks; }

    uint        secsPerSample() const { return m_secsPerSample; }
    uint        samples() const { return m_samples; }
    double      maxDepth() const { return m_maxDepth; }

    /*
    || Operators
    */

    DiveProfileVO& operator=( const DiveProfileVO& p );

    friend ostream& operator<<( ostream& ostr, const DiveProfileVO& profile );
    friend istream& operator>>( istream& istr, DiveProfileVO& profile );
    friend string&  operator>>( string&   str, DiveProfileVO& profile );

private:
    void init();

    QPointArray m_profile;
    marker_map  m_marks;

    uint m_secsPerSample;
    uint m_samples;
    double m_maxDepth;
};


#endif
