/**********************************************************************************
* Filename : DiverNotFoundException.h																					    *
* CVS Id   : $Id: DiverNotFoundException.h,v 1.2 2001/12/21 12:43:56 markus Exp $ *
* ------------------------------------------------------------------------------- *
* Files subject    : Exception thrown by DivelogDAO if a Divecomputer couldn't    *
*                    be identified.                                               *
* Owner            : Markus Grunwald                                              *
* Date of Creation : Thu Nov 15 2001                                              *
* ------------------------------------------------------------------------------- *
* To Do List : Just incapsulate (inherit?) a DiverVO ...                          *
* ------------------------------------------------------------------------------- *
* Notes :                                                                         *
**********************************************************************************/
#ifndef DIVER_NOT_FOUND_EXCEPTION
#define DIVER_NOT_FOUND_EXCEPTION

#include "DivelogDAOException.h"
#include <string>

class ostream;
class DiverVO;

class DiverNotFoundException : public DivelogDAOException
{
public:
    
    DiverNotFoundException( const unsigned int& number=0,
                            const string& first_name="",
                            const string& last_name="",
                            const string& brevet="",
                            const string& street="",
                            const string& house_number="",
                            const int& zip=0,
                            const string& place="",
                            const string& phone="",
                            const string& email="" );

    DiverNotFoundException( const DiverVO& diver );

    friend ostream& operator << (ostream& os, const DiverNotFoundException e);

    unsigned int number() const;
    string first_name() const;
    string last_name() const;
    string brevet() const;
    string street() const;
    string house_number() const;
    int 	 zip() const;
    string place() const;
    string phone() const;
    string email() const;

private:

    unsigned int m_number;
    string m_first_name;
    string m_last_name;
    string m_brevet;
    string m_street;
    string m_house_number;
    int m_zip;
    string m_place;
    string m_phone;
    string m_email;
};

#endif
