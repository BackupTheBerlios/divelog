/******************************************************************************
* Filename : DiverVO.cpp                                                      *
* CVS Id   : $Id: DiverVO.cpp,v 1.3 2001/12/01 19:21:35 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divers (Value Object)   *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#include "DiverVO.h"


/*
|| Constructors
*/
DiverVO::DiverVO()
{
    init();
}

DiverVO::DiverVO( const DiverVO& d )
{
    m_number       = d.m_number;
    m_first_name   = d.m_first_name;
    m_last_name    = d.m_last_name;
    m_brevet       = d.m_brevet;
    m_street       = d.m_street;
    m_house_number = d.m_house_number;
    m_zip          = d.m_zip;
    m_place        = d.m_place;
    m_phone        = d.m_phone;
    m_email        = d.m_email;
}

DiverVO::DiverVO( const unsigned int& number, const string& first_name, const string& last_name, const string& brevet,
    			   const string& street, const string& house_number, const int& zip, const string& place,
    			   const string& phone, const string& email )
{
    init( number, first_name, last_name, brevet, street,
          house_number, zip, place, phone, email);
}

void DiverVO::init( const unsigned int& number, const string& first_name, const string& last_name, const string& brevet,
    			 const string& street, const string& house_number, const int& zip, const string& place,
    			 const string& phone, const string& email )
{
    m_number       = number;
    m_first_name   = first_name;
    m_last_name    = last_name;
    m_brevet       = brevet;
    m_street       = street;
    m_house_number = house_number;
    m_zip          = zip;
    m_place        = place;
    m_phone        = phone;
    m_email        = email;
}

DiverVO& DiverVO::operator=( const DiverVO& d )
{
    m_number       = d.m_number;
    m_first_name   = d.m_first_name;
    m_last_name    = d.m_last_name;
    m_brevet       = d.m_brevet;
    m_street       = d.m_street;
    m_house_number = d.m_house_number;
    m_zip          = d.m_zip;
    m_place        = d.m_place;
    m_phone        = d.m_phone;
    m_email        = d.m_email;
}

void DiverVO::init()
{
}

/*
|| Accessors
*/

unsigned int DiverVO::number() const
{
    return m_number;
}

string DiverVO::first_name() const
{
    return m_first_name;
}

string DiverVO::last_name() const
{
    return m_last_name;
}

string DiverVO::brevet() const
{
    return m_brevet;
}

string DiverVO::street() const
{
    return m_street;
}

string DiverVO::house_number() const
{
    return m_house_number;
}

int 	 DiverVO::zip() const
{
    return m_zip;
}

string DiverVO::place() const
{
    return m_place;
}

string DiverVO::phone() const
{
    return m_phone;
}

string DiverVO::email() const
{
    return m_email;
}



void DiverVO::setNumber ( const unsigned int& number )
{
    m_number=number;
}

void DiverVO::setFirst_name ( const string& first_name )
{
    m_first_name=first_name;
}

void DiverVO::setLast_name ( const string& last_name )
{
    m_last_name=last_name;
}

void DiverVO::setBrevet ( const string& brevet )
{
    m_brevet=brevet;
}

void DiverVO::setStreet ( const string& street )
{
    m_street=street;
}

void DiverVO::setHouse_number( const string& house_number )
{
    m_house_number=house_number;
}

void DiverVO::setZip	( const int& zip )
{
    m_zip=zip;
}

void DiverVO::setPlace	( const string& place )
{
    m_place=place;
}

void DiverVO::setPhone ( const string& phone )
{
    m_phone=phone;
}

void DiverVO::setEmail	( const string& email )
{
    m_email=email;
}

