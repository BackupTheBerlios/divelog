/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.2 2001/11/09 14:13:26 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Data Access Object (DAO) for the mysql-divelog database  *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : throw exception on missing table entries. Then you can call    *
*              the corresponding dialog, insert the entry and retry...        *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char *DivelogDAO_cvs_id="$Id: DivelogDAO.cpp,v 1.2 2001/11/09 14:13:26 markus Exp $";

#include "divelogdao.h"
//#include <iostream>   // first see, what we need...
//#include <iomanip>    // dito
#include <vector>
#include <sqlplus.hh>   // the mysql++ classes
#include <custom.hh>    // needed for "sql_create_n"
#include <qglobal.h>
#include <UDCF.h>

sql_create_3 (diveComputer,    			// table name
              1, 3,             		// compare by field, nr of attributes
              string, serial_number,
              int, diver_number,
              string, name )



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

        /*
        || First look up if we know that dive-computer
        */

        Query query = m_con->query();
        query << "select * from divecomputer where serial_number=" << udcfData->serialID;

        vector < diveComputer > db_diveComputers; // Database result

        query.storein( db_diveComputers );

        vector < diveComputer >::iterator i;
        for ( i=db_diveComputers.begin(); i!=db_diveComputers.end() ;i++ )
        {
            qDebug( "mysql: divecomputer serial number =%s", i->serial_number.latin1() );
            qDebug( "mysql: divecomputer diver  number =%s", i->diver_number.latin1() );
            qDebug( "mysql: divecomputer name          =%s", i->name.latin1() );
        }

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