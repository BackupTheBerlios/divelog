/* Copyright 2002 Markus Grunwald */
/* All other Copyrights (especially Qt and mysql) belong to their owners */

/*************************************************************************
This file is part of divelog.

divelog is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

divelog is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with divelog; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**************************************************************************/

#ifndef DIVELOGDAO_H
#define DIVELOGDAO_H
/******************************************************************************
* Filename : divelogdao.h                                                     *
* CVS Id   : $Id: DivelogDAO.h,v 1.18 2002/05/15 17:04:11 grunwalm Exp $         *
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
//#define MYSQL_HOST   "zaphod"
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
