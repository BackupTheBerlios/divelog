/*******************************************************************************************
* Filename : DiveComputerNotFoundException.cpp																             *
* CVS Id   : $Id: DiveComputerNotFoundException.cpp,v 1.2 2001/12/01 19:21:34 markus Exp $ *
* ---------------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecomputer couldn't             *
*                    be identified.                                                        *
* Owner            : Markus Grunwald                                                       *
* Date of Creation : Thu Nov 15 2001                                                       *
* ---------------------------------------------------------------------------------------- *
* To Do List :                                                                             *
* ---------------------------------------------------------------------------------------- *
* Notes :                                                                                  *
*******************************************************************************************/
static char *DiveComputerNotFoundException_cvs_id="$Id: DiveComputerNotFoundException.cpp,v 1.2 2001/12/01 19:21:34 markus Exp $";

#include "DiveComputerNotFoundException.h"
#include "DivelogDAOException.h"
#include <iostream>

DiveComputerNotFoundException::DiveComputerNotFoundException( const string serialNumber,
                                   														const string model=0,
                                 	 														const string personalInfo=0 )
: DivelogDAOException()
{
    m_serialNumber = serialNumber;
    m_model 			 = model;
    m_personalInfo = personalInfo;
}

ostream& operator << (ostream& os, const DiveComputerNotFoundException e)
{
    os << "DiveComputerNotFoundException:" << endl
        << "\tSerial Number (key-value): "   << e.m_serialNumber << endl
        << "\tModel                    : "   << e.m_model << endl
        << "\tPersonal Info            : "   << e.m_personalInfo << endl;
   return os;
}

