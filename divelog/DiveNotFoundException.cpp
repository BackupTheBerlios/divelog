/************************************************************************************
* Filename : DiveNotFoundException.cpp																              *
* CVS Id   : $Id: DiveNotFoundException.cpp,v 1.1 2002/04/03 11:43:33 markus Exp $ *
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
static char *DiveNotFoundException_cvs_id="$Id: DiveNotFoundException.cpp,v 1.1 2002/04/03 11:43:33 markus Exp $";

#include "DiveNotFoundException.h"
#include "DivelogDAOException.h"
#include <iostream>
                                               
DiveNotFoundException::DiveNotFoundException( )
: DivelogDAOException()
{
}


