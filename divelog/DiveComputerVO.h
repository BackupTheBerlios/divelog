#ifndef DIVECOMPUTERVO_H
#define DIVECOMPUTERVO_H
/******************************************************************************
* Filename : DiveComputerVO.h                                                 *
* CVS Id   : $Id: DiveComputerVO.h,v 1.1 2001/12/12 09:31:55 markus Exp $ *
* --------------------------------------------------------------------------- *
* Files subject    : Header File for DiveComputerVO.cpp                       *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Thu Nov 22 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

#include <string>

class DiveComputerVO
{
public:
    /*
    || Constructors
    */
    DiveComputerVO();
    DiveComputerVO( const DiveComputerVO& diveComputer );
    DiveComputerVO( const string& serial_number,
										const unsigned int& diver_number,
                    const string& name
                  );

    void init( const string& serial_number,
							 const unsigned int& diver_number,
               const string& name
             );

    /*
    || Accessors
    */

    string serial_number() const;
    unsigned int diver_number() const;
    string name() const;

    void setSerial_number ( const string& serialNumber );
    void setDiver_number( const unsigned int& diver_number );
    void setName( const string& name );

    /*
    || Operators
    */

    DiveComputerVO& operator=( const DiveComputerVO& diveComputer );


private:
    void init();

    string m_serial_number;
    unsigned int m_diver_number;
    string m_name;

};

#endif
