#ifndef DIVELISTVO_H
#define DIVELISTVO_H
/******************************************************************************
* Filename : DiveListVO.h                                                     *
* CVS Id   : $Id: DiveListVO.h,v 1.1 2002/03/25 08:41:44 markus Exp $         *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveListVO.cpp                           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Mon Mar 18 2002                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveListVO
{
public:
    /*
    || Constructors
    */
    DiveListVO();
    DiveListVO( const DiveListVO& d );
    DiveListVO( const int&    number,
                const string& date,  // DATETIME split up
                const string& time,
                const int&    diver_number,
                const string& place,
                const string& location );

    void init( const int&    number,
               const string& date,  // DATETIME split up
               const string& time,
               const int&    diver_number,
               const string& place,
               const string& location );

    /*
    || Accessors
    */
    void setNumber( const int& number );
    void setDate( const string& date );
    void setTime( const string& time );
    void setDiver_number( const int& diver_number );
    void setPlace( const string& place );
    void setLocation( const string& location );

    int    number() const 								{ return m_number; }
    string date() const   								{ return m_date; }
    string time() const   								{ return m_time; }
    int    diver_number() const 					{ return m_diver_number; }
    string place() const  								{ return m_place; }
    string location() const 							{ return m_location; }

    /*
    || Operators
    */

    DiveListVO& operator=( const DiveListVO& d );


private:
    void init();

    int    m_number;
    string m_date;  // DATETIME split up
    string m_time;
    int    m_diver_number;
    string m_place;
    string m_location;
};


#endif
