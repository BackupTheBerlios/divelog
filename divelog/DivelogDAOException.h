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

/*******************************************************************************
* Filename : DivelogDAOException.h																						 *
* CVS Id   : $Id: DivelogDAOException.h,v 1.5 2002/08/10 18:15:44 grunwalm Exp $ *
* ---------------------------------------------------------------------------- *
* Files subject    : Header for DivelogDAOException                            *
* Owner            : Markus Grunwald                                           *
* Date of Creation : Thu Nov 15 2001                                           *
* ---------------------------------------------------------------------------- *
* To Do List :                                                                 *
* ---------------------------------------------------------------------------- *
* Notes :                                                                      *
*******************************************************************************/
#ifndef DIVELOG_DAO_EXCEPTION
#define DIVELOG_DAO_EXCEPTION
#include <string>                      
#include <iostream.h>

using namespace std;

class DivelogDAOException //: public exception
{
public:
    
    DivelogDAOException( const string message = "");
    ~DivelogDAOException() throw(){};
    friend ostream& operator << (ostream& os, const DivelogDAOException e);

    const char* what () const throw()
    {
        cerr << "Exception.what() called." << endl;
        return m_msg.c_str();
    }

protected:
    string m_msg;
};

#endif
