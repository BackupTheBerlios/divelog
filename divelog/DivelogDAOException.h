/*******************************************************************************
* Filename : DivelogDAOException.h																						 *
* CVS Id   : $Id: DivelogDAOException.h,v 1.2 2002/02/04 10:07:44 markus Exp $ *
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
class ostream;

class DivelogDAOException : public exception
{
public:
    
    DivelogDAOException(const string message = "");
    friend ostream& operator << (ostream& os, const DivelogDAOException e);

    const char* what () const
    {
        cerr << "Exception.what() called." << endl;
        return m_msg.c_str();
    }

protected:
    string m_msg;
};

#endif
