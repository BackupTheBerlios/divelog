#ifndef FILLINGSTATIONVO_H
#define FILLINGSTATIONVO_H
/******************************************************************************
* Filename : FillingStationVO.h                                               *
* CVS Id   : $Id: FillingStationVO.h,v 1.1 2001/12/06 08:10:10 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for FillingStationVO.cpp                     *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class FillingStationVO
{
public:
    /*
    || Constructors
    */
    FillingStationVO();
    FillingStationVO( const FillingStationVO& fs );
    FillingStationVO( const unsigned int& number,
    									const string& stationname,
    									const string& first_name,
                      const string& last_name
                    );

    void init( const unsigned int& number,
    					 const string& stationname,
    					 const string& first_name,
               const string& last_name
             );

    /*
    || Accessors
    */

    unsigned int number() const;
    string stationname() const;
    string first_name() const;
    string last_name() const;

    void setNumber ( const unsigned int& number );
    void setStationname( const string& stationname );
    void setFirst_name( const string& first_name );
    void setLast_name( const string& last_name );

    /*
    || Operators
    */

    FillingStationVO& operator=( const FillingStationVO& fs );


private:
    void init();

    unsigned int m_number;
    string m_stationname;
    string m_first_name;
    string m_last_name;

};

#endif
