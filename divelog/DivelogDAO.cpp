/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.12 2001/12/06 08:10:10 markus Exp $       *
* --------------------------------------------------------------------------- *
* Files subject    : Data Access Object (DAO) for the mysql-divelog database  *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : throw exception on missing table entries. Then you can call    *
*               the corresponding dialog, insert the entry and retry...       *
*              libUDCF can't handle "Gruni's EON" due to the ' -> FIX it      *
* --------------------------------------------------------------------------- *
* Notes :                                                                     *
******************************************************************************/
static char *DivelogDAO_cvs_id="$Id: DivelogDAO.cpp,v 1.12 2001/12/06 08:10:10 markus Exp $";
#include "DivelogDAO.h"
#include "DiverVO.h"
#include "DivelogDAOException.h"
#include "DiveComputerNotFoundException.h"
#include "DiverNotFoundException.h"

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

        if ( !db_diveComputers.empty() )
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

vector<DiverVO> DivelogDAO::diverList()
{
    vector<DiverVO> t;
    try
    {
        Connection con( use_exceptions );
        con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD );
        
        Query query = con.query();
        query << "select * from diver order by last_name";
    
        Result db_divers = query.store(); // Database result
    
        Row row;

        if ( !db_divers.empty() )
        {
            Result::iterator i;
            for ( i=db_divers.begin(); i!=db_divers.end() ;i++ )
            {
                row=*i;

                /*
                || MySQL++ may deliver null-values which give a BadConversion error
                || -> check for null-values
                || access via index-number is faster then via string
                */
                DiverVO diver( ( row[0].is_null() ? 0  : (int)   row[0] ),  // number
                               ( row[1].is_null() ? "" : (string)row[1] ),  // first_name
                               ( row[2].is_null() ? "" : (string)row[2] ),  // last_name
                               ( row[3].is_null() ? "" : (string)row[3] ),  // brevet
                               ( row[4].is_null() ? "" : (string)row[4] ),  // street
                               ( row[5].is_null() ? "" : (string)row[5] ),  // house_number
                               ( row[6].is_null() ? 0  : (int)   row[6] ),  // zip
                               ( row[7].is_null() ? "" : (string)row[7] ),  // place
                               ( row[8].is_null() ? "" : (string)row[8] ),  // phone
                               ( row[9].is_null() ? "" : (string)row[9] ) );// email

                t.push_back( diver );
            }
        }
        else
        {
            //qDebug("getDivers: no divers found!");
            throw DiverNotFoundException();
        }

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
    return t;
}

// -------------------------------------------------
// Use : Insert a new Diver in the database
// Parameters   : DiverVO : a Diver Value Object
//                containing the divers data.
// Outputs      : None
// Returns      : None
// Side-Effects : MySQL-Convention: When the number field
//                  is 0, the number will be auto-incremented
// Exceptions   : Throws DivelogDAOException on failure
//                // FIXME: Does it ? -^-
// -------------------------------------------------
void DivelogDAO::insertDiver( const DiverVO& diver ) throw ( DivelogDAOException )
{
    if ( diver.first_name() == "" )
    {
        throw DivelogDAOException( "DiverVO.first_name() must not be empty !" );
    }

    try
    {
        Connection con( use_exceptions );
        con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD );

        Query query = con.query();
        query << "insert into diver values( "
            << diver.number() << ", "
            << "\"" << diver.first_name() << "\", " ;
        ( diver.last_name()=="" 	 ? query << "NULL, " : query << "\"" << diver.last_name() 	 << "\", " );
        ( diver.brevet()=="" 			 ? query << "NULL, " : query << "\"" << diver.brevet() 		   << "\", " );
        ( diver.street()=="" 			 ? query << "NULL, " : query << "\"" << diver.street() 		   << "\", " );
        ( diver.house_number()=="" ? query << "NULL, " : query << "\"" << diver.house_number() << "\", " );
        ( diver.zip()==0  				 ? query << "NULL, " : query << "\"" << diver.zip()          << "\", " );
        ( diver.place()=="" 			 ? query << "NULL, " : query << "\"" << diver.place() 		   << "\", " );
        ( diver.phone()=="" 			 ? query << "NULL, " : query << "\"" << diver.phone()        << "\", " );
        ( diver.email()=="" 			 ? query << "NULL  " : query << "\"" << diver.email()        << "\" " );
        query << " )";

        query.execute();
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

// -------------------------------------------------
// Use : Insert a new fillingstation into the database
// Parameters   : FillingStationVO : a Value Object
//                containing the FS's data.
// Outputs      : None
// Returns      : None
// Side-Effects : MySQL-Convention: When the number field
//                  is 0, the number will be auto-incremented
// Exceptions   : Throws DivelogDAOException on failure
//                // FIXME: Does it ? -^-
// -------------------------------------------------
void DivelogDAO::insertFillingStation( const FillingStationVO& fillingStation ) throw ( DivelogDAOException )
{
    cerr << "Not implemented" << endl;
    /*
    if ( fillingStation.first_name() == "" )
    {
        throw DivelogDAOException( "FillingStationVO.first_name() must not be empty !" );
    }

    try
    {
        Connection con( use_exceptions );
        con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD );

        Query query = con.query();
        query << "insert into fillingStation values( "
            << fillingStation.number() << ", "
            << "\"" << fillingStation.first_name() << "\", " ;
        ( fillingStation.last_name()=="" 	 ? query << "NULL, " : query << "\"" << fillingStation.last_name() 	 << "\", " );
        ( fillingStation.brevet()=="" 			 ? query << "NULL, " : query << "\"" << fillingStation.brevet() 		   << "\", " );
        ( fillingStation.street()=="" 			 ? query << "NULL, " : query << "\"" << fillingStation.street() 		   << "\", " );
        ( fillingStation.house_number()=="" ? query << "NULL, " : query << "\"" << fillingStation.house_number() << "\", " );
        ( fillingStation.zip()==0  				 ? query << "NULL, " : query << "\"" << fillingStation.zip()          << "\", " );
        ( fillingStation.place()=="" 			 ? query << "NULL, " : query << "\"" << fillingStation.place() 		   << "\", " );
        ( fillingStation.phone()=="" 			 ? query << "NULL, " : query << "\"" << fillingStation.phone()        << "\", " );
        ( fillingStation.email()=="" 			 ? query << "NULL  " : query << "\"" << fillingStation.email()        << "\" " );
        query << " )";

        query.execute();
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
   */
}

