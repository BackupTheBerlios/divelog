#ifndef DIVERVO_H
#define DIVERVO_H
/******************************************************************************
* Filename : DiverVO.h                                                        *
* CVS Id   : $Id: DiverVO.h,v 1.2 2001/11/23 15:59:06 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiverVO.cpp                              *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiverVO
{
public:
    /*
    || Constructors
    */
    DiverVO();
    DiverVO( const DiverVO& d );
    DiverVO( const int& number, const string& first_name, const string& last_name, const string& brevet,
    			   const string& street, const string& house_number, const int& zip, const string& place,
    			   const string& phone, const string& email );

    void init( const int& number, const string& first_name, const string& last_name, const string& brevet,
    			 const string& street, const string& house_number, const int& zip, const string& place,
    			 const string& phone, const string& email );

    /*
    || Accessors
    */

    int 	 number() const;
    string first_name() const;
    string last_name() const;
    string brevet() const;
    string street() const;
    string house_number() const;
    int 	 zip() const;
    string place() const;
    string phone() const;
    string email() const;

    void setNumber ( const int& number );
    void setFirst_name ( const string& first_name );
    void setLast_name ( const string& last_name );
    void setBrevet ( const string& brevet );
    void setStreet ( const string& street );
    void setHouse_number( const string& house_number );
    void setZip	( const int& zip );
    void setPlace	( const string& place );
    void setPhone ( const string& phone );
    void setEmail	( const string& email );

    /*
    || Operators
    */

    DiverVO& operator=( const DiverVO& d );


private:
    void init();

    int m_number;
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
