/**********************************************************************************
* Filename : DiveNotFoundException.h																					    *
* CVS Id   : $Id: DiveNotFoundException.h,v 1.1 2002/04/03 11:43:33 markus Exp $  *
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
