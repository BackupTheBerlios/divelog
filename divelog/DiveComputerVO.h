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

#ifndef DIVECOMPUTERVO_H
#define DIVECOMPUTERVO_H
/******************************************************************************
* Filename : DiveComputerVO.h                                                 *
* CVS Id   : $Id: DiveComputerVO.h,v 1.4 2002/09/16 17:08:11 grunwalm Exp $   *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveComputerVO.cpp                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <qstring.h>

class DiveComputerVO
{
public:
    /*
    || Constructors
    */
    DiveComputerVO();
    DiveComputerVO( const DiveComputerVO& diveComputer );
    DiveComputerVO( const QString& serial_number,
										const unsigned int& diver_number,
                    const QString& name
                  );

    void init( const QString& serial_number,
							 const unsigned int& diver_number,
               const QString& name
             );

    /*
    || Accessors
    */

    QString serial_number() const;
    unsigned int diver_number() const;
    QString name() const;

    void serial_number ( const QString& serialNumber );
    void diver_number( const unsigned int& diver_number );
    void name( const QString& name );

    /*
    || Operators
    */

    DiveComputerVO& operator=( const DiveComputerVO& diveComputer );


private:
    void init();

    QString m_serial_number;
    unsigned int m_diver_number;
    QString m_name;

};

#endif
