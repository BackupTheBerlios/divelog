#ifndef DIVEPROFILEVO_H
#define DIVEPROFILEVO_H
/******************************************************************************
* Filename : DiveProfileVO.h                                                  *
* CVS Id   : $Id: DiveProfileVO.h,v 1.2 2002/02/08 16:41:33 markus Exp $      *
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

    map< uint, UDCFMarkerType > marks() const { return m_marks; }

    uint        secsPerSample() const { return m_secsPerSample; }
    uint        samples() const { return m_samples; }
    double      maxDepth() const { return m_maxDepth; }

    /*
    || Operators
    */

    DiveProfileVO& operator=( const DiveProfileVO& p );

    friend ostream& operator<<( ostream& ostr, DiveProfileVO& profile );
    friend istream& operator>>( istream& istr, DiveProfileVO& profile );

private:
    void init();

    QPointArray m_profile;
    map< uint, UDCFMarkerType > m_marks;

    uint m_secsPerSample;
    uint m_samples;
    double m_maxDepth;
};


#endif
