/* Copyright (C) 2002 Markus Grunwald */
/* Copyright (C) 1995-2000 Trolltech AS.  All rights reserved. */

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
* Filename : MainWidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.56 2002/09/16 17:08:11 grunwalm Exp $    *
* --------------------------------------------------------------------------- *
* Files subject    : Contains the main widget of the divelog, i.e. most of the*
*                    other Widgets.                                           *
*                    Supplies application with menus etc.                     *
* Owner            : Markus Grunwald (MG)                                     *
* Date of Creation : Sun Aug 12 2001                                          *
* --------------------------------------------------------------------------- *
* To Do List : improve menu                                                   *
*              Feed info area with values                                     *
*              Ability to edit data                                           *
*              lots to come !                                                 *
* --------------------------------------------------------------------------- *
* Notes : migrated to qt-desiger generated Widget on Sat Sep 7 2002           *
******************************************************************************/
static char mainwidget_cvs_id[]="$Id: MainWidget.cpp,v 1.56 2002/09/16 17:08:11 grunwalm Exp $";

// own headers
#include "MainWidget.h"

#include "MyScrollBar.h"
#include "ProfileField.h"
#include "DivelogDAO.h"
#include "DiveListVO.h"
#include "DiveListViewItem.h"
#include "DiverNotFoundException.h"
#include "DiveNotFoundException.h"
#include "DiveComputerVO.h"
#include "DiveComputerNotFoundException.h"
#include "NewDiverFrm.h"
#include "NewFillingStationFrm.h"
#include "FillingStationVO.h"
#include "DiverVO.h"
#include "DiveVO.h"
#include "DiveSO.h"
#include "DivelogDAOException.h"
#include "NewDiveTypeFrm.h"
#include "DiveTypeVO.h"
#include "NewDiveComputerFrm.h"
#include "DiveComputerVO.h"
#include "DiveProfileVO.h"

// Qt
#include <qscrollbar.h>
#include <qlistview.h>
#include <qsplitter.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qstring.h>
#include <qlineedit.h>
#include <qtabwidget.h>
#include <qlabel.h>

// Other
#include <vector>
#include <float.h>

/*
 *  Constructs a MainWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 */
MainWidget::MainWidget( QWidget* parent,  const char* name, WFlags fl )
    : MainWidgetBaseFrm( parent, name, fl )
{
    // Adjust orientation. Designer cant handle this (?) for
    // custom widgets...
    m_samplesBar->setOrientation( MyScrollBar::Horizontal );
    m_offsetBar->setOrientation( MyScrollBar::Horizontal );

    // Handling of the samples bar is a bit weired:
    // The value means 'hide that much values',
    // i.e. 0=show all values
    m_samplesBar->setMinValue( 0 );
    m_samplesBar->setMaxValue( m_profile->samples()-3 );
    m_samplesBar->setValue( 0 );

    m_offsetBar->setMinValue( 0 );
    m_offsetBar->setMaxValue( 0 );

    m_diveListView->setSorting( 1 ); // Initially sort by date
    m_diveListView->setColumnAlignment( 0 , QListView::AlignRight );

    // Call method to fill the list with data
    dbLoadDiveList();

    m_verMoveSplitter->setResizeMode( (QWidget*)m_InfoArea, QSplitter::KeepSize );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    mainwidget_cvs_id[0]+=0;
}

/*  
 *  Destroys the object and frees any allocated resources
 */
MainWidget::~MainWidget()
{
    // no need to delete child widgets, Qt does it all for us
}

/* 
 * public slot
 */
void MainWidget::helpIndex()
{
    qWarning( "MainWidget::helpIndex() not yet implemented!" ); 
}

/* 
 * public slot
 */
void MainWidget::helpContents()
{
    qWarning( "MainWidget::helpContents() not yet implemented!" ); 
}

/* 
 * public slot
 */
void MainWidget::helpAbout()
{
    QMessageBox::about( this, "About linux divelog",
                                "Divelog is an electronic logbook for all the divers among us\n\n"
                                "Copyright 2002 Markus Grunwald.\n"
                                "You can use it under the License GPL Version 2 or later\n\n"
                                "For technical support, see\n"
                                "http://www.grunwald.2xs.de/divelog\n");
}

/* 
 * protected slot
 */
void MainWidget::helpAboutQt()
{
    QMessageBox::aboutQt( this, "Linux divelog" );
}

/* 
 * public slot
 */
void MainWidget::dbImport()
// -------------------------------------------------
// Use : Menu slot. Imports a UDCF File into the
//       database.
// -------------------------------------------------
{
    // Create a standard file dialog
    QString s( QFileDialog::getOpenFileName( QString::null, "Universal Dive Computer Format (*.UDCF)", this ) );
    if ( !s.isEmpty() )
    {
        DivelogDAO db;                              // Database access object
        DiveComputerVO* diveComputer;               // Value object for divecomputers

        bool do_import=true;                        // On the first try, we want import
        bool import_failed=true;                    // a file.
        while ( import_failed && do_import )
        {
            try // to import the UDCF File
            {
                db.importUDCFFile( s.latin1() );    // Insert the file into the database
                import_failed= false;
            }
            /*
            || If the database doesn't know the UDCF files divecomputer, it cannot
            || identify the according diver. So we have to find out !
            */
            catch ( DiveComputerNotFoundException e )
            {
                cerr << endl << e << endl;    
                switch( QMessageBox::information( this, "Divelog",
                                                  "The Divecomputer which recorded \n"+ s +"\n "
                                                  "is not in the database.\n You have to add it "
                                                  "to load this file.\n\nDo you want to add it?",
                                                  "&Add", "&Don't Add",
                                                  0,      // Enter == button 0
                                                  1       // Escape== button 1
                                                )
                      )
                { // Escape == button 1
                case 0: // Add the diver
                    diveComputer = new DiveComputerVO( e.serialNumber(), 0, e.model() );
                    dbNewDiveComputer( *diveComputer ); // FIXME: Check success !!!
                    delete diveComputer;
                    break;
                case 1: // Don't add the diver
                    do_import=false;
                    break;
                default:
                    cerr << "Shouldn't happen !";
                    break;
                }

            }
            catch( DivelogDAOException e )
            {
                cerr << "Exception in MainWidget::dbImport" << endl;
                cerr << endl << e << endl;    
                do_import=false;
            }
            catch( ... )
            {
                cerr << "Exception in MainWidget::dbImport" << endl;
                do_import=false;
            }
        }
        if ( !import_failed )
        {   // Show the new data in the list
            dbLoadDiveList();
        }
    }
}


/* 
 * protected slot
 */
void MainWidget::dbLoadDiveList()
// -------------------------------------------------
// Use : Menu slot. Read a list of most important data
//       from tha database and insert this
//       into the list widget
// -------------------------------------------------
{

    DivelogDAO db;                     // access object to the database
    vector< DiveListVO > *allDivesTmp; // temporary container for the list entries

    bool load_list=true;               // On the first try, we want to load the list
    bool list_failed=true;             // No try yet, so no errors
    while ( list_failed && load_list ) // Loop as long as we want to load data and there are errors
    {
        try // to load the list items from database
        {
            allDivesTmp = new vector < DiveListVO > ( db.diveList( 1 ) ); // FIXME: get diver number from rc file
            list_failed=false;
        }
        catch( DiverNotFoundException e)
        {
            cerr << e << endl ;
            switch( QMessageBox::information( this, "Divelog",
                                              "The diver with number 1 (you?) could not be found "
                                              "in the database. Do you want to add him/her now?",
                                              "&Add", "&Don't Add",
                                              0,      // Enter == button 0
                                              1       // Escape== button 1
                                            )
                  )
            { // Escape == button 1
            case 0: // Add the diver
                dbNewDiver();
                break;
            case 1: // Don't add the diver
                load_list=false;
                allDivesTmp = new vector< DiveListVO >;
                break;
            default:
                cerr << "In MainWidget::dbLoadDiveList: unknown exception !";
                break;
            }
        }
        catch( DiveNotFoundException e )
        {
            cerr << e << endl ;
            QMessageBox::information( this, "Divelog",
                                      "There are none of your dives in the Database.",
                                      "&Ok");
            allDivesTmp = new vector< DiveListVO >;
            list_failed=false;
        }
    }

    // Ensure that we have a valid pointer
    CHECK_PTR( allDivesTmp );
    /*
    || Strange. Didn't manage to make this an "int i" loop
    || Had to do it with an iterator...
    */
    // First clean the list.
    m_diveListView->clear();

    // Now iterate over all list items and insert them into
    // the list widget
    vector< DiveListVO >::iterator i;
    for ( i=allDivesTmp->begin(); i!= allDivesTmp->end(); i++ )
    {
        (void) new DiveListViewItem( *i, m_diveListView );
    }

    delete allDivesTmp;
    // Now we should adapt the lists size to the new data
    // This doesn't work, yet...
    m_diveListView->updateGeometry();
    m_horMoveSplitter->setResizeMode( m_diveListView, QSplitter::KeepSize );
}

/* 
 * protected slot
 */
void MainWidget::dbNewDiveComputer( const DiveComputerVO & diveComputer )
// -------------------------------------------------
// Use : Menu slot. Use a pre-initialised dialog
//       Box to enter data about divecomputers
// -------------------------------------------------
{
    int result=0;

    // Create a modal dialogbox and fill in values that we know
    // allready
    NewDiveComputerFrm newDiveComputerFrm( diveComputer.serial_number(),
                                           diveComputer.name(),
                                           this,
                                           "newDiveComputer" );
    result=newDiveComputerFrm.exec();

    if ( result ) // Dialogbox left with "OK"
    {
        // Create a value object with the data from the dialogbox
        DiveComputerVO diveComputer( newDiveComputerFrm.m_SerialNumber->text().latin1(),
                                     newDiveComputerFrm.diver_number(),
                                     newDiveComputerFrm.m_ComputerName->text().latin1()
                                   );
        DivelogDAO db; // Database Access Object
        try // to insert the value object into the database
        {
            db.insertDiveComputer( diveComputer );
        }
        catch( DivelogDAOException e )  
        {
            cerr << e << endl;
        }
    }
}

/* 
 * protected slot
 */
void MainWidget::dbNewDiveComputer()
// -------------------------------------------------
// Use : Menu slot. Use a dialog box to enter
//       information about a divecomputer
// -------------------------------------------------

{
    DiveComputerVO empty;
    dbNewDiveComputer( empty );
}

/* 
 * protected slot
 */
void MainWidget::dbNewDiveType()
// -------------------------------------------------
// Use : Menu slot. Use a dialog box to enter data
//       about a dive type and insert this into the
//       database
// -------------------------------------------------
{
    int result=0;
    NewDiveTypeFrm newDiveTypeFrm( this, "newDiveTypeFrm", true );
    result=newDiveTypeFrm.exec();

    // This is stereotype to the other methods... see
    // dbNewDiveComputer, dbNewDiver ...
    if ( result )
    {
        DiveTypeVO diveType( 0, // Auto increment
                             newDiveTypeFrm.m_DiveType->text().latin1()
                           );
        DivelogDAO db;
        try
        {
            db.insertDiveType( diveType );
        }
        catch( DivelogDAOException e )  
        {
            cerr << e << endl;
        }
    }
}

/* 
 * protected slot
 */
void MainWidget::dbNewDiver()
// -------------------------------------------------
// Use : Open a dialog to enter data about a new Diver
//			 and insert into the database
// -------------------------------------------------
{
    int result=0;
    // Create the modal dialog...
    NewDiverFrm newDiverFrm( this, "newDiverFrm", true ); // parent, name, modal

    // ... and show it.
    result=newDiverFrm.exec();
    if ( result ) // Dialog left with "Ok" = we have some data
    {
        /*
        || Insert the diver into the database
        */
        // i.e. fill in the value object
        DiverVO diver( 0, // Auto increment
                       newDiverFrm.m_FirstName->text().latin1(),
                       newDiverFrm.m_LastName->text().latin1(),
                       newDiverFrm.m_Brevet->text().latin1(),
                       newDiverFrm.m_Street->text().latin1(),
                       newDiverFrm.m_HouseNumber->text().latin1(),
                       newDiverFrm.m_Zip->text().toUInt(),
                       newDiverFrm.m_Place->text().latin1(),
                       newDiverFrm.m_Phone->text().latin1(),
                       newDiverFrm.m_EMail->text().latin1()
                     );

        DivelogDAO db; // connect to the database
        try
        {
            db.insertDiver( diver ); // and insert the data.
        }
        catch( DivelogDAOException e )
        {
            cerr << e << endl; // show error mesages
        }
    }
}

/* 
 * protected slot
 */
void MainWidget::dbNewFillingStation()
// -------------------------------------------------
// Use : Menu slot. Use a dialog box to enter data
//       about a filling station and insert this into
//       the database
// -------------------------------------------------
{
    int result=0;
    // Create a new modal dialogbox
    NewFillingStationFrm newFillingStationFrm( this, "newFillingStation", true );
    result=newFillingStationFrm.exec();

    if ( result ) // the dialogbox was left with "OK"
    {
        // Create a value object for the fillingstation and fill in the new data
        FillingStationVO fillingStation( 0, // Auto increment
                                         newFillingStationFrm.m_StationName->text().latin1(),
                                         newFillingStationFrm.m_FirstName->text().latin1(),
                                         newFillingStationFrm.m_LastName->text().latin1()
                                       );
        DivelogDAO db; // Database access object
        try // to insert the fillingstation into the database
        {
            db.insertFillingStation( fillingStation );
        }
        catch( DivelogDAOException e )  
        {
            cerr << e << endl;
        }
    }
}

/* 
 * protected slot
 */
void MainWidget::settingCommunication()
// -------------------------------------------------
// Use : Menu solot. Open a dialogbox to enter
//       settings for the communication with the dive
//       computer
// -------------------------------------------------
{
    qWarning( "MainWidget::settingCommunication() not yet implemented!" ); 
}

/* 
 * protected slot
 */
void MainWidget::helpAboutLicense()
{
    qWarning( "MainWidget::helpAboutLicense() not yet implemented!" ); 
}

/* 
 * protected slot
 */
void MainWidget::diveSelected( QListViewItem * item )
// -------------------------------------------------
// Use : Menu slot. Fill all data about the selected
//       Dive into the profile and info area
// -------------------------------------------------
{
    // Create a value object containing the search key(s)
    // Search key is here the dive number
    DiveSO search;
    search.number( item->text(0).toInt() );

    vector< DiveVO > result;

    DivelogDAO db;  // Data Access Object
    try // to find the data for the selected dive
    {
                                      
        result = db.searchDive( search );
    }
    catch( DivelogDAOException e )   // FIXME: better exception handling
    {
        cerr << e << endl;
    }

    if ( result.size() > 1 ) // We search for the primary key, so we expect
    {                         // exactly one result.
        cerr << "Error: found more than one entry for Dive Nr" << item->text( 0 ).latin1() << endl
             << "The Database is corrupt !" << endl;
    }
    else if ( result.empty() ) // No results. Chances are good, this is caught by exception,
    {                          // and it shouldn't happen anyway...
        QMessageBox::warning( this, "Divelog",
                                   "This dive was not found in the database.\n"
                                   "Maybe it is corrupt :(" );
    }
    else // we have one perfect result
    {
        DiveVO dive = result.front(); // Our wanted data is the first (and only) one

        /*
        || Set up profile field
        */

        DiveProfileVO diveProfile = dive.profile();

        m_profile->setProfile( diveProfile );
        m_profile->setHideSamples( 0, false );
        m_profile->setTimeStart( 0, false );

        /*
        || Set up info area
        */
        //m_InfoArea->
        m_Number->setNum( dive.number() );
        m_DateTime->setText( dive.date_time().toString( Qt::LocalDate ) );

        m_Place->setText( dive.place() );
        m_Location->setText( dive.location() );
        m_DiveType->setText( QString::number( dive.dive_type() ) ); //FIXME : lookup dive type !
        m_Buddy->setText( QString::number( dive.partner_diver_number() ) ); //FIXME : lookup diver name !
        m_WaterTemperature->setText( ( dive.water_temperature() == DBL_MAX ? QString("") : QString::number( dive.water_temperature() ) ) );
        m_AirTemperature->setText( ( dive.air_temperature() == DBL_MAX ? QString("") : QString::number( dive.air_temperature() ) ) );
        m_MaxDepth->setText( ( dive.max_depth() == DBL_MAX ? QString("") : QString::number( dive.max_depth() ) )  );
        m_Duration->setText( dive.duration() );
    }
}


