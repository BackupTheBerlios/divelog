/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.7 2001/11/19 19:37:04 markus Exp $       *
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
static char *DivelogDAO_cvs_id="$Id: DivelogDAO.cpp,v 1.7 2001/11/19 19:37:04 markus Exp $";
#include "DivelogDAO.h"
#include "DivelogDAOException.h"
#include "DiveComputerNotFoundException.h"
//#include <iostream>   // first see, what we need...
//#include <iomanip>    // dito
#include <sqlplus.hh>   // the mysql++ classes
#include <custom.hh>    // needed for "sql_create_n"
#include <qglobal.h>
#include <UDCF.h>
#include <string.h>

DivelogDAO::DivelogDAO( char* db= MYSQL_DATABASE, char* host=MYSQL_HOST, char* user=MYSQL_USER, char* passwd=MYSQL_PASSWD )
{
    m_db=db;
    m_host=host;
    m_user=user;
    m_passwd=passwd;

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DivelogDAO_cvs_id+=0;
}

DivelogDAO::~DivelogDAO()
{
//    delete m_con;
}

void DivelogDAO::importUDCFFile( const char* filename ) throw ( DivelogDAOException )
{

    int s = strlen( filename );
    char* test= new char[s];
    strcpy( test, filename );


    qDebug( "test=%s", test );

    UDCF* udcfData=UDCFReadFile( test );
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

    try
    {
        Connection con( use_exceptions );
        con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD );
        // Here I broke making the connection into two calls.
        // The first one creates the Connection object with the 
        // use exceptions option turned on and the second one
        // makes the connection
        
        Query query = con.query();
        query << "select * from divecomputer where serial_number=\"" << udcfData->serialID <<"\"";
    
        Result db_diveComputers = query.store(); // Database result
    
        /*FIXME: That damn b...t doesn't work. Why ????
                 I.e. : dynamically creating the Connection object gives
                 strange errors...
        */
    
        Row row;

        if ( row )
        {
            Result::iterator i;
            for ( i=db_diveComputers.begin(); i!=db_diveComputers.end() ;i++ )
            {
                row=*i;                                          // better use index number
                qDebug( "mysql: divecomputer serial number =%s", row["serial_number"].c_str() );
//                qDebug( "mysql: divecomputer diver  number =%d", row["diver_number"] );
                qDebug( "mysql: divecomputer name          =%s", row["name"].c_str() );
            }
        }
        else
        {
            throw DiveComputerNotFoundException(  udcfData->serialID,
                                                  udcfData->model,
                                                  udcfData->personalInfo );
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
    catch (BadQuery &er)
    {
        cerr << "Error: " << er.error << endl;
    }
    catch (BadConversion &er)
    { // handle bad conversions
        cerr << "Error: Tried to convert \"" << er.data << "\" to a \""
             << er.type_name << "\"." << endl;
    }
}