/* Copyright 2002 Markus Grunwald */
/* All other Copyrights (especially Qt and mysql) belong to their owners */

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
* CVS Id   : $Id: DiveNotFoundException.h,v 1.2 2002/05/15 09:27:51 grunwalm Exp $  *
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

class ostream;
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
