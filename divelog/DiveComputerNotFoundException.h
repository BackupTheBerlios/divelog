/******************************************************************************
* Filename : DiveComputerNotFoundException.h																	*
* CVS Id   : $Id: DiveComputerNotFoundException.h,v 1.2 2001/11/19 19:37:04 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecomputer couldn't*
*                    be identified.                                           *
* Owner            : Markus Grunwald                                          *
* Date of Creation : Thu Nov 15 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#ifndef DIVECOMPUTER_NOT_FOUND_EXCEPTION
#define DIVECOMPUTER_NOT_FOUND_EXCEPTION

#include "DivelogDAOException.h"
#include <string>

class ostream;

class DiveComputerNotFoundException : public DivelogDAOException
{
public:
    
    DiveComputerNotFoundException( const string serialNumber,
                                   const string model=0,
                                 	 const string personalInfo=0 );
    friend ostream& operator << (ostream& os, const DiveComputerNotFoundException e);

    const string model() const
    {
        return m_model;
    }

    const string serialNumber() const
    {
        return m_serialNumber;
    }

    const string personalInfo() const
    {
        return m_personalInfo;
    }

private:

    string m_serialNumber;
    string m_model;
    string m_personalInfo;
};

#endif
