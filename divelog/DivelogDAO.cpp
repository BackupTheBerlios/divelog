/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */
/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB */

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

/******************************************************************************
* Filename : DivelogDAO.cpp                                                   *
* CVS Id   : $Id: DivelogDAO.cpp,v 1.31 2002/09/16 17:08:11 grunwalm Exp $    *
* --------------------------------------------------------------------------- *
* Files subject    : Data Access Object (DAO) for the mysql-divelog database  *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Fri Oct 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : throw exception on missing table entries. Then you can call    *
*               the corresponding dialog, insert the entry and retry...       *
*              libUDCF can't handle "Gruni's EON" due to the ' -> FIX it      *
*               (new libUDCF should be ready by now)                          *
*              migrate from MySQL++ to QT3 Sql                                *
*              perhaps migrate fomr STL "string" to QString...                *
* --------------------------------------------------------------------------- *
* Notes : I want to keep this free of any Qt classes since it simply hasn't   *
*         anything to do with it. ( This refers especially to QString which   *
*         would be far more powerfull then basic_string...)                   *
*                                                                             *
*         As you see, i didn't manage to, because MySQL++ is unusable,at least*
*         with g++ 3.x. With 2.95, there were lots of warnings, too.          *
*                                                                             *
*         Perhaps, one day I will use plain mysql libs...                     *
******************************************************************************/
static const char DivelogDAO_cvs_id[]="$Id: DivelogDAO.cpp,v 1.31 2002/09/16 17:08:11 grunwalm Exp $";
#include "DivelogDAO.h"
#include "DiverVO.h"
#include "DiverSO.h"
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

#include <qglobal.h>
#include <UDCF.h>
#include <string>
#include <iomanip>
#include <float.h>
#include <qtextstream.h>

#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qstring.h>

DivelogDAO::DivelogDAO( const char db[]= MYSQL_DATABASE,
                        const char host[]=MYSQL_HOST,
                        const char user[]=MYSQL_USER,
                        const char passwd[]=MYSQL_PASSWD ) throw ( DivelogDAOException )
{
    QSqlDatabase *m_db = QSqlDatabase::addDatabase( "QMYSQL3" );
    if ( m_db )
    {
        m_db->setDatabaseName( db );
        m_db->setUserName( user );
        m_db->setPassword( passwd );
        m_db->setHostName( host );

        if ( ! m_db->open() )
        {
            qWarning( "Failed to open database: " +
                      m_db->lastError().driverText() );
            qWarning( m_db->lastError().databaseText() );
            throw DivelogDAOException( "Could not connect to MySQL Server." );
        }
    }
    else
    {
        qWarning( "Failed to connect to driver" );
    }

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    DivelogDAO_cvs_id;
}

DivelogDAO::~DivelogDAO()
{
}

void DivelogDAO::importUDCFFile( const char* filename ) throw ( DivelogDAOException )
{

    int s = strlen( filename );
    char* test= new char[s];
    strcpy( test, filename );

    UDCF* udcfData=UDCFReadFile( test );
    CHECK_PTR( udcfData );
/*
    qDebug( "Version:\t%ld", udcfData->version );
    qDebug( "Vendor:\t%s", udcfData->vendor );
    qDebug( "Model:\t%s", udcfData->model );
    qDebug( "Driver Version:\t%ld", udcfData->driverVersion );
    qDebug( "Personal Info:\t%s", udcfData->personalInfo );
    qDebug( "Total Dives:\t%ld", udcfData->totalDives );
    qDebug( "Serial ID:\t%s", udcfData->serialID );
    qDebug( "Group Size:\t%ld", udcfData->groupSize );
    qDebug( "Group Index:\t%ld", udcfData->groupIndex );
*/
    /*
    || First look up if we know that dive-computer
    */

    QSqlQuery query( QString("select diver_number from divecomputer where serial_number=\"")+
                     QString(udcfData->serialID) + QString("\"") );

    if ( !query.isActive() )
    {
        throw DivelogDAOException( "Query not active !" );
    }
    if ( query.size()>1 )
    {
        throw DivelogDAOException( "More then one result for primary key!" );
    }
    if ( query.size()==0 )
    {
        throw DiveComputerNotFoundException(  udcfData->serialID,
                                              udcfData->model,
                                              udcfData->personalInfo );
    }

    if ( !query.first() )
    {
        throw DivelogDAOException( "Could not select first entry!" );
    }
    int diver_number=query.value(0).toInt();


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

            QString profileString = profile.toQString();
//            QTextStream profileStream( profileString, IO_ReadWrite );
//            profileStream << profile ;

            qDebug( "profileString=%s", profileString.latin1() );
            // Calculate dive time
            int secs     = profile.samples() * profile.secsPerSample();
            int h,m,s;

            h=secs/3600;
            m=( secs%3600 )/60;
            s=secs-h*3600-m*60;

            QString diveDuration;
            diveDuration.sprintf( "%i:%02i:%02i", h, m, s );

            QString
                queryString ="insert into dive ( date_time, sync, diver_number, surface_intervall, ";
            queryString+="altitude_mode, water_temperature, start_pressure, ";
            queryString+="end_pressure, max_depth, duration, profile ) values ( ";
            // date
            queryString+="\"";
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].year )   + "-";
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].month )  + "-";
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].day )    + " ";
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].hour )   + ":";
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].minute ) + ":00\", ";
            // sync = has this dive to be synchronised with manual added data ?
            //        1 = synchron, no need to synchronize
            //        0 = not synchron, need to synchronize
            // FIXME: unhandled yet, so handle it !
            queryString+= "1, ";
            // diver_number
            queryString+= QString::number( diver_number ) + ", ";
            // surface_intervall
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].surfaceInterval, 'f',2 ) + ", ";
            // altitude_mode
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].altitude, 'f', 2 ) + ", ";
            // water_temperature
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].temperature, 'f', 2 ) + ", ";
            // start_pressure
            // FIXME: This is too simple and WILL cause errors, once multiple mixes
            //        should be used...                         V
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].mixList[0].pressureStart/10.0e4, 'f', 2 ) + ", ";
            // end_pressure
            // FIXME: This is too simple and WILL cause errors, once multiple mixes
            //        should be used...                         V
            queryString+= QString::number( udcfData->groupList[group].diveList[dive].mixList[0].pressureEnd/10.0e4, 'f', 2 ) + ", ";
            // max_depth
            queryString+= QString::number( profile.maxDepth(), 'f', 2 ) + ", ";
            // dive duration
            queryString+= "\"" + diveDuration + "\",";
            // profile
            queryString+= "\"" ;
            queryString+= profileString ;
            queryString+= "\" )";;

            if ( ! query.exec( queryString ) )
            {
                throw DivelogDAOException( "Query failed: "+queryString) ;
            }

            count++;
        }
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

    QSqlQuery query;
    QString queryString;


    queryString += "insert into diver values( ";
    queryString += QString::number( diver.number() ) + ", ";
    queryString += "\"" + diver.first_name() + "\", " ;
    ( diver.last_name()=="" 	 ? queryString += "NULL, " : queryString += "\"" + diver.last_name()  + "\", " );
    ( diver.brevet()=="" 			 ? queryString += "NULL, " : queryString += "\"" + diver.brevet()		  + "\", " );
    ( diver.street()=="" 			 ? queryString += "NULL, " : queryString += "\"" + diver.street()		  + "\", " );
    ( diver.house_number()=="" ? queryString += "NULL, " : queryString += "\"" + diver.house_number() + "\", ") ;
    ( diver.zip()==0  				 ? queryString += "NULL, " : queryString += "\"" + QString::number(diver.zip())          + "\", " );
    ( diver.place()=="" 			 ? queryString += "NULL, " : queryString += "\"" + diver.place() 		    + "\", " );
    ( diver.phone()=="" 			 ? queryString += "NULL, " : queryString += "\"" + diver.phone()        + "\", " );
    ( diver.email()=="" 			 ? queryString += "NULL  " : queryString += "\"" + diver.email()        + "\" "  );
    queryString += " )";

    if ( ! query.exec( queryString ) )
    {
        throw DivelogDAOException( "Query failed: "+queryString) ;
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

    QSqlQuery query;
    QString queryString;
    queryString = "insert into filling_station values( ";
    queryString += QString::number( fillingStation.number() ) + ", ";
    queryString += "\"" +  fillingStation.stationname()  + "\", " ;
    ( fillingStation.first_name()=="" ? queryString += "NULL, " : queryString += "\"" +  fillingStation.first_name()  + "\", " );
    ( fillingStation.last_name()=="" 	? queryString += "NULL, " : queryString += "\"" +  fillingStation.last_name()   + "\" " );
    queryString += " )";

    if ( ! query.exec( queryString ) )
    {
        throw DivelogDAOException( "Query failed: "+queryString) ;
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

    QSqlQuery query;
    QString queryString;
    queryString = "insert into divetype values( ";
    queryString += QString::number( diveType.number() ) + ", ";
    queryString += "\"" +  diveType.description() + "\" ";

    if ( ! query.exec( queryString ) )
    {
        throw DivelogDAOException( "Query failed: "+ queryString ) ;
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
    DiverSO diverSearchPattern;

    diverSearchPattern.number( diveComputer.diver_number() );
    divers=searchDiver( diverSearchPattern );

    if ( divers.empty() )
    {
        throw DiverNotFoundException( diverSearchPattern );
    }

    QSqlQuery query;
    QString queryString;
    queryString  = "insert into divecomputer values( ";
    queryString += "\"" +  diveComputer.serial_number()  + "\", ";
    queryString += QString::number( diveComputer.diver_number() ) + ", " ;

    ( diveComputer.name()=="" ? queryString += "NULL, " : queryString += "\"" +  diveComputer.name()  + "\" " );
    queryString += " )";

    if ( ! query.exec( queryString ) )
    {
        qDebug( "queryString=%s", queryString.latin1() );
    }
}

vector<DiverVO> DivelogDAO::searchDiver( const DiverSO& d )
// FIXME: Document search scheme
// FIXME: add search type  >, <, =, contains...
{
    vector<DiverVO> t;

    QSqlQuery query;
    QString queryString;

    queryString = QString( "select number, first_name, last_name, brevet, street, house_number, zip, "
                           "place, phone, email from diver " );

    queryString += ( d.checkSearchField( DiverSO::SF_number ) && d.number()==0 ? "" : " where " );

    if ( d.checkSearchField( DiverSO::SF_number ) && d.number()!=0 )
    {

        queryString += " number=" + QString::number( d.number() );
        if ( d.checkMoreFields(DiverSO::SF_number) )
        {
            queryString += " and ";
        }

    }

    if ( ( ! d.checkSearchField( DiverSO::SF_number ) ) ||  d.number()!=0 )
    {
        if ( d.checkSearchField( DiverSO::SF_first_name ) )
        {
            queryString += "first_name=" +  d.first_name() ;
            if ( d.checkMoreFields(DiverSO::SF_first_name) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_last_name ) )
        {
            queryString += "last_name=" +  d.last_name() ;
            if ( d.checkMoreFields(DiverSO::SF_last_name) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_brevet ) )
        {
            queryString += "brevet=" +   d.brevet() ;
            if ( d.checkMoreFields(DiverSO::SF_brevet) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_street ) )
        {
            queryString += "street=" +  d.street() ;
            if ( d.checkMoreFields(DiverSO::SF_street) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_house_number ) )
        {
            queryString += "house_number=" +  d.house_number() ;
            if ( d.checkMoreFields(DiverSO::SF_house_number) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_zip ) )
        {
            queryString += "zip=" + QString::number( d.zip() );
            if ( d.checkMoreFields(DiverSO::SF_zip) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_place ) )
        {
            queryString += "place=" +  d.place() ;
            if ( d.checkMoreFields(DiverSO::SF_place) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_phone ) )
        {
            queryString += "phone=" +  d.phone() ;
            if ( d.checkMoreFields(DiverSO::SF_phone) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiverSO::SF_email ) )
        {
            queryString += "email=" +  d.email() ;
        }
    }
    queryString += " order by last_name";
    query.exec( queryString );

    if ( query.isActive() )
    {
        if ( query.numRowsAffected()<=0 )
        {
            qDebug( "Query String: %s", queryString.latin1() );
            throw DiverNotFoundException();
        }

        while( query.next() )
        {
            /*
            || MySQL++ may deliver null-values which give a BadConversion error
            || -> check for null-values
            || access via index-number is faster then via string
            */
            const QString emptyStr("");
            DiverVO diver( ( query.isNull(0) ? 0  : query.value(0).toInt() ),               // number
                           ( query.isNull(1) ? emptyStr : query.value(1).toString() ) ,  // first_name
                           ( query.isNull(2) ? emptyStr : query.value(2).toString() ) ,  // last_name
                           ( query.isNull(3) ? emptyStr : query.value(3).toString() ) ,  // brevet
                           ( query.isNull(4) ? emptyStr : query.value(4).toString() ) ,  // street
                           ( query.isNull(5) ? emptyStr : query.value(5).toString() ) ,  // house_number
                           ( query.isNull(6) ? 0  : query.value(6).toInt() ),               // zip
                           ( query.isNull(7) ? emptyStr : query.value(7).toString() ) ,  // place
                           ( query.isNull(8) ? emptyStr : query.value(8).toString() ) ,  // phone
                           ( query.isNull(9) ? emptyStr : query.value(9).toString() ) ) ;// email

            t.push_back( diver );
        }
    }
    else
    {
        //qDebug("getDivers: no divers found!");
        qDebug( "Query String: %s", queryString.latin1() );
        throw DiverNotFoundException();
    }
    return t;
}

vector<DiveVO> DivelogDAO::searchDive( const DiveSO& d )
// idea: use >, <, =, contains...
{
    vector<DiveVO> t;

    QSqlQuery query;
    QString queryString;
    queryString += "select number, date_time, sync, diver_number, place, location, altitude_mode, ";
    queryString += "water_temperature, start_pressure, end_pressure, surface_intervall, max_depth, ";
    queryString += "duration, profile, log, partner_diver_number, weather, sight, lead, air_temperature, ";
    queryString += "dive_type, filling_station_number, bottle_number from dive  ";

    queryString += ( d.checkSearchField( DiveSO::SF_number ) && d.number()==0 ? "" : " where " );

    if ( d.checkSearchField( DiveSO::SF_number ) && d.number()!=0 )
    {

        queryString += " number=" + QString::number( d.number() );
        if ( d.checkMoreFields(DiveSO::SF_number) )
        {
            queryString += " and ";
        }

    }

    if ( ( ! d.checkSearchField( DiveSO::SF_number ) ) ||  d.number()!=0 )
    {

        if ( d.checkSearchField( DiveSO::SF_date_time ) )
        {
            queryString += "date_time=" +  d.date_time().toString("\"yyyy-MM-dd hh:mm:ss\"")  ;
            if ( d.checkMoreFields( DiveSO::SF_date_time ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_sync ) )
        {
            queryString += "sync=" + QString::number( d.sync() );
            if ( d.checkMoreFields( DiveSO::SF_sync ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_diver_number ) )
        {
            queryString += "diver_number=" + QString::number( d.diver_number() );
            if ( d.checkMoreFields( DiveSO::SF_diver_number ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_place ) )
        {
            queryString += "place=" +  d.place() ;
            if ( d.checkMoreFields( DiveSO::SF_place ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_location ) )
        {
            queryString += "location=" +  d.location() ;
            if ( d.checkMoreFields( DiveSO::SF_location ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_altitude_mode ) )
        {
            queryString += "altitude_mode=" + QString::number( d.altitude_mode() );
            if ( d.checkMoreFields( DiveSO::SF_altitude_mode ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_water_temperature ) )
        {
            queryString += "water_temperature=" + QString::number( d.water_temperature() );
            if ( d.checkMoreFields( DiveSO::SF_water_temperature ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_start_pressure ) )
        {
            queryString += "start_pressure=" + QString::number( d.start_pressure() );
            if ( d.checkMoreFields( DiveSO::SF_start_pressure ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_end_pressure ) )
        {
            queryString += "end_pressure=" + QString::number( d.end_pressure() );
            if ( d.checkMoreFields( DiveSO::SF_end_pressure ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_surface_intervall ) )
        {
            queryString += "surface_intervall=" + QString::number( d.surface_intervall() );
            if ( d.checkMoreFields( DiveSO::SF_surface_intervall ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_max_depth ) )
        {
            queryString += "max_depth=" + QString::number( d.max_depth() );
            if ( d.checkMoreFields( DiveSO::SF_max_depth ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_duration ) )
        {
            queryString += "duration=" +  d.duration() ;
            if ( d.checkMoreFields( DiveSO::SF_duration ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_profile ) )
        {
            queryString += "profile=" + d.profile().toQString() ;
            if ( d.checkMoreFields( DiveSO::SF_profile ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_log ) )
        {                                // FIXME: better do a "contains" search
            queryString += "log=" +  d.log() ;
            if ( d.checkMoreFields( DiveSO::SF_log ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_partner_diver_number ) )
        {
            queryString += "partner_diver_number=" + QString::number( d.partner_diver_number() );
            if ( d.checkMoreFields( DiveSO::SF_partner_diver_number ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_weather ) )
        {
            queryString += "weather=" +  d.weather() ;
            if ( d.checkMoreFields( DiveSO::SF_weather ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_sight ) )
        {
            queryString += "sight=" +  d.sight() ;
            if ( d.checkMoreFields( DiveSO::SF_sight ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_lead ) )
        {
            queryString += "lead=" + QString::number( d.lead() );
            if ( d.checkMoreFields( DiveSO::SF_lead ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_air_temperature ) )
        {
            queryString += "air_temperature=" + QString::number( d.air_temperature() );
            if ( d.checkMoreFields( DiveSO::SF_air_temperature ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_dive_type ) )
        {
            queryString += "dive_type=" + QString::number( d.dive_type() );
            if ( d.checkMoreFields( DiveSO::SF_dive_type ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_filling_station_number ) )
        {
            queryString += "filling_station_number=" + QString::number( d.filling_station_number() );
            if ( d.checkMoreFields( DiveSO::SF_filling_station_number ) )
            {
                queryString += " and ";
            }
        }

        if ( d.checkSearchField( DiveSO::SF_bottle_number ) )
        {
            queryString += "bottle_number=" + QString::number( d.bottle_number() );
        }
    }
    qDebug( "Query String: %s", queryString.latin1() );
    query.exec( queryString ); // Database result

    if ( query.isActive() )
    {
        if ( query.numRowsAffected()<=0 )
        {
            qDebug( "Query String: %s", queryString.latin1() );
            throw DiverNotFoundException();
        }

        while( query.next() )
        {
            /*
            || MySQL++ may deliver null-values which give a BadConversion error
            || -> check for null-values
            || access via index-number is faster then via string
            */

//            QString datetime( query.value(1).toString() );   // split up date and time
//            QString date=datetime.section('T', 0, 0 );
//            QString time=datetime.section('T', 1, 1 );

            QDateTime date_time( QDateTime::fromString( query.value(1).toString(), Qt::ISODate ) );

            DiveProfileVO profile;

            if ( ! query.isNull(13) )
            {
                QString profileString=query.value(13).toString();
                //qDebug( "profileString=%s", profileString.latin1() );
                profile.fromQString( profileString );
            }
            else
            {
                // FIXME: Program crashes on NULL profile
            }

            const QString emptyStr("");

            DiveVO dive( ( query.isNull( 0) ? 0  : query.value( 0).toInt() ),           // number
                         date_time,                                                     // date_time
                         ( query.isNull( 2) ? 0  : query.value( 2).toInt() ),           // sync
                         ( query.isNull( 3) ? 0  : query.value( 3).toInt() ),           // diver_number
                         ( query.isNull( 4) ? emptyStr : query.value( 4).toString() ),  // place
                         ( query.isNull( 5) ? emptyStr : query.value( 5).toString() ),  // location
                         ( query.isNull( 6) ? DBL_MAX : query.value( 6).toDouble() ),   // altitude_mode
                         ( query.isNull( 7) ? DBL_MAX : query.value( 7).toDouble() ),   // water_temperature
                         ( query.isNull( 8) ? DBL_MAX : query.value( 8).toDouble() ),   // start_pressure
                         ( query.isNull( 9) ? DBL_MAX : query.value( 9).toDouble() ),   // end_pressure
                         ( query.isNull(10) ? DBL_MAX : query.value(10).toDouble() ),   // surface_intervall
                         ( query.isNull(11) ? DBL_MAX : query.value(11).toDouble() ),   // max_depth
                         ( query.isNull(12) ? emptyStr : query.value(12).toString() ),  // duration
                         profile,                                                       // profile
                         ( query.isNull(14) ? emptyStr : query.value(14).toString() ),  // log
                         ( query.isNull(15) ? 0  : query.value(15).toInt() ),           // partner_diver_number
                         ( query.isNull(16) ? emptyStr : query.value(16).toString() ),  // weather
                         ( query.isNull(17) ? emptyStr : query.value(17).toString() ),  // sight
                         ( query.isNull(18) ? DBL_MAX : query.value(18).toDouble() ),   // lead
                         ( query.isNull(19) ? DBL_MAX : query.value(19).toDouble() ),   // air_temperature
                         ( query.isNull(20) ? 0  : query.value(20).toInt() ),           // dive_type
                         ( query.isNull(21) ? 0  : query.value(21).toInt() ),           // filling_station_number
                         ( query.isNull(22) ? 0  : query.value(22).toInt() ) );         // bottle_number
            t.push_back( dive );
        }
    }
    else
    {
        qDebug( "Query String: %s", queryString.latin1() );
        throw DiveNotFoundException();
    }
    return t;
}

vector<DiveListVO> DivelogDAO::diveList( const int& diver_number )
{
    vector<DiveListVO> diveList;

    QSqlQuery query;
    QString queryString;

    queryString = "select number, date_time, diver_number, place, location from dive where diver_number=" + QString::number(diver_number);
    query.exec( queryString );

    if ( query.isActive() )
    {
        if ( query.numRowsAffected()<=0 )
        {
            qDebug( "Query String: %s", queryString.latin1() );
            throw DiveNotFoundException();
        }

        while( query.next() )
        {
            /*
            || MySQL++ may deliver null-values which give a BadConversion error
            || -> check for null-values
            || access via index-number is faster then via string
            */

            QString datetime( query.value(1).toString() );   // split up date and time
            QString date=datetime.section('T', 0, 0 );
            QString time=datetime.section('T', 1, 1 );

            DiveListVO dl(  query.value(0).toInt(),  // number
                             date , 																	    		      // date
                             time ,                                                // time
                            query.value(2).toInt() ,  // diver_number
                            query.value(3).toString() ,   // place
                            ( query.isNull(4) ? QString("") : query.value(4).toString() )   // location
                         );

            diveList.push_back( dl );
        }
    }
    else
    {
        qDebug( "Query String: %s", queryString.latin1() );
        throw DiveNotFoundException();
    }

    return diveList;
}
