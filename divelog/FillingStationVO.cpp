/**********************************************************************
* Filename : FillingStationVO.cpp                                     *
* CVS Id   : $Id: FillingStationVO.cpp,v 1.1 2001/12/06 08:10:10 markus Exp $                                                     *
* ------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about fillingstations	*
*                    (Value Object)   																*
* Owner            : Markus Grunwald (MG)                             *
* Date of Creation : Thu Nov 22 2001                                  *
* ------------------------------------------------------------------- *
* To Do List :                                                        *
* ------------------------------------------------------------------- *
* Notes :                                                             *
**********************************************************************/
#include "FillingStationVO.h"

/*
|| Constructors
*/
FillingStationVO::FillingStationVO()
{
    init();
}

FillingStationVO::FillingStationVO( const FillingStationVO& fs )
{
    m_number       = fs.m_number;
    m_stationname  = fs.m_stationname;
    m_first_name   = fs.m_first_name;
    m_last_name    = fs.m_last_name;;
}

FillingStationVO::FillingStationVO( const unsigned int& number,
                                    const string& stationname,
                                    const string& first_name,
                                    const string& last_name )
{
    init( number, stationname, first_name, last_name );
}

void FillingStationVO::init( const unsigned int& number,
                             const string& stationname,
                             const string& first_name,
                             const string& last_name )
{
    m_number       = number;
    m_stationname  = stationname;
    m_first_name   = first_name;
    m_last_name    = last_name;
}

FillingStationVO& FillingStationVO::operator=( const FillingStationVO& fs )
{
    m_number       = fs.m_number;
    m_stationname  = fs.m_stationname;
    m_first_name   = fs.m_first_name;
    m_last_name    = fs.m_last_name;;
}

void FillingStationVO::init()
{
}

/*
|| Accessors
*/

unsigned int FillingStationVO::number() const
{
    return m_number;
}

string FillingStationVO::stationname() const
{
    return m_stationname;
}

string FillingStationVO::first_name() const
{
    return m_first_name;
}

string FillingStationVO::last_name() const
{
    return m_last_name;
}


void FillingStationVO::setNumber ( const unsigned int& number )
{
    m_number=number;
}

void FillingStationVO::setStationname( const string& stationname )
{
    m_stationname=stationname;
}

void FillingStationVO::setFirst_name( const string& first_name )
{
    m_first_name=first_name;
}

void FillingStationVO::setLast_name( const string& last_name )
{
    m_last_name=last_name;
}

