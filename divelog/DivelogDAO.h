#ifndef DIVELOGDAO_H
#define DIVELOGDAO_H
/******************************************************************************
* Filename : divelogdao.h                                                     *
* CVS Id   : $Id: DivelogDAO.h,v 1.16 2002/05/07 16:18:38 markus Exp $         *
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
//#define MYSQL_HOST   "localhost"
#define MYSQL_HOST   "zaphod"
#define MYSQL_USER   "markus"
#define MYSQL_PASSWD "ArPPCa"

#include <vector>
#include <string>


class DivelogDAOException;
class DiverVO;
class DiveVO;
class DiveListVO;
class FillingStationVO;
class DiveTypeVO;
class DiveComputerVO;
class DivelogDAO
{

public:
    DivelogDAO( char* db=MYSQL_DATABASE, char* host=MYSQL_HOST, char* user=MYSQL_USER, char* passwd=MYSQL_PASSWD );
    ~DivelogDAO();

    void importUDCFFile( const char* filename ) throw ( DivelogDAOException );
    void insertDiver( const DiverVO& diver ) throw ( DivelogDAOException );
    void insertFillingStation( const FillingStationVO& fs ) throw ( DivelogDAOException );
    void insertDiveType( const DiveTypeVO& diveType ) throw ( DivelogDAOException );
    void insertDiveComputer( const DiveComputerVO& diveComputer ) throw ( DivelogDAOException );

    vector<DiverVO> searchDiver( const DiverVO& d, const string& mask="0000000000" );
    vector<DiveVO>  searchDive ( const DiveVO&  d, const string& mask="00000000000000000000000" );

    vector<DiveListVO> diveList( const int& diver_number );


private:

    char* m_db;
    char* m_host;
    char* m_user;
    char* m_passwd;
};
#endif
