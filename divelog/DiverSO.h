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

#ifndef DIVERSO_H
#define DIVERSO_H
/******************************************************************************
* Filename : DiverSO.h                                                        *
* CVS Id   : $Id: DiverSO.h,v 1.1 2002/09/16 17:08:11 grunwalm Exp $          *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiverSO.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thr Aug 29 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include "DiverVO.h"

class DiverSO
{
public:
    enum SearchFieldEnum
    {
        SF_invalidLow   = -1,
        SF_empty        =  0,
        SF_number       =  1 <<  0,
        SF_first_name   =  1 <<  1,
        SF_last_name    =  1 <<  2,
        SF_brevet       =  1 <<  3,
        SF_street       =  1 <<  4,
        SF_house_number =  1 <<  5,
        SF_zip          =  1 <<  6,
        SF_place        =  1 <<  7,
        SF_phone        =  1 <<  8,
        SF_email        =  1 <<  9,
        SF_all          = (1 << 10)-1,
        SF_invalidHigh  =  1 << 10
    };
    
    /*
    || Constructors
    */

    DiverSO();

    DiverSO( const DiverSO& d ) 
    {
        m_diver       = d.m_diver;
        m_searchField = d.m_searchField;
    };

    DiverSO( const unsigned int& number,
             const QString& first_name,
             const QString& last_name,
             const QString& brevet,
             const QString& street,
             const QString& house_number,
             const int& zip,
             const QString& place,
             const QString& phone,
             const QString& email,
             const SearchFieldEnum& sfe
           ) : m_diver( number, first_name, last_name,
                        brevet, street, house_number,
                        zip, place, phone, email )
    {
        m_searchField = sfe;
    };

/*
|| Accessors
*/
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

    unsigned int number() const    { return m_diver.number(); }
    QString first_name() const     { return m_diver.first_name(); }
    QString last_name() const      { return m_diver.last_name(); }
    QString brevet() const         { return m_diver.brevet(); }
    QString street() const         { return m_diver.street(); }
    QString house_number() const   { return m_diver.house_number(); }
    int  	  zip() const            { return m_diver.zip(); }
    QString place() const          { return m_diver.place(); }
    QString phone() const          { return m_diver.phone(); }
    QString email() const          { return m_diver.email(); }

    SearchFieldEnum searchField() const
    {
        return m_searchField;
    }

    void addSearchField( const SearchFieldEnum& sfe )
    {
        m_searchField = static_cast< SearchFieldEnum > ( m_searchField | sfe );
    }

    void clearSearchField( const SearchFieldEnum& sfe= SF_empty );
    bool checkSearchField( const SearchFieldEnum& sfe ) const;

    bool checkMoreFields( const SearchFieldEnum& sfe ) const;


/*
|| Operators
*/

    DiverSO& operator=( const DiverSO& d )
    {
        m_diver       = d.m_diver;
        m_searchField = d.m_searchField;

        return *this;
    }

private:
    SearchFieldEnum m_searchField;
    DiverVO         m_diver;

};


#endif // DIVERSO_H
