#ifndef DIVEPROFILEVO_H
#define DIVEPROFILEVO_H
/******************************************************************************
* Filename : DiveProfileVO.h                                                  *
* CVS Id   : $Id: DiveProfileVO.h,v 1.1 2002/02/05 20:10:15 markus Exp $      *
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
    uint        secsPerSample() const { return m_secsPerSample; }
    uint        samples() const { return m_samples; }
    double      maxDepth() const { return m_maxDepth; }

    /*
    || Operators
    */

    DiveProfileVO& operator=( const DiveProfileVO& p );


private:
    void init();

    QPointArray m_profile;
    uint m_secsPerSample;
    uint m_samples;
    double m_maxDepth;
};


#endif
