#ifndef CHANGE_ME
#define CHANGE_ME
/******************************************************************************
* Filename : divelogdao.h                                                     *
* CVS Id   : $Id: DivelogDAO.h,v 1.2 2001/11/09 14:13:26 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Header file for divelogdao.cpp                           *
* Owner            : Markus Grunwald                                          *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/

// FIXME: move this info to a better place
#define MYSQL_DATABASE "divelog-test"
#define MYSQL_HOST   "localhost"
#define MYSQL_USER   "markus"
#define MYSQL_PASSWD "ArPPCa"

class Connection;

class DivelogDAO
{
public:
    DivelogDAO( char* db=MYSQL_DATABASE, char* host=MYSQL_HOST, char* user=MYSQL_USER, char* passwd=MYSQL_PASSWD );
    ~DivelogDAO();

    void importUDCFFile( char* filename );
private:
     Connection* m_con;
/*
=================================================================
    UDCF Data
=================================================================


    UDCF* 				m_udcfData;
    UDCFGroup*    m_udcfGroup;
    UDCFDive*     m_udcfDive;
*/
};
#endif
