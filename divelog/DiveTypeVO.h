#ifndef DIVETYPE_H
#define DIVETYPE_H
/******************************************************************************
* Filename : DiveTypeVO.h                                                     *
* CVS Id   : $Id: DiveTypeVO.h,v 1.1 2001/12/06 12:45:00 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveTypeVO.cpp                           *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveTypeVO
{
public:
    /*
    || Constructors
    */
    DiveTypeVO();
    DiveTypeVO( const DiveTypeVO& fs );
    DiveTypeVO( const unsigned int& number,
    						const string& description
    					);

    void init( const unsigned int& number,
    					 const string& description
             );

    /*
    || Accessors
    */

    unsigned int number() const;
    string description() const;

    void setNumber ( const unsigned int& number );
    void setDescription( const string& description );

    /*
    || Operators
    */

    DiveTypeVO& operator=( const DiveTypeVO& diveType );


private:
    void init();

    unsigned int m_number;
    string 			 m_description;

};

#endif
