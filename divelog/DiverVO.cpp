/******************************************************************************
* Filename : DiverVO.cpp                                                      *
* CVS Id   : $Id: DiverVO.cpp,v 1.1 2001/11/23 14:36:52 markus Exp $                                                             *
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

DiverVO::DiverVO( const int& number, const string& first_name, const string& last_name, const string& brevet,
    			   const string& street, const string& house_number, const int& zip, const string& place,
    			   const string& phone, const string& email )
{
    init( number, first_name, last_name, brevet, street,
          house_number, zip, place, phone, email);
}

void DiverVO::init( const int& number, const string& first_name, const string& last_name, const string& brevet,
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

/*
|| Accessors
*/

inline int DiverVO::number() const
{
    return m_number;
}

inline string DiverVO::first_name() const
{
    return m_first_name;
}

inline string DiverVO::last_name() const
{
    return m_last_name;
}

inline string DiverVO::brevet() const
{
    return m_brevet;
}

inline string DiverVO::street() const
{
    return m_street;
}

inline string DiverVO::house_number() const
{
    return m_house_number;
}

inline int 	 DiverVO::zip() const
{
    return m_zip;
}

inline string DiverVO::place() const
{
    return m_place;
}

inline string DiverVO::phone() const
{
    return m_phone;
}

inline string DiverVO::email() const
{
    return m_email;
}

inline void DiverVO::number ( const int& number )
{
    m_number=number;
}

inline void DiverVO::first_name ( const string& first_name )
{
    m_first_name=first_name;
}

inline void DiverVO::last_name ( const string& last_name )
{
    m_last_name=last_name;
}

inline void DiverVO::brevet ( const string& brevet )
{
    m_brevet=brevet;
}

inline void DiverVO::street ( const string& street )
{
    m_street=street;
}

inline void DiverVO::house_number( const string& house_number )
{
    m_house_number=house_number;
}

inline void DiverVO::zip	( const int& zip )
{
    m_zip=zip;
}

inline void DiverVO::place	( const string& place )
{
    m_place=place;
}

inline void DiverVO::phone ( const string& phone )
{
    m_phone=phone;
}

inline void DiverVO::email	( const string& email )
{
    m_email=email;
}

