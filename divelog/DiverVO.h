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

#ifndef DIVERVO_H
#define DIVERVO_H
/******************************************************************************
* Filename : DiverVO.h                                                        *
* CVS Id   : $Id: DiverVO.h,v 1.7 2002/09/16 17:08:11 grunwalm Exp $          *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiverVO.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <qstring.h>

class DiverVO
{
public:

    /*
    || Constructors
    */
    DiverVO();
    DiverVO( const DiverVO& d );
    DiverVO( const unsigned int& number,
             const QString& first_name,
             const QString& last_name,
             const QString& brevet,
             const QString& street,
             const QString& house_number,
             const int& zip,
             const QString& place,
             const QString& phone,
             const QString& email );

    void init( const unsigned int& number,
               const QString& first_name,
               const QString& last_name,
               const QString& brevet,
               const QString& street,
               const QString& house_number,
               const int& zip,
               const QString& place,
               const QString& phone,
               const QString& email );

    /*
    || Accessors
    */

    unsigned int number() const;
    QString first_name() const;
    QString last_name() const;
    QString brevet() const;
    QString street() const;
    QString house_number() const;
    int 	 zip() const;
    QString place() const;
    QString phone() const;
    QString email() const;

    void number ( const unsigned int& number );
    void first_name ( const QString& first_name );
    void last_name ( const QString& last_name );
    void brevet ( const QString& brevet );
    void street ( const QString& street );
    void house_number( const QString& house_number );
    void zip	( const int& zip );
    void place	( const QString& place );
    void phone ( const QString& phone );
    void email	( const QString& email );

    /*
    || Operators
    */

    DiverVO& operator=( const DiverVO& d );

protected:
    void init();

private:

    unsigned int m_number;
    QString m_first_name;
    QString m_last_name;
    QString m_brevet;
    QString m_street;
    QString m_house_number;
    int m_zip;
    QString m_place;
    QString m_phone;
    QString m_email;
};


#endif
