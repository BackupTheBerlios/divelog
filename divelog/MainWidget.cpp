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
* Filename : mainwidget.cpp                                                   *
* CVS Id 	 : $Id: MainWidget.cpp,v 1.55 2002/08/10 18:15:44 grunwalm Exp $    *
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
* Notes : mn_ = menu                                                          *
******************************************************************************/
static const char *mainwidget_cvs_id="$Id: MainWidget.cpp,v 1.55 2002/08/10 18:15:44 grunwalm Exp $";

// own headers
#include "MainWidget.h"
#include "ProfileField.h"
#include "MyScrollBar.h"
#include "dive104.dat"
#include "NewDiverFrm.h"
#include "NewDiveTypeFrm.h"
#include "NewDiveComputerFrm.h"
#include "NewFillingStationFrm.h"
#include "InfoAreaFrm.h"
#include "DivelogDAO.h"
#include "DiverVO.h"
#include "DiveVO.h"
#include "DiveTypeVO.h"
#include "DiveComputerVO.h"
#include "FillingStationVO.h"
#include "DiveComputerNotFoundException.h"
#include "DiverNotFoundException.h"
#include "DiveNotFoundException.h"
#include "DivelogDAOException.h"
#include "DiveListVO.h"
#include "DiveListViewItem.h"

// Qt
#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qmessagebox.h>
#include <qsplitter.h>
#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qpointarray.h>
#include <qabstractlayout.h>
#include <qfiledialog.h>
#include <qlistview.h>
#include <qheader.h>
#include <qcombobox.h>
#include <qtextview.h>
#include <qlineedit.h>

// others
#include <string>
#include <float.h>

#define MOUSE_TIME_LABEL "Time: "       // Label for time at mouse cursor.
#define MOUSE_DEPTH_LABEL "Depth: "     // Label for depth at mouse cursor.
                                        // FIXME: Move to a better place

using namespace std;

MainWidget::MainWidget( QWidget* parent=0, const char* name=0 )
    : QMainWindow( parent, name )
// -------------------------------------------------
// Use : Constructor.
//       Set up of all contained widgets
//       and connection of SIGNALS and SLOTS
// Parameters  : parent = parent of this widget.
//                null means root window
//               name = name of the widget
// -------------------------------------------------
{
    /*
    || Build up the Menu
    */

    QPopupMenu *db_mn = new QPopupMenu( this );     // make a database menu
    CHECK_PTR( db_mn );                             // better check if it worked...
                                                
    // now add items to the menu
    db_mn->insertItem( "&Import",    this, SLOT( dbImport() ) );
    db_mn->insertItem( "(Re)Load Divelist", this, SLOT( dbLoadDiveList() ) );
    db_mn->insertItem( "New &Diver", this, SLOT( dbNewDiver() ) );
    db_mn->insertItem( "New &Filling Station", this, SLOT( dbNewFillingStation() ) );
    db_mn->insertItem( "New Dive &Type", this, SLOT( dbNewDiveType() ) );
    db_mn->insertItem( "New Dive C&omputer", this, SLOT( dbNewDiveComputer() ) );
    db_mn->insertSeparator();
    db_mn->insertItem( "E&xit",  qApp, SLOT( quit() ), CTRL+Key_Q );

    // same as above (see database menu)
    QPopupMenu *settings_mn = new QPopupMenu( this );
    CHECK_PTR( settings_mn );

    settings_mn->insertItem( "&Communication", this, SLOT( settingsCommunication() ) );

    QPopupMenu *help_mn = new QPopupMenu( this );
    CHECK_PTR( help_mn );

    help_mn->insertItem( "&About", this, SLOT( about() ) );
    help_mn->insertItem( "About &Qt", this, SLOT( aboutQt() ) );
    help_mn->insertItem( "About &License", this, SLOT( aboutLicense() ) );

    // Now create the main menu and insert the submenus
    m_main_mn = new QMenuBar( this );
    CHECK_PTR( m_main_mn );

    m_main_mn->insertItem( "&Database", db_mn );
    m_main_mn->insertItem( "&Settings", settings_mn );
    m_main_mn->insertSeparator();
    m_main_mn->insertItem( "&Help", help_mn );
    m_main_mn->setSeparator( QMenuBar::InWindowsStyle );


    /*
    || Set up Splitters
    */

    m_s1 = new QSplitter( QSplitter::Vertical, this , "m_s1" );
    m_s2 = new QSplitter( QSplitter::Horizontal, m_s1 , "m_s2" );

    m_infoArea    = new InfoAreaFrm( m_s1, "m_infoArea" );
    m_diveListView= new QListView( m_s2, "m_diveListView" );

    /*
    || Set up Profile Area
    */

    m_profileBox = new QVBox( m_s2 ,"m_profileBox" );
    m_profile    = new ProfileField( m_profileBox, "m_profile" );

    /*
    || Set up Scrollbars
    */

    // The offset bar sets the start of the displayed area in the profile field.
    m_offsetBar  = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_offsetBar" );
    // The samples bar sets the zoom-factor
    m_samplesBar = new MyScrollBar( MyScrollBar::Horizontal, m_profileBox, "m_samplesBar" );

    // Handling of the samples bar is a bit weired:
    // The value means 'hide that much values',
    // i.e. 0=show all values
    m_samplesBar->setMinValue( 0 );
    m_samplesBar->setMaxValue( m_profile->samples()-3 );
    m_samplesBar->setValue( 0 );

    m_offsetBar->setMinValue( 0 );
    m_offsetBar->setMaxValue( 0 );

    // *When you see all samples, scrolling is useless, so
    // the offset bar has full length and can't be moved
    // *When zoom is at maximum, the offset bar has minimal length
    // Cross connect the samples bar value to the profile field
    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), m_profile, SLOT( setHideSamples ( int ) ) );
    connect( m_profile   , SIGNAL( hideSamplesChanged( int ) ), m_samplesBar, SLOT( setValue( int ) ) );

    // the offset bar's maximum value depends on the zoom factor=value of samples bar
    connect( m_samplesBar, SIGNAL( valueChanged( int ) ), m_offsetBar, SLOT( setMaxValue( int ) ) );

    // Cross connect the offset bar value to the profile field.
    connect( m_offsetBar , SIGNAL( valueChanged( int ) ), m_profile, SLOT( setTimeStart( int ) ) );
    connect( m_profile   , SIGNAL( timeStartChanged( int ) ), m_offsetBar, SLOT( setValue( int ) ) );

    /*
    || Set up the mouse data fields
    ||
    || Every graph display should show the exact values at the mouse
    || cursor somehow. Of course, we do it here ;)
    ||
    || how can the layout be change to something not equally spaced or
    || at least some more space in the middle... ???
    */
    m_profileMouseDataBox    = new QHBox( m_profileBox, "m_profileMouseDataBox" );

    m_profileMouseTimeLabel  = new QLabel( MOUSE_TIME_LABEL,  m_profileMouseDataBox );
    m_profileMouseTime       = new QLabel( "1:10",  m_profileMouseDataBox );
    m_profileMouseDepthLabel = new QLabel( MOUSE_DEPTH_LABEL, m_profileMouseDataBox );
    m_profileMouseDepth      = new QLabel( "20.5", m_profileMouseDataBox );

    // This doesn't work. Why ?
    m_profileMouseDataSpacer = new QSpacerItem( m_profileMouseTimeLabel->frameRect().width(),
                                                m_profileMouseTimeLabel->frameRect().height(),
                                                QSizePolicy::Fixed,
                                                QSizePolicy::Fixed
                                              );
    // Show new values on mouse move above the profile
    connect( m_profile, SIGNAL( mouseTimeChanged( const QString& ) ), m_profileMouseTime, SLOT( setText( const QString & ) ) );
    connect( m_profile, SIGNAL( mouseDepthChanged( const QString& ) ), m_profileMouseDepth, SLOT( setText( const QString & ) ) );


    /*
    || Set up Tabbed Area
    */

    /*
    || Set up List Area
    */
    // Make header
    m_diveListView->addColumn( "#" );
    m_diveListView->addColumn( "Date" );
    m_diveListView->addColumn( "Time" );
    m_diveListView->addColumn( "Place" );

    m_diveListView->setAllColumnsShowFocus( TRUE );
    m_diveListView->setSorting( 1 ); // Initially sort by date
    m_diveListView->setColumnAlignment( 0 , QListView::AlignRight );

    // Call method to fill the list with data
    dbLoadDiveList();

    m_s1->setResizeMode( m_infoArea, QSplitter::KeepSize );

    // Click or Return selects entry
    connect( m_diveListView, SIGNAL( clicked ( QListViewItem*  ) ), this, SLOT( diveSelected(  QListViewItem*  ) ) );
    connect( m_diveListView, SIGNAL( returnPressed ( QListViewItem*  ) ), this, SLOT( diveSelected(  QListViewItem*  ) ) );
                          
    setCentralWidget( m_s1 );

    // just to get rid of the warning: `const char * xxx_cvs_id' defined but not used
    mainwidget_cvs_id+=0;
}

/*
=================================================================
Slots
=================================================================
*/

/*
|| Menu-slots : implement the menu functions
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
                                              "The diver with number 1 (you?) could not be found"
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
    m_s2->setResizeMode( m_diveListView, QSplitter::KeepSize );

}

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
        qDebug( "Filename: %s", s.latin1() );       // DEBUG output
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
                                                  "The Divecomputer which recorded "+ s +""
                                                  "is not in the database. You have to add it"
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
            catch(...)
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

    qDebug( "NewFillingStationFrm->result=%d", result );

    if ( result ) // the dialogbox was left with "OK"
    {
        qDebug( "Station Name:\t%s", newFillingStationFrm.m_StationName->text().latin1() );
        qDebug( "First Name:\t%s",   newFillingStationFrm.m_FirstName->text().latin1() );
        qDebug( "Last Name:\t%s",    newFillingStationFrm.m_LastName->text().latin1() );

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
    qDebug( "NewDiveTypeFrm->result=%d", result );
    if ( result )
    {
        qDebug( "Dive Type:\t%s", newDiveTypeFrm.m_DiveType->text().latin1() );

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

void MainWidget::dbNewDiveComputer()
// -------------------------------------------------
// Use : Menu slot. Use a dialog box to enter
//       information about a divecomputer
// -------------------------------------------------

{
    DiveComputerVO empty;
    dbNewDiveComputer( empty );
}

void MainWidget::dbNewDiveComputer( const DiveComputerVO& diveComputer )
// -------------------------------------------------
// Use : Menu slot. Use a pre-initialised dialog
//       Box to enter data about divecomputers
// -------------------------------------------------
{
    int result=0;

    // Create a modal dialogbox and fill in values that we know
    // allready
    NewDiveComputerFrm newDiveComputerFrm( diveComputer.serial_number().c_str(),
                                           diveComputer.name().c_str(),
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

void MainWidget::settingsCommunication()
// -------------------------------------------------
// Use : Menu solot. Open a dialogbox te enter
//       settings for the communication with the dive
//       computer
// -------------------------------------------------
{
    qWarning( "Not Implemented: MainWidget::settingsCommunication()");
}

void MainWidget::diveSelected( QListViewItem* item )
// -------------------------------------------------
// Use : Menu slot. Fill all data about the selected
//       Dive into the profile and info area
// -------------------------------------------------
{
    // Create a value object containing the search key(s)
    // Search key is here the dive number
    DiveVO search;
    search.setNumber( item->text(0).toInt() );

    vector< DiveVO > result;

    DivelogDAO db;  // Data Access Object
    try // to find the data for the selected dive
    {
                                      // V Search only by number
        result = db.searchDive( search, "10000000000000000000000" );
    }
    catch( DivelogDAOException e )   // FIXME: better exception handling
    {
        cerr << e << endl;
    }

    if ( result.size() > 1 ) // We search for the primary key, so we expect
    {                         // exactly one result.
        cerr << "Error: found more than one entry for Dive Nr" << item->text( 0 ) << endl
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

        // order is importand here, allthough it shouldn't...
        m_profile->setDepth( diveProfile.maxDepth() );
        m_profile->setSamples( diveProfile.samples() );
        m_profile->setHideSamples( 0, false );
        m_profile->setSecsPerSample( diveProfile.secsPerSample() );
        m_profile->setTimeStart( 0, false );

        m_profile->setProfile( diveProfile.profile() );

        /*
        || Set up info area
        */
        m_infoArea->m_Number->setNum( dive.number() );
        m_infoArea->m_Date->setText( dive.date().c_str() );
        m_infoArea->m_Time->setText( dive.time().c_str() );

        m_infoArea->m_Place->insertItem( dive.place().c_str() );
        m_infoArea->m_Location->insertItem( dive.location().c_str() );
        m_infoArea->m_DiveType->insertItem( QString::number( dive.dive_type() ) ); //FIXME : lookup dive type !
        m_infoArea->m_Buddy->insertItem( QString::number( dive.partner_diver_number() ) ); //FIXME : lookup diver name !
        m_infoArea->m_WaterTemperature->setText( ( dive.water_temperature() == DBL_MAX ? QString("") : QString::number( dive.water_temperature() ) ) );
        m_infoArea->m_AirTemperature->setText( ( dive.air_temperature() == DBL_MAX ? QString("") : QString::number( dive.air_temperature() ) ) );
        m_infoArea->m_MaxDepth->setText( ( dive.max_depth() == DBL_MAX ? QString("") : QString::number( dive.max_depth() ) )  );
        m_infoArea->m_Duration->setText( dive.length().c_str() ); //FIXME : length() vs Duration is inconsistent
    }
}


void MainWidget::about()
// Use: tell the user about divelog
{
    QMessageBox::about( this, "About linux divelog",
                                "Divelog is an electronic logbook for all the divers among us\n\n"
                                "Copyright 2002 Markus Grunwald.\n"
                                "You can use it under the License GPL Version 2 or later\n\n"
                                "For technical support, see\n"
                                "http://www.grunwald.2xs.de/divelog\n");
}

void MainWidget::aboutQt()
// Use: tell the user about the used qt version
{
    QMessageBox::aboutQt( this, "Linux divelog" );
}


void MainWidget::aboutLicense()
// Use: tell the user about the used license
{

}
