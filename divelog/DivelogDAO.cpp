/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.27 2002/05/07 16:18:38 markus Exp $      *
* --------------------------------------------------------------------------- *
* Files subject    : Data Access Object (DAO) for the mysql-divelog database  *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : throw exception on missing table entries. Then you can call    *
*               the corresponding dialog, insert the entry and retry...       *
*              libUDCF can't handle "Gruni's EON" due to the ' -> FIX it      *
* --------------------------------------------------------------------------- *
* Notes : I want to keep this free of any Qt classes since it simply hasn't   *
*         anything to do with it. ( This refers especially to QString which   *
*         would be far more powerfull then basic_string...)                   *
******************************************************************************/
static char *DivelogDAO_cvs_id="$Id: DivelogDAO.cpp,v 1.27 2002/05/07 16:18:38 markus Exp $";
#include "DivelogDAO.h"
#include "DiverVO.h"
#include "DiveVO.h"
#include "FillingStationVO.h"
#include "DiveTypeVO.h"
#include "DiveComputerVO.h"
#include "DivelogDAOException.h"
#include "DiveComputerNotFoundException.h"
#include "DiverNotFoundException.h"
#include "DiveNotFoundException.h"
#include "DiveProfileVO.h"
#include "DiveListVO.h"

#include <fstream.h> // DEBUG

//#include <iostream>   // first see, what we need...
//#include <iomanip>    // dito
#include <sqlplus.hh>   // the mysql++ classes
//#include <custom.hh>  // needed for "sql_create_n"
#include <qglobal.h>
#include <UDCF.h>
#include <string>
#include <iomanip>
#include <float.h>


double checkDoubleNull( ColData c )
{
    ( c.is_null() ? DBL_MAX : (double)c );
}

unsigned int checkUIntNull( ColData c )
{
    ( c.is_null() ? UINT_MAX : (unsigned int)c );
}

string checkStringNull( ColData c )
{
    ( c.is_null() ? "" : (string) c );
}



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
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            UDCFFree( udcfData );
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }

        Query query = con.query();
        Row row;
        query << "select * from divecomputer where serial_number=\"" << udcfData->serialID <<"\"";
    
        Result db_diveComputers = query.store(); // Database result
    
        /*FIXME: That damn b...t doesn't work. Why ????
                 I.e. : dynamically creating the Connection object gives
                 strange errors...
        */
    

        if ( db_diveComputers.empty() )
        {
            // DEBUG UDCFFree( udcfData );
            throw DiveComputerNotFoundException(  udcfData->serialID,
                                                  udcfData->model,
                                                  udcfData->personalInfo );
        }
        else
        {
            Result::iterator i;
            for ( i=db_diveComputers.begin(); i!=db_diveComputers.end() ;i++ )
            {                           // FIXME: What to do on multiple entries ?
                row=*i;                                          // better use index number
                qDebug( "mysql: divecomputer serial number =%s", row["serial_number"].c_str() );
                //qDebug( "mysql: divecomputer diver  number =%d", row["diver_number"] );
                qDebug( "mysql: divecomputer name          =%s", row["name"].c_str() );
            }
        }

        /*
        || Now we know the Divecomputer
        || so we iterate through all dives and insert them into the database
        */

        int count=0;

        for ( int group=0; group<=udcfData->groupIndex; group++)  // iterate through groups
        {
            for ( int dive=0; dive<=udcfData->groupList[group].diveIndex; dive++ )
            {                                                     // iterate through dives

                DiveProfileVO profile( udcfData->groupList[group].diveList[dive].sampleList,
                                       udcfData->groupList[group].diveList[dive].sampleIndex );

                // Calculate dive time
                int secs     = profile.samples() * profile.secsPerSample();
                int h,m,s;

                h=secs/3600;
                m=( secs%3600 )/60;
                s=secs-h*3600-m*60;

                query << "insert into dive ( date, sync, diver_number, surface_intervall, "
                    <<									    "altitude_mode, water_temperature, start_pressure, "
                    <<                      "end_pressure, max_depth, length, profile ) values ( "
                    // date
                    << "\""
                    << udcfData->groupList[group].diveList[dive].year  << "-"
                    << udcfData->groupList[group].diveList[dive].month << "-"
                    << udcfData->groupList[group].diveList[dive].day   << " "
                    << udcfData->groupList[group].diveList[dive].hour   << ":"
                    << udcfData->groupList[group].diveList[dive].minute  << ":00\", "
                    // sync = has this dive to be synchronised with manual added data ?
                    //        1 = synchron, no need to synchronize
                    //        0 = not synchron, need to synchronize
                    // FIXME: unhandled yet, so handle it !
                    << 1 << ", "
                    // diver_number
                    << row["diver_number"] << ", "    // FIXME: What to do on multple entries (s.o.) ?
                    // surface_intervall
                    << udcfData->groupList[group].diveList[dive].surfaceInterval << ", "
                    // altitude_mode
                    << udcfData->groupList[group].diveList[dive].altitude << ", "
                    // water_temperature
                    << udcfData->groupList[group].diveList[dive].temperature << ", "
                    // start_pressure
                    // FIXME: This is too simple and WILL cause errors, once multiple mixes
                    //        should be used...                          V
                    << udcfData->groupList[group].diveList[dive].mixList[0].pressureStart/10.0e4 << ", "
                    // end_pressure
                    // FIXME: This is too simple and WILL cause errors, once multiple mixes
                    //        should be used...                          V
                    << udcfData->groupList[group].diveList[dive].mixList[0].pressureEnd/10.0e4 << ", "
                    // max_depth
                    << profile.maxDepth() << ", "
                    // dive length
                    << "\"" << h << ":"
                    << setfill('0') << setw( 2 ) << m << ":"
                    << setfill('0') << setw( 2 ) << s << "\", "
                    // profile
                    << "\"" << profile << "\" )";

                try
                {
                    query.store();
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

                count++;
            }
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
    UDCFFree( udcfData );
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
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }
        
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
    if ( fillingStation.stationname() == "" )
    {
        throw DivelogDAOException( "FillingStationVO.stationname() must not be empty !" );
    }

    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }
        

        Query query = con.query();
        query << "insert into filling_station values( "
            << fillingStation.number() << ", "
            << "\"" << fillingStation.stationname() << "\", " ;
        ( fillingStation.first_name()=="" ? query << "NULL, " : query << "\"" << fillingStation.first_name() 	 << "\", " );
        ( fillingStation.last_name()=="" 	? query << "NULL, " : query << "\"" << fillingStation.last_name() 	 << "\" " );
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
// Use : Insert a new dive type into the database
// Parameters   : DiveTypeVO : a Value Object
//                containing the Dive Types's data.
// Outputs      : None
// Returns      : None
// Side-Effects : MySQL-Convention: When the number field
//                  is 0, the number will be auto-incremented
// Exceptions   : Throws DivelogDAOException on failure
// -------------------------------------------------
void DivelogDAO::insertDiveType( const DiveTypeVO& diveType ) throw ( DivelogDAOException )
{
    if ( diveType.description() == "" )
    {
        throw DivelogDAOException( "DiveTypeVO.description() must not be empty !" );
    }

    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }
        

        Query query = con.query();
        query << "insert into divetype values( "
            << diveType.number() << ", "
            << "\"" << diveType.description() << "\" )";

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
// Use : Insert a new divecomputer in the database
// Parameters   : DiveComputerVO : a Diver Value Object
//                containing the computers data.
// Outputs      : None
// Returns      : None
// Side-Effects : MySQL-Convention:
//                * When the number field is 0, the
//                  number will be auto-incremented
//                * The diver_number field has to point
//                  to a valid entry in the diver table
// Exceptions   : Throws DivelogDAOException on failure
// -------------------------------------------------
void DivelogDAO::insertDiveComputer( const DiveComputerVO& diveComputer ) throw ( DivelogDAOException )
{
    if ( diveComputer.serial_number() == "" )
    {
        throw DivelogDAOException( "DiveComputerVO.serial_number() must not be empty !" );
    }

    if ( diveComputer.diver_number() == 0 )
    {
        throw DivelogDAOException( "DiveComputerVO.diver_number() must not be 0 (zero) !" );
    }

    /*
    || See if the diver number is valid
    */
    vector< DiverVO > divers;
    DiverVO diverSearchPattern;

    diverSearchPattern.setNumber( diveComputer.diver_number() );
    divers=searchDiver( diverSearchPattern, "1000000000" );

    if ( divers.empty() )
    {
        throw DiverNotFoundException( diverSearchPattern );
    }

    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }
        
        Query query = con.query();
        query << "insert into divecomputer values( "
              << "\"" << diveComputer.serial_number() << "\", "
              << diveComputer.diver_number() << ", " ;

        ( diveComputer.name()=="" 	  ? query << "NULL, " : query << "\"" << diveComputer.name() 	 << "\" " );
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
    catch( ... )
    {
        cerr << " DivelogDAO: unknown exception. ";
    }

}

vector<DiverVO> DivelogDAO::searchDiver( const DiverVO& d, const string& mask="0000000000" )
// BIG FIXME: mask handling is ugly and wrong. Make it better and document it !
// mask==1 -> use this field
// idea: mask==o -> or expression
//             a -> and expression ???
// better: >, <, =, contains...
{
    ASSERT( mask.size()==10 );
    vector<DiverVO> t;
    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }

        Query query = con.query();
        query << "select * from diver";



        if( mask!="0000000000" )
        {
            query<< " where ";

            if (mask[ 0 ] == '1' )
            {
                query << "number=" << d.number();  // FIXME: need posibility to search or "*"
                if ( mask[ 1 ]=='1' )
                {
                    query << " and "; // FIXME: wrong. What it mask[1]==0, but mask[2]==1 !
                }
            }

            if (mask[ 1 ] == '1' )
            {
                query << "first_name=" << d.first_name();
                if ( mask[ 2 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 2 ] == '1' )
            {
                query << "last_name=" << d.last_name();
                if ( mask[ 3 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 3 ] == '1' )
            {
                query << "brevet=" << d.brevet();
                if ( mask[ 4 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 4 ] == '1' )
            {
                query << "street=" << d.street();
                if ( mask[ 2 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 5 ] == '1' )
            {
                query << "house_number=" << d.house_number();
                if ( mask[ 6 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 6 ] == '1' )
            {
                query << "zip=" << d.zip();
                if ( mask[ 7 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 7 ] == '1' )
            {
                query << "place=" << d.place();
                if ( mask[ 8 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 8 ] == '1' )
            {
                query << "phone=" << d.phone();
                if ( mask[ 9 ]=='1' )
                {
                    query << " and ";
                }
            }

            if (mask[ 9 ] == '1' )
            {
                query << "email=" << d.email();
            }
        }

        query << " order by last_name";
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
}                                                                         //         1         2
                                                                          //12345678901234567890123
vector<DiveVO> DivelogDAO::searchDive( const DiveVO& d, const string& mask="00000000000000000000000" )
// mask==1 -> use this field
// idea: use mask with  >, <, =, contains...
{
    ASSERT( mask.size()==23 );
    vector<DiveVO> t;
    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }

        Query query = con.query();
        query << "select * from dive";

        bool pred=false; // Predecessor. True, if there have been selections
                         // before. Used for "and" concatenations

        if( mask!="00000000000000000000000" )
        {
            query<< " where ";

            if (mask[ 0 ] == '1' )
            {
                query << "number=" << d.number();  // FIXME: need posibility to search for "*"
                pred=true;
            }

            if ( (mask[ 1 ] == '1' ) || ( mask[ 2 ] == '1' ) )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "date=" << d.date() << " " << d.time() ;
                pred=true;
            }

            if (mask[ 3 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "sync=" << d.sync();
                pred=true;
            }

            if (mask[ 4 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "diver_number=" << d.diver_number();
                pred=true;
            }

            if (mask[ 5 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "place=" << d.place();
                pred=true;
            }

            if (mask[ 6 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "location=" << d.location();
                pred=true;
            }

            if (mask[ 7 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "altitude_mode=" << d.altitude_mode();
                pred=true;
            }

            if (mask[ 8 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "water_temperature=" << d.water_temperature();
                pred=true;
            }

            if (mask[ 9 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "start_pressure=" << d.start_pressure();
                pred=true;
            }

            if (mask[ 10 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "end_pressure=" << d.end_pressure();
                pred=true;
            }

            if (mask[ 11 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "surface_intervall=" << d.surface_intervall();
                pred=true;
            }

            if (mask[ 12 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "max_depth=" << d.max_depth();
                pred=true;
            }

            if (mask[ 13 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "length=" << d.length();
                pred=true;
            }

            if (mask[ 14 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "profile=" << d.profile();
                                           
                pred=true;
            }

            if (mask[ 15 ] == '1' )          // FIXME: mostly useless this way.
            {                                // FIXME: better do a "contains" search
                if ( pred )
                {
                    query << " and ";
                }

                query << "log=" << d.log();
                pred=true;
            }

            if (mask[ 16 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "partner_diver_number=" << d.partner_diver_number();
                pred=true;
            }

            if (mask[ 17 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "weather=" << d.weather();
                pred=true;
            }

            if (mask[ 18 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "sight=" << d.sight();
                pred=true;
            }

            if (mask[ 18 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "lead=" << d.lead();
                pred=true;
            }

            if (mask[ 19 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "air_temperature=" << d.air_temperature();
                pred=true;
            }

            if (mask[ 20 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "dive_type=" << d.dive_type();
                pred=true;
            }

            if (mask[ 21 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "filling_station_number=" << d.filling_station_number();
                pred=true;
            }

            if (mask[ 22 ] == '1' )
            {
                if ( pred )
                {
                    query << " and ";
                }

                query << "bottle_number=" << d.bottle_number();
            }
        }

        Result db_dives = query.store(); // Database result
    
        Row row;

        if ( !db_dives.empty() )
        {
            Result::iterator i;
            for ( i=db_dives.begin(); i!=db_dives.end() ;i++ )
            {
                row=*i;

                /*
                || MySQL++ may deliver null-values which give a BadConversion error
                || -> check for null-values
                || access via index-number is faster then via string
                */

                string datetime( (string) row[1] );   // split up date and time
                int sep_pos = datetime.find( ' ' );

                string date( datetime, 0, sep_pos );
                string time( datetime, sep_pos+1  );

                DiveProfileVO profile;

                if ( ! row[13].is_null() )
                {
                    //profile << (string) row[13];
                    string tmp = (string) row[13];
                    tmp >> profile ;
                }

                DiveVO dive( ( row[ 0].is_null() ? 0  : (int)   row[ 0] ),  // number
                             date, 																	    		 // date
                             time,                                          // time
                             ( row[ 2].is_null() ? 0  : (int)   row[ 2] ),  // sync
                             ( row[ 3].is_null() ? 0  : (int)   row[ 3] ),  // diver_number
                             ( row[ 4].is_null() ? "" : (string)row[ 4] ),  // place
                             ( row[ 5].is_null() ? "" : (string)row[ 5] ),  // location
                             //( row[ 6].is_null() ? DBL_MAX : (double)row[ 6] ),  // altitude_mode
                             checkDoubleNull( row[6] ),
                             ( row[ 7].is_null() ? DBL_MAX : (double)row[ 7] ),  // water_temperature
                             ( row[ 8].is_null() ? DBL_MAX : (double)row[ 8] ),  // start_pressure
                             ( row[ 9].is_null() ? DBL_MAX : (double)row[ 9] ), // end_pressure
                             ( row[10].is_null() ? DBL_MAX : (double)row[10] ),  // surface_intervall
                             ( row[11].is_null() ? DBL_MAX : (double)row[11] ),  // max_depth
                             ( row[12].is_null() ? "" : (string)row[12] ),  // length
                             profile,  // profile
                             ( row[14].is_null() ? "" : (string)row[14] ),  // log
                             ( row[15].is_null() ? 0  : (int)   row[15] ),  // partner_diver_number
                             ( row[16].is_null() ? "" : (string)row[16] ),  // weather
                             ( row[17].is_null() ? "" : (string)row[17] ),  // sight
                             ( row[18].is_null() ? DBL_MAX : (double)row[18] ),  // lead
                             ( row[19].is_null() ? DBL_MAX : (double)row[19] ),   // air_temperature
                             ( row[20].is_null() ? 0  : (int)   row[20] ),  // dive_type
                             ( row[21].is_null() ? 0  : (int)   row[21] ),  // filling_station_number
                             ( row[22].is_null() ? 0  : (int)   row[22] ));  // bottle_number

                t.push_back( dive );
            }
        }
        else
        {
            throw DiveNotFoundException();
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
vector<DiveListVO> DivelogDAO::diveList( const int& diver_number )
{
    vector<DiveListVO> diveList;
    try
    {
        Connection con( use_exceptions );
        if ( ! con.connect( MYSQL_DATABASE, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWD ) )
        {
            // FIXME: Better errormessage
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }

        Query query = con.query();
        query << "select number, date, diver_number, place, location from dive where diver_number="
              << diver_number
              << endl;
                                 
        Result db_dives = query.store(); // Database result
    
        Row row;

        if ( !db_dives.empty() )
        {
            Result::iterator i;
            for ( i=db_dives.begin(); i!=db_dives.end() ;i++ )
            {
                row=*i;

                /*
                || MySQL++ may deliver null-values which give a BadConversion error
                || -> check for null-values
                || access via index-number is faster then via string
                */

                string datetime( (string) row[1] );   // split up date and time
                int sep_pos = datetime.find( ' ' );

                string date( datetime, 0, sep_pos );
                string time( datetime, sep_pos+1  );

                DiveListVO dl(  ( int )    row[0] ,  // number
                                date,
                                time,
                                ( int )    row[2] ,  // diver_number
                                ( string ) row[3],   // place
                                ( row[4].is_null() ? "" : (string)row[4] )  // location
                             );

                diveList.push_back( dl );
            }
        }
        else
        {
            throw DiveNotFoundException();
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
    return diveList;
}
