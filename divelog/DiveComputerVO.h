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

#ifndef DIVECOMPUTERVO_H
#define DIVECOMPUTERVO_H
/******************************************************************************
* Filename : DiveComputerVO.h                                                 *
* CVS Id   : $Id: DiveComputerVO.h,v 1.2 2002/05/15 09:27:51 grunwalm Exp $ *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveComputerVO.cpp                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveComputerVO
{
public:
    /*
    || Constructors
    */
    DiveComputerVO();
    DiveComputerVO( const DiveComputerVO& diveComputer );
    DiveComputerVO( const string& serial_number,
										const unsigned int& diver_number,
                    const string& name
                  );

    void init( const string& serial_number,
							 const unsigned int& diver_number,
               const string& name
             );

    /*
    || Accessors
    */

    string serial_number() const;
    unsigned int diver_number() const;
    string name() const;

    void setSerial_number ( const string& serialNumber );
    void setDiver_number( const unsigned int& diver_number );
    void setName( const string& name );

    /*
    || Operators
    */

    DiveComputerVO& operator=( const DiveComputerVO& diveComputer );


private:
    void init();

    string m_serial_number;
    unsigned int m_diver_number;
    string m_name;

};

#endif
