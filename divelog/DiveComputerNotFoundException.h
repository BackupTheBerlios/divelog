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

/******************************************************************************
* Filename : DiveComputerNotFoundException.h																	*
* CVS Id   : $Id: DiveComputerNotFoundException.h,v 1.5 2002/08/10 18:15:44 grunwalm Exp $                                                             *
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
#include <iostream>

class DiveComputerNotFoundException : public DivelogDAOException
{
public:
    
    DiveComputerNotFoundException( const string serialNumber,
                                   const string model=0,
                                 	 const string personalInfo=0 );
    ~DiveComputerNotFoundException() throw();

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
