/**********************************************************************
* Filename : DiveTypeVO.cpp                                           *
* CVS Id   : $Id: DiveTypeVO.cpp,v 1.1 2001/12/06 12:45:00 markus Exp $                                                     *
* ------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divetypes	      *
*                    (Value Object)   																*
* Owner            : Markus Grunwald (MG)                             *
* Date of Creation : Thu Nov 22 2001                                  *
* ------------------------------------------------------------------- *
* To Do List :                                                        *
* ------------------------------------------------------------------- *
* Notes :                                                             *
**********************************************************************/
#include "DiveTypeVO.h"

/*
|| Constructors
*/
DiveTypeVO::DiveTypeVO()
{
    init();
}

DiveTypeVO::DiveTypeVO( const DiveTypeVO& diveType )
{
    m_number       = diveType.m_number;
    m_description  = diveType.m_description;
}

DiveTypeVO::DiveTypeVO( const unsigned int& number,
                        const string& description
											)
{
    init( number, description );
}

void DiveTypeVO::init( const unsigned int& number,
                       const string& description
                     )
{
    m_number       = number;
    m_description  = description;
}

DiveTypeVO& DiveTypeVO::operator=( const DiveTypeVO& diveType )
{
    m_number       = diveType.m_number;
    m_description  = diveType.m_description;
}

void DiveTypeVO::init()
{
}

/*
|| Accessors
*/

unsigned int DiveTypeVO::number() const
{
    return m_number;
}

string DiveTypeVO::description() const
{
    return m_description;
}



void DiveTypeVO::setNumber ( const unsigned int& number )
{
    m_number=number;
}

void DiveTypeVO::setDescription( const string& description )
{
    m_description=description;
}

