/******************************************************************************
* Filename : DivelogDAOException.cpp																          *
* CVS Id   : $Id: DivelogDAOException.cpp,v 1.1 2001/11/19 18:52:55 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Base-Exception thrown by DivelogDAO 											*
* Owner            : Markus Grunwald                                          *
* Date of Creation : Thu Nov 15 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char *DivelogDAOException_cvs_id="$Id: DivelogDAOException.cpp,v 1.1 2001/11/19 18:52:55 markus Exp $";

#include "DivelogDAOException.h"
#include<iostream>
#include<string>

DivelogDAOException::DivelogDAOException(const string message = "")
{
    m_msg = message;
}
    
ostream& operator << (ostream& os, const DivelogDAOException e)
{
   os << "DivelogDAOException(" << e.m_msg << ")";
   return os;
}

