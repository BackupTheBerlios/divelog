/* Copyright 2002 Markus Grunwald */
/* All other Copyrights (especially Qt and mysql) belong to their owners */

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

#ifndef DIVEPROFILEVO_H
#define DIVEPROFILEVO_H
/******************************************************************************
* Filename : DiveProfileVO.h                                                  *
* CVS Id   : $Id: DiveProfileVO.h,v 1.4 2002/05/15 09:27:51 grunwalm Exp $      *
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
