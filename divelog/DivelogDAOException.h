/******************************************************************************
* Filename : DivelogDAOException.h																						*
* CVS Id   : $Id: DivelogDAOException.h,v 1.1 2001/11/19 18:52:55 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header for DivelogDAOException                           *
* Owner            : Markus Grunwald                                          *
* Date of Creation : Thu Nov 15 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
#ifndef DIVELOG_DAO_EXCEPTION
#define DIVELOG_DAO_EXCEPTION
#include <string>

class ostream;

class DivelogDAOException
{
public:
    
    DivelogDAOException(const string message = "");
    friend ostream& operator << (ostream& os, const DivelogDAOException e);

protected:
    string m_msg;
};

#endif
