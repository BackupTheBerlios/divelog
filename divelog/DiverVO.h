#ifndef DIVERVO_H
#define DIVERVO_H
/******************************************************************************
* Filename : DiverVO.h                                                        *
* CVS Id   : $Id: DiverVO.h,v 1.1 2001/11/23 14:36:52 markus Exp $                                                             *
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

    void number ( const int& number );
    void first_name ( const string& first_name );
    void last_name ( const string& last_name );
    void brevet ( const string& brevet );
    void street ( const string& street );
    void house_number( const string& house_number );
    void zip	( const int& zip );
    void place	( const string& place );
    void phone ( const string& phone );
    void email	( const string& email );

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
