/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.1 2001/10/16 07:19:58 markus Exp $                                                             *
* --------------------------------------------------------------------------- *
* Files subject    : Data Access Object (DAO) for the mysql-divelog database  *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List :                                                                *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char *DivelogDAO_cvs_id="$Id: DivelogDAO.cpp,v 1.1 2001/10/16 07:19:58 markus Exp $";

#include "divelogdao.h"
//#include <iostream>   // first see, what we need...
//#include <iomanip>    // dito
#include <sqlplus.hh>
#include <qglobal.h>
#include <UDCF.h>

DivelogDAO::DivelogDAO( char* db= MYSQL_DATABASE, char* host=MYSQL_HOST, char* user=MYSQL_USER, char* passwd=MYSQL_PASSWD )
{
    m_con = new Connection( db, host, user, passwd );
    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DivelogDAO_cvs_id+=0;
}

DivelogDAO::~DivelogDAO()
{
    delete m_con;
}

void DivelogDAO::importUDCFFile( char* filename )
{
        UDCF* udcfData=UDCFReadFile( filename );
        CHECK_PTR( udcfData );

        qDebug( "Version:\t%ld", udcfData->version );
        qDebug( "Vendor:\t%s", udcfData->vendor );
        qDebug( "Model:\t%s", udcfData->model );
        qDebug( "Driver Version:\t%ld", udcfData->driverVersion );
        qDebug( "Personal Info:\t%s", udcfData->personalInfo );
        qDebug( "Total Dives:\t%ld", udcfData->totalDives );
        qDebug( "Serial ID:\t%s", udcfData->serialID );
        qDebug( "Group Size:\t%ld", udcfData->groupSize );
        qDebug( "Group Index:\t%ld", udcfData->groupIndex );

        int count=0;

        for ( int group=0; group<=udcfData->groupIndex; group++)
        {
            for ( int dive=0; dive<=udcfData->groupList[group].diveIndex; dive++ )
            {

                qDebug( "#%04d Group[%d].diveList[%d] %02d.%02d.%04d %02d:%02d",
                        count, group, dive,
                        udcfData->groupList[group].diveList[dive].day,
                        udcfData->groupList[group].diveList[dive].month,
                        udcfData->groupList[group].diveList[dive].year,
                        udcfData->groupList[group].diveList[dive].hour,
                        udcfData->groupList[group].diveList[dive].minute );

                count++;

            }
        }
        UDCFFree( udcfData );
}