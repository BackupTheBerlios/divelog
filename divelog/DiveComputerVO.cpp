/**********************************************************************
* Filename : DiveComputerVO.cpp                                       *
* CVS Id   : $Id*
* ------------------------------------------------------------------- *
* Files subject    : Datastructure holding data about divecomputers 	*
*                    (Value Object)   																*
* Owner            : Markus Grunwald (MG)                             *
* Date of Creation : Thu Nov 22 2001                                  *
* ------------------------------------------------------------------- *
* To Do List :                                                        *
* ------------------------------------------------------------------- *
* Notes :                                                             *
**********************************************************************/
#include "DiveComputerVO.h"

/*
|| Constructors
*/
DiveComputerVO::DiveComputerVO()
{
    init();
}
                  
DiveComputerVO::DiveComputerVO( const DiveComputerVO& diveComputer )
{
    m_serial_number = diveComputer.m_serial_number;
    m_diver_number  = diveComputer.m_diver_number;
    m_name   				= diveComputer.m_name;
}

DiveComputerVO::DiveComputerVO( const string& serial_number,
																const unsigned int& diver_number,
                    						const string& name)
{
    init( serial_number, diver_number, name );
}

void DiveComputerVO::init( const string& serial_number,
													 const unsigned int& diver_number,
                    			 const string& name )
{
    m_serial_number = serial_number;
    m_diver_number  = diver_number;
    m_name   				= name;
}

DiveComputerVO& DiveComputerVO::operator=( const DiveComputerVO& diveComputer )
{
    m_serial_number = diveComputer.m_serial_number;
    m_diver_number  = diveComputer.m_diver_number;
    m_name   				= diveComputer.m_name;
}

void DiveComputerVO::init()
{
}

/*
|| Accessors
*/

string DiveComputerVO::serial_number() const
{
    return m_serial_number;
}

unsigned int DiveComputerVO::diver_number() const
{
    return m_diver_number;
}

string DiveComputerVO::name() const
{
    return m_name;
}


void DiveComputerVO::setSerial_number ( const string& serial_number )
{
    m_serial_number=serial_number;
}

void DiveComputerVO::setDiver_number( const unsigned int& diver_number )
{
    m_diver_number=diver_number;
}

void DiveComputerVO::setName( const string& name )
{
    m_name=name;
}
