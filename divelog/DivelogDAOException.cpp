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
* Filename : DivelogDAOException.cpp																          *
* CVS Id   : $Id: DivelogDAOException.cpp,v 1.4 2002/06/02 09:55:13 grunwalm Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Base-Exception thrown by DivelogDAO 											*
* Owner            : Markus Grunwald                                          *
* Date of Creation : Thu Nov 15 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char *DivelogDAOException_cvs_id="$Id: DivelogDAOException.cpp,v 1.4 2002/06/02 09:55:13 grunwalm Exp $";

#include "DivelogDAOException.h"
#include<iostream>
#include<string>

DivelogDAOException::DivelogDAOException(const string message = "")
    : m_msg(message)
{
    m_msg = message;
}
    
ostream& operator << (ostream& os, const DivelogDAOException e)
{
   os << "DivelogDAOException(" << e.m_msg << ")";
   return os;
}

