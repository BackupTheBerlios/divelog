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

/**********************************************************************************
* Filename : DiveNotFoundException.h																					    *
* CVS Id   : $Id: DiveNotFoundException.h,v 1.4 2002/08/10 18:15:44 grunwalm Exp $  *
* ------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Dive couldn't be         *
*                    identified.                                                  *
* Owner            : Markus Grunwald                                              *
* Date of Creation : Tue Mar 26 2002                                              *
* ------------------------------------------------------------------------------- *
* To Do List : Just incapsulate (inherit?) a DiveVO ...                           *
* ------------------------------------------------------------------------------- *
* Notes :                                                                         *
**********************************************************************************/
#ifndef DIVE_NOT_FOUND_EXCEPTION
#define DIVE_NOT_FOUND_EXCEPTION

#include "DivelogDAOException.h"
#include <string>
#include <iostream>

class DiveVO;

class DiveNotFoundException : public DivelogDAOException
{
public:
    
    DiveNotFoundException( );
/*
    DiveNotFoundException( const DiveVO& diver );

    friend ostream& operator << (ostream& os, const DiveNotFoundException e);
*/
};

#endif
