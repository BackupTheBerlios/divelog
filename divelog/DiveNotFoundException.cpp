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

/************************************************************************************
* Filename : DiveNotFoundException.cpp																              *
* CVS Id   : $Id: DiveNotFoundException.cpp,v 1.4 2002/09/16 17:08:11 grunwalm Exp $ *
* --------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Dive couldn't              *
*                    be identified.                                                 *
* Owner            : Markus Grunwald                                                *
* Date of Creation : Tue Mar 26 2002                                                *
* --------------------------------------------------------------------------------- *
* To Do List :  Just incapsulate (inherit?) a DiveVO ...                            *
* --------------------------------------------------------------------------------- *
* Notes :                                                                           *
*************************************************************************************/
static char DiveNotFoundException_cvs_id[]="$Id: DiveNotFoundException.cpp,v 1.4 2002/09/16 17:08:11 grunwalm Exp $";

#include "DiveNotFoundException.h"
#include "DivelogDAOException.h"
#include <iostream>
                                               
DiveNotFoundException::DiveNotFoundException( )
: DivelogDAOException()
{
    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DiveNotFoundException_cvs_id[0]+=0;
}


