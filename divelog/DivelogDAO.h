#ifndef DIVELOGDAO_H
#define DIVELOGDAO_H
/******************************************************************************
* Filename : divelogdao.h                                                     *
* CVS Id   : $Id: DivelogDAO.h,v 1.6 2001/11/23 14:36:52 markus Exp $         *
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

#include <vector>
#include <string>


class DivelogDAOException;
class DiverVO;

class DivelogDAO
{

public:
    DivelogDAO( char* db=MYSQL_DATABASE, char* host=MYSQL_HOST, char* user=MYSQL_USER, char* passwd=MYSQL_PASSWD );
    ~DivelogDAO();

    void importUDCFFile( const char* filename ) throw ( DivelogDAOException );
    vector<DiverVO> diverList();

private:

    char* m_db;
    char* m_host;
    char* m_user;
    char* m_passwd;
};
#endif
