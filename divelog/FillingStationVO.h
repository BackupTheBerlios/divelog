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

#ifndef FILLINGSTATIONVO_H
#define FILLINGSTATIONVO_H
/******************************************************************************
* Filename : FillingStationVO.h                                               *
* CVS Id   : $Id: FillingStationVO.h,v 1.4 2002/09/16 17:08:11 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for FillingStationVO.cpp                     *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <qstring.h>

class FillingStationVO
{
public:
    /*
    || Constructors
    */
    FillingStationVO();
    FillingStationVO( const FillingStationVO& fs );
    FillingStationVO( const unsigned int& number,
    									const QString& stationname,
    									const QString& first_name,
                      const QString& last_name
                    );

    void init( const unsigned int& number,
    					 const QString& stationname,
    					 const QString& first_name,
               const QString& last_name
             );

    /*
    || Accessors
    */

    unsigned int number() const;
    QString stationname() const;
    QString first_name() const;
    QString last_name() const;

    void number ( const unsigned int& number );
    void stationname( const QString& stationname );
    void first_name( const QString& first_name );
    void last_name( const QString& last_name );

    /*
    || Operators
    */

    FillingStationVO& operator=( const FillingStationVO& fs );


private:
    void init();

    unsigned int m_number;
    QString m_stationname;
    QString m_first_name;
    QString m_last_name;

};

#endif
